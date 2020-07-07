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
#include "DGOneMuOneTotal1MeV.C"
#include "DGOneMuOneTotalHalfMeV.C"
#include "DGTwoMuOneTotal1MeV.C"
#include "DGTwoMuOneTotalHalfMeV.C"

TH1D * MassHistLooseHalfMeV = nullptr;
TH1D * MassHistMidHalfMeV = nullptr;
TH1D * MassHistTightHalfMeV = nullptr;

TH1D * MassHistLoose1MeV = nullptr;
TH1D * MassHistMid1MeV = nullptr;
TH1D * MassHistTight1MeV = nullptr;

TH1D * LcLowP = nullptr;
TH1D * LcMidLowP = nullptr;
TH1D * LcMidHighP = nullptr;
TH1D * LcHighP = nullptr;
TH1D * LcPDistribution = nullptr;

TH1D * PolarityMagUp = nullptr;
TH1D * PolarityMagDown = nullptr;

TH1D * Particle = nullptr;
TH1D * AntiParticle = nullptr;

TGraphErrors * gLcP = nullptr;
TGraphErrors * gXiP = nullptr;
TGraphErrors * gPolarity = nullptr;
TGraphErrors * gPID = nullptr;

TGraphErrors * gLcPDG = nullptr;
TGraphErrors * gXiPDG = nullptr;
TGraphErrors * gPolarityDG = nullptr;
TGraphErrors * gPIDDG = nullptr;

TFile * File = nullptr;

TCanvas * c1 = nullptr;
TCanvas * ex1 = nullptr;

void FirstCuts2017::Begin(TTree * /*tree*/)
{
   TString option = GetOption();

   MassHistLooseHalfMeV = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 300, 2210, 2360);
   MassHistLooseHalfMeV->GetXaxis()->SetTitle("MeV");
   MassHistLooseHalfMeV->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   MassHistMidHalfMeV = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 300, 2210, 2360);
   MassHistMidHalfMeV->GetXaxis()->SetTitle("MeV");
   MassHistMidHalfMeV->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   MassHistTightHalfMeV = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 300, 2210, 2360);
   MassHistTightHalfMeV->GetXaxis()->SetTitle("MeV");
   MassHistTightHalfMeV->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   MassHistLoose1MeV = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 150, 2210, 2360);
   MassHistLoose1MeV->GetXaxis()->SetTitle("MeV");
   MassHistLoose1MeV->GetYaxis()->SetTitle("Events Per 1 MeV");

   MassHistMid1MeV = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 150, 2210, 2360);
   MassHistMid1MeV->GetXaxis()->SetTitle("MeV");
   MassHistMid1MeV->GetYaxis()->SetTitle("Events Per 1 MeV");

   MassHistTight1MeV = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 150, 2210, 2360);
   MassHistTight1MeV->GetXaxis()->SetTitle("MeV");
   MassHistTight1MeV->GetYaxis()->SetTitle("Events Per 1 MeV");

            LcLowP = new TH1D("Figures of Merit", "LambdaC Mass - Low LcP", 300, 2210, 2360);
            LcLowP->GetXaxis()->SetTitle("MeV");
            LcLowP->GetYaxis()->SetTitle("Events Per 1/2 MeV");

            LcMidLowP = new TH1D("Figures of Merit", "LambdaC Mass - MidLow LcP", 300, 2210, 2360);
            LcMidLowP->GetXaxis()->SetTitle("MeV");
            LcMidLowP->GetYaxis()->SetTitle("Events Per 1/2 MeV");

            LcMidHighP = new TH1D("Figures of Merit", "LambdaC Mass - MidHigh LcP", 300, 2210, 2360);
            LcMidHighP->GetXaxis()->SetTitle("MeV");
            LcMidHighP->GetYaxis()->SetTitle("Events Per 1/2 MeV");

            LcHighP = new TH1D("Figures of Merit", "LambdaC Mass - High LcP", 300, 2210, 2360);
            LcHighP->GetXaxis()->SetTitle("MeV");
            LcHighP->GetYaxis()->SetTitle("Events Per 1/2 MeV");

            LcPDistribution = new TH1D("Figures of Merit", "LcP Distribution After Cuts", 300, 0, 250000);
            LcPDistribution->GetXaxis()->SetTitle("MeV");
            LcPDistribution->GetYaxis()->SetTitle("Events Per 2500 MeV");
   
             PolarityMagDown = new TH1D("Figures of Merit", "LambdaC Mass - MagnetDown", 300, 2210, 2360);
            PolarityMagDown->GetXaxis()->SetTitle("MeV");
            PolarityMagDown->GetYaxis()->SetTitle("Events Per 1/2 MeV");

            PolarityMagUp = new TH1D("Figures of Merit", "LambdaC Mass - MagnetUp", 300, 2210, 2360);
            PolarityMagUp->GetXaxis()->SetTitle("MeV");
            PolarityMagUp->GetYaxis()->SetTitle("Events Per 1/2 MeV");

            Particle = new TH1D("Figures of Merit", "LambdaC Mass - LambdaC Baryon", 300, 2210, 2360);
            Particle->GetXaxis()->SetTitle("MeV");
            Particle->GetYaxis()->SetTitle("Events Per 1/2 MeV");

            AntiParticle = new TH1D("Figures of Merit", "LambdaC Mass - LambdaC AntiBaryon", 300, 2210, 2360);
            AntiParticle->GetXaxis()->SetTitle("MeV");
            AntiParticle->GetYaxis()->SetTitle("Events Per 1/2 MeV");
   
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
     LcPDistribution->Fill(*Lcplus_P);
   }

 /////////////////////////////////////////  
   
     bool LcLowPCut = (
     (*Lcplus_P < 70000.)
   );

   bool LcMidLowPCut = (
     (*Lcplus_P > 70000. && *Lcplus_P < 88500.)
   );

   bool LcMidHighPCut = (
     (*Lcplus_P > 88500. && *Lcplus_P < 112000.)
   );

   bool LcHighPCut = (
     (*Lcplus_P > 112000.)
   );

   bool MagDown = (
      (*Polarity < 0.)
   );

   bool MagUp = (
      (*Polarity > 0.)
   );

   bool Particles = (
      (*Lcplus_ID > 0.)
   );

   bool AntiParticles = (
      (*Lcplus_ID < 0.)
   );
  
 ///////////////////
   
 if (TightCuts && LcLowPCut){
   LcLowP->Fill(*Lcplus_M);}
  
    if (TightCuts && LcMidLowPCut){
   LcMidLowP->Fill(*Lcplus_M);}
 
       if (TightCuts && LcMidHighPCut){
   LcMidHighP->Fill(*Lcplus_M);}
   
          if (TightCuts && LcHighPCut){
   LcHighP->Fill(*Lcplus_M);}
   
   ///////////////
   
  if (TightCuts && MagDown){
   PolarityMagDown->Fill(*Lcplus_M);}
  
    if (TightCuts && MagUp){
   PolarityMagUp->Fill(*Lcplus_M);}
 
  /////////////// 
   
       if (TightCuts && Particles){
   Particle->Fill(*Lcplus_M);}
   
          if (TightCuts && AntiParticles){
   AntiParticle->Fill(*Lcplus_M);}  
   
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
TF1 *GaussianLooseHalfMeVDG1Mu = new TF1("GaussianLooseHalfMeVDG1Mu",DGOneMuOneTotalHalfMeV,2200.,2400.,7);
GaussianLooseHalfMeVDG1Mu->SetParameter(0, 0.5);
GaussianLooseHalfMeVDG1Mu->SetParameter(1, 10000);
GaussianLooseHalfMeVDG1Mu->SetParameter(2, 2287.);
GaussianLooseHalfMeVDG1Mu->SetParameter(3, 5);
GaussianLooseHalfMeVDG1Mu->SetParameter(4, 5);
GaussianLooseHalfMeVDG1Mu->SetParLimits(3, 0., 20.);
GaussianLooseHalfMeVDG1Mu->SetParLimits(4, 0., 20.);
GaussianLooseHalfMeVDG1Mu->SetParameter(5, 0.);
GaussianLooseHalfMeVDG1Mu->SetParameter(6, 0.);

pad1->cd();
MassHistLooseHalfMeV->SetMinimum(0);
MassHistLooseHalfMeV->Fit("GaussianLooseHalfMeVDG1Mu");

int BinHeightLooseHalfMeVDG1Mu[300];
int FitHeightLooseHalfMeVDG1Mu[300];
double PullLooseHalfMeVDG1Mu[300];

double LooseHalfMeVDG1Mucount1 = 0;
double LooseHalfMeVDG1Mucount2 = 0;
double LooseHalfMeVDG1Mucount3 = 0;

for (int bin = 0; bin < 300; bin++){
BinHeightLooseHalfMeVDG1Mu[bin] = MassHistLooseHalfMeV->GetBinContent(bin + 1);
PullxHalfMeV[bin] = (bin + 1);
int xvalueHalfMeVDG1Mu = 2210.25 + 0.5*(bin);
FitHeightLooseHalfMeVDG1Mu[bin] = round(GaussianLooseHalfMeVDG1Mu->Eval(xvalueHalfMeVDG1Mu));
PullLooseHalfMeVDG1Mu[bin] = (BinHeightLooseHalfMeVDG1Mu[bin] - FitHeightLooseHalfMeVDG1Mu[bin])/TMath::Sqrt(FitHeightLooseHalfMeVDG1Mu[bin]);

if (PullLooseHalfMeVDG1Mu[bin] > -1 && PullLooseHalfMeVDG1Mu[bin] < 1){
  LooseHalfMeVDG1Mucount1 += 1;
}

if (PullLooseHalfMeVDG1Mu[bin] > -2 && PullLooseHalfMeVDG1Mu[bin] < 2){
  LooseHalfMeVDG1Mucount2 += 1;
}

if (PullLooseHalfMeVDG1Mu[bin] > -3 && PullLooseHalfMeVDG1Mu[bin] < 3){
  LooseHalfMeVDG1Mucount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotLooseHalfMeVDG1Mu = new TGraph(300, PullxHalfMeV, PullLooseHalfMeVDG1Mu);
PullPlotLooseHalfMeVDG1Mu->GetXaxis()->SetLimits(0.5,300.5);
PullPlotLooseHalfMeVDG1Mu->GetXaxis()->SetTickLength(0.);
PullPlotLooseHalfMeVDG1Mu->GetYaxis()->SetTickLength(0.);
PullPlotLooseHalfMeVDG1Mu->SetFillColor(38);
PullPlotLooseHalfMeVDG1Mu->GetYaxis()->SetTitle("Pull");
PullPlotLooseHalfMeVDG1Mu->GetYaxis()->CenterTitle();
PullPlotLooseHalfMeVDG1Mu->GetYaxis()->SetTitleSize(0.10);
PullPlotLooseHalfMeVDG1Mu->GetYaxis()->SetTitleOffset(0.2);
PullPlotLooseHalfMeVDG1Mu->GetXaxis()->SetLabelSize(0);
PullPlotLooseHalfMeVDG1Mu->GetYaxis()->SetLabelFont(42);
PullPlotLooseHalfMeVDG1Mu->GetYaxis()->SetLabelSize(0.06);
PullPlotLooseHalfMeVDG1Mu->SetTitle("");
PullPlotLooseHalfMeVDG1Mu->SetMinimum(-5);
PullPlotLooseHalfMeVDG1Mu->SetMaximum(5);
PullPlotLooseHalfMeVDG1Mu->Draw("AB");
      c1->Write("Lc Mass - Loose/HalfMeVDG1Mu");

ex1->cd();
 ex1->Clear();
   Tl.SetTextAlign(12);
   Tl.SetTextSize(0.04);
   Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianLooseHalfMeVDG1Mu->GetParameter(1)));
   Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianLooseHalfMeVDG1Mu->GetParError(1)));
   Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianLooseHalfMeVDG1Mu->GetParameter(0)));
   Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianLooseHalfMeVDG1Mu->GetParError(0)));
   Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianLooseHalfMeVDG1Mu->GetParameter(2)));
   Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianLooseHalfMeVDG1Mu->GetParError(2)));
   Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianLooseHalfMeVDG1Mu->GetParameter(3)));
   Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianLooseHalfMeVDG1Mu->GetParError(3)));
   Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianLooseHalfMeVDG1Mu->GetParameter(4)));
   Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianLooseHalfMeVDG1Mu->GetParError(4)));
   Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", LooseHalfMeVDG1Mucount1));
   Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", LooseHalfMeVDG1Mucount2));
   Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", LooseHalfMeVDG1Mucount3));
   ex1->Write("Loose Fit Values/HalfMeVDG1Mu");
