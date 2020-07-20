#define CrystalBallTest_cxx
#include "CrystalBallTest.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

#include "CrystalBallHalfMeV.C"
#include "CrystalBall1MeV.C"
#include "DGOneMuOneTotalHalfMeV.C"
#include "DGOneMuOneTotal1MeV.C"

TH1D * MassHistHalfMeV = nullptr;
TH1D * MassHist1MeV = nullptr;

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

TFile * File = nullptr;

TCanvas * c1 = nullptr;
TCanvas * ex1 = nullptr;
TCanvas * grid = nullptr;

void CrystalBallTest::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
   
   MassHistHalfMeV= new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 300, 2210, 2360);
   MassHistHalfMeV->GetXaxis()->SetTitle("MeV");
   MassHistHalfMeV->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   MassHist1MeV= new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 150, 2210, 2360);
   MassHist1MeV->GetXaxis()->SetTitle("MeV");
   MassHist1MeV->GetYaxis()->SetTitle("Events Per 1 MeV");
   
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
   
   File = new TFile("CrystalFitTest.root", "RECREATE");
  gFile = File;

   c1 = new TCanvas("canvas", "Test Canvas");
   ex1 = new TCanvas("ex1","Latex",500,600);
   grid = new TCanvas("grid", "Grid Canvas");
}

void CrystalBallTest::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

}

Bool_t CrystalBallTest::Process(Long64_t entry)
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
   
bool Cuts= (
     ((*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp) > 0.87)
  && ((*Kminus_ProbNNk)*(*Kplus_ProbNNk) > 0.9)
  && (*Proton_ProbNNp > 0.9) 
  && (M2_KpKm > 1.02)
  && (M2_KpKm < 1.06)   
  && ((TMath::Log10(*Proton_IPCHI2_OWNPV) < 2.5))
  && ((TMath::Log10(*Kminus_IPCHI2_OWNPV) < 2.5))
  && ((TMath::Log10(*Kplus_IPCHI2_OWNPV) < 2.5))   
  && (*Proton_PT > 950)
  && (*Lcplus_Loki_DOCACHI2MAX < 18)
  && (*Lcplus_TAU < 0.002) 
      );
   
 
   if (Cuts){
     MassHistHalfMeV->Fill(*Lcplus_M);
     MassHist1MeV->Fill(*Lcplus_M); 
     LcPDistribution->Fill(*Lcplus_P);
   }  
   
       bool LcLowPCut = (
     (*Lcplus_P < 66000.)
   );

   bool LcMidLowPCut = (
     (*Lcplus_P > 66000. && *Lcplus_P < 88000.)
   );

   bool LcMidHighPCut = (
     (*Lcplus_P > 88000. && *Lcplus_P < 115000.)
   );

   bool LcHighPCut = (
     (*Lcplus_P > 115000.)
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
   
 if (Cuts && LcLowPCut){
   LcLowP->Fill(*Lcplus_M);}
  
    if (Cuts && LcMidLowPCut){
   LcMidLowP->Fill(*Lcplus_M);}
 
       if (Cuts && LcMidHighPCut){
   LcMidHighP->Fill(*Lcplus_M);}
   
          if (Cuts && LcHighPCut){
   LcHighP->Fill(*Lcplus_M);}
   
   ///////////////
   
  if (Cuts && MagDown){
   PolarityMagDown->Fill(*Lcplus_M);}
  
    if (Cuts && MagUp){
   PolarityMagUp->Fill(*Lcplus_M);}
 
  /////////////// 
   
       if (Cuts && Particles){
   Particle->Fill(*Lcplus_M);}
   
          if (Cuts && AntiParticles){
   AntiParticle->Fill(*Lcplus_M);}  

   return kTRUE;
}

void CrystalBallTest::SlaveTerminate()
{
}

void CrystalBallTest::Terminate()
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

TF1 *GaussianHalfMeVDG1Mu = new TF1("GaussianHalfMeVDG1Mu",DGOneMuOneTotalHalfMeV,2200.,2400.,7);
GaussianHalfMeVDG1Mu->SetParameter(0, 0.4);
GaussianHalfMeVDG1Mu->SetParameter(1, 12000);
GaussianHalfMeVDG1Mu->SetParameter(2, 2287.);
GaussianHalfMeVDG1Mu->SetParameter(3, 3);
GaussianHalfMeVDG1Mu->SetParameter(4, 6);
GaussianHalfMeVDG1Mu->SetParLimits(3, 0., 20.);
GaussianHalfMeVDG1Mu->SetParLimits(4, 0., 20.);
GaussianHalfMeVDG1Mu->SetParameter(5, 0.);
GaussianHalfMeVDG1Mu->SetParameter(6, 0.);

