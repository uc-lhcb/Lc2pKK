/////Add Fit and Stat Analysis For Looser Cut

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
#include "GaussCrystalHalfMeV.C"
#include "GaussCrystal1MeV.C"
#include "NewCrystalBallHalfMeV.C"
#include "NewCrystalBall1MeV.C"

TH1D * SignalHistLoose = nullptr;
TH1D * MassHistHalfMeVLoose = nullptr;
TH1D * MassHist1MeVLoose = nullptr;

TH1D * LcLowPLoose = nullptr;
TH1D * LcMidLowPLoose = nullptr;
TH1D * LcMidHighPLoose = nullptr;
TH1D * LcHighPLoose = nullptr;
TH1D * LcPDistributionLoose = nullptr;

TH1D * PolarityMagUpLoose = nullptr;
TH1D * PolarityMagDownLoose = nullptr;

TH1D * ParticleLoose = nullptr;
TH1D * AntiParticleLoose = nullptr;

TGraphErrors * gLcPLoose = nullptr;
TGraphErrors * gXiPLoose = nullptr;
TGraphErrors * gPolarityLoose = nullptr;
TGraphErrors * gPIDLoose = nullptr;

TFile * File = nullptr;

TCanvas * c1 = nullptr;
TCanvas * ex1 = nullptr;
TCanvas * grid = nullptr;

void CrystalBallTest::Begin(TTree * /*tree*/)
{
   TString option = GetOption();  

TH1::SetDefaultSumw2(kTRUE);
   
   SignalHistLoose = new TH1D("Mass [MeV]", "Lc Mass - Signal", 300, 2212, 2362);
   SignalHistLoose->GetXaxis()->SetTitle("MeV");
   SignalHistLoose->GetYaxis()->SetTitle("Events Per 1/2 MeV");   
   
   MassHistHalfMeVLoose= new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 300, 2212, 2362);
   MassHistHalfMeVLoose->GetXaxis()->SetTitle("MeV");
   MassHistHalfMeVLoose->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   MassHist1MeVLoose = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 150, 2212, 2362);
   MassHist1MeVLoose->GetXaxis()->SetTitle("MeV");
   MassHist1MeVLoose->GetYaxis()->SetTitle("Events Per 1 MeV");
   
LcLowPLoose = new TH1D("Figures of Merit", "LambdaC Mass - Low LcP", 300, 2212, 2362);
LcLowPLoose->GetXaxis()->SetTitle("MeV");
LcLowPLoose->GetYaxis()->SetTitle("Events Per 1/2 MeV");

LcMidLowPLoose = new TH1D("Figures of Merit", "LambdaC Mass - MidLow LcP", 300, 2212, 2362);
LcMidLowPLoose->GetXaxis()->SetTitle("MeV");
LcMidLowPLoose->GetYaxis()->SetTitle("Events Per 1/2 MeV");

LcMidHighPLoose = new TH1D("Figures of Merit", "LambdaC Mass - MidHigh LcP", 300, 2212, 2362);
LcMidHighPLoose->GetXaxis()->SetTitle("MeV");
LcMidHighPLoose->GetYaxis()->SetTitle("Events Per 1/2 MeV");

LcHighPLoose = new TH1D("Figures of Merit", "LambdaC Mass - High LcP", 300, 2212, 2362);
LcHighPLoose->GetXaxis()->SetTitle("MeV");
LcHighPLoose->GetYaxis()->SetTitle("Events Per 1/2 MeV");

LcPDistributionLoose = new TH1D("Figures of Merit", "LcP Distribution After Cuts", 300, 0, 250000);
LcPDistributionLoose->GetXaxis()->SetTitle("MeV");
LcPDistributionLoose->GetYaxis()->SetTitle("Events Per 2500 MeV");
   
PolarityMagDownLoose = new TH1D("Figures of Merit", "LambdaC Mass - MagnetDown", 300, 2212, 2362);
PolarityMagDownLoose->GetXaxis()->SetTitle("MeV");
PolarityMagDownLoose->GetYaxis()->SetTitle("Events Per 1/2 MeV");

PolarityMagUpLoose = new TH1D("Figures of Merit", "LambdaC Mass - MagnetUp", 300, 2212, 2362);
PolarityMagUpLoose->GetXaxis()->SetTitle("MeV");
PolarityMagUpLoose->GetYaxis()->SetTitle("Events Per 1/2 MeV");

ParticleLoose = new TH1D("Figures of Merit", "LambdaC Mass - LambdaC Baryon", 300, 2212, 2362);
ParticleLoose->GetXaxis()->SetTitle("MeV");
ParticleLoose->GetYaxis()->SetTitle("Events Per 1/2 MeV");

AntiParticleLoose = new TH1D("Figures of Merit", "LambdaC Mass - LambdaC AntiBaryon", 300, 2212, 2362);
AntiParticleLoose->GetXaxis()->SetTitle("MeV");
AntiParticleLoose->GetYaxis()->SetTitle("Events Per 1/2 MeV");
   
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


