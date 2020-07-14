//Determine KpKm Cut
//Apply KpKm Cut + PID Cuts

#define DalitzPlot_cxx
#include "DalitzPlot.h"

#include "DGOneMuOneTotalHalfMeV.C"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

//Plots when Lc Mass Less than Resonance Using Loose PID Cut
TH2D * DPLooseLB = nullptr;
TH1D * KpKmLooseLB = nullptr;
TH1D * PKmLooseLB = nullptr;
TH1D * PKpLooseLB = nullptr;
TH1D * KpKmLooseLBZoom = nullptr;
//Plots when Lc Mass at Resonance Using Loose PID Cut
TH2D * DPLooseSig = nullptr;
TH1D * KpKmLooseSig = nullptr;
TH1D * PKmLooseSig = nullptr;
TH1D * PKpLooseSig = nullptr;
TH1D * KpKmLooseSigZoom = nullptr;
//Plots when Lc Mass Greater than Resonance Using Loose PID Cut
TH2D * DPLooseRB = nullptr;
TH1D * KpKmLooseRB = nullptr;
TH1D * PKmLooseRB = nullptr;
TH1D * PKpLooseRB = nullptr;
TH1D * KpKmLooseRBZoom = nullptr;

//////////////////////////////////////////////////////////

//Plots when Lc Mass Less than Resonance Using Tight PID Cut
TH2D * DPTightLB = nullptr;
TH1D * KpKmTightLB = nullptr;
TH1D * PKmTightLB = nullptr;
TH1D * PKpTightLB = nullptr;
TH1D * KpKmTightLBZoom = nullptr;
//Plots when Lc Mass at Resonance Using Tight PID Cut
TH2D * DPTightSig = nullptr;
TH1D * KpKmTightSig = nullptr;
TH1D * PKmTightSig = nullptr;
TH1D * PKpTightSig = nullptr;
TH1D * KpKmTightSigZoom = nullptr;
//Plots when Lc Mass Greater than Resonance Using Tight PID Cut
TH2D * DPTightRB = nullptr;
TH1D * KpKmTightRB = nullptr;
TH1D * PKmTightRB = nullptr;
TH1D * PKpTightRB = nullptr;
TH1D * KpKmTightRBZoom = nullptr;

////////////////////////////////////////////////////////////

TH1D * MHistLoose = nullptr;
TH1D * MHistTight = nullptr;
TH1D * MHistDalitzLoose = nullptr;
TH1D * MHistDalitzTight = nullptr;

TFile * File = nullptr;

TCanvas * c1 = nullptr;
TCanvas * ex1 = nullptr;

