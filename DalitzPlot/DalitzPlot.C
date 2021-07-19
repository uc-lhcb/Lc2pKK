#define DalitzPlot_cxx
#include "DalitzPlot.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>
#include <TLine.h>
#include <TH2.h>
#include <TStyle.h>

#include "DGOneMuOneTotalHalfMeV.C"

TH2D * DalitzPlot1 = nullptr;
TH1D * DalitzSignal = nullptr;
TH1D * DalitzSignalEst = nullptr;
TH1D * DalitzBackground = nullptr;
TH1D * PIDDalitzMass = nullptr;

TCanvas * c1 = nullptr;
TCanvas * c2 = nullptr;

void DalitzPlot::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void DalitzPlot::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();


      DalitzPlot1 = new TH2D("", "", 200, 0.8, 2.2, 200, 1.7, 3.7);
      DalitzPlot1->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+}) [GeV^{2}]");
      DalitzPlot1->GetYaxis()->SetTitle("m^{2}(pK^{-}) [GeV^{2}]");
      DalitzPlot1->GetZaxis()->SetTitle("Entries");
      DalitzSignal = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Signal Region", 120, 0.96, 1.20);
      DalitzSignal->SetLineColor(kBlue);
      DalitzSignalEst = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Signal Estimate", 120, 0.96, 1.20);
      DalitzSignalEst->SetLineColor(kGreen+3);
      DalitzBackground = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Background Region", 120, 0.96, 1.20);
      DalitzBackground->SetLineColor(kRed);

      PIDDalitzMass = new TH1D("", "", 260, 2222, 2352);
      PIDDalitzMass->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
      PIDDalitzMass->GetYaxis()->SetTitle("Entries / (0.5 MeV)");

          c1 = new TCanvas("canvas1", "Test Canvas1");
          c2 = new TCanvas("canvas2", "Test Canvas2");
}

Bool_t DalitzPlot::Process(Long64_t entry)
{
  GetEntry(entry);
  fReader.SetLocalEntry(entry);

  bool MassRange= (
  (*Lc_M > 2222 && *Lc_M < 2352)
  );

  TLorentzVector P_vec(*Proton_PX, *Proton_PY, *Proton_PZ, *Proton_PE);
  TLorentzVector Kp_vec(*Kplus_PX, *Kplus_PY, *Kplus_PZ, *Kplus_PE);
  TLorentzVector Km_vec(*Kminus_PX, *Kminus_PY, *Kminus_PZ, *Kminus_PE);

  TLorentzVector PKp_vec;
  TLorentzVector PKm_vec;
  TLorentzVector KpKm_vec;

  PKp_vec = P_vec+Kp_vec;
  PKm_vec = P_vec+Km_vec;
  KpKm_vec = Kp_vec+Km_vec;

  double M2_PKp = PKp_vec.Mag2()/(1000*1000);
  double M2_PKm  = PKm_vec.Mag2()/(1000*1000);
  double M2_KpKm = KpKm_vec.Mag2()/(1000*1000);

double prodProbNN = (*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp);

  bool  PIDBSubbedCuts= (
       (prodProbNN > 0.8)
    && (*Proton_ProbNNp > 0.9)
        );

 double DalitzLow = (1.019455-0.012)*(1.019455-0.012);
 double DalitzHigh = (1.019455+0.012)*(1.019455+0.012);

  bool DalitzCuts= (
    M2_KpKm > DalitzLow
&&  M2_KpKm < DalitzHigh
  );

bool SignalRegion = *Lc_M > 2274. && *Lc_M < 2300.;
bool BackgroundRegion = (*Lc_M > 2222. && *Lc_M < 2235.) || (*Lc_M > 2339. && *Lc_M < 2352.);

if(PIDBSubbedCuts && MassRange){
DalitzPlot1->Fill(M2_KpKm, M2_PKm);

if(SignalRegion){
  DalitzSignal->Fill(M2_KpKm);
}

if(BackgroundRegion){
  DalitzBackground->Fill(M2_KpKm);
}

if(DalitzCuts){
PIDDalitzMass->Fill(*Lc_M);
}
}

   return kTRUE;
}

