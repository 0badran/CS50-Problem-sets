#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
float *totals(string s);
int main(void)
{
    string text = get_string("Text: ");
    const int MAX = 16, MIN = 1;
    float *arr = totals(text);
    float total_letters = arr[0], total_words = arr[1], total_sentences = arr[2];
    float L = (total_letters / total_words) * 100;
    float S = (total_sentences / total_words) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);
    if (grade > MAX)
    {
        printf("Grade 16+\n");
    }
    else if (grade < MIN)
    {
        printf("Before Grade 1\n");
    }
    else
    {

        printf("Grade %i\n", grade);
    }
    return 0;
}
float *totals(string s)
{
    // https://www.tutorialspoint.com/cprogramming/c_return_arrays_from_function.htm
    float L = 0.0, S = 0.0, W = 1.0;
    static float array[3];
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i]))
        {
            L++;
        }
        else if (isblank(s[i]))
        {
            W++;
        }
        else if (s[i] == '!' || s[i] == '?' || s[i] == '.')
        {
            S++;
        }
    }
    array[0] = L;
    array[1] = W;
    array[2] = S;
    return array;
}
