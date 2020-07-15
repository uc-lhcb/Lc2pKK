//Background Subtracting Data To Observe Patterns in ROOT Variables
//Check PT, IPCHI2_OWNPV, DOCAMAXCHI2MAX, & TAU

#define BSubAnalysis_cxx
#include "BSubAnalysis.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

#include "fit1MeV_Gaussian.C"
#include "fitHalfMeV_Gaussian.C"
#include "DGOneMuOneTotal1MeV.C"
#include "DGOneMuOneTotalHalfMeV.C"
#include "DGTwoMuOneTotal1MeV.C"
#include "DGTwoMuOneTotalHalfMeV.C"

TH1D * PreliminaryMass = nullptr;

TH1D * LcPTSignal = nullptr;
TH1D * LcPTBkgd = nullptr;
TH1D * LcPTSignalEstimate = nullptr;

TH1D * PrPTSignal = nullptr;
TH1D * PrPTBkgd = nullptr;
TH1D * PrPTSignalEstimate = nullptr;

TH1D * KpPTSignal = nullptr;
TH1D * KpPTBkgd = nullptr;
TH1D * KpPTSignalEstimate = nullptr;

TH1D * KmPTSignal = nullptr;
TH1D * KmPTBkgd = nullptr;
TH1D * KmPTSignalEstimate = nullptr;

TH1D * PrChi2Signal = nullptr;
TH1D * PrChi2Bkgd = nullptr;
TH1D * PrChi2SignalEstimate = nullptr;

TH1D * KpChi2Signal = nullptr;
TH1D * KpChi2Bkgd = nullptr;
TH1D * KpChi2SignalEstimate = nullptr;

TH1D * KmChi2Signal = nullptr;
TH1D * KmChi2Bkgd = nullptr;
TH1D * KmChi2SignalEstimate = nullptr;

TH1D * DOCAMaxSignal = nullptr;
TH1D * DOCAMaxBkgd = nullptr;
TH1D * DOCAMaxSignalEstimate = nullptr;

TH1D * LcTAUSignal = nullptr;
TH1D * LcTAUBkgd = nullptr;
TH1D * LcTAUSignalEstimate = nullptr;

TCanvas * c1 = nullptr;
TCanvas * ex1 = nullptr;
TFile * File = nullptr;

void BSubAnalysis::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
   
}

void BSubAnalysis::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

   c1 = new TCanvas("canvas", "Test Canvas");
   ex1 = new TCanvas("ex1","Latex",500,600); 
     File = new TFile("BackgroundSubtraction.root", "RECREATE");
     gFile = File;

   TH1::SetDefaultSumw2(kTRUE);

   PreliminaryMass = new TH1D("Mass", "LambdaC Mass - Phi Resonance & PID Cuts", 300, 2210, 2360);
   PreliminaryMass->GetXaxis()->SetTitle("MeV");
   PreliminaryMass->GetYaxis()->SetTitle("Events Per 1/2 MeV");

LcPTSignal = new TH1D("Transverse Momentum", "Signal Region", 200, 2600, 22600);
LcPTBkgd = new TH1D("Transverse Momentum", "Background Region", 200, 2600, 22600);
LcPTSignalEstimate = new TH1D("Transverse Momentum", "Signal Estimation", 200, 2600, 22600);
LcPTSignal->SetLineColor(kBlue);
LcPTBkgd->SetLineColor(kRed);
LcPTSignalEstimate->SetLineColor(kGreen+3);
   
PrPTSignal = new TH1D("Transverse Momentum", "Signal Region", 200, 950, 12000);
PrPTBkgd = new TH1D("Transverse Momentum", "Background Region", 200, 800, 12000);
PrPTSignalEstimate = new TH1D("Transverse Momentum", "Signal Estimation", 200, 800, 12000);   
PrPTSignal->SetLineColor(kBlue);
PrPTBkgd->SetLineColor(kRed);
PrPTSignalEstimate->SetLineColor(kGreen+3);
   
KpPTSignal = new TH1D("Transverse Momentum", "Signal Region", 100, 300, 8300);
KpPTBkgd = new TH1D("Transverse Momentum", "Background Region", 100, 300, 8300);
KpPTSignalEstimate = new TH1D("Transverse Momentum", "Signal Estimation", 100, 300, 8300);
KpPTSignal->SetLineColor(kBlue);
KpPTBkgd->SetLineColor(kRed);
KpPTSignalEstimate->SetLineColor(kGreen+3);  
   
