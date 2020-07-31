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


TH1D * SignalHistTight = nullptr;
TH1D * MassHistHalfMeVTight = nullptr;
TH1D * MassHist1MeVTight = nullptr;

TH1D * LcLowPTight = nullptr;
TH1D * LcMidLowPTight = nullptr;
TH1D * LcMidHighPTight = nullptr;
TH1D * LcHighPTight = nullptr;
TH1D * LcPDistributionTight = nullptr;

TH1D * PolarityMagUpTight = nullptr;
TH1D * PolarityMagDownTight = nullptr;

TH1D * ParticleTight = nullptr;
TH1D * AntiParticleTight = nullptr;

TGraphErrors * gLcPTight = nullptr;
TGraphErrors * gXiPTight = nullptr;
TGraphErrors * gPolarityTight = nullptr;
TGraphErrors * gPIDTight = nullptr;

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
   
   SignalHistTight = new TH1D("Mass [MeV]", "Lc Mass - Signal", 300, 2212, 2362);
   SignalHistTight->GetXaxis()->SetTitle("MeV");
   SignalHistTight->GetYaxis()->SetTitle("Events Per 1/2 MeV");   
   
   MassHistHalfMeVTight= new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 300, 2212, 2362);
   MassHistHalfMeVTight->GetXaxis()->SetTitle("MeV");
   MassHistHalfMeVTight->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   MassHist1MeVTight = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 150, 2212, 2362);
   MassHist1MeVTight->GetXaxis()->SetTitle("MeV");
   MassHist1MeVTight->GetYaxis()->SetTitle("Events Per 1 MeV");
   
LcLowPTight = new TH1D("Figures of Merit", "LambdaC Mass - Low LcP", 300, 2212, 2362);
LcLowPTight->GetXaxis()->SetTitle("MeV");
LcLowPTight->GetYaxis()->SetTitle("Events Per 1/2 MeV");

LcMidLowPTight = new TH1D("Figures of Merit", "LambdaC Mass - MidLow LcP", 300, 2212, 2362);
LcMidLowPTight->GetXaxis()->SetTitle("MeV");
LcMidLowPTight->GetYaxis()->SetTitle("Events Per 1/2 MeV");

LcMidHighPTight = new TH1D("Figures of Merit", "LambdaC Mass - MidHigh LcP", 300, 2212, 2362);
LcMidHighPTight->GetXaxis()->SetTitle("MeV");
LcMidHighPTight->GetYaxis()->SetTitle("Events Per 1/2 MeV");

LcHighPTight = new TH1D("Figures of Merit", "LambdaC Mass - High LcP", 300, 2212, 2362);
LcHighPTight->GetXaxis()->SetTitle("MeV");
LcHighPTight->GetYaxis()->SetTitle("Events Per 1/2 MeV");

LcPDistributionTight = new TH1D("Figures of Merit", "LcP Distribution After Cuts", 300, 0, 250000);
LcPDistributionTight->GetXaxis()->SetTitle("MeV");
LcPDistributionTight->GetYaxis()->SetTitle("Events Per 2500 MeV");
   
PolarityMagDownTight = new TH1D("Figures of Merit", "LambdaC Mass - MagnetDown", 300, 2212, 2362);
PolarityMagDownTight->GetXaxis()->SetTitle("MeV");
PolarityMagDownTight->GetYaxis()->SetTitle("Events Per 1/2 MeV");

PolarityMagUpTight = new TH1D("Figures of Merit", "LambdaC Mass - MagnetUp", 300, 2212, 2362);
PolarityMagUpTight->GetXaxis()->SetTitle("MeV");
PolarityMagUpTight->GetYaxis()->SetTitle("Events Per 1/2 MeV");

ParticleTight = new TH1D("Figures of Merit", "LambdaC Mass - LambdaC Baryon", 300, 2212, 2362);
ParticleTight->GetXaxis()->SetTitle("MeV");
ParticleTight->GetYaxis()->SetTitle("Events Per 1/2 MeV");

AntiParticleTight = new TH1D("Figures of Merit", "LambdaC Mass - LambdaC AntiBaryon", 300, 2212, 2362);
AntiParticleTight->GetXaxis()->SetTitle("MeV");
AntiParticleTight->GetYaxis()->SetTitle("Events Per 1/2 MeV");
   
   
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
  ((*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp) > 0.65)
&& ((*Kminus_ProbNNk)*(*Kplus_ProbNNk) > 0.70)
&& (*Proton_ProbNNp > 0.70) 
&& (M2_KpKm > 1.02)
&& (M2_KpKm < 1.06)   
);
   
bool TightCuts= (
  ((*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp) > 0.88)
&& ((*Kminus_ProbNNk)*(*Kplus_ProbNNk) > 0.9)
&& (*Proton_ProbNNp > 0.9) 
&& (M2_KpKm > 1.02)
&& (M2_KpKm < 1.06)   
);   

