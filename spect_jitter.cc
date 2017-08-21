#include "lib/csv_reader.h"
int main (){
  csv_reader csv;
  source_jitter jitter, jitter2, jitter3, jitter4, jitter5;
  /*  csv.read("/Users/ozgursahin/Documents/PCD-SSA-E5052B/Si5344jitterspectrum120mhztlb200.csv", jitter, "Si5344 out@120 MHz - loopBW-threshold 200 Hz");
  csv.read("/Users/ozgursahin/Documents/PCD-SSA-E5052B/Si5344jitterspectrum120mhztlb400.csv", jitter2, "Si5344 out@120 MHz - loopBW-threshold 400 Hz");
  csv.read("/Users/ozgursahin/Documents/PCD-SSA-E5052B/Si5344jitterspectrum120mhztlb1k.csv", jitter3, "Si5344 out@120 MHz - loopBW-threshold 1 kHz");
  csv.read("/Users/ozgursahin/Documents/PCD-SSA-E5052B/Si5344jitterspectrum120mhztlb4k.csv", jitter4, "Si5344 out@120 MHz - loopBW-threshold 4 kHz");*/
  /*  csv.read("/Users/ozgursahin/Documents/PCD-SSA-E5052B/cg635jitterRJ.csv", jitter, "cg635 out@40 MHz");
  csv.read("/Users/ozgursahin/Documents/PCD-SSA-E5052B/Si5344jitterspectrum40MHzTLB1k.csv", jitter2, "Si5344 out@40 MHz - loopBW-threshold 1 kHz");
  csv.read("/Users/ozgursahin/Documents/PCD-SSA-E5052B/Si5344jitterspectrum40MHzTLB2k.csv", jitter3, "Si5344 out@40 MHz - loopBW-threshold 2 kHz");
  csv.read("/Users/ozgursahin/Documents/PCD-SSA-E5052B/Si5344jitterspectrum40MHzTLB4k.csv", jitter4, "Si5344 out@40 MHz - loopBW-threshold 4 kHz");*/



  csv.read("./examples/1st-measures-eLink-clk.csv", jitter, "VLDB e-link@40 MHz - loopBW-threshold 100 Hz");
  csv.read("./examples/elinkjitterspectrum40mhztlb400long2ch.csv", jitter2, "VLDB e-link@40 MHz - loopBW-threshold 400 Hz");

  //  jitter_handler jhandler(120.234);
  jitter_handler jhandler(40.078);
  std::cout<< jhandler.rms_jitter(jitter)  << std::endl;
  std::cout<< jhandler.rms_jitter(jitter2) << std::endl;
  //  std::cout<< jhandler.rms_jitter(jitter3) << std::endl;
  //  std::cout<< jhandler.rms_jitter(jitter4) << std::endl;

  plot_jitter graph;
  graph.add_plot(jitter);
  graph.add_plot(jitter2);
  //  graph.add_plot(jitter3);
  //  graph.add_plot(jitter4);
  graph.print_plot();
  return 0;
}
