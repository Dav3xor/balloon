#parse text file with list of places and makes a c header file

import wikipediaapi
import sqlite3
from jinja2 import Environment, FileSystemLoader


#set up wikipediaAPI agent
wiki = wikipediaapi.Wikipedia(user_agent='MyProjectName (merlin@example.com)', language='en')

#set up counter to represent the priority of a place
priority_counter = 0

conn   = sqlite3.connect('web/db.sqlite3')
cursor = conn.cursor()

targets = cursor.execute('SELECT latitude, longitude, priority, name, comment, rowid FROM targets ORDER BY rowid;').fetchall()
        
env      = Environment(loader=FileSystemLoader(""))
template = env.get_template("wishlist.jinja2")
result   = template.render(targets=targets)

print(result)
