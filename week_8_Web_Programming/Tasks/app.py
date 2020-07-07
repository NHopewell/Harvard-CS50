from flask import Flask, redirect, render_template, request, session
from flask_session import Session

app = Flask(__name__)
app.config["SESSION_PERMANENT"] = False
#store on user file system
app.config["SESSION_TYPE"] = "filesystem"
#enable sessions for this flask app
Session(app)

# tasks todo
todos = []

@app.route("/")
def tasks():
    #if user does not have todos in their current session, add
    if "todos" not in session:
        session["todos"] = []

    #return users session todos
    return render_template("tasks.html", todos=session["todos"] )

@app.route("/add", methods=["GET", "POST"])
def add():
    if request.method == 'GET':
        return render_template("add.html")
    else:
        todo = request.form.get("task")
        session["todos"].append(todo)

        return redirect("/")