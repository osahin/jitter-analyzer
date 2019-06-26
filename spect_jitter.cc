#include "lib/csv_reader.h"
#include <TH2D.h>
#include <TCanvas.h>
#include <TStyle.h>
int main (){

  TString PATH = "/Users/yunus/analiz/jitter_1/jitter-analyzer/examples/";
  //  TString fileName = ""
  TString fileName = "elinkjitterspectrum40mhztlb400long2ch.csv"; //elinkjitterspectrum40mhztlb400long2ch
  TString fileName2 = "st-measures-eLink-clk.csv";
 jitter_handler jhandler(160.0);
  /* set minimum offset freq */
  double minF = 0.999;
  double maxF = 1.01e6;
  jhandler.set_min_freq(minF);
  jhandler.set_max_freq(maxF);

  plot_jitter graph, graph2;
  /* file reader */
  csv_reader csv;
  /* jitter info container */
  source_jitter jitter, jitter2;
  try{
  csv.read(TString(PATH+fileName).Data(), jitter, TString("Single"));
  }catch(const int a){return 0;} //"const int a" here is just d dummy used for cathcing
  std::cout << " first file -rms_jitter--> " << jhandler.rms_jitter(jitter) << std::endl;
//second one
  try{
  csv.read(TString(PATH+fileName2).Data(), jitter2, TString("Double"));
  }catch(const int b){return 0;}
  std::cout << " second file -rms_jitter --> " << jhandler.rms_jitter(jitter2) << std::endl;
/* returns jitter value */
  graph.add_plot(jitter2,minF,maxF); 

  graph.add_plot(jitter,minF,maxF);


  graph.print_plot("");

  graph.print_plot("same");
  


  return 0;
}
