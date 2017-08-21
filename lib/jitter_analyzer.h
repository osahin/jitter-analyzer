#ifndef jitter_analyzer_h
#define jitter_analyzer_h
#include <vector>
#include <iostream>
#include <string>
#include <TGraph.h>
struct source_jitter{
  std::vector<std::vector<double>> jitter;
  std::string fileName;
  std::string sampleTitle;
  double RMSJitter;
};
class jitter_handler{
 public:
  jitter_handler(double refFreq){_refFreq = refFreq; };
  double rms_jitter(source_jitter & sj);
  void set_ref_freq(double refFreq){_refFreq = refFreq;};
 private:
  double integrate( const source_jitter & sj);
  double _maxFreq = 1.1e7;
  double _minFreq = 0.;
  double _refFreq = 40.078;
};

#endif

class plot_jitter{
 public:
  void add_plot(const source_jitter & sj);
  void print_plot();
 private:
  std::vector<TGraph*> _graphs;
  std::vector<double> _graphJitter;
  std::vector<std::string> _graphLegend;
};

