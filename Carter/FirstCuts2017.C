//Initial Cuts with Various Fits and Pull Plots

#define FirstCuts2017_cxx
#include "FirstCuts2017.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

#include "fit1MeV_Gaussian.C"
#include "fitHalfMeV_Gaussian.C"
#include "DGOneMuOneTotals1MeV.C"
#include "DGOneMuOneTotalsHalfMeV.C"
#include "DGTwoMuOneTotals1MeV.C"
#include "DGTwoMuOneTotalsHalfMeV.C"

TH1D * MassHistLooseHalfMeV = nullptr;
TH1D * MassHistMidHalfMeV = nullptr;
TH1D * MassHistTightHalfMeV = nullptr;

TH1D * MassHistLoose1MeV = nullptr;
TH1D * MassHistMid1MeV = nullptr;
TH1D * MassHistTight1MeV = nullptr;

TFile * File = nullptr;

TCanvas * c1 = nullptr;
TCanvas * ex1 = nullptr;

void FirstCuts2017::Begin(TTree * /*tree*/)
{
   TString option = GetOption();

   MassHistLooseHalfMeV = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 300, 2210, 2360);
   MassHistLooseHalfMeV->GetXaxis()->SetTitle("MeV");
   MassHistLooseHalfMeV->GetYaxis()->SetTitle("Events Per 2 MeV");

   MassHistMidHalfMeV = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 300, 2210, 2360);
   MassHistMidHalfMeV->GetXaxis()->SetTitle("MeV");
   MassHistMidHalfMeV->GetYaxis()->SetTitle("Events Per 2 MeV");

   MassHistTightHalfMeV = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 300, 2210, 2360);
   MassHistTightHalfMeV->GetXaxis()->SetTitle("MeV");
   MassHistTightHalfMeV->GetYaxis()->SetTitle("Events Per 2 MeV");

   MassHistLoose1MeV = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 150, 2210, 2360);
   MassHistLoose1MeV->GetXaxis()->SetTitle("MeV");
   MassHistLoose1MeV->GetYaxis()->SetTitle("Events Per 1 MeV");

   MassHistMid1MeV = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 150, 2210, 2360);
   MassHistMid1MeV->GetXaxis()->SetTitle("MeV");
   MassHistMid1MeV->GetYaxis()->SetTitle("Events Per 1 MeV");

   MassHistTight1MeV = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 150, 2210, 2360);
   MassHistTight1MeV->GetXaxis()->SetTitle("MeV");
   MassHistTight1MeV->GetYaxis()->SetTitle("Events Per 1 MeV");

   File = new TFile("MassHist2017.root", "RECREATE");
  gFile = File;

   c1 = new TCanvas("canvas", "Test Canvas");
   ex1 = new TCanvas("ex1","Latex",500,600);
}

void FirstCuts2017::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

}

Bool_t FirstCuts2017::Process(Long64_t entry)
{

    GetEntry(entry);
   fReader.SetLocalEntry(entry);

   bool LooseCuts = (
      (((*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp)) > 0.85)
   && (*Proton_PT > 900)
   && (*Kminus_PT > 750)
   && (*Kplus_PT > 750)
   );

   bool MidCuts = (
      (((*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp)) > 0.9)
   && (*Proton_PT > 900)
   && (*Kminus_PT > 750)
   && (*Kplus_PT > 750)
   );

   bool TightCuts = (
      (((*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp)) > 0.95)
   && (*Proton_PT > 900)
   && (*Kminus_PT > 750)
   && (*Kplus_PT > 750)
   );

   if (MidCuts){
     MassHistMidHalfMeV->Fill(*Lcplus_M);
     MassHistMid1MeV->Fill(*Lcplus_M);
   }

   if (LooseCuts){
     MassHistLooseHalfMeV->Fill(*Lcplus_M);
     MassHistLoose1MeV->Fill(*Lcplus_M);
   }

   if (TightCuts){
     MassHistTightHalfMeV->Fill(*Lcplus_M);
     MassHistTight1MeV->Fill(*Lcplus_M);
   }

   return kTRUE;
}

void FirstCuts2017::SlaveTerminate()
{
}

void FirstCuts2017::Terminate()
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

double PullxHalfMeV[300];
double Pullx1MeV[150];

TPad *pad1 = new TPad("pad1","pad1",0,0.33,1,1);
TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.33);
pad2->SetTopMargin(0.03030303);
pad1->Draw();
pad2->Draw();

/////////////////////////////
TF1 *GaussianLooseHalfMeVSG = new TF1("GaussianLooseHalfMeVSG",fitHalfMeV_Gaussian,2100.,2500.,5);
GaussianLooseHalfMeVSG->SetParameter(0,400.);
GaussianLooseHalfMeVSG->SetParameter(1,2287);
GaussianLooseHalfMeVSG->SetParameter(2, 6);
GaussianLooseHalfMeVSG->SetParLimits(2, 0.,20.);
GaussianLooseHalfMeVSG->SetParameter(3, 0.);
GaussianLooseHalfMeVSG->SetParameter(4, 0.);

pad1->cd();
MassHistLooseHalfMeV->SetMinimum(0);
MassHistLooseHalfMeV->Fit("GaussianLooseHalfMeVSG");

int BinHeightLooseHalfMeVSG[300];
int FitHeightLooseHalfMeVSG[300];
double PullLooseHalfMeVSG[300];

double LooseHalfMeVSGcount1 = 0;
double LooseHalfMeVSGcount2 = 0;
double LooseHalfMeVSGcount3 = 0;

for (int bin = 0; bin < 300; bin++){
BinHeightLooseHalfMeVSG[bin] = MassHistLooseHalfMeV->GetBinContent(bin + 1);
PullxHalfMeV[bin] = (bin + 1);
int xvalueHalfMeVSG = 2210.25 + 0.5*(bin);
FitHeightLooseHalfMeVSG[bin] = round(GaussianLooseHalfMeVSG->Eval(xvalueHalfMeVSG));
PullLooseHalfMeVSG[bin] = (BinHeightLooseHalfMeVSG[bin] - FitHeightLooseHalfMeVSG[bin])/TMath::Sqrt(FitHeightLooseHalfMeVSG[bin]);

if (PullLooseHalfMeVSG[bin] > -1 && PullLooseHalfMeVSG[bin] < 1){
  LooseHalfMeVSGcount1 += 1;
}

if (PullLooseHalfMeVSG[bin] > -2 && PullLooseHalfMeVSG[bin] < 2){
  LooseHalfMeVSGcount2 += 1;
}

if (PullLooseHalfMeVSG[bin] > -3 && PullLooseHalfMeVSG[bin] < 3){
  LooseHalfMeVSGcount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotLooseHalfMeVSG = new TGraph(300, PullxHalfMeV, PullLooseHalfMeVSG);
PullPlotLooseHalfMeVSG->GetXaxis()->SetLimits(0.5,300.5);
PullPlotLooseHalfMeVSG->GetXaxis()->SetTickLength(0.);
PullPlotLooseHalfMeVSG->GetYaxis()->SetTickLength(0.);
PullPlotLooseHalfMeVSG->SetFillColor(38);
PullPlotLooseHalfMeVSG->GetYaxis()->SetTitle("Pull");
PullPlotLooseHalfMeVSG->GetYaxis()->CenterTitle();
PullPlotLooseHalfMeVSG->GetYaxis()->SetTitleSize(0.10);
PullPlotLooseHalfMeVSG->GetYaxis()->SetTitleOffset(0.2);
PullPlotLooseHalfMeVSG->GetXaxis()->SetLabelSize(0);
PullPlotLooseHalfMeVSG->GetYaxis()->SetLabelFont(42);
PullPlotLooseHalfMeVSG->GetYaxis()->SetLabelSize(0.06);
PullPlotLooseHalfMeVSG->SetTitle("");
PullPlotLooseHalfMeVSG->SetMinimum(-5);
PullPlotLooseHalfMeVSG->SetMaximum(5);
PullPlotLooseHalfMeVSG->Draw("AB");
      c1->Write("Lc Mass - Loose/HalfMeVSG");

ex1->cd();
   TLatex Tl;
   Tl.SetTextAlign(12);
   Tl.SetTextSize(0.04);
   Tl.DrawLatex(0.1,0.9,Form("Number of Signal Entries: %f Events", GaussianLooseHalfMeVSG->GetParameter(0)));
   Tl.DrawLatex(0.1,0.85,Form("Error: %f Events", GaussianLooseHalfMeVSG->GetParError(0)));
   Tl.DrawLatex(0.1,0.7,Form("Mean Value: %f MeV", GaussianLooseHalfMeVSG->GetParameter(1)));
   Tl.DrawLatex(0.1,0.65,Form("Error: %f MeV", GaussianLooseHalfMeVSG->GetParError(1)));
   Tl.DrawLatex(0.1,0.5,Form("Sigma: %f MeV", GaussianLooseHalfMeVSG->GetParameter(2)));
   Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianLooseHalfMeVSG->GetParError(2)));
   Tl.DrawLatex(0.1,0.3,Form("Bins Between -1 & 1 %f Bins", LooseHalfMeVSGcount1));
   Tl.DrawLatex(0.1,0.2,Form("Bins Between -2 & 2 %f Bins", LooseHalfMeVSGcount2));
   Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", LooseHalfMeVSGcount3));
   ex1->Write("Loose Fit Values/HalfMeVSG");