pad1->cd();
MassHistHalfMeV->SetMinimum(0);
MassHistHalfMeV->Fit("GaussianHalfMeVDG1Mu");

int BinHeightHalfMeVDG1Mu[300];
int FitHeightHalfMeVDG1Mu[300];
double PullHalfMeVDG1Mu[300];

double   HalfMeVDG1Mucount1 = 0;
double   HalfMeVDG1Mucount2 = 0;
double   HalfMeVDG1Mucount3 = 0;

for (int bin = 0; bin < 300; bin++){
BinHeightHalfMeVDG1Mu[bin] = MassHistHalfMeV->GetBinContent(bin + 1);
PullxHalfMeV[bin] = (bin + 1);   
int xvalueHalfMeVDG1Mu = 2210.25 + 0.5*(bin);
FitHeightHalfMeVDG1Mu[bin] = round(GaussianHalfMeVDG1Mu->Eval(xvalueHalfMeVDG1Mu));
PullHalfMeVDG1Mu[bin] = (BinHeightHalfMeVDG1Mu[bin] - FitHeightHalfMeVDG1Mu[bin])/TMath::Sqrt(FitHeightHalfMeVDG1Mu[bin]);

if (PullHalfMeVDG1Mu[bin] > -1 && PullHalfMeVDG1Mu[bin] < 1){
HalfMeVDG1Mucount1 += 1;
}

if (PullHalfMeVDG1Mu[bin] > -2 && PullHalfMeVDG1Mu[bin] < 2){
HalfMeVDG1Mucount2 += 1;
}

if (PullHalfMeVDG1Mu[bin] > -3 && PullHalfMeVDG1Mu[bin] < 3){
HalfMeVDG1Mucount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotHalfMeVDG1Mu = new TGraph(300, PullxHalfMeV, PullHalfMeVDG1Mu);
PullPlotHalfMeVDG1Mu->GetXaxis()->SetLimits(0.5,300.5);
PullPlotHalfMeVDG1Mu->GetXaxis()->SetTickLength(0.);
PullPlotHalfMeVDG1Mu->GetYaxis()->SetTickLength(0.);
PullPlotHalfMeVDG1Mu->SetFillColor(38);
PullPlotHalfMeVDG1Mu->GetYaxis()->SetTitle("Pull");
PullPlotHalfMeVDG1Mu->GetYaxis()->CenterTitle();
PullPlotHalfMeVDG1Mu->GetYaxis()->SetTitleSize(0.10);
PullPlotHalfMeVDG1Mu->GetYaxis()->SetTitleOffset(0.2);
PullPlotHalfMeVDG1Mu->GetXaxis()->SetLabelSize(0);
PullPlotHalfMeVDG1Mu->GetYaxis()->SetLabelFont(42);
PullPlotHalfMeVDG1Mu->GetYaxis()->SetLabelSize(0.06);
PullPlotHalfMeVDG1Mu->SetTitle("");
PullPlotHalfMeVDG1Mu->SetMinimum(-5);
PullPlotHalfMeVDG1Mu->SetMaximum(5);
PullPlotHalfMeVDG1Mu->Draw("AB");
MassHistHalfMeV->SetTitle("#Lambda_{c}^{+} Mass - Double Gaussian Fit");
    c1->Write("Lc Mass - HalfMeVDG1Mu");

ex1->cd();
   TLatex Tl;
   Tl.SetTextAlign(12);
   Tl.SetTextSize(0.04);
 Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianHalfMeVDG1Mu->GetParameter(1)));
 Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianHalfMeVDG1Mu->GetParError(1)));
 Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianHalfMeVDG1Mu->GetParameter(0)));
 Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianHalfMeVDG1Mu->GetParError(0)));
 Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianHalfMeVDG1Mu->GetParameter(2)));
 Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianHalfMeVDG1Mu->GetParError(2)));
 Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianHalfMeVDG1Mu->GetParameter(3)));
 Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianHalfMeVDG1Mu->GetParError(3)));
 Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianHalfMeVDG1Mu->GetParameter(4)));
 Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianHalfMeVDG1Mu->GetParError(4)));
 Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", HalfMeVDG1Mucount1));
 Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", HalfMeVDG1Mucount2));
 Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", HalfMeVDG1Mucount3));
 ex1->Write(" Fit Values - HalfMeVDG1Mu");
