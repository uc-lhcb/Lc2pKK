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
#include "fit2MeV_Gaussian.C"
#include "DGOneMuTwoTotals1MeV.C"
#include "DGOneMuTwoTotals2MeV.C"

TH1D * MassHistLoose2MeV = nullptr;
TH1D * MassHistMid2MeV = nullptr;
TH1D * MassHistTight2MeV = nullptr;

TH1D * MassHistLoose1MeV = nullptr;
TH1D * MassHistMid1MeV = nullptr;
TH1D * MassHistTight1MeV = nullptr;

TFile * File = nullptr;

TCanvas * c1 = nullptr;
TCanvas * ex1 = nullptr;

void FirstCuts2017::Begin(TTree * /*tree*/)
{
   TString option = GetOption();

   MassHistLoose2MeV = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 75, 2210, 2360);
   MassHistLoose2MeV->GetXaxis()->SetTitle("MeV");
   MassHistLoose2MeV->GetYaxis()->SetTitle("Events Per 2 MeV");

   MassHistMid2MeV = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 75, 2210, 2360);
   MassHistMid2MeV->GetXaxis()->SetTitle("MeV");
   MassHistMid2MeV->GetYaxis()->SetTitle("Events Per 2 MeV");

   MassHistTight2MeV = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 75, 2210, 2360);
   MassHistTight2MeV->GetXaxis()->SetTitle("MeV");
   MassHistTight2MeV->GetYaxis()->SetTitle("Events Per 2 MeV");

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
   && (*Proton_PT > 850)
   && (*Kminus_PT > 700)
   && (*Kplus_PT > 700)
   );

   bool MidCuts = (
      (((*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp)) > 0.9)
   && (*Proton_PT > 850)
   && (*Kminus_PT > 700)
   && (*Kplus_PT > 700)
   );

   bool TightCuts = (
      (((*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp)) > 0.95)
   && (*Proton_PT > 850)
   && (*Kminus_PT > 700)
   && (*Kplus_PT > 700)
   );

   if (MidCuts){
     MassHistMid2MeV->Fill(*Lcplus_M);
     MassHistMid1MeV->Fill(*Lcplus_M);
   }

   if (LooseCuts){
     MassHistLoose2MeV->Fill(*Lcplus_M);
     MassHistLoose1MeV->Fill(*Lcplus_M);
   }

   if (TightCuts){
     MassHistTight2MeV->Fill(*Lcplus_M);
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

double Pullx2MeV[75];
double Pullx1MeV[150];

TPad *pad1 = new TPad("pad1","pad1",0,0.33,1,1);
TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.33);
pad2->SetTopMargin(0.03030303);
pad1->Draw();
pad2->Draw();

/////////////////////////////
TF1 *GaussianLoose2MeVSG = new TF1("GaussianLoose2MeVSG",fit2MeV_Gaussian,2100.,2500.,5);
GaussianLoose2MeVSG->SetParameter(0,400.);
GaussianLoose2MeVSG->SetParameter(1,2287);
GaussianLoose2MeVSG->SetParameter(2, 6);
GaussianLoose2MeVSG->SetParLimits(2, 0.,20.);
GaussianLoose2MeVSG->SetParameter(3, 0.);
GaussianLoose2MeVSG->SetParameter(4, 0.);

pad1->cd();
MassHistLoose2MeV->SetMinimum(0);
MassHistLoose2MeV->Fit("GaussianLoose2MeVSG");

int BinHeightLoose2MeVSG[75];
int FitHeightLoose2MeVSG[75];
double PullLoose2MeVSG[75];

double Loose2MeVSGcount1 = 0;
double Loose2MeVSGcount2 = 0;
double Loose2MeVSGcount3 = 0;

