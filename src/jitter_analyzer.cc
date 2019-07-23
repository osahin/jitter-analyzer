#include "../lib/jitter_analyzer.h"
#include <cmath>
#include <TString.h>
#include <TGraph.h>
#include <TObjArray.h>
#include <TObject.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TAxis.h>
#include <TText.h>
#include <TLegend.h>
#include <TObjString.h>
/* returns pi value */
double pi() { return std::atan(1)*4; }
/* returns the area under curve (trapezoidal algorithm - seems to be the best among the popular ones) */
double jitter_handler::integrate( const source_jitter & sj) {
  double integral = 0.;
  double minPower = sj.valJitter.front().at(1);
  for(auto iter = sj.valJitter.begin(); iter+1 != sj.valJitter.end(); iter++){
    if( (iter+1)->at(0) < _maxFreq && iter->at(0) > _minFreq){
      integral += (std::pow(10.,(iter+1)->at(1)/10.)+std::pow(10.,iter->at(1)/10.))/2.*((iter+1)->at(0)-iter->at(0)); 
    }
  }
  return integral;
}
/* returns the RMS jitter of the integrated value */
double jitter_handler::rms_jitter(source_jitter & sj){
  double RMSJitter = std::sqrt(2.*integrate(sj))/(2.*pi()*_refFreq*1.e-6);
  sj.RMSJitter = RMSJitter;
  return RMSJitter;
}

/* Adding new entities to the jitter plots */
void plot_jitter::add_plot(const source_jitter & sj){
  double x[sj.valJitter.size()], y[sj.valJitter.size()];
  int ind = 0;
  for(auto const &iter : sj.valJitter){
    x[ind] = iter.at(0);
    y[ind] = iter.at(1);
    ind++;
  } 
  TGraph *jitterG = new TGraph (sj.valJitter.size(),x,y);
  TString name(sj.fileName);
  name= ((TObjString*)((TObjArray*)(name.Tokenize("/"))->Last()))->GetString();
  std::cout << "Plotting " << name << std::endl;
  jitterG->SetName(name);
  _graphs.push_back(jitterG);
  _graphJitter.push_back(sj.RMSJitter);
  _graphLegend.push_back(sj.sampleTitle);
}

/* Adding new entities to the jitter plots with selected range */
void plot_jitter::add_plot(const source_jitter & sj, const double  minFreq, const double  maxFreq){
  double x[sj.valJitter.size()], y[sj.valJitter.size()];

  int ind = 0;
  //for(auto const &iter : sj.valJitter){
  for(auto iter = sj.valJitter.begin(); iter+1 != sj.valJitter.end(); iter++){
    if( (iter+1)->at(0) < maxFreq && iter->at(0) > minFreq){
      x[ind] = iter->at(0);
      y[ind] = iter->at(1);
      ind++;
    }
  }

  TGraph *jitterG = new TGraph (ind,x,y);
  TString name(sj.fileName);
  name= ((TObjString*)((TObjArray*)(name.Tokenize("/"))->Last()))->GetString();
  std::cout << "Plotting " << name << std::endl;
  jitterG->SetName(name);
  _graphs.push_back(jitterG);
  _graphJitter.push_back(sj.RMSJitter);
  _graphLegend.push_back(sj.sampleTitle);
}


/* printing the plots (saving the root files and a PDF output), this method also deals with makeup and legend of the plots  */
void plot_jitter::print_plot(TString graphName){
  TCanvas * JitterCanvas = new TCanvas("JitterGraph", graphName, 1200, 1000);

  JitterCanvas->cd();
  JitterCanvas->SetLogx();
  int index = 0;
  TFile * jitterFile = new TFile(graphName+"JitterPlots.root", "RECREATE");
  TString dtos;
  auto legend = new TLegend(0.55,0.88-_graphs.size()*0.033,0.92,0.92);
  legend->SetTextFont(4);
  legend->SetTextSize(24);
  legend->SetFillColorAlpha(0,0.8);
  int color;
  for(auto const &iter: _graphs){
    if (index < 9) 
      color = index+1;
    else 
      color = index*2+index;
    if(color == 5) color = 46;

    iter->SetLineColorAlpha(color,0.65);
    iter->SetTitle( graphName );
    iter->GetXaxis()->SetTitle("Offset freq. [Hz]");

    iter->GetYaxis()->SetTitle("Phase noise [dBc/Hz]");
    iter->SetLineWidth(2);

    iter->GetYaxis()->SetTitleOffset(1.20);
    iter->GetXaxis()->SetTitleOffset(1.05);

    iter->GetYaxis()->SetTitleSize(0.05);
    iter->GetXaxis()->SetTitleSize(0.05);

    legend->AddEntry(iter,(TString)_graphLegend.at(index),"l");
    std::cout << "jitter read at this point: " << _graphJitter.at(index) << std::endl;;
    dtos.Form("%.2lf",(_graphJitter.at(index)));
    TText *jinfo;
    if ( index < 5) 
      jinfo = new TText(0.18,0.32-0.028*(1.+index),(TString)"RMS: "+dtos+" ps");
    else
      jinfo = new TText(0.32,0.32-0.028*(index-4.),(TString)"RMS: "+dtos+" ps");
    jinfo->SetTextFont(4);
    jinfo->SetTextSize(28);
    jinfo->SetTextColor(color);
    jinfo->SetNDC();
    if(0 == index) 
      iter->Draw("AC");
    else iter->Draw("same C");
    jinfo->Draw();
    index++;
    iter->Write();
  JitterCanvas->Update();
  }

  legend->SetLineWidth(0);
  legend->Draw();
  JitterCanvas->SetTickx();
  JitterCanvas->SetTicky();
  JitterCanvas->SetRightMargin(0.05);
  JitterCanvas->SetLeftMargin(0.14);
  JitterCanvas->SetTopMargin(0.07);
  JitterCanvas->SetBottomMargin(0.16);


  JitterCanvas->Update();
  JitterCanvas->Modified();
  JitterCanvas->SaveAs(graphName+"jitter.pdf");
  JitterCanvas->Write();
  jitterFile->Close();
};
