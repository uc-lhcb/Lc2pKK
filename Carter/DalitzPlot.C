#define DalitzPlot_cxx
#include "DalitzPlot.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

TH2D * DalitzPlot = nullptr;
TH1D * KpKmMassHist = nullptr;
TH1D * PKmMassHist = nullptr;

void DalitzPlot::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
         DalitzPlot = new TH2D("Dalitz Plot", "Dalitz Plot of Lc->pKK Decay", 100, 0.7, 4.2, 100, 0.25, 1.0);
         DalitzPlot->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
         DalitzPlot->GetYaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
         DalitzPlot->GetZaxis()->SetTitle(Entries);
                                          
         KpKmMassHist = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Pplus Invariant Mass Combination", 100, 1, 2);
         KpKmMassHist->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");                    
         KpKmMassHist->GetYaxis()->SetTitle("Events");
 
         PKmMassHist = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Pplus Invariant Mass Combination", 100, 1.5, 3);
         PKmMassHist->GetXaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");                   
         PKmMassHist->GetYaxis()->SetTitle("Events");
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
     
  double E_P  = TMATH::Sqrt((P_P)*(P_P)+(P_M)*(P_M));
  double E_Kp = TMATH::Sqrt((Kp_P)*(Kp_P)+(Kp_M)*(Kp_M));
  double E_Km = TMATH::Sqrt((Km_P)*(Km_P)+(Km_M)*(Km_M));
   
double M2_KpKm = (((E_Kp)+(E_Km))*((E_Kp)+(E_Km)) - ((Kp_P)+(Km_P))*((Kp_P)+(Km_P)))/(1000*1000);
double M2_PKm  = (((E_P)+(E_Km))*((E_P)+(E_Km)) - ((P_P)+(Km_P))*((P_P)+(Km_P)))/(1000*1000);
   
 KpKmMassHist->Fill(M2_KpKm);
   
   return kTRUE;
}

void DalitzPlot::SlaveTerminate()
{
}

void DalitzPlot::Terminate()
{
KpKmMassHist->Draw();
}
