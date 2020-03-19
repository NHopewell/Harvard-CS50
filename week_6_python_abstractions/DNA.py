import sys
import csv

# database csv data
database = sys.argv[1]
database_data = csv.DictReader(open(database))
# sequence text file
sequence = sys.argv[2]
f = open(sequence, "r")
sequence_data = f.read()
f.close()

# Short Tandem Repeats in DNA sequences
STR = ('AGATC','AATG','TATC')
# counters for each STR
STR_counter_dict = {
    'AGATC' : 0,
    'AATG' : 0,
    'TATC' : 0
}

for i in range(len(sequence_data)):
    if (sequence_data[i: i+4] in STR) or (sequence_data[i: i+5] in STR):
        # must change shift constant
        if sequence_data[i: i+4] in STR:
            SHIFT = 4
        elif sequence_data[i: i+5] in STR:
            SHIFT = 5

        # remember match
        match = sequence_data[i: i+SHIFT]
        # increment to track and shift position in array
        num_repeats = 1
        multiplier = 1
        # continue until match not repeated
        while sequence_data[i+(SHIFT*multiplier): (i+SHIFT) + (SHIFT*multiplier)] == match:
            num_repeats += 1
            multiplier += 1
        # update dict with max repeats at each key
        if num_repeats > STR_counter_dict[match]:
            STR_counter_dict[match] = num_repeats

# iter rows of db data
for row in database_data:
    # flag condition
    most_likely = True
    # the indexes we care about, not all SRIs are important for DNA matching - store in tuple
    person_SRI = (row['AGATC'], row['AATG'], row['TATC'])
    # iterate through zipped collections and compare
    for k, v in zip(STR_counter_dict.values(), person_SRI):
        if k != int(v):
            most_likely = False
    # return name if most_likely still true after iterating through rows
    if most_likely:
        print( row['name'] )
        sys.exit(0)
# if no match
print("No match")