c1->cd();
///////////////////////////////////////////////////////

TF1 *GaussianMidHalfMeVSG = new TF1("GaussianMidHalfMeVSG",fitHalfMeV_Gaussian,2100.,2500.,5);
GaussianMidHalfMeVSG->SetParameter(0,400.);
GaussianMidHalfMeVSG->SetParameter(1,2287);
GaussianMidHalfMeVSG->SetParameter(2, 6);
GaussianMidHalfMeVSG->SetParLimits(2, 0.,20.);
GaussianMidHalfMeVSG->SetParameter(3, 0.);
GaussianMidHalfMeVSG->SetParameter(4, 0.);

  pad1->cd();
  MassHistMidHalfMeV->SetMinimum(0);
  MassHistMidHalfMeV->Fit("GaussianMidHalfMeVSG");

  int BinHeightMidHalfMeVSG[300];
  int FitHeightMidHalfMeVSG[300];
  double PullMidHalfMeVSG[300];

double   MidHalfMeVSGcount1 = 0;
double   MidHalfMeVSGcount2 = 0;
double   MidHalfMeVSGcount3 = 0;

  for (int bin = 0; bin < 300; bin++){
  BinHeightMidHalfMeVSG[bin] = MassHistMidHalfMeV->GetBinContent(bin + 1);
  int xvalueHalfMeVSG = 2210.25 + 0.5*(bin);
  FitHeightMidHalfMeVSG[bin] = round(GaussianMidHalfMeVSG->Eval(xvalueHalfMeVSG));
  PullMidHalfMeVSG[bin] = (BinHeightMidHalfMeVSG[bin] - FitHeightMidHalfMeVSG[bin])/TMath::Sqrt(FitHeightMidHalfMeVSG[bin]);

  if (PullMidHalfMeVSG[bin] > -1 && PullMidHalfMeVSG[bin] < 1){
  MidHalfMeVSGcount1 += 1;
  }

  if (PullMidHalfMeVSG[bin] > -2 && PullMidHalfMeVSG[bin] < 2){
  MidHalfMeVSGcount2 += 1;
  }

  if (PullMidHalfMeVSG[bin] > -3 && PullMidHalfMeVSG[bin] < 3){
  MidHalfMeVSGcount3 += 1;
  }
  }

  pad2->cd();
TGraph* PullPlotMidHalfMeVSG = new TGraph(300, PullxHalfMeV, PullMidHalfMeVSG);
PullPlotMidHalfMeVSG->GetXaxis()->SetLimits(0.5,300.5);
PullPlotMidHalfMeVSG->GetXaxis()->SetTickLength(0.);
PullPlotMidHalfMeVSG->GetYaxis()->SetTickLength(0.);
PullPlotMidHalfMeVSG->SetFillColor(38);
PullPlotMidHalfMeVSG->GetYaxis()->SetTitle("Pull");
PullPlotMidHalfMeVSG->GetYaxis()->CenterTitle();
PullPlotMidHalfMeVSG->GetYaxis()->SetTitleSize(0.10);
PullPlotMidHalfMeVSG->GetYaxis()->SetTitleOffset(0.2);
PullPlotMidHalfMeVSG->GetXaxis()->SetLabelSize(0);
PullPlotMidHalfMeVSG->GetYaxis()->SetLabelFont(42);
PullPlotMidHalfMeVSG->GetYaxis()->SetLabelSize(0.06);
PullPlotMidHalfMeVSG->SetTitle("");
PullPlotMidHalfMeVSG->SetMinimum(-5);
PullPlotMidHalfMeVSG->SetMaximum(5);
PullPlotMidHalfMeVSG->Draw("AB");

      c1->Write("Lc Mass - Mid/HalfMeVSG");

ex1->cd();
   ex1->Clear();
Tl.DrawLatex(0.1,0.9,Form("Number of Signal Entries: %f Events", GaussianMidHalfMeVSG->GetParameter(0)));
Tl.DrawLatex(0.1,0.85,Form("Error: %f Events", GaussianMidHalfMeVSG->GetParError(0)));
Tl.DrawLatex(0.1,0.7,Form("Mean Value: %f MeV", GaussianMidHalfMeVSG->GetParameter(1)));
Tl.DrawLatex(0.1,0.65,Form("Error: %f MeV", GaussianMidHalfMeVSG->GetParError(1)));
Tl.DrawLatex(0.1,0.5,Form("Sigma: %f MeV", GaussianMidHalfMeVSG->GetParameter(2)));
Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianMidHalfMeVSG->GetParError(2)));
Tl.DrawLatex(0.1,0.3,Form("Bins Between -1 & 1 %f Bins", MidHalfMeVSGcount1));
Tl.DrawLatex(0.1,0.2,Form("Bins Between -2 & 2 %f Bins", MidHalfMeVSGcount2));
Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", MidHalfMeVSGcount3));
   ex1->Write("Mid Fit Values/HalfMeVSG");
c1->cd();
//////////////////////////////////////////////////////

TF1 *GaussianTightHalfMeVSG = new TF1("GaussianTightHalfMeVSG",fitHalfMeV_Gaussian,2100.,2500.,5);
GaussianTightHalfMeVSG->SetParameter(0,400.);
GaussianTightHalfMeVSG->SetParameter(1,2286);
GaussianTightHalfMeVSG->SetParameter(2, 6);
GaussianTightHalfMeVSG->SetParLimits(2, 0.,20.);
GaussianTightHalfMeVSG->SetParameter(3, 0.);
GaussianTightHalfMeVSG->SetParameter(4, 0.);

pad1->cd();
MassHistTightHalfMeV->SetMinimum(0);
MassHistTightHalfMeV->Fit("GaussianTightHalfMeVSG");

int BinHeightTightHalfMeVSG[300];
int FitHeightTightHalfMeVSG[300];
double PullTightHalfMeVSG[300];

double TightHalfMeVSGcount1 = 0;
double TightHalfMeVSGcount2 = 0;
double TightHalfMeVSGcount3 = 0;

