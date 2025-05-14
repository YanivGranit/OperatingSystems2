#include "types.h"         // uint, uint64, int, uchar
#include "riscv.h"         // pagetable_t, pte_t
#include "defs.h"

uint64 
sys_peterson_acquire(void) 
{
    int lock_id, role;
    argint(0, &lock_id);
    argint(1, &role);
    return (uint64) peterson_acquire(lock_id, role);
}

uint64 
sys_peterson_release(void) 
{
    int lock_id, role;
    argint(0, &lock_id);
    argint(1, &role);
    return (uint64) peterson_release(lock_id, role);
}

uint64 
sys_peterson_create(void) 
{
    return (uint64) peterson_create();
}

uint64 
sys_peterson_destroy(void) 
{
    int lock_id;
    argint(0, &lock_id);
    return (uint64) peterson_destroy(lock_id);
}