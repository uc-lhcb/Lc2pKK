// Relax Tau and IPCHI2 of Lc
// Lower Tau Should have Lower IPCHI2
// Higher Tau Should have Higher IPCHI2B
// Create S/B Plot over large 2D parameter space

#define TauIPChi2SB_cxx
#include "TauIPChi2SB.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

#include "DGOneMuOneTotalHalfMeV.C"

TH1D * FinalMass = nullptr;

TH1D * IPCHI2Signal = nullptr;
TH1D * IPCHI2Background = nullptr;
TH1D * IPCHI2SignalEstimate = nullptr;
TH1D * TAUSignal = nullptr;
TH1D * TAUBackground = nullptr;
TH1D * TAUSignalEstimate = nullptr;

TH2D * TAULcIPEvents = nullptr;
TH2D * TAULcIPSignal = nullptr;
TH2D * TAULcIPSignalEstimate = nullptr;
TH2D * TAULcIPBackground = nullptr;
TH2D * TAULcIPBackgroundSqrt = nullptr;

TFile * File = nullptr;
TCanvas * c1 = nullptr;

void TauIPChi2SB::Begin(TTree * /*tree*/)
{

   TString option = GetOption();
}

void TauIPChi2SB::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

   FinalMass = new TH1D("", "", 260, 2222, 2352);
   FinalMass->GetXaxis()->SetTitle("MeV(p^{+}K^{+}K^{-})");
   FinalMass->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   IPCHI2Signal= new TH1D("", "Signal Region", 100, 0., 1.2);
   IPCHI2Background = new TH1D("", "Background Region", 100, 0., 1.2);
   IPCHI2SignalEstimate = new TH1D("", "Signal Estimate", 100, 0., 1.2);
   IPCHI2Signal->SetLineColor(kBlue);
   IPCHI2Background->SetLineColor(kRed);
   IPCHI2SignalEstimate->SetLineColor(kGreen+3);

   TAUSignal= new TH1D("", "Signal Region", 100, 0.0003, 0.002);
   TAUBackground = new TH1D("", "Background Region", 100, 0.0003, 0.002);
   TAUSignalEstimate = new TH1D("", "Signal Estimate", 100, 0.0003, 0.002);
   TAUSignal->SetLineColor(kBlue);
   TAUBackground->SetLineColor(kRed);
   TAUSignalEstimate->SetLineColor(kGreen+3);

   TAULcIPEvents = new TH2D("", "", 100, 0.0003, 0.002, 100, 0., 1.2);
   TAULcIPEvents->GetZaxis()->SetTitle("Events");

   TAULcIPSignal = new TH2D("", "", 100, 0.0003, 0.002, 100, 0., 1.2);
   TAULcIPSignal->GetZaxis()->SetTitle("Events");

   TAULcIPBackground = new TH2D("", "", 100, 0.0003, 0.002, 100, 0., 1.2);
   TAULcIPBackground->GetZaxis()->SetTitle("Events");

   TAULcIPSignalEstimate = new TH2D("", "", 100, 0.0003, 0.002, 100, 0., 1.2);
   TAULcIPSignalEstimate->GetZaxis()->SetTitle("Events");

   File = new TFile("TrackCuts.root", "RECREATE");
   gFile = File;

    c1 = new TCanvas("canvas", "Test Canvas");

}