for (int bin = 0; bin < 300; bin++){
BinHeightTightHalfMeVSG[bin] = MassHistTightHalfMeV->GetBinContent(bin + 1);
int xvalueHalfMeVSG = 2210.25 + 0.5*(bin);
FitHeightTightHalfMeVSG[bin] = round(GaussianTightHalfMeVSG->Eval(xvalueHalfMeVSG));

PullTightHalfMeVSG[bin] = (BinHeightTightHalfMeVSG[bin] - FitHeightTightHalfMeVSG[bin])/TMath::Sqrt(FitHeightTightHalfMeVSG[bin]);

if (PullTightHalfMeVSG[bin] > -1 && PullTightHalfMeVSG[bin] < 1){
TightHalfMeVSGcount1 += 1;
}

if (PullTightHalfMeVSG[bin] > -2 && PullTightHalfMeVSG[bin] < 2){
TightHalfMeVSGcount2 += 1;
}

if (PullTightHalfMeVSG[bin] > -3 && PullTightHalfMeVSG[bin] < 3){
TightHalfMeVSGcount3 += 1;
}
}
     pad2->cd();
     TGraph* PullPlotTightHalfMeVSG = new TGraph(300, PullxHalfMeV, PullTightHalfMeVSG);
     PullPlotTightHalfMeVSG->GetXaxis()->SetLimits(0.5,300.5);
     PullPlotTightHalfMeVSG->GetXaxis()->SetTickLength(0.);
     PullPlotTightHalfMeVSG->GetYaxis()->SetTickLength(0.);
     PullPlotTightHalfMeVSG->SetFillColor(38);
     PullPlotTightHalfMeVSG->GetYaxis()->SetTitle("Pull");
     PullPlotTightHalfMeVSG->GetYaxis()->CenterTitle();
     PullPlotTightHalfMeVSG->GetYaxis()->SetTitleSize(0.10);
     PullPlotTightHalfMeVSG->GetYaxis()->SetTitleOffset(0.2);
     PullPlotTightHalfMeVSG->GetXaxis()->SetLabelSize(0);
     PullPlotTightHalfMeVSG->GetYaxis()->SetLabelFont(42);
     PullPlotTightHalfMeVSG->GetYaxis()->SetLabelSize(0.06);
     PullPlotTightHalfMeVSG->SetTitle("");
     PullPlotTightHalfMeVSG->SetMinimum(-5);
     PullPlotTightHalfMeVSG->SetMaximum(5);
     PullPlotTightHalfMeVSG->Draw("AB");
     c1->Write("Lc Mass - Tight/HalfMeVSG");

ex1->cd();
   ex1->Clear();
Tl.DrawLatex(0.1,0.9,Form("Number of Signal Entries: %f Events", GaussianTightHalfMeVSG->GetParameter(0)));
Tl.DrawLatex(0.1,0.85,Form("Error: %f Events", GaussianTightHalfMeVSG->GetParError(0)));
Tl.DrawLatex(0.1,0.7,Form("Mean Value: %f MeV", GaussianTightHalfMeVSG->GetParameter(1)));
Tl.DrawLatex(0.1,0.65,Form("Error: %f MeV", GaussianTightHalfMeVSG->GetParError(1)));
Tl.DrawLatex(0.1,0.5,Form("Sigma: %f MeV", GaussianTightHalfMeVSG->GetParameter(2)));
Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianTightHalfMeVSG->GetParError(2)));
Tl.DrawLatex(0.1,0.3,Form("Bins Between -1 & 1 %f Bins", TightHalfMeVSGcount1));
Tl.DrawLatex(0.1,0.2,Form("Bins Between -2 & 2 %f Bins", TightHalfMeVSGcount2));
Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", TightHalfMeVSGcount3));
   ex1->Write("Tight Fit Values/HalfMeVSG");
c1->cd();
/////////////////////////////

TF1 *GaussianLoose1MeVSG = new TF1("GaussianLoose1MeVSG",fit1MeV_Gaussian,2100.,2500.,5);
GaussianLoose1MeVSG->SetParameter(0,400.);
GaussianLoose1MeVSG->SetParameter(1,2287);
GaussianLoose1MeVSG->SetParameter(2, 6);
GaussianLoose1MeVSG->SetParLimits(2, 0.,20.);
GaussianLoose1MeVSG->SetParameter(3, 0.);
GaussianLoose1MeVSG->SetParameter(4, 0.);

pad1->cd();
MassHistLoose1MeV->SetMinimum(0);
MassHistLoose1MeV->Fit("GaussianLoose1MeVSG");

int BinHeightLoose1MeVSG[150];
int FitHeightLoose1MeVSG[150];
double PullLoose1MeVSG[150];

double Loose1MeVSGcount1 = 0;
double Loose1MeVSGcount2 = 0;
double Loose1MeVSGcount3 = 0;

for (int bin = 0; bin < 150; bin++){
BinHeightLoose1MeVSG[bin] = MassHistLoose1MeV->GetBinContent(bin + 1);
Pullx1MeV[bin] = (bin + 1);
int xvalue1MeVSG = 2210.5 + 1*(bin);
FitHeightLoose1MeVSG[bin] = round(GaussianLoose1MeVSG->Eval(xvalue1MeVSG));
PullLoose1MeVSG[bin] = (BinHeightLoose1MeVSG[bin] - FitHeightLoose1MeVSG[bin])/TMath::Sqrt(FitHeightLoose1MeVSG[bin]);

if (PullLoose1MeVSG[bin] > -1 && PullLoose1MeVSG[bin] < 1){
  Loose1MeVSGcount1 += 1;
}

if (PullLoose1MeVSG[bin] > -2 && PullLoose1MeVSG[bin] < 2){
  Loose1MeVSGcount2 += 1;
}

if (PullLoose1MeVSG[bin] > -3 && PullLoose1MeVSG[bin] < 3){
  Loose1MeVSGcount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotLoose1MeVSG = new TGraph(150, Pullx1MeV, PullLoose1MeVSG);
PullPlotLoose1MeVSG->GetXaxis()->SetLimits(0.5,150.5);
PullPlotLoose1MeVSG->GetXaxis()->SetTickLength(0.);
PullPlotLoose1MeVSG->GetYaxis()->SetTickLength(0.);
PullPlotLoose1MeVSG->SetFillColor(38);
PullPlotLoose1MeVSG->GetYaxis()->SetTitle("Pull");
PullPlotLoose1MeVSG->GetYaxis()->CenterTitle();
PullPlotLoose1MeVSG->GetYaxis()->SetTitleSize(0.10);
PullPlotLoose1MeVSG->GetYaxis()->SetTitleOffset(0.2);
PullPlotLoose1MeVSG->GetXaxis()->SetLabelSize(0);
PullPlotLoose1MeVSG->GetYaxis()->SetLabelFont(42);
PullPlotLoose1MeVSG->GetYaxis()->SetLabelSize(0.06);
PullPlotLoose1MeVSG->SetTitle("");
PullPlotLoose1MeVSG->SetMinimum(-5);
PullPlotLoose1MeVSG->SetMaximum(5);
PullPlotLoose1MeVSG->Draw("AB");
      c1->Write("Lc Mass - Loose/1MeVSG");

ex1->cd();
    ex1->Clear();
   Tl.SetTextAlign(12);
   Tl.SetTextSize(0.04);
   Tl.DrawLatex(0.1,0.9,Form("Number of Signal Entries: %f Events", GaussianLoose1MeVSG->GetParameter(0)));
   Tl.DrawLatex(0.1,0.85,Form("Error: %f Events", GaussianLoose1MeVSG->GetParError(0)));
   Tl.DrawLatex(0.1,0.7,Form("Mean Value: %f MeV", GaussianLoose1MeVSG->GetParameter(1)));
   Tl.DrawLatex(0.1,0.65,Form("Error: %f MeV", GaussianLoose1MeVSG->GetParError(1)));
   Tl.DrawLatex(0.1,0.5,Form("Sigma: %f MeV", GaussianLoose1MeVSG->GetParameter(2)));
   Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianLoose1MeVSG->GetParError(2)));
   Tl.DrawLatex(0.1,0.3,Form("Bins Between -1 & 1 %f Bins", Loose1MeVSGcount1));
   Tl.DrawLatex(0.1,0.2,Form("Bins Between -2 & 2 %f Bins", Loose1MeVSGcount2));
   Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", Loose1MeVSGcount3));
   ex1->Write("Loose Fit Values/1MeVSG");