bool LooseCuts= (
  ((*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp) > 0.75)
&& ((*Kminus_ProbNNk)*(*Kplus_ProbNNk) > 0.8)
&& (*Proton_ProbNNp > 0.8) 
&& (M2_KpKm > 1.02)
&& (M2_KpKm < 1.06)   
);

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
   
   if (LooseCuts){
     MassHistHalfMeVLoose->Fill(*Lcplus_M);
     MassHist1MeVLoose->Fill(*Lcplus_M); 
     LcPDistributionLoose->Fill(*Lcplus_P);
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
   
 if (LooseCuts && LcLowPCut){
   LcLowPLoose->Fill(*Lcplus_M);}
  
    if (LooseCuts && LcMidLowPCut){
   LcMidLowPLoose->Fill(*Lcplus_M);}
 
       if (LooseCuts && LcMidHighPCut){
   LcMidHighPLoose->Fill(*Lcplus_M);}
   
          if (LooseCuts && LcHighPCut){
   LcHighPLoose->Fill(*Lcplus_M);}
   
   ///////////////
   
  if (LooseCuts && MagDown){
   PolarityMagDownLoose->Fill(*Lcplus_M);}
  
    if (LooseCuts && MagUp){
   PolarityMagUpLoose->Fill(*Lcplus_M);}
 
  /////////////// 
   
       if (LooseCuts && Particles){
   ParticleLoose->Fill(*Lcplus_M);}
   
          if (LooseCuts && AntiParticles){
   AntiParticleLoose->Fill(*Lcplus_M);}  

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
TSpectrum *sLoose = new TSpectrum(); 
TH1 * BackgroundHistLoose = sLoose->Background(MassHistHalfMeV, 100,"");  
MassHistHalfMeVLoose->Draw();
 BackgroundHistLoose->Draw("SAME"); 
 c1->Write("Background Estimate - Loose");
 c1->Clear();
   
SignalHistLoose->Add(MassHistHalfMeVLoose,BackgroundHistLoose,1.0,-1.0);
SignalHistLoose->SetMinimum(0); 
SignalHistLoose->SetMaximum(6250);   
SignalHistLoose->Draw();  
 MassHistHalfMeVLoose->Draw("SAME"); 
 c1->Write("Signal Estimate - Loose");
  c1->Clear();

double PullxHalfMeV[300];
double Pullx1MeV[150];
   
TPad *pad1 = new TPad("pad1","pad1",0,0.33,1,1);
TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.33);
pad2->SetTopMargin(0.03030303);
pad1->Draw();
pad2->Draw();

TF1 *GaussianHalfMeVDG1MuLoose = new TF1("GaussianHalfMeVDG1MuLoose",DGOneMuOneTotalHalfMeV,2200.,2400.,7);
GaussianHalfMeVDG1MuLoose->SetParameter(0, 0.4);
GaussianHalfMeVDG1MuLoose->SetParameter(1, 12000);
GaussianHalfMeVDG1MuLoose->SetParameter(2, 2287.);
GaussianHalfMeVDG1MuLoose->SetParameter(3, 3);
GaussianHalfMeVDG1MuLoose->SetParameter(4, 6);
GaussianHalfMeVDG1MuLoose->SetParLimits(3, 0., 20.);
GaussianHalfMeVDG1MuLoose->SetParLimits(4, 0., 20.);
GaussianHalfMeVDG1MuLoose->SetParameter(5, 0.);
GaussianHalfMeVDG1MuLoose->SetParameter(6, 0.);

pad1->cd();
MassHistHalfMeV->SetMinimum(0);
MassHistHalfMeV->Fit("GaussianHalfMeVDG1MuLoose");

int BinHeightHalfMeVDG1MuLoose[300];
int FitHeightHalfMeVDG1MuLoose[300];
double PullHalfMeVDG1MuLoose[300];

double   HalfMeVDG1MuLoosecount1 = 0;
double   HalfMeVDG1MuLoosecount2 = 0;
double   HalfMeVDG1MuLoosecount3 = 0;

for (int bin = 0; bin < 300; bin++){
BinHeightHalfMeVDG1MuLoose[bin] = MassHistHalfMeV->GetBinContent(bin + 1);
PullxHalfMeV[bin] = (bin + 1);   
int xvalueHalfMeVDG1Mu = 2212.25 + 0.5*(bin);
FitHeightHalfMeVDG1MuLoose[bin] = round(GaussianHalfMeVDG1MuLoose->Eval(xvalueHalfMeVDG1Mu));
PullHalfMeVDG1MuLoose[bin] = (BinHeightHalfMeVDG1MuLoose[bin] - FitHeightHalfMeVDG1MuLoose[bin])/TMath::Sqrt(FitHeightHalfMeVDG1MuLoose[bin]);

if (PullHalfMeVDG1MuLoose[bin] > -1 && PullHalfMeVDG1MuLoose[bin] < 1){
HalfMeVDG1MuLoosecount1 += 1;
}

if (PullHalfMeVDG1MuLoose[bin] > -2 && PullHalfMeVDG1MuLoose[bin] < 2){
HalfMeVDG1MuLoosecount2 += 1;
}

if (PullHalfMeVDG1MuLoose[bin] > -3 && PullHalfMeVDG1MuLoose[bin] < 3){
HalfMeVDG1MuLoosecount3 += 1;
}
}