for (int bin = 0; bin < 75; bin++){
BinHeightLoose2MeVSG[bin] = MassHistLoose2MeV->GetBinContent(bin + 1);
Pullx2MeV[bin] = (bin + 1);
int xvalue2MeVSG = 2211 + 2*(bin);
FitHeightLoose2MeVSG[bin] = round(GaussianLoose2MeVSG->Eval(xvalue2MeVSG));
PullLoose2MeVSG[bin] = (BinHeightLoose2MeVSG[bin] - FitHeightLoose2MeVSG[bin])/TMath::Sqrt(FitHeightLoose2MeVSG[bin]);

if (PullLoose2MeVSG[bin] > -1 && PullLoose2MeVSG[bin] < 1){
  Loose2MeVSGcount1 += 1;
}

if (PullLoose2MeVSG[bin] > -2 && PullLoose2MeVSG[bin] < 2){
  Loose2MeVSGcount2 += 1;
}

if (PullLoose2MeVSG[bin] > -3 && PullLoose2MeVSG[bin] < 3){
  Loose2MeVSGcount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotLoose2MeVSG = new TGraph(75, Pullx2MeV, PullLoose2MeVSG);
PullPlotLoose2MeVSG->GetXaxis()->SetLimits(0.5,75.5);
PullPlotLoose2MeVSG->GetXaxis()->SetTickLength(0.);
PullPlotLoose2MeVSG->GetYaxis()->SetTickLength(0.);
PullPlotLoose2MeVSG->SetFillColor(38);
PullPlotLoose2MeVSG->GetYaxis()->SetTitle("Pull");
PullPlotLoose2MeVSG->GetYaxis()->CenterTitle();
PullPlotLoose2MeVSG->GetYaxis()->SetTitleSize(0.10);
PullPlotLoose2MeVSG->GetYaxis()->SetTitleOffset(0.2);
PullPlotLoose2MeVSG->GetXaxis()->SetLabelSize(0);
PullPlotLoose2MeVSG->GetYaxis()->SetLabelFont(42);
PullPlotLoose2MeVSG->GetYaxis()->SetLabelSize(0.06);
PullPlotLoose2MeVSG->SetTitle("");
PullPlotLoose2MeVSG->SetMinimum(-5);
PullPlotLoose2MeVSG->SetMaximum(5);
PullPlotLoose2MeVSG->Draw("AB");
      c1->Write("Lc Mass - Loose/2MeVSG");

ex1->cd();
   TLatex Tl;
   Tl.SetTextAlign(12);
   Tl.SetTextSize(0.04);
   Tl.DrawLatex(0.1,0.9,Form("Number of Signal Entries: %f Events", GaussianLoose2MeVSG->GetParameter(0)));
   Tl.DrawLatex(0.1,0.85,Form("Error: %f Events", GaussianLoose2MeVSG->GetParError(0)));
   Tl.DrawLatex(0.1,0.7,Form("Mean Value: %f MeV", GaussianLoose2MeVSG->GetParameter(1)));
   Tl.DrawLatex(0.1,0.65,Form("Error: %f MeV", GaussianLoose2MeVSG->GetParError(1)));
   Tl.DrawLatex(0.1,0.5,Form("Sigma: %f MeV", GaussianLoose2MeVSG->GetParameter(2)));
   Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianLoose2MeVSG->GetParError(2)));
   Tl.DrawLatex(0.1,0.3,Form("Bins Between -1 & 1 %f Bins", Loose2MeVSGcount1));
   Tl.DrawLatex(0.1,0.2,Form("Bins Between -2 & 2 %f Bins", Loose2MeVSGcount2));
   Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", Loose2MeVSGcount3));
   ex1->Write("Loose Fit Values/2MeVSG");
c1->cd();
///////////////////////////////////////////////////////

TF1 *GaussianMid2MeVSG = new TF1("GaussianMid2MeVSG",fit2MeV_Gaussian,2100.,2500.,5);
GaussianMid2MeVSG->SetParameter(0,400.);
GaussianMid2MeVSG->SetParameter(1,2287);
GaussianMid2MeVSG->SetParameter(2, 6);
GaussianMid2MeVSG->SetParLimits(2, 0.,20.);
GaussianMid2MeVSG->SetParameter(3, 0.);
GaussianMid2MeVSG->SetParameter(4, 0.);

  pad1->cd();
  MassHistMid2MeV->SetMinimum(0);
  MassHistMid2MeV->Fit("GaussianMid2MeVSG");

  int BinHeightMid2MeVSG[75];
  int FitHeightMid2MeVSG[75];
  double PullMid2MeVSG[75];