c1->cd();
/////////////////////////////

TF1 *GaussianMidHalfMeVDG1Mu = new TF1("GaussianMidHalfMeVDG1Mu",DGOneMuOneTotalHalfMeV,2200.,2400.,7);
GaussianMidHalfMeVDG1Mu->SetParameter(0, 0.5);
GaussianMidHalfMeVDG1Mu->SetParameter(1, 10000);
GaussianMidHalfMeVDG1Mu->SetParameter(2, 2287.);
GaussianMidHalfMeVDG1Mu->SetParameter(3, 5);
GaussianMidHalfMeVDG1Mu->SetParameter(4, 5);
GaussianMidHalfMeVDG1Mu->SetParLimits(3, 0., 20.);
GaussianMidHalfMeVDG1Mu->SetParLimits(4, 0., 20.);
GaussianMidHalfMeVDG1Mu->SetParameter(5, 0.);
GaussianMidHalfMeVDG1Mu->SetParameter(6, 0.);

pad1->cd();
MassHistMidHalfMeV->SetMinimum(0);
MassHistMidHalfMeV->Fit("GaussianMidHalfMeVDG1Mu");

int BinHeightMidHalfMeVDG1Mu[300];
int FitHeightMidHalfMeVDG1Mu[300];
double PullMidHalfMeVDG1Mu[300];

double   MidHalfMeVDG1Mucount1 = 0;
double   MidHalfMeVDG1Mucount2 = 0;
double   MidHalfMeVDG1Mucount3 = 0;

for (int bin = 0; bin < 300; bin++){
BinHeightMidHalfMeVDG1Mu[bin] = MassHistMidHalfMeV->GetBinContent(bin + 1);
int xvalueHalfMeVDG1Mu = 2210.25 + 0.5*(bin);
FitHeightMidHalfMeVDG1Mu[bin] = round(GaussianMidHalfMeVDG1Mu->Eval(xvalueHalfMeVDG1Mu));
PullMidHalfMeVDG1Mu[bin] = (BinHeightMidHalfMeVDG1Mu[bin] - FitHeightMidHalfMeVDG1Mu[bin])/TMath::Sqrt(FitHeightMidHalfMeVDG1Mu[bin]);

if (PullMidHalfMeVDG1Mu[bin] > -1 && PullMidHalfMeVDG1Mu[bin] < 1){
MidHalfMeVDG1Mucount1 += 1;
}

if (PullMidHalfMeVDG1Mu[bin] > -2 && PullMidHalfMeVDG1Mu[bin] < 2){
MidHalfMeVDG1Mucount2 += 1;
}

if (PullMidHalfMeVDG1Mu[bin] > -3 && PullMidHalfMeVDG1Mu[bin] < 3){
MidHalfMeVDG1Mucount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotMidHalfMeVDG1Mu = new TGraph(300, PullxHalfMeV, PullMidHalfMeVDG1Mu);
PullPlotMidHalfMeVDG1Mu->GetXaxis()->SetLimits(0.5,300.5);
PullPlotMidHalfMeVDG1Mu->GetXaxis()->SetTickLength(0.);
PullPlotMidHalfMeVDG1Mu->GetYaxis()->SetTickLength(0.);
PullPlotMidHalfMeVDG1Mu->SetFillColor(38);
PullPlotMidHalfMeVDG1Mu->GetYaxis()->SetTitle("Pull");
PullPlotMidHalfMeVDG1Mu->GetYaxis()->CenterTitle();
PullPlotMidHalfMeVDG1Mu->GetYaxis()->SetTitleSize(0.10);
PullPlotMidHalfMeVDG1Mu->GetYaxis()->SetTitleOffset(0.2);
PullPlotMidHalfMeVDG1Mu->GetXaxis()->SetLabelSize(0);
PullPlotMidHalfMeVDG1Mu->GetYaxis()->SetLabelFont(42);
PullPlotMidHalfMeVDG1Mu->GetYaxis()->SetLabelSize(0.06);
PullPlotMidHalfMeVDG1Mu->SetTitle("");
PullPlotMidHalfMeVDG1Mu->SetMinimum(-5);
PullPlotMidHalfMeVDG1Mu->SetMaximum(5);
PullPlotMidHalfMeVDG1Mu->Draw("AB");

    c1->Write("Lc Mass - Mid/HalfMeVDG1Mu");

ex1->cd();
 ex1->Clear();
 Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianMidHalfMeVDG1Mu->GetParameter(1)));
 Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianMidHalfMeVDG1Mu->GetParError(1)));
 Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianMidHalfMeVDG1Mu->GetParameter(0)));
 Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianMidHalfMeVDG1Mu->GetParError(0)));
 Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianMidHalfMeVDG1Mu->GetParameter(2)));
 Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianMidHalfMeVDG1Mu->GetParError(2)));
 Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianMidHalfMeVDG1Mu->GetParameter(3)));
 Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianMidHalfMeVDG1Mu->GetParError(3)));
 Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianMidHalfMeVDG1Mu->GetParameter(4)));
 Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianMidHalfMeVDG1Mu->GetParError(4)));
 Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", MidHalfMeVDG1Mucount1));
 Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", MidHalfMeVDG1Mucount2));
 Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", MidHalfMeVDG1Mucount3));
 ex1->Write("Mid Fit Values/HalfMeVDG1Mu");
c1->cd();
//////////////////////////////////////

TF1 *GaussianTightHalfMeVDG1Mu = new TF1("GaussianTightHalfMeVDG1Mu",DGOneMuOneTotalHalfMeV,2200.,2400.,7);
GaussianTightHalfMeVDG1Mu->SetParameter(0, 0.5);
GaussianTightHalfMeVDG1Mu->SetParameter(1, 10000);
GaussianTightHalfMeVDG1Mu->SetParameter(2, 2287.);
GaussianTightHalfMeVDG1Mu->SetParameter(3, 5);
GaussianTightHalfMeVDG1Mu->SetParameter(4, 5);
GaussianTightHalfMeVDG1Mu->SetParLimits(3, 0., 20.);
GaussianTightHalfMeVDG1Mu->SetParLimits(4, 0., 20.);
GaussianTightHalfMeVDG1Mu->SetParameter(5, 0.);
GaussianTightHalfMeVDG1Mu->SetParameter(6, 0.);

pad1->cd();
MassHistTightHalfMeV->SetMinimum(0);
MassHistTightHalfMeV->Fit("GaussianTightHalfMeVDG1Mu");

int BinHeightTightHalfMeVDG1Mu[300];
int FitHeightTightHalfMeVDG1Mu[300];
double PullTightHalfMeVDG1Mu[300];

double TightHalfMeVDG1Mucount1 = 0;
double TightHalfMeVDG1Mucount2 = 0;
double TightHalfMeVDG1Mucount3 = 0;

for (int bin = 0; bin < 300; bin++){
BinHeightTightHalfMeVDG1Mu[bin] = MassHistTightHalfMeV->GetBinContent(bin + 1);
int xvalueHalfMeVDG1Mu = 2210.25 + 0.5*(bin);
FitHeightTightHalfMeVDG1Mu[bin] = round(GaussianTightHalfMeVDG1Mu->Eval(xvalueHalfMeVDG1Mu));

PullTightHalfMeVDG1Mu[bin] = (BinHeightTightHalfMeVDG1Mu[bin] - FitHeightTightHalfMeVDG1Mu[bin])/TMath::Sqrt(FitHeightTightHalfMeVDG1Mu[bin]);

if (PullTightHalfMeVDG1Mu[bin] > -1 && PullTightHalfMeVDG1Mu[bin] < 1){
TightHalfMeVDG1Mucount1 += 1;
}

if (PullTightHalfMeVDG1Mu[bin] > -2 && PullTightHalfMeVDG1Mu[bin] < 2){
TightHalfMeVDG1Mucount2 += 1;
}

if (PullTightHalfMeVDG1Mu[bin] > -3 && PullTightHalfMeVDG1Mu[bin] < 3){
TightHalfMeVDG1Mucount3 += 1;
}
}
     pad2->cd();
     TGraph* PullPlotTightHalfMeVDG1Mu = new TGraph(300, PullxHalfMeV, PullTightHalfMeVDG1Mu);
     PullPlotTightHalfMeVDG1Mu->GetXaxis()->SetLimits(0.5,300.5);
     PullPlotTightHalfMeVDG1Mu->GetXaxis()->SetTickLength(0.);
     PullPlotTightHalfMeVDG1Mu->GetYaxis()->SetTickLength(0.);
     PullPlotTightHalfMeVDG1Mu->SetFillColor(38);
     PullPlotTightHalfMeVDG1Mu->GetYaxis()->SetTitle("Pull");
     PullPlotTightHalfMeVDG1Mu->GetYaxis()->CenterTitle();
     PullPlotTightHalfMeVDG1Mu->GetYaxis()->SetTitleSize(0.10);
     PullPlotTightHalfMeVDG1Mu->GetYaxis()->SetTitleOffset(0.2);
     PullPlotTightHalfMeVDG1Mu->GetXaxis()->SetLabelSize(0);
     PullPlotTightHalfMeVDG1Mu->GetYaxis()->SetLabelFont(42);
     PullPlotTightHalfMeVDG1Mu->GetYaxis()->SetLabelSize(0.06);
     PullPlotTightHalfMeVDG1Mu->SetTitle("");
     PullPlotTightHalfMeVDG1Mu->SetMinimum(-5);
     PullPlotTightHalfMeVDG1Mu->SetMaximum(5);
     PullPlotTightHalfMeVDG1Mu->Draw("AB");
     c1->Write("Lc Mass - Tight/HalfMeVDG1Mu");

