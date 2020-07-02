#define DalitzPlot_cxx
#include "DalitzPlot.h"

//ROOT Libraries
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

//Histogram Creation
TH2D * DalitzPlotLc = nullptr;
TH1D * KpKmMassHist = nullptr;
TH1D * PKmMassHist = nullptr;
TH1D * PKpMassHist = nullptr;


TH1D * MassHist = nullptr;
TH1D * BSubHist = nullptr;

//ROOT File Creation
TFile * File = nullptr;

//Canvas Creation
TCanvas * c1 = nullptr;

void DalitzPlot::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
   
         //Dalitz Plot is a 2D Histogram
         DalitzPlotLc = new TH2D("Dalitz Plot", "Dalitz Plot of Lc->pKK Decay", 100, 0.8, 2.2, 100, 1.7, 3.7);
         DalitzPlotLc->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
         DalitzPlotLc->GetYaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
         DalitzPlotLc->GetZaxis()->SetTitle("Events");
         
         //Plot of M^2 Variable for K+ and K- Combination
         KpKmMassHist = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Kminus Invariant Mass Combination", 100, 0.95, 2);
         KpKmMassHist->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");                    
         KpKmMassHist->GetYaxis()->SetTitle("Events");
 
         //Plot of M^2 Variable for p+ and K- Combination
         PKmMassHist = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kminus Invariant Mass Combination", 100, 2, 3.5);
         PKmMassHist->GetXaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");                   
         PKmMassHist->GetYaxis()->SetTitle("Events");
   
         //Plot of M^2 Variable for p+ and K+ Combination (Not Used for Dalitz Plot)
         PKpMassHist = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kplus Invariant Mass Combination", 100, 2, 3.5);
         PKpMassHist->GetXaxis()->SetTitle("m^{2}(pK^{+})[GeV^{2}/c^{4}]");                   
         PKpMassHist->GetYaxis()->SetTitle("Events");   

   
   MassHist = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 300, 2210, 2360);
   MassHist->GetXaxis()->SetTitle("MeV");
   MassHist->GetYaxis()->SetTitle("Events Per 2 MeV");
   
   BSubHist = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 50, 2275, 2300);
   BSubHist->GetXaxis()->SetTitle("MeV");
   BSubHist->GetYaxis()->SetTitle("Events Per 2 MeV");
   
   //Output ROOT File
    File = new TFile("DalitzAnalysis.root", "RECREATE");
  gFile = File;

   //Defining Canvas
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
 
//Defining Variables
double P_P  = *Proton_P;
double P_Kp = *Kplus_P;
double P_Km = *Kminus_P;
 
double M_P  = *Proton_M;
double M_Kp = *Kplus_M;
double M_Km = *Kminus_M;
 
//Creating Energy Variables
double E_P  = TMath::Sqrt(((P_P)*(P_P))+((M_P)*(M_P)));
double E_Kp = TMath::Sqrt(((P_Kp)*(P_Kp))+((M_Kp)*(M_Kp)));
double E_Km = TMath::Sqrt(((P_Km)*(P_Km))+((M_Km)*(M_Km)));
   
//Creating M^2 Variables
double M2_KpKm = ((((E_Kp)+(E_Km))*((E_Kp)+(E_Km))) - (((P_Kp)+(P_Km))*((P_Kp)+(P_Km))))/(1000*1000);
double M2_PKm  = ((((E_P)+(E_Km))*((E_P)+(E_Km))) - (((P_P)+(P_Km))*((P_P)+(P_Km))))/(1000*1000);
double M2_PKp  = ((((E_P)+(E_Kp))*((E_P)+(E_Kp))) - (((P_P)+(P_Kp))*((P_P)+(P_Kp))))/(1000*1000);

 if ((*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp)) > 0.6){
    MassHist->Fill(*Lcplus_M);
    BsubHist->Fill(*Lcplus_M);
 }  
       
//Filling Histogram
 KpKmMassHist->Fill(M2_KpKm);
 PKmMassHist->Fill(M2_PKm);
 PKpMassHist->Fill(M2_PKp);
 DalitzPlotLc->Fill(M2_KpKm, M2_PKm);
   
   return kTRUE;
}

void DalitzPlot::SlaveTerminate()
{
}

void DalitzPlot::Terminate()
{
   
//Changes Current Directory to c1 to Canvas 
c1->cd();

//Creates Dalitz Plots with Various Options
DalitzPlotLc->Draw();
 c1->Write("Dalitz Plot");
DalitzPlotLc->Draw("COLZ");
 c1->Write("Dalitz Plot - COLZ");
DalitzPlotLc->Draw("CONTZ");
 c1->Write("Dalitz Plot - CONTZ");

 //Creates Histograms for M^2 Variables  
KpKmMassHist->Draw();
 c1->Write("Kp & Km Mass"); 
   
 PKmMassHist->Draw();
 c1->Write("P & Km Mass");
   
 PKpMassHist->Draw();
 c1->Write("P & Kp Mass");
 
   
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
   
TF1 *GaussianLooseHalfMeVSG = new TF1("GaussianLooseHalfMeVSG",fitHalfMeV_Gaussian,2100.,2500.,5);
GaussianLooseHalfMeVSG->SetParameter(0,400.);
GaussianLooseHalfMeVSG->SetParameter(1,2287);
GaussianLooseHalfMeVSG->SetParameter(2, 6);
GaussianLooseHalfMeVSG->SetParLimits(2, 0.,20.);
GaussianLooseHalfMeVSG->SetParameter(3, 0.);
GaussianLooseHalfMeVSG->SetParameter(4, 0.);
   
MassHist->SetMinimum(0);
MassHist->Fit("GaussianLooseHalfMeVSG");  
 c1->Write("Lc Mass"); 
   
BSubHist->Draw();
c1->Write("Signal Events")  
   
File->Close();
}