void DalitzPlot::Begin(TTree * /*tree*/)
{
   TString option = GetOption();

   //Dalitz Plot LooseLB
   DPLooseLB = new TH2D("Dalitz Plot", "Dalitz Plot of Lc->pKK Decay - LooseLB", 200, 0.8, 2.2, 200, 1.7, 3.7);
   DPLooseLB->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   DPLooseLB->GetYaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
   DPLooseLB->GetZaxis()->SetTitle("Events");
   //Plot of M^2 Variable for K+ and K- Combination LooseLB
   KpKmLooseLB = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Kminus Invariant Mass Combination LooseLB", 200, 0.95, 2);
   KpKmLooseLB->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   KpKmLooseLB->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for K+ and K- Combination LooseLB Zoomed into Resonance
   KpKmLooseLBZoom = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Kminus Invariant Mass Combination LooseLB", 200, 0.95, 1.21);
   KpKmLooseLBZoom->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   KpKmLooseLBZoom->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for p+ and K- Combination LooseLB
   PKmLooseLB = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kminus Invariant Mass Combination LooseLB", 200, 2, 3.5);
   PKmLooseLB->GetXaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
   PKmLooseLB->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for p+ and K+ Combination LooseLB (Not Used for Dalitz Plot)
   PKpLooseLB = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kplus Invariant Mass Combination LooseLB", 200, 2, 3.5);
   PKpLooseLB->GetXaxis()->SetTitle("m^{2}(pK^{+})[GeV^{2}/c^{4}]");
   PKpLooseLB->GetYaxis()->SetTitle("Events");

   //Dalitz Plot LooseSig
   DPLooseSig = new TH2D("Dalitz Plot", "Dalitz Plot of Lc->pKK Decay - LooseSig", 200, 0.8, 2.2, 200, 1.7, 3.7);
   DPLooseSig->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   DPLooseSig->GetYaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
   DPLooseSig->GetZaxis()->SetTitle("Events");
   //Plot of M^2 Variable for K+ and K- Combination LooseSig
   KpKmLooseSig = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Kminus Invariant Mass Combination LooseSig", 200, 0.95, 2);
   KpKmLooseSig->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   KpKmLooseSig->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for K+ and K- Combination LooseSig Zoomed into Resonance
   KpKmLooseSigZoom = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Kminus Invariant Mass Combination LooseSig", 200, 0.95, 1.21);
   KpKmLooseSigZoom->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   KpKmLooseSigZoom->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for p+ and K- Combination LooseSig
   PKmLooseSig = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kminus Invariant Mass Combination LooseSig", 200, 2, 3.5);
   PKmLooseSig->GetXaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
   PKmLooseSig->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for p+ and K+ Combination LooseSig (Not Used for Dalitz Plot)
   PKpLooseSig = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kplus Invariant Mass Combination LooseSig", 200, 2, 3.5);
   PKpLooseSig->GetXaxis()->SetTitle("m^{2}(pK^{+})[GeV^{2}/c^{4}]");
   PKpLooseSig->GetYaxis()->SetTitle("Events");

   //Dalitz Plot LooseRB
   DPLooseRB = new TH2D("Dalitz Plot", "Dalitz Plot of Lc->pKK Decay - LooseRB", 200, 0.8, 2.2, 200, 1.7, 3.7);
   DPLooseRB->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   DPLooseRB->GetYaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
   DPLooseRB->GetZaxis()->SetTitle("Events");
   //Plot of M^2 Variable for K+ and K- Combination LooseRB
   KpKmLooseRB = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Kminus Invariant Mass Combination LooseRB", 200, 0.95, 2);
   KpKmLooseRB->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   KpKmLooseRB->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for K+ and K- Combination LooseRB Zoomed into Resonance
   KpKmLooseRBZoom = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Kminus Invariant Mass Combination LooseRB", 200, 0.95, 1.21);
   KpKmLooseRBZoom->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   KpKmLooseRBZoom->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for p+ and K- Combination LooseRB
   PKmLooseRB = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kminus Invariant Mass Combination LooseRB", 200, 2, 3.5);
   PKmLooseRB->GetXaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
   PKmLooseRB->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for p+ and K+ Combination LooseRB (Not Used for Dalitz Plot)
   PKpLooseRB = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kplus Invariant Mass Combination LooseRB", 200, 2, 3.5);
   PKpLooseRB->GetXaxis()->SetTitle("m^{2}(pK^{+})[GeV^{2}/c^{4}]");
   PKpLooseRB->GetYaxis()->SetTitle("Events");

   //Dalitz Plot TightLB
   DPTightLB = new TH2D("Dalitz Plot", "Dalitz Plot of Lc->pKK Decay - TightLB", 200, 0.8, 2.2, 200, 1.7, 3.7);
   DPTightLB->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   DPTightLB->GetYaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
   DPTightLB->GetZaxis()->SetTitle("Events");
   //Plot of M^2 Variable for K+ and K- Combination TightLB
   KpKmTightLB = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Kminus Invariant Mass Combination TightLB", 200, 0.95, 2);
   KpKmTightLB->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   KpKmTightLB->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for K+ and K- Combination TightLB Zoomed into Resonance
   KpKmTightLBZoom = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Kminus Invariant Mass Combination TightLB", 200, 0.95, 1.21);
   KpKmTightLBZoom->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   KpKmTightLBZoom->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for p+ and K- Combination TightLB
   PKmTightLB = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kminus Invariant Mass Combination TightLB", 200, 2, 3.5);
   PKmTightLB->GetXaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
   PKmTightLB->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for p+ and K+ Combination TightLB (Not Used for Dalitz Plot)
   PKpTightLB = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kplus Invariant Mass Combination TightLB", 200, 2, 3.5);
   PKpTightLB->GetXaxis()->SetTitle("m^{2}(pK^{+})[GeV^{2}/c^{4}]");
   PKpTightLB->GetYaxis()->SetTitle("Events");

   //Dalitz Plot TightSig
   DPTightSig = new TH2D("Dalitz Plot", "Dalitz Plot of Lc->pKK Decay - TightSig", 200, 0.8, 2.2, 200, 1.7, 3.7);
   DPTightSig->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   DPTightSig->GetYaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
   DPTightSig->GetZaxis()->SetTitle("Events");
   //Plot of M^2 Variable for K+ and K- Combination TightSig
   KpKmTightSig = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Kminus Invariant Mass Combination TightSig", 200, 0.95, 2);
   KpKmTightSig->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   KpKmTightSig->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for K+ and K- Combination TightSig Zoomed into Resonance
   KpKmTightSigZoom = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Kminus Invariant Mass Combination TightSig", 200, 0.95, 1.21);
   KpKmTightSigZoom->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   KpKmTightSigZoom->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for p+ and K- Combination TightSig
   PKmTightSig = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kminus Invariant Mass Combination TightSig", 200, 2, 3.5);
   PKmTightSig->GetXaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
   PKmTightSig->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for p+ and K+ Combination TightSig (Not Used for Dalitz Plot)
   PKpTightSig = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kplus Invariant Mass Combination TightSig", 200, 2, 3.5);
   PKpTightSig->GetXaxis()->SetTitle("m^{2}(pK^{+})[GeV^{2}/c^{4}]");
   PKpTightSig->GetYaxis()->SetTitle("Events");

   //Dalitz Plot TightRB
   DPTightRB = new TH2D("Dalitz Plot", "Dalitz Plot of Lc->pKK Decay - TightRB", 200, 0.8, 2.2, 200, 1.7, 3.7);
   DPTightRB->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   DPTightRB->GetYaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
   DPTightRB->GetZaxis()->SetTitle("Events");
   //Plot of M^2 Variable for K+ and K- Combination TightRB
   KpKmTightRB = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Kminus Invariant Mass Combination TightRB", 200, 0.95, 2);
   KpKmTightRB->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   KpKmTightRB->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for K+ and K- Combination TightRB Zoomed into Resonance
   KpKmTightRBZoom = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Kminus Invariant Mass Combination TightRB", 200, 0.95, 1.21);
   KpKmTightRBZoom->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
   KpKmTightRBZoom->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for p+ and K- Combination TightRB
   PKmTightRB = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kminus Invariant Mass Combination TightRB", 200, 2, 3.5);
   PKmTightRB->GetXaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
   PKmTightRB->GetYaxis()->SetTitle("Events");
   //Plot of M^2 Variable for p+ and K+ Combination TightRB (Not Used for Dalitz Plot)
   PKpTightRB = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kplus Invariant Mass Combination TightRB", 200, 2, 3.5);
   PKpTightRB->GetXaxis()->SetTitle("m^{2}(pK^{+})[GeV^{2}/c^{4}]");
   PKpTightRB->GetYaxis()->SetTitle("Events");

///////////////////////////////////////////////////////////////////////////////////////////////

   MHistLoose = new TH1D("Mass [MeV]", "Lc Mass - PID Cuts", 300, 2210, 2360);
   MHistLoose->GetXaxis()->SetTitle("MeV");
   MHistLoose->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   MHistTight = new TH1D("Mass [MeV]", "Lc Mass - PID Cuts", 300, 2210, 2360);
   MHistTight->GetXaxis()->SetTitle("MeV");
   MHistTight->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   MHistDalitzLoose = new TH1D("Mass [MeV]", "Lc Mass - PID Cuts & Phi Resonance", 300, 2210, 2360);
   MHistDalitzLoose->GetXaxis()->SetTitle("MeV");
   MHistDalitzLoose->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   MHistDalitzTight = new TH1D("Mass [MeV]", "Lc Mass - PID Cuts & Phi Resonance", 300, 2210, 2360);
   MHistDalitzTight->GetXaxis()->SetTitle("MeV");
   MHistDalitzTight->GetYaxis()->SetTitle("Events Per 1/2 MeV");

    File = new TFile("DalitzAnalysis.root", "RECREATE");
  gFile = File;


   c1 = new TCanvas("canvas", "Test Canvas");
   ex1 = new TCanvas("ex1","Latex",500,600);
}

