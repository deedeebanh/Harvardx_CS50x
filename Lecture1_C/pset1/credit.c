#include<cs50.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
// make *: to compile
// style50 *.c: to check code readability
// ./* : run the code
// check50 cs50/problems/*: check code compiles and works as it should
// check50 cs50/problems/2021/x/credit
// style50 credit.c
// submit50 cs50/problems/2021/x/credit


// Prompt for input
// Calculate checksum
// Check for card length and starting digits
// Print AMEX, MASTERCARD, VISA, or INVALID.

int main(void)
{
    long number;
    int remainder_num = 0;
    int i = 0;
    int digit;
    int sumDigit = 0;
    long AMEX = number/1e+13; // American Express uses 15-digit numbers
    long MasterCard = number/1e+14; // MasterCard uses 16-digit numbers,


    do
    {
        number = get_long("Number: ");
    } while(number < 0);


    while (number > 0)
    {
        remainder_num = number%10;
        number = number/10;
        if (i%2 != 0) // even
        {
            // multiply each of the even digits by 2
            digit = remainder_num*2;
            // If Number has 2 Digits, add those products’ digits
            if (digit > 9)
            {
                digit = digit%10 + digit/10;
            }
            sumDigit += digit;
        }
        else // odd, sum those that weren’t multiplied by 2
        {
            sumDigit += remainder_num;
        }
        i++;
    }

    if (sumDigit%10 == 0)
    {
        // Visa uses 13- and 16-digit numbers
        // all Visa numbers start with 4
        if ((i == 13 || i == 16) && remainder_num == 4)
        {
            printf("VISA\n");
        }

        // start with 34 or 37
        else if (i == 15 && (AMEX == 34 || AMEX == 37))
        {
            printf("AMEX\n");
        }
        // numbers start with 51, 52, 53, 54, or 55
        else if (i == 16 && (MasterCard >= 51 && MasterCard <= 55))
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
