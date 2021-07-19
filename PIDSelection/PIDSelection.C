#define PIDSelection_cxx
#include "PIDSelection.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

#include "DGOneMuOneTotalHalfMeV.C"

TH1D * UncutMass = nullptr;

TH1D * PreliminaryMass = nullptr;
TH1D * PreliminaryBackground = nullptr;
TH1D * PreliminaryMid = nullptr;
TH1D * PreliminarySignal = nullptr;

TH1D * PIDBSubedMass = nullptr;
TH1D * ProbNNpVariable = nullptr;
TH1D * ProbNNpCut = nullptr;
TH1D * ProbNNxVariable = nullptr;
TH1D * ProbNNxCut = nullptr;
TH1D * ProbNNSignal = nullptr;
TH1D * ProbNNBackground = nullptr;
TH1D * ProbNNSignalEstimate = nullptr;
TH1D * ProbNNpSignal = nullptr;
TH1D * ProbNNpBackground = nullptr;
TH1D * ProbNNpSignalEstimate = nullptr;

TCanvas * c1 = nullptr;
TCanvas * c2 = nullptr;
TCanvas * grid = nullptr;

void PIDSelection::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void PIDSelection::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

   UncutMass = new TH1D("", "", 260, 2222, 2352);
   UncutMass->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
   UncutMass->GetYaxis()->SetTitle("Entries / (0.5 MeV)");

   PreliminaryMass = new TH1D("", "", 260, 2222, 2352);
   PreliminaryMass->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
   PreliminaryMass->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   PreliminaryBackground = new TH1D("", "", 260, 2222, 2352);
   PreliminaryBackground->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
   PreliminaryBackground->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   PreliminaryBackground->SetFillColor(kRed);
   PreliminarySignal = new TH1D("", "", 260, 2222, 2352);
   PreliminarySignal->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
   PreliminarySignal->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   PreliminarySignal->SetFillColor(kBlue);
   PreliminaryMid = new TH1D("", "", 260, 2222, 2352);
   PreliminaryMid->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
   PreliminaryMid->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   PreliminaryMid->SetFillColor(kYellow);

   PIDBSubedMass = new TH1D("", "", 260, 2222, 2352);
   PIDBSubedMass->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
   PIDBSubedMass->GetYaxis()->SetTitle("Entries / (0.5 MeV)");

   ProbNNSignal= new TH1D("", "Signal Region", 120, 0.3, 1.);
   ProbNNBackground = new TH1D("", "Background Region", 120, 0.3, 1.);
   ProbNNSignalEstimate = new TH1D("", "Signal Estimate", 120, 0.3, 1.);
   ProbNNSignal->SetLineColor(kBlue);
   ProbNNBackground->SetLineColor(kRed);
   ProbNNSignalEstimate->SetLineColor(kGreen+3);

   ProbNNpSignal= new TH1D("", "Signal Region", 80, 0.6, 1.);
   ProbNNpBackground = new TH1D("", "Background Region", 80, 0.6, 1.);
   ProbNNpSignalEstimate = new TH1D("", "Signal Estimate", 80, 0.6, 1.);
   ProbNNpSignal->SetLineColor(kBlue);
   ProbNNpBackground->SetLineColor(kRed);
   ProbNNpSignalEstimate->SetLineColor(kGreen+3);

   ProbNNpVariable= new TH1D("", "", 200, 0., 1.);
   ProbNNpVariable->GetYaxis()->SetTitle("Entries / (0.005 Probability)");
   ProbNNpVariable->GetXaxis()->SetTitle("Proton_ProbNNp");
   ProbNNpCut= new TH1D("", "", 200, 0., 1.);
   ProbNNpCut->SetFillColor(kBlue);
   ProbNNxVariable= new TH1D("", "", 200, 0., 1.);
   ProbNNxVariable->GetYaxis()->SetTitle("Entries / (0.005 Probability)");
   ProbNNxVariable->GetXaxis()->SetTitle("Prod(ProbNNx)");
   ProbNNxCut= new TH1D("", "", 200, 0., 1.);
   ProbNNxCut->SetFillColor(kBlue);

    c1 = new TCanvas("canvas", "Test Canvas");
    c2 = new TCanvas("canvas2", "Test Canvas2");
}