KmPTSignal = new TH1D("Transverse Momentum", "Signal Region", 100, 300, 8300);
KmPTBkgd = new TH1D("Transverse Momentum", "Background Region", 100, 300, 8300);
KmPTSignalEstimate = new TH1D("Transverse Momentum", "Signal Estimation", 100, 300, 8300);
KmPTSignal->SetLineColor(kBlue);
KmPTBkgd->SetLineColor(kRed);
KmPTSignalEstimate->SetLineColor(kGreen+3); 
   
PrChi2Signal = new TH1D("Log(IPCHI2)", "Signal Region", 175, 0.75, 2.5);
PrChi2Bkgd = new TH1D("Log(IPCHI2)", "Background Region", 175, 0.75, 2.5);
PrChi2SignalEstimate = new TH1D("Log(IPCHI2)", "Signal Estimation", 175, 0.75, 2.5);
PrChi2Signal->SetLineColor(kBlue);
PrChi2Bkgd->SetLineColor(kRed);
PrChi2SignalEstimate->SetLineColor(kGreen+3);

KpChi2Signal = new TH1D("Log(IPCHI2)", "Signal Region", 175, 0.75, 2.5);
KpChi2Bkgd = new TH1D("Log(IPCHI2)", "Background Region", 175, 0.75, 2.5);
KpChi2SignalEstimate = new TH1D("Log(IPCHI2)", "Signal Estimation", 175, 0.75, 2.5);   
KpChi2Signal->SetLineColor(kBlue);
KpChi2Bkgd->SetLineColor(kRed);
KpChi2SignalEstimate->SetLineColor(kGreen+3);
   
KmChi2Signal = new TH1D("Log(IPCHI2)", "Signal Region", 175, 0.75, 2.5);
KmChi2Bkgd = new TH1D("Log(IPCHI2)", "Background Region", 175, 0.75, 2.5);
KmChi2SignalEstimate = new TH1D("Log(IPCHI2)", "Signal Estimation", 175, 0.75, 2.5);   
KmChi2Signal->SetLineColor(kBlue);
KmChi2Bkgd->SetLineColor(kRed);
KmChi2SignalEstimate->SetLineColor(kGreen+3);

DOCAMaxSignal = new TH1D("DOCA", "Signal Region", 100, 0, 18);
DOCAMaxBkgd = new TH1D("DOCA", "Background Region", 100, 0, 18);
DOCAMaxSignalEstimate = new TH1D("DOCA", "Signal Estimation", 100, 0, 18);
DOCAMaxSignal->SetLineColor(kBlue);
DOCAMaxBkgd->SetLineColor(kRed);
DOCAMaxSignalEstimate->SetLineColor(kGreen+3);
 
LcTAUSignal = new TH1D("TAU", "Signal Region", 100, 0.0025, 0.02);
LcTAUBkgd = new TH1D("TAU", "Background Region", 100, 0.0025, 0.02);
LcTAUSignalEstimate = new TH1D("TAU", "Signal Estimation", 100, 0.0025, 0.012);
LcTAUSignal->SetLineColor(kBlue);
LcTAUBkgd->SetLineColor(kRed);
LcTAUSignalEstimate->SetLineColor(kGreen+3);
   
}

