#include "user.h"

int my_id;
int num_levels;
int num_procs;

int 
log2(int x) {
    int res = 0;
    while (x >>= 1) res++;
    return res;
}

int 
get_lock_index(int level) 
{
    int index_in_the_level = my_id >> (num_levels - level);
    int level_offset =  (1 << level) - 1;
    int index_in_array = index_in_the_level + level_offset;
    return index_in_array;
}

int 
get_process_role_by_level(int level) 
{
    return (my_id & (1 << (num_levels - level - 1))) >> (num_levels - level - 1);
}

int 
tournament_create(int processes) 
{
    if (processes !=2 && processes !=4 && processes !=8 && processes !=16) 
    {
        return -1;  
    }

    num_procs = processes;
    num_levels = log2(processes);

    // Create (num_procs-1) Peterson locks
    for (int i = 1; i < num_procs; i++) 
    {
        peterson_create();
    }    

    // Create processes
    for (int i = 0; i < processes; i++) 
    {
        int pid = fork();
        if (pid < 0) 
        {
            return -1;
        }    
        if (pid == 0) 
        {
            my_id = i;
            return i;  // Each child returns its ID
        }    
    }    

    return 0;
}    

int 
tournament_acquire(void) 
{
    for (int level = 0; level < num_levels; level++) 
    {
        int lock_index = get_lock_index(level);
        int role = get_process_role_by_level(level);
        if (peterson_acquire(lock_index, role) < 0) 
        {
            return -1;
        }    
    }    

    return 0;  // Successfully reached root lock
}    

int 
tournament_release(void) 
{
    for (int level = num_levels - 1; level >= 0; level--) 
    {
        int lock_index = get_lock_index(level);
        int role = get_process_role_by_level(level);
        if (peterson_release(lock_index, role) < 0) 
        {
            return -1;
        }    
    }    

    return 0;
}    