c1->cd();
   
TF1 *CrystalBallFunctionHalfMeV = new TF1("CrystalBallFunctionHalfMeV", CrystalBallHalfMeV,2100.,2500.,7);
CrystalBallFunctionHalfMeV->SetParameter(0,2287.);
CrystalBallFunctionHalfMeV->SetParLimits(0, 2285., 2288.);
CrystalBallFunctionHalfMeV->SetParameter(1, 4.1);
CrystalBallFunctionHalfMeV->SetParLimits(1, 3., 6.);
CrystalBallFunctionHalfMeV->SetParameter(2, 110000);   
CrystalBallFunctionHalfMeV->SetParameter(3, 8.);
CrystalBallFunctionHalfMeV->SetParLimits(3, 0., 30.);   
CrystalBallFunctionHalfMeV->SetParameter(4, 8.);
CrystalBallFunctionHalfMeV->SetParLimits(4, 0., 30.);     
CrystalBallFunctionHalfMeV->SetParameter(5, 0.);
CrystalBallFunctionHalfMeV->SetParameter(6, 0.);

pad1->cd();
MassHistHalfMeV->SetMinimum(0);
MassHistHalfMeV->Fit("CrystalBallFunctionHalfMeV");

int BinHeightCBHalfMeV[300];
int FitHeightCBHalfMeV[300];
double PullCBHalfMeV[300];

double CBHalfMeV1 = 0;
double CBHalfMeV2 = 0;
double CBHalfMeV3 = 0;

for (int bin = 0; bin < 300; bin++){
BinHeightCBHalfMeV[bin] = MassHistHalfMeV->GetBinContent(bin + 1);
int xvalue = 2210.25 + 0.5*(bin);
FitHeightCBHalfMeV[bin] = round(CrystalBallFunctionHalfMeV->Eval(xvalue));
PullCBHalfMeV[bin] = (BinHeightCBHalfMeV[bin] - FitHeightCBHalfMeV[bin])/TMath::Sqrt(FitHeightCBHalfMeV[bin]);

if (PullCBHalfMeV[bin] > -1 && PullCBHalfMeV[bin] < 1){
  CBHalfMeV1 += 1;
}

if (PullCBHalfMeV[bin] > -2 && PullCBHalfMeV[bin] < 2){
  CBHalfMeV2 += 1;
}

if (PullCBHalfMeV[bin] > -3 && PullCBHalfMeV[bin] < 3){
  CBHalfMeV3 += 1;
}
}

pad2->cd();
TGraph* PullCBHalfMeVPlot = new TGraph(300, PullxHalfMeV, PullCBHalfMeV);
PullCBHalfMeVPlot->GetXaxis()->SetLimits(0.5,300.5);
PullCBHalfMeVPlot->GetXaxis()->SetTickLength(0.);
PullCBHalfMeVPlot->GetYaxis()->SetTickLength(0.);
PullCBHalfMeVPlot->SetFillColor(38);
PullCBHalfMeVPlot->GetYaxis()->SetTitle("Pull");
PullCBHalfMeVPlot->GetYaxis()->CenterTitle();
PullCBHalfMeVPlot->GetYaxis()->SetTitleSize(0.10);
PullCBHalfMeVPlot->GetYaxis()->SetTitleOffset(0.2);
PullCBHalfMeVPlot->GetXaxis()->SetLabelSize(0);
PullCBHalfMeVPlot->GetYaxis()->SetLabelFont(42);
PullCBHalfMeVPlot->GetYaxis()->SetLabelSize(0.06);
PullCBHalfMeVPlot->SetTitle("");
PullCBHalfMeVPlot->SetMinimum(-5);
PullCBHalfMeVPlot->SetMaximum(5);
PullCBHalfMeVPlot->Draw("AB");
MassHistHalfMeV->SetTitle("#Lambda_{c}^{+} Mass - Crystal Ball Fit");   
      c1->Write("Lc Mass - Crystal Ball Half MeV");

