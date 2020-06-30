#define DalitzPlot_cxx
#include "DalitzPlot.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

#include "fitHalfMeV_Gaussian.C"

TH2D * DalitzPlotLc = nullptr;
TH1D * KpKmMassHist = nullptr;
TH1D * PKmMassHist = nullptr;
TH1D * PKpMassHist = nullptr;
TH1D * MassHist = nullptr;


TFile * File = nullptr;

TCanvas * c1 = nullptr;

void DalitzPlot::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
         DalitzPlotLc = new TH2D("Dalitz Plot", "Dalitz Plot of Lc->pKK Decay", 100, 0.8, 2.2, 100, 1.7, 3.7);
         DalitzPlotLc->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
         DalitzPlotLc->GetYaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
         DalitzPlotLc->GetZaxis()->SetTitle("Events");
                                          
         KpKmMassHist = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Kplus Invariant Mass Combination", 100, 0.95, 2);
         KpKmMassHist->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");                    
         KpKmMassHist->GetYaxis()->SetTitle("Events");
 
         PKmMassHist = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kminus Invariant Mass Combination", 100, 2, 3.5);
         PKmMassHist->GetXaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");                   
         PKmMassHist->GetYaxis()->SetTitle("Events");
   
         PKpMassHist = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kplus Invariant Mass Combination", 100, 2, 3.5);
         PKpMassHist->GetXaxis()->SetTitle("m^{2}(pK^{+})[GeV^{2}/c^{4}]");                   
         PKpMassHist->GetYaxis()->SetTitle("Events");   
   
         MassHist = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 300, 2210, 2360);
         MassHist->GetXaxis()->SetTitle("MeV");
         MassHist->GetYaxis()->SetTitle("Events Per 0.5 MeV");
   
    File = new TFile("DalitzAnalysis.root", "RECREATE");
  gFile = File;

   c1 = new TCanvas("canvas", "Test Canvas");
}

void DalitzPlot::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
}

Bool_t DalitzPlot::Process(Long64_t entry)
{
   GetEntry(entry);
   fReader.SetLocalEntry(entry);
 
  double P_P  = *Proton_P;
  double P_Kp = *Kplus_P;
  double P_Km = *Kminus_P;
 
  double M_P  = *Proton_M;
  double M_Kp = *Kplus_M;
  double M_Km = *Kminus_M;
     
  double E_P  = TMath::Sqrt(((P_P)*(P_P))+((M_P)*(M_P)));
  double E_Kp = TMath::Sqrt(((P_Kp)*(P_Kp))+((M_Kp)*(M_Kp)));
  double E_Km = TMath::Sqrt(((P_Km)*(P_Km))+((M_Km)*(M_Km)));
   
double M2_KpKm = ((((E_Kp)+(E_Km))*((E_Kp)+(E_Km))) - (((P_Kp)+(P_Km))*((P_Kp)+(P_Km))))/(1000*1000);
double M2_PKm  = ((((E_P)+(E_Km))*((E_P)+(E_Km))) - (((P_P)+(P_Km))*((P_P)+(P_Km))))/(1000*1000);
double M2_PKp  = (((E_P)+(E_Kp))*((E_P)+(E_Kp))) - (((P_P)+(P_Kp))*((P_P)+(P_Kp))))/(1000*1000);
   
 KpKmMassHist->Fill(M2_KpKm);
 PKmMassHist->Fill(M2_PKm);
 PKpMassHist->Fill(M2_PKp);
 DalitzPlotLc->Fill(M2_KpKm, M2_PKm);

 bool Cuts = (
   M2_KpKm < 1.1
&& M2_PKm < 2.1
 );
   
   if (Cuts){
    MassHist->Fill(*Lcplus_M);
 }
   
   return kTRUE;
}

void DalitzPlot::SlaveTerminate()
{
}

void DalitzPlot::Terminate()
{
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
   
c1->cd();
DalitzPlotLc->Draw();
 c1->Write("Dalitz Plot");
DalitzPlotLc->Draw("COLZ");
 c1->Write("Dalitz Plot - COLZ");
DalitzPlotLc->Draw("CONTZ");
 c1->Write("Dalitz Plot - CONTZ");
   
KpKmMassHist->Draw();
 c1->Write("Kp & Km Mass"); 
   
 PKmMassHist->Draw();
 c1->Write("P & Km Mass");
   
 PKpMassHist->Draw();
 c1->Write("P & Kp Mass");
   
TF1 *GaussianTightHalfMeVSG = new TF1("GaussianTightHalfMeVSG",fitHalfMeV_Gaussian,2100.,2500.,5);
GaussianTightHalfMeVSG->SetParameter(0,400.);
GaussianTightHalfMeVSG->SetParameter(1,2286);
GaussianTightHalfMeVSG->SetParameter(2, 6);
GaussianTightHalfMeVSG->SetParLimits(2, 0.,20.);
GaussianTightHalfMeVSG->SetParameter(3, 0.);
GaussianTightHalfMeVSG->SetParameter(4, 0.);

MassHist->SetMinimum(0);
MassHist->Fit("GaussianTightHalfMeVSG");
c1->Write("Lc Mass");
File->Close();
}