ex1->cd();
   ex1->Clear();
   Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianTightHalfMeVDG1Mu->GetParameter(1)));
   Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianTightHalfMeVDG1Mu->GetParError(1)));
   Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianTightHalfMeVDG1Mu->GetParameter(0)));
   Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianTightHalfMeVDG1Mu->GetParError(0)));
   Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianTightHalfMeVDG1Mu->GetParameter(2)));
   Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianTightHalfMeVDG1Mu->GetParError(2)));
   Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianTightHalfMeVDG1Mu->GetParameter(3)));
   Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianTightHalfMeVDG1Mu->GetParError(3)));
   Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianTightHalfMeVDG1Mu->GetParameter(4)));
   Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianTightHalfMeVDG1Mu->GetParError(4)));
   Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", TightHalfMeVDG1Mucount1));
   Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", TightHalfMeVDG1Mucount2));
   Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", TightHalfMeVDG1Mucount3));
   ex1->Write("Tight Fit Values/HalfMeVDG1Mu");
c1->cd();
/////////////////////////////////////

TF1 *GaussianLoose1MeVDG1Mu = new TF1("GaussianLoose1MeVDG1Mu",DGOneMuOneTotal1MeV,2200.,2400.,7);
GaussianLoose1MeVDG1Mu->SetParameter(0, 2000.);
GaussianLoose1MeVDG1Mu->SetParLimits(0, 0, 80000);
GaussianLoose1MeVDG1Mu->SetParameter(1, 2286);
GaussianLoose1MeVDG1Mu->SetParameter(2, 5);
GaussianLoose1MeVDG1Mu->SetParLimits(2, 0., 20.);
GaussianLoose1MeVDG1Mu->SetParameter(3, 2000.);
GaussianLoose1MeVDG1Mu->SetParLimits(3, 0, 80000);
GaussianLoose1MeVDG1Mu->SetParameter(4, 5);
GaussianLoose1MeVDG1Mu->SetParLimits(4, 0., 20.);
GaussianLoose1MeVDG1Mu->SetParameter(5, 0.);
GaussianLoose1MeVDG1Mu->SetParameter(6, 0.);

pad1->cd();
MassHistLoose1MeV->SetMinimum(0);
MassHistLoose1MeV->Fit("GaussianLoose1MeVDG1Mu");

int BinHeightLoose1MeVDG1Mu[150];
int FitHeightLoose1MeVDG1Mu[150];
double PullLoose1MeVDG1Mu[150];

double Loose1MeVDG1Mucount1 = 0;
double Loose1MeVDG1Mucount2 = 0;
double Loose1MeVDG1Mucount3 = 0;

for (int bin = 0; bin < 150; bin++){
BinHeightLoose1MeVDG1Mu[bin] = MassHistLoose1MeV->GetBinContent(bin + 1);
Pullx1MeV[bin] = (bin + 1);
int xvalue1MeVDG1Mu = 2210.5 + 1*(bin);
FitHeightLoose1MeVDG1Mu[bin] = round(GaussianLoose1MeVDG1Mu->Eval(xvalue1MeVDG1Mu));
PullLoose1MeVDG1Mu[bin] = (BinHeightLoose1MeVDG1Mu[bin] - FitHeightLoose1MeVDG1Mu[bin])/TMath::Sqrt(FitHeightLoose1MeVDG1Mu[bin]);

if (PullLoose1MeVDG1Mu[bin] > -1 && PullLoose1MeVDG1Mu[bin] < 1){
  Loose1MeVDG1Mucount1 += 1;
}

if (PullLoose1MeVDG1Mu[bin] > -2 && PullLoose1MeVDG1Mu[bin] < 2){
  Loose1MeVDG1Mucount2 += 1;
}

if (PullLoose1MeVDG1Mu[bin] > -3 && PullLoose1MeVDG1Mu[bin] < 3){
  Loose1MeVDG1Mucount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotLoose1MeVDG1Mu = new TGraph(150, Pullx1MeV, PullLoose1MeVDG1Mu);
PullPlotLoose1MeVDG1Mu->GetXaxis()->SetLimits(0.5,150.5);
PullPlotLoose1MeVDG1Mu->GetXaxis()->SetTickLength(0.);
PullPlotLoose1MeVDG1Mu->GetYaxis()->SetTickLength(0.);
PullPlotLoose1MeVDG1Mu->SetFillColor(38);
PullPlotLoose1MeVDG1Mu->GetYaxis()->SetTitle("Pull");
PullPlotLoose1MeVDG1Mu->GetYaxis()->CenterTitle();
PullPlotLoose1MeVDG1Mu->GetYaxis()->SetTitleSize(0.10);
PullPlotLoose1MeVDG1Mu->GetYaxis()->SetTitleOffset(0.2);
PullPlotLoose1MeVDG1Mu->GetXaxis()->SetLabelSize(0);
PullPlotLoose1MeVDG1Mu->GetYaxis()->SetLabelFont(42);
PullPlotLoose1MeVDG1Mu->GetYaxis()->SetLabelSize(0.06);
PullPlotLoose1MeVDG1Mu->SetTitle("");
PullPlotLoose1MeVDG1Mu->SetMinimum(-5);
PullPlotLoose1MeVDG1Mu->SetMaximum(5);
PullPlotLoose1MeVDG1Mu->Draw("AB");
      c1->Write("Lc Mass - Loose/1MeVDG1Mu");

ex1->cd();
    ex1->Clear();
   Tl.SetTextAlign(12);
   Tl.SetTextSize(0.04);
   Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianLoose1MeVDG1Mu->GetParameter(1)));
   Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianLoose1MeVDG1Mu->GetParError(1)));
   Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianLoose1MeVDG1Mu->GetParameter(0)));
   Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianLoose1MeVDG1Mu->GetParError(0)));
   Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianLoose1MeVDG1Mu->GetParameter(2)));
   Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianLoose1MeVDG1Mu->GetParError(2)));
   Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianLoose1MeVDG1Mu->GetParameter(3)));
   Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianLoose1MeVDG1Mu->GetParError(3)));
   Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianLoose1MeVDG1Mu->GetParameter(4)));
   Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianLoose1MeVDG1Mu->GetParError(4)));
   Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", Loose1MeVDG1Mucount1));
   Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", Loose1MeVDG1Mucount2));
   Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", Loose1MeVDG1Mucount3));
   ex1->Write("Loose Fit Values/1MeVDG1Mu");
c1->cd();
//////////////////////////////////////

TF1 *GaussianMid1MeVDG1Mu = new TF1("GaussianMid1MeVDG1Mu",DGOneMuOneTotal1MeV,2200.,2400.,7);
GaussianMid1MeVDG1Mu->SetParameter(0, 0.5);
GaussianMid1MeVDG1Mu->SetParameter(1, 10000);
GaussianMid1MeVDG1Mu->SetParameter(2, 2287.);
GaussianMid1MeVDG1Mu->SetParameter(3, 5);
GaussianMid1MeVDG1Mu->SetParameter(4, 5);
GaussianMid1MeVDG1Mu->SetParLimits(3, 0., 20.);
GaussianMid1MeVDG1Mu->SetParLimits(4, 0., 20.);
GaussianMid1MeVDG1Mu->SetParameter(5, 0.);
GaussianMid1MeVDG1Mu->SetParameter(6, 0.);

pad1->cd();
MassHistMid1MeV->SetMinimum(0);
MassHistMid1MeV->Fit("GaussianMid1MeVDG1Mu");

int BinHeightMid1MeVDG1Mu[150];
int FitHeightMid1MeVDG1Mu[150];
double PullMid1MeVDG1Mu[150];

double   Mid1MeVDG1Mucount1 = 0;
double   Mid1MeVDG1Mucount2 = 0;
double   Mid1MeVDG1Mucount3 = 0;

for (int bin = 0; bin < 150; bin++){
BinHeightMid1MeVDG1Mu[bin] = MassHistMid1MeV->GetBinContent(bin + 1);
int xvalue1MeVDG1Mu = 2210.5 + 1*(bin);
FitHeightMid1MeVDG1Mu[bin] = round(GaussianMid1MeVDG1Mu->Eval(xvalue1MeVDG1Mu));
PullMid1MeVDG1Mu[bin] = (BinHeightMid1MeVDG1Mu[bin] - FitHeightMid1MeVDG1Mu[bin])/TMath::Sqrt(FitHeightMid1MeVDG1Mu[bin]);

if (PullMid1MeVDG1Mu[bin] > -1 && PullMid1MeVDG1Mu[bin] < 1){
Mid1MeVDG1Mucount1 += 1;
}

if (PullMid1MeVDG1Mu[bin] > -2 && PullMid1MeVDG1Mu[bin] < 2){
Mid1MeVDG1Mucount2 += 1;
}

if (PullMid1MeVDG1Mu[bin] > -3 && PullMid1MeVDG1Mu[bin] < 3){
Mid1MeVDG1Mucount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotMid1MeVDG1Mu = new TGraph(150, Pullx1MeV, PullMid1MeVDG1Mu);
PullPlotMid1MeVDG1Mu->GetXaxis()->SetLimits(0.5,150.5);
PullPlotMid1MeVDG1Mu->GetXaxis()->SetTickLength(0.);
PullPlotMid1MeVDG1Mu->GetYaxis()->SetTickLength(0.);
PullPlotMid1MeVDG1Mu->SetFillColor(38);
PullPlotMid1MeVDG1Mu->GetYaxis()->SetTitle("Pull");
PullPlotMid1MeVDG1Mu->GetYaxis()->CenterTitle();
PullPlotMid1MeVDG1Mu->GetYaxis()->SetTitleSize(0.10);
PullPlotMid1MeVDG1Mu->GetYaxis()->SetTitleOffset(0.2);
PullPlotMid1MeVDG1Mu->GetXaxis()->SetLabelSize(0);
PullPlotMid1MeVDG1Mu->GetYaxis()->SetLabelFont(42);
PullPlotMid1MeVDG1Mu->GetYaxis()->SetLabelSize(0.06);
PullPlotMid1MeVDG1Mu->SetTitle("");
PullPlotMid1MeVDG1Mu->SetMinimum(-5);
PullPlotMid1MeVDG1Mu->SetMaximum(5);
PullPlotMid1MeVDG1Mu->Draw("AB");

    c1->Write("Lc Mass - Mid/1MeVDG1Mu");

ex1->cd();
 ex1->Clear();
 Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianMid1MeVDG1Mu->GetParameter(1)));
 Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianMid1MeVDG1Mu->GetParError(1)));
 Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianMid1MeVDG1Mu->GetParameter(0)));
 Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianMid1MeVDG1Mu->GetParError(0)));
 Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianMid1MeVDG1Mu->GetParameter(2)));
 Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianMid1MeVDG1Mu->GetParError(2)));
 Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianMid1MeVDG1Mu->GetParameter(3)));
 Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianMid1MeVDG1Mu->GetParError(3)));
 Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianMid1MeVDG1Mu->GetParameter(4)));
 Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianMid1MeVDG1Mu->GetParError(4)));
 Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", Mid1MeVDG1Mucount1));
 Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", Mid1MeVDG1Mucount2));
 Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", Mid1MeVDG1Mucount3));
 ex1->Write("Mid Fit Values/1MeVDG1Mu");