ex1->cd();
ex1->Clear();
   Tl.DrawLatex(0.1,0.9,Form("Mean Value: %f MeV", CrystalBallFunctionHalfMeV->GetParameter(0)));
   Tl.DrawLatex(0.1,0.85,Form("Error: %f MeV", CrystalBallFunctionHalfMeV->GetParError(0)));
   Tl.DrawLatex(0.1,0.7,Form("Sigma: %f MeV", CrystalBallFunctionHalfMeV->GetParameter(1)));
   Tl.DrawLatex(0.1,0.65,Form("Error: %f MeV", CrystalBallFunctionHalfMeV->GetParError(1)));
   Tl.DrawLatex(0.1,0.5,Form("Signal Events: %f Events", CrystalBallFunctionHalfMeV->GetParameter(2)));
   Tl.DrawLatex(0.1,0.45,Form("Error: %f Events", CrystalBallFunctionHalfMeV->GetParError(2)));
   Tl.DrawLatex(0.1,0.3,Form("Bins Between -1 & 1 %f Bins", CBHalfMeV1));
   Tl.DrawLatex(0.1,0.2,Form("Bins Between -2 & 2 %f Bins", CBHalfMeV2));
   Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", CBHalfMeV3));
   ex1->Write("Crystal Ball Fit Values Half MeV");
c1->cd();
   

TF1 *Gaussian1MeVDG1Mu = new TF1("Gaussian1MeVDG1Mu",DGOneMuOneTotal1MeV,2200.,2400.,7);
Gaussian1MeVDG1Mu->SetParameter(0, 0.4);
Gaussian1MeVDG1Mu->SetParameter(1, 12000);
Gaussian1MeVDG1Mu->SetParameter(2, 2287.);
Gaussian1MeVDG1Mu->SetParameter(3, 3);
Gaussian1MeVDG1Mu->SetParameter(4, 6);
Gaussian1MeVDG1Mu->SetParLimits(3, 0., 20.);
Gaussian1MeVDG1Mu->SetParLimits(4, 0., 20.);
Gaussian1MeVDG1Mu->SetParameter(5, 0.);
Gaussian1MeVDG1Mu->SetParameter(6, 0.);

pad1->cd();
MassHist1MeV->SetMinimum(0);
MassHist1MeV->Fit("Gaussian1MeVDG1Mu");

int BinHeight1MeVDG1Mu[150];
int FitHeight1MeVDG1Mu[150];
double Pull1MeVDG1Mu[150];

double   DG1MeVDG1Mucount1 = 0;
double   DG1MeVDG1Mucount2 = 0;
double   DG1MeVDG1Mucount3 = 0;

for (int bin = 0; bin < 150; bin++){
BinHeight1MeVDG1Mu[bin] = MassHist1MeV->GetBinContent(bin + 1);
Pullx1MeV[bin] = (bin + 1);   
int xvalue1MeVDG1Mu = 2210.5 + 1*(bin);
FitHeight1MeVDG1Mu[bin] = round(Gaussian1MeVDG1Mu->Eval(xvalue1MeVDG1Mu));
Pull1MeVDG1Mu[bin] = (BinHeight1MeVDG1Mu[bin] - FitHeight1MeVDG1Mu[bin])/TMath::Sqrt(FitHeight1MeVDG1Mu[bin]);

if (Pull1MeVDG1Mu[bin] > -1 && Pull1MeVDG1Mu[bin] < 1){
DG1MeVDG1Mucount1 += 1;
}

if (Pull1MeVDG1Mu[bin] > -2 && Pull1MeVDG1Mu[bin] < 2){
DG1MeVDG1Mucount2 += 1;
}

if (Pull1MeVDG1Mu[bin] > -3 && Pull1MeVDG1Mu[bin] < 3){
DG1MeVDG1Mucount3 += 1;
}
}

pad2->cd();
TGraph* PullPlot1MeVDG1Mu = new TGraph(150, Pullx1MeV, Pull1MeVDG1Mu);
PullPlot1MeVDG1Mu->GetXaxis()->SetLimits(0.5,150.5);
PullPlot1MeVDG1Mu->GetXaxis()->SetTickLength(0.);
PullPlot1MeVDG1Mu->GetYaxis()->SetTickLength(0.);
PullPlot1MeVDG1Mu->SetFillColor(38);
PullPlot1MeVDG1Mu->GetYaxis()->SetTitle("Pull");
PullPlot1MeVDG1Mu->GetYaxis()->CenterTitle();
PullPlot1MeVDG1Mu->GetYaxis()->SetTitleSize(0.10);
PullPlot1MeVDG1Mu->GetYaxis()->SetTitleOffset(0.2);
PullPlot1MeVDG1Mu->GetXaxis()->SetLabelSize(0);
PullPlot1MeVDG1Mu->GetYaxis()->SetLabelFont(42);
PullPlot1MeVDG1Mu->GetYaxis()->SetLabelSize(0.06);
PullPlot1MeVDG1Mu->SetTitle("");
PullPlot1MeVDG1Mu->SetMinimum(-5);
PullPlot1MeVDG1Mu->SetMaximum(5);
PullPlot1MeVDG1Mu->Draw("AB");
MassHist1MeV->SetTitle("#Lambda_{c}^{+} Mass - Double Gaussian Fit");
    c1->Write("Lc Mass - 1MeVDG1Mu");

