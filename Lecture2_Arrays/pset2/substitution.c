./sort1 reversed10000.txt#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) < 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string key = argv[1];

    // string key = "VcHpRzGjNtLsKfBdQwAxEuYmOi";

    // Duplicates in key
    // YFDTSMPBVIEERGHWONUAKLQXCZ
    // BBCCEFGHIJKLMNOPQRSTUVWXYZ
    for (int i=0;i < 26;i++)
    {
        if ((key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A' && key[i] <= 'Z')) // Valid letters a-z, A - Z
        {
            for (int j=i+1; j < 26; j++) // Letter shouldn't repeat
            {
                if (key[i] == key[j])
                {
                    return 1;
                }
            }
        }
        else
        {
            return 1;
        }
    }
    string s = get_string("plaintext: ");
    //string s = "hello, world";
    //printf("plaintext: %s\n", s);
    printf("ciphertext: ");

    for (int i = 0; i < strlen(s); i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            for (int j=0;j<26;j++)
            {
                if (s[i] == alphabet[j])
                {
                    printf("%c",toupper(key[j]));
                }
                else if (s[i] == tolower(alphabet[j]))
                {
                    printf("%c",tolower(key[j]));
                }
            }
        }
        else
        {
            printf("%c",s[i]);
        }
    }
    printf("\n");

    return 0;
}