void DalitzPlot::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
}

Bool_t DalitzPlot::Process(Long64_t entry)
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

bool DalitzCut = (
     (M2_KpKm > 1.024)
  && (M2_KpKm < 1.057)
   );

   bool LBCut = (
        (*Lcplus_M > 2220)
    &&  (*Lcplus_M < 2246)
   );

bool SigCut = (
     (*Lcplus_M > 2274)
 &&  (*Lcplus_M < 2300)
);

bool RBCut = (
     (*Lcplus_M > 2328)
 &&  (*Lcplus_M < 2354)
);

bool  PIDCutLoose = (
        ((*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp) > 0.65)
     && ((*Kminus_ProbNNk)*(*Kplus_ProbNNk) > 0.75)
   );

   bool  PIDCutTight = (
        ((*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp) > 0.8)
     && ((*Kminus_ProbNNk)*(*Kplus_ProbNNk) > 0.9)
      );
   
   bool IPCHI2Cut = (
      ((TMath::Log10(*Proton_IPCHI2_OWNPV) < 3.))
   && ((TMath::Log10(*Kminus_IPCHI2_OWNPV) < 3.))
   && ((TMath::Log10(*Kplus_IPCHI2_OWNPV) < 3.))
       );
       
   bool PTCut = (
      (*Proton_PT > 800)
   );  
      

