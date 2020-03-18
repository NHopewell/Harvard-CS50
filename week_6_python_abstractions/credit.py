sum_every_other, sum_rest, total = 0, 0, 0

prompt = True

while prompt:
    try:
        cc_num = int(
            input("Number: "))
        prompt = False
    except ValueError:
        print("Must enter a number - try again.")

str_cc_num = str(cc_num)
cc_len = len(str_cc_num)

for i in range(len(str_cc_num)-2, -1, -2):
    n = int(str_cc_num[i]) * 2

    if n > 9:
        str_n = str(n)
        for j in str_n:
            sum_every_other += int(j)
    else:
        sum_every_other += n

for i in range(len(str_cc_num)-1, -1, -2):
    n = int(str_cc_num[i])
    sum_rest += n

total += sum_every_other + sum_rest

if ((total % 10) == 0):

    first_digit = int(str_cc_num[0])
    first_two_digits = int(str_cc_num[0] + str_cc_num[1])

    if ( (cc_len == 15) and (first_two_digits in (34, 37)) ):
        print("AMEX")
    elif ( (cc_len == 16) and (first_two_digits in (51, 52, 53, 54, 55)) ):
        print("MASTERCARD")
    elif ( (cc_len == 16) and (first_digit == 4) ):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")