ex1->cd();
 ex1->Clear();
 Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", Gaussian1MeVDG1Mu->GetParameter(1)));
 Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", Gaussian1MeVDG1Mu->GetParError(1)));
 Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", Gaussian1MeVDG1Mu->GetParameter(0)));
 Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", Gaussian1MeVDG1Mu->GetParError(0)));
 Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", Gaussian1MeVDG1Mu->GetParameter(2)));
 Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", Gaussian1MeVDG1Mu->GetParError(2)));
 Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", Gaussian1MeVDG1Mu->GetParameter(3)));
 Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", Gaussian1MeVDG1Mu->GetParError(3)));
 Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", Gaussian1MeVDG1Mu->GetParameter(4)));
 Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", Gaussian1MeVDG1Mu->GetParError(4)));
 Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", DG1MeVDG1Mucount1));
 Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", DG1MeVDG1Mucount2));
 Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", DG1MeVDG1Mucount3));
 ex1->Write(" Fit Values - 1MeVDG1Mu");   
   
TF1 *CrystalBallFunction1MeV = new TF1("CrystalBallFunction1MeV", CrystalBall1MeV,2100.,2500.,7);
CrystalBallFunction1MeV->SetParameter(0,2287.);
CrystalBallFunction1MeV->SetParLimits(0, 2285., 2288.);
CrystalBallFunction1MeV->SetParameter(1, 4.1);
CrystalBallFunction1MeV->SetParLimits(1, 3., 6.);
CrystalBallFunction1MeV->SetParameter(2, 110000);   
CrystalBallFunction1MeV->SetParameter(3, 8.);
CrystalBallFunction1MeV->SetParLimits(3, 0., 30.);   
CrystalBallFunction1MeV->SetParameter(4, 8.);
CrystalBallFunction1MeV->SetParLimits(4, 0., 30.);     
CrystalBallFunction1MeV->SetParameter(5, 0.);
CrystalBallFunction1MeV->SetParameter(6, 0.);

pad1->cd();
MassHist1MeV->SetMinimum(0);
MassHist1MeV->Fit("CrystalBallFunction1MeV");

int BinHeightCB1MeV[150];
int FitHeightCB1MeV[150];
double PullCB1MeV[150];

double CB1MeV1 = 0;
double CB1MeV2 = 0;
double CB1MeV3 = 0;

for (int bin = 0; bin < 150; bin++){
BinHeightCB1MeV[bin] = MassHist1MeV->GetBinContent(bin + 1);
int xvalue = 2210.5 + 1.0*(bin);
FitHeightCB1MeV[bin] = round(CrystalBallFunction1MeV->Eval(xvalue));
PullCB1MeV[bin] = (BinHeightCB1MeV[bin] - FitHeightCB1MeV[bin])/TMath::Sqrt(FitHeightCB1MeV[bin]);

if (PullCB1MeV[bin] > -1 && PullCB1MeV[bin] < 1){
  CB1MeV1 += 1;
}

if (PullCB1MeV[bin] > -2 && PullCB1MeV[bin] < 2){
  CB1MeV2 += 1;
}

if (PullCB1MeV[bin] > -3 && PullCB1MeV[bin] < 3){
  CB1MeV3 += 1;
}
}

pad2->cd();
TGraph* PullCB1MeVPlot = new TGraph(150, Pullx1MeV, PullCB1MeV);
PullCB1MeVPlot->GetXaxis()->SetLimits(0.5,150.5);
PullCB1MeVPlot->GetXaxis()->SetTickLength(0.);
PullCB1MeVPlot->GetYaxis()->SetTickLength(0.);
PullCB1MeVPlot->SetFillColor(38);
PullCB1MeVPlot->GetYaxis()->SetTitle("Pull");
PullCB1MeVPlot->GetYaxis()->CenterTitle();
PullCB1MeVPlot->GetYaxis()->SetTitleSize(0.10);
PullCB1MeVPlot->GetYaxis()->SetTitleOffset(0.2);
PullCB1MeVPlot->GetXaxis()->SetLabelSize(0);
PullCB1MeVPlot->GetYaxis()->SetLabelFont(42);
PullCB1MeVPlot->GetYaxis()->SetLabelSize(0.06);
PullCB1MeVPlot->SetTitle("");
PullCB1MeVPlot->SetMinimum(-5);
PullCB1MeVPlot->SetMaximum(5);
PullCB1MeVPlot->Draw("AB");
MassHist1MeV->SetTitle("#Lambda_{c}^{+} Mass - Crystal Ball Fit");   
      c1->Write("Lc Mass - Crystal Ball 1 MeV");