if (PIDCutLoose){
MHistLoose->Fill(*Lcplus_M);
}

if (PIDCutTight){
MHistTight->Fill(*Lcplus_M);
}

if (PIDCutLoose && DalitzCut){
MHistDalitzLoose->Fill(*Lcplus_M);
}

if (PIDCutTight && DalitzCut){
MHistDalitzTight->Fill(*Lcplus_M);
}

if (PIDCutLoose && LBCut){
  DPLooseLB->Fill(M2_KpKm, M2_PKm);
  KpKmLooseLB->Fill(M2_KpKm);
  PKmLooseLB->Fill(M2_PKm);
  PKpLooseLB->Fill(M2_PKp);
  KpKmLooseLBZoom->Fill(M2_KpKm);
}

if (PIDCutLoose && SigCut){
  DPLooseSig->Fill(M2_KpKm, M2_PKm);
  KpKmLooseSig->Fill(M2_KpKm);
  PKmLooseSig->Fill(M2_PKm);
  PKpLooseSig->Fill(M2_PKp);
  KpKmLooseSigZoom->Fill(M2_KpKm);
}

if (PIDCutLoose && RBCut){
  DPLooseRB->Fill(M2_KpKm, M2_PKm);
  KpKmLooseRB->Fill(M2_KpKm);
  PKmLooseRB->Fill(M2_PKm);
  PKpLooseRB->Fill(M2_PKp);
  KpKmLooseRBZoom->Fill(M2_KpKm);
}

if (PIDCutTight && LBCut){
  DPTightLB->Fill(M2_KpKm, M2_PKm);
  KpKmTightLB->Fill(M2_KpKm);
  PKmTightLB->Fill(M2_PKm);
  PKpTightLB->Fill(M2_PKp);
  KpKmTightLBZoom->Fill(M2_KpKm);
}

if (PIDCutTight && SigCut){
  DPTightSig->Fill(M2_KpKm, M2_PKm);
  KpKmTightSig->Fill(M2_KpKm);
  PKmTightSig->Fill(M2_PKm);
  PKpTightSig->Fill(M2_PKp);
  KpKmTightSigZoom->Fill(M2_KpKm);
}

if (PIDCutTight && RBCut){
  DPTightRB->Fill(M2_KpKm, M2_PKm);
  KpKmTightRB->Fill(M2_KpKm);
  PKmTightRB->Fill(M2_PKm);
  PKpTightRB->Fill(M2_PKp);
  KpKmTightRBZoom->Fill(M2_KpKm);
}

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

DPLooseLB->Draw("COLZ");
 c1->Write("Dalitz Plot - LooseLB");
 DPLooseSig->Draw("COLZ");
  c1->Write("Dalitz Plot - LooseSig");
  DPLooseRB->Draw("COLZ");
   c1->Write("Dalitz Plot - LooseRB");
   DPTightLB->Draw("COLZ");
    c1->Write("Dalitz Plot - TightLB");
    DPTightSig->Draw("COLZ");
     c1->Write("Dalitz Plot - TightSig");
     DPTightRB->Draw("COLZ");
      c1->Write("Dalitz Plot - TightRB");


 //Creates Histograms for M^2 Variables