pad2->cd();
TGraph* PullPlotHalfMeVDG1MuLoose = new TGraph(300, PullxHalfMeV, PullHalfMeVDG1MuLoose);
PullPlotHalfMeVDG1MuLoose->GetXaxis()->SetLimits(0.5,300.5);
PullPlotHalfMeVDG1MuLoose->GetXaxis()->SetTickLength(0.);
PullPlotHalfMeVDG1MuLoose->GetYaxis()->SetTickLength(0.);
PullPlotHalfMeVDG1MuLoose->SetFillColor(38);
PullPlotHalfMeVDG1MuLoose->GetYaxis()->SetTitle("Pull");
PullPlotHalfMeVDG1MuLoose->GetYaxis()->CenterTitle();
PullPlotHalfMeVDG1MuLoose->GetYaxis()->SetTitleSize(0.10);
PullPlotHalfMeVDG1MuLoose->GetYaxis()->SetTitleOffset(0.2);
PullPlotHalfMeVDG1MuLoose->GetXaxis()->SetLabelSize(0);
PullPlotHalfMeVDG1MuLoose->GetYaxis()->SetLabelFont(42);
PullPlotHalfMeVDG1MuLoose->GetYaxis()->SetLabelSize(0.06);
PullPlotHalfMeVDG1MuLoose->SetTitle("");
PullPlotHalfMeVDG1MuLoose->SetMinimum(-5);
PullPlotHalfMeVDG1MuLoose->SetMaximum(5);
PullPlotHalfMeVDG1MuLoose->Draw("AB");
MassHistHalfMeV->SetTitle("#Lambda_{c}^{+} Mass - Double Gaussian Fit");
  c1->Write("Lc Mass Loose - HalfMeVDG1Mu");

ex1->cd();
 TLatex Tl;
 Tl.SetTextAlign(12);
 Tl.SetTextSize(0.04);
Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", GaussianHalfMeVDG1MuLoose->GetParameter(1)));
Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", GaussianHalfMeVDG1MuLoose->GetParError(1)));
Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", GaussianHalfMeVDG1MuLoose->GetParameter(0)));
Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", GaussianHalfMeVDG1MuLoose->GetParError(0)));
Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", GaussianHalfMeVDG1MuLoose->GetParameter(2)));
Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", GaussianHalfMeVDG1MuLoose->GetParError(2)));
Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", GaussianHalfMeVDG1MuLoose->GetParameter(3)));
Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", GaussianHalfMeVDG1MuLoose->GetParError(3)));
Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", GaussianHalfMeVDG1MuLoose->GetParameter(4)));
Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", GaussianHalfMeVDG1MuLoose->GetParError(4)));
Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", HalfMeVDG1MuLoosecount1));
Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", HalfMeVDG1MuLoosecount2));
Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", HalfMeVDG1MuLoosecount3));
ex1->Write(" Fit Values Loose - HalfMeVDG1Mu");
c1->cd();

TF1 *CrystalBallFunctionHalfMeVLoose = new TF1("CrystalBallFunctionHalfMeVLoose", NewCrystalBallHalfMeV,2212.,2362.,9);
CrystalBallFunctionHalfMeVLoose->SetParameter(0,115000); 
CrystalBallFunctionHalfMeVLoose->SetParameter(1, 2285.);
CrystalBallFunctionHalfMeVLoose->SetParameter(2, 5);  
CrystalBallFunctionHalfMeVLoose->SetParameter(3, 4);  
CrystalBallFunctionHalfMeVLoose->SetParameter(4, 0.7);
CrystalBallFunctionHalfMeVLoose->SetParLimits(4, 0.001, 0.999);   
CrystalBallFunctionHalfMeVLoose->SetParameter(5, 750.);   
CrystalBallFunctionHalfMeVLoose->SetParameter(6, -0.2);     
CrystalBallFunctionHalfMeVLoose->SetParameter(7, 2.0);
CrystalBallFunctionHalfMeVLoose->SetParameter(8, 3.0);   
CrystalBallFunctionHalfMeVLoose->SetParLimits(8, 1.000001, 8.);   
   
pad1->cd();
MassHistHalfMeV->SetMinimum(0);
MassHistHalfMeV->Fit("CrystalBallFunctionHalfMeVLoose");

int BinHeightCBHalfMeVLoose[300];
int FitHeightCBHalfMeVLoose[300];
double PullCBHalfMeVLoose[300];

double CBHalfMeVLoosecount1 = 0;
double CBHalfMeVLoosecount2 = 0;
double CBHalfMeVLoosecount3 = 0;

for (int bin = 0; bin < 300; bin++){
BinHeightCBHalfMeVLoose[bin] = MassHistHalfMeV->GetBinContent(bin + 1);
int xvalue = 2212.25 + 0.5*(bin);
FitHeightCBHalfMeVLoose[bin] = round(CrystalBallFunctionHalfMeVLoose->Eval(xvalue));
PullCBHalfMeVLoose[bin] = (BinHeightCBHalfMeVLoose[bin] - FitHeightCBHalfMeVLoose[bin])/TMath::Sqrt(FitHeightCBHalfMeVLoose[bin]);

if (PullCBHalfMeVLoose[bin] > -1 && PullCBHalfMeVLoose[bin] < 1){
CBHalfMeVLoosecount1 += 1;
}

if (PullCBHalfMeVLoose[bin] > -2 && PullCBHalfMeVLoose[bin] < 2){
CBHalfMeVLoosecount2 += 1;
}

if (PullCBHalfMeVLoose[bin] > -3 && PullCBHalfMeVLoose[bin] < 3){
CBHalfMeVLoosecount3 += 1;
}
}