ex1->cd();
ex1->Clear();
   Tl.DrawLatex(0.1,0.9,Form("Mean Value: %f MeV", CrystalBallFunction1MeV->GetParameter(0)));
   Tl.DrawLatex(0.1,0.85,Form("Error: %f MeV", CrystalBallFunction1MeV->GetParError(0)));
   Tl.DrawLatex(0.1,0.7,Form("Sigma: %f MeV", CrystalBallFunction1MeV->GetParameter(1)));
   Tl.DrawLatex(0.1,0.65,Form("Error: %f MeV", CrystalBallFunction1MeV->GetParError(1)));
   Tl.DrawLatex(0.1,0.5,Form("Signal Events: %f Events", CrystalBallFunction1MeV->GetParameter(2)));
   Tl.DrawLatex(0.1,0.45,Form("Error: %f Events", CrystalBallFunction1MeV->GetParError(2)));
   Tl.DrawLatex(0.1,0.3,Form("Bins Between -1 & 1 %f Bins", CB1MeV1));
   Tl.DrawLatex(0.1,0.2,Form("Bins Between -2 & 2 %f Bins", CB1MeV2));
   Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", CB1MeV3));
   ex1->Write("Crystal Ball Fit Values 1 MeV");
c1->cd();
   

 TF1 *LcFitSG1 = new TF1("LcFitSG1",CrystalBallHalfMeV,2200.,2400.,7);
LcFitSG1->SetParameter(0,2287.);
LcFitSG1->SetParLimits(0, 2285., 2288.);
LcFitSG1->SetParameter(1, 4.1);
LcFitSG1->SetParLimits(1, 3., 6.);
LcFitSG1->SetParameter(2, 110000);   
LcFitSG1->SetParameter(3, 8.);
LcFitSG1->SetParLimits(3, 0., 30.);   
LcFitSG1->SetParameter(4, 8.);
LcFitSG1->SetParLimits(4, 0., 30.);     
LcFitSG1->SetParameter(5, 0.);
LcFitSG1->SetParameter(6, 0.);

 TF1 *LcFitSG2 = new TF1("LcFitSG2",CrystalBallHalfMeV,2200.,2400.,7);
LcFitSG2->SetParameter(0,2287.);
LcFitSG2->SetParLimits(0, 2285., 2288.);
LcFitSG2->SetParameter(1, 4.1);
LcFitSG2->SetParLimits(1, 3., 6.);
LcFitSG2->SetParameter(2, 110000);   
LcFitSG2->SetParameter(3, 8.);
LcFitSG2->SetParLimits(3, 0., 30.);   
LcFitSG2->SetParameter(4, 8.);
LcFitSG2->SetParLimits(4, 0., 30.);     
LcFitSG2->SetParameter(5, 0.);
LcFitSG2->SetParameter(6, 0.);

 TF1 *LcFitSG3 = new TF1("LcFitSG3",CrystalBallHalfMeV,2200.,2400.,7);
LcFitSG3->SetParameter(0,2287.);
LcFitSG3->SetParLimits(0, 2285., 2288.);
LcFitSG3->SetParameter(1, 4.1);
LcFitSG3->SetParLimits(1, 3., 6.);
LcFitSG3->SetParameter(2, 110000);   
LcFitSG3->SetParameter(3, 8.);
LcFitSG3->SetParLimits(3, 0., 30.);   
LcFitSG3->SetParameter(4, 8.);
LcFitSG3->SetParLimits(4, 0., 30.);     
LcFitSG3->SetParameter(5, 0.);
LcFitSG3->SetParameter(6, 0.);

 TF1 *LcFitSG4 = new TF1("LcFitSG4",CrystalBallHalfMeV,2200.,2400.,7);
