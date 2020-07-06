from flask import Flask, render_template
import random

app = Flask(__name__)

@app.route("/")
def index():
    number = random.randint(0,1)
    return render_template("index.html", name="Nick", number=number)

@app.route("/goodbye")
def bye():
    return "Goodbye!"