pad2->cd();
TGraph* PullCBHalfMeVPlotLoose = new TGraph(300, PullxHalfMeV, PullCBHalfMeVLoose);
PullCBHalfMeVPlotLoose->GetXaxis()->SetLimits(0.5,300.5);
PullCBHalfMeVPlotLoose->GetXaxis()->SetTickLength(0.);
PullCBHalfMeVPlotLoose->GetYaxis()->SetTickLength(0.);
PullCBHalfMeVPlotLoose->SetFillColor(38);
PullCBHalfMeVPlotLoose->GetYaxis()->SetTitle("Pull");
PullCBHalfMeVPlotLoose->GetYaxis()->CenterTitle();
PullCBHalfMeVPlotLoose->GetYaxis()->SetTitleSize(0.10);
PullCBHalfMeVPlotLoose->GetYaxis()->SetTitleOffset(0.2);
PullCBHalfMeVPlotLoose->GetXaxis()->SetLabelSize(0);
PullCBHalfMeVPlotLoose->GetYaxis()->SetLabelFont(42);
PullCBHalfMeVPlotLoose->GetYaxis()->SetLabelSize(0.06);
PullCBHalfMeVPlotLoose->SetTitle("");
PullCBHalfMeVPlotLoose->SetMinimum(-5);
PullCBHalfMeVPlotLoose->SetMaximum(5);
PullCBHalfMeVPlotLoose->Draw("AB");
MassHistHalfMeV->SetTitle("#Lambda_{c}^{+} Mass - Crystal Ball Fit");   
    c1->Write("Lc Mass Loose - Crystal Ball Half MeV");
// c1->Clear();

ex1->cd();
ex1->Clear();
 Tl.DrawLatex(0.1,0.9,Form("Mean Value: %f MeV", CrystalBallFunctionHalfMeVLoose->GetParameter(0)));
 Tl.DrawLatex(0.1,0.85,Form("Error: %f MeV", CrystalBallFunctionHalfMeVLoose->GetParError(0)));
 Tl.DrawLatex(0.1,0.7,Form("Sigma: %f MeV", CrystalBallFunctionHalfMeVLoose->GetParameter(1)));
 Tl.DrawLatex(0.1,0.65,Form("Error: %f MeV", CrystalBallFunctionHalfMeVLoose->GetParError(1)));
 Tl.DrawLatex(0.1,0.5,Form("Signal Events: %f Events", CrystalBallFunctionHalfMeVLoose->GetParameter(2)));
 Tl.DrawLatex(0.1,0.45,Form("Error: %f Events", CrystalBallFunctionHalfMeVLoose->GetParError(2)));
 Tl.DrawLatex(0.1,0.3,Form("Bins Between -1 & 1 %f Bins", CBHalfMeVLoosecount1));
 Tl.DrawLatex(0.1,0.2,Form("Bins Between -2 & 2 %f Bins", CBHalfMeVLoosecount2));
 Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", CBHalfMeVLoosecount3));
 ex1->Write("Fit Values Loose - CBHalfMeV");
c1->cd();
 

TF1 *Gaussian1MeVDG1MuLoose = new TF1("Gaussian1MeVDG1MuLoose",DGOneMuOneTotal1MeV,2212.,2362.,7);
Gaussian1MeVDG1MuLoose->SetParameter(0, 0.4);
Gaussian1MeVDG1MuLoose->SetParameter(1, 12000);
Gaussian1MeVDG1MuLoose->SetParameter(2, 2287.);
Gaussian1MeVDG1MuLoose->SetParameter(3, 3);
Gaussian1MeVDG1MuLoose->SetParameter(4, 6);
Gaussian1MeVDG1MuLoose->SetParLimits(3, 0., 20.);
Gaussian1MeVDG1MuLoose->SetParLimits(4, 0., 20.);
Gaussian1MeVDG1MuLoose->SetParameter(5, 0.);
Gaussian1MeVDG1MuLoose->SetParameter(6, 0.);

pad1->cd();
MassHist1MeV->SetMinimum(0);
MassHist1MeV->Fit("Gaussian1MeVDG1MuLoose");

int BinHeight1MeVDG1MuLoose[150];
int FitHeight1MeVDG1MuLoose[150];
double Pull1MeVDG1MuLoose[150];

double   DG1MeVDG1MuLoosecount1 = 0;
double   DG1MeVDG1MuLoosecount2 = 0;
double   DG1MeVDG1MuLoosecount3 = 0;

for (int bin = 0; bin < 150; bin++){
BinHeight1MeVDG1MuLoose[bin] = MassHist1MeV->GetBinContent(bin + 1);
Pullx1MeV[bin] = (bin + 1);   
int xvalue1MeVDG1Mu = 2212.5 + 1*(bin);
FitHeight1MeVDG1MuLoose[bin] = round(Gaussian1MeVDG1MuLoose->Eval(xvalue1MeVDG1Mu));
Pull1MeVDG1MuLoose[bin] = (BinHeight1MeVDG1MuLoose[bin] - FitHeight1MeVDG1MuLoose[bin])/TMath::Sqrt(FitHeight1MeVDG1MuLoose[bin]);

if (Pull1MeVDG1MuLoose[bin] > -1 && Pull1MeVDG1MuLoose[bin] < 1){
DG1MeVDG1MuLoosecount1 += 1;
}

if (Pull1MeVDG1MuLoose[bin] > -2 && Pull1MeVDG1MuLoose[bin] < 2){
DG1MeVDG1MuLoosecount2 += 1;
}

if (Pull1MeVDG1MuLoose[bin] > -3 && Pull1MeVDG1MuLoose[bin] < 3){
DG1MeVDG1MuLoosecount3 += 1;
}
}

