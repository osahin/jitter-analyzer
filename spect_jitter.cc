#include "lib/csv_reader.h"
#include <TH2D.h>
#include <TCanvas.h>
#include <TStyle.h>
int main (){

  TString PATH = "/Users/yunus/analiz/jitter_1/jitter-analyzer/examples/";
  //  TString fileName = ""
  TString fileName = "elinkjitterspectrum40mhztlb400long2ch.csv";
  jitter_handler jhandler(160.0);
  /* set minimum offset freq */
  double minF = 0.999;
  double maxF = 1.01e6;
  jhandler.set_min_freq(minF);
  jhandler.set_max_freq(maxF);

  plot_jitter graph;
  /* file reader */
  csv_reader csv;
  /* jitter info container */
  source_jitter jitter;
  try{
  csv.read(TString(PATH+fileName).Data(), jitter, TString("Single"));
  }catch (int a){
    return 0; }

  std::cout <<  jhandler.rms_jitter(jitter) << std::endl;
  /* returns jitter value */
  graph.add_plot(jitter,minF,maxF);
 
  graph.print_plot("");
  


  return 0;
}
