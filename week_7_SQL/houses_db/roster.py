import sys
import csv
from cs50 import SQL

# check args
if len(sys.argv) != 2:
    print("""Please enter one arguement (the name of a csv file) """
          """from the command line.""")
    sys.exit(1)


# sqlite db
db = SQL("sqlite:///students.db")

result_set = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", sys.argv[1])

for row in result_set:
    if not row["middle"]:
        print(row["first"], row["last"], row["birth"])
    else:
        print(row["first"], row["middle"], row["last"], row["birth"])