pad2->cd();
TGraph* PullPlot1MeVDG1MuLoose = new TGraph(150, Pullx1MeV, Pull1MeVDG1MuLoose);
PullPlot1MeVDG1MuLoose->GetXaxis()->SetLimits(0.5,150.5);
PullPlot1MeVDG1MuLoose->GetXaxis()->SetTickLength(0.);
PullPlot1MeVDG1MuLoose->GetYaxis()->SetTickLength(0.);
PullPlot1MeVDG1MuLoose->SetFillColor(38);
PullPlot1MeVDG1MuLoose->GetYaxis()->SetTitle("Pull");
PullPlot1MeVDG1MuLoose->GetYaxis()->CenterTitle();
PullPlot1MeVDG1MuLoose->GetYaxis()->SetTitleSize(0.10);
PullPlot1MeVDG1MuLoose->GetYaxis()->SetTitleOffset(0.2);
PullPlot1MeVDG1MuLoose->GetXaxis()->SetLabelSize(0);
PullPlot1MeVDG1MuLoose->GetYaxis()->SetLabelFont(42);
PullPlot1MeVDG1MuLoose->GetYaxis()->SetLabelSize(0.06);
PullPlot1MeVDG1MuLoose->SetTitle("");
PullPlot1MeVDG1MuLoose->SetMinimum(-5);
PullPlot1MeVDG1MuLoose->SetMaximum(5);
PullPlot1MeVDG1MuLoose->Draw("AB");
MassHist1MeV->SetTitle("#Lambda_{c}^{+} Mass - Double Gaussian Fit");
  c1->Write("Lc Mass Loose - 1MeVDG1Mu");
// c1->Clear();

ex1->cd();
ex1->Clear();
Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", Gaussian1MeVDG1MuLoose->GetParameter(1)));
Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", Gaussian1MeVDG1MuLoose->GetParError(1)));
Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", Gaussian1MeVDG1MuLoose->GetParameter(0)));
Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", Gaussian1MeVDG1MuLoose->GetParError(0)));
Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", Gaussian1MeVDG1MuLoose->GetParameter(2)));
Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", Gaussian1MeVDG1MuLoose->GetParError(2)));
Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", Gaussian1MeVDG1MuLoose->GetParameter(3)));
Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", Gaussian1MeVDG1MuLoose->GetParError(3)));
Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", Gaussian1MeVDG1MuLoose->GetParameter(4)));
Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", Gaussian1MeVDG1MuLoose->GetParError(4)));
Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", DG1MeVDG1MuLoosecount1));
Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", DG1MeVDG1MuLoosecount2));
Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", DG1MeVDG1MuLoosecount3));
ex1->Write(" Fit Values Loose - 1MeVDG1Mu");   

TF1 *CrystalBallFunction1MeVLoose = new TF1("CrystalBallFunction1MeVLoose", NewCrystalBall1MeV,2212.,2362.,9);
CrystalBallFunction1MeVLoose->SetParameter(0,115000); 
CrystalBallFunction1MeVLoose->SetParameter(1, 2285.);
CrystalBallFunction1MeVLoose->SetParameter(2, 5);  
CrystalBallFunction1MeVLoose->SetParameter(3, 4);  
CrystalBallFunction1MeVLoose->SetParameter(4, 0.7);
CrystalBallFunction1MeVLoose->SetParLimits(4, 0.001, 0.999);   
CrystalBallFunction1MeVLoose->SetParameter(5, 750.);   
CrystalBallFunction1MeVLoose->SetParameter(6, -0.2);     
CrystalBallFunction1MeVLoose->SetParameter(7, 2.0);
CrystalBallFunction1MeVLoose->SetParameter(8, 3.0);   
CrystalBallFunction1MeVLoose->SetParLimits(8, 1.000001, 8.);    
 
pad1->cd();
MassHist1MeV->SetMinimum(0);
MassHist1MeV->Fit("CrystalBallFunction1MeVLoose");

int BinHeightCB1MeVLoose[150];
int FitHeightCB1MeVLoose[150];
double PullCB1MeVLoose[150];

double CB1MeVLoosecount1 = 0;
double CB1MeVLoosecount2 = 0;
double CB1MeVLoosecount3 = 0;

for (int bin = 0; bin < 150; bin++){
BinHeightCB1MeVLoose[bin] = MassHist1MeV->GetBinContent(bin + 1);
int xvalue = 2212.5 + 1.0*(bin);
FitHeightCB1MeVLoose[bin] = round(CrystalBallFunction1MeVLoose->Eval(xvalue));
PullCB1MeVLoose[bin] = (BinHeightCB1MeVLoose[bin] - FitHeightCB1MeVLoose[bin])/TMath::Sqrt(FitHeightCB1MeVLoose[bin]);

if (PullCB1MeVLoose[bin] > -1 && PullCB1MeVLoose[bin] < 1){
CB1MeVLoosecount1 += 1;
}

if (PullCB1MeVLoose[bin] > -2 && PullCB1MeVLoose[bin] < 2){
CB1MeVLoosecount2 += 1;
}

if (PullCB1MeVLoose[bin] > -3 && PullCB1MeVLoose[bin] < 3){
CB1MeVLoosecount3 += 1;
}
}

pad2->cd();
TGraph* PullCB1MeVPlotLoose = new TGraph(150, Pullx1MeV, PullCB1MeVLoose);
PullCB1MeVPlotLoose->GetXaxis()->SetLimits(0.5,150.5);
PullCB1MeVPlotLoose->GetXaxis()->SetTickLength(0.);
PullCB1MeVPlotLoose->GetYaxis()->SetTickLength(0.);
PullCB1MeVPlotLoose->SetFillColor(38);
PullCB1MeVPlotLoose->GetYaxis()->SetTitle("Pull");
PullCB1MeVPlotLoose->GetYaxis()->CenterTitle();
PullCB1MeVPlotLoose->GetYaxis()->SetTitleSize(0.10);
PullCB1MeVPlotLoose->GetYaxis()->SetTitleOffset(0.2);
PullCB1MeVPlotLoose->GetXaxis()->SetLabelSize(0);
PullCB1MeVPlotLoose->GetYaxis()->SetLabelFont(42);
PullCB1MeVPlotLoose->GetYaxis()->SetLabelSize(0.06);
PullCB1MeVPlotLoose->SetTitle("");
PullCB1MeVPlotLoose->SetMinimum(-5);
PullCB1MeVPlotLoose->SetMaximum(5);
PullCB1MeVPlotLoose->Draw("AB");
MassHist1MeV->SetTitle("#Lambda_{c}^{+} Mass - Crystal Ball Fit");   
    c1->Write("Lc Mass Loose - Crystal Ball 1 MeV");