c1->cd();
//////////////////////////////////////

TF1 *GaussianTight1MeVDG1Mu = new TF1("GaussianTight1MeVDG1Mu",DGOneMuOneTotal1MeV,2200.,2400.,7);
GaussianTight1MeVDG1Mu->SetParameter(0, 0.5);
GaussianTight1MeVDG1Mu->SetParameter(1, 10000);
GaussianTight1MeVDG1Mu->SetParameter(2, 2287.);
GaussianTight1MeVDG1Mu->SetParameter(3, 5);
GaussianTight1MeVDG1Mu->SetParameter(4, 5);
GaussianTight1MeVDG1Mu->SetParLimits(3, 0., 20.);
GaussianTight1MeVDG1Mu->SetParLimits(4, 0., 20.);
GaussianTight1MeVDG1Mu->SetParameter(5, 0.);
GaussianTight1MeVDG1Mu->SetParameter(6, 0.);

pad1->cd();
MassHistTight1MeV->SetMinimum(0);
MassHistTight1MeV->Fit("GaussianTight1MeVDG1Mu");

int BinHeightTight1MeVDG1Mu[150];
int FitHeightTight1MeVDG1Mu[150];
double PullTight1MeVDG1Mu[150];

double Tight1MeVDG1Mucount1 = 0;
double Tight1MeVDG1Mucount2 = 0;
double Tight1MeVDG1Mucount3 = 0;

for (int bin = 0; bin < 150; bin++){
BinHeightTight1MeVDG1Mu[bin] = MassHistTight1MeV->GetBinContent(bin + 1);
int xvalue1MeVDG1Mu = 2210.5 + 1*(bin);
FitHeightTight1MeVDG1Mu[bin] = round(GaussianTight1MeVDG1Mu->Eval(xvalue1MeVDG1Mu));

PullTight1MeVDG1Mu[bin] = (BinHeightTight1MeVDG1Mu[bin] - FitHeightTight1MeVDG1Mu[bin])/TMath::Sqrt(FitHeightTight1MeVDG1Mu[bin]);

if (PullTight1MeVDG1Mu[bin] > -1 && PullTight1MeVDG1Mu[bin] < 1){
Tight1MeVDG1Mucount1 += 1;
}

if (PullTight1MeVDG1Mu[bin] > -2 && PullTight1MeVDG1Mu[bin] < 2){
Tight1MeVDG1Mucount2 += 1;
}

if (PullTight1MeVDG1Mu[bin] > -3 && PullTight1MeVDG1Mu[bin] < 3){
Tight1MeVDG1Mucount3 += 1;
}
}
     pad2->cd();
     TGraph* PullPlotTight1MeVDG1Mu = new TGraph(150, Pullx1MeV, PullTight1MeVDG1Mu);
     PullPlotTight1MeVDG1Mu->GetXaxis()->SetLimits(0.5,150.5);
     PullPlotTight1MeVDG1Mu->GetXaxis()->SetTickLength(0.);
     PullPlotTight1MeVDG1Mu->GetYaxis()->SetTickLength(0.);
     PullPlotTight1MeVDG1Mu->SetFillColor(38);
     PullPlotTight1MeVDG1Mu->GetYaxis()->SetTitle("Pull");
     PullPlotTight1MeVDG1Mu->GetYaxis()->CenterTitle();
     PullPlotTight1MeVDG1Mu->GetYaxis()->SetTitleSize(0.10);
     PullPlotTight1MeVDG1Mu->GetYaxis()->SetTitleOffset(0.2);
     PullPlotTight1MeVDG1Mu->GetXaxis()->SetLabelSize(0);
     PullPlotTight1MeVDG1Mu->GetYaxis()->SetLabelFont(42);
     PullPlotTight1MeVDG1Mu->GetYaxis()->SetLabelSize(0.06);
     PullPlotTight1MeVDG1Mu->SetTitle("");
     PullPlotTight1MeVDG1Mu->SetMinimum(-5);
     PullPlotTight1MeVDG1Mu->SetMaximum(5);
     PullPlotTight1MeVDG1Mu->Draw("AB");
     c1->Write("Lc Mass - Tight/1MeVDG1Mu");

ex1->cd();
   ex1->Clear();
Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianTight1MeVDG1Mu->GetParameter(1)));
Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianTight1MeVDG1Mu->GetParError(1)));
Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianTight1MeVDG1Mu->GetParameter(0)));
Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianTight1MeVDG1Mu->GetParError(0)));
Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianTight1MeVDG1Mu->GetParameter(2)));
Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianTight1MeVDG1Mu->GetParError(2)));
Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianTight1MeVDG1Mu->GetParameter(3)));
Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianTight1MeVDG1Mu->GetParError(3)));
Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianTight1MeVDG1Mu->GetParameter(4)));
Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianTight1MeVDG1Mu->GetParError(4)));
Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", Tight1MeVDG1Mucount1));
Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", Tight1MeVDG1Mucount2));
Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", Tight1MeVDG1Mucount3));
   ex1->Write("Tight Fit Values/1MeVDG1Mu");
c1->cd();
/////////////////////////////
TF1 *GaussianLooseHalfMeVDG2Mu = new TF1("GaussianLooseHalfMeVDG2Mu",DGTwoMuOneTotalHalfMeV,2200.,2400.,8);
GaussianLooseHalfMeVDG2Mu->SetParameter(0, 0.5);
GaussianLooseHalfMeVDG2Mu->SetParLimits(0, 0.1, 0.9);
GaussianLooseHalfMeVDG2Mu->SetParameter(1, 12000);
GaussianLooseHalfMeVDG2Mu->SetParameter(2, 2286.);
GaussianLooseHalfMeVDG2Mu->SetParameter(3, 5);
GaussianLooseHalfMeVDG2Mu->SetParameter(4, 2287);
GaussianLooseHalfMeVDG2Mu->SetParameter(5, 5);
GaussianLooseHalfMeVDG2Mu->SetParLimits(3, 0., 20.);
GaussianLooseHalfMeVDG2Mu->SetParLimits(5, 0., 20.);
GaussianLooseHalfMeVDG2Mu->SetParameter(6, 0.);
GaussianLooseHalfMeVDG2Mu->SetParameter(7, 0.);

pad1->cd();
MassHistLooseHalfMeV->SetMinimum(0);
MassHistLooseHalfMeV->Fit("GaussianLooseHalfMeVDG2Mu");

int BinHeightLooseHalfMeVDG2Mu[300];
int FitHeightLooseHalfMeVDG2Mu[300];
double PullLooseHalfMeVDG2Mu[300];

double LooseHalfMeVDG2Mucount1 = 0;
double LooseHalfMeVDG2Mucount2 = 0;
double LooseHalfMeVDG2Mucount3 = 0;

for (int bin = 0; bin < 300; bin++){
BinHeightLooseHalfMeVDG2Mu[bin] = MassHistLooseHalfMeV->GetBinContent(bin + 1);
PullxHalfMeV[bin] = (bin + 1);
int xvalueHalfMeVDG2Mu = 2210.25 + 0.5*(bin);
FitHeightLooseHalfMeVDG2Mu[bin] = round(GaussianLooseHalfMeVDG2Mu->Eval(xvalueHalfMeVDG2Mu));
PullLooseHalfMeVDG2Mu[bin] = (BinHeightLooseHalfMeVDG2Mu[bin] - FitHeightLooseHalfMeVDG2Mu[bin])/TMath::Sqrt(FitHeightLooseHalfMeVDG2Mu[bin]);

if (PullLooseHalfMeVDG2Mu[bin] > -1 && PullLooseHalfMeVDG2Mu[bin] < 1){
  LooseHalfMeVDG2Mucount1 += 1;
}

if (PullLooseHalfMeVDG2Mu[bin] > -2 && PullLooseHalfMeVDG2Mu[bin] < 2){
  LooseHalfMeVDG2Mucount2 += 1;
}

if (PullLooseHalfMeVDG2Mu[bin] > -3 && PullLooseHalfMeVDG2Mu[bin] < 3){
  LooseHalfMeVDG2Mucount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotLooseHalfMeVDG2Mu = new TGraph(300, PullxHalfMeV, PullLooseHalfMeVDG2Mu);
PullPlotLooseHalfMeVDG2Mu->GetXaxis()->SetLimits(0.5,300.5);
PullPlotLooseHalfMeVDG2Mu->GetXaxis()->SetTickLength(0.);
PullPlotLooseHalfMeVDG2Mu->GetYaxis()->SetTickLength(0.);
PullPlotLooseHalfMeVDG2Mu->SetFillColor(38);
PullPlotLooseHalfMeVDG2Mu->GetYaxis()->SetTitle("Pull");
PullPlotLooseHalfMeVDG2Mu->GetYaxis()->CenterTitle();
PullPlotLooseHalfMeVDG2Mu->GetYaxis()->SetTitleSize(0.10);
PullPlotLooseHalfMeVDG2Mu->GetYaxis()->SetTitleOffset(0.2);
PullPlotLooseHalfMeVDG2Mu->GetXaxis()->SetLabelSize(0);
PullPlotLooseHalfMeVDG2Mu->GetYaxis()->SetLabelFont(42);
PullPlotLooseHalfMeVDG2Mu->GetYaxis()->SetLabelSize(0.06);
PullPlotLooseHalfMeVDG2Mu->SetTitle("");
PullPlotLooseHalfMeVDG2Mu->SetMinimum(-5);
PullPlotLooseHalfMeVDG2Mu->SetMaximum(5);
PullPlotLooseHalfMeVDG2Mu->Draw("AB");
      c1->Write("Lc Mass - Loose/HalfMeVDG2Mu");

ex1->cd();
 ex1->Clear();
   Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianLooseHalfMeVDG2Mu->GetParameter(1)));
   Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianLooseHalfMeVDG2Mu->GetParError(1)));
   Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianLooseHalfMeVDG2Mu->GetParameter(0)));
   Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianLooseHalfMeVDG2Mu->GetParError(0)));
   Tl.DrawLatex(0.1,0.65,Form("Mean Value of First Gaussian: %f MeV", GaussianLooseHalfMeVDG2Mu->GetParameter(2)));
   Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianLooseHalfMeVDG2Mu->GetParError(2)));
   Tl.DrawLatex(0.1,0.5,Form("Mean Value of Second Gaussian: %f MeV", GaussianLooseHalfMeVDG2Mu->GetParameter(4)));
   Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianLooseHalfMeVDG2Mu->GetParError(4)));
   Tl.DrawLatex(0.1,0.35,Form("Sigma of First Gaussian: %f MeV", GaussianLooseHalfMeVDG2Mu->GetParameter(3)));
   Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianLooseHalfMeVDG2Mu->GetParError(3)));
   Tl.DrawLatex(0.1,0.2,Form("Sigma of Second Gaussian: %f MeV", GaussianLooseHalfMeVDG2Mu->GetParameter(5)));
   Tl.DrawLatex(0.1,0.15,Form("Error: %f MeV", GaussianLooseHalfMeVDG2Mu->GetParError(5)));
   Tl.DrawLatex(0.1,0.1,Form("Bins Between -1 & 1 %f Bins", LooseHalfMeVDG2Mucount1));
   Tl.DrawLatex(0.1,0.06,Form("Bins Between -2 & 2 %f Bins", LooseHalfMeVDG2Mucount2));
   Tl.DrawLatex(0.1,0.02,Form("Bins Between -3 & 3 %f Bins", LooseHalfMeVDG2Mucount3));
   ex1->Write("Loose Fit Values/HalfMeVDG2Mu");
