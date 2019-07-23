#ifndef jitter_analyzer_h
#define jitter_analyzer_h
#include <vector>
#include <iostream>
#include <string>
#include <TString.h>
#include <TGraph.h>
struct source_jitter{
  std::vector<std::vector<double>> valJitter;
  std::vector<std::vector<double>> valTDC;
  double meanValTDC1;
  double meanValTDC2;
  double meanValTDCdiff;
  std::string fileName;
  std::string sampleTitle;
  double RMSJitter;
};
struct deter_jitter_freq{
  double frequencyMHz;
  double noiseV;
};
class jitter_handler{
 public:
  jitter_handler(double refFreq){_refFreq = refFreq; };
  double rms_jitter(source_jitter & sj);
  void set_ref_freq(double refFreq){_refFreq = refFreq; _periodPS=1.0e6/_refFreq;};
  void set_min_freq(double minF){_minFreq = minF;};
  void set_max_freq(double maxF){_maxFreq = maxF;};
 private:
  double integrate( const source_jitter & sj);
  double _maxFreq = 1.1e7;
  double _minFreq = 0.;
  double _refFreq = 40.078;
  double _periodPS  = 24951.; // in PS
};

class plot_jitter{
 public:
  void add_plot(const source_jitter & sj);
  void add_plot(const source_jitter & sj, double, double);
  void print_plot(TString graphName);
 private:
  std::vector<TGraph*> _graphs;
  std::vector<double> _graphJitter;
  std::vector<std::string> _graphLegend;
};

#endif