// c1->Clear();

ex1->cd();
ex1->Clear();
 Tl.DrawLatex(0.1,0.9,Form("Mean Value: %f MeV", CrystalBallFunction1MeVLoose->GetParameter(0)));
 Tl.DrawLatex(0.1,0.85,Form("Error: %f MeV", CrystalBallFunction1MeVLoose->GetParError(0)));
 Tl.DrawLatex(0.1,0.7,Form("Sigma: %f MeV", CrystalBallFunction1MeVLoose->GetParameter(1)));
 Tl.DrawLatex(0.1,0.65,Form("Error: %f MeV", CrystalBallFunction1MeVLoose->GetParError(1)));
 Tl.DrawLatex(0.1,0.5,Form("Signal Events: %f Events", CrystalBallFunction1MeVLoose->GetParameter(2)));
 Tl.DrawLatex(0.1,0.45,Form("Error: %f Events", CrystalBallFunction1MeVLoose->GetParError(2)));
 Tl.DrawLatex(0.1,0.3,Form("Bins Between -1 & 1 %f Bins", CB1MeVLoosecount1));
 Tl.DrawLatex(0.1,0.2,Form("Bins Between -2 & 2 %f Bins", CB1MeVLoosecount2));
 Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", CB1MeVLoosecount3));
 ex1->Write("Fit Values Loose - CB1MeV");
c1->cd();

TF1 *LcFitSGLoose1 = new TF1("LcFitSGLoose1", NewCrystalBallHalfMeV,2212.,2362.,9);
LcFitSGLoose1->SetParameter(0,115000); 
LcFitSGLoose1->SetParameter(1, 2285.);
LcFitSGLoose1->SetParameter(2, 5);  
LcFitSGLoose1->SetParameter(3, 4);  
LcFitSGLoose1->SetParameter(4, 0.7);
LcFitSGLoose1->SetParLimits(4, 0.001, 0.999);   
LcFitSGLoose1->SetParameter(5, 750.);   
LcFitSGLoose1->SetParameter(6, -0.2);     
LcFitSGLoose1->SetParameter(7, 2.0);
LcFitSGLoose1->SetParameter(8, 3.0);   
LcFitSGLoose1->SetParLimits(8, 1.000001, 8.);  
   
TF1 *LcFitSGLoose2 = new TF1("LcFitSGLoose2", NewCrystalBallHalfMeV,2212.,2362.,9);
LcFitSGLoose2->SetParameter(0,115000); 
LcFitSGLoose2->SetParameter(1, 2285.);
LcFitSGLoose2->SetParameter(2, 5);  
LcFitSGLoose2->SetParameter(3, 4);  
LcFitSGLoose2->SetParameter(4, 0.7);
LcFitSGLoose2->SetParLimits(4, 0.001, 0.999);   
LcFitSGLoose2->SetParameter(5, 750.);   
LcFitSGLoose2->SetParameter(6, -0.2);     
LcFitSGLoose2->SetParameter(7, 2.0);
LcFitSGLoose2->SetParameter(8, 3.0);   
LcFitSGLoose2->SetParLimits(8, 1.000001, 8.);  

TF1 *LcFitSGLoose3 = new TF1("LcFitSGLoose3", NewCrystalBallHalfMeV,2212.,2362.,9);
LcFitSGLoose3->SetParameter(0,115000); 
LcFitSGLoose3->SetParameter(1, 2285.);
LcFitSGLoose3->SetParameter(2, 5);  
LcFitSGLoose3->SetParameter(3, 4);  
LcFitSGLoose3->SetParameter(4, 0.7);
LcFitSGLoose3->SetParLimits(4, 0.001, 0.999);   
LcFitSGLoose3->SetParameter(5, 750.);   
LcFitSGLoose3->SetParameter(6, -0.2);     
LcFitSGLoose3->SetParameter(7, 2.0);
LcFitSGLoose3->SetParameter(8, 3.0);   
LcFitSGLoose3->SetParLimits(8, 1.000001, 8.);  

TF1 *LcFitSGLoose4 = new TF1("LcFitSGLoose4", NewCrystalBallHalfMeV,2212.,2362.,9);
LcFitSGLoose4->SetParameter(0,115000); 
LcFitSGLoose4->SetParameter(1, 2285.);
LcFitSGLoose4->SetParameter(2, 5);  
LcFitSGLoose4->SetParameter(3, 4);  
LcFitSGLoose4->SetParameter(4, 0.7);
LcFitSGLoose4->SetParLimits(4, 0.001, 0.999);   
LcFitSGLoose4->SetParameter(5, 750.);   
LcFitSGLoose4->SetParameter(6, -0.2);     
LcFitSGLoose4->SetParameter(7, 2.0);
LcFitSGLoose4->SetParameter(8, 3.0);   
LcFitSGLoose4->SetParLimits(8, 1.000001, 8.);  
 
