#include "clock_gen.h"
int main (){
  /* generate clock with jitter */
  /* arguments: (nCycles, clock period in ps, RJ in ps, DJ in ps) */
  generateClock jitterClock(100000,24951,10.0,15.0);
  jitterClock.getClockSim();
  return 0;
}
