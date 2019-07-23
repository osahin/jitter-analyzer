#ifndef tdc_analyzer_h
#define tdc_analyzer_h
#include "../lib/jitter_analyzer.h"
#include <vector>
#include <iostream>
#include <string>
#include <TString.h>
#include <TGraph.h>
class tdc_handler{
 public:
  tdc_handler(double refFreq){_refFreq = refFreq; };
  bool allignTDC(source_jitter & sj, int locTDC1, int locTDC2);
  bool writeTDC(source_jitter & sj, int locTDC1, int locTDC2);
  bool plotTDC(source_jitter & sj, int locTDC1, int locTDC2);
  void set_ref_freq(double refFreq){_refFreq = refFreq; _periodPS=1.0e6/_refFreq;};
 private:
  double allignTDC( source_jitter & sj);
  double _maxFreq = 1.1e7;
  double _minFreq = 0.;
  double _refFreq = 40.078;
  double _periodPS  = 1.0e6/_refFreq; // in PS
};
#endif