c1->cd();
///////////////////////////////////////////////////////

TF1 *GaussianMid1MeVSG = new TF1("GaussianMid1MeVSG",fit1MeV_Gaussian,2100.,2500.,5);
GaussianMid1MeVSG->SetParameter(0,400.);
GaussianMid1MeVSG->SetParameter(1,2287);
GaussianMid1MeVSG->SetParameter(2, 6);
GaussianMid1MeVSG->SetParLimits(2, 0.,20.);
GaussianMid1MeVSG->SetParameter(3, 0.);
GaussianMid1MeVSG->SetParameter(4, 0.);

  pad1->cd();
  MassHistMid1MeV->SetMinimum(0);
  MassHistMid1MeV->Fit("GaussianMid1MeVSG");

  int BinHeightMid1MeVSG[150];
  int FitHeightMid1MeVSG[150];
  double PullMid1MeVSG[150];

double   Mid1MeVSGcount1 = 0;
double   Mid1MeVSGcount2 = 0;
double   Mid1MeVSGcount3 = 0;

  for (int bin = 0; bin < 150; bin++){
  BinHeightMid1MeVSG[bin] = MassHistMid1MeV->GetBinContent(bin + 1);
  int xvalue1MeVSG = 2210.5 + 1*(bin);
  FitHeightMid1MeVSG[bin] = round(GaussianMid1MeVSG->Eval(xvalue1MeVSG));
  PullMid1MeVSG[bin] = (BinHeightMid1MeVSG[bin] - FitHeightMid1MeVSG[bin])/TMath::Sqrt(FitHeightMid1MeVSG[bin]);

  if (PullMid1MeVSG[bin] > -1 && PullMid1MeVSG[bin] < 1){
  Mid1MeVSGcount1 += 1;
  }

  if (PullMid1MeVSG[bin] > -2 && PullMid1MeVSG[bin] < 2){
  Mid1MeVSGcount2 += 1;
  }

  if (PullMid1MeVSG[bin] > -3 && PullMid1MeVSG[bin] < 3){
  Mid1MeVSGcount3 += 1;
  }
  }

  pad2->cd();
TGraph* PullPlotMid1MeVSG = new TGraph(150, Pullx1MeV, PullMid1MeVSG);
PullPlotMid1MeVSG->GetXaxis()->SetLimits(0.5,150.5);
PullPlotMid1MeVSG->GetXaxis()->SetTickLength(0.);
PullPlotMid1MeVSG->GetYaxis()->SetTickLength(0.);
PullPlotMid1MeVSG->SetFillColor(38);
PullPlotMid1MeVSG->GetYaxis()->SetTitle("Pull");
PullPlotMid1MeVSG->GetYaxis()->CenterTitle();
PullPlotMid1MeVSG->GetYaxis()->SetTitleSize(0.10);
PullPlotMid1MeVSG->GetYaxis()->SetTitleOffset(0.2);
PullPlotMid1MeVSG->GetXaxis()->SetLabelSize(0);
PullPlotMid1MeVSG->GetYaxis()->SetLabelFont(42);
PullPlotMid1MeVSG->GetYaxis()->SetLabelSize(0.06);
PullPlotMid1MeVSG->SetTitle("");
PullPlotMid1MeVSG->SetMinimum(-5);
PullPlotMid1MeVSG->SetMaximum(5);
PullPlotMid1MeVSG->Draw("AB");

      c1->Write("Lc Mass - Mid/1MeVSG");

ex1->cd();
   ex1->Clear();
Tl.DrawLatex(0.1,0.9,Form("Number of Signal Entries: %f Events", GaussianMid1MeVSG->GetParameter(0)));
Tl.DrawLatex(0.1,0.85,Form("Error: %f Events", GaussianMid1MeVSG->GetParError(0)));
Tl.DrawLatex(0.1,0.7,Form("Mean Value: %f MeV", GaussianMid1MeVSG->GetParameter(1)));
Tl.DrawLatex(0.1,0.65,Form("Error: %f MeV", GaussianMid1MeVSG->GetParError(1)));
Tl.DrawLatex(0.1,0.5,Form("Sigma: %f MeV", GaussianMid1MeVSG->GetParameter(2)));
Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianMid1MeVSG->GetParError(2)));
Tl.DrawLatex(0.1,0.3,Form("Bins Between -1 & 1 %f Bins", Mid1MeVSGcount1));
Tl.DrawLatex(0.1,0.2,Form("Bins Between -2 & 2 %f Bins", Mid1MeVSGcount2));
Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", Mid1MeVSGcount3));
   ex1->Write("Mid Fit Values/1MeVSG");
c1->cd();
//////////////////////////////////////////////////////

TF1 *GaussianTight1MeVSG = new TF1("GaussianTight1MeVSG",fit1MeV_Gaussian,2100.,2500.,5);
GaussianTight1MeVSG->SetParameter(0,400.);
GaussianTight1MeVSG->SetParameter(1,2286);
GaussianTight1MeVSG->SetParameter(2, 6);
GaussianTight1MeVSG->SetParLimits(2, 0.,20.);
GaussianTight1MeVSG->SetParameter(3, 0.);
GaussianTight1MeVSG->SetParameter(4, 0.);

pad1->cd();
MassHistTight1MeV->SetMinimum(0);
MassHistTight1MeV->Fit("GaussianTight1MeVSG");

int BinHeightTight1MeVSG[150];
int FitHeightTight1MeVSG[150];
double PullTight1MeVSG[150];

double Tight1MeVSGcount1 = 0;
double Tight1MeVSGcount2 = 0;
double Tight1MeVSGcount3 = 0;

for (int bin = 0; bin < 150; bin++){
BinHeightTight1MeVSG[bin] = MassHistTight1MeV->GetBinContent(bin + 1);
int xvalue1MeVSG = 2210.5 + 1*(bin);
FitHeightTight1MeVSG[bin] = round(GaussianTight1MeVSG->Eval(xvalue1MeVSG));

PullTight1MeVSG[bin] = (BinHeightTight1MeVSG[bin] - FitHeightTight1MeVSG[bin])/TMath::Sqrt(FitHeightTight1MeVSG[bin]);

if (PullTight1MeVSG[bin] > -1 && PullTight1MeVSG[bin] < 1){
Tight1MeVSGcount1 += 1;
}

if (PullTight1MeVSG[bin] > -2 && PullTight1MeVSG[bin] < 2){
Tight1MeVSGcount2 += 1;
}

if (PullTight1MeVSG[bin] > -3 && PullTight1MeVSG[bin] < 3){
Tight1MeVSGcount3 += 1;
}
}
     pad2->cd();
     TGraph* PullPlotTight1MeVSG = new TGraph(150, Pullx1MeV, PullTight1MeVSG);
     PullPlotTight1MeVSG->GetXaxis()->SetLimits(0.5,150.5);
     PullPlotTight1MeVSG->GetXaxis()->SetTickLength(0.);
     PullPlotTight1MeVSG->GetYaxis()->SetTickLength(0.);
     PullPlotTight1MeVSG->SetFillColor(38);
     PullPlotTight1MeVSG->GetYaxis()->SetTitle("Pull");
     PullPlotTight1MeVSG->GetYaxis()->CenterTitle();
     PullPlotTight1MeVSG->GetYaxis()->SetTitleSize(0.10);
     PullPlotTight1MeVSG->GetYaxis()->SetTitleOffset(0.2);
     PullPlotTight1MeVSG->GetXaxis()->SetLabelSize(0);
     PullPlotTight1MeVSG->GetYaxis()->SetLabelFont(42);
     PullPlotTight1MeVSG->GetYaxis()->SetLabelSize(0.06);
     PullPlotTight1MeVSG->SetTitle("");
     PullPlotTight1MeVSG->SetMinimum(-5);
     PullPlotTight1MeVSG->SetMaximum(5);
     PullPlotTight1MeVSG->Draw("AB");
     c1->Write("Lc Mass - Tight/1MeVSG");

