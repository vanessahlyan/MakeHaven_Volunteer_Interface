#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long long card_number = get_long_long("Provide a credit card number: ");

    long long digit_sum = 0;

    for (long long n = card_number / 10; n > 0; n = n / 100)
    {
        long long two_times_digit = n % 10 * 2;
        if (two_times_digit >= 10)
        {
            long long second_product_digit = two_times_digit % 10;
            long long first_product_digit = two_times_digit / 10;
            digit_sum += second_product_digit + first_product_digit;
        }
        else
        {
            digit_sum += two_times_digit;
        }
        //beginning from 2nd to last digit, going through every other digit
        //multiplying the digit by 2 and adding it to the digit_sum

    }

    for (long long a = card_number; a > 0; a = a / 100)
    {
        digit_sum = digit_sum + a % 10;

        //adding the rest of the digits to the digit_sum
    }


    if (digit_sum % 10 == 0)
    {

        //figure out first two digits of card number
        long long b = card_number;
        while (b > 100)
        {
            b /= 10;
        }
        //b now represents the first two digits of the card number



        //figure out length of card_number
        long long num_digits = 0;
        for (long long c = card_number; c > 0; c = c / 10)
        {
            num_digits = num_digits + 1;
        }
        //num_digits now represents the length of card_number


        //if first two digits are 34 or 37
        if (b == 34 || b == 37)
        {
            if (num_digits == 15)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        //if first two digits are between 51 and 55
        else if (51 <= b && b <= 55)
        {
            if (num_digits == 16)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        //if first two digits are between 40 and 49
        else if (40 <= b && b <= 49)
        {
            if (num_digits == 13 || num_digits == 16)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }


}