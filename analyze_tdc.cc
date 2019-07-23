#include "lib/tdc_analyzer.h"
#include "lib/csv_reader.h"
#include "lib/jitter_analyzer.h"
#include <TH2D.h>
#include <TCanvas.h>
#include <TStyle.h>
int main (){
  TString PATH =  "/Users/osahin/Downloads/csv_files/0-delay.csv";
  source_jitter valuesTDC; 
  double clkRefMHz = 40.078;
  csv_reader csvTDC;
  tdc_handler gpx2(clkRefMHz); 
  csvTDC.read(PATH.Data(),valuesTDC,"5.00ps-stop2delay",true);
  gpx2.allignTDC(valuesTDC,1,3);
  gpx2.writeTDC(valuesTDC,1,3);
  gpx2.plotTDC(valuesTDC,1,3);
  return 0;
}
