#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int cand_idx = 0; cand_idx < candidate_count; cand_idx++)
    {
        if (strcmp(name, candidates[cand_idx].name) == 0)
        {
            preferences[voter][rank] = cand_idx;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int vote_idx = 0; vote_idx < voter_count; vote_idx++)
    {
        for (int rank = 0; rank < candidate_count; rank++)
        {
            int candidate_point = preferences[vote_idx][rank];
            if (!candidates[candidate_point].eliminated)
            {
                candidates[candidate_point].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int total_votes = 0;
    for (int cand_idx = 0; cand_idx < candidate_count; cand_idx++)
    {
        total_votes += candidates[cand_idx].votes;
    }
    int winner_limit = ceil(total_votes / (float) 2);
    for (int cand_idx = 0; cand_idx < candidate_count; cand_idx++)
    {
        candidate candidate_self = candidates[cand_idx];
        if (candidate_self.votes > winner_limit)
        {
            printf("%s\n", candidate_self.name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int smallest = candidates[0].votes;
    int smallest_idx = 0;
    bool all_eliminated = true;
    for (int cand_idx = 0; cand_idx < candidate_count; cand_idx++)
    {
        candidate candidate_self = candidates[cand_idx];
        if (!candidate_self.eliminated && smallest > candidate_self.votes)
        {
            smallest = candidate_self.votes;
            smallest_idx = cand_idx;
        }
        if (!candidate_self.eliminated)
        {
            all_eliminated = false;
        }
    }

    if (all_eliminated)
    {
        return 0;
    }
    return candidates[smallest_idx].votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int all_candidates_equal_votes = 0;
    int all_candidates_not_eliminated = 0;
    for (int cand_idx = 0; cand_idx < candidate_count; cand_idx++)
    {
        candidate candidate_self = candidates[cand_idx];
        if (candidate_self.votes == min && !candidate_self.eliminated)
        {
            all_candidates_equal_votes++;
        }
        if (!candidate_self.eliminated)
        {
            all_candidates_not_eliminated++;
        }
    }
    if (all_candidates_not_eliminated == all_candidates_equal_votes)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int cand_idx = 0; cand_idx < candidate_count; cand_idx++)
    {
        candidate candidate_self = candidates[cand_idx];
        if (candidate_self.votes == min && !candidate_self.eliminated)
        {
            candidates[cand_idx].eliminated = true;
        }
    }
    return;
}
