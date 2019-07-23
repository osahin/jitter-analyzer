#include "../lib/tdc_analyzer.h"
#include <cmath>
#include <TString.h>
#include <TGraph.h>
#include <TObjArray.h>
#include <TObject.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TAxis.h>
#include <TH1F.h>
#include <TText.h>
#include <TLegend.h>
#include <TObjString.h>
/* returns pi value */
double pi() { return std::atan(1)*4; }

bool tdc_handler::allignTDC(source_jitter & sj, int locTDC1, int locTDC2) {
  double penalty = 0.5;
  bool needCorr1 = false , needCorr2 = false;
  sj.meanValTDCdiff = 0.;
  for(int i = 1; i < sj.valTDC.size()-2; i++){ /* we will have access to pre and 2 post cycles */
    if(fabs(sj.valTDC[i][locTDC1] - sj.valTDC[i][locTDC2]) / (_periodPS*penalty) > 1.){
      if(fabs(sj.valTDC[i][locTDC1] - sj.valTDC[i-1][locTDC1]) / _periodPS < 1. && !needCorr1 && !needCorr2 ){
	needCorr1 = true;
      } else if(fabs(sj.valTDC[i][locTDC2] - sj.valTDC[i-1][locTDC2]) / _periodPS < 1. && !needCorr1 && !needCorr2){
	needCorr2 = true;
      }      
    } else if(fabs(sj.valTDC[i][locTDC1]-sj.valTDC[i][locTDC2]) / (_periodPS*penalty) < 1. && fabs(sj.valTDC[i+1][locTDC1]-sj.valTDC[i+1][locTDC2]) / (_periodPS*penalty) < 1. && fabs(sj.valTDC[i+2][locTDC1]-sj.valTDC[i+2][locTDC2]) / (_periodPS*penalty) < 1. ){
      needCorr1 = false; 
      needCorr2 = false;
    }
    if(needCorr1){
      sj.valTDC[i][locTDC1] = sj.valTDC[i+1][locTDC1];
    }
    if(needCorr2){
      sj.valTDC[i][locTDC2] = sj.valTDC[i+1][locTDC2];
    }
    sj.meanValTDCdiff += fabs(sj.valTDC[i][locTDC1] - sj.valTDC[i][locTDC2]);
  }
  sj.meanValTDCdiff = sj.meanValTDCdiff / sj.valTDC.size();
  return true;
}

bool tdc_handler::writeTDC(source_jitter & sj, int locTDC1, int locTDC2) {
  int index = 0;
  std::cout << "  mean TDC difference: " << sj.meanValTDCdiff << std::endl; 
  for(const std::vector<double> & valueTDC: sj.valTDC){
    //    if(!(fabs(valueTDC[locTDC1]-valueTDC[locTDC2])> 188-2 && fabs(valueTDC[locTDC1]-valueTDC[locTDC2])< 188+2)) continue;
    std::cout << index << " " <<  valueTDC[locTDC1] << " " << valueTDC[locTDC2] << " " << fabs( valueTDC[locTDC1] -  valueTDC[locTDC2]) << std::endl;
    index++;
  }
}

bool tdc_handler::plotTDC(source_jitter & sj, int locTDC1, int locTDC2) {
  int index = 0;
  TFile* fileTDC = new TFile("tdc.root","RECREATE");
  TH1F* hTDC1 = new TH1F("TDC1histogram","",25000, 0., 100000.);
  TH1F* hTDC2 = new TH1F("TDC2histogram","",25000, 0., 100000.);
  TH1F* hTDCdiff = new TH1F("TDCdiffhistogram","",500, sj.meanValTDCdiff-250., sj.meanValTDCdiff+250.);

  for(const std::vector<double> & valueTDC: sj.valTDC){
    //    if(!(fabs(valueTDC[locTDC1]-valueTDC[locTDC2])> 188-2 && fabs(valueTDC[locTDC1]-valueTDC[locTDC2])< 188+2)) continue;
    index++;
    hTDC1->Fill(valueTDC[locTDC1]);
    hTDC2->Fill(valueTDC[locTDC2]);
    hTDCdiff->Fill(fabs(valueTDC[locTDC1]-valueTDC[locTDC2]));
  }
  hTDC1->Write();
  hTDC2->Write();
  hTDCdiff->Write();
  fileTDC->Write();
  fileTDC->Close();
}

