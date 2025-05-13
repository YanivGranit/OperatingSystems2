#include "user.h"

int main() 
{
    int procId = tournament_create(16);
    if (procId < 0) 
    {
        printf("Failed to create tournament\n");
        exit(1);
    }

    
    // Children
    if (procId != 0) 
    {
        if (tournament_acquire() < 0) 
        {
            printf("Process %d failed to acquire lock\n", procId);
            exit(1);
        }

        printf("Process %d took the last lock\n", procId);
        if (tournament_release() < 0) 
        {
            printf("Process %d failed to release lock\n", procId);
            exit(1);
        }
        
        exit(0);
    }

    // Parent
    for (int i = 0; i < 16; i++) 
    {
        wait(0);
    }

    exit(0);
}