Bool_t PIDSelection::Process(Long64_t entry)
{
  GetEntry(entry);
  fReader.SetLocalEntry(entry);

  bool MassRange= (
  (*Lc_M > 2222 && *Lc_M < 2352)
  );

double prodProbNN = (*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp);

  bool  PreliminaryCuts= (
       (prodProbNN > 0.3)
    && (*Proton_ProbNNp > 0.6)
        );

if(prodProbNN >  0.3 && MassRange){
        ProbNNxCut->Fill(prodProbNN);
}

if(*Proton_ProbNNp >  0.6 && MassRange){
        ProbNNpCut->Fill(*Proton_ProbNNp);
}

        bool  PIDBSubbedCuts= (
             (prodProbNN > 0.8)
          && (*Proton_ProbNNp > 0.9)
              );

if (MassRange){
UncutMass->Fill(*Lc_M);
ProbNNpVariable->Fill(*Proton_ProbNNp);
ProbNNxVariable->Fill(prodProbNN);
}

bool SignalRegion = *Lc_M > 2274. && *Lc_M < 2300.;
bool BackgroundRegion = (*Lc_M > 2222. && *Lc_M < 2235.) || (*Lc_M > 2339. && *Lc_M < 2352.);
bool MidRegion = (*Lc_M > 2235. && *Lc_M < 2274.) || (*Lc_M > 2300. && *Lc_M < 2339.);

if(PreliminaryCuts && MassRange){
PreliminaryMass->Fill(*Lc_M);

if(SignalRegion){
  ProbNNSignal->Fill(prodProbNN);
  ProbNNpSignal->Fill(*Proton_ProbNNp);
  PreliminarySignal->Fill(*Lc_M);
}

if(BackgroundRegion){
  ProbNNBackground->Fill(prodProbNN);
  ProbNNpBackground->Fill(*Proton_ProbNNp);
  PreliminaryBackground->Fill(*Lc_M);
}

if(MidRegion){
  PreliminaryMid->Fill(*Lc_M);
}
}

if(PIDBSubbedCuts && MassRange){
PIDBSubedMass->Fill(*Lc_M);
}



   return kTRUE;
}

void PIDSelection::SlaveTerminate()
{

}

