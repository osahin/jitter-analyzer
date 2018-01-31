#include "clock_gen.h"
int main (){
  /* generate clock with jitter */
  /* arguments: (nCycles, clock period in ps, RJ in ps, DJ in ps) */
  generateClock jitterClock(100000,24951,8.2,18.6);
  jitterClock.getClockSim();
  return 0;
}
