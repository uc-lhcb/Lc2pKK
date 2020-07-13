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
TH1D * LcPTBkgrd = nullptr;
TH1D * LcPTSignalEstimate = nullptr;

TH1D * PrPTSignal = nullptr;
TH1D * PrPTBkgrd = nullptr;
TH1D * PrPTSignalEstimate = nullptr;

TH1D * KpPTSignal = nullptr;
TH1D * KpPTBkgrd = nullptr;
TH1D * KpPTSignalEstimate = nullptr;

TH1D * KmPTSignal = nullptr;
TH1D * KmPTBkgrd = nullptr;
TH1D * KmPTSignalEstimate = nullptr;

TH1D * PrChi2Signal = nullptr;
TH1D * PrChi2Bkgrd = nullptr;
TH1D * PrChi2SignalEstimate = nullptr;

TH1D * KpChi2Signal = nullptr;
TH1D * KpChi2Bkgrd = nullptr;
TH1D * KpChi2SignalEstimate = nullptr;

TH1D * KmChi2Signal = nullptr;
TH1D * KmChi2Bkgrd = nullptr;
TH1D * KmChi2SignalEstimate = nullptr;

TH1D * DOCAMaxSignal = nullptr;
TH1D * DOCAMaxBkgrd = nullptr;
TH1D * DOCAMaxSignalEstimate = nullptr;

TH1D * LcTAUSignal = nullptr;
TH1D * LcTAUBkgrd = nullptr;
TH1D * LcTAUSignalEstimate = nullptr;

TCanvas * c1 = nullptr;
TFile * File = nullptr;

void BSubAnalysis::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
   
}

void BSubAnalysis::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();


c1 = new TCanvas("Background Subtraction","Histograms",1000,500);   
     File = new TFile("BackgroundSubtraction.root", "RECREATE");
     gFile = File;

   TH1::SetDefaultSumw2(kTRUE);

   PreliminaryMass = new TH1D("Mass", "LambdaC Mass - Phi Resonance & PID Cuts", 300, 2210, 2360);
   PreliminaryMass->GetXaxis()->SetTitle("MeV");
   PreliminaryMass->GetYaxis()->SetTitle("Events Per 1/2 MeV");

LcPTSignal = new TH1D("Transverse Momentum", "Signal Region", 200, 2000, 22000);
LcPTBkgd = new TH1D("Transverse Momentum", "Background Region", 200, 2000, 22000);
LcPTSignalEstimate = new TH1D("Transverse Momentum", "Signal Estimation", 200, 2000, 22000);
LcPTSignal->SetLineColor(kBlue);
LcPTBkgd->SetLineColor(kRed);
LcPTSignalEstimate->SetLineColor(kGreen+3);
   
PrPTSignal = new TH1D("Transverse Momentum", "Signal Region", 200, 0, 12000);
PrPTBkgd = new TH1D("Transverse Momentum", "Background Region", 200, 0, 12000);
PrPTSignalEstimate = new TH1D("Transverse Momentum", "Signal Estimation", 200, 0, 12000);   
PrPTSignal->SetLineColor(kBlue);
PrPTBkgd->SetLineColor(kRed);
PrPTSignalEstimate->SetLineColor(kGreen+3);
   
KpPTSignal = new TH1D("Transverse Momentum", "Signal Region", 200, 0, 9000);
KpPTBkgd = new TH1D("Transverse Momentum", "Background Region", 200, 0, 9000);
KpPTSignalEstimate = new TH1D("Transverse Momentum", "Signal Estimation", 200, 0, 9000);
KpPTSignal->SetLineColor(kBlue);
KpPTBkgd->SetLineColor(kRed);
KpPTSignalEstimate->SetLineColor(kGreen+3);  
   
KmPTSignal = new TH1D("Transverse Momentum", "Signal Region", 200, 0, 9000);
KmPTBkgd = new TH1D("Transverse Momentum", "Background Region", 200, 0, 9000);
KmPTSignalEstimate = new TH1D("Transverse Momentum", "Signal Estimation", 200, 0, 9000);
KmPTSignal->SetLineColor(kBlue);
KmPTBkgd->SetLineColor(kRed);
KmPTSignalEstimate->SetLineColor(kGreen+3); 
   