Bool_t TauIPChi2SB::Process(Long64_t entry)
{
  GetEntry(entry);
  fReader.SetLocalEntry(entry);

  TLorentzVector P_vec(*Proton_PX, *Proton_PY, *Proton_PZ, *Proton_PE);
  TLorentzVector Kp_vec(*Kplus_PX, *Kplus_PY, *Kplus_PZ, *Kplus_PE);
  TLorentzVector Km_vec(*Kminus_PX, *Kminus_PY, *Kminus_PZ, *Kminus_PE);
  TLorentzVector LcVec;

  TLorentzVector PKp_vec;
  TLorentzVector PKm_vec;
  TLorentzVector KpKm_vec;

  PKp_vec = P_vec+Kp_vec;
  PKm_vec = P_vec+Km_vec;
  KpKm_vec = Kp_vec+Km_vec;

  double M2_PKp = PKp_vec.Mag2()/(1000*1000);
  double M2_PKm  = PKm_vec.Mag2()/(1000*1000);
  double M2_KpKm = KpKm_vec.Mag2()/(1000*1000);

double prodProbNNx = (*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp);
double DalitzLow = (1.019455-0.012)*(1.019455-0.012);
double DalitzHigh = (1.019455+0.012)*(1.019455+0.012);

  bool  PIDBSubbedCuts= (
       (prodProbNNx > 0.8)
    && (*Proton_ProbNNp > 0.9)
        );

  bool DalitzCuts= (
    M2_KpKm > DalitzLow
&&  M2_KpKm < DalitzHigh
  );

 bool MomentumCut= (
   (*Lc_P < 110000)
 );

bool TauIPCut= (
  ((1/0.9)*(1/0.9)*TMath::Log10(*Lc_IPCHI2_OWNPV)*TMath::Log10(*Lc_IPCHI2_OWNPV) + (1/0.0010)*(1/0.0010)*(*Lc_TAU - 0.0003)*(*Lc_TAU - 0.0003)) < 1
);

 bool SignalRegion = *Lc_M > 2275.4 && *Lc_M < 2299.4;
 bool BackgroundRegion = (*Lc_M > 2222. && *Lc_M < 2270.) || (*Lc_M > 2304. && *Lc_M < 2352.);

 if(PIDBSubbedCuts && DalitzCuts && MomentumCut){
TAULcIPEvents->Fill(*Lc_TAU, TMath::Log10(*Lc_IPCHI2_OWNPV));

 if(SignalRegion){
   IPCHI2Signal->Fill(TMath::Log10(*Lc_IPCHI2_OWNPV));
   TAUSignal->Fill(*Lc_TAU);
   TAULcIPSignal->Fill(*Lc_TAU, TMath::Log10(*Lc_IPCHI2_OWNPV));
 }

 if(BackgroundRegion){
   IPCHI2Background->Fill(TMath::Log10(*Lc_IPCHI2_OWNPV));
   TAUBackground->Fill(*Lc_TAU);
   TAULcIPBackground->Fill(*Lc_TAU, TMath::Log10(*Lc_IPCHI2_OWNPV));
 }

if (TauIPCut){
FinalMass->Fill(*Lc_M);
}
 }



   return kTRUE;
}

void TauIPChi2SB::SlaveTerminate()
{
}

