#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int ALPHABET_LENGTH = 26;
int alphabet_duplicate(string s);
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string key = argv[1];
    int length = strlen(key);
    if (length != ALPHABET_LENGTH)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (alphabet_duplicate(key) == 1)
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }
    else if (alphabet_duplicate(key) == 2)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }
    else
    {
        string text = get_string("Plaintext:  ");
        int plain_length = strlen(text);
        char ciphertext[plain_length];
        for (int i = 0; i < plain_length; i++)
        {
            char letter = text[i];
            if (isalpha(letter))
            {
                if (isupper(letter))
                {
                    ciphertext[i] = toupper(key[letter - 'A']);
                }
                else
                {
                    ciphertext[i] = tolower(key[letter - 'a']);
                }
            }
            else
            {
                ciphertext[i] = letter;
            }
        }
        printf("ciphertext: ");
        for (int i = 0; i < plain_length; i++)
        {
            printf("%c", ciphertext[i]);
        }
        printf("\n");
    }
    return 0;
}

int alphabet_duplicate(string s)
{
    int frequency[ALPHABET_LENGTH] = {0};
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        char letter = s[i];
        if (isalpha(letter))
        {
            char lower_case = tolower(letter);
            int index = lower_case - 'a';
            frequency[index] = frequency[index] + 1;
        }
        else
        {
            return 1;
        }
    }
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        if (frequency[i] > 1)
        {
            return 2;
        }
    }
    return 0;
}