c1->cd();
/////////////////////////////

TF1 *GaussianMidHalfMeVDG2Mu = new TF1("GaussianMidHalfMeVDG2Mu",DGTwoMuOneTotalHalfMeV,2200.,2400.,8);
GaussianMidHalfMeVDG2Mu->SetParameter(0, 0.5);
GaussianMidHalfMeVDG2Mu->SetParLimits(0, 0.1, 0.9);
GaussianMidHalfMeVDG2Mu->SetParameter(1, 12000);
GaussianMidHalfMeVDG2Mu->SetParameter(2, 2286.);
GaussianMidHalfMeVDG2Mu->SetParameter(3, 5);
GaussianMidHalfMeVDG2Mu->SetParameter(4, 2287);
GaussianMidHalfMeVDG2Mu->SetParameter(5, 5);
GaussianMidHalfMeVDG2Mu->SetParLimits(3, 0., 20.);
GaussianMidHalfMeVDG2Mu->SetParLimits(5, 0., 20.);
GaussianMidHalfMeVDG2Mu->SetParameter(6, 0.);
GaussianMidHalfMeVDG2Mu->SetParameter(7, 0.);

pad1->cd();
MassHistMidHalfMeV->SetMinimum(0);
MassHistMidHalfMeV->Fit("GaussianMidHalfMeVDG2Mu");

int BinHeightMidHalfMeVDG2Mu[300];
int FitHeightMidHalfMeVDG2Mu[300];
double PullMidHalfMeVDG2Mu[300];

double   MidHalfMeVDG2Mucount1 = 0;
double   MidHalfMeVDG2Mucount2 = 0;
double   MidHalfMeVDG2Mucount3 = 0;

for (int bin = 0; bin < 300; bin++){
BinHeightMidHalfMeVDG2Mu[bin] = MassHistMidHalfMeV->GetBinContent(bin + 1);
int xvalueHalfMeVDG2Mu = 2210.25 + 0.5*(bin);
FitHeightMidHalfMeVDG2Mu[bin] = round(GaussianMidHalfMeVDG2Mu->Eval(xvalueHalfMeVDG2Mu));
PullMidHalfMeVDG2Mu[bin] = (BinHeightMidHalfMeVDG2Mu[bin] - FitHeightMidHalfMeVDG2Mu[bin])/TMath::Sqrt(FitHeightMidHalfMeVDG2Mu[bin]);

if (PullMidHalfMeVDG2Mu[bin] > -1 && PullMidHalfMeVDG2Mu[bin] < 1){
MidHalfMeVDG2Mucount1 += 1;
}

if (PullMidHalfMeVDG2Mu[bin] > -2 && PullMidHalfMeVDG2Mu[bin] < 2){
MidHalfMeVDG2Mucount2 += 1;
}

if (PullMidHalfMeVDG2Mu[bin] > -3 && PullMidHalfMeVDG2Mu[bin] < 3){
MidHalfMeVDG2Mucount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotMidHalfMeVDG2Mu = new TGraph(300, PullxHalfMeV, PullMidHalfMeVDG2Mu);
PullPlotMidHalfMeVDG2Mu->GetXaxis()->SetLimits(0.5,300.5);
PullPlotMidHalfMeVDG2Mu->GetXaxis()->SetTickLength(0.);
PullPlotMidHalfMeVDG2Mu->GetYaxis()->SetTickLength(0.);
PullPlotMidHalfMeVDG2Mu->SetFillColor(38);
PullPlotMidHalfMeVDG2Mu->GetYaxis()->SetTitle("Pull");
PullPlotMidHalfMeVDG2Mu->GetYaxis()->CenterTitle();
PullPlotMidHalfMeVDG2Mu->GetYaxis()->SetTitleSize(0.10);
PullPlotMidHalfMeVDG2Mu->GetYaxis()->SetTitleOffset(0.2);
PullPlotMidHalfMeVDG2Mu->GetXaxis()->SetLabelSize(0);
PullPlotMidHalfMeVDG2Mu->GetYaxis()->SetLabelFont(42);
PullPlotMidHalfMeVDG2Mu->GetYaxis()->SetLabelSize(0.06);
PullPlotMidHalfMeVDG2Mu->SetTitle("");
PullPlotMidHalfMeVDG2Mu->SetMinimum(-5);
PullPlotMidHalfMeVDG2Mu->SetMaximum(5);
PullPlotMidHalfMeVDG2Mu->Draw("AB");

    c1->Write("Lc Mass - Mid/HalfMeVDG2Mu");

ex1->cd();
 ex1->Clear();
 Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianMidHalfMeVDG2Mu->GetParameter(1)));
 Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianMidHalfMeVDG2Mu->GetParError(1)));
 Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianMidHalfMeVDG2Mu->GetParameter(0)));
 Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianMidHalfMeVDG2Mu->GetParError(0)));
 Tl.DrawLatex(0.1,0.65,Form("Mean Value of First Gaussian: %f MeV", GaussianMidHalfMeVDG2Mu->GetParameter(2)));
 Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianMidHalfMeVDG2Mu->GetParError(2)));
 Tl.DrawLatex(0.1,0.5,Form("Mean Value of Second Gaussian: %f MeV", GaussianMidHalfMeVDG2Mu->GetParameter(4)));
 Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianMidHalfMeVDG2Mu->GetParError(4)));
 Tl.DrawLatex(0.1,0.35,Form("Sigma of First Gaussian: %f MeV", GaussianMidHalfMeVDG2Mu->GetParameter(3)));
 Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianMidHalfMeVDG2Mu->GetParError(3)));
 Tl.DrawLatex(0.1,0.2,Form("Sigma of Second Gaussian: %f MeV", GaussianMidHalfMeVDG2Mu->GetParameter(5)));
 Tl.DrawLatex(0.1,0.15,Form("Error: %f MeV", GaussianMidHalfMeVDG2Mu->GetParError(5)));
 Tl.DrawLatex(0.1,0.1,Form("Bins Between -1 & 1 %f Bins", MidHalfMeVDG2Mucount1));
 Tl.DrawLatex(0.1,0.06,Form("Bins Between -2 & 2 %f Bins", MidHalfMeVDG2Mucount2));
 Tl.DrawLatex(0.1,0.02,Form("Bins Between -3 & 3 %f Bins", MidHalfMeVDG2Mucount3));
 ex1->Write("Mid Fit Values/HalfMeVDG2Mu");
c1->cd();
//////////////////////////////////////

TF1 *GaussianTightHalfMeVDG2Mu = new TF1("GaussianTightHalfMeVDG2Mu",DGTwoMuOneTotalHalfMeV,2200.,2400.,8);
GaussianTightHalfMeVDG2Mu->SetParameter(0, 0.5);
GaussianTightHalfMeVDG2Mu->SetParLimits(0, 0.1, 0.9);
GaussianTightHalfMeVDG2Mu->SetParameter(1, 12000);
GaussianTightHalfMeVDG2Mu->SetParameter(2, 2286.);
GaussianTightHalfMeVDG2Mu->SetParameter(3, 5);
GaussianTightHalfMeVDG2Mu->SetParameter(4, 2287);
GaussianTightHalfMeVDG2Mu->SetParameter(5, 5);
GaussianTightHalfMeVDG2Mu->SetParLimits(3, 0., 20.);
GaussianTightHalfMeVDG2Mu->SetParLimits(5, 0., 20.);
GaussianTightHalfMeVDG2Mu->SetParameter(6, 0.);
GaussianTightHalfMeVDG2Mu->SetParameter(7, 0.);

pad1->cd();
MassHistTightHalfMeV->SetMinimum(0);
MassHistTightHalfMeV->Fit("GaussianTightHalfMeVDG2Mu");

int BinHeightTightHalfMeVDG2Mu[300];
int FitHeightTightHalfMeVDG2Mu[300];
double PullTightHalfMeVDG2Mu[300];

double TightHalfMeVDG2Mucount1 = 0;
double TightHalfMeVDG2Mucount2 = 0;
double TightHalfMeVDG2Mucount3 = 0;

