#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
/*

plaintext       H   E   L   L   O
+ key	        1	1	1	1	1
= ciphertext	I	F	M	M	P
*/

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //string s = get_string("plaintext: ");
    string s = "be sure to drink your Ovaltine";
    printf("ciphertext: ");
    int key = atoi(argv[1]);
    //printf("key: %d\n",key);
    for (int i = 0; i < strlen(s); i++)
    {
        printf("%c",s[i]);
    }
    printf("\n");

    for (int i = 0; i < strlen(s); i++)
    {
        printf("%c",s[i]+key);
    }
    printf("\n");

    return 0;
}