bool Kinematics = (  
     ((TMath::Log10(*Proton_IPCHI2_OWNPV) < 2.5))
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
   
   if (TightCuts){
     MassHistHalfMeVTight->Fill(*Lcplus_M);
     MassHist1MeVTight->Fill(*Lcplus_M); 
     LcPDistributionTight->Fill(*Lcplus_P);
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

/////////////////
   
 if (TightCuts && LcLowPCut){
   LcLowPTight->Fill(*Lcplus_M);}
  
    if (TightCuts && LcMidLowPCut){
   LcMidLowPTight->Fill(*Lcplus_M);}
 
       if (TightCuts && LcMidHighPCut){
   LcMidHighPTight->Fill(*Lcplus_M);}
   
          if (TightCuts && LcHighPCut){
   LcHighPTight->Fill(*Lcplus_M);}
   
   ///////////////
   
  if (TightCuts && MagDown){
   PolarityMagDownTight->Fill(*Lcplus_M);}
  
    if (TightCuts && MagUp){
   PolarityMagUpTight->Fill(*Lcplus_M);}
 
  /////////////// 
   
       if (TightCuts && Particles){
   ParticleTight->Fill(*Lcplus_M);}
   
          if (TightCuts && AntiParticles){
   AntiParticleTight->Fill(*Lcplus_M);}     
   
   return kTRUE;
}

void CrystalBallTest::SlaveTerminate()
{
}

void CrystalBallTest::Terminate()
{
 
 c1->cd();
TSpectrum *sLoose = new TSpectrum(); 
TH1 * BackgroundHistLoose = sLoose->Background(MassHistHalfMeVLoose, 100,"");  
MassHistHalfMeVLoose->Draw();
 BackgroundHistLoose->Draw("SAME"); 
 c1->Write("Background Estimate - Loose");
 c1->Clear();
   
SignalHistLoose->Add(MassHistHalfMeVLoose,BackgroundHistLoose,1.0,-1.0);
SignalHistLoose->SetMinimum(0); 
SignalHistLoose->SetMaximum(11000);   
SignalHistLoose->Draw();  
 MassHistHalfMeVLoose->Draw("SAME"); 
 c1->Write("Signal Estimate - Loose");
  c1->Clear();
   
TSpectrum *sTight = new TSpectrum(); 
TH1 * BackgroundHistTight = sTight->Background(MassHistHalfMeVTight, 100,"");  
MassHistHalfMeVTight->Draw();
 BackgroundHistTight->Draw("SAME"); 
 c1->Write("Background Estimate - Tight");
 c1->Clear();
   
SignalHistTight->Add(MassHistHalfMeVTight,BackgroundHistTight,1.0,-1.0);
SignalHistTight->SetMinimum(0); 
SignalHistTight->SetMaximum(7500);   
SignalHistTight->Draw();  
 MassHistHalfMeVTight->Draw("SAME"); 
 c1->Write("Signal Estimate - Tight");
  c1->Clear();   
   
TPad *pad1 = new TPad("pad1","pad1",0,0.33,1,1);
TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.33);
pad1->SetBottomMargin(0);
pad1->SetLeftMargin(0.15);
pad2->SetTopMargin(0);
pad2->SetBottomMargin(0.4);
pad2->SetLeftMargin(0.15);
pad2->SetGridx();   
pad1->Draw();
pad2->Draw();

/////////////////////////////////////   
   
TF1 *GaussianHalfMeVDGLoose = new TF1("GaussianHalfMeVDGLoose",DGOneMuOneTotalHalfMeV,2200.,2400.,7);  
GaussianHalfMeVDGLoose->SetParameter(0, 0.4);
GaussianHalfMeVDGLoose->SetParameter(1, 12000);
GaussianHalfMeVDGLoose->SetParameter(2, 2287.);
GaussianHalfMeVDGLoose->SetParameter(3, 3);
GaussianHalfMeVDGLoose->SetParameter(4, 6);
GaussianHalfMeVDGLoose->SetParLimits(3, 0., 20.);
GaussianHalfMeVDGLoose->SetParLimits(4, 0., 20.);
GaussianHalfMeVDGLoose->SetParameter(5, 0.);
GaussianHalfMeVDGLoose->SetParameter(6, 0.);

pad1->cd();
MassHistHalfMeVLoose->SetMinimum(0.0001);
MassHistHalfMeVLoose->Fit("GaussianHalfMeVDGLoose");

TString SignalDGH;
TString SignalErDGH;
SignalDGH.Form("%5.2f\n", GaussianHalfMeVDGLoose->GetParameter(1));
SignalErDGH.Form("%5.2f\n", GaussianHalfMeVDGLoose->GetParError(1));  
TString FractionDGH;
TString FractionErDGH;
FractionDGH.Form("%5.2f\n", GaussianHalfMeVDGLoose->GetParameter(0));
FractionErDGH.Form("%5.2f\n", GaussianHalfMeVDGLoose->GetParError(0));    
TString muDGH;
TString muErDGH;
muDGH.Form("%5.2f\n", GaussianHalfMeVDGLoose->GetParameter(2));
muErDGH.Form("%5.2f\n", GaussianHalfMeVDGLoose->GetParError(2));    
TString sigma1DGH;
TString sigma1ErDGH;
sigma1DGH.Form("%5.2f\n", GaussianHalfMeVDGLoose->GetParameter(3));
sigma1ErDGH.Form("%5.2f\n", GaussianHalfMeVDGLoose->GetParError(3));     
TString sigma2DGH;
TString sigma2ErDGH;
sigma2DGH.Form("%5.2f\n", GaussianHalfMeVDGLoose->GetParameter(4));
sigma2ErDGH.Form("%5.2f\n", GaussianHalfMeVDGLoose->GetParError(4));  
   
auto lt = new TLatex();
lt->SetTextSize(0.03);
lt->DrawLatexNDC(0.6, 0.70, "Signal Events = "+SignalDGH+" #pm "+SignalErDGH+" Events");
lt->DrawLatexNDC(0.6, 0.65, "Fraction in First Gaussian = "+FractionDGH+" #pm "+FractionErDGH+);   
lt->DrawLatexNDC(0.6, 0.6, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");   
lt->DrawLatexNDC(0.6, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");  
lt->DrawLatexNDC(0.6, 0.5, "#sigma_{2} = "+sigma2DGH+" #pm "+sigma2ErDGH+" MeV");   

pad2->cd();
TH1D* PullPlotHalfMeVDGLoose = new TH1D("Mass [MeV]", "Lc Mass", 300, 2212, 2362);   
PullPlotHalfMeVDGLoose->SetStats(0);  
PullPlotHalfMeVDGLoose->GetXaxis()->SetTitle("Mass[MeV]");
PullPlotHalfMeVDGLoose->GetXaxis()->SetTitleSize(15);  
PullPlotHalfMeVDGLoose->GetXaxis()->SetTitleFont(43);   
PullPlotHalfMeVDGLoose->GetXaxis()->SetTitleOffset(2);
PullPlotHalfMeVDGLoose->GetXaxis()->SetLabelSize(0.1);   
PullPlotHalfMeVDGLoose->GetYaxis()->SetTitle("Pull"); 
PullPlotHalfMeVDGLoose->GetYaxis()->CenterTitle(true);
PullPlotHalfMeVDGLoose->GetYaxis()->SetTitleSize(15);
PullPlotHalfMeVDGLoose->GetYaxis()->SetTitleFont(43);    
PullPlotHalfMeVDGLoose->GetYaxis()->SetLabelSize(0.05);   
PullPlotHalfMeVDGLoose->GetXaxis()->SetTitleOffset(3);   
PullPlotHalfMeVDGLoose->SetFillColor(kBlue);
PullPlotHalfMeVDGLoose->SetLineColor(kBlue);
PullPlotHalfMeVDGLoose->SetBit(TH1::kNoTitle);  

 for (Int_t i=1;i<300;i++) {
 Double_t x = MassHistHalfMeVLoose->GetBinCenter(i);
 Double_t val = GaussianHalfMeVDGLoose->Eval(x);
 Double_t sigma = sqrt(val);
 Double_t pull = (MassHistHalfMeVLoose->GetBinContent(i)-val)/sigma;
PullPlotHalfMeVDGLoose->SetBinContent(i,pull);
   }  
PullPlotHalfMeVDGLoose->Draw();  
      
MassHistHalfMeVLoose->SetTitle("#Lambda_{c}^{+} Mass - Double Gaussian Fit");
  c1->Write("Lc Mass Loose - HalfMeVDG");
  pad1->Clear();
 
/////////////////////////   
   
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
MassHistHalfMeVLoose->SetMinimum(0.0001);
MassHistHalfMeVLoose->Fit("CrystalBallFunctionHalfMeVLoose");

TString SignalCBH;
TString SignalErCBH;
SignalCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVLoose->GetParameter(0));
SignalErCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVLoose->GetParError(0));  
TString FractionCBH;
TString FractionErCBH;
FractionCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVLoose->GetParameter(4));
FractionErCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVLoose->GetParError(4));    
TString muCBH;
TString muErCBH;
muCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVLoose->GetParameter(1));
muErCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVLoose->GetParError(1));    
TString sigmaGauCBH;
TString sigmaGauErCBH;
sigmaGauCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVLoose->GetParameter(3));
sigmaGauErCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVLoose->GetParError(3));     
TString sigma2CBH;
TString sigma2ErCBH;
Double_t sigma2 = TMath::Sqrt((CrystalBallFunctionHalfMeVLoose->GetParameter(4)*CrystalBallFunctionHalfMeVLoose->GetParameter(4) - CrystalBallFunctionHalfMeVLoose->GetParameter(4)*CrystalBallFunctionHalfMeVLoose->GetParameter(3)*CrystalBallFunctionHalfMeVLoose->GetParameter(3)) / (1 - CrystalBallFunctionHalfMeVLoose->GetParameter(4)));
Double_t sigma2Err = TMath::Sqrt((CrystalBallFunctionHalfMeVLoose->GetParError(4)*CrystalBallFunctionHalfMeVLoose->GetParError(4) - CrystalBallFunctionHalfMeVLoose->GetParError(4)*CrystalBallFunctionHalfMeVLoose->GetParError(3)*CrystalBallFunctionHalfMeVLoose->GetParError(3)) / (1 - CrystalBallFunctionHalfMeVLoose->GetParError(4)));
sigma2CBH.Form("%5.2f\n", sigma2);
sigma2ErCBH.Form("%5.2f\n", sigma2Err);  
TString alphaCBH;
TString alphaErCBH;
alphaCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVLoose->GetParameter(7));
alphaErCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVLoose->GetParError(7));    
TString nCBH;
TString nErCBH;
nCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVLoose->GetParameter(8));
nErCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVLoose->GetParError(8)); 
    
lt->DrawLatexNDC(0.6, 0.70, "Signal Events = "+SignalCBH+" #pm "+SignalErCBH+" Events");
lt->DrawLatexNDC(0.6, 0.65, "Fraction in Gaussian = "+FractionCBH+" #pm "+FractionErCBH+);   
lt->DrawLatexNDC(0.6, 0.6, "#mu = "+muCBH+" #pm "+muErCBH+" MeV");   
lt->DrawLatexNDC(0.6, 0.55, "#sigma_{Gaussian} = "+sigmaGauCBH+" #pm "+sigmaGauErCBH+" MeV");  
lt->DrawLatexNDC(0.6, 0.5, "#sigma_{CrystalBall} = "+sigma2CBH+" #pm "+sigma2ErCBH+" MeV");   