KpKmLooseLB->Draw();
 c1->Write("Kp & Km - LooseLB");
 KpKmLooseLBZoom->Draw();
  c1->Write("Kp & Km - LooseLBZoom");
 PKmLooseLB->Draw();
 c1->Write("P & Km - LooseLB");
 PKpLooseLB->Draw();
 c1->Write("P & Kp - LooseLB");

 KpKmLooseSig->Draw();
  c1->Write("Kp & Km - LooseSig");
  KpKmLooseSigZoom->Draw();
   c1->Write("Kp & Km - LooseSigZoom");
  PKmLooseSig->Draw();
  c1->Write("P & Km - LooseSig");
  PKpLooseSig->Draw();
  c1->Write("P & Kp - LooseSig");

  KpKmLooseRB->Draw();
   c1->Write("Kp & Km - LooseRB");
   KpKmLooseRBZoom->Draw();
    c1->Write("Kp & Km - LooseRBZoom");
   PKmLooseRB->Draw();
   c1->Write("P & Km - LooseRB");
   PKpLooseRB->Draw();
   c1->Write("P & Kp - LooseRB");

   KpKmTightLB->Draw();
    c1->Write("Kp & Km - TightLB");
    KpKmTightLBZoom->Draw();
     c1->Write("Kp & Km - TightLBZoom");
    PKmTightLB->Draw();
    c1->Write("P & Km - TightLB");
    PKpTightLB->Draw();
    c1->Write("P & Kp - TightLB");

    KpKmTightSig->Draw();
     c1->Write("Kp & Km - TightSig");
     KpKmTightSigZoom->Draw();
      c1->Write("Kp & Km - TightSigZoom");
     PKmTightSig->Draw();
     c1->Write("P & Km - TightSig");
     PKpTightSig->Draw();
     c1->Write("P & Kp - TightSig");

     KpKmTightRB->Draw();
      c1->Write("Kp & Km - TightRB");
      KpKmTightRBZoom->Draw();
       c1->Write("Kp & Km - TightRBZoom");
      PKmTightRB->Draw();
      c1->Write("P & Km - TightRB");
      PKpTightRB->Draw();
      c1->Write("P & Kp - TightRB");

