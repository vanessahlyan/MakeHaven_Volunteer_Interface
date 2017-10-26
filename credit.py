from cs50 import get_int

card_number = get_int("Provide a credit card number: ")
digit_sum = 0

n = card_number // 10

while n > 0:
    two_times_digit = n % 10 * 2
    if two_times_digit >= 10:
        product_second_digit = two_times_digit % 10
        product_first_digit = two_times_digit // 10
        digit_sum += product_second_digit + product_first_digit
    else:
        digit_sum += two_times_digit
    n //= 100

    # beginning from 2nd to last digit, going through every other digit
    # multiplying the digit by 2 and adding it to the digit sum

a = card_number
while a > 0:
    digit_sum += a % 10
    a //= 100
    # adding the rest of the digits to the digit_sum

if digit_sum % 10 == 0:
    # figure out first two digits of card number
    b = card_number
    while b > 100:
        b //= 10
    # b now represents the first two digits of the card number

    # figure out length of card_number
    num_digits = 0
    c = card_number
    while c > 0:
        num_digits += 1
        c //= 10
        # num_digits now represents the length of card_number

    # if first two digits are 34 or 37
    if b == 34 or b == 37:
        if num_digits == 15:
            print("AMEX")
        else:
            print("INVALID")

    # if first two digits are between 51 and 55
    elif 51 <= b and b <= 55:
        if num_digits == 16:
            print("MASTERCARD")
        else:
            print("INVALID")

    # if first two digits are between 40 and 49
    elif 40 <= b and b <= 49:
        if num_digits == 13 or num_digits == 16:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")
else:
    print("INVALID")