void TauIPChi2SB::Terminate()
{
    gStyle->SetOptStat(11);
    c1->SetBottomMargin(0.2);
    c1->SetLeftMargin(0.15);
    auto lt = new TLatex();
    lt->SetTextSize(0.04);

  IPCHI2SignalEstimate->Add(IPCHI2Signal,IPCHI2Background,1.0,-0.25);
  TAUSignalEstimate->Add(TAUSignal,TAUBackground,1.0,-0.25);
  TAULcIPSignalEstimate->Add(TAULcIPSignal,TAULcIPBackground,1.0,-0.25);

  FinalMass->SetMinimum(0.0001);
  FinalMass->GetXaxis()->CenterTitle(true);
  FinalMass->GetXaxis()->SetTitleSize(20);
  FinalMass->GetXaxis()->SetTitleFont(43);
  FinalMass->GetXaxis()->SetTitleOffset(1.5);
  FinalMass->GetXaxis()->SetLabelSize(0.05);
  FinalMass->GetYaxis()->SetTitleSize(20);
  FinalMass->GetYaxis()->SetTitleFont(43);
  FinalMass->GetYaxis()->SetLabelSize(0.05);
  FinalMass->Draw();
  c1->SaveAs("LcMTauIPCHI.pdf");

  gStyle->SetOptStat(0);

  IPCHI2Signal->GetYaxis()->SetTitle("Events per 0.025 Bin Width");
  IPCHI2Signal->GetXaxis()->SetTitle("#chi^{2}_{IP} on Log10 Scale");
  IPCHI2Signal->SetMinimum(0);
  IPCHI2Signal->GetXaxis()->CenterTitle(true);
  IPCHI2Signal->GetXaxis()->SetTitleSize(20);
  IPCHI2Signal->GetXaxis()->SetTitleFont(43);
  IPCHI2Signal->GetXaxis()->SetTitleOffset(1.5);
  IPCHI2Signal->GetXaxis()->SetLabelSize(0.05);
  IPCHI2Signal->GetYaxis()->SetTitleSize(20);
  IPCHI2Signal->GetYaxis()->SetTitleFont(43);
  IPCHI2Signal->GetYaxis()->SetLabelSize(0.05);
  IPCHI2Signal->Draw();
  IPCHI2SignalEstimate->Draw("SAME");
  IPCHI2Background->Draw("SAME");
  gPad->BuildLegend(0.65,0.65,0.85,0.85);
  lt->DrawLatexNDC(0.65, 0.60, "LHCb Preliminary");
  IPCHI2Signal->SetTitle("");
  c1->SaveAs("IPCHI2Bsub.pdf");

  TAUSignal->GetYaxis()->SetTitle("Events per 0.00004 Bin Width");
  TAUSignal->GetXaxis()->SetTitle("#Lambda_{c}_TAU [ns]");
  TAUSignal->SetMinimum(0);
  TAUSignal->GetXaxis()->CenterTitle(true);
  TAUSignal->GetXaxis()->SetTitleSize(20);
  TAUSignal->GetXaxis()->SetTitleFont(43);
  TAUSignal->GetXaxis()->SetTitleOffset(1.5);
  TAUSignal->GetXaxis()->SetLabelSize(0.05);
  TAUSignal->GetYaxis()->SetTitleSize(20);
  TAUSignal->GetYaxis()->SetTitleFont(43);
  TAUSignal->GetYaxis()->SetLabelSize(0.05);
  TAUSignal->GetXaxis()->SetNdivisions(-6);
  TAUSignal->Draw();
  TAUSignalEstimate->Draw("SAME");
  TAUBackground->Draw("SAME");
  gPad->BuildLegend(0.65,0.65,0.85,0.85);
  lt->DrawLatexNDC(0.65, 0.60, "LHCb Preliminary");
  TAUSignal->SetTitle("");
  c1->SaveAs("TAUBsub.pdf");

  c1->SetRightMargin(0.15);

  TAULcIPEvents->GetYaxis()->SetTitle("#chi^{2}_{IP} on Log10 Scale");
  TAULcIPEvents->GetXaxis()->SetTitle("#Lambda_{c}_TAU [ns]");
  TAULcIPEvents->GetXaxis()->CenterTitle(true);
  TAULcIPEvents->GetXaxis()->SetTitleSize(20);
  TAULcIPEvents->GetXaxis()->SetTitleFont(43);
  TAULcIPEvents->GetXaxis()->SetTitleOffset(1.5);
  TAULcIPEvents->GetXaxis()->SetLabelSize(0.05);
  TAULcIPEvents->GetYaxis()->SetTitleSize(20);
  TAULcIPEvents->GetYaxis()->SetTitleFont(43);
  TAULcIPEvents->GetYaxis()->SetLabelSize(0.05);
  TAULcIPEvents->GetXaxis()->SetNdivisions(-6);
  TAULcIPEvents->GetZaxis()->SetTitleOffset(1);
  TAULcIPEvents->SetTitle("Decay-time vs #chi^{2}_{IP} - All Events");
  TAULcIPEvents->Draw("COLZ");
  TF1 *f1 = new TF1("f1","0.9*TMath::Sqrt(1 - (1/0.0010)*(1/0.0010)*(x-0.0003)*(x-0.0003))",0.0003,0.001299);
  f1->SetLineColor(kRed);
  f1->SetLineWidth(3);
  f1->Draw("SAME");
    c1->SaveAs("TauLcIPEvents.pdf");

  TAULcIPSignal->GetYaxis()->SetTitle("#chi^{2}_{IP} on Log10 Scale");
  TAULcIPSignal->GetXaxis()->SetTitle("#Lambda_{c}_TAU [ns]");
  TAULcIPSignal->GetXaxis()->CenterTitle(true);
  TAULcIPSignal->GetXaxis()->SetTitleSize(20);
  TAULcIPSignal->GetXaxis()->SetTitleFont(43);
  TAULcIPSignal->GetXaxis()->SetTitleOffset(1.5);
  TAULcIPSignal->GetXaxis()->SetLabelSize(0.05);
  TAULcIPSignal->GetYaxis()->SetTitleSize(20);
  TAULcIPSignal->GetYaxis()->SetTitleFont(43);
  TAULcIPSignal->GetYaxis()->SetLabelSize(0.05);
  TAULcIPSignal->GetXaxis()->SetNdivisions(-6);
  TAULcIPSignal->GetZaxis()->SetTitleOffset(1);
  TAULcIPSignal->Draw("CONTZ");
    c1->SaveAs("TauLcIPSignal.pdf");

    TAULcIPSignalEstimate->GetYaxis()->SetTitle("#chi^{2}_{IP} on Log10 Scale");
    TAULcIPSignalEstimate->GetXaxis()->SetTitle("#Lambda_{c}_TAU [ns]");
    TAULcIPSignalEstimate->GetXaxis()->CenterTitle(true);
    TAULcIPSignalEstimate->GetXaxis()->SetTitleSize(20);
    TAULcIPSignalEstimate->GetXaxis()->SetTitleFont(43);
    TAULcIPSignalEstimate->GetXaxis()->SetTitleOffset(1.5);
    TAULcIPSignalEstimate->GetXaxis()->SetLabelSize(0.05);
    TAULcIPSignalEstimate->GetYaxis()->SetTitleSize(20);
    TAULcIPSignalEstimate->GetYaxis()->SetTitleFont(43);
    TAULcIPSignalEstimate->GetYaxis()->SetLabelSize(0.05);
    TAULcIPSignalEstimate->GetXaxis()->SetNdivisions(-6);
    TAULcIPSignalEstimate->GetZaxis()->SetTitleOffset(1);
    TAULcIPSignalEstimate->Draw("CONTZ");
      c1->SaveAs("TauLcIPSignalEstimate.pdf");

  TAULcIPBackground->GetYaxis()->SetTitle("#chi^{2}_{IP} on Log10 Scale");
  TAULcIPBackground->GetXaxis()->SetTitle("#Lambda_{c}_TAU [ns]");
  TAULcIPBackground->GetXaxis()->CenterTitle(true);
  TAULcIPBackground->GetXaxis()->SetTitleSize(20);
  TAULcIPBackground->GetXaxis()->SetTitleFont(43);
  TAULcIPBackground->GetXaxis()->SetTitleOffset(1.5);
  TAULcIPBackground->GetXaxis()->SetLabelSize(0.05);
  TAULcIPBackground->GetYaxis()->SetTitleSize(20);
  TAULcIPBackground->GetYaxis()->SetTitleFont(43);
  TAULcIPBackground->GetYaxis()->SetLabelSize(0.05);
  TAULcIPBackground->GetXaxis()->SetNdivisions(-6);
  TAULcIPBackground->GetZaxis()->SetTitleOffset(1);
  TAULcIPBackground->Draw("CONTZ");
    c1->SaveAs("TauLcIPBackground.pdf");

TAULcIPSignalEstimate->Divide(TAULcIPBackground);
TAULcIPSignalEstimate->SetTitle("Decay-time vs #chi^{2}_{IP} - S/B Scatterplot");
TAULcIPSignalEstimate->Draw("CONTZ");
TAULcIPSignalEstimate->GetZaxis()->SetTitle("S/B");
  c1->SaveAs("TauLcIPSB.pdf");
  f1->Draw("SAME");
  c1->SaveAs("TauLcIPSBCut.pdf");

}
