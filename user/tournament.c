#include "user.h"

int main() 
{
    int procId = tournament_create(16);
    if (procId < 0) 
    {
        printf("Failed to create tournament\n");
        exit(1);
    }

    // Acquire
    if (tournament_acquire() < 0) 
    {
        printf("Process %d failed to acquire lock\n", procId);
        exit(1);
    }

    // CS
    printf("Process %d took the last lock\n", procId);   
    
    // Release
    if (tournament_release() < 0) 
    {
        printf("Process %d failed to release lock\n", procId);
        exit(1);
    }

    // Child
    if (procId != 0) 
    {
        exit(0);
    }

    // Parent
    for (int i = 0; i < 16; i++) 
    {
        wait(0);
    }

    exit(0);
}