void PIDSelection::Terminate()
{

    gStyle->SetStatW(0.25);
    gStyle->SetStatH(0.25);

  auto lt = new TLatex();
  lt->SetTextSize(0.04);

  ProbNNSignalEstimate->Add(ProbNNSignal,ProbNNBackground,1.0,-1.0);
  ProbNNpSignalEstimate->Add(ProbNNpSignal,ProbNNpBackground,1.0,-1.0);

  c2->cd();
  c2->SetBottomMargin(0.2);
  c2->SetLeftMargin(0.15);

  gStyle->SetOptStat(0);
  ProbNNpVariable->Draw();
  ProbNNpVariable->SetMinimum(0);
  ProbNNpVariable->SetLineWidth(2);
  ProbNNpVariable->GetXaxis()->CenterTitle(true);
  ProbNNpVariable->GetXaxis()->SetTitleSize(20);
  ProbNNpVariable->GetXaxis()->SetTitleFont(43);
  ProbNNpVariable->GetXaxis()->SetTitleOffset(1.5);
  ProbNNpVariable->GetXaxis()->SetLabelSize(0.05);
  ProbNNpVariable->GetYaxis()->SetTitleSize(20);
  ProbNNpVariable->GetYaxis()->SetTitleFont(43);
  ProbNNpVariable->GetYaxis()->SetLabelSize(0.05);
  lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
  ProbNNpCut->Draw("SAME");
  c2->SaveAs("ProbNNpVariable.pdf");

  ProbNNxVariable->Draw();
  ProbNNxVariable->SetMinimum(0);
  ProbNNxVariable->SetLineWidth(2);
  ProbNNxVariable->GetXaxis()->CenterTitle(true);
  ProbNNxVariable->GetXaxis()->SetTitleSize(20);
  ProbNNxVariable->GetXaxis()->SetTitleFont(43);
  ProbNNxVariable->GetXaxis()->SetTitleOffset(1.5);
  ProbNNxVariable->GetXaxis()->SetLabelSize(0.05);
  ProbNNxVariable->GetYaxis()->SetTitleSize(20);
  ProbNNxVariable->GetYaxis()->SetTitleFont(43);
  ProbNNxVariable->GetYaxis()->SetLabelSize(0.05);
  lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
  ProbNNxCut->Draw("SAME");
  c2->SaveAs("ProbNNxVariable.pdf");


  gStyle->SetOptStat(11);
  PreliminaryMass->Draw();
  PreliminaryMass->SetMinimum(0);
  PreliminaryMass->GetXaxis()->CenterTitle(true);
  PreliminaryMass->GetXaxis()->SetTitleSize(20);
  PreliminaryMass->GetXaxis()->SetTitleFont(43);
  PreliminaryMass->GetXaxis()->SetTitleOffset(1.5);
  PreliminaryMass->GetXaxis()->SetLabelSize(0.05);
  PreliminaryMass->GetYaxis()->SetTitleSize(20);
  PreliminaryMass->GetYaxis()->SetTitleFont(43);
  PreliminaryMass->GetYaxis()->SetLabelSize(0.05);
  PreliminarySignal->Draw("SAME");
  PreliminaryMid->Draw("SAME");
  PreliminaryBackground->Draw("SAME");
  lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
  c2->SaveAs("LcMPreliminaryCut.pdf");

  gStyle->SetOptStat(0);

  ProbNNSignal->GetYaxis()->SetTitle("Entries / (0.005 Probability)");
  ProbNNSignal->GetXaxis()->SetTitle("Prod(ProbNNx)");
  ProbNNSignal->SetMinimum(0);
  ProbNNSignal->GetXaxis()->CenterTitle(true);
  ProbNNSignal->GetXaxis()->SetTitleSize(20);
  ProbNNSignal->GetXaxis()->SetTitleFont(43);
  ProbNNSignal->GetXaxis()->SetTitleOffset(1.5);
  ProbNNSignal->GetXaxis()->SetLabelSize(0.05);
  ProbNNSignal->GetYaxis()->SetTitleSize(20);
  ProbNNSignal->GetYaxis()->SetTitleFont(43);
  ProbNNSignal->GetYaxis()->SetLabelSize(0.05);
  ProbNNSignal->Draw();
  ProbNNSignalEstimate->Draw("SAME");
  ProbNNBackground->Draw("SAME");
  ProbNNSignal->SetLineWidth(3);
  ProbNNSignalEstimate->SetLineWidth(3);
  ProbNNBackground->SetLineWidth(3);
  gPad->BuildLegend(0.25,0.65,0.65,0.85);
  lt->DrawLatexNDC(0.25, 0.60, "LHCb Preliminary");
  ProbNNSignal->SetTitle("");
  c2->SaveAs("ProbNNBsub.pdf");

  ProbNNpSignal->GetYaxis()->SetTitle("Entries per / (0.005 Probability)");
  ProbNNpSignal->GetXaxis()->SetTitle("Proton_ProbNNp");
  ProbNNpSignal->SetMinimum(0);
  ProbNNpSignal->GetXaxis()->CenterTitle(true);
  ProbNNpSignal->GetXaxis()->SetTitleSize(20);
  ProbNNpSignal->GetXaxis()->SetTitleFont(43);
  ProbNNpSignal->GetXaxis()->SetTitleOffset(1.5);
  ProbNNpSignal->GetXaxis()->SetLabelSize(0.05);
  ProbNNpSignal->GetYaxis()->SetTitleSize(20);
  ProbNNpSignal->GetYaxis()->SetTitleFont(43);
  ProbNNpSignal->GetYaxis()->SetLabelSize(0.05);
  ProbNNpSignal->Draw();
  ProbNNpSignalEstimate->Draw("SAME");
  ProbNNpBackground->Draw("SAME");
  ProbNNpSignal->SetLineWidth(3);
  ProbNNpSignalEstimate->SetLineWidth(3);
  ProbNNpBackground->SetLineWidth(3);
  gPad->BuildLegend(0.25,0.65,0.65,0.85);
  lt->DrawLatexNDC(0.25, 0.60, "LHCb Preliminary");
  ProbNNpSignal->SetTitle("");
  c2->SaveAs("ProbNNpBsub.pdf");

  c2->cd();


//////////////////////////////////////
    gStyle->SetOptStat(11);
    gStyle->SetStatW(0.25);
    gStyle->SetStatH(0.25);

UncutMass->SetMinimum(0.0001);
UncutMass->GetXaxis()->CenterTitle(true);
UncutMass->GetXaxis()->SetTitleSize(20);
UncutMass->GetXaxis()->SetTitleFont(43);
UncutMass->GetXaxis()->SetTitleOffset(1.5);
UncutMass->GetXaxis()->SetLabelSize(0.05);
UncutMass->GetYaxis()->SetTitleSize(20);
UncutMass->GetYaxis()->SetTitleFont(43);
UncutMass->GetYaxis()->SetLabelSize(0.05);
UncutMass->Draw();
gPad->Update();
UncutMass->SetLineWidth(2);
lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
c2->SaveAs("LcMUncut.pdf");

////////////////////////////////////////////////////////
PIDBSubedMass->SetMinimum(0.0001);
PIDBSubedMass->GetXaxis()->CenterTitle(true);
PIDBSubedMass->GetXaxis()->SetTitleSize(20);
PIDBSubedMass->GetXaxis()->SetTitleFont(43);
PIDBSubedMass->GetXaxis()->SetTitleOffset(1.5);
PIDBSubedMass->GetXaxis()->SetLabelSize(0.05);
PIDBSubedMass->GetYaxis()->SetTitleSize(20);
PIDBSubedMass->GetYaxis()->SetTitleFont(43);
PIDBSubedMass->GetYaxis()->SetLabelSize(0.05);
PIDBSubedMass->Draw();
gPad->Update();
PIDBSubedMass->SetLineWidth(2);
lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
c2->SaveAs("LcMPIDBSubed.pdf");

}
