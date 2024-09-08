#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int product_digits(int n);

int main(void)
{
    string digits = get_string("Number: ");
    int credit_length = strlen(digits);
    char first2[] = {digits[0], digits[1]};
    int first2_numbers = atoi(first2);
    int sum_numbers_multiply_2 = 0;
    int sum_numbers_not_multiply_2 = 0;
    char revers_digits[20];
    for (int i = credit_length - 1; i >= 0; i--)
    {
        revers_digits[(credit_length - 1) - i] = digits[i];
    }

    for (int i = 0; i < credit_length; i++)
    {
        int current_number = revers_digits[i] - '0';
        if (i % 2 == 1)
        {
            int digit = current_number * 2;
            if (digit > 9)
            {
                sum_numbers_multiply_2 += product_digits(digit);
            }
            else
            {
                sum_numbers_multiply_2 += digit;
            }
        }
        else
        {
            sum_numbers_not_multiply_2 += current_number;
        }
    }
    int final_digit = (sum_numbers_not_multiply_2 + sum_numbers_multiply_2) % 10;
    if (final_digit == 0)
    {
        if ((first2_numbers == 34 || first2_numbers == 37) && credit_length == 15)
        {
            printf("AMEX\n");
        }
        else if (first2[0] == '4' && (credit_length == 13 || credit_length == 16))
        {
            printf("VISA\n");
        }
        else if ((first2_numbers >= 51 && first2_numbers <= 55) && credit_length == 16)
        {
            printf("MASTERCARD\n");
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

int product_digits(int n)
{
    char digits[2];
    int sum = 0;
    sprintf(digits, "%i", n);
    int len = strlen(digits);
    for (int i = 0; i < len; i++)
    {
        sum += digits[i] - '0';
    }
    return sum;
}