for (int bin = 0; bin < 300; bin++){
BinHeightTightHalfMeVDG2Mu[bin] = MassHistTightHalfMeV->GetBinContent(bin + 1);
int xvalueHalfMeVDG2Mu = 2210.25 + 0.5*(bin);
FitHeightTightHalfMeVDG2Mu[bin] = round(GaussianTightHalfMeVDG2Mu->Eval(xvalueHalfMeVDG2Mu));

PullTightHalfMeVDG2Mu[bin] = (BinHeightTightHalfMeVDG2Mu[bin] - FitHeightTightHalfMeVDG2Mu[bin])/TMath::Sqrt(FitHeightTightHalfMeVDG2Mu[bin]);

if (PullTightHalfMeVDG2Mu[bin] > -1 && PullTightHalfMeVDG2Mu[bin] < 1){
TightHalfMeVDG2Mucount1 += 1;
}

if (PullTightHalfMeVDG2Mu[bin] > -2 && PullTightHalfMeVDG2Mu[bin] < 2){
TightHalfMeVDG2Mucount2 += 1;
}

if (PullTightHalfMeVDG2Mu[bin] > -3 && PullTightHalfMeVDG2Mu[bin] < 3){
TightHalfMeVDG2Mucount3 += 1;
}
}
     pad2->cd();
     TGraph* PullPlotTightHalfMeVDG2Mu = new TGraph(300, PullxHalfMeV, PullTightHalfMeVDG2Mu);
     PullPlotTightHalfMeVDG2Mu->GetXaxis()->SetLimits(0.5,300.5);
     PullPlotTightHalfMeVDG2Mu->GetXaxis()->SetTickLength(0.);
     PullPlotTightHalfMeVDG2Mu->GetYaxis()->SetTickLength(0.);
     PullPlotTightHalfMeVDG2Mu->SetFillColor(38);
     PullPlotTightHalfMeVDG2Mu->GetYaxis()->SetTitle("Pull");
     PullPlotTightHalfMeVDG2Mu->GetYaxis()->CenterTitle();
     PullPlotTightHalfMeVDG2Mu->GetYaxis()->SetTitleSize(0.10);
     PullPlotTightHalfMeVDG2Mu->GetYaxis()->SetTitleOffset(0.2);
     PullPlotTightHalfMeVDG2Mu->GetXaxis()->SetLabelSize(0);
     PullPlotTightHalfMeVDG2Mu->GetYaxis()->SetLabelFont(42);
     PullPlotTightHalfMeVDG2Mu->GetYaxis()->SetLabelSize(0.06);
     PullPlotTightHalfMeVDG2Mu->SetTitle("");
     PullPlotTightHalfMeVDG2Mu->SetMinimum(-5);
     PullPlotTightHalfMeVDG2Mu->SetMaximum(5);
     PullPlotTightHalfMeVDG2Mu->Draw("AB");
     c1->Write("Lc Mass - Tight/HalfMeVDG2Mu");

ex1->cd();
   ex1->Clear();
   Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianTightHalfMeVDG2Mu->GetParameter(1)));
   Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianTightHalfMeVDG2Mu->GetParError(1)));
   Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianTightHalfMeVDG2Mu->GetParameter(0)));
   Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianTightHalfMeVDG2Mu->GetParError(0)));
   Tl.DrawLatex(0.1,0.65,Form("Mean Value of First Gaussian: %f MeV", GaussianTightHalfMeVDG2Mu->GetParameter(2)));
   Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianTightHalfMeVDG2Mu->GetParError(2)));
   Tl.DrawLatex(0.1,0.5,Form("Mean Value of Second Gaussian: %f MeV", GaussianTightHalfMeVDG2Mu->GetParameter(4)));
   Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianTightHalfMeVDG2Mu->GetParError(4)));
   Tl.DrawLatex(0.1,0.35,Form("Sigma of First Gaussian: %f MeV", GaussianTightHalfMeVDG2Mu->GetParameter(3)));
   Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianTightHalfMeVDG2Mu->GetParError(3)));
   Tl.DrawLatex(0.1,0.2,Form("Sigma of Second Gaussian: %f MeV", GaussianTightHalfMeVDG2Mu->GetParameter(5)));
   Tl.DrawLatex(0.1,0.15,Form("Error: %f MeV", GaussianTightHalfMeVDG2Mu->GetParError(5)));
   Tl.DrawLatex(0.1,0.1,Form("Bins Between -1 & 1 %f Bins", TightHalfMeVDG2Mucount1));
   Tl.DrawLatex(0.1,0.06,Form("Bins Between -2 & 2 %f Bins", TightHalfMeVDG2Mucount2));
   Tl.DrawLatex(0.1,0.02,Form("Bins Between -3 & 3 %f Bins", TightHalfMeVDG2Mucount3));
   ex1->Write("Tight Fit Values/HalfMeVDG2Mu");
c1->cd();
/////////////////////////////////////

TF1 *GaussianLoose1MeVDG2Mu = new TF1("GaussianLoose1MeVDG2Mu",DGTwoMuOneTotal1MeV,2200.,2400.,8);
GaussianLoose1MeVDG2Mu->SetParameter(0, 0.5);
GaussianLoose1MeVDG2Mu->SetParLimits(0, 0.1, 0.9);
GaussianLoose1MeVDG2Mu->SetParameter(1, 12000);
GaussianLoose1MeVDG2Mu->SetParameter(2, 2286.);
GaussianLoose1MeVDG2Mu->SetParameter(3, 5);
GaussianLoose1MeVDG2Mu->SetParameter(4, 2287);
GaussianLoose1MeVDG2Mu->SetParameter(5, 5);
GaussianLoose1MeVDG2Mu->SetParLimits(3, 0., 20.);
GaussianLoose1MeVDG2Mu->SetParLimits(5, 0., 20.);
GaussianLoose1MeVDG2Mu->SetParameter(6, 0.);
GaussianLoose1MeVDG2Mu->SetParameter(7, 0.);

pad1->cd();
MassHistLoose1MeV->SetMinimum(0);
MassHistLoose1MeV->Fit("GaussianLoose1MeVDG2Mu");

int BinHeightLoose1MeVDG2Mu[150];
int FitHeightLoose1MeVDG2Mu[150];
double PullLoose1MeVDG2Mu[150];

double Loose1MeVDG2Mucount1 = 0;
double Loose1MeVDG2Mucount2 = 0;
double Loose1MeVDG2Mucount3 = 0;

for (int bin = 0; bin < 150; bin++){
BinHeightLoose1MeVDG2Mu[bin] = MassHistLoose1MeV->GetBinContent(bin + 1);
Pullx1MeV[bin] = (bin + 1);
int xvalue1MeVDG2Mu = 2210.5 + 1*(bin);
FitHeightLoose1MeVDG2Mu[bin] = round(GaussianLoose1MeVDG2Mu->Eval(xvalue1MeVDG2Mu));
PullLoose1MeVDG2Mu[bin] = (BinHeightLoose1MeVDG2Mu[bin] - FitHeightLoose1MeVDG2Mu[bin])/TMath::Sqrt(FitHeightLoose1MeVDG2Mu[bin]);

if (PullLoose1MeVDG2Mu[bin] > -1 && PullLoose1MeVDG2Mu[bin] < 1){
  Loose1MeVDG2Mucount1 += 1;
}

if (PullLoose1MeVDG2Mu[bin] > -2 && PullLoose1MeVDG2Mu[bin] < 2){
  Loose1MeVDG2Mucount2 += 1;
}

if (PullLoose1MeVDG2Mu[bin] > -3 && PullLoose1MeVDG2Mu[bin] < 3){
  Loose1MeVDG2Mucount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotLoose1MeVDG2Mu = new TGraph(150, Pullx1MeV, PullLoose1MeVDG2Mu);
PullPlotLoose1MeVDG2Mu->GetXaxis()->SetLimits(0.5,150.5);
PullPlotLoose1MeVDG2Mu->GetXaxis()->SetTickLength(0.);
PullPlotLoose1MeVDG2Mu->GetYaxis()->SetTickLength(0.);
PullPlotLoose1MeVDG2Mu->SetFillColor(38);
PullPlotLoose1MeVDG2Mu->GetYaxis()->SetTitle("Pull");
PullPlotLoose1MeVDG2Mu->GetYaxis()->CenterTitle();
PullPlotLoose1MeVDG2Mu->GetYaxis()->SetTitleSize(0.10);
PullPlotLoose1MeVDG2Mu->GetYaxis()->SetTitleOffset(0.2);
PullPlotLoose1MeVDG2Mu->GetXaxis()->SetLabelSize(0);
PullPlotLoose1MeVDG2Mu->GetYaxis()->SetLabelFont(42);
PullPlotLoose1MeVDG2Mu->GetYaxis()->SetLabelSize(0.06);
PullPlotLoose1MeVDG2Mu->SetTitle("");
PullPlotLoose1MeVDG2Mu->SetMinimum(-5);
PullPlotLoose1MeVDG2Mu->SetMaximum(5);
PullPlotLoose1MeVDG2Mu->Draw("AB");
      c1->Write("Lc Mass - Loose/1MeVDG2Mu");

ex1->cd();
    ex1->Clear();
   Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianLoose1MeVDG2Mu->GetParameter(1)));
   Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianLoose1MeVDG2Mu->GetParError(1)));
   Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianLoose1MeVDG2Mu->GetParameter(0)));
   Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianLoose1MeVDG2Mu->GetParError(0)));
   Tl.DrawLatex(0.1,0.65,Form("Mean Value of First Gaussian: %f MeV", GaussianLoose1MeVDG2Mu->GetParameter(2)));
   Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianLoose1MeVDG2Mu->GetParError(2)));
   Tl.DrawLatex(0.1,0.5,Form("Mean Value of Second Gaussian: %f MeV", GaussianLoose1MeVDG2Mu->GetParameter(4)));
   Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianLoose1MeVDG2Mu->GetParError(4)));
   Tl.DrawLatex(0.1,0.35,Form("Sigma of First Gaussian: %f MeV", GaussianLoose1MeVDG2Mu->GetParameter(3)));
   Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianLoose1MeVDG2Mu->GetParError(3)));
   Tl.DrawLatex(0.1,0.2,Form("Sigma of Second Gaussian: %f MeV", GaussianLoose1MeVDG2Mu->GetParameter(5)));
   Tl.DrawLatex(0.1,0.15,Form("Error: %f MeV", GaussianLoose1MeVDG2Mu->GetParError(5)));
   Tl.DrawLatex(0.1,0.1,Form("Bins Between -1 & 1 %f Bins", Loose1MeVDG2Mucount1));
   Tl.DrawLatex(0.1,0.06,Form("Bins Between -2 & 2 %f Bins", Loose1MeVDG2Mucount2));
   Tl.DrawLatex(0.1,0.02,Form("Bins Between -3 & 3 %f Bins", Loose1MeVDG2Mucount3));
   ex1->Write("Loose Fit Values/1MeVDG2Mu");