pad2->cd();
TH1D* PullPlotHalfMeVCBLoose = new TH1D("Mass [MeV]", "Lc Mass", 300, 2212, 2362);   
PullPlotHalfMeVCBLoose->SetStats(0);  
PullPlotHalfMeVCBLoose->GetXaxis()->SetTitle("Mass[MeV]");
PullPlotHalfMeVCBLoose->GetXaxis()->SetTitleSize(15);  
PullPlotHalfMeVCBLoose->GetXaxis()->SetTitleFont(43);   
PullPlotHalfMeVCBLoose->GetXaxis()->SetTitleOffset(2);
PullPlotHalfMeVCBLoose->GetXaxis()->SetLabelSize(0.1);   
PullPlotHalfMeVCBLoose->GetYaxis()->SetTitle("Pull"); 
PullPlotHalfMeVCBLoose->GetYaxis()->CenterTitle(true);
PullPlotHalfMeVCBLoose->GetYaxis()->SetTitleSize(15);
PullPlotHalfMeVCBLoose->GetYaxis()->SetTitleFont(43);    
PullPlotHalfMeVCBLoose->GetYaxis()->SetLabelSize(0.05);   
PullPlotHalfMeVCBLoose->GetXaxis()->SetTitleOffset(3);   
PullPlotHalfMeVCBLoose->SetFillColor(kBlue);
PullPlotHalfMeVCBLoose->SetLineColor(kBlue);
PullPlotHalfMeVCBLoose->SetBit(TH1::kNoTitle);  

 for (Int_t i=1;i<300;i++) {
 Double_t x = MassHistHalfMeVLoose->GetBinCenter(i);
 Double_t val = CrystalBallFunctionHalfMeVLoose->Eval(x);
 Double_t sigma = sqrt(val);
 Double_t pull = (MassHistHalfMeVLoose->GetBinContent(i)-val)/sigma;
PullPlotHalfMeVCBLoose->SetBinContent(i,pull);
   }  
PullPlotHalfMeVCBLoose->Draw();  
      
MassHistHalfMeVLoose->SetTitle("#Lambda_{c}^{+} Mass - Gaussian + CrystalBall Fit");
  c1->Write("Lc Mass Loose - HalfMeVCB"); 
  pad1->Clear();
 
//////////////////////////////////   
   
TF1 *Gaussian1MeVDGLoose = new TF1("Gaussian1MeVDGLoose",DGOneMuOneTotal1MeV,2212.,2362.,7);
Gaussian1MeVDGLoose->SetParameter(0, 0.4);
Gaussian1MeVDGLoose->SetParameter(1, 12000);
Gaussian1MeVDGLoose->SetParameter(2, 2287.);
Gaussian1MeVDGLoose->SetParameter(3, 3);
Gaussian1MeVDGLoose->SetParameter(4, 6);
Gaussian1MeVDGLoose->SetParLimits(3, 0., 20.);
Gaussian1MeVDGLoose->SetParLimits(4, 0., 20.);
Gaussian1MeVDGLoose->SetParameter(5, 0.);
Gaussian1MeVDGLoose->SetParameter(6, 0.);

pad1->cd();
MassHist1MeVLoose->SetMinimum(0.0001);
MassHist1MeVLoose->Fit("Gaussian1MeVDGLoose");

SignalDGH.Form("%5.2f\n", Gaussian1MeVDGLoose->GetParameter(1));
SignalErDGH.Form("%5.2f\n", Gaussian1MeVDGLoose->GetParError(1));  

FractionDGH.Form("%5.2f\n", Gaussian1MeVDGLoose->GetParameter(0));
FractionErDGH.Form("%5.2f\n", Gaussian1MeVDGLoose->GetParError(0));    

muDGH.Form("%5.2f\n", Gaussian1MeVDGLoose->GetParameter(2));
muErDGH.Form("%5.2f\n", Gaussian1MeVDGLoose->GetParError(2));    

sigma1DGH.Form("%5.2f\n", Gaussian1MeVDGLoose->GetParameter(3));
sigma1ErDGH.Form("%5.2f\n", Gaussian1MeVDGLoose->GetParError(3));     

sigma2DGH.Form("%5.2f\n", Gaussian1MeVDGLoose->GetParameter(4));
sigma2ErDGH.Form("%5.2f\n", Gaussian1MeVDGLoose->GetParError(4));  
   
