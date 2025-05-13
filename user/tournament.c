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
        sleep(300); // Wait for all children to be created
        if (tournament_acquire() < 0) 
        {
            printf("Process %d failed to acquire lock\n", procId);
            exit(1);
        }

        // CS
        printf("Process %d has the lock!\n", procId);

        if (tournament_release() < 0) 
        {
            printf("Process %d failed to release lock\n", procId);
            exit(1);
        }

        printf("Process %d released the lock\n", procId);
        exit(0);
    }

    // Parent
    for (int i = 0; i < 16; i++) 
    {
        wait(0);
    }

    exit(0);
}
