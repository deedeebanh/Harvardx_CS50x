+#include <cs50.h>
#include <stdio.h>
// check50 cs50/labs/2021/x/population
// style50 population.c
// submit50 cs50/labs/2021/x/population
// results: https://submit.cs50.io/users/myzzdeedee/cs50/labs/2021/x/population
int main(void)
{
    int start_size;
    int end_size;
    int counter;
    do
    {
        start_size = get_int("Start size: ");
    } while (start_size < 9);
    do
    {
        end_size = get_int("End size: ");
    } while (start_size > end_size);
    counter = 0;
    while (end_size > start_size)
    {
        start_size += start_size/3 - start_size/4;
        counter++;
    }
    printf("Years: %i\n", counter);
}