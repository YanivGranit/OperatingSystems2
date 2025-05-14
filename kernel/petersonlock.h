// Long-term locks for processes
struct petersonlock 
{
  int interested[2]; 
  int turn;
  int state;
};