void DalitzPlot::SlaveTerminate()
{
}

void DalitzPlot::Terminate()
{

    c1->cd();

DalitzSignalEst->Add(DalitzSignal,DalitzBackground,1.0,-1.0);

gStyle->SetOptStat(11);
c1->SetBottomMargin(0.2);
c1->SetLeftMargin(0.15);
auto lt = new TLatex();
lt->SetTextSize(0.04);
gStyle->SetStatW(0.25);
gStyle->SetStatH(0.25);

PIDDalitzMass->SetMinimum(0.0001);
PIDDalitzMass->GetXaxis()->CenterTitle(true);
PIDDalitzMass->GetXaxis()->SetTitleSize(20);
PIDDalitzMass->GetXaxis()->SetTitleFont(43);
PIDDalitzMass->GetXaxis()->SetTitleOffset(1.5);
PIDDalitzMass->GetXaxis()->SetLabelSize(0.05);
PIDDalitzMass->GetYaxis()->SetTitleSize(20);
PIDDalitzMass->GetYaxis()->SetTitleFont(43);
PIDDalitzMass->GetYaxis()->SetLabelSize(0.05);
PIDDalitzMass->Draw();
PIDDalitzMass->SetLineWidth(2);
lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
c1->SaveAs("LcMPIDDalitz.pdf");

gStyle->SetOptStat(0);
DalitzSignal->GetYaxis()->SetTitle("Entries / (0.002 GeV^{2})");
DalitzSignal->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+}) [GeV^{2}]");
DalitzSignal->SetMinimum(0);
DalitzSignal->GetXaxis()->CenterTitle(true);
DalitzSignal->GetXaxis()->SetTitleSize(20);
DalitzSignal->GetXaxis()->SetTitleFont(43);
DalitzSignal->GetXaxis()->SetTitleOffset(1.5);
DalitzSignal->GetXaxis()->SetLabelSize(0.05);
DalitzSignal->GetYaxis()->SetTitleSize(20);
DalitzSignal->GetYaxis()->SetTitleFont(43);
DalitzSignal->GetYaxis()->SetLabelSize(0.05);
DalitzSignal->Draw();
DalitzSignalEst->Draw("SAME");
DalitzBackground->Draw("SAME");
DalitzSignal->SetLineWidth(3);
DalitzSignalEst->SetLineWidth(3);
DalitzBackground->SetLineWidth(3);
gPad->BuildLegend(0.45,0.65,0.85,0.85);
TLine *line1 = new TLine(1.01496,0,1.01496,15000);
line1->SetLineWidth(2);
line1->Draw();
 TLine *line2 = new TLine(1.0639,0,1.0639,15000);
 line2->SetLineWidth(2);
 line2->Draw();
lt->DrawLatexNDC(0.5, 0.60, "LHCb Preliminary");
DalitzSignal->SetTitle("");
c1->SaveAs("DalitzBsub.pdf");

c1->SetRightMargin(0.2);

DalitzPlot1->Draw("COLZ");
DalitzPlot1->SetMinimum(0);
DalitzPlot1->GetXaxis()->CenterTitle(true);
DalitzPlot1->GetXaxis()->SetTitleSize(20);
DalitzPlot1->GetXaxis()->SetTitleFont(43);
DalitzPlot1->GetXaxis()->SetTitleOffset(1.5);
DalitzPlot1->GetXaxis()->SetLabelSize(0.05);
DalitzPlot1->GetYaxis()->SetTitleSize(20);
DalitzPlot1->GetYaxis()->SetTitleFont(43);
DalitzPlot1->GetYaxis()->SetLabelSize(0.05);
DalitzPlot1->GetZaxis()->SetTitleSize(20);
DalitzPlot1->GetZaxis()->SetTitleFont(43);
DalitzPlot1->GetZaxis()->SetTitleOffset(1.5);
DalitzPlot1->GetZaxis()->SetLabelSize(0.05);
lt->DrawLatexNDC(0.55, 0.80, "LHCb Preliminary");
c1->SaveAs("DalitzPlot.pdf");
}
