#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int i = (candidate_count - 1);
    for (; i < 0 ; i--)
    {
        if (candidates[i].votes == candidates[i-1].votes)
        {
            printf("%s\n",candidates[i-1].votes);
        }


}