LcFitSG4->SetParameter(0,2287.);
LcFitSG4->SetParLimits(0, 2285., 2288.);
LcFitSG4->SetParameter(1, 4.1);
LcFitSG4->SetParLimits(1, 3., 6.);
LcFitSG4->SetParameter(2, 110000);   
LcFitSG4->SetParameter(3, 8.);
LcFitSG4->SetParLimits(3, 0., 30.);   
LcFitSG4->SetParameter(4, 8.);
LcFitSG4->SetParLimits(4, 0., 30.);     
LcFitSG4->SetParameter(5, 0.);
LcFitSG4->SetParameter(6, 0.);
 
  TF1 *MagDownFitSG = new TF1("MagDownFitSG",CrystalBallHalfMeV,2200.,2400.,7);
MagDownFitSG->SetParameter(0,2287.);
MagDownFitSG->SetParLimits(0, 2285., 2288.);
MagDownFitSG->SetParameter(1, 4.1);
MagDownFitSG->SetParLimits(1, 3., 6.);
MagDownFitSG->SetParameter(2, 110000);   
MagDownFitSG->SetParameter(3, 8.);
MagDownFitSG->SetParLimits(3, 0., 30.);   
MagDownFitSG->SetParameter(4, 8.);
MagDownFitSG->SetParLimits(4, 0., 30.);     
MagDownFitSG->SetParameter(5, 0.);
MagDownFitSG->SetParameter(6, 0.);
 
 TF1 *MagUpFitSG = new TF1("MagUpFitSG",CrystalBallHalfMeV,2200.,2400.,7);
MagUpFitSG->SetParameter(0,2287.);
MagUpFitSG->SetParLimits(0, 2285., 2288.);
MagUpFitSG->SetParameter(1, 4.1);
MagUpFitSG->SetParLimits(1, 3., 6.);
MagUpFitSG->SetParameter(2, 110000);   
MagUpFitSG->SetParameter(3, 8.);
MagUpFitSG->SetParLimits(3, 0., 30.);   
MagUpFitSG->SetParameter(4, 8.);
MagUpFitSG->SetParLimits(4, 0., 30.);     
MagUpFitSG->SetParameter(5, 0.);
MagUpFitSG->SetParameter(6, 0.);
 
 TF1 *ParticleFitSG = new TF1("ParticleFitSG",CrystalBallHalfMeV,2200.,2400.,7);
ParticleFitSG->SetParameter(0,2287.);
ParticleFitSG->SetParLimits(0, 2285., 2288.);
ParticleFitSG->SetParameter(1, 4.1);
ParticleFitSG->SetParLimits(1, 3., 6.);
ParticleFitSG->SetParameter(2, 110000);   
ParticleFitSG->SetParameter(3, 8.);
ParticleFitSG->SetParLimits(3, 0., 30.);   
ParticleFitSG->SetParameter(4, 8.);
ParticleFitSG->SetParLimits(4, 0., 30.);     
ParticleFitSG->SetParameter(5, 0.);
ParticleFitSG->SetParameter(6, 0.);
 
 TF1 *AntiParticleFitSG = new TF1("AntiParticleFitSG",CrystalBallHalfMeV,2200.,2400.,7);
AntiParticleFitSG->SetParameter(0,2287.);
AntiParticleFitSG->SetParLimits(0, 2285., 2288.);
AntiParticleFitSG->SetParameter(1, 4.1);
AntiParticleFitSG->SetParLimits(1, 3., 6.);
AntiParticleFitSG->SetParameter(2, 110000);   
AntiParticleFitSG->SetParameter(3, 8.);
AntiParticleFitSG->SetParLimits(3, 0., 30.);   
AntiParticleFitSG->SetParameter(4, 8.);
AntiParticleFitSG->SetParLimits(4, 0., 30.);     
AntiParticleFitSG->SetParameter(5, 0.);
AntiParticleFitSG->SetParameter(6, 0.);
 
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

 double y1 = LcFitSG1->GetParameter(0);
 double y2 = LcFitSG2->GetParameter(0);
 double y3 = LcFitSG3->GetParameter(0);
 double y4 = LcFitSG4->GetParameter(0);

 double yerr1 = LcFitSG1->GetParError(0);
 double yerr2 = LcFitSG2->GetParError(0);
 double yerr3 = LcFitSG3->GetParError(0);
 double yerr4 = LcFitSG4->GetParError(0);

 const Int_t n = 4;
 Double_t x[n] = {1,2,3,4};
 Double_t xerr[n] = {0,0,0,0};

