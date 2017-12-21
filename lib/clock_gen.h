#ifndef clock_gen_h
#define clock_gen_h
#include <TRandom3.h>
#include <TH1D.h>
class generateClock{
 public:
  generateClock(int maxCycles, double periodPS, double RJ, double DJ){
    _RJ = RJ;
    _DJ = DJ;
    _hRJ = RJ/std::sqrt(2.);
    _period = periodPS;
    _maxCount = maxCycles;
    _hClock = new TH1D("histClock","Clock with jitter", 2*(int)(_RJ/0.68+_DJ+_RJ*10), ((int)_period-(int)(_RJ/0.68+_DJ+_RJ*10)/2), ((int)_period+(int)(_RJ/0.68+_DJ+_RJ*10)/2));
  }
  void getClockSim();
 private:
  void   writeFiles();
  double getRandom();
  double _RJ = 0., _DJ = 0., _period = 0., _hRJ = 0.;
  TRandom3 _randGen; 
  int _count = 0, _maxCount = 0;
  TH1D* _hClock;
};
#endif
