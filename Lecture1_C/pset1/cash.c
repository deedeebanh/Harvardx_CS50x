#include<cs50.h>
#include<stdio.h>
#include<math.h>
// make *: to compile
// style50 *.c: to check code readability
// ./* : run the code
// check50 cs50/problems/*: check code compiles and works as it should
// check50 cs50/problems/2021/x/cash
// style50 cash.c
// submit50 cs50/problems/2021/x/cash

int main(void)
{
    float dollars;
    int pennies = 1;
    int nickel  = 5;
    int dime    = 10;
    int quarter = 25;
    int counter = 0;

    do{
        dollars = get_float("Change owed: ");
    }while(dollars < 0);

    int cents = round(dollars * 100);

    while (cents >= quarter)
    {
        cents -= quarter;
        counter++;
    }
    while (cents >= dime)
    {
        cents -= dime;
        counter++;
    }
    while (cents >= nickel)
    {
        cents -= nickel;
        counter++;
    }
    while (cents >= pennies)
    {
        cents -= pennies;
        counter++;
    }
    printf("%i\n",counter);
}