grid->cd();
grid->SetGridy();

 double LcPAvG = ((y1 + y2 + y3 + y4)/n);
 Double_t y[n] = {y1 - LcPAvG,y2 - LcPAvG,y3 - LcPAvG,y4 - LcPAvG};
 Double_t yerr[n] = {yerr1,yerr2,yerr3,yerr4};
 gLcP = new TGraphErrors(n,x,y,xerr,yerr);
 gLcP->SetMarkerColor(2);
 gLcP->SetMarkerStyle(20);
 gLcP->GetXaxis()->SetNdivisions(4);
 gLcP->GetXaxis()->SetTitle("LambdaC P Regions");
 gLcP->GetYaxis()->SetTitle("Measured Mass - Average Mass [MeV]");
 gLcP->SetTitle("Deviations in LambdaC Mass of Different LambdaC_P Regions");
 gLcP->Draw("ap");
 gLcP->GetXaxis()->SetAlphanumeric();
 gLcP->GetXaxis()->SetBinLabel(9, "(0-70) GeV");
 gLcP->GetXaxis()->SetBinLabel(36, "(70-88.5) GeV");
 gLcP->GetXaxis()->SetBinLabel(63, "(88.5-112) GeV");
 gLcP->GetXaxis()->SetBinLabel(90, "(112-250) GeV");   
 gLcP->GetXaxis()->LabelsOption("h");
 grid->Write("Lcplus_P Statistics");

c1->cd();

PolarityMagDown->Fit("MagDownFitSG");
PolarityMagDown->SetMinimum(0);
c1->Write("PolarityMagDown");

PolarityMagUp->Fit("MagUpFitSG");
PolarityMagUp->SetMinimum(0);
c1->Write("PolarityMagUp");

double p1 = MagDownFitSG->GetParameter(0);
double p2 = MagUpFitSG->GetParameter(0);

double perr1 = MagDownFitSG->GetParError(0);
double perr2 = MagUpFitSG->GetParError(0);

 const Int_t m = 2;

double PolarityAvG = ((p1 + p2)/m);
Double_t p[m] = {p1 - PolarityAvG,p2 - PolarityAvG};
Double_t perr[m] = {perr1,perr2};

grid->cd();

gPolarity = new TGraphErrors(m,x,p,xerr,perr);
gPolarity->SetMarkerColor(2);
gPolarity->SetMarkerStyle(20);
gPolarity->GetXaxis()->SetNdivisions(2);
gPolarity->GetXaxis()->SetTitle("Magnet Orientations");
gPolarity->GetYaxis()->SetTitle("Measured Mass - Average Mass [MeV]");
gPolarity->SetTitle("Deviations in LambdaC Mass of Different Magnet Orientations");
gPolarity->GetXaxis()->SetAlphanumeric();
gPolarity->GetXaxis()->SetBinLabel(9, "MagDown");
gPolarity->GetXaxis()->SetBinLabel(92, "MagUp");   
gPolarity->GetXaxis()->LabelsOption("h");   
gPolarity->Draw("ap");

grid->Write("Polarity Statistics");

c1->cd();

Particle->Fit("ParticleFitSG");
Particle->SetMinimum(0);
c1->Write("Baryon");

AntiParticle->Fit("AntiParticleFitSG");
AntiParticle->SetMinimum(0);
c1->Write("AntiBaryon");

double pp1 = ParticleFitSG->GetParameter(0);
double pp2 = AntiParticleFitSG->GetParameter(0);

double pperr1 = ParticleFitSG->GetParError(0);
double pperr2 = AntiParticleFitSG->GetParError(0);

double ParticleAvG = ((pp1 + pp2)/m);
Double_t pp[m] = {pp1 - ParticleAvG,pp2 - ParticleAvG};
Double_t pperr[m] = {pperr1,pperr2};

grid->cd();
 
gPID = new TGraphErrors(m,x,pp,xerr,pperr);
gPID->SetMarkerColor(2);
gPID->SetMarkerStyle(20);
gPID->GetXaxis()->SetNdivisions(2);
gPID->GetXaxis()->SetTitle("Particle ID");
gPID->GetYaxis()->SetTitle("Measured Mass - Average Mass [MeV]");
gPID->SetTitle("Deviations in LambdaC Mass of Baryon or AntiBaryon");
gPID->GetXaxis()->SetAlphanumeric();
gPID->GetXaxis()->SetBinLabel(9, "Baryon");
gPID->GetXaxis()->SetBinLabel(92, "AntiBaryon");   
gPID->GetXaxis()->LabelsOption("h");   
gPID->Draw("ap");
grid->Write("ParticleStatistics");

   File->Close();
}
