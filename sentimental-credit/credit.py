from cs50 import get_int

credit = str(get_int("Number: "))
first2 = credit[0] + credit[1]
length = len(credit)
multiply_digits = 0
normal_digits = 0

for i in range(length):
    # Accessed credit number be reversed
    number = int(credit[length-1-i])
    # Get every last other digits
    if i % 2 == 1:
        x2 = number*2
        # If there number more than 9 iterate on each digit's and sum them
        if x2 > 9:
            tmp = str(x2)
            x2 = 0
            for i in tmp:
                x2 += int(i)
        # The digits are multiply by 2
        multiply_digits += x2
    else:
        # The odd normal digits
        normal_digits += number
result = multiply_digits+normal_digits
if (result % 10) == 0:
    if first2 in ['34', '37'] and length == 15:
        print("AMEX")
    elif first2[0] == '4' and length in [13, 16]:
        print("VISA")
    elif int(first2) >= 51 and int(first2) <= 55:
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")