ex1->cd();
   ex1->Clear();
Tl.DrawLatex(0.1,0.9,Form("Number of Signal Entries: %f Events", GaussianTight1MeVSG->GetParameter(0)));
Tl.DrawLatex(0.1,0.85,Form("Error: %f Events", GaussianTight1MeVSG->GetParError(0)));
Tl.DrawLatex(0.1,0.7,Form("Mean Value: %f MeV", GaussianTight1MeVSG->GetParameter(1)));
Tl.DrawLatex(0.1,0.65,Form("Error: %f MeV", GaussianTight1MeVSG->GetParError(1)));
Tl.DrawLatex(0.1,0.5,Form("Sigma: %f MeV", GaussianTight1MeVSG->GetParameter(2)));
Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianTight1MeVSG->GetParError(2)));
Tl.DrawLatex(0.1,0.3,Form("Bins Between -1 & 1 %f Bins", Tight1MeVSGcount1));
Tl.DrawLatex(0.1,0.2,Form("Bins Between -2 & 2 %f Bins", Tight1MeVSGcount2));
Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", Tight1MeVSGcount3));
   ex1->Write("Tight Fit Values/1MeVSG");
c1->cd();
/////////////////////////////
TF1 *GaussianLooseHalfMeVDG = new TF1("GaussianLooseHalfMeVDG",DGOneMuTwoTotalsHalfMeV,2200.,2400.,7);
GaussianLooseHalfMeVDG->SetParameter(0, 2000.);
GaussianLooseHalfMeVDG->SetParLimits(0, 0, 80000);
GaussianLooseHalfMeVDG->SetParameter(1, 2286);
GaussianLooseHalfMeVDG->SetParameter(2, 5);
GaussianLooseHalfMeVDG->SetParLimits(2, 0., 20.);
GaussianLooseHalfMeVDG->SetParameter(3, 2000.);
GaussianLooseHalfMeVDG->SetParLimits(3, 0, 80000);
GaussianLooseHalfMeVDG->SetParameter(4, 5);
GaussianLooseHalfMeVDG->SetParLimits(4, 0., 20.);
GaussianLooseHalfMeVDG->SetParameter(5, 0.);
GaussianLooseHalfMeVDG->SetParameter(6, 0.);

pad1->cd();
MassHistLooseHalfMeV->SetMinimum(0);
MassHistLooseHalfMeV->Fit("GaussianLooseHalfMeVDG");

int BinHeightLooseHalfMeVDG[300];
int FitHeightLooseHalfMeVDG[300];
double PullLooseHalfMeVDG[300];

double LooseHalfMeVDGcount1 = 0;
double LooseHalfMeVDGcount2 = 0;
double LooseHalfMeVDGcount3 = 0;

for (int bin = 0; bin < 300; bin++){
BinHeightLooseHalfMeVDG[bin] = MassHistLooseHalfMeV->GetBinContent(bin + 1);
PullxHalfMeV[bin] = (bin + 1);
int xvalueHalfMeVDG = 2210.25 + 0.5*(bin);
FitHeightLooseHalfMeVDG[bin] = round(GaussianLooseHalfMeVDG->Eval(xvalueHalfMeVDG));
PullLooseHalfMeVDG[bin] = (BinHeightLooseHalfMeVDG[bin] - FitHeightLooseHalfMeVDG[bin])/TMath::Sqrt(FitHeightLooseHalfMeVDG[bin]);

if (PullLooseHalfMeVDG[bin] > -1 && PullLooseHalfMeVDG[bin] < 1){
  LooseHalfMeVDGcount1 += 1;
}

if (PullLooseHalfMeVDG[bin] > -2 && PullLooseHalfMeVDG[bin] < 2){
  LooseHalfMeVDGcount2 += 1;
}

if (PullLooseHalfMeVDG[bin] > -3 && PullLooseHalfMeVDG[bin] < 3){
  LooseHalfMeVDGcount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotLooseHalfMeVDG = new TGraph(300, PullxHalfMeV, PullLooseHalfMeVDG);
PullPlotLooseHalfMeVDG->GetXaxis()->SetLimits(0.5,300.5);
PullPlotLooseHalfMeVDG->GetXaxis()->SetTickLength(0.);
PullPlotLooseHalfMeVDG->GetYaxis()->SetTickLength(0.);
PullPlotLooseHalfMeVDG->SetFillColor(38);
PullPlotLooseHalfMeVDG->GetYaxis()->SetTitle("Pull");
PullPlotLooseHalfMeVDG->GetYaxis()->CenterTitle();
PullPlotLooseHalfMeVDG->GetYaxis()->SetTitleSize(0.10);
PullPlotLooseHalfMeVDG->GetYaxis()->SetTitleOffset(0.2);
PullPlotLooseHalfMeVDG->GetXaxis()->SetLabelSize(0);
PullPlotLooseHalfMeVDG->GetYaxis()->SetLabelFont(42);
PullPlotLooseHalfMeVDG->GetYaxis()->SetLabelSize(0.06);
PullPlotLooseHalfMeVDG->SetTitle("");
PullPlotLooseHalfMeVDG->SetMinimum(-5);
PullPlotLooseHalfMeVDG->SetMaximum(5);
PullPlotLooseHalfMeVDG->Draw("AB");
      c1->Write("Lc Mass - Loose/HalfMeVDG");

ex1->cd();
 ex1->Clear();
   Tl.SetTextAlign(12);
   Tl.SetTextSize(0.04);
   Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries in First Gaussian: %f Events", GaussianLooseHalfMeVDG->GetParameter(0)));
   Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianLooseHalfMeVDG->GetParError(0)));
   Tl.DrawLatex(0.1,0.8,Form("Number of Signal Entries in Second Gaussian: %f Events", GaussianLooseHalfMeVDG->GetParameter(3)));
   Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianLooseHalfMeVDG->GetParError(3)));
   Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianLooseHalfMeVDG->GetParameter(1)));
   Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianLooseHalfMeVDG->GetParError(1)));
   Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianLooseHalfMeVDG->GetParameter(2)));
   Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianLooseHalfMeVDG->GetParError(2)));
   Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianLooseHalfMeVDG->GetParameter(4)));
   Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianLooseHalfMeVDG->GetParError(4)));
   Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", LooseHalfMeVDGcount1));
   Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", LooseHalfMeVDGcount2));
   Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", LooseHalfMeVDGcount3));
   ex1->Write("Loose Fit Values/HalfMeVDG");
c1->cd();
/////////////////////////////

TF1 *GaussianMidHalfMeVDG = new TF1("GaussianMidHalfMeVDG",DGOneMuTwoTotalsHalfMeV,2200.,2400.,7);
GaussianMidHalfMeVDG->SetParameter(0, 2000.);
GaussianMidHalfMeVDG->SetParLimits(0, 0, 80000);
GaussianMidHalfMeVDG->SetParameter(1, 2286);
GaussianMidHalfMeVDG->SetParameter(2, 5);
GaussianMidHalfMeVDG->SetParLimits(2, 0., 20.);
GaussianMidHalfMeVDG->SetParameter(3, 2000.);
GaussianMidHalfMeVDG->SetParLimits(3, 0, 80000);
GaussianMidHalfMeVDG->SetParameter(4, 5);
GaussianMidHalfMeVDG->SetParLimits(4, 0., 20.);
GaussianMidHalfMeVDG->SetParameter(5, 0.);
GaussianMidHalfMeVDG->SetParameter(6, 0.);

