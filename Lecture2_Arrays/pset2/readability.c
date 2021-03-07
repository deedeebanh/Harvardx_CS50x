#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/*
./readability
Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
Grade 3
*/
float countLetters(string s);
float countSentences(string s);
float countWords(string s);

int main(void)
{
    string s = get_string("Text: ");
    float W = countWords(s);
    float L = countLetters(s) / W * 100;
    float S = countSentences(s) / W * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >=1 && index < 16)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

float countLetters(string s)
{
    int sum = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            sum = sum + 1;
        }
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            sum = sum + 1;
        }
    }
    //printf("%i letter(s)\n", sum);
    return sum;
}

float countSentences(string s)
{
    int sum = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            sum = sum + 1;
        }
    }
    //printf("%i sentence(s)\n", sum);
    return sum;
}

float countWords(string s)
{
    int sum = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == ' ')
        {
            sum = sum + 1;
        }
    }
    //printf("%i word(s)\n", sum);
    return sum+1;
}