Bool_t BSubAnalysis::Process(Long64_t entry)
{
   GetEntry(entry);
   fReader.SetLocalEntry(entry);

TLorentzVector P(*Proton_PX, *Proton_PY, *Proton_PZ, *Proton_PE);
TLorentzVector Kp(*Kplus_PX, *Kplus_PY, *Kplus_PZ, *Kplus_PE);
TLorentzVector Km(*Kminus_PX, *Kminus_PY, *Kminus_PZ, *Kminus_PE);

TLorentzVector PKp;
TLorentzVector PKm;
TLorentzVector KpKm;

PKp = P+Kp;
PKm = P+Km;
KpKm = Kp+Km;

double M2_PKp = PKp.Mag2()/(1000*1000);
double M2_PKm  = PKm.Mag2()/(1000*1000);
double M2_KpKm = KpKm.Mag2()/(1000*1000);
   
bool  PreliminaryCuts= (
     ((*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp) > 0.87)
  && ((*Kminus_ProbNNk)*(*Kplus_ProbNNk) > 0.9)
  && (M2_KpKm > 1.024)
  && (M2_KpKm < 1.057)   
      );
   
   bool IPCHI2Cut = (
      ((TMath::Log10(*Proton_IPCHI2_OWNPV) < 2.5))
   && ((TMath::Log10(*Kminus_IPCHI2_OWNPV) < 2.5))
   && ((TMath::Log10(*Kplus_IPCHI2_OWNPV) < 2.5))
       );
       
   bool PTCut = (
      (*Proton_PT > 950)
   );  
   
   bool DOCACut = (
      (*Lcplus_Loki_DOCACHI2MAX < 18)
  );
   
 if (PreliminaryCuts && IPCHI2Cut && PTCut && DOCACut)
 PreliminaryMass->Fill(*Lcplus_M);
   
 //Defining Signal Region & Background Region//
   bool SignalRegion = *Lcplus_M > 2274. && *Lcplus_M < 2300.;
   bool BackgroundRegion = (*Lcplus_M > 2220. && *Lcplus_M < 2246.) || (*Lcplus_M > 2328. && *Lcplus_M < 2354.);
  
if (PreliminaryCuts & SignalRegion && IPCHI2Cut && PTCut && DOCACut){ 
 LcPTSignal->Fill(*Lcplus_PT);
 PrPTSignal->Fill(*Proton_PT);
 KpPTSignal->Fill(*Kplus_PT);  
 KmPTSignal->Fill(*Kminus_PT); 
 PrChi2Signal->Fill(TMath::Log10(*Proton_IPCHI2_OWNPV));
 KpChi2Signal->Fill(TMath::Log10(*Kplus_IPCHI2_OWNPV)); 
 KmChi2Signal->Fill(TMath::Log10(*Kminus_IPCHI2_OWNPV));
 DOCAMaxSignal->Fill(*Lcplus_Loki_DOCACHI2MAX);
 LcTAUSignal->Fill(*Lcplus_TAU);                                       
}   
   
if (PreliminaryCuts & BackgroundRegion && IPCHI2Cut && PTCut && DOCACut){ 
 LcPTBkgd->Fill(*Lcplus_PT);
 PrPTBkgd->Fill(*Proton_PT);
 KpPTBkgd->Fill(*Kplus_PT);  
 KmPTBkgd->Fill(*Kminus_PT); 
 PrChi2Bkgd->Fill(TMath::Log10(*Proton_IPCHI2_OWNPV));
 KpChi2Bkgd->Fill(TMath::Log10(*Kplus_IPCHI2_OWNPV)); 
 KmChi2Bkgd->Fill(TMath::Log10(*Kminus_IPCHI2_OWNPV));
 DOCAMaxBkgd->Fill(*Lcplus_Loki_DOCACHI2MAX);
 LcTAUBkgd->Fill(*Lcplus_TAU); 
}
 
LcPTSignalEstimate->Add(LcPTSignal,LcPTBkgd,1.0,-0.5);                  
PrPTSignalEstimate->Add(PrPTSignal,PrPTBkgd,1.0,-0.5);  
KpPTSignalEstimate->Add(KpPTSignal,KpPTBkgd,1.0,-0.5);  
KmPTSignalEstimate->Add(KmPTSignal,KmPTBkgd,1.0,-0.5);  
PrChi2SignalEstimate->Add(PrChi2Signal,PrChi2Bkgd,1.0,-0.5);                    
KpChi2SignalEstimate->Add(KpChi2Signal,KpChi2Bkgd,1.0,-0.5);  
KmChi2SignalEstimate->Add(KmChi2Signal,KmChi2Bkgd,1.0,-0.5);  
DOCAMaxSignalEstimate->Add(DOCAMaxSignal,DOCAMaxBkgd,1.0,-0.5);  
LcTAUSignalEstimate->Add(LcTAUSignal,LcTAUBkgd,1.0,-0.5);                    
               
   return kTRUE;
}

void BSubAnalysis::SlaveTerminate()
{
}

