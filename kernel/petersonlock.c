// Sleeping locks

#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sleeplock.h"
#include "petersonlock.h"


struct petersonlock petersonlocks[NPETERSONLOCK];


void
peterson_init(void)
{
  for (int i = 0; i < NPETERSONLOCK; i++) 
  {
    petersonlocks[i].interested[0] = 0;
    petersonlocks[i].interested[1] = 0;
    petersonlocks[i].turn = 0;
    petersonlocks[i].state = 0;
  }
}

int
peterson_create(void)
{
  for (int i = 0; i < NPETERSONLOCK; i++) 
  {     
    __sync_synchronize();

    if (__sync_lock_test_and_set(&petersonlocks[i].state, 1) == 0)
    {
      __sync_synchronize();

      petersonlocks[i].interested[0] = 0;
      petersonlocks[i].interested[1] = 0;
      petersonlocks[i].turn = 0;

      __sync_synchronize();
      
      return i;
    }
  }
    return -1;
}

int 
peterson_acquire(int lock_id, int role) 
{
  if (lock_id < 0 || lock_id >= NPETERSONLOCK)
    return -1;

  if (role != 0 && role != 1)
    return -1;

  struct petersonlock *lk = &petersonlocks[lock_id];

  // Check if the lock is active
  if (lk->state != 1)
    return -1;

  int other = 1 - role;
  lk->interested[role] = 1;
  lk->turn = other;

  __sync_synchronize();

  while (lk->interested[other] && lk->turn == other) 
  {
    yield(); // Give up CPU to avoid busy waiting
  }

  __sync_synchronize();

  return 0;
}

int 
peterson_release(int lock_id, int role) 
{
  // Validate role
  if (role != 0 && role != 1)
    return -1;

  // Validate lock_id
  if (lock_id < 0 || lock_id >= NPETERSONLOCK || petersonlocks[lock_id].state == 0)
    return -1;

  struct petersonlock *lk = &petersonlocks[lock_id];

  __sync_synchronize();

  // Indicate no longer interested
  lk->interested[role] = 0;

  __sync_synchronize();

  return 0;
}

// TODO: to verify what to do in case of role is interested
int
peterson_destroy(int lock_id) 
{
  // Validate lock_id
  if (lock_id < 0 || lock_id >= NPETERSONLOCK || petersonlocks[lock_id].state == 0)
    return -1;

  struct petersonlock *lk = &petersonlocks[lock_id];

  __sync_synchronize();

  // Invalidate the lock
  lk->state = 0;
  lk->interested[0] = 0;
  lk->interested[1] = 0;
  lk->turn = 0;

  __sync_synchronize();

  return 0;
}



