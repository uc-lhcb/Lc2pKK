#define DalitzPlot_cxx
#include "DalitzPlot.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

TH2D * DalitzPlotLc = nullptr;
TH1D * KpKmMassHist = nullptr;
TH1D * PKmMassHist = nullptr;
TH1D * MassHist = nullptr;

void DalitzPlot::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
         DalitzPlotLc = new TH2D("Dalitz Plot", "Dalitz Plot of Lc->pKK Decay", 100, 0.7, 4.2, 100, 0.25, 1.0);
         DalitzPlotLc->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
         DalitzPlotLc->GetYaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
         DalitzPlotLc->GetZaxis()->SetTitle("Events");
                                          
         KpKmMassHist = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Kplus Invariant Mass Combination", 100, 0.95, 2);
         KpKmMassHist->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");                    
         KpKmMassHist->GetYaxis()->SetTitle("Events");
 
         PKmMassHist = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kminus Invariant Mass Combination", 100, 2, 3.5);
         PKmMassHist->GetXaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");                   
         PKmMassHist->GetYaxis()->SetTitle("Events");
   
         MassHist = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 300, 2210, 2360);
         MassHist->GetXaxis()->SetTitle("MeV");
         MassHist->GetYaxis()->SetTitle("Events Per 0.5 MeV");
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
     
  double E_P  = TMath::Sqrt((P_P)*(P_P)+(M_P)*(M_P));
  double E_Kp = TMath::Sqrt((P_Kp)*(P_Kp)+(M_Kp)*(M_Kp));
  double E_Km = TMath::Sqrt((P_Km)*(P_Km)+(M_Km)*(M_Km));
   
double M2_KpKm = (((E_Kp)+(E_Km))*((E_Kp)+(E_Km)) - ((P_Kp)+(P_Km))*((P_Kp)+(P_Km)))/(1000*1000);
double M2_PKm  = (((E_P)+(E_Km))*((E_P)+(E_Km)) - ((P_P)+(P_Km))*((P_P)+(P_Km)))/(1000*1000);
   
 KpKmMassHist->Fill(M2_KpKm);
 PKmMassHist->Fill(M2_PKm);

   if (M2_KpKm < 1.1){
    MassHist->Fill(*Lcplus_M);
&& (*Kminus_ProbNNk)*(Kplus_ProbNNk)*(Proton_ProbNNp) > 0.9;
 }
   
   return kTRUE;
}

void DalitzPlot::SlaveTerminate()
{
}

void DalitzPlot::Terminate()
{
MassHist->Draw();
}
