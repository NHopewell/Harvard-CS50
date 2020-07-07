import sqlite3, json
from flask import Flask, g, render_template

app = Flask(__name__)
DATABASE = 'lecture.db'

def connect():
    """
    """
    db = getattr(g, '_database', None)
    if not db:
        db = g._database = sqlite3.connect(DATABASE)
        db.row_factory = dict_factory

    return db

def dict_factory(cursor, row):
    """
    """
    d = {}
    for idx, col in enumerate(cursor.description):
        d[col[0]] = row[idx]
    return d

def query_db(query, args=(), one=False):
    """
    """
    cur = connect().cursor()
    cur.execute(query, args)
    res = json.dumps(cur.fetchall())
    cur.close()

    return res

@app.route("/")
def index():
    """
    """
    rows = query_db('SELECT * FROM registrants')

    #return rows
    return render_template("index.html", rows=rows)