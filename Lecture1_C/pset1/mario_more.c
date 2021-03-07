#include <cs50.h>
#include <stdio.h>
// make *: to compile
// style50 *.c: to check code readability
// ./* : run the code
// check50 cs50/problems/*: check code compiles and works as it should
// check50 cs50/problems/2021/x/mario/more
// style50 mario_more.c
// submit50 cs50/problems/2021/x/mario/more
int main(void)
{
    int num;
    int countup;
    int countdown;
    do
    {
        num = get_int("Height: ");
    }while (num > 8 || num < 1);

    countup = 1;
    countdown = num - 1;
    while (countup <= num)
    {
        for (int j = countdown; j > 0; j--)
        {
            printf(" ");
        }
        for (int i = 0; i < countup; i++)
        {
            printf("#");
        }
        printf(" ");
        for (int i = 0; i < countup; i++)
        {
            printf("#");
        }
        printf("\n");
        countup++;
        countdown--;
    }
}