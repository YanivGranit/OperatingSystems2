#include "user.h"

int main(int argc, char *argv[]) 
{
    int procs_number = atoi(argv[1]);
    int procId = tournament_create(procs_number);

    if(procId < 0) 
    {
        printf("Failed to create tournament\n");
        exit(1);
    }

    // Acquire
    if(tournament_acquire() < 0) 
    {
        printf("Process %d failed to acquire lock\n", procId);
        exit(1);
    }

    // CS
    printf("Process %d took the last lock\n", procId);   
    
    // Release
    if(tournament_release() < 0) 
    {
        printf("Process %d failed to release lock\n", procId);
        exit(1);
    }

    // Child
    if(procId != 0) 
    {
        exit(0);
    }

    // Parent
    for(int i = 0; i < 16; i++) 
    {
        wait(0);
    }

    exit(0);
}