c1->cd();
//////////////////////////////////////

TF1 *GaussianMid1MeVDG2Mu = new TF1("GaussianMid1MeVDG2Mu",DGTwoMuOneTotal1MeV,2200.,2400.,8);
GaussianMid1MeVDG2Mu->SetParameter(0, 0.5);
GaussianMid1MeVDG2Mu->SetParLimits(0, 0.1, 0.9);
GaussianMid1MeVDG2Mu->SetParameter(1, 12000);
GaussianMid1MeVDG2Mu->SetParameter(2, 2286.);
GaussianMid1MeVDG2Mu->SetParameter(3, 5);
GaussianMid1MeVDG2Mu->SetParameter(4, 2287);
GaussianMid1MeVDG2Mu->SetParameter(5, 5);
GaussianMid1MeVDG2Mu->SetParLimits(3, 0., 20.);
GaussianMid1MeVDG2Mu->SetParLimits(5, 0., 20.);
GaussianMid1MeVDG2Mu->SetParameter(6, 0.);
GaussianMid1MeVDG2Mu->SetParameter(7, 0.);

pad1->cd();
MassHistMid1MeV->SetMinimum(0);
MassHistMid1MeV->Fit("GaussianMid1MeVDG2Mu");

int BinHeightMid1MeVDG2Mu[150];
int FitHeightMid1MeVDG2Mu[150];
double PullMid1MeVDG2Mu[150];

double   Mid1MeVDG2Mucount1 = 0;
double   Mid1MeVDG2Mucount2 = 0;
double   Mid1MeVDG2Mucount3 = 0;

for (int bin = 0; bin < 150; bin++){
BinHeightMid1MeVDG2Mu[bin] = MassHistMid1MeV->GetBinContent(bin + 1);
int xvalue1MeVDG2Mu = 2210.5 + 1*(bin);
FitHeightMid1MeVDG2Mu[bin] = round(GaussianMid1MeVDG2Mu->Eval(xvalue1MeVDG2Mu));
PullMid1MeVDG2Mu[bin] = (BinHeightMid1MeVDG2Mu[bin] - FitHeightMid1MeVDG2Mu[bin])/TMath::Sqrt(FitHeightMid1MeVDG2Mu[bin]);

if (PullMid1MeVDG2Mu[bin] > -1 && PullMid1MeVDG2Mu[bin] < 1){
Mid1MeVDG2Mucount1 += 1;
}

if (PullMid1MeVDG2Mu[bin] > -2 && PullMid1MeVDG2Mu[bin] < 2){
Mid1MeVDG2Mucount2 += 1;
}

if (PullMid1MeVDG2Mu[bin] > -3 && PullMid1MeVDG2Mu[bin] < 3){
Mid1MeVDG2Mucount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotMid1MeVDG2Mu = new TGraph(150, Pullx1MeV, PullMid1MeVDG2Mu);
PullPlotMid1MeVDG2Mu->GetXaxis()->SetLimits(0.5,150.5);
PullPlotMid1MeVDG2Mu->GetXaxis()->SetTickLength(0.);
PullPlotMid1MeVDG2Mu->GetYaxis()->SetTickLength(0.);
PullPlotMid1MeVDG2Mu->SetFillColor(38);
PullPlotMid1MeVDG2Mu->GetYaxis()->SetTitle("Pull");
PullPlotMid1MeVDG2Mu->GetYaxis()->CenterTitle();
PullPlotMid1MeVDG2Mu->GetYaxis()->SetTitleSize(0.10);
PullPlotMid1MeVDG2Mu->GetYaxis()->SetTitleOffset(0.2);
PullPlotMid1MeVDG2Mu->GetXaxis()->SetLabelSize(0);
PullPlotMid1MeVDG2Mu->GetYaxis()->SetLabelFont(42);
PullPlotMid1MeVDG2Mu->GetYaxis()->SetLabelSize(0.06);
PullPlotMid1MeVDG2Mu->SetTitle("");
PullPlotMid1MeVDG2Mu->SetMinimum(-5);
PullPlotMid1MeVDG2Mu->SetMaximum(5);
PullPlotMid1MeVDG2Mu->Draw("AB");

    c1->Write("Lc Mass - Mid/1MeVDG2Mu");

ex1->cd();
 ex1->Clear();
 Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianMid1MeVDG2Mu->GetParameter(1)));
 Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianMid1MeVDG2Mu->GetParError(1)));
 Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianMid1MeVDG2Mu->GetParameter(0)));
 Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianMid1MeVDG2Mu->GetParError(0)));
 Tl.DrawLatex(0.1,0.65,Form("Mean Value of First Gaussian: %f MeV", GaussianMid1MeVDG2Mu->GetParameter(2)));
 Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianMid1MeVDG2Mu->GetParError(2)));
 Tl.DrawLatex(0.1,0.5,Form("Mean Value of Second Gaussian: %f MeV", GaussianMid1MeVDG2Mu->GetParameter(4)));
 Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianMid1MeVDG2Mu->GetParError(4)));
 Tl.DrawLatex(0.1,0.35,Form("Sigma of First Gaussian: %f MeV", GaussianMid1MeVDG2Mu->GetParameter(3)));
 Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianMid1MeVDG2Mu->GetParError(3)));
 Tl.DrawLatex(0.1,0.2,Form("Sigma of Second Gaussian: %f MeV", GaussianMid1MeVDG2Mu->GetParameter(5)));
 Tl.DrawLatex(0.1,0.15,Form("Error: %f MeV", GaussianMid1MeVDG2Mu->GetParError(5)));
 Tl.DrawLatex(0.1,0.1,Form("Bins Between -1 & 1 %f Bins", Mid1MeVDG2Mucount1));
 Tl.DrawLatex(0.1,0.06,Form("Bins Between -2 & 2 %f Bins", Mid1MeVDG2Mucount2));
 Tl.DrawLatex(0.1,0.02,Form("Bins Between -3 & 3 %f Bins", Mid1MeVDG2Mucount3));
 ex1->Write("Mid Fit Values/1MeVDG2Mu");
c1->cd();
//////////////////////////////////////

TF1 *GaussianTight1MeVDG2Mu = new TF1("GaussianTight1MeVDG2Mu",DGTwoMuOneTotal1MeV,2200.,2400.,8);
GaussianTight1MeVDG2Mu->SetParameter(0, 0.5);
GaussianTight1MeVDG2Mu->SetParLimits(0, 0.1, 0.9);
GaussianTight1MeVDG2Mu->SetParameter(1, 12000);
GaussianTight1MeVDG2Mu->SetParameter(2, 2286.);
GaussianTight1MeVDG2Mu->SetParameter(3, 5);
GaussianTight1MeVDG2Mu->SetParameter(4, 2287);
GaussianTight1MeVDG2Mu->SetParameter(5, 5);
GaussianTight1MeVDG2Mu->SetParLimits(3, 0., 20.);
GaussianTight1MeVDG2Mu->SetParLimits(5, 0., 20.);
GaussianTight1MeVDG2Mu->SetParameter(6, 0.);
GaussianTight1MeVDG2Mu->SetParameter(7, 0.);

pad1->cd();
MassHistTight1MeV->SetMinimum(0);
MassHistTight1MeV->Fit("GaussianTight1MeVDG2Mu");

int BinHeightTight1MeVDG2Mu[150];
int FitHeightTight1MeVDG2Mu[150];
double PullTight1MeVDG2Mu[150];

double Tight1MeVDG2Mucount1 = 0;
double Tight1MeVDG2Mucount2 = 0;
double Tight1MeVDG2Mucount3 = 0;

for (int bin = 0; bin < 150; bin++){
BinHeightTight1MeVDG2Mu[bin] = MassHistTight1MeV->GetBinContent(bin + 1);
int xvalue1MeVDG2Mu = 2210.5 + 1*(bin);
FitHeightTight1MeVDG2Mu[bin] = round(GaussianTight1MeVDG2Mu->Eval(xvalue1MeVDG2Mu));

PullTight1MeVDG2Mu[bin] = (BinHeightTight1MeVDG2Mu[bin] - FitHeightTight1MeVDG2Mu[bin])/TMath::Sqrt(FitHeightTight1MeVDG2Mu[bin]);

if (PullTight1MeVDG2Mu[bin] > -1 && PullTight1MeVDG2Mu[bin] < 1){
Tight1MeVDG2Mucount1 += 1;
}

if (PullTight1MeVDG2Mu[bin] > -2 && PullTight1MeVDG2Mu[bin] < 2){
Tight1MeVDG2Mucount2 += 1;
}

if (PullTight1MeVDG2Mu[bin] > -3 && PullTight1MeVDG2Mu[bin] < 3){
Tight1MeVDG2Mucount3 += 1;
}
}
     pad2->cd();
     TGraph* PullPlotTight1MeVDG2Mu = new TGraph(150, Pullx1MeV, PullTight1MeVDG2Mu);
     PullPlotTight1MeVDG2Mu->GetXaxis()->SetLimits(0.5,150.5);
     PullPlotTight1MeVDG2Mu->GetXaxis()->SetTickLength(0.);
     PullPlotTight1MeVDG2Mu->GetYaxis()->SetTickLength(0.);
     PullPlotTight1MeVDG2Mu->SetFillColor(38);
     PullPlotTight1MeVDG2Mu->GetYaxis()->SetTitle("Pull");
     PullPlotTight1MeVDG2Mu->GetYaxis()->CenterTitle();
     PullPlotTight1MeVDG2Mu->GetYaxis()->SetTitleSize(0.10);
     PullPlotTight1MeVDG2Mu->GetYaxis()->SetTitleOffset(0.2);
     PullPlotTight1MeVDG2Mu->GetXaxis()->SetLabelSize(0);
     PullPlotTight1MeVDG2Mu->GetYaxis()->SetLabelFont(42);
     PullPlotTight1MeVDG2Mu->GetYaxis()->SetLabelSize(0.06);
     PullPlotTight1MeVDG2Mu->SetTitle("");
     PullPlotTight1MeVDG2Mu->SetMinimum(-5);
     PullPlotTight1MeVDG2Mu->SetMaximum(5);
     PullPlotTight1MeVDG2Mu->Draw("AB");
     c1->Write("Lc Mass - Tight/1MeVDG2Mu");