TF1 *MagDownFitSGLoose = new TF1("MagDownFitSGLoose", NewCrystalBallHalfMeV,2212.,2362.,9);
MagDownFitSGLoose->SetParameter(0,115000); 
MagDownFitSGLoose->SetParameter(1, 2285.);
MagDownFitSGLoose->SetParameter(2, 5);  
MagDownFitSGLoose->SetParameter(3, 4);  
MagDownFitSGLoose->SetParameter(4, 0.7);
MagDownFitSGLoose->SetParLimits(4, 0.001, 0.999);   
MagDownFitSGLoose->SetParameter(5, 750.);   
MagDownFitSGLoose->SetParameter(6, -0.2);     
MagDownFitSGLoose->SetParameter(7, 2.0);
MagDownFitSGLoose->SetParameter(8, 3.0);   
MagDownFitSGLoose->SetParLimits(8, 1.000001, 8.);  
 
TF1 *MagUpFitSGLoose = new TF1("MagUpFitSGLoose", NewCrystalBallHalfMeV,2212.,2362.,9);
MagUpFitSGLoose->SetParameter(0,115000); 
MagUpFitSGLoose->SetParameter(1, 2285.);
MagUpFitSGLoose->SetParameter(2, 5);  
MagUpFitSGLoose->SetParameter(3, 4);  
MagUpFitSGLoose->SetParameter(4, 0.7);
MagUpFitSGLoose->SetParLimits(4, 0.001, 0.999);   
MagUpFitSGLoose->SetParameter(5, 750.);   
MagUpFitSGLoose->SetParameter(6, -0.2);     
MagUpFitSGLoose->SetParameter(7, 2.0);
MagUpFitSGLoose->SetParameter(8, 3.0);   
MagUpFitSGLoose->SetParLimits(8, 1.000001, 8.);  
 
TF1 *ParticleFitSGLoose = new TF1("ParticleFitSGLoose", NewCrystalBallHalfMeV,2212.,2362.,9);
ParticleFitSGLoose->SetParameter(0,115000); 
ParticleFitSGLoose->SetParameter(1, 2285.);
ParticleFitSGLoose->SetParameter(2, 5);  
ParticleFitSGLoose->SetParameter(3, 4);  
ParticleFitSGLoose->SetParameter(4, 0.7);
ParticleFitSGLoose->SetParLimits(4, 0.001, 0.999);   
ParticleFitSGLoose->SetParameter(5, 750.);   
ParticleFitSGLoose->SetParameter(6, -0.2);     
ParticleFitSGLoose->SetParameter(7, 2.0);
ParticleFitSGLoose->SetParameter(8, 3.0);   
ParticleFitSGLoose->SetParLimits(8, 1.000001, 8.);  
 
TF1 *AntiParticleFitSGLoose = new TF1("AntiParticleFitSGLoose", NewCrystalBallHalfMeV,2212.,2362.,9);
AntiParticleFitSGLoose->SetParameter(0,115000); 
AntiParticleFitSGLoose->SetParameter(1, 2285.);
AntiParticleFitSGLoose->SetParameter(2, 5);  
AntiParticleFitSGLoose->SetParameter(3, 4);  
AntiParticleFitSGLoose->SetParameter(4, 0.7);
AntiParticleFitSGLoose->SetParLimits(4, 0.001, 0.999);   
AntiParticleFitSGLoose->SetParameter(5, 750.);   
AntiParticleFitSGLoose->SetParameter(6, -0.2);     
AntiParticleFitSGLoose->SetParameter(7, 2.0);
AntiParticleFitSGLoose->SetParameter(8, 3.0);   
AntiParticleFitSGLoose->SetParLimits(8, 1.000001, 8.);  
 
  LcLowPLoose->Fit("LcFitSGLoose1");
 LcLowPLoose->SetMinimum(0);
 c1->Write("Low Lc Momentum Region - Loose");
 c1->Clear();

 LcMidLowPLoose->Fit("LcFitSGLoose2");
 LcMidLowPLoose->SetMinimum(0);
 c1->Write("MidLow Lc Momentum Region - Loose");
 c1->Clear();

 LcMidHighPLoose->Fit("LcFitSGLoose3");
 LcMidHighPLoose->SetMinimum(0);
 c1->Write("MidHigh Lc Momentum Region - Loose");
 c1->Clear();

 LcHighPLoose->Fit("LcFitSGLoose4");
 LcHighPLoose->SetMinimum(0);
 c1->Write("High Lc Momentum Region - Loose");
 c1->Clear();

 LcPDistributionLoose->Draw();
 LcPDistributionLoose->SetMinimum(0);
 c1->Write("Lc Momentum Distribution - Loose");
 c1->Clear();

 double yLoose1 = LcFitSGLoose1->GetParameter(1);
 double yLoose2 = LcFitSGLoose2->GetParameter(1);
 double yLoose3 = LcFitSGLoose3->GetParameter(1);
 double yLoose4 = LcFitSGLoose4->GetParameter(1);

 double yerrLoose1 = LcFitSGLoose1->GetParError(1);
 double yerrLoose2 = LcFitSGLoose2->GetParError(1);
 double yerrLoose3 = LcFitSGLoose3->GetParError(1);
 double yerrLoose4 = LcFitSGLoose4->GetParError(1);

 const Int_t n = 4;
 Double_t x[n] = {1,2,3,4};
 Double_t xerr[n] = {0,0,0,0};