pad1->cd();
MassHistMidHalfMeV->SetMinimum(0);
MassHistMidHalfMeV->Fit("GaussianMidHalfMeVDG");

int BinHeightMidHalfMeVDG[300];
int FitHeightMidHalfMeVDG[300];
double PullMidHalfMeVDG[300];

double   MidHalfMeVDGcount1 = 0;
double   MidHalfMeVDGcount2 = 0;
double   MidHalfMeVDGcount3 = 0;

for (int bin = 0; bin < 300; bin++){
BinHeightMidHalfMeVDG[bin] = MassHistMidHalfMeV->GetBinContent(bin + 1);
int xvalueHalfMeVDG = 2210.25 + 0.5*(bin);
FitHeightMidHalfMeVDG[bin] = round(GaussianMidHalfMeVDG->Eval(xvalueHalfMeVDG));
PullMidHalfMeVDG[bin] = (BinHeightMidHalfMeVDG[bin] - FitHeightMidHalfMeVDG[bin])/TMath::Sqrt(FitHeightMidHalfMeVDG[bin]);

if (PullMidHalfMeVDG[bin] > -1 && PullMidHalfMeVDG[bin] < 1){
MidHalfMeVDGcount1 += 1;
}

if (PullMidHalfMeVDG[bin] > -2 && PullMidHalfMeVDG[bin] < 2){
MidHalfMeVDGcount2 += 1;
}

if (PullMidHalfMeVDG[bin] > -3 && PullMidHalfMeVDG[bin] < 3){
MidHalfMeVDGcount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotMidHalfMeVDG = new TGraph(300, PullxHalfMeV, PullMidHalfMeVDG);
PullPlotMidHalfMeVDG->GetXaxis()->SetLimits(0.5,300.5);
PullPlotMidHalfMeVDG->GetXaxis()->SetTickLength(0.);
PullPlotMidHalfMeVDG->GetYaxis()->SetTickLength(0.);
PullPlotMidHalfMeVDG->SetFillColor(38);
PullPlotMidHalfMeVDG->GetYaxis()->SetTitle("Pull");
PullPlotMidHalfMeVDG->GetYaxis()->CenterTitle();
PullPlotMidHalfMeVDG->GetYaxis()->SetTitleSize(0.10);
PullPlotMidHalfMeVDG->GetYaxis()->SetTitleOffset(0.2);
PullPlotMidHalfMeVDG->GetXaxis()->SetLabelSize(0);
PullPlotMidHalfMeVDG->GetYaxis()->SetLabelFont(42);
PullPlotMidHalfMeVDG->GetYaxis()->SetLabelSize(0.06);
PullPlotMidHalfMeVDG->SetTitle("");
PullPlotMidHalfMeVDG->SetMinimum(-5);
PullPlotMidHalfMeVDG->SetMaximum(5);
PullPlotMidHalfMeVDG->Draw("AB");

    c1->Write("Lc Mass - Mid/HalfMeVDG");

ex1->cd();
 ex1->Clear();
 Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries in First Gaussian: %f Events", GaussianMidHalfMeVDG->GetParameter(0)));
 Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianMidHalfMeVDG->GetParError(0)));
 Tl.DrawLatex(0.1,0.8,Form("Number of Signal Entries in Second Gaussian: %f Events", GaussianMidHalfMeVDG->GetParameter(3)));
 Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianMidHalfMeVDG->GetParError(3)));
 Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianMidHalfMeVDG->GetParameter(1)));
 Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianMidHalfMeVDG->GetParError(1)));
 Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianMidHalfMeVDG->GetParameter(2)));
 Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianMidHalfMeVDG->GetParError(2)));
 Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianMidHalfMeVDG->GetParameter(4)));
 Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianMidHalfMeVDG->GetParError(4)));
 Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", MidHalfMeVDGcount1));
 Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", MidHalfMeVDGcount2));
 Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", MidHalfMeVDGcount3));
 ex1->Write("Mid Fit Values/HalfMeVDG");
c1->cd();
//////////////////////////////////////

TF1 *GaussianTightHalfMeVDG = new TF1("GaussianTightHalfMeVDG",DGOneMuTwoTotalsHalfMeV,2200.,2400.,7);
GaussianTightHalfMeVDG->SetParameter(0, 2000.);
GaussianTightHalfMeVDG->SetParLimits(0, 0, 80000);
GaussianTightHalfMeVDG->SetParameter(1, 2286);
GaussianTightHalfMeVDG->SetParameter(2, 5);
GaussianTightHalfMeVDG->SetParLimits(2, 0., 20.);
GaussianTightHalfMeVDG->SetParameter(3, 2000.);
GaussianTightHalfMeVDG->SetParLimits(3, 0, 80000);
GaussianTightHalfMeVDG->SetParameter(4, 5);
GaussianTightHalfMeVDG->SetParLimits(4, 0., 20.);
GaussianTightHalfMeVDG->SetParameter(5, 0.);
GaussianTightHalfMeVDG->SetParameter(6, 0.);

pad1->cd();
MassHistTightHalfMeV->SetMinimum(0);
MassHistTightHalfMeV->Fit("GaussianTightHalfMeVDG");

int BinHeightTightHalfMeVDG[300];
int FitHeightTightHalfMeVDG[300];
double PullTightHalfMeVDG[300];

double TightHalfMeVDGcount1 = 0;
double TightHalfMeVDGcount2 = 0;
double TightHalfMeVDGcount3 = 0;

for (int bin = 0; bin < 300; bin++){
BinHeightTightHalfMeVDG[bin] = MassHistTightHalfMeV->GetBinContent(bin + 1);
int xvalueHalfMeVDG = 2210.25 + 0.5*(bin);
FitHeightTightHalfMeVDG[bin] = round(GaussianTightHalfMeVDG->Eval(xvalueHalfMeVDG));

PullTightHalfMeVDG[bin] = (BinHeightTightHalfMeVDG[bin] - FitHeightTightHalfMeVDG[bin])/TMath::Sqrt(FitHeightTightHalfMeVDG[bin]);

if (PullTightHalfMeVDG[bin] > -1 && PullTightHalfMeVDG[bin] < 1){
TightHalfMeVDGcount1 += 1;
}

if (PullTightHalfMeVDG[bin] > -2 && PullTightHalfMeVDG[bin] < 2){
TightHalfMeVDGcount2 += 1;
}

if (PullTightHalfMeVDG[bin] > -3 && PullTightHalfMeVDG[bin] < 3){
TightHalfMeVDGcount3 += 1;
}
}
     pad2->cd();
     TGraph* PullPlotTightHalfMeVDG = new TGraph(300, PullxHalfMeV, PullTightHalfMeVDG);
     PullPlotTightHalfMeVDG->GetXaxis()->SetLimits(0.5,300.5);
     PullPlotTightHalfMeVDG->GetXaxis()->SetTickLength(0.);
     PullPlotTightHalfMeVDG->GetYaxis()->SetTickLength(0.);
     PullPlotTightHalfMeVDG->SetFillColor(38);
     PullPlotTightHalfMeVDG->GetYaxis()->SetTitle("Pull");
     PullPlotTightHalfMeVDG->GetYaxis()->CenterTitle();
     PullPlotTightHalfMeVDG->GetYaxis()->SetTitleSize(0.10);
     PullPlotTightHalfMeVDG->GetYaxis()->SetTitleOffset(0.2);
     PullPlotTightHalfMeVDG->GetXaxis()->SetLabelSize(0);
     PullPlotTightHalfMeVDG->GetYaxis()->SetLabelFont(42);
     PullPlotTightHalfMeVDG->GetYaxis()->SetLabelSize(0.06);
     PullPlotTightHalfMeVDG->SetTitle("");
     PullPlotTightHalfMeVDG->SetMinimum(-5);
     PullPlotTightHalfMeVDG->SetMaximum(5);
     PullPlotTightHalfMeVDG->Draw("AB");
     c1->Write("Lc Mass - Tight/HalfMeVDG");

