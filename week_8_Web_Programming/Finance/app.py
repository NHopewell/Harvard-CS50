import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    rows = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
    user_total_cash = rows[0]["cash"]

    stock_counts = db.execute("SELECT user_id, stock_symbol, SUM(num_shares) FROM purchases GROUP BY user_id, stock_symbol HAVING user_id = :id;", id=session["user_id"])

    for row in stock_counts:
        current_price = lookup(row["stock_symbol"])["price"]
        total_value = row["SUM(num_shares)"] * current_price
        row["Current Price"] = current_price
        row["TOTAL"] = total_value

    total = sum(row["TOTAL"] for row in stock_counts)

    return render_template("index.html", stock_counts=stock_counts, cash=usd(user_total_cash), total=usd(total))

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    rows = db.execute("SELECT * FROM purchases WHERE user_id = :user_id", user_id=session["user_id"])
    total_spent = db.execute("SELECT SUM(total_cost) FROM purchases GROUP BY user_id HAVING user_id = :id", id=session["user_id"])
    total_spent = total_spent[0]['SUM(total_cost)']
    remainder = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
    remainder = remainder[0]["cash"]
    all_funds = remainder + total_spent

    return render_template("history.html", rows=rows, cash=usd(remainder), all_funds=usd(all_funds))


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == 'POST':
        # Ensure stock was submitted
        if not request.form.get("stockSymbol"):
            return apology("must provide a stock symbol to look up", 403)

        stock = lookup(request.form.get("stockSymbol"))

        if not stock:
            return render_template("quoted.html")

        return render_template("quoted.html", stock_name=stock["name"],
                        stock_symbol=stock["symbol"], stock_value=stock["price"])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == 'POST':

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)
        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation of password", 403)

        username = request.form.get("username")
        pw = request.form.get("password")
        confirm_pw = request.form.get("confirmation")

        if pw != confirm_pw:
            return redirect("/register")

        _hashed_pw = generate_password_hash(pw)

        db.execute("INSERT INTO users (username, hash) VALUES (:name, :hash);",
                    name=username, hash=_hashed_pw)

        # Redirect user to home page
        return redirect("/")
    else:
        return render_template("register.html")

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == 'POST':
        # query db to mske sure the user can afford the stock (check cash and compare to price of stock (using lookup() x number of stock) the purchase the stock for user)
        # will have to add more tables to the db to store users stocks (stock bought, how many shares bought, who bought the stock)

        # Ensure user input a stock symbol
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Must provide a stock symbol", 403)

        quantity = int(request.form.get("shares"))
        if not quantity:
            return apology("Must provide a quantity to buy", 403)
        elif quantity <= 0:
            return apology("Must provide a positive number of stocks to buy", 403)

        stock = lookup(symbol)
        if not stock:
            return apology("Stock symbol entered is not valid", 403)

        total_cost = stock["price"] * quantity

        rows = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
        user_total_cash = rows[0]["cash"]

        if user_total_cash < total_cost:
            return apology("You do not have enough funds", 403)

        db.execute("INSERT INTO purchases (user_id, stock_symbol, stock_value, num_shares, total_cost) VALUES (:user, :symbol, :value, :shares, :total);",
                user=session["user_id"], symbol=symbol, value=stock["price"], shares=quantity, total=total_cost)

        remainder = user_total_cash - total_cost

        db.execute("UPDATE users SET cash = :remainder WHERE id = :id", remainder=remainder, id=session["user_id"])

        rows = db.execute("SELECT * FROM purchases WHERE user_id = :user_id", user_id=session["user_id"])

        total_spent = db.execute("SELECT SUM(total_cost) FROM purchases GROUP BY user_id HAVING user_id = :id", id=session["user_id"])

        total_spent = total_spent[0]['SUM(total_cost)']

        all_funds = remainder + total_spent


        return render_template("history.html", rows=rows, cash=usd(remainder), all_funds=usd(all_funds))
    else:
        return render_template("buy.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == 'POST':
        # sell specified num of stock, first check if they own that stock and own enough of it,
        # update the users total cash with the share price (lookup()) x num shares
        # update tables of the users stock once they have sold their stock
        pass
    else:
        # display form of what stock they want to buy and how many shares
        pass

    #return apology("TODO")
    #return apology("TODO")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
