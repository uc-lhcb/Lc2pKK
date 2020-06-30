#define Run1Dalitz_cxx
#include "Run1Dalitz.h"

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

void Run1Dalitz::Begin(TTree * /*tree*/)
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
   
    File = new TFile("DalitzRun1.root", "RECREATE");
  gFile = File;

   c1 = new TCanvas("canvas", "Test Canvas")
}

void Run1Dalitz::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

}

Bool_t Run1Dalitz::Process(Long64_t entry)
{
   GetEntry(entry);
   fReader.SetLocalEntry(entry);
 
  double P_P  = *Lc_p_P;
  double P_Kp = *Lc_h2_P;
  double P_Km = *Lc_h1_P;
 
  double M_P  = *Lc_p_M;
  double M_Kp = *Lc_h2_M;
  double M_Km = *Lc_h1_M;
     
  double E_P  = TMath::Sqrt(((P_P)*(P_P))+((M_P)*(M_P)));
  double E_Kp = TMath::Sqrt(((P_Kp)*(P_Kp))+((M_Kp)*(M_Kp)));
  double E_Km = TMath::Sqrt(((P_Km)*(P_Km))+((M_Km)*(M_Km)));
   
double M2_KpKm = ((((E_Kp)+(E_Km))*((E_Kp)+(E_Km))) - (((P_Kp)+(P_Km))*((P_Kp)+(P_Km))))/(1000*1000);
double M2_PKm  = ((((E_P)+(E_Km))*((E_P)+(E_Km))) - (((P_P)+(P_Km))*((P_P)+(P_Km))))/(1000*1000);
double M2_PKp  = ((((E_P)+(E_Kp))*((E_P)+(E_Kp))) - (((P_P)+(P_Kp))*((P_P)+(P_Kp))))/(1000*1000);

 KpKmMassHist->Fill(M2_KpKm);
 PKmMassHist->Fill(M2_PKm);
 PKpMassHist->Fill(M2_PKp);
 DalitzPlotLc->Fill(M2_KpKm, M2_PKm);

   return kTRUE;
}

void Run1Dalitz::SlaveTerminate()
{
}

void Run1Dalitz::Terminate()
{
   
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
   
}