double   Mid2MeVSGcount1 = 0;
double   Mid2MeVSGcount2 = 0;
double   Mid2MeVSGcount3 = 0;

  for (int bin = 0; bin < 75; bin++){
  BinHeightMid2MeVSG[bin] = MassHistMid2MeV->GetBinContent(bin + 1);
  int xvalue2MeVSG = 2211 + 2*(bin);
  FitHeightMid2MeVSG[bin] = round(GaussianMid2MeVSG->Eval(xvalue2MeVSG));
  PullMid2MeVSG[bin] = (BinHeightMid2MeVSG[bin] - FitHeightMid2MeVSG[bin])/TMath::Sqrt(FitHeightMid2MeVSG[bin]);

  if (PullMid2MeVSG[bin] > -1 && PullMid2MeVSG[bin] < 1){
  Mid2MeVSGcount1 += 1;
  }

  if (PullMid2MeVSG[bin] > -2 && PullMid2MeVSG[bin] < 2){
  Mid2MeVSGcount2 += 1;
  }

  if (PullMid2MeVSG[bin] > -3 && PullMid2MeVSG[bin] < 3){
  Mid2MeVSGcount3 += 1;
  }
  }

  pad2->cd();
TGraph* PullPlotMid2MeVSG = new TGraph(75, Pullx2MeV, PullMid2MeVSG);
PullPlotMid2MeVSG->GetXaxis()->SetLimits(0.5,75.5);
PullPlotMid2MeVSG->GetXaxis()->SetTickLength(0.);
PullPlotMid2MeVSG->GetYaxis()->SetTickLength(0.);
PullPlotMid2MeVSG->SetFillColor(38);
PullPlotMid2MeVSG->GetYaxis()->SetTitle("Pull");
PullPlotMid2MeVSG->GetYaxis()->CenterTitle();
PullPlotMid2MeVSG->GetYaxis()->SetTitleSize(0.10);
PullPlotMid2MeVSG->GetYaxis()->SetTitleOffset(0.2);
PullPlotMid2MeVSG->GetXaxis()->SetLabelSize(0);
PullPlotMid2MeVSG->GetYaxis()->SetLabelFont(42);
PullPlotMid2MeVSG->GetYaxis()->SetLabelSize(0.06);
PullPlotMid2MeVSG->SetTitle("");
PullPlotMid2MeVSG->SetMinimum(-5);
PullPlotMid2MeVSG->SetMaximum(5);
PullPlotMid2MeVSG->Draw("AB");

      c1->Write("Lc Mass - Mid/2MeVSG");

ex1->cd();
   ex1->Clear();
Tl.DrawLatex(0.1,0.9,Form("Number of Signal Entries: %f Events", GaussianMid2MeVSG->GetParameter(0)));
Tl.DrawLatex(0.1,0.85,Form("Error: %f Events", GaussianMid2MeVSG->GetParError(0)));
Tl.DrawLatex(0.1,0.7,Form("Mean Value: %f MeV", GaussianMid2MeVSG->GetParameter(1)));
Tl.DrawLatex(0.1,0.65,Form("Error: %f MeV", GaussianMid2MeVSG->GetParError(1)));
Tl.DrawLatex(0.1,0.5,Form("Sigma: %f MeV", GaussianMid2MeVSG->GetParameter(2)));
Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianMid2MeVSG->GetParError(2)));
Tl.DrawLatex(0.1,0.3,Form("Bins Between -1 & 1 %f Bins", Mid2MeVSGcount1));
Tl.DrawLatex(0.1,0.2,Form("Bins Between -2 & 2 %f Bins", Mid2MeVSGcount2));
Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", Mid2MeVSGcount3));
   ex1->Write("Mid Fit Values/2MeVSG");
c1->cd();
//////////////////////////////////////////////////////

TF1 *GaussianTight2MeVSG = new TF1("GaussianTight2MeVSG",fit2MeV_Gaussian,2100.,2500.,5);
GaussianTight2MeVSG->SetParameter(0,400.);
GaussianTight2MeVSG->SetParameter(1,2286);
GaussianTight2MeVSG->SetParameter(2, 6);
GaussianTight2MeVSG->SetParLimits(2, 0.,20.);
GaussianTight2MeVSG->SetParameter(3, 0.);
GaussianTight2MeVSG->SetParameter(4, 0.);

