#include <iostream>
#include <TRandom3.h>
#include "clock_gen.h"
#include <TFile.h>
#include <fstream>
#include <TString.h>
#include <TLatex.h>
#include <TMultiGraph.h>

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
  double period = 0., hPeriod = 0., cumuPeriod = 0., cumuRef = 0.;
  int nrGraph = 0, countGraph = 0, color = 0;
  TMultiGraph *demoGraphs = new TMultiGraph();
  std::ofstream textfile;
  double ti[7*_demoGraphLength], vo[7*_demoGraphLength];
  bool status = false;
  textfile.open("jitter_text_io.txt");
  for(;_count < 2*_maxCount; _count++){
    hPeriod = getRandom();
    period += hPeriod;
    textfile << hPeriod << std::endl;
    if(_count < _demoGraphSize * _demoGraphLength * 2){
      vo[countGraph] = double(status) - 0.5;
      ti[countGraph] = cumuPeriod;
      status =!status; 
      countGraph++;
      vo[countGraph] = double(status) - 0.5;
      ti[countGraph] = cumuPeriod;
      countGraph++;
      cumuPeriod += hPeriod;
      cumuRef += _period / 2.;
      if(countGraph == 6*_demoGraphLength){
	status = false;
	_demoGraph.at(nrGraph) = new TGraph(countGraph-1,ti,vo);
	_demoGraph.at(nrGraph)->SetLineColorAlpha(color%99+1, 0.6+0.01*(nrGraph%20));
	demoGraphs->Add(_demoGraph.at(nrGraph));
	color++;
	nrGraph++;
	countGraph = 0;
	cumuPeriod = cumuPeriod - cumuRef;
	cumuRef = 0;
      }
    }

    if(_count % 2 == 1){
       _hClock->Fill(period);
      period = 0;
    }
  }
  _demoCanvas->cd();
  demoGraphs->Draw("AL");
  makeupDemoGraphs(demoGraphs,_demoCanvas); 
  textfile.close();
  writeFiles();
}
void generateClock::makeupDemoGraphs(TMultiGraph * demoGraphs, TCanvas * demoCanvas){
  /* this method should be called after 'demoGraphs->Draw()' */
  demoGraphs->GetXaxis()->SetTitle("t [ps]");
  demoGraphs->GetYaxis()->SetTitle("V");
  demoGraphs->GetYaxis()->SetLabelSize(0.05); //in pixels
  demoGraphs->GetYaxis()->SetTitleSize(0.058); //in pixels
  demoGraphs->GetXaxis()->SetLabelSize(0.05); //in pixels
  demoGraphs->GetXaxis()->SetTitleSize(0.058); //in pixels
  demoGraphs->GetYaxis()->SetTickSize(0.02);
  demoGraphs->GetXaxis()->SetTickSize(0.02);
  demoGraphs->GetYaxis()->SetTitleOffset(0.8); 
  demoGraphs->GetXaxis()->SetTitleOffset(0.85); 
  demoCanvas->SetTicks();
  demoCanvas->SetPad(0,0.0,1,1);
  demoCanvas->SetTopMargin(0.03);
  demoCanvas->SetBottomMargin(0.12);
  TLatex info;
  info.SetNDC();
  info.SetTextFont(132);
  info.SetTextColor(1);
  info.SetTextSize(0.050);
  info.DrawLatex(0.79,0.85,Form("RJ = %5.2f ps",_RJ));
  info.DrawLatex(0.79,0.75,Form("DJ = %5.2f ps",_DJ));
  demoCanvas->Update();
  demoCanvas->Modified();
}
void generateClock::writeFiles(){
  TFile * file = new TFile("genClock.root","RECREATE");
  _hClock->Write();
  _demoCanvas->Print((TString)"waveform"+(TString::Itoa(_demoGraphSize,10))+"OverlaysOf_"+(TString::Itoa(_demoGraphLength+1,10))+(TString)"CyclesWindow.pdf");
  file->Close();
}
