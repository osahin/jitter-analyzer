#include <iostream>
#include <TRandom3.h>
#include "clock_gen.h"
#include <TFile.h>
#include <fstream>
double generateClock::getRandom(){
  double hPeriod = 0.;
  if(_count % 2 == 0){
    hPeriod =  _period/2. + _randGen.Gaus(0., _hRJ);
  } else {
    hPeriod =  _period/2. + (_randGen.Binomial(1,0.5)*2-1) * _DJ/2. + _randGen.Gaus(0., _hRJ);
  }
  return hPeriod;
}
void generateClock::getClockSim(){
  double period = 0., hPeriod = 0.;
  std::ofstream textfile;
  textfile.open("jitter_text_io.txt");
  for(;_count < 2*_maxCount; _count++){
    hPeriod = getRandom();
    period += hPeriod;
    textfile << hPeriod << std::endl;
    if(_count % 2 == 1){
       _hClock->Fill(period);
      period = 0;
    }
  }
  textfile.close();
  writeFiles();
}
void generateClock::writeFiles(){
  TFile * file = new TFile("genClock.root","RECREATE");
  _hClock->Write();
  file->Close();
}
