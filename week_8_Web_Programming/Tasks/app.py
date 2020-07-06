from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def tasks():
    return render_template("tasks.html")

@app.route("/add")
def add():
    return "Add new task"