grid->cd();
grid->SetGridy();

 double LcPAvGLoose = ((yLoose1 + yLoose2 + yLoose3 + yLoose4)/n);
 Double_t yLoose[n] = {yLoose1 - LcPAvGLoose,yLoose2 - LcPAvGLoose,yLoose3 - LcPAvGLoose,yLoose4 - LcPAvGLoose};
 Double_t yerrLoose[n] = {yerrLoose1,yerrLoose2,yerrLoose3,yerrLoose4};
 gLcPLoose = new TGraphErrors(n,x,yLoose,xerr,yerrLoose);
 gLcPLoose->SetMarkerColor(2);
 gLcPLoose->SetMarkerStyle(20);
 gLcPLoose->GetXaxis()->SetNdivisions(4);
 gLcPLoose->GetXaxis()->SetTitle("LambdaC P Regions");
 gLcPLoose->GetYaxis()->SetTitle("Measured Mass - Average Mass [MeV]");
 gLcPLoose->SetTitle("Deviations in LambdaC Mass of Different LambdaC_P Regions");
 gLcPLoose->Draw("ap");
 gLcPLoose->GetXaxis()->SetAlphanumeric();
 gLcPLoose->GetXaxis()->SetBinLabel(9, "(0-70) GeV");
 gLcPLoose->GetXaxis()->SetBinLabel(36, "(70-88.5) GeV");
 gLcPLoose->GetXaxis()->SetBinLabel(63, "(88.5-112) GeV");
 gLcPLoose->GetXaxis()->SetBinLabel(90, "(112-250) GeV");   
 gLcPLoose->GetXaxis()->LabelsOption("h");
 grid->Write("Lcplus_P Statistics - Loose");

c1->cd();

PolarityMagDownLoose->Fit("MagDownFitSGLoose");
PolarityMagDownLoose->SetMinimum(0);
c1->Write("PolarityMagDown - Loose");
 c1->Clear();

PolarityMagUpLoose->Fit("MagUpFitSGLoose");
PolarityMagUpLoose->SetMinimum(0);
c1->Write("PolarityMagUp - Loose");
 c1->Clear();

double pLoose1 = MagDownFitSGLoose->GetParameter(1);
double pLoose2 = MagUpFitSGLoose->GetParameter(1);

double perrLoose1 = MagDownFitSGLoose->GetParError(1);
double perrLoose2 = MagUpFitSGLoose->GetParError(1);

 const Int_t m = 2;

double PolarityAvGLoose = ((pLoose1 + pLoose2)/m);
Double_t pLoose[m] = {pLoose1 - PolarityAvGLoose,pLoose2 - PolarityAvGLoose};
Double_t perrLoose[m] = {perrLoose1,perrLoose2};

grid->cd();

gPolarityLoose = new TGraphErrors(m,x,pLoose,xerr,perrLoose);
gPolarityLoose->SetMarkerColor(2);
gPolarityLoose->SetMarkerStyle(20);
gPolarityLoose->GetXaxis()->SetNdivisions(2);
gPolarityLoose->GetXaxis()->SetTitle("Magnet Orientations");
gPolarityLoose->GetYaxis()->SetTitle("Measured Mass - Average Mass [MeV]");
gPolarityLoose->SetTitle("Deviations in LambdaC Mass of Different Magnet Orientations");
gPolarityLoose->GetXaxis()->SetAlphanumeric();
gPolarityLoose->GetXaxis()->SetBinLabel(9, "MagDown");
gPolarityLoose->GetXaxis()->SetBinLabel(92, "MagUp");   
gPolarityLoose->GetXaxis()->LabelsOption("h");   
gPolarityLoose->Draw("ap");

grid->Write("Polarity Statistics - Loose");

c1->cd();

ParticleLoose->Fit("ParticleFitSGLoose");
ParticleLoose->SetMinimum(0);
c1->Write("Baryon - Loose");
 c1->Clear();

AntiParticleLoose->Fit("AntiParticleFitSGLoose");
AntiParticleLoose->SetMinimum(0);
c1->Write("AntiBaryon - Loose");
 c1->Clear();

double ppLoose1 = ParticleFitSGLoose->GetParameter(1);
double ppLoose2 = AntiParticleFitSGLoose->GetParameter(1);

double pperrLoose1 = ParticleFitSGLoose->GetParError(1);
double pperrLoose2 = AntiParticleFitSGLoose->GetParError(1);

double ParticleAvGLoose = ((ppLoose1 + ppLoose2)/m);
Double_t ppLoose[m] = {ppLoose1 - ParticleAvGLoose,ppLoose2 - ParticleAvGLoose};
Double_t pperrLoose[m] = {pperrLoose1,pperrLoose2};

grid->cd();
 
gPIDLoose = new TGraphErrors(m,x,ppLoose,xerr,pperrLoose);
gPIDLoose->SetMarkerColor(2);
gPIDLoose->SetMarkerStyle(20);
gPIDLoose->GetXaxis()->SetNdivisions(2);
gPIDLoose->GetXaxis()->SetTitle("Particle ID");
gPIDLoose->GetYaxis()->SetTitle("Measured Mass - Average Mass [MeV]");
gPIDLoose->SetTitle("Deviations in LambdaC Mass of Baryon or AntiBaryon");
gPIDLoose->GetXaxis()->SetAlphanumeric();
gPIDLoose->GetXaxis()->SetBinLabel(9, "Baryon");
gPIDLoose->GetXaxis()->SetBinLabel(92, "AntiBaryon");   
gPIDLoose->GetXaxis()->LabelsOption("h");   
gPIDLoose->Draw("ap");
grid->Write("ParticleStatistics - Loose");

   File->Close();
}