lt->DrawLatexNDC(0.6, 0.70, "Signal Events = "+SignalDGH+" #pm "+SignalErDGH+" Events");
lt->DrawLatexNDC(0.6, 0.65, "Fraction in First Gaussian = "+FractionDGH+" #pm "+FractionErDGH+);   
lt->DrawLatexNDC(0.6, 0.6, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");   
lt->DrawLatexNDC(0.6, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");  
lt->DrawLatexNDC(0.6, 0.5, "#sigma_{2} = "+sigma2DGH+" #pm "+sigma2ErDGH+" MeV");   

pad2->cd();
TH1D* PullPlot1MeVDGLoose = new TH1D("Mass [MeV]", "Lc Mass", 150, 2212, 2362);   
PullPlot1MeVDGLoose->SetStats(0);  
PullPlot1MeVDGLoose->GetXaxis()->SetTitle("Mass[MeV]");
PullPlot1MeVDGLoose->GetXaxis()->SetTitleSize(15);  
PullPlot1MeVDGLoose->GetXaxis()->SetTitleFont(43);   
PullPlot1MeVDGLoose->GetXaxis()->SetTitleOffset(2);
PullPlot1MeVDGLoose->GetXaxis()->SetLabelSize(0.1);   
PullPlot1MeVDGLoose->GetYaxis()->SetTitle("Pull"); 
PullPlot1MeVDGLoose->GetYaxis()->CenterTitle(true);
PullPlot1MeVDGLoose->GetYaxis()->SetTitleSize(15);
PullPlot1MeVDGLoose->GetYaxis()->SetTitleFont(43);    
PullPlot1MeVDGLoose->GetYaxis()->SetLabelSize(0.05);   
PullPlot1MeVDGLoose->GetXaxis()->SetTitleOffset(3);   
PullPlot1MeVDGLoose->SetFillColor(kBlue);
PullPlot1MeVDGLoose->SetLineColor(kBlue);
PullPlot1MeVDGLoose->SetBit(TH1::kNoTitle);  

 for (Int_t i=1;i<150;i++) {
 Double_t x = MassHist1MeVLoose->GetBinCenter(i);
 Double_t val = Gaussian1MeVDGLoose->Eval(x);
 Double_t sigma = sqrt(val);
 Double_t pull = (MassHist1MeVLoose->GetBinContent(i)-val)/sigma;
PullPlot1MeVDGLoose->SetBinContent(i,pull);
   }  
PullPlot1MeVDGLoose->Draw();  
      
MassHist1MeVLoose->SetTitle("#Lambda_{c}^{+} Mass - Double Gaussian Fit");
  c1->Write("Lc Mass Loose - 1MeVDG");
  pad1->Clear();
   
///////////////////////////////////////////   

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
MassHist1MeVLoose->SetMinimum(0.0001);
MassHist1MeVLoose->Fit("CrystalBallFunction1MeVLoose");


SignalCBH.Form("%5.2f\n", CrystalBallFunction1MeVLoose->GetParameter(0));
SignalErCBH.Form("%5.2f\n", CrystalBallFunction1MeVLoose->GetParError(0));  

FractionCBH.Form("%5.2f\n", CrystalBallFunction1MeVLoose->GetParameter(4));
FractionErCBH.Form("%5.2f\n", CrystalBallFunction1MeVLoose->GetParError(4));    

muCBH.Form("%5.2f\n", CrystalBallFunction1MeVLoose->GetParameter(1));
muErCBH.Form("%5.2f\n", CrystalBallFunction1MeVLoose->GetParError(1));    

sigmaGauCBH.Form("%5.2f\n", CrystalBallFunction1MeVLoose->GetParameter(3));
sigmaGauErCBH.Form("%5.2f\n", CrystalBallFunction1MeVLoose->GetParError(3));     

Double_t sigma21MeVLoose = TMath::Sqrt((CrystalBallFunction1MeVLoose->GetParameter(4)*CrystalBallFunction1MeVLoose->GetParameter(4) - CrystalBallFunction1MeVLoose->GetParameter(4)*CrystalBallFunction1MeVLoose->GetParameter(3)*CrystalBallFunction1MeVLoose->GetParameter(3)) / (1 - CrystalBallFunction1MeVLoose->GetParameter(4)));
Double_t sigma2Err1MeVLoose  = TMath::Sqrt((CrystalBallFunction1MeVLoose->GetParError(4)*CrystalBallFunction1MeVLoose->GetParError(4) - CrystalBallFunction1MeVLoose->GetParError(4)*CrystalBallFunction1MeVLoose->GetParError(3)*CrystalBallFunction1MeVLoose->GetParError(3)) / (1 - CrystalBallFunction1MeVLoose->GetParError(4)));
sigma2CBH.Form("%5.2f\n", sigma21MeVLoose );
sigma2ErCBH.Form("%5.2f\n", sigma2Err1MeVLoose );  

alphaCBH.Form("%5.2f\n", CrystalBallFunction1MeVLoose->GetParameter(7));
alphaErCBH.Form("%5.2f\n", CrystalBallFunction1MeVLoose->GetParError(7));    

nCBH.Form("%5.2f\n", CrystalBallFunction1MeVLoose->GetParameter(8));
nErCBH.Form("%5.2f\n", CrystalBallFunction1MeVLoose->GetParError(8)); 
    
lt->DrawLatexNDC(0.6, 0.70, "Signal Events = "+SignalCBH+" #pm "+SignalErCBH+" Events");
lt->DrawLatexNDC(0.6, 0.65, "Fraction in Gaussian = "+FractionCBH+" #pm "+FractionErCBH+);   
lt->DrawLatexNDC(0.6, 0.6, "#mu = "+muCBH+" #pm "+muErCBH+" MeV");   
lt->DrawLatexNDC(0.6, 0.55, "#sigma_{Gaussian} = "+sigmaGauCBH+" #pm "+sigmaGauErCBH+" MeV");  
lt->DrawLatexNDC(0.6, 0.5, "#sigma_{CrystalBall} = "+sigma2CBH+" #pm "+sigma2ErCBH+" MeV");   

pad2->cd();
TH1D* PullPlot1MeVCBLoose = new TH1D("Mass [MeV]", "Lc Mass", 150, 2212, 2362);   
PullPlot1MeVCBLoose->SetStats(0);  
PullPlot1MeVCBLoose->GetXaxis()->SetTitle("Mass[MeV]");
PullPlot1MeVCBLoose->GetXaxis()->SetTitleSize(15);  
PullPlot1MeVCBLoose->GetXaxis()->SetTitleFont(43);   
PullPlot1MeVCBLoose->GetXaxis()->SetTitleOffset(2);
PullPlot1MeVCBLoose->GetXaxis()->SetLabelSize(0.1);   
PullPlot1MeVCBLoose->GetYaxis()->SetTitle("Pull"); 
PullPlot1MeVCBLoose->GetYaxis()->CenterTitle(true);
PullPlot1MeVCBLoose->GetYaxis()->SetTitleSize(15);
PullPlot1MeVCBLoose->GetYaxis()->SetTitleFont(43);    
PullPlot1MeVCBLoose->GetYaxis()->SetLabelSize(0.05);   
PullPlot1MeVCBLoose->GetXaxis()->SetTitleOffset(3);   
PullPlot1MeVCBLoose->SetFillColor(kBlue);
PullPlot1MeVCBLoose->SetLineColor(kBlue);
PullPlot1MeVCBLoose->SetBit(TH1::kNoTitle);  

 for (Int_t i=1;i<150;i++) {
 Double_t x = MassHist1MeVLoose->GetBinCenter(i);
 Double_t val = CrystalBallFunction1MeVLoose->Eval(x);
 Double_t sigma = sqrt(val);
 Double_t pull = (MassHist1MeVLoose->GetBinContent(i)-val)/sigma;
PullPlot1MeVCBLoose->SetBinContent(i,pull);
   }  
PullPlot1MeVCBLoose->Draw();  
      
MassHist1MeVLoose->SetTitle("#Lambda_{c}^{+} Mass - Gaussian + CrystalBall Fit");
  c1->Write("Lc Mass Loose - 1MeVCB"); 
  pad1->Clear();
   
///////////////////////////   
   
TF1 *GaussianHalfMeVDGTight = new TF1("GaussianHalfMeVDGTight",DGOneMuOneTotalHalfMeV,2200.,2400.,7);
GaussianHalfMeVDGTight->SetParameter(0, 0.4);
GaussianHalfMeVDGTight->SetParameter(1, 12000);
GaussianHalfMeVDGTight->SetParameter(2, 2287.);
GaussianHalfMeVDGTight->SetParameter(3, 3);
GaussianHalfMeVDGTight->SetParameter(4, 6);
GaussianHalfMeVDGTight->SetParLimits(3, 0., 20.);
GaussianHalfMeVDGTight->SetParLimits(4, 0., 20.);
GaussianHalfMeVDGTight->SetParameter(5, 0.);
GaussianHalfMeVDGTight->SetParameter(6, 0.);

pad1->cd();
MassHistHalfMeVTight->SetMinimum(0.0001);
MassHistHalfMeVTight->Fit("GaussianHalfMeVDGTight");


SignalDGH.Form("%5.2f\n", GaussianHalfMeVDGTight->GetParameter(1));
SignalErDGH.Form("%5.2f\n", GaussianHalfMeVDGTight->GetParError(1));  

FractionDGH.Form("%5.2f\n", GaussianHalfMeVDGTight->GetParameter(0));
FractionErDGH.Form("%5.2f\n", GaussianHalfMeVDGTight->GetParError(0));    

muDGH.Form("%5.2f\n", GaussianHalfMeVDGTight->GetParameter(2));
muErDGH.Form("%5.2f\n", GaussianHalfMeVDGTight->GetParError(2));    

sigma1DGH.Form("%5.2f\n", GaussianHalfMeVDGTight->GetParameter(3));
sigma1ErDGH.Form("%5.2f\n", GaussianHalfMeVDGTight->GetParError(3));     

sigma2DGH.Form("%5.2f\n", GaussianHalfMeVDGTight->GetParameter(4));
sigma2ErDGH.Form("%5.2f\n", GaussianHalfMeVDGTight->GetParError(4));  
   
lt->DrawLatexNDC(0.6, 0.70, "Signal Events = "+SignalDGH+" #pm "+SignalErDGH+" Events");
lt->DrawLatexNDC(0.6, 0.65, "Fraction in First Gaussian = "+FractionDGH+" #pm "+FractionErDGH+);   
lt->DrawLatexNDC(0.6, 0.6, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");   
lt->DrawLatexNDC(0.6, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");  
lt->DrawLatexNDC(0.6, 0.5, "#sigma_{2} = "+sigma2DGH+" #pm "+sigma2ErDGH+" MeV");   

pad2->cd();
TH1D* PullPlotHalfMeVDGTight = new TH1D("Mass [MeV]", "Lc Mass", 300, 2212, 2362);   
PullPlotHalfMeVDGTight->SetStats(0);  
PullPlotHalfMeVDGTight->GetXaxis()->SetTitle("Mass[MeV]");
PullPlotHalfMeVDGTight->GetXaxis()->SetTitleSize(15);  
PullPlotHalfMeVDGTight->GetXaxis()->SetTitleFont(43);   
PullPlotHalfMeVDGTight->GetXaxis()->SetTitleOffset(2);
PullPlotHalfMeVDGTight->GetXaxis()->SetLabelSize(0.1);   
PullPlotHalfMeVDGTight->GetYaxis()->SetTitle("Pull"); 
PullPlotHalfMeVDGTight->GetYaxis()->CenterTitle(true);
PullPlotHalfMeVDGTight->GetYaxis()->SetTitleSize(15);
PullPlotHalfMeVDGTight->GetYaxis()->SetTitleFont(43);    
PullPlotHalfMeVDGTight->GetYaxis()->SetLabelSize(0.05);   
PullPlotHalfMeVDGTight->GetXaxis()->SetTitleOffset(3);   
PullPlotHalfMeVDGTight->SetFillColor(kBlue);
PullPlotHalfMeVDGTight->SetLineColor(kBlue);
PullPlotHalfMeVDGTight->SetBit(TH1::kNoTitle);  

 for (Int_t i=1;i<300;i++) {
 Double_t x = MassHistHalfMeVTight->GetBinCenter(i);
 Double_t val = GaussianHalfMeVDGTight->Eval(x);
 Double_t sigma = sqrt(val);
 Double_t pull = (MassHistHalfMeVTight->GetBinContent(i)-val)/sigma;
PullPlotHalfMeVDGTight->SetBinContent(i,pull);
   }  
PullPlotHalfMeVDGTight->Draw();  
      
MassHistHalfMeVTight->SetTitle("#Lambda_{c}^{+} Mass - Double Gaussian Fit");
  c1->Write("Lc Mass Tight - HalfMeVDG");
  pad1->Clear();
   
/////////////////////////////////////////////   

TF1 *CrystalBallFunctionHalfMeVTight = new TF1("CrystalBallFunctionHalfMeVTight", NewCrystalBallHalfMeV,2212.,2362.,9);
CrystalBallFunctionHalfMeVTight->SetParameter(0,115000); 
CrystalBallFunctionHalfMeVTight->SetParameter(1, 2285.);
CrystalBallFunctionHalfMeVTight->SetParameter(2, 5);  
CrystalBallFunctionHalfMeVTight->SetParameter(3, 4);  
CrystalBallFunctionHalfMeVTight->SetParameter(4, 0.7);
CrystalBallFunctionHalfMeVTight->SetParLimits(4, 0.001, 0.999);   
CrystalBallFunctionHalfMeVTight->SetParameter(5, 750.);   
CrystalBallFunctionHalfMeVTight->SetParameter(6, -0.2);     
CrystalBallFunctionHalfMeVTight->SetParameter(7, 2.0);
CrystalBallFunctionHalfMeVTight->SetParameter(8, 3.0);   
CrystalBallFunctionHalfMeVTight->SetParLimits(8, 1.000001, 8.);   
 
pad1->cd();
MassHistHalfMeVTight->SetMinimum(0.0001);
MassHistHalfMeVTight->Fit("CrystalBallFunctionHalfMeVTight");

SignalCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVTight->GetParameter(0));
SignalErCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVTight->GetParError(0));  

FractionCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVTight->GetParameter(4));
FractionErCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVTight->GetParError(4));    

muCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVTight->GetParameter(1));
muErCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVTight->GetParError(1));    

sigmaGauCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVTight->GetParameter(3));
sigmaGauErCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVTight->GetParError(3));     

Double_t sigma2HalfMeVTight = TMath::Sqrt((CrystalBallFunctionHalfMeVTight->GetParameter(4)*CrystalBallFunctionHalfMeVTight->GetParameter(4) - CrystalBallFunctionHalfMeVTight->GetParameter(4)*CrystalBallFunctionHalfMeVTight->GetParameter(3)*CrystalBallFunctionHalfMeVTight->GetParameter(3)) / (1 - CrystalBallFunctionHalfMeVTight->GetParameter(4)));
Double_t sigma2ErrHalfMeVTight = TMath::Sqrt((CrystalBallFunctionHalfMeVTight->GetParError(4)*CrystalBallFunctionHalfMeVTight->GetParError(4) - CrystalBallFunctionHalfMeVTight->GetParError(4)*CrystalBallFunctionHalfMeVTight->GetParError(3)*CrystalBallFunctionHalfMeVTight->GetParError(3)) / (1 - CrystalBallFunctionHalfMeVTight->GetParError(4)));
sigma2CBH.Form("%5.2f\n", sigma2HalfMeVTight);
sigma2ErCBH.Form("%5.2f\n", sigma2ErrHalfMeVTight);  

alphaCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVTight->GetParameter(7));
alphaErCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVTight->GetParError(7));    

nCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVTight->GetParameter(8));
nErCBH.Form("%5.2f\n", CrystalBallFunctionHalfMeVTight->GetParError(8)); 
    
lt->DrawLatexNDC(0.6, 0.70, "Signal Events = "+SignalCBH+" #pm "+SignalErCBH+" Events");
lt->DrawLatexNDC(0.6, 0.65, "Fraction in Gaussian = "+FractionCBH+" #pm "+FractionErCBH+);   
lt->DrawLatexNDC(0.6, 0.6, "#mu = "+muCBH+" #pm "+muErCBH+" MeV");   
lt->DrawLatexNDC(0.6, 0.55, "#sigma_{Gaussian} = "+sigmaGauCBH+" #pm "+sigmaGauErCBH+" MeV");  
lt->DrawLatexNDC(0.6, 0.5, "#sigma_{CrystalBall} = "+sigma2CBH+" #pm "+sigma2ErCBH+" MeV");   

pad2->cd();
TH1D* PullPlotHalfMeVCBTight = new TH1D("Mass [MeV]", "Lc Mass", 300, 2212, 2362);   
PullPlotHalfMeVCBTight->SetStats(0);  
PullPlotHalfMeVCBTight->GetXaxis()->SetTitle("Mass[MeV]");
PullPlotHalfMeVCBTight->GetXaxis()->SetTitleSize(15);  
PullPlotHalfMeVCBTight->GetXaxis()->SetTitleFont(43);   
PullPlotHalfMeVCBTight->GetXaxis()->SetTitleOffset(2);
PullPlotHalfMeVCBTight->GetXaxis()->SetLabelSize(0.1);   
PullPlotHalfMeVCBTight->GetYaxis()->SetTitle("Pull"); 
PullPlotHalfMeVCBTight->GetYaxis()->CenterTitle(true);
PullPlotHalfMeVCBTight->GetYaxis()->SetTitleSize(15);
PullPlotHalfMeVCBTight->GetYaxis()->SetTitleFont(43);    
PullPlotHalfMeVCBTight->GetYaxis()->SetLabelSize(0.05);   
PullPlotHalfMeVCBTight->GetXaxis()->SetTitleOffset(3);   
PullPlotHalfMeVCBTight->SetFillColor(kBlue);
PullPlotHalfMeVCBTight->SetLineColor(kBlue);
PullPlotHalfMeVCBTight->SetBit(TH1::kNoTitle);  

 for (Int_t i=1;i<300;i++) {
 Double_t x = MassHistHalfMeVTight->GetBinCenter(i);
 Double_t val = CrystalBallFunctionHalfMeVTight->Eval(x);
 Double_t sigma = sqrt(val);
 Double_t pull = (MassHistHalfMeVTight->GetBinContent(i)-val)/sigma;
PullPlotHalfMeVCBTight->SetBinContent(i,pull);
   }  
PullPlotHalfMeVCBTight->Draw();  
      
MassHistHalfMeVTight->SetTitle("#Lambda_{c}^{+} Mass - Gaussian + CrystalBall Fit");
  c1->Write("Lc Mass Tight - HalfMeVCB"); 
  pad1->Clear();
 
//////////////////////////////////////////////////////   
   
TF1 *Gaussian1MeVDGTight = new TF1("Gaussian1MeVDGTight",DGOneMuOneTotal1MeV,2212.,2362.,7);
Gaussian1MeVDGTight->SetParameter(0, 0.4);
Gaussian1MeVDGTight->SetParameter(1, 12000);
Gaussian1MeVDGTight->SetParameter(2, 2287.);
Gaussian1MeVDGTight->SetParameter(3, 3);
Gaussian1MeVDGTight->SetParameter(4, 6);
Gaussian1MeVDGTight->SetParLimits(3, 0., 20.);
Gaussian1MeVDGTight->SetParLimits(4, 0., 20.);
Gaussian1MeVDGTight->SetParameter(5, 0.);
Gaussian1MeVDGTight->SetParameter(6, 0.);