////////////////////////////////////////////////////////////

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

  TF1 *GaussianLoose = new TF1("GaussianLoose",DGOneMuOneTotalHalfMeV,2200.,2400.,7);
  GaussianLoose->SetParameter(0, 0.6);
  GaussianLoose->SetParLimits(0, 0., 1.);
  GaussianLoose->SetParameter(1, 20000);
  GaussianLoose->SetParameter(2, 2287.);
  GaussianLoose->SetParameter(3, 5);
  GaussianLoose->SetParameter(4, 5);
  GaussianLoose->SetParLimits(3, 0., 15.);
  GaussianLoose->SetParLimits(4, 0., 15.);
  GaussianLoose->SetParameter(5, 0.);
  GaussianLoose->SetParameter(6, 0.);

  pad1->cd();
  MHistLoose->SetMinimum(0);
  MHistLoose->Fit("GaussianLoose");

  double PullxLoose[300];
  int BinHeightLoose[300];
  int FitHeightLoose[300];
  double PullLoose[300];

  double Loosecount1 = 0;
  double Loosecount2 = 0;
  double Loosecount3 = 0;

  for (int bin = 0; bin < 300; bin++){
  BinHeightLoose[bin] = MHistLoose->GetBinContent(bin + 1);
  PullxLoose[bin] = (bin + 1);
  int xvalue = 2210.25 + 0.5*(bin);
  FitHeightLoose[bin] = round(GaussianLoose->Eval(xvalue));
  PullLoose[bin] = (BinHeightLoose[bin] - FitHeightLoose[bin])/TMath::Sqrt(FitHeightLoose[bin]);

  if (PullLoose[bin] > -1 && PullLoose[bin] < 1){
    Loosecount1 += 1;
  }

  if (PullLoose[bin] > -2 && PullLoose[bin] < 2){
    Loosecount2 += 1;
  }

  if (PullLoose[bin] > -3 && PullLoose[bin] < 3){
    Loosecount3 += 1;
  }
  }

  pad2->cd();
  TGraph* PullLoosePlot = new TGraph(300, PullxLoose, PullLoose);
  PullLoosePlot->GetXaxis()->SetLimits(0.5,300.5);
  PullLoosePlot->GetXaxis()->SetTickLength(0.);
  PullLoosePlot->GetYaxis()->SetTickLength(0.);
  PullLoosePlot->SetFillColor(38);
  PullLoosePlot->GetYaxis()->SetTitle("Pull");
  PullLoosePlot->GetYaxis()->CenterTitle();
  PullLoosePlot->GetYaxis()->SetTitleSize(0.10);
  PullLoosePlot->GetYaxis()->SetTitleOffset(0.2);
  PullLoosePlot->GetXaxis()->SetLabelSize(0);
  PullLoosePlot->GetYaxis()->SetLabelFont(42);
  PullLoosePlot->GetYaxis()->SetLabelSize(0.06);
  PullLoosePlot->SetTitle("");
  PullLoosePlot->SetMinimum(-5);
  PullLoosePlot->SetMaximum(5);
  PullLoosePlot->Draw("AB");
        c1->Write("Lc Mass - Loose");

  ex1->cd();
   ex1->Clear();
     TLatex Tl;
     Tl.SetTextAlign(12);
     Tl.SetTextSize(0.04);
     Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianLoose->GetParameter(1)));
     Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianLoose->GetParError(1)));
     Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianLoose->GetParameter(0)));
     Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianLoose->GetParError(0)));
     Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianLoose->GetParameter(2)));
     Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianLoose->GetParError(2)));
     Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianLoose->GetParameter(3)));
     Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianLoose->GetParError(3)));
     Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianLoose->GetParameter(4)));
     Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianLoose->GetParError(4)));
     Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", Loosecount1));
     Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", Loosecount2));
     Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", Loosecount3));

     ex1->Write("Fit Values - Loose");

     TF1 *GaussianTight = new TF1("GaussianTight",DGOneMuOneTotalHalfMeV,2200.,2400.,7);
     GaussianTight->SetParameter(0, 0.6);
     GaussianTight->SetParLimits(0, 0., 1.);
     GaussianTight->SetParameter(1, 20000);
     GaussianTight->SetParameter(2, 2287.);
     GaussianTight->SetParameter(3, 5);
     GaussianTight->SetParameter(4, 5);
     GaussianTight->SetParLimits(3, 0., 15.);
     GaussianTight->SetParLimits(4, 0., 15.);
     GaussianTight->SetParameter(5, 0.);
     GaussianTight->SetParameter(6, 0.);

     pad1->cd();
     MHistTight->SetMinimum(0);
     MHistTight->Fit("GaussianTight");

     double PullxTight[300];
     int BinHeightTight[300];
     int FitHeightTight[300];
     double PullTight[300];

     double Tightcount1 = 0;
     double Tightcount2 = 0;
     double Tightcount3 = 0;

     for (int bin = 0; bin < 300; bin++){
     BinHeightTight[bin] = MHistTight->GetBinContent(bin + 1);
     PullxTight[bin] = (bin + 1);
     int xvalue = 2210.25 + 0.5*(bin);
     FitHeightTight[bin] = round(GaussianTight->Eval(xvalue));
     PullTight[bin] = (BinHeightTight[bin] - FitHeightTight[bin])/TMath::Sqrt(FitHeightTight[bin]);

     if (PullTight[bin] > -1 && PullTight[bin] < 1){
       Tightcount1 += 1;
     }

     if (PullTight[bin] > -2 && PullTight[bin] < 2){
       Tightcount2 += 1;
     }

     if (PullTight[bin] > -3 && PullTight[bin] < 3){
       Tightcount3 += 1;
     }
     }

     pad2->cd();
     TGraph* PullTightPlot = new TGraph(300, PullxTight, PullTight);
     PullTightPlot->GetXaxis()->SetLimits(0.5,300.5);
     PullTightPlot->GetXaxis()->SetTickLength(0.);
     PullTightPlot->GetYaxis()->SetTickLength(0.);
     PullTightPlot->SetFillColor(38);
     PullTightPlot->GetYaxis()->SetTitle("Pull");
     PullTightPlot->GetYaxis()->CenterTitle();
     PullTightPlot->GetYaxis()->SetTitleSize(0.10);
     PullTightPlot->GetYaxis()->SetTitleOffset(0.2);
     PullTightPlot->GetXaxis()->SetLabelSize(0);
     PullTightPlot->GetYaxis()->SetLabelFont(42);
     PullTightPlot->GetYaxis()->SetLabelSize(0.06);
     PullTightPlot->SetTitle("");
     PullTightPlot->SetMinimum(-5);
     PullTightPlot->SetMaximum(5);
     PullTightPlot->Draw("AB");
           c1->Write("Lc Mass - Tight");

     ex1->cd();
      ex1->Clear();
        Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianTight->GetParameter(1)));
        Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianTight->GetParError(1)));
        Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianTight->GetParameter(0)));
        Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianTight->GetParError(0)));
        Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianTight->GetParameter(2)));
        Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianTight->GetParError(2)));
        Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianTight->GetParameter(3)));
        Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianTight->GetParError(3)));
        Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianTight->GetParameter(4)));
        Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianTight->GetParError(4)));
        Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", Tightcount1));
        Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", Tightcount2));
        Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", Tightcount3));

        ex1->Write("Fit Values - Tight");

        TF1 *GaussianDalitzLoose = new TF1("GaussianDalitzLoose",DGOneMuOneTotalHalfMeV,2200.,2400.,7);
        GaussianDalitzLoose->SetParameter(0, 0.6);
        GaussianDalitzLoose->SetParLimits(0, 0., 1.);
        GaussianDalitzLoose->SetParameter(1, 20000);
        GaussianDalitzLoose->SetParameter(2, 2287.);
        GaussianDalitzLoose->SetParameter(3, 5);
        GaussianDalitzLoose->SetParameter(4, 5);
        GaussianDalitzLoose->SetParLimits(3, 0., 15.);
        GaussianDalitzLoose->SetParLimits(4, 0., 15.);
        GaussianDalitzLoose->SetParameter(5, 0.);
        GaussianDalitzLoose->SetParameter(6, 0.);

        pad1->cd();
        MHistDalitzLoose->SetMinimum(0);
        MHistDalitzLoose->Fit("GaussianDalitzLoose");

        double PullxDalitzLoose[300];
        int BinHeightDalitzLoose[300];
        int FitHeightDalitzLoose[300];
        double PullDalitzLoose[300];

        double DalitzLoosecount1 = 0;
        double DalitzLoosecount2 = 0;
        double DalitzLoosecount3 = 0;

        for (int bin = 0; bin < 300; bin++){
        BinHeightDalitzLoose[bin] = MHistDalitzLoose->GetBinContent(bin + 1);
        PullxDalitzLoose[bin] = (bin + 1);
        int xvalue = 2210.25 + 0.5*(bin);
        FitHeightDalitzLoose[bin] = round(GaussianDalitzLoose->Eval(xvalue));
        PullDalitzLoose[bin] = (BinHeightDalitzLoose[bin] - FitHeightDalitzLoose[bin])/TMath::Sqrt(FitHeightDalitzLoose[bin]);

        if (PullDalitzLoose[bin] > -1 && PullDalitzLoose[bin] < 1){
          DalitzLoosecount1 += 1;
        }

        if (PullDalitzLoose[bin] > -2 && PullDalitzLoose[bin] < 2){
          DalitzLoosecount2 += 1;
        }

        if (PullDalitzLoose[bin] > -3 && PullDalitzLoose[bin] < 3){
          DalitzLoosecount3 += 1;
        }
        }

        pad2->cd();
        TGraph* PullDalitzLoosePlot = new TGraph(300, PullxDalitzLoose, PullDalitzLoose);
        PullDalitzLoosePlot->GetXaxis()->SetLimits(0.5,300.5);
        PullDalitzLoosePlot->GetXaxis()->SetTickLength(0.);
        PullDalitzLoosePlot->GetYaxis()->SetTickLength(0.);
        PullDalitzLoosePlot->SetFillColor(38);
        PullDalitzLoosePlot->GetYaxis()->SetTitle("Pull");
        PullDalitzLoosePlot->GetYaxis()->CenterTitle();
        PullDalitzLoosePlot->GetYaxis()->SetTitleSize(0.10);
        PullDalitzLoosePlot->GetYaxis()->SetTitleOffset(0.2);
        PullDalitzLoosePlot->GetXaxis()->SetLabelSize(0);
        PullDalitzLoosePlot->GetYaxis()->SetLabelFont(42);
        PullDalitzLoosePlot->GetYaxis()->SetLabelSize(0.06);
        PullDalitzLoosePlot->SetTitle("");
        PullDalitzLoosePlot->SetMinimum(-5);
        PullDalitzLoosePlot->SetMaximum(5);
        PullDalitzLoosePlot->Draw("AB");
              c1->Write("Lc Mass - DalitzLoose");

        ex1->cd();
         ex1->Clear();
           Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianDalitzLoose->GetParameter(1)));
           Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianDalitzLoose->GetParError(1)));
           Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianDalitzLoose->GetParameter(0)));
           Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianDalitzLoose->GetParError(0)));
           Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianDalitzLoose->GetParameter(2)));
           Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianDalitzLoose->GetParError(2)));
           Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianDalitzLoose->GetParameter(3)));
           Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianDalitzLoose->GetParError(3)));
           Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianDalitzLoose->GetParameter(4)));
           Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianDalitzLoose->GetParError(4)));
           Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", DalitzLoosecount1));
           Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", DalitzLoosecount2));
           Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", DalitzLoosecount3));

           ex1->Write("Fit Values - DalitzLoose");

           TF1 *GaussianDalitzTight = new TF1("GaussianDalitzTight",DGOneMuOneTotalHalfMeV,2200.,2400.,7);
           GaussianDalitzTight->SetParameter(0, 0.6);
           GaussianDalitzTight->SetParLimits(0, 0., 1.);
           GaussianDalitzTight->SetParameter(1, 20000);
           GaussianDalitzTight->SetParameter(2, 2287.);
           GaussianDalitzTight->SetParameter(3, 5);
           GaussianDalitzTight->SetParameter(4, 5);
           GaussianDalitzTight->SetParLimits(3, 0., 15.);
           GaussianDalitzTight->SetParLimits(4, 0., 15.);
           GaussianDalitzTight->SetParameter(5, 0.);
           GaussianDalitzTight->SetParameter(6, 0.);

           pad1->cd();
           MHistDalitzTight->SetMinimum(0);
           MHistDalitzTight->Fit("GaussianDalitzTight");

           double PullxDalitzTight[300];
           int BinHeightDalitzTight[300];
           int FitHeightDalitzTight[300];
           double PullDalitzTight[300];

           double DalitzTightcount1 = 0;
           double DalitzTightcount2 = 0;
           double DalitzTightcount3 = 0;

           for (int bin = 0; bin < 300; bin++){
           BinHeightDalitzTight[bin] = MHistDalitzTight->GetBinContent(bin + 1);
           PullxDalitzTight[bin] = (bin + 1);
           int xvalue = 2210.25 + 0.5*(bin);
           FitHeightDalitzTight[bin] = round(GaussianDalitzTight->Eval(xvalue));
           PullDalitzTight[bin] = (BinHeightDalitzTight[bin] - FitHeightDalitzTight[bin])/TMath::Sqrt(FitHeightDalitzTight[bin]);

           if (PullDalitzTight[bin] > -1 && PullDalitzTight[bin] < 1){
             DalitzTightcount1 += 1;
           }

           if (PullDalitzTight[bin] > -2 && PullDalitzTight[bin] < 2){
             DalitzTightcount2 += 1;
           }

           if (PullDalitzTight[bin] > -3 && PullDalitzTight[bin] < 3){
             DalitzTightcount3 += 1;
           }
           }

           pad2->cd();
           TGraph* PullDalitzTightPlot = new TGraph(300, PullxDalitzTight, PullDalitzTight);
           PullDalitzTightPlot->GetXaxis()->SetLimits(0.5,300.5);
           PullDalitzTightPlot->GetXaxis()->SetTickLength(0.);
           PullDalitzTightPlot->GetYaxis()->SetTickLength(0.);
           PullDalitzTightPlot->SetFillColor(38);
           PullDalitzTightPlot->GetYaxis()->SetTitle("Pull");
           PullDalitzTightPlot->GetYaxis()->CenterTitle();
           PullDalitzTightPlot->GetYaxis()->SetTitleSize(0.10);
           PullDalitzTightPlot->GetYaxis()->SetTitleOffset(0.2);
           PullDalitzTightPlot->GetXaxis()->SetLabelSize(0);
           PullDalitzTightPlot->GetYaxis()->SetLabelFont(42);
           PullDalitzTightPlot->GetYaxis()->SetLabelSize(0.06);
           PullDalitzTightPlot->SetTitle("");
           PullDalitzTightPlot->SetMinimum(-5);
           PullDalitzTightPlot->SetMaximum(5);
           PullDalitzTightPlot->Draw("AB");
                 c1->Write("Lc Mass - DalitzTight");

           ex1->cd();
            ex1->Clear();
              Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianDalitzTight->GetParameter(1)));
              Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianDalitzTight->GetParError(1)));
              Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianDalitzTight->GetParameter(0)));
              Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianDalitzTight->GetParError(0)));
              Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianDalitzTight->GetParameter(2)));
              Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianDalitzTight->GetParError(2)));
              Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianDalitzTight->GetParameter(3)));
              Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianDalitzTight->GetParError(3)));
              Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianDalitzTight->GetParameter(4)));
              Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianDalitzTight->GetParError(4)));
              Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", DalitzTightcount1));
              Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", DalitzTightcount2));
              Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", DalitzTightcount3));

              ex1->Write("Fit Values - DalitzTight");                   

File->Close();
}