ex1->cd();
   ex1->Clear();
   Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries in First Gaussian: %f Events", GaussianTightHalfMeVDG->GetParameter(0)));
   Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianTightHalfMeVDG->GetParError(0)));
   Tl.DrawLatex(0.1,0.8,Form("Number of Signal Entries in Second Gaussian: %f Events", GaussianTightHalfMeVDG->GetParameter(3)));
   Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianTightHalfMeVDG->GetParError(3)));
   Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianTightHalfMeVDG->GetParameter(1)));
   Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianTightHalfMeVDG->GetParError(1)));
   Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianTightHalfMeVDG->GetParameter(2)));
   Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianTightHalfMeVDG->GetParError(2)));
   Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianTightHalfMeVDG->GetParameter(4)));
   Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianTightHalfMeVDG->GetParError(4)));
   Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", TightHalfMeVDGcount1));
   Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", TightHalfMeVDGcount2));
   Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", TightHalfMeVDGcount3));
   ex1->Write("Tight Fit Values/HalfMeVDG");
c1->cd();
/////////////////////////////////////

TF1 *GaussianLoose1MeVDG = new TF1("GaussianLoose1MeVDG",DGOneMuTwoTotals1MeV,2200.,2400.,7);
GaussianLoose1MeVDG->SetParameter(0, 2000.);
GaussianLoose1MeVDG->SetParLimits(0, 0, 80000);
GaussianLoose1MeVDG->SetParameter(1, 2286);
GaussianLoose1MeVDG->SetParameter(2, 5);
GaussianLoose1MeVDG->SetParLimits(2, 0., 20.);
GaussianLoose1MeVDG->SetParameter(3, 2000.);
GaussianLoose1MeVDG->SetParLimits(3, 0, 80000);
GaussianLoose1MeVDG->SetParameter(4, 5);
GaussianLoose1MeVDG->SetParLimits(4, 0., 20.);
GaussianLoose1MeVDG->SetParameter(5, 0.);
GaussianLoose1MeVDG->SetParameter(6, 0.);

pad1->cd();
MassHistLoose1MeV->SetMinimum(0);
MassHistLoose1MeV->Fit("GaussianLoose1MeVDG");

int BinHeightLoose1MeVDG[150];
int FitHeightLoose1MeVDG[150];
double PullLoose1MeVDG[150];

double Loose1MeVDGcount1 = 0;
double Loose1MeVDGcount2 = 0;
double Loose1MeVDGcount3 = 0;

for (int bin = 0; bin < 150; bin++){
BinHeightLoose1MeVDG[bin] = MassHistLoose1MeV->GetBinContent(bin + 1);
Pullx1MeV[bin] = (bin + 1);
int xvalue1MeVDG = 2210.5 + 1*(bin);
FitHeightLoose1MeVDG[bin] = round(GaussianLoose1MeVDG->Eval(xvalue1MeVDG));
PullLoose1MeVDG[bin] = (BinHeightLoose1MeVDG[bin] - FitHeightLoose1MeVDG[bin])/TMath::Sqrt(FitHeightLoose1MeVDG[bin]);

if (PullLoose1MeVDG[bin] > -1 && PullLoose1MeVDG[bin] < 1){
  Loose1MeVDGcount1 += 1;
}

if (PullLoose1MeVDG[bin] > -2 && PullLoose1MeVDG[bin] < 2){
  Loose1MeVDGcount2 += 1;
}

if (PullLoose1MeVDG[bin] > -3 && PullLoose1MeVDG[bin] < 3){
  Loose1MeVDGcount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotLoose1MeVDG = new TGraph(150, Pullx1MeV, PullLoose1MeVDG);
PullPlotLoose1MeVDG->GetXaxis()->SetLimits(0.5,150.5);
PullPlotLoose1MeVDG->GetXaxis()->SetTickLength(0.);
PullPlotLoose1MeVDG->GetYaxis()->SetTickLength(0.);
PullPlotLoose1MeVDG->SetFillColor(38);
PullPlotLoose1MeVDG->GetYaxis()->SetTitle("Pull");
PullPlotLoose1MeVDG->GetYaxis()->CenterTitle();
PullPlotLoose1MeVDG->GetYaxis()->SetTitleSize(0.10);
PullPlotLoose1MeVDG->GetYaxis()->SetTitleOffset(0.2);
PullPlotLoose1MeVDG->GetXaxis()->SetLabelSize(0);
PullPlotLoose1MeVDG->GetYaxis()->SetLabelFont(42);
PullPlotLoose1MeVDG->GetYaxis()->SetLabelSize(0.06);
PullPlotLoose1MeVDG->SetTitle("");
PullPlotLoose1MeVDG->SetMinimum(-5);
PullPlotLoose1MeVDG->SetMaximum(5);
PullPlotLoose1MeVDG->Draw("AB");
      c1->Write("Lc Mass - Loose/1MeVDG");

ex1->cd();
    ex1->Clear();
   Tl.SetTextAlign(12);
   Tl.SetTextSize(0.04);
   Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries in First Gaussian: %f Events", GaussianLoose1MeVDG->GetParameter(0)));
   Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianLoose1MeVDG->GetParError(0)));
   Tl.DrawLatex(0.1,0.8,Form("Number of Signal Entries in Second Gaussian: %f Events", GaussianLoose1MeVDG->GetParameter(3)));
   Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianLoose1MeVDG->GetParError(3)));
   Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianLoose1MeVDG->GetParameter(1)));
   Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianLoose1MeVDG->GetParError(1)));
   Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianLoose1MeVDG->GetParameter(2)));
   Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianLoose1MeVDG->GetParError(2)));
   Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianLoose1MeVDG->GetParameter(4)));
   Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianLoose1MeVDG->GetParError(4)));
   Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", Loose1MeVDGcount1));
   Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", Loose1MeVDGcount2));
   Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", Loose1MeVDGcount3));
   ex1->Write("Loose Fit Values/1MeVDG");
c1->cd();
//////////////////////////////////////

TF1 *GaussianMid1MeVDG = new TF1("GaussianMid1MeVDG",DGOneMuTwoTotals1MeV,2200.,2400.,7);
GaussianMid1MeVDG->SetParameter(0, 2000.);
GaussianMid1MeVDG->SetParLimits(0, 0, 80000);
GaussianMid1MeVDG->SetParameter(1, 2286);
GaussianMid1MeVDG->SetParameter(2, 5);
GaussianMid1MeVDG->SetParLimits(2, 0., 20.);
GaussianMid1MeVDG->SetParameter(3, 2000.);
GaussianMid1MeVDG->SetParLimits(3, 0, 80000);
GaussianMid1MeVDG->SetParameter(4, 5);
GaussianMid1MeVDG->SetParLimits(4, 0., 20.);
GaussianMid1MeVDG->SetParameter(5, 0.);
GaussianMid1MeVDG->SetParameter(6, 0.);

pad1->cd();
MassHistMid1MeV->SetMinimum(0);
MassHistMid1MeV->Fit("GaussianMid1MeVDG");

int BinHeightMid1MeVDG[150];
int FitHeightMid1MeVDG[150];
double PullMid1MeVDG[150];

double   Mid1MeVDGcount1 = 0;
double   Mid1MeVDGcount2 = 0;
double   Mid1MeVDGcount3 = 0;

