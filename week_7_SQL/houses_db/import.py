import sys
import csv
from cs50 import SQL

# check args
if len(sys.argv) != 2:
    print("""Please enter one arguement (the name of a csv file) """
          """from the command line.""")
    sys.exit(1)

# Create database
# open("students.db", "w").close()

# sqlite db
db = SQL("sqlite:///students.db")

# read in
with open(sys.argv[1], "r") as characters:

    #create dict reader
    reader = csv.DictReader(characters)

    for row in reader:
        names = row["name"].split()

        # if no middle name, send NULL
        if len(names) < 3:
            names.insert(1, None)

        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
            names[0], names[1], names[2], row["house"], row["birth"])