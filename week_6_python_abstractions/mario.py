pyramid_size = 0
filler = ' '
block = '#'

while (pyramid_size < 1 or pyramid_size > 8):
    try:
        pyramid_size = int(
            input("Please enter a number between 1 and 8 to represent the pyramids height: "))
    except ValueError:
        print("Must enter a number - try again")

for i in range(1, pyramid_size+1):
    print(
        f"{filler * (pyramid_size - i)}{block * i}{filler * 2}{block * i}")