for (int bin = 0; bin < 150; bin++){
BinHeightMid1MeVDG[bin] = MassHistMid1MeV->GetBinContent(bin + 1);
int xvalue1MeVDG = 2210.5 + 1*(bin);
FitHeightMid1MeVDG[bin] = round(GaussianMid1MeVDG->Eval(xvalue1MeVDG));
PullMid1MeVDG[bin] = (BinHeightMid1MeVDG[bin] - FitHeightMid1MeVDG[bin])/TMath::Sqrt(FitHeightMid1MeVDG[bin]);

if (PullMid1MeVDG[bin] > -1 && PullMid1MeVDG[bin] < 1){
Mid1MeVDGcount1 += 1;
}

if (PullMid1MeVDG[bin] > -2 && PullMid1MeVDG[bin] < 2){
Mid1MeVDGcount2 += 1;
}

if (PullMid1MeVDG[bin] > -3 && PullMid1MeVDG[bin] < 3){
Mid1MeVDGcount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotMid1MeVDG = new TGraph(150, Pullx1MeV, PullMid1MeVDG);
PullPlotMid1MeVDG->GetXaxis()->SetLimits(0.5,150.5);
PullPlotMid1MeVDG->GetXaxis()->SetTickLength(0.);
PullPlotMid1MeVDG->GetYaxis()->SetTickLength(0.);
PullPlotMid1MeVDG->SetFillColor(38);
PullPlotMid1MeVDG->GetYaxis()->SetTitle("Pull");
PullPlotMid1MeVDG->GetYaxis()->CenterTitle();
PullPlotMid1MeVDG->GetYaxis()->SetTitleSize(0.10);
PullPlotMid1MeVDG->GetYaxis()->SetTitleOffset(0.2);
PullPlotMid1MeVDG->GetXaxis()->SetLabelSize(0);
PullPlotMid1MeVDG->GetYaxis()->SetLabelFont(42);
PullPlotMid1MeVDG->GetYaxis()->SetLabelSize(0.06);
PullPlotMid1MeVDG->SetTitle("");
PullPlotMid1MeVDG->SetMinimum(-5);
PullPlotMid1MeVDG->SetMaximum(5);
PullPlotMid1MeVDG->Draw("AB");

    c1->Write("Lc Mass - Mid/1MeVDG");

ex1->cd();
 ex1->Clear();
 Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries in First Gaussian: %f Events", GaussianMid1MeVDG->GetParameter(0)));
 Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianMid1MeVDG->GetParError(0)));
 Tl.DrawLatex(0.1,0.8,Form("Number of Signal Entries in Second Gaussian: %f Events", GaussianMid1MeVDG->GetParameter(3)));
 Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianMid1MeVDG->GetParError(3)));
 Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianMid1MeVDG->GetParameter(1)));
 Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianMid1MeVDG->GetParError(1)));
 Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianMid1MeVDG->GetParameter(2)));
 Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianMid1MeVDG->GetParError(2)));
 Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianMid1MeVDG->GetParameter(4)));
 Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianMid1MeVDG->GetParError(4)));
 Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", Mid1MeVDGcount1));
 Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", Mid1MeVDGcount2));
 Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", Mid1MeVDGcount3));
 ex1->Write("Mid Fit Values/1MeVDG");
c1->cd();
//////////////////////////////////////

TF1 *GaussianTight1MeVDG = new TF1("GaussianTight1MeVDG",DGOneMuTwoTotals1MeV,2200.,2400.,7);
GaussianTight1MeVDG->SetParameter(0, 2000.);
GaussianTight1MeVDG->SetParLimits(0, 0, 80000);
GaussianTight1MeVDG->SetParameter(1, 2286);
GaussianTight1MeVDG->SetParameter(2, 5);
GaussianTight1MeVDG->SetParLimits(2, 0., 20.);
GaussianTight1MeVDG->SetParameter(3, 2000.);
GaussianTight1MeVDG->SetParLimits(3, 0, 80000);
GaussianTight1MeVDG->SetParameter(4, 5);
GaussianTight1MeVDG->SetParLimits(4, 0., 20.);
GaussianTight1MeVDG->SetParameter(5, 0.);
GaussianTight1MeVDG->SetParameter(6, 0.);

pad1->cd();
MassHistTight1MeV->SetMinimum(0);
MassHistTight1MeV->Fit("GaussianTight1MeVDG");

int BinHeightTight1MeVDG[150];
int FitHeightTight1MeVDG[150];
double PullTight1MeVDG[150];

double Tight1MeVDGcount1 = 0;
double Tight1MeVDGcount2 = 0;
double Tight1MeVDGcount3 = 0;

for (int bin = 0; bin < 150; bin++){
BinHeightTight1MeVDG[bin] = MassHistTight1MeV->GetBinContent(bin + 1);
int xvalue1MeVDG = 2210.5 + 1*(bin);
FitHeightTight1MeVDG[bin] = round(GaussianTight1MeVDG->Eval(xvalue1MeVDG));

PullTight1MeVDG[bin] = (BinHeightTight1MeVDG[bin] - FitHeightTight1MeVDG[bin])/TMath::Sqrt(FitHeightTight1MeVDG[bin]);

if (PullTight1MeVDG[bin] > -1 && PullTight1MeVDG[bin] < 1){
Tight1MeVDGcount1 += 1;
}

if (PullTight1MeVDG[bin] > -2 && PullTight1MeVDG[bin] < 2){
Tight1MeVDGcount2 += 1;
}

if (PullTight1MeVDG[bin] > -3 && PullTight1MeVDG[bin] < 3){
Tight1MeVDGcount3 += 1;
}
}
     pad2->cd();
     TGraph* PullPlotTight1MeVDG = new TGraph(150, Pullx1MeV, PullTight1MeVDG);
     PullPlotTight1MeVDG->GetXaxis()->SetLimits(0.5,150.5);
     PullPlotTight1MeVDG->GetXaxis()->SetTickLength(0.);
     PullPlotTight1MeVDG->GetYaxis()->SetTickLength(0.);
     PullPlotTight1MeVDG->SetFillColor(38);
     PullPlotTight1MeVDG->GetYaxis()->SetTitle("Pull");
     PullPlotTight1MeVDG->GetYaxis()->CenterTitle();
     PullPlotTight1MeVDG->GetYaxis()->SetTitleSize(0.10);
     PullPlotTight1MeVDG->GetYaxis()->SetTitleOffset(0.2);
     PullPlotTight1MeVDG->GetXaxis()->SetLabelSize(0);
     PullPlotTight1MeVDG->GetYaxis()->SetLabelFont(42);
     PullPlotTight1MeVDG->GetYaxis()->SetLabelSize(0.06);
     PullPlotTight1MeVDG->SetTitle("");
     PullPlotTight1MeVDG->SetMinimum(-5);
     PullPlotTight1MeVDG->SetMaximum(5);
     PullPlotTight1MeVDG->Draw("AB");
     c1->Write("Lc Mass - Tight/1MeVDG");

ex1->cd();
   ex1->Clear();
Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries in First Gaussian: %f Events", GaussianTight1MeVDG->GetParameter(0)));
Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianTight1MeVDG->GetParError(0)));
Tl.DrawLatex(0.1,0.8,Form("Number of Signal Entries in Second Gaussian: %f Events", GaussianTight1MeVDG->GetParameter(3)));
Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianTight1MeVDG->GetParError(3)));
Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianTight1MeVDG->GetParameter(1)));
Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianTight1MeVDG->GetParError(1)));
Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianTight1MeVDG->GetParameter(2)));
Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianTight1MeVDG->GetParError(2)));
Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianTight1MeVDG->GetParameter(4)));
Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianTight1MeVDG->GetParError(4)));
Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", Tight1MeVDGcount1));
Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", Tight1MeVDGcount2));
Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", Tight1MeVDGcount3));
   ex1->Write("Tight Fit Values/1MeVDG");
c1->cd();
/////////////////////////////

        File->Close();
}
