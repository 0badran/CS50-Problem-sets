#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int sum_points(string text);
int main(void)
{
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");
    int score1 = sum_points(player1);
    int score2 = sum_points(player2);
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score1 < score2)
    {

        printf("Player 2 wins!");
    }
    else
    {

        printf("Tie!");
    }
}

int sum_points(string text)
{
    int points = 0;
    int numbers[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                     1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    char letter;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letter = toupper(text[i]);
            int letter_number = letter;
            points += numbers[letter_number - 65];
        }
    }
    return points;
}
