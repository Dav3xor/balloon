from flask import Flask
from flask import render_template
from flask import request
from flask import redirect
import jinja2
import sqlite3
import wikipediaapi

print (wikipediaapi.__version__)
#set up wikipediaAPI agent
wiki = wikipediaapi.Wikipedia(user_agent='MyProjectName (merlin@example.com)', language='en')

app = Flask(__name__)

stmt1 = "INSERT INTO targets (latitude,longitude,name,comment) VALUES (?,?,?,?);"
stmt2 = "SELECT latitude,longitude,name,comment,created,priority,approved FROM targets ORDER BY rowid DESC LIMIT 5;" 


def return_index(conn,**args):
    cursor = conn.cursor()

    error = args['error'] if 'error' in args else None

    last_few = cursor.execute(stmt2).fetchall()
    return render_template('index.html',error=error, last_few=last_few)

@app.route("/new", methods = ['POST'])
def new():
    # Connect to SQLite database
    conn = sqlite3.connect('db.sqlite3')
    cursor = conn.cursor()
    
    latitude  = request.form['latitude']
    longitude = request.form['longitude']
    comment   = request.form['comment']
    place     = request.form['place'] \

    error     = None

    if place and not (latitude and longitude):
        place = place.strip()
        page = wiki.page(place)
        if page.exists() and hasattr(page,'coordinates'):
            coords              = wiki.coordinates(page)
            latitude, longitude = coords[0].lat, coords[0].lon
            if not comment:
                comment = page.summary[:200]+'...'
        else:
            error = "Wikipedia Page Not Found..."
    
    if not (latitude and longitude):
        error = "No Coordinates"
    else:
        cursor.execute(stmt1,
                       (latitude,longitude,place,comment))
        conn.commit()
    return return_index(conn,error=error)
    
@app.route("/")
def index():
    # Connect to SQLite database
    conn = sqlite3.connect('db.sqlite3')
    cursor = conn.cursor()

    last_few = cursor.execute(stmt2).fetchall()
    return return_index(conn)