PrChi2Signal = new TH1D("Log(IPCHI2)", "Signal Region", 100, 0, 4.5);
PrChi2Bkgd = new TH1D("Log(IPCHI2)", "Background Region", 100, 0, 4.5);
PrChi2SignalEstimate = new TH1D("Log(IPCHI2)", "Signal Estimation", 100, 0, 4.5);
PrChi2Signal->SetLineColor(kBlue);
PrChi2Bkgd->SetLineColor(kRed);
PrChi2SignalEstimate->SetLineColor(kGreen+3);

KpChi2Signal = new TH1D("Log(IPCHI2)", "Signal Region", 100, 0, 5);
KpChi2Bkgd = new TH1D("Log(IPCHI2)", "Background Region", 100, 0, 5);
KpChi2SignalEstimate = new TH1D("Log(IPCHI2)", "Signal Estimation", 100, 0, 5);   
KpChi2Signal->SetLineColor(kBlue);
KpChi2Bkgd->SetLineColor(kRed);
KpChi2SignalEstimate->SetLineColor(kGreen+3);
   
KmChi2Signal = new TH1D("Log(IPCHI2)", "Signal Region", 100, 0, 5);
KmChi2Bkgd = new TH1D("Log(IPCHI2)", "Background Region", 100, 0, 5);
KmChi2SignalEstimate = new TH1D("Log(IPCHI2)", "Signal Estimation", 100, 0, 5);   
KmChi2Signal->SetLineColor(kBlue);
KmChi2Bkgd->SetLineColor(kRed);
KmChi2SignalEstimate->SetLineColor(kGreen+3);

DOCAMaxSignal = new TH1D("DOCA", "Signal Region", 200, 0, 1500);
DOCAMaxBkgd = new TH1D("DOCA", "Background Region", 200, 0, 1500);
DOCAMaxSignalEstimate = new TH1D("DOCA", "Signal Estimation", 200, 0, 1500);
DOCAMaxSignal->SetLineColor(kBlue);
DOCAMaxBkgd->SetLineColor(kRed);
DOCAMaxSignalEstimate->SetLineColor(kGreen+3);
 
LcTAUSignal = new TH1D("DOCA", "Signal Region", 200, -0.5, 1.5);
LcTAUBkgd = new TH1D("DOCA", "Background Region", 200, -0.5, 1.5);
LcTAUSignalEstimate = new TH1D("DOCA", "Signal Estimation", 200, -0.5, 1.5);
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
     ((*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp) > 0.8)
  && ((*Kminus_ProbNNk)*(*Kplus_ProbNNk) > 0.9)
  && (M2_KpKm > 1.024)
  && (M2_KpKm < 1.057)   
      );
   

 if (PreliminaryCuts)
 PreliminaryMass->Fill(*Lcplus_M);
   
 //Defining Signal Region & Background Region//
   bool SignalRegion = CorrectedLambdaMass > 2274. && CorrectedLambdaMass < 2300.;
   bool BackgroundRegion = (CorrectedLambdaMass > 2220. && CorrectedLambdaMass < 2246.) || (CorrectedLambdaMass > 2328. && CorrectedLambdaMass < 2354.);
  
if (PreliminaryCuts & SignalRegion){ 
 LcPTSignal->Fill(*Lcplus_PT);
 PrPTSignal->Fill(*Proton_PT);
 KpPTSignal->Fill(*Kplus_PT);  
 KmPTSignal->Fill(*Kminus_PT); 
 PrChi2Signal->Fill(TMath::Log10(*Proton_IPCHI2_OWNPV);
 KpChi2Signal->Fill(TMath::Log10(*Kplus_IPCHI2_OWNPV); 
 KmChi2Signal->Fill(TMath::Log10(*Kminus_IPCHI2_OWNPV);
 DOCAMaxSignal->Fill(*Lcplus_Loki_DOCACHI2MAX);
 LcTAUSignal->Fill(*Lcplus_TAU);                                       
}   
   
if (PreliminaryCuts & BackgroundRegion){ 
 LcPTBkgd->Fill(*Lcplus_PT);
 PrPTBkgd->Fill(*Proton_PT);
 KpPTBkgd->Fill(*Kplus_PT);  
 KmPTBkgd->Fill(*Kminus_PT); 
 PrChi2Bkgd->Fill(TMath::Log10(*Proton_IPCHI2_OWNPV);
 KpChi2Bkgd->Fill(TMath::Log10(*Kplus_IPCHI2_OWNPV); 
 KmChi2Bkgd->Fill(TMath::Log10(*Kminus_IPCHI2_OWNPV);
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
 ////add doca and tau                 
   return kTRUE;
}

void BSubAnalysis::SlaveTerminate()
{

}

void BSubAnalysis::Terminate()
{

}
