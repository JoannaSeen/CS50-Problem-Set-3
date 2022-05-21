#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


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
}
candidate;

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
            int voter = i;
            int rank = j;

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
    for (int i = 0 ; i < candidate_count ; i++)
    {
            if (strcmp(candidates[i].name, name) == 0)
            {
                preferences[voter][rank] = i;
                //printf("%i\n", preferences[voter][rank]);
                return true;
            }

    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int j = 0 ; j < voter_count ; j++)
    {
        int z = preferences[j][0];
        int y;
       if (candidates[z].eliminated == true)
       {
           do
           {
            int n = 1;
            n = n + 1;
            y = preferences[j][n];
           }
           while (candidates[y].eliminated == false);

            candidates[y].votes = candidates[y].votes + 1;
       }
       else
        {
            candidates[z].votes = candidates[z].votes + 1;
        }

    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int x = (int) ceil(voter_count/2);
    for (int i = 0 ; i < candidate_count; i++)
    {
        if (candidates[i].votes > x )
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
//do the bubble sort method to sort the array from smallest to largest number
//Do note that may need to sieve out the eliminated individuals
int find_min(void)
{
    int swap_counter = 0;

    do
    {
        swap_counter = 0;

        for (int i = 0 ; i < candidate_count - 1; i++)
        {
            if (candidates[i].votes > candidates[i + 1].votes)
            {
                int swap = candidates[i].votes;
                candidates[i].votes = candidates[i + 1].votes;
                candidates[i + 1].votes = swap;
                string swap_name = candidates[i].name;
                candidates[i].name = candidates[i + 1].name;
                candidates[i + 1].name = swap_name;

                swap_counter = swap_counter + 1;
            }
        }

    }
    while (swap_counter != 0);
    return candidates[0].votes;
}


// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)

    {
        if (candidates[i].votes != min)
        return false;
    }

    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].votes = 0;
            candidates[i].eliminated = false;
        }

    }

    return;
}
