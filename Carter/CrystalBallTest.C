#define CrystalBallTest_cxx
#include "CrystalBallTest.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

#include "CrystalBall.C"


TH1D * MassHist = nullptr;

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
   
   MassHist= new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 300, 2210, 2360);
   MassHist->GetXaxis()->SetTitle("MeV");
   MassHist->GetYaxis()->SetTitle("Events Per 1/2 MeV");
   
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
  && (M2_KpKm > 1.024)
  && (M2_KpKm < 1.057)   
  && ((TMath::Log10(*Proton_IPCHI2_OWNPV) < 2.5))
  && ((TMath::Log10(*Kminus_IPCHI2_OWNPV) < 2.5))
  && ((TMath::Log10(*Kplus_IPCHI2_OWNPV) < 2.5))   
  && (*Proton_PT > 950)
//  && (*Lcplus_Loki_DOCACHI2MAX < 18)
//  && (*Lcplus_TAU < 0.0035) 
      );
   
 
   if (Cuts){
     MassHist->Fill(*Lcplus_M);
     LcPDistribution->Fill(*Lcplus_P);
   }  
   
       bool LcLowPCut = (
     (*Lcplus_P < 71000.)
   );

   bool LcMidLowPCut = (
     (*Lcplus_P > 71000. && *Lcplus_P < 88500.)
   );

   bool LcMidHighPCut = (
     (*Lcplus_P > 88500. && *Lcplus_P < 110000.)
   );

   bool LcHighPCut = (
     (*Lcplus_P > 110000.)
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

double Pullx[300];

TPad *pad1 = new TPad("pad1","pad1",0,0.33,1,1);
TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.33);
pad2->SetTopMargin(0.03030303);
pad1->Draw();
pad2->Draw();

TF1 *CrystalBallFunction = new TF1("CrystalBallFunction", CrystalBall,2100.,2500.,7);
CrystalBallFunction->SetParameter(0,2287.);
CrystalBallFunction->SetParLimits(0, 2285., 2288.);
CrystalBallFunction->SetParameter(1, 4.1);
CrystalBallFunction->SetParLimits(1, 3., 6.);
CrystalBallFunction->SetParameter(2, 110000);   
CrystalBallFunction->SetParameter(3, 8.);
CrystalBallFunction->SetParLimits(3, 0., 30.);   
CrystalBallFunction->SetParameter(4, 8.);
CrystalBallFunction->SetParLimits(4, 0., 30.);     
CrystalBallFunction->SetParameter(5, 0.);
CrystalBallFunction->SetParameter(6, 0.);

pad1->cd();
MassHist->SetMinimum(0);
MassHist->Fit("CrystalBallFunction");

int BinHeight[300];
int FitHeight[300];
double Pull[300];

double count1 = 0;
double count2 = 0;
double count3 = 0;

for (int bin = 0; bin < 300; bin++){
BinHeight[bin] = MassHist->GetBinContent(bin + 1);
Pullx[bin] = (bin + 1);
int xvalue = 2210.25 + 0.5*(bin);
FitHeight[bin] = round(CrystalBallFunction->Eval(xvalue));
Pull[bin] = (BinHeight[bin] - FitHeight[bin])/TMath::Sqrt(FitHeight[bin]);

if (Pull[bin] > -1 && Pull[bin] < 1){
  count1 += 1;
}

if (Pull[bin] > -2 && Pull[bin] < 2){
  count2 += 1;
}

if (Pull[bin] > -3 && Pull[bin] < 3){
  count3 += 1;
}
}

pad2->cd();
TGraph* PullPlot = new TGraph(300, Pullx, Pull);
PullPlot->GetXaxis()->SetLimits(0.5,300.5);
PullPlot->GetXaxis()->SetTickLength(0.);
PullPlot->GetYaxis()->SetTickLength(0.);
PullPlot->SetFillColor(38);
PullPlot->GetYaxis()->SetTitle("Pull");
PullPlot->GetYaxis()->CenterTitle();
PullPlot->GetYaxis()->SetTitleSize(0.10);
PullPlot->GetYaxis()->SetTitleOffset(0.2);
PullPlot->GetXaxis()->SetLabelSize(0);
PullPlot->GetYaxis()->SetLabelFont(42);
PullPlot->GetYaxis()->SetLabelSize(0.06);
PullPlot->SetTitle("");
PullPlot->SetMinimum(-5);
PullPlot->SetMaximum(5);
PullPlot->Draw("AB");
      c1->Write("Lc Mass");

ex1->cd();
   TLatex Tl;
   Tl.SetTextAlign(12);
   Tl.SetTextSize(0.04);
   Tl.DrawLatex(0.1,0.9,Form("Mean Value: %f MeV", CrystalBallFunction->GetParameter(0)));
   Tl.DrawLatex(0.1,0.85,Form("Error: %f MeV", CrystalBallFunction->GetParError(0)));
   Tl.DrawLatex(0.1,0.7,Form("Sigma: %f MeV", CrystalBallFunction->GetParameter(1)));
   Tl.DrawLatex(0.1,0.65,Form("Error: %f MeV", CrystalBallFunction->GetParError(1)));
//   Tl.DrawLatex(0.1,0.5,Form("Sigma: %f MeV", CrystalBallFunction->GetParameter(2)));
//   Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", CrystalBallFunction->GetParError(2)));
   Tl.DrawLatex(0.1,0.3,Form("Bins Between -1 & 1 %f Bins", count1));
   Tl.DrawLatex(0.1,0.2,Form("Bins Between -2 & 2 %f Bins", count2));
   Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", count3));
   ex1->Write("Crystal Ball Fit Values");
c1->cd();

 TF1 *LcFitSG1 = new TF1("LcFitSG1",CrystalBall,2200.,2400.,7);
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

 TF1 *LcFitSG2 = new TF1("LcFitSG2",CrystalBall,2200.,2400.,7);
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

 TF1 *LcFitSG3 = new TF1("LcFitSG3",CrystalBall,2200.,2400.,7);
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

 TF1 *LcFitSG4 = new TF1("LcFitSG4",CrystalBall,2200.,2400.,7);
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
 
  TF1 *MagDownFitSG = new TF1("MagDownFitSG",CrystalBall,2200.,2400.,7);
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
 
 TF1 *MagUpFitSG = new TF1("MagUpFitSG",CrystalBall,2200.,2400.,7);
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
 
 TF1 *ParticleFitSG = new TF1("ParticleFitSG",CrystalBall,2200.,2400.,7);
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
 
 TF1 *AntiParticleFitSG = new TF1("AntiParticleFitSG",CrystalBall,2200.,2400.,7);
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