pad1->cd();
MassHist1MeVTight->SetMinimum(0.0001);
MassHist1MeVTight->Fit("Gaussian1MeVDGTight");

SignalDGH.Form("%5.2f\n", Gaussian1MeVDGTight->GetParameter(1));
SignalErDGH.Form("%5.2f\n", Gaussian1MeVDGTight->GetParError(1));  

FractionDGH.Form("%5.2f\n", Gaussian1MeVDGTight->GetParameter(0));
FractionErDGH.Form("%5.2f\n", Gaussian1MeVDGTight->GetParError(0));    

muDGH.Form("%5.2f\n", Gaussian1MeVDGTight->GetParameter(2));
muErDGH.Form("%5.2f\n", Gaussian1MeVDGTight->GetParError(2));    

sigma1DGH.Form("%5.2f\n", Gaussian1MeVDGTight->GetParameter(3));
sigma1ErDGH.Form("%5.2f\n", Gaussian1MeVDGTight->GetParError(3));     

sigma2DGH.Form("%5.2f\n", Gaussian1MeVDGTight->GetParameter(4));
sigma2ErDGH.Form("%5.2f\n", Gaussian1MeVDGTight->GetParError(4));  
   
lt->DrawLatexNDC(0.6, 0.70, "Signal Events = "+SignalDGH+" #pm "+SignalErDGH+" Events");
lt->DrawLatexNDC(0.6, 0.65, "Fraction in First Gaussian = "+FractionDGH+" #pm "+FractionErDGH+);   
lt->DrawLatexNDC(0.6, 0.6, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");   
lt->DrawLatexNDC(0.6, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");  
lt->DrawLatexNDC(0.6, 0.5, "#sigma_{2} = "+sigma2DGH+" #pm "+sigma2ErDGH+" MeV");   

pad2->cd();
TH1D* PullPlot1MeVDGTight = new TH1D("Mass [MeV]", "Lc Mass", 150, 2212, 2362);   
PullPlot1MeVDGTight->SetStats(0);  
PullPlot1MeVDGTight->GetXaxis()->SetTitle("Mass[MeV]");
PullPlot1MeVDGTight->GetXaxis()->SetTitleSize(15);  
PullPlot1MeVDGTight->GetXaxis()->SetTitleFont(43);   
PullPlot1MeVDGTight->GetXaxis()->SetTitleOffset(2);
PullPlot1MeVDGTight->GetXaxis()->SetLabelSize(0.1);   
PullPlot1MeVDGTight->GetYaxis()->SetTitle("Pull"); 
PullPlot1MeVDGTight->GetYaxis()->CenterTitle(true);
PullPlot1MeVDGTight->GetYaxis()->SetTitleSize(15);
PullPlot1MeVDGTight->GetYaxis()->SetTitleFont(43);    
PullPlot1MeVDGTight->GetYaxis()->SetLabelSize(0.05);   
PullPlot1MeVDGTight->GetXaxis()->SetTitleOffset(3);   
PullPlot1MeVDGTight->SetFillColor(kBlue);
PullPlot1MeVDGTight->SetLineColor(kBlue);
PullPlot1MeVDGTight->SetBit(TH1::kNoTitle);  

 for (Int_t i=1;i<150;i++) {
 Double_t x = MassHist1MeVTight->GetBinCenter(i);
 Double_t val = Gaussian1MeVDGTight->Eval(x);
 Double_t sigma = sqrt(val);
 Double_t pull = (MassHist1MeVTight->GetBinContent(i)-val)/sigma;
PullPlot1MeVDGTight->SetBinContent(i,pull);
   }  
PullPlot1MeVDGTight->Draw();  
      
MassHist1MeVTight->SetTitle("#Lambda_{c}^{+} Mass - Double Gaussian Fit");
  c1->Write("Lc Mass Tight - 1MeVDG");
  pad1->Clear();

////////////////////////////////////////////////   
   
TF1 *CrystalBallFunction1MeVTight = new TF1("CrystalBallFunction1MeVTight", NewCrystalBall1MeV,2212.,2362.,9);
CrystalBallFunction1MeVTight->SetParameter(0,115000); 
CrystalBallFunction1MeVTight->SetParameter(1, 2285.);
CrystalBallFunction1MeVTight->SetParameter(2, 5);  
CrystalBallFunction1MeVTight->SetParameter(3, 4);  
CrystalBallFunction1MeVTight->SetParameter(4, 0.7);
CrystalBallFunction1MeVTight->SetParLimits(4, 0.001, 0.999);   
CrystalBallFunction1MeVTight->SetParameter(5, 750.);   
CrystalBallFunction1MeVTight->SetParameter(6, -0.2);     
CrystalBallFunction1MeVTight->SetParameter(7, 2.0);
CrystalBallFunction1MeVTight->SetParameter(8, 3.0);   
CrystalBallFunction1MeVTight->SetParLimits(8, 1.000001, 8.);    
 
pad1->cd();
MassHist1MeVTight->SetMinimum(0.0001);
MassHist1MeVTight->Fit("CrystalBallFunction1MeVTight");


SignalCBH.Form("%5.2f\n", CrystalBallFunction1MeVTight->GetParameter(0));
SignalErCBH.Form("%5.2f\n", CrystalBallFunction1MeVTight->GetParError(0));  

FractionCBH.Form("%5.2f\n", CrystalBallFunction1MeVTight->GetParameter(4));
FractionErCBH.Form("%5.2f\n", CrystalBallFunction1MeVTight->GetParError(4));    

muCBH.Form("%5.2f\n", CrystalBallFunction1MeVTight->GetParameter(1));
muErCBH.Form("%5.2f\n", CrystalBallFunction1MeVTight->GetParError(1));    

sigmaGauCBH.Form("%5.2f\n", CrystalBallFunction1MeVTight->GetParameter(3));
sigmaGauErCBH.Form("%5.2f\n", CrystalBallFunction1MeVTight->GetParError(3));     

Double_t sigma21MeVTight = TMath::Sqrt((CrystalBallFunction1MeVTight->GetParameter(4)*CrystalBallFunction1MeVTight->GetParameter(4) - CrystalBallFunction1MeVTight->GetParameter(4)*CrystalBallFunction1MeVTight->GetParameter(3)*CrystalBallFunction1MeVTight->GetParameter(3)) / (1 - CrystalBallFunction1MeVTight->GetParameter(4)));
Double_t sigma2Err1MeVTight = TMath::Sqrt((CrystalBallFunction1MeVTight->GetParError(4)*CrystalBallFunction1MeVTight->GetParError(4) - CrystalBallFunction1MeVTight->GetParError(4)*CrystalBallFunction1MeVTight->GetParError(3)*CrystalBallFunction1MeVTight->GetParError(3)) / (1 - CrystalBallFunction1MeVTight->GetParError(4)));
sigma2CBH.Form("%5.2f\n", sigma21MeVTight);
sigma2ErCBH.Form("%5.2f\n", sigma2Err1MeVTight);  

alphaCBH.Form("%5.2f\n", CrystalBallFunction1MeVTight->GetParameter(7));
alphaErCBH.Form("%5.2f\n", CrystalBallFunction1MeVTight->GetParError(7));    

nCBH.Form("%5.2f\n", CrystalBallFunction1MeVTight->GetParameter(8));
nErCBH.Form("%5.2f\n", CrystalBallFunction1MeVTight->GetParError(8)); 
    
lt->DrawLatexNDC(0.6, 0.70, "Signal Events = "+SignalCBH+" #pm "+SignalErCBH+" Events");
lt->DrawLatexNDC(0.6, 0.65, "Fraction in Gaussian = "+FractionCBH+" #pm "+FractionErCBH+);   
lt->DrawLatexNDC(0.6, 0.6, "#mu = "+muCBH+" #pm "+muErCBH+" MeV");   
lt->DrawLatexNDC(0.6, 0.55, "#sigma_{Gaussian} = "+sigmaGauCBH+" #pm "+sigmaGauErCBH+" MeV");  
lt->DrawLatexNDC(0.6, 0.5, "#sigma_{CrystalBall} = "+sigma2CBH+" #pm "+sigma2ErCBH+" MeV");   

pad2->cd();
TH1D* PullPlot1MeVCBTight = new TH1D("Mass [MeV]", "Lc Mass", 150, 2212, 2362);   
PullPlot1MeVCBTight->SetStats(0);  
PullPlot1MeVCBTight->GetXaxis()->SetTitle("Mass[MeV]");
PullPlot1MeVCBTight->GetXaxis()->SetTitleSize(15);  
PullPlot1MeVCBTight->GetXaxis()->SetTitleFont(43);   
PullPlot1MeVCBTight->GetXaxis()->SetTitleOffset(2);
PullPlot1MeVCBTight->GetXaxis()->SetLabelSize(0.1);   
PullPlot1MeVCBTight->GetYaxis()->SetTitle("Pull"); 
PullPlot1MeVCBTight->GetYaxis()->CenterTitle(true);
PullPlot1MeVCBTight->GetYaxis()->SetTitleSize(15);
PullPlot1MeVCBTight->GetYaxis()->SetTitleFont(43);    
PullPlot1MeVCBTight->GetYaxis()->SetLabelSize(0.05);   
PullPlot1MeVCBTight->GetXaxis()->SetTitleOffset(3);   
PullPlot1MeVCBTight->SetFillColor(kBlue);
PullPlot1MeVCBTight->SetLineColor(kBlue);
PullPlot1MeVCBTight->SetBit(TH1::kNoTitle);  

 for (Int_t i=1;i<150;i++) {
 Double_t x = MassHist1MeVTight->GetBinCenter(i);
 Double_t val = CrystalBallFunction1MeVTight->Eval(x);
 Double_t sigma = sqrt(val);
 Double_t pull = (MassHist1MeVTight->GetBinContent(i)-val)/sigma;
PullPlot1MeVCBTight->SetBinContent(i,pull);
   }  
PullPlot1MeVCBTight->Draw();  
      
MassHist1MeVTight->SetTitle("#Lambda_{c}^{+} Mass - Gaussian + CrystalBall Fit");
  c1->Write("Lc Mass Tight - 1MeVCB"); 
  pad1->Clear();

////////////////////////////////   
   
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


TF1 *LcFitSGTight1 = new TF1("LcFitSGTight1", NewCrystalBallHalfMeV,2212.,2362.,9);
LcFitSGTight1->SetParameter(0,115000); 
LcFitSGTight1->SetParameter(1, 2285.);
LcFitSGTight1->SetParameter(2, 5);  
LcFitSGTight1->SetParameter(3, 4);  
LcFitSGTight1->SetParameter(4, 0.7);
LcFitSGTight1->SetParLimits(4, 0.001, 0.999);   
LcFitSGTight1->SetParameter(5, 750.);   
LcFitSGTight1->SetParameter(6, -0.2);     
LcFitSGTight1->SetParameter(7, 2.0);
LcFitSGTight1->SetParameter(8, 3.0);   
LcFitSGTight1->SetParLimits(8, 1.000001, 8.);  
   
TF1 *LcFitSGTight2 = new TF1("LcFitSGTight2", NewCrystalBallHalfMeV,2212.,2362.,9);
LcFitSGTight2->SetParameter(0,115000); 
LcFitSGTight2->SetParameter(1, 2285.);
LcFitSGTight2->SetParameter(2, 5);  
LcFitSGTight2->SetParameter(3, 4);  
LcFitSGTight2->SetParameter(4, 0.7);
LcFitSGTight2->SetParLimits(4, 0.001, 0.999);   
LcFitSGTight2->SetParameter(5, 750.);   
LcFitSGTight2->SetParameter(6, -0.2);     
LcFitSGTight2->SetParameter(7, 2.0);
LcFitSGTight2->SetParameter(8, 3.0);   
LcFitSGTight2->SetParLimits(8, 1.000001, 8.);  

TF1 *LcFitSGTight3 = new TF1("LcFitSGTight3", NewCrystalBallHalfMeV,2212.,2362.,9);
LcFitSGTight3->SetParameter(0,115000); 
LcFitSGTight3->SetParameter(1, 2285.);
LcFitSGTight3->SetParameter(2, 5);  
LcFitSGTight3->SetParameter(3, 4);  
LcFitSGTight3->SetParameter(4, 0.7);
LcFitSGTight3->SetParLimits(4, 0.001, 0.999);   
LcFitSGTight3->SetParameter(5, 750.);   
LcFitSGTight3->SetParameter(6, -0.2);     
LcFitSGTight3->SetParameter(7, 2.0);
LcFitSGTight3->SetParameter(8, 3.0);   
LcFitSGTight3->SetParLimits(8, 1.000001, 8.);  

TF1 *LcFitSGTight4 = new TF1("LcFitSGTight4", NewCrystalBallHalfMeV,2212.,2362.,9);
LcFitSGTight4->SetParameter(0,115000); 
LcFitSGTight4->SetParameter(1, 2285.);
LcFitSGTight4->SetParameter(2, 5);  
LcFitSGTight4->SetParameter(3, 4);  
LcFitSGTight4->SetParameter(4, 0.7);
LcFitSGTight4->SetParLimits(4, 0.001, 0.999);   
LcFitSGTight4->SetParameter(5, 750.);   
LcFitSGTight4->SetParameter(6, -0.2);     
LcFitSGTight4->SetParameter(7, 2.0);
LcFitSGTight4->SetParameter(8, 3.0);   
LcFitSGTight4->SetParLimits(8, 1.000001, 8.);  
 
TF1 *MagDownFitSGTight = new TF1("MagDownFitSGTight", NewCrystalBallHalfMeV,2212.,2362.,9);
MagDownFitSGTight->SetParameter(0,115000); 
MagDownFitSGTight->SetParameter(1, 2285.);
MagDownFitSGTight->SetParameter(2, 5);  
MagDownFitSGTight->SetParameter(3, 4);  
MagDownFitSGTight->SetParameter(4, 0.7);
MagDownFitSGTight->SetParLimits(4, 0.001, 0.999);   
MagDownFitSGTight->SetParameter(5, 750.);   
MagDownFitSGTight->SetParameter(6, -0.2);     
MagDownFitSGTight->SetParameter(7, 2.0);
MagDownFitSGTight->SetParameter(8, 3.0);   
MagDownFitSGTight->SetParLimits(8, 1.000001, 8.);  
 
TF1 *MagUpFitSGTight = new TF1("MagUpFitSGTight", NewCrystalBallHalfMeV,2212.,2362.,9);
MagUpFitSGTight->SetParameter(0,115000); 
MagUpFitSGTight->SetParameter(1, 2285.);
MagUpFitSGTight->SetParameter(2, 5);  
MagUpFitSGTight->SetParameter(3, 4);  
MagUpFitSGTight->SetParameter(4, 0.7);
MagUpFitSGTight->SetParLimits(4, 0.001, 0.999);   
MagUpFitSGTight->SetParameter(5, 750.);   
MagUpFitSGTight->SetParameter(6, -0.2);     
MagUpFitSGTight->SetParameter(7, 2.0);
MagUpFitSGTight->SetParameter(8, 3.0);   
MagUpFitSGTight->SetParLimits(8, 1.000001, 8.);  
 
TF1 *ParticleFitSGTight = new TF1("ParticleFitSGTight", NewCrystalBallHalfMeV,2212.,2362.,9);
ParticleFitSGTight->SetParameter(0,115000); 
ParticleFitSGTight->SetParameter(1, 2285.);
ParticleFitSGTight->SetParameter(2, 5);  
ParticleFitSGTight->SetParameter(3, 4);  
ParticleFitSGTight->SetParameter(4, 0.7);
ParticleFitSGTight->SetParLimits(4, 0.001, 0.999);   
ParticleFitSGTight->SetParameter(5, 750.);   
ParticleFitSGTight->SetParameter(6, -0.2);     
ParticleFitSGTight->SetParameter(7, 2.0);
ParticleFitSGTight->SetParameter(8, 3.0);   
ParticleFitSGTight->SetParLimits(8, 1.000001, 8.);  
 
TF1 *AntiParticleFitSGTight = new TF1("AntiParticleFitSGTight", NewCrystalBallHalfMeV,2212.,2362.,9);
AntiParticleFitSGTight->SetParameter(0,115000); 
AntiParticleFitSGTight->SetParameter(1, 2285.);
AntiParticleFitSGTight->SetParameter(2, 5);  
AntiParticleFitSGTight->SetParameter(3, 4);  
AntiParticleFitSGTight->SetParameter(4, 0.7);
AntiParticleFitSGTight->SetParLimits(4, 0.001, 0.999);   
AntiParticleFitSGTight->SetParameter(5, 750.);   
AntiParticleFitSGTight->SetParameter(6, -0.2);     
AntiParticleFitSGTight->SetParameter(7, 2.0);
AntiParticleFitSGTight->SetParameter(8, 3.0);   
AntiParticleFitSGTight->SetParLimits(8, 1.000001, 8.);  
 
  LcLowPTight->Fit("LcFitSGTight1");
 LcLowPTight->SetMinimum(0);
 c1->Write("Low Lc Momentum Region - Tight");
 c1->Clear();

 LcMidLowPTight->Fit("LcFitSGTight2");
 LcMidLowPTight->SetMinimum(0);
 c1->Write("MidLow Lc Momentum Region - Tight");
 c1->Clear();

 LcMidHighPTight->Fit("LcFitSGTight3");
 LcMidHighPTight->SetMinimum(0);
 c1->Write("MidHigh Lc Momentum Region - Tight");
 c1->Clear();

 LcHighPTight->Fit("LcFitSGTight4");
 LcHighPTight->SetMinimum(0);
 c1->Write("High Lc Momentum Region - Tight");
 c1->Clear();

 LcPDistributionTight->Draw();
 LcPDistributionTight->SetMinimum(0);
 c1->Write("Lc Momentum Distribution - Tight");
 c1->Clear();

 double yTight1 = LcFitSGTight1->GetParameter(1);
 double yTight2 = LcFitSGTight2->GetParameter(1);
 double yTight3 = LcFitSGTight3->GetParameter(1);
 double yTight4 = LcFitSGTight4->GetParameter(1);

 double yerrTight1 = LcFitSGTight1->GetParError(1);
 double yerrTight2 = LcFitSGTight2->GetParError(1);
 double yerrTight3 = LcFitSGTight3->GetParError(1);
 double yerrTight4 = LcFitSGTight4->GetParError(1);

grid->cd();
grid->SetGridy();

 double LcPAvGTight = ((yTight1 + yTight2 + yTight3 + yTight4)/n);
 Double_t yTight[n] = {yTight1 - LcPAvGTight,yTight2 - LcPAvGTight,yTight3 - LcPAvGTight,yTight4 - LcPAvGTight};
 Double_t yerrTight[n] = {yerrTight1,yerrTight2,yerrTight3,yerrTight4};
 gLcPTight = new TGraphErrors(n,x,yTight,xerr,yerrTight);
 gLcPTight->SetMarkerColor(2);
 gLcPTight->SetMarkerStyle(20);
 gLcPTight->GetXaxis()->SetNdivisions(4);
 gLcPTight->GetXaxis()->SetTitle("LambdaC P Regions");
 gLcPTight->GetYaxis()->SetTitle("Measured Mass - Average Mass [MeV]");
 gLcPTight->SetTitle("Deviations in LambdaC Mass of Different LambdaC_P Regions");
 gLcPTight->Draw("ap");
 gLcPTight->GetXaxis()->SetAlphanumeric();
 gLcPTight->GetXaxis()->SetBinLabel(9, "(0-70) GeV");
 gLcPTight->GetXaxis()->SetBinLabel(36, "(70-88.5) GeV");
 gLcPTight->GetXaxis()->SetBinLabel(63, "(88.5-112) GeV");
 gLcPTight->GetXaxis()->SetBinLabel(90, "(112-250) GeV");   
 gLcPTight->GetXaxis()->LabelsOption("h");
 grid->Write("Lcplus_P Statistics - Tight");

c1->cd();

PolarityMagDownTight->Fit("MagDownFitSGTight");
PolarityMagDownTight->SetMinimum(0);
c1->Write("PolarityMagDown - Tight");
 c1->Clear();

PolarityMagUpTight->Fit("MagUpFitSGTight");
PolarityMagUpTight->SetMinimum(0);
c1->Write("PolarityMagUp - Tight");
 c1->Clear();

double pTight1 = MagDownFitSGTight->GetParameter(1);
double pTight2 = MagUpFitSGTight->GetParameter(1);

double perrTight1 = MagDownFitSGTight->GetParError(1);
double perrTight2 = MagUpFitSGTight->GetParError(1);

double PolarityAvGTight = ((pTight1 + pTight2)/m);
Double_t pTight[m] = {pTight1 - PolarityAvGTight,pTight2 - PolarityAvGTight};
Double_t perrTight[m] = {perrTight1,perrTight2};

grid->cd();

gPolarityTight = new TGraphErrors(m,x,pTight,xerr,perrTight);
gPolarityTight->SetMarkerColor(2);
gPolarityTight->SetMarkerStyle(20);
gPolarityTight->GetXaxis()->SetNdivisions(2);
gPolarityTight->GetXaxis()->SetTitle("Magnet Orientations");
gPolarityTight->GetYaxis()->SetTitle("Measured Mass - Average Mass [MeV]");
gPolarityTight->SetTitle("Deviations in LambdaC Mass of Different Magnet Orientations");
gPolarityTight->GetXaxis()->SetAlphanumeric();
gPolarityTight->GetXaxis()->SetBinLabel(9, "MagDown");
gPolarityTight->GetXaxis()->SetBinLabel(92, "MagUp");   
gPolarityTight->GetXaxis()->LabelsOption("h");   
gPolarityTight->Draw("ap");

grid->Write("Polarity Statistics - Tight");

c1->cd();

ParticleTight->Fit("ParticleFitSGTight");
ParticleTight->SetMinimum(0);
c1->Write("Baryon - Tight");
 c1->Clear();

AntiParticleTight->Fit("AntiParticleFitSGTight");
AntiParticleTight->SetMinimum(0);
c1->Write("AntiBaryon - Tight");
 c1->Clear();

double ppTight1 = ParticleFitSGTight->GetParameter(1);
double ppTight2 = AntiParticleFitSGTight->GetParameter(1);

double pperrTight1 = ParticleFitSGTight->GetParError(1);
double pperrTight2 = AntiParticleFitSGTight->GetParError(1);

double ParticleAvGTight = ((ppTight1 + ppTight2)/m);
Double_t ppTight[m] = {ppTight1 - ParticleAvGTight,ppTight2 - ParticleAvGTight};
Double_t pperrTight[m] = {pperrTight1,pperrTight2};

grid->cd();
 
gPIDTight = new TGraphErrors(m,x,ppTight,xerr,pperrTight);
gPIDTight->SetMarkerColor(2);
gPIDTight->SetMarkerStyle(20);
gPIDTight->GetXaxis()->SetNdivisions(2);
gPIDTight->GetXaxis()->SetTitle("Particle ID");
gPIDTight->GetYaxis()->SetTitle("Measured Mass - Average Mass [MeV]");
gPIDTight->SetTitle("Deviations in LambdaC Mass of Baryon or AntiBaryon");
gPIDTight->GetXaxis()->SetAlphanumeric();
gPIDTight->GetXaxis()->SetBinLabel(9, "Baryon");
gPIDTight->GetXaxis()->SetBinLabel(92, "AntiBaryon");   
gPIDTight->GetXaxis()->LabelsOption("h");   
gPIDTight->Draw("ap");
grid->Write("ParticleStatistics - Tight");
   
   File->Close();
}