pad1->cd();
MassHistTight2MeV->SetMinimum(0);
MassHistTight2MeV->Fit("GaussianTight2MeVSG");

int BinHeightTight2MeVSG[75];
int FitHeightTight2MeVSG[75];
double PullTight2MeVSG[75];

double Tight2MeVSGcount1 = 0;
double Tight2MeVSGcount2 = 0;
double Tight2MeVSGcount3 = 0;

for (int bin = 0; bin < 75; bin++){
BinHeightTight2MeVSG[bin] = MassHistTight2MeV->GetBinContent(bin + 1);
int xvalue2MeVSG = 2211 + 2*(bin);
FitHeightTight2MeVSG[bin] = round(GaussianTight2MeVSG->Eval(xvalue2MeVSG));

PullTight2MeVSG[bin] = (BinHeightTight2MeVSG[bin] - FitHeightTight2MeVSG[bin])/TMath::Sqrt(FitHeightTight2MeVSG[bin]);

if (PullTight2MeVSG[bin] > -1 && PullTight2MeVSG[bin] < 1){
Tight2MeVSGcount1 += 1;
}

if (PullTight2MeVSG[bin] > -2 && PullTight2MeVSG[bin] < 2){
Tight2MeVSGcount2 += 1;
}

if (PullTight2MeVSG[bin] > -3 && PullTight2MeVSG[bin] < 3){
Tight2MeVSGcount3 += 1;
}
}
     pad2->cd();
     TGraph* PullPlotTight2MeVSG = new TGraph(75, Pullx2MeV, PullTight2MeVSG);
     PullPlotTight2MeVSG->GetXaxis()->SetLimits(0.5,75.5);
     PullPlotTight2MeVSG->GetXaxis()->SetTickLength(0.);
     PullPlotTight2MeVSG->GetYaxis()->SetTickLength(0.);
     PullPlotTight2MeVSG->SetFillColor(38);
     PullPlotTight2MeVSG->GetYaxis()->SetTitle("Pull");
     PullPlotTight2MeVSG->GetYaxis()->CenterTitle();
     PullPlotTight2MeVSG->GetYaxis()->SetTitleSize(0.10);
     PullPlotTight2MeVSG->GetYaxis()->SetTitleOffset(0.2);
     PullPlotTight2MeVSG->GetXaxis()->SetLabelSize(0);
     PullPlotTight2MeVSG->GetYaxis()->SetLabelFont(42);
     PullPlotTight2MeVSG->GetYaxis()->SetLabelSize(0.06);
     PullPlotTight2MeVSG->SetTitle("");
     PullPlotTight2MeVSG->SetMinimum(-5);
     PullPlotTight2MeVSG->SetMaximum(5);
     PullPlotTight2MeVSG->Draw("AB");
     c1->Write("Lc Mass - Tight/2MeVSG");

ex1->cd();
   ex1->Clear();
Tl.DrawLatex(0.1,0.9,Form("Number of Signal Entries: %f Events", GaussianTight2MeVSG->GetParameter(0)));
Tl.DrawLatex(0.1,0.85,Form("Error: %f Events", GaussianTight2MeVSG->GetParError(0)));
Tl.DrawLatex(0.1,0.7,Form("Mean Value: %f MeV", GaussianTight2MeVSG->GetParameter(1)));
Tl.DrawLatex(0.1,0.65,Form("Error: %f MeV", GaussianTight2MeVSG->GetParError(1)));
Tl.DrawLatex(0.1,0.5,Form("Sigma: %f MeV", GaussianTight2MeVSG->GetParameter(2)));
Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianTight2MeVSG->GetParError(2)));
Tl.DrawLatex(0.1,0.3,Form("Bins Between -1 & 1 %f Bins", Tight2MeVSGcount1));
Tl.DrawLatex(0.1,0.2,Form("Bins Between -2 & 2 %f Bins", Tight2MeVSGcount2));
Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", Tight2MeVSGcount3));
   ex1->Write("Tight Fit Values/2MeVSG");
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
Pullx1MeVSG[bin] = (bin + 1);
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
   TLatex Tl;
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

        File->Close();
}