ex1->cd();
   ex1->Clear();
Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianTight1MeVDG2Mu->GetParameter(1)));
Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianTight1MeVDG2Mu->GetParError(1)));
Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianTight1MeVDG2Mu->GetParameter(0)));
Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianTight1MeVDG2Mu->GetParError(0)));
Tl.DrawLatex(0.1,0.65,Form("Mean Value of First Gaussian: %f MeV", GaussianTight1MeVDG2Mu->GetParameter(2)));
Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianTight1MeVDG2Mu->GetParError(2)));
Tl.DrawLatex(0.1,0.5,Form("Mean Value of Second Gaussian: %f MeV", GaussianTight1MeVDG2Mu->GetParameter(4)));
Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianTight1MeVDG2Mu->GetParError(4)));
Tl.DrawLatex(0.1,0.35,Form("Sigma of First Gaussian: %f MeV", GaussianTight1MeVDG2Mu->GetParameter(3)));
Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianTight1MeVDG2Mu->GetParError(3)));
Tl.DrawLatex(0.1,0.2,Form("Sigma of Second Gaussian: %f MeV", GaussianTight1MeVDG2Mu->GetParameter(5)));
Tl.DrawLatex(0.1,0.15,Form("Error: %f MeV", GaussianTight1MeVDG2Mu->GetParError(5)));
Tl.DrawLatex(0.1,0.1,Form("Bins Between -1 & 1 %f Bins", Tight1MeVDG2Mucount1));
Tl.DrawLatex(0.1,0.06,Form("Bins Between -2 & 2 %f Bins", Tight1MeVDG2Mucount2));
Tl.DrawLatex(0.1,0.02,Form("Bins Between -3 & 3 %f Bins", Tight1MeVDG2Mucount3));
   ex1->Write("Tight Fit Values/1MeVDG2Mu");
c1->cd();
/////////////////////////////
   
     TF1 *myLambdaFitSG = new TF1("myLambdaFitSG",fitHalfMeV_Gaussian,2200.,2400.,5);
      myLambdaFitSG->SetParameter(0,400.);
      myLambdaFitSG->SetParameter(1,2286.5);
      myLambdaFitSG->SetParameter(2, 6);
      myLambdaFitSG->SetParLimits(2, 0.,20.);
      myLambdaFitSG->SetParameter(3, 0.);
      myLambdaFitSG->SetParameter(4, 0.);

      TF1 *LcFitSG1 = new TF1("LcFitSG1",fitHalfMeV_Gaussian,2200.,2400.,5);
      LcFitSG1->SetParameter(0,400.);
      LcFitSG1->SetParameter(1,2286.5);
      LcFitSG1->SetParameter(2, 6);
      LcFitSG1->SetParLimits(2, 0.,20.);
      LcFitSG1->SetParameter(3, 0.);
      LcFitSG1->SetParameter(4, 0.);

      TF1 *LcFitSG2 = new TF1("LcFitSG2",fitHalfMeV_Gaussian,2200.,2400.,5);
      LcFitSG2->SetParameter(0,400.);
      LcFitSG2->SetParameter(1,2286.5);
      LcFitSG2->SetParameter(2, 6);
      LcFitSG2->SetParLimits(2, 0.,20.);
      LcFitSG2->SetParameter(3, 0.);
      LcFitSG2->SetParameter(4, 0.);

      TF1 *LcFitSG3 = new TF1("LcFitSG3",fitHalfMeV_Gaussian,2200.,2400.,5);
      LcFitSG3->SetParameter(0,400.);
      LcFitSG3->SetParameter(1,2286.5);
      LcFitSG3->SetParameter(2, 6);
      LcFitSG3->SetParLimits(2, 0.,20.);
      LcFitSG3->SetParameter(3, 0.);
      LcFitSG3->SetParameter(4, 0.);

      TF1 *LcFitSG4 = new TF1("LcFitSG4",fitHalfMeV_Gaussian,2200.,2400.,5);
      LcFitSG4->SetParameter(0,400.);
      LcFitSG4->SetParameter(1,2286.5);
      LcFitSG4->SetParameter(2, 6);
      LcFitSG4->SetParLimits(2, 0.,20.);
      LcFitSG4->SetParameter(3, 0.);
      LcFitSG4->SetParameter(4, 0.);
   
       TF1 *MagDownFitSG = new TF1("MagDownFitSG",fitHalfMeV_Gaussian,2200.,2400.,5);
      MagDownFitSG->SetParameter(0,400.);
      MagDownFitSG->SetParameter(1,2286.5);
      MagDownFitSG->SetParameter(2, 6);
      MagDownFitSG->SetParLimits(2, 0.,20.);
      MagDownFitSG->SetParameter(3, 0.);
      MagDownFitSG->SetParameter(4, 0.);

      TF1 *MagUpFitSG = new TF1("MagUpFitSG",fitHalfMeV_Gaussian,2200.,2400.,5);
      MagUpFitSG->SetParameter(0,400.);
      MagUpFitSG->SetParameter(1,2286.5);
      MagUpFitSG->SetParameter(2, 6);
      MagUpFitSG->SetParLimits(2, 0.,20.);
      MagUpFitSG->SetParameter(3, 0.);
      MagUpFitSG->SetParameter(4, 0.);

      TF1 *ParticleFitSG = new TF1("ParticleFitSG",fitHalfMeV_Gaussian,2200.,2400.,5);
      ParticleFitSG->SetParameter(0,400.);
      ParticleFitSG->SetParameter(1,2286.5);
      ParticleFitSG->SetParameter(2, 6);
      ParticleFitSG->SetParLimits(2, 0.,20.);
      ParticleFitSG->SetParameter(3, 0.);
      ParticleFitSG->SetParameter(4, 0.);

      TF1 *AntiParticleFitSG = new TF1("AntiParticleFitSG",fitHalfMeV_Gaussian,2200.,2400.,5);
      AntiParticleFitSG->SetParameter(0,400.);
      AntiParticleFitSG->SetParameter(1,2286.5);
      AntiParticleFitSG->SetParameter(2, 6);
      AntiParticleFitSG->SetParLimits(2, 0.,20.);
      AntiParticleFitSG->SetParameter(3, 0.);
      AntiParticleFitSG->SetParameter(4, 0.);

       LcLowP->Fit("LcFitSG1");
      LcLowP->SetMinimum(0);
      c1->Write("Low Lc Momentum Region");

      LcMidLowP->Fit("LcFitSG2");
      LcMidLowP->SetMinimum(0);
      c1->Write("MidLow Lc Momentum Region");

      LcMidHighP->Fit("LcFitSG3");
      LcMidHighP->SetMinimum(0);
      c1->Write("MidHigh Lc Momentum Region");

      LcHighP->Fit("LcFitSG4");
      LcHighP->SetMinimum(0);
      c1->Write("High Lc Momentum Region");

      LcPDistribution->Draw();
      LcPDistribution->SetMinimum(0);
      c1->Write("Lc Momentum Distribution");

      double y1 = LcFitSG1->GetParameter(1);
      double y2 = LcFitSG2->GetParameter(1);
      double y3 = LcFitSG3->GetParameter(1);
      double y4 = LcFitSG4->GetParameter(1);

      double yerr1 = LcFitSG1->GetParError(1);
      double yerr2 = LcFitSG2->GetParError(1);
      double yerr3 = LcFitSG3->GetParError(1);
      double yerr4 = LcFitSG4->GetParError(1);

      const Int_t n = 4;
      Double_t x[n] = {1,2,3,4};
      Double_t xerr[n] = {0,0,0,0};

      double LcPAvG = ((y1 + y2 + y3 + y4)/n);
      Double_t y[n] = {y1 - LcPAvG,y2 - LcPAvG,y3 - LcPAvG,y4 - LcPAvG};
      Double_t yerr[n] = {yerr1,yerr2,yerr3,yerr4};
      gLcP = new TGraphErrors(n,x,y,xerr,yerr);
      gLcP->SetMarkerColor(2);
      gLcP->SetMarkerStyle(20);
      gLcP->GetXaxis()->SetNdivisions(4);
      gLcP->GetXaxis()->SetTitle("LambdaC_P Regions");
      gLcP->GetYaxis()->SetTitle("Measured Mass - Average Mass [MeV]");
      gLcP->SetTitle("Deviations in LambdaC_MM of Different LambdaC_P Regions");
      gLcP->Draw("ap");
      c1->Write("Lcplus_P Statistics");
   
    PolarityMagDown->Fit("MagDownFitSG");
    PolarityMagDown->SetMinimum(0);
    c1->Write("PolarityMagDown");

    PolarityMagUp->Fit("MagUpFitSG");
    PolarityMagUp->SetMinimum(0);
    c1->Write("PolarityMagUp");

    double p1 = MagDownFitSG->GetParameter(1);
    double p2 = MagUpFitSG->GetParameter(1);

    double perr1 = MagDownFitSG->GetParError(1);
    double perr2 = MagUpFitSG->GetParError(1);

      const Int_t m = 2;

    double PolarityAvG = ((p1 + p2)/m);
    Double_t p[m] = {p1 - PolarityAvG,p2 - PolarityAvG};
    Double_t perr[m] = {perr1,perr2};

    gPolarity = new TGraphErrors(m,x,p,xerr,perr);
    gPolarity->SetMarkerColor(2);
    gPolarity->SetMarkerStyle(20);
    gPolarity->GetXaxis()->SetNdivisions(2);
    gPolarity->GetXaxis()->SetTitle("Magnet Orientations");
    gPolarity->GetYaxis()->SetTitle("Measured Mass - Average Mass [MeV]");
    gPolarity->SetTitle("Deviations in LambdaC_MM of Different Magnet Orientations");
    gPolarity->Draw("ap");
    c1->Write("Polarity Statistics");

    Particle->Fit("ParticleFitSG");
    Particle->SetMinimum(0);
    c1->Write("Baryon");

    AntiParticle->Fit("AntiParticleFitSG");
    AntiParticle->SetMinimum(0);
    c1->Write("AntiBaryon");

    double pp1 = ParticleFitSG->GetParameter(1);
    double pp2 = AntiParticleFitSG->GetParameter(1);

    double pperr1 = ParticleFitSG->GetParError(1);
    double pperr2 = AntiParticleFitSG->GetParError(1);

    double ParticleAvG = ((pp1 + pp2)/m);
    Double_t pp[m] = {pp1 - ParticleAvG,pp2 - ParticleAvG};
    Double_t pperr[m] = {pperr1,pperr2};

    gPID = new TGraphErrors(m,x,pp,xerr,pperr);
    gPID->SetMarkerColor(2);
    gPID->SetMarkerStyle(20);
    gPID->GetXaxis()->SetNdivisions(2);
    gPID->GetXaxis()->SetTitle("Particle ID");
    gPID->GetYaxis()->SetTitle("Measured Mass - Average Mass [MeV]");
    gPID->SetTitle("Deviations in LambdaC_MM of Baryon or AntiBaryon");
    gPID->Draw("ap");
    c1->Write("ParticleStatistics");
   
        File->Close();
}
