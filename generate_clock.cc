#include "clock_gen.h"
int main (){
  /* generate clock with jitter */
  /* arguments: (nCycles, clock period in ps, RJ in ps, DJ in ps) */
  generateClock jitterClock(100000,24951,7,38);
  jitterClock.getClockSim();
  return 0;
}