void BSubAnalysis::Terminate()
{
   
gStyle->SetOptTitle(0);
c1->cd();
LcPTSignal->GetYaxis()->SetTitle("Events per 100 MeV");
LcPTSignal->GetXaxis()->SetTitle("MeV");   
LcPTSignal->SetMinimum(0);
LcPTSignal->Draw();
LcPTSignalEstimate->Draw("SAME");
LcPTBkgd->Draw("SAME");   
gPad->BuildLegend(0.78,0.75,0.98,0.95);
LcPTSignal->SetTitle("Lcplus_PT Signal Estimates");      
c1->Write("LcPT Estimations");
 c1->Clear();  
  
PrPTSignal->GetYaxis()->SetTitle("Events per 60 MeV");
PrPTSignal->GetXaxis()->SetTitle("MeV");   
PrPTSignal->SetMinimum(0);
PrPTSignal->Draw();
PrPTSignalEstimate->Draw("SAME");
PrPTBkgd->Draw("SAME");     
gPad->BuildLegend(0.78,0.75,0.98,0.95);
PrPTSignal->SetTitle("Proton_PT Signal Estimates");   
c1->Write("PrPT Estimations");
 c1->Clear();     
 
KpPTSignal->GetYaxis()->SetTitle("Events per 50 MeV");
KpPTSignal->GetXaxis()->SetTitle("MeV");   
KpPTSignal->SetMinimum(0);
KpPTSignal->Draw();
KpPTSignalEstimate->Draw("SAME");
KpPTBkgd->Draw("SAME");     
gPad->BuildLegend(0.78,0.75,0.98,0.95);
KpPTSignal->SetTitle("Kplus_PT Signal Estimates");      
c1->Write("KpPT Estimations");
 c1->Clear();  
   
KmPTSignal->GetYaxis()->SetTitle("Events per 50 MeV");
KmPTSignal->GetXaxis()->SetTitle("MeV");   
KmPTSignal->SetMinimum(0);
KmPTSignal->Draw();
KmPTSignalEstimate->Draw("SAME");
KmPTBkgd->Draw("SAME");     
gPad->BuildLegend(0.78,0.75,0.98,0.95);
KmPTSignal->SetTitle("Kminus_PT Signal Estimates");     
c1->Write("KmPT Estimations");
c1->Clear();       
  
PrChi2Signal->GetYaxis()->SetTitle("Events per 1/20 Log10(mm)");
PrChi2Signal->GetXaxis()->SetTitle("Log10(mm)");   
PrChi2Signal->SetMinimum(0);
PrChi2Signal->Draw();
PrChi2SignalEstimate->Draw("SAME");
PrChi2Bkgd->Draw("SAME");     
gPad->BuildLegend(0.78,0.75,0.98,0.95);
PrChi2Signal->SetTitle("Proton_IPCHI2_OWNPV Signal Estimates");    
c1->Write("PrChi2 Estimations");
c1->Clear();  
 
KpChi2Signal->GetYaxis()->SetTitle("Events per 1/20 Log10(mm)");
KpChi2Signal->GetXaxis()->SetTitle("Log10(mm)");   
KpChi2Signal->SetMinimum(0);
KpChi2Signal->Draw();
KpChi2SignalEstimate->Draw("SAME");
KpChi2Bkgd->Draw("SAME");     
gPad->BuildLegend(0.78,0.75,0.98,0.95);
KpChi2Signal->SetTitle("Kplus_IPCHI2_OWNPV Signal Estimates");      
c1->Write("KpChi2 Estimations");
c1->Clear();
   
KmChi2Signal->GetYaxis()->SetTitle("Events per 1/20 Log10(mm)");
KmChi2Signal->GetXaxis()->SetTitle("Log10(mm)");   
KmChi2Signal->SetMinimum(0);
KmChi2Signal->Draw();
KmChi2SignalEstimate->Draw("SAME");
KmChi2Bkgd->Draw("SAME");     
gPad->BuildLegend(0.78,0.75,0.98,0.95);
KmChi2Signal->SetTitle("Kminus_IPCHI2_OWNPV Signal Estimates");      
c1->Write("KmChi2 Estimations");
c1->Clear();    
  
DOCAMaxSignal->GetYaxis()->SetTitle("Events per 1 mm");
DOCAMaxSignal->GetXaxis()->SetTitle("mm");   
DOCAMaxSignal->SetMinimum(0);
DOCAMaxSignal->Draw();
DOCAMaxSignalEstimate->Draw("SAME");
DOCAMaxBkgd->Draw("SAME");     
gPad->BuildLegend(0.78,0.75,0.98,0.95);
DOCAMaxSignal->SetTitle("Lcplus_Loki_DOCACHI2MAX Signal Estimates");      
c1->Write("DOCAMax Estimations");
c1->Clear();  
   
LcTAUSignal->GetYaxis()->SetTitle("Events per 1/1000 nanoseconds");
LcTAUSignal->GetXaxis()->SetTitle("nanoseconds");   
LcTAUSignal->SetMinimum(0);
LcTAUSignal->Draw();
LcTAUSignalEstimate->Draw("SAME");
LcTAUBkgd->Draw("SAME");     
gPad->BuildLegend(0.78,0.75,0.98,0.95);
LcTAUSignal->SetTitle("Lcplus_TAU Signal Estimates");    
c1->Write("LcTAU Estimations");
c1->Clear();     
   
TPad *pad1 = new TPad("pad1","pad1",0,0.33,1,1);
TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.33);
pad2->SetTopMargin(0.03030303);
pad1->Draw();
pad2->Draw();    
   
  Double_t sigma;
  Double_t deltaSigma;
  Double_t mu;
  Double_t deltaMu;
  Double_t total;
  Double_t deltaTotal;
  TString sigmaStr;
  TString deltaSigmaStr;
  TString muStr;
  TString deltaMuStr;
  TString totalStr;
  TString deltaTotalStr;

  TF1 *Gaussian = new TF1("Gaussian",DGOneMuOneTotalHalfMeV,2200.,2400.,7);
  Gaussian->SetParameter(0, 0.6);
  Gaussian->SetParLimits(0, 0., 1.);
  Gaussian->SetParameter(1, 20000);
  Gaussian->SetParameter(2, 2287.);
  Gaussian->SetParameter(3, 5);
  Gaussian->SetParameter(4, 5);
  Gaussian->SetParLimits(3, 0., 15.);
  Gaussian->SetParLimits(4, 0., 15.);
  Gaussian->SetParameter(5, 0.);
  Gaussian->SetParameter(6, 0.);

  pad1->cd();
  PreliminaryMass->SetMinimum(0);
  PreliminaryMass->Fit("Gaussian");

  double Pullx[300];
  int BinHeight[300];
  int FitHeight[300];
  double Pull[300];

  double count1 = 0;
  double count2 = 0;
  double count3 = 0;

  for (int bin = 0; bin < 300; bin++){
  BinHeight[bin] = PreliminaryMass->GetBinContent(bin + 1);
  Pullx[bin] = (bin + 1);
  int xvalue = 2210.25 + 0.5*(bin);
  FitHeight[bin] = round(Gaussian->Eval(xvalue));
  Pull[bin] = (BinHeight[bin] - FitHeight[bin])/TMath::Sqrt(FitHeight[bin]);

  if (Pull[bin] > -1 && Pull[bin] < 1){
    count1 += 1;
  }

  if (Pull[bin] > -2 && Pull[bin] < 2){
    count2 += 1;
  }

  if (Pull[bin] > -3 && Pull[bin] < 3){
    count3 += 1;
  }
  }

  pad2->cd();
  TGraph* PullPlot = new TGraph(300, Pullx, Pull);
  PullPlot->GetXaxis()->SetLimits(0.5,300.5);
  PullPlot->GetXaxis()->SetTickLength(0.);
  PullPlot->GetYaxis()->SetTickLength(0.);
  PullPlot->SetFillColor(38);
  PullPlot->GetYaxis()->SetTitle("Pull");
  PullPlot->GetYaxis()->CenterTitle();
  PullPlot->GetYaxis()->SetTitleSize(0.10);
  PullPlot->GetYaxis()->SetTitleOffset(0.2);
  PullPlot->GetXaxis()->SetLabelSize(0);
  PullPlot->GetYaxis()->SetLabelFont(42);
  PullPlot->GetYaxis()->SetLabelSize(0.06);
  PullPlot->SetTitle("");
  PullPlot->SetMinimum(-5);
  PullPlot->SetMaximum(5);
  PullPlot->Draw("AB");
        c1->Write("Lc Mass");

  ex1->cd();
   ex1->Clear();
     TLatex Tl;
     Tl.SetTextAlign(12);
     Tl.SetTextSize(0.04);
     Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", Gaussian->GetParameter(1)));
     Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", Gaussian->GetParError(1)));
     Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", Gaussian->GetParameter(0)));
     Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", Gaussian->GetParError(0)));
     Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", Gaussian->GetParameter(2)));
     Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", Gaussian->GetParError(2)));
     Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", Gaussian->GetParameter(3)));
     Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", Gaussian->GetParError(3)));
     Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", Gaussian->GetParameter(4)));
     Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", Gaussian->GetParError(4)));
     Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", count1));
     Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", count2));
     Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", count3));

     ex1->Write("Fit Values");
   File->Close();
}
