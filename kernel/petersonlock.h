// Long-term locks for processes
struct petersonlock {
  int interested[2]; 
  int turn;
  int state;
};

void peterson_init(void); 
int peterson_destroy(int lock_id);
int peterson_release(int lock_id, int role); 
int peterson_acquire(int lock_id, int role);
int peterson_create(void);

