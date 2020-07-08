#define DalitzPlot_cxx
#include "DalitzPlot.h"

#include "DGOneMuOneTotalHalfMeV.C"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

TH2D * DalitzPlotUncut = nullptr;
TH2D * DalitzPlotLc = nullptr;
TH1D * KpKmMassHist = nullptr;
TH1D * PKmMassHist = nullptr;
TH1D * PKpMassHist = nullptr;


TH1D * MassHist = nullptr;
TH1D * BSubHist = nullptr;

TFile * File = nullptr;

TCanvas * c1 = nullptr;
TCanvas * ex1 = nullptr;

void DalitzPlot::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
   
         //Dalitz Plot is a 2D Histogram
         DalitzPlotLc = new TH2D("Dalitz Plot", "Dalitz Plot of Lc->pKK Decay - Background Subtracted", 100, 0.8, 2.2, 100, 1.7, 3.7);
         DalitzPlotLc->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
         DalitzPlotLc->GetYaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
         DalitzPlotLc->GetZaxis()->SetTitle("Events");
   
            //Dalitz Plot is a 2D Histogram
         DalitzPlotUncut = new TH2D("Dalitz Plot", "Dalitz Plot of Lc->pKK Decay - Uncut", 100, 0.8, 2.2, 100, 1.7, 3.7);
         DalitzPlotUncut->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
         DalitzPlotUncut->GetYaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
         DalitzPlotUncut->GetZaxis()->SetTitle("Events");
         
         //Plot of M^2 Variable for K+ and K- Combination
         KpKmMassHist = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Kplus & Kminus Invariant Mass Combination", 100, 0.95, 2);
         KpKmMassHist->GetXaxis()->SetTitle("m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");                    
         KpKmMassHist->GetYaxis()->SetTitle("Events");
 
         //Plot of M^2 Variable for p+ and K- Combination
         PKmMassHist = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kminus Invariant Mass Combination", 100, 2, 3.5);
         PKmMassHist->GetXaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");                   
         PKmMassHist->GetYaxis()->SetTitle("Events");
   
         //Plot of M^2 Variable for p+ and K+ Combination (Not Used for Dalitz Plot)
         PKpMassHist = new TH1D("M^{2} [GeV^{2}/c^{4}]", "Proton & Kplus Invariant Mass Combination", 100, 2, 3.5);
         PKpMassHist->GetXaxis()->SetTitle("m^{2}(pK^{+})[GeV^{2}/c^{4}]");                   
         PKpMassHist->GetYaxis()->SetTitle("Events");   

   
   MassHist = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 300, 2210, 2360);
   MassHist->GetXaxis()->SetTitle("MeV");
   MassHist->GetYaxis()->SetTitle("Events Per 2 MeV");
   
   BSubHist = new TH1D("Mass [MeV]", "Lc->pKK - Lc Mass", 50, 2275, 2300);
   BSubHist->GetXaxis()->SetTitle("MeV");
   BSubHist->GetYaxis()->SetTitle("Events Per 2 MeV");
   
    File = new TFile("DalitzAnalysis.root", "RECREATE");
  gFile = File;


   c1 = new TCanvas("canvas", "Test Canvas");
   ex1 = new TCanvas("ex1","Latex",500,600);
}

void DalitzPlot::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
}

Bool_t DalitzPlot::Process(Long64_t entry)
{
   GetEntry(entry);
   fReader.SetLocalEntry(entry);
 
//Defining Variables
double P_P  = *Proton_P;
double P_Kp = *Kplus_P;
double P_Km = *Kminus_P;
 
double M_P  = *Proton_M;
double M_Kp = *Kplus_M;
double M_Km = *Kminus_M;
 
//Creating Energy Variables
double E_P  = TMath::Sqrt(((P_P)*(P_P))+((M_P)*(M_P)));
double E_Kp = TMath::Sqrt(((P_Kp)*(P_Kp))+((M_Kp)*(M_Kp)));
double E_Km = TMath::Sqrt(((P_Km)*(P_Km))+((M_Km)*(M_Km)));
 
TLorentzVector P(*Proton_PX, *Proton_PY, *Proton_PZ, *Proton_PE);
TLorentzVector Kp(*Kplus_PX, *Kplus_PY, *Kplus_PZ, *Kplus_PE);
TLorentzVector Km(*Kminus_PX, *Kminus_PY, *Kminus_PZ, *Kminus_PE);

double ProtonMass = P.Mag();
double KplusMass  = Kp.Mag();
double KminusMass = Km.Mag();

   //Creating M^2 Variables
double M2_KpKm = (KplusMass + KminusMass)*(KplusMass + KminusMass)/(1000*1000);
double M2_PKm  = (ProtonMass + KminusMass)*(ProtonMass + KminusMass)/(1000*1000);
double M2_PKp  = (KplusMass + ProtonMass)*(KplusMass + ProtonMass)/(1000*1000);
//double M2_KpKm = ((((E_Kp)+(E_Km))*((E_Kp)+(E_Km))) - (((P_Kp)+(P_Km))*((P_Kp)+(P_Km))))/(1000*1000);
//double M2_PKm  = ((((E_P)+(E_Km))*((E_P)+(E_Km))) - (((P_P)+(P_Km))*((P_P)+(P_Km))))/(1000*1000);
//double M2_PKp  = ((((E_P)+(E_Kp))*((E_P)+(E_Kp))) - (((P_P)+(P_Kp))*((P_P)+(P_Kp))))/(1000*1000);

 DalitzPlotUncut->Fill(M2_KpKm, M2_PKm);   
   
bool Cut = (
     ((*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp) > 0.9)
&&   ((*Kminus_ProbNNk)*(*Kplus_ProbNNk) > 0.95)
&&   ((*Proton_ProbNNp)*(*Kplus_ProbNNk) > 0.95)
&&   ((*Kminus_ProbNNk)*(*Proton_ProbNNp) > 0.95)
   );

bool SignalRegion = (
    (*Lcplus_M > 2275.)  
 && (*Lcplus_M < 2300.)  
   );
   
 if (Cut){
    MassHist->Fill(*Lcplus_M);
 }  
       
if (Cut & SignalRegion){
 BSubHist->Fill(*Lcplus_M);
 KpKmMassHist->Fill(M2_KpKm);
 PKmMassHist->Fill(M2_PKm);
 PKpMassHist->Fill(M2_PKp);
 DalitzPlotLc->Fill(M2_KpKm, M2_PKm);
}
   
   return kTRUE;
}

void DalitzPlot::SlaveTerminate()
{
}

void DalitzPlot::Terminate()
{
   
//Changes Current Directory to c1 to Canvas 
c1->cd();

//Creates Dalitz Plots with Various Options
DalitzPlotUncut->Draw();
 c1->Write("Dalitz Plot - Uncut");
   DalitzPlotLc->Draw();
 c1->Write("Dalitz Plot - Background Subtracted");
DalitzPlotLc->Draw("COLZ");
 c1->Write("Dalitz Plot - COLZ");
DalitzPlotLc->Draw("CONTZ");
 c1->Write("Dalitz Plot - CONTZ");

 //Creates Histograms for M^2 Variables  
KpKmMassHist->Draw();
 c1->Write("Kp & Km Mass"); 
   
 PKmMassHist->Draw();
 c1->Write("P & Km Mass");
   
 PKpMassHist->Draw();
 c1->Write("P & Kp Mass");
    
BSubHist->Draw();
c1->Write("Signal Events");
   
TPad *pad1 = new TPad("pad1","pad1",0,0.33,1,1);
TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.33);
pad2->SetTopMargin(0.03030303);
pad1->Draw();
pad2->Draw();
   
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
   
TF1 *Gaussian = new TF1("Gaussian",DGOneMuOneTotalHalfMeV,2200.,2400.,7);
Gaussian->SetParameter(0, 0.5);
Gaussian->SetParameter(1, 10000);
Gaussian->SetParameter(2, 2287.);
Gaussian->SetParameter(3, 5);
Gaussian->SetParameter(4, 5);
Gaussian->SetParLimits(3, 0., 20.);
Gaussian->SetParLimits(4, 0., 20.);
Gaussian->SetParameter(5, 0.);
Gaussian->SetParameter(6, 0.);

pad1->cd();
MassHist->SetMinimum(0);
MassHist->Fit("Gaussian");

double Pullx[300];
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
FitHeight[bin] = round(Gaussian->Eval(xvalue));
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
 ex1->Clear();
   TLatex Tl;
   Tl.SetTextAlign(12);
   Tl.SetTextSize(0.04);
   Tl.DrawLatex(0.1,0.95,Form("Number of Signal Entries: %f Events", Gaussian->GetParameter(1)));
   Tl.DrawLatex(0.1,0.9,Form("Error: %f Events", Gaussian->GetParError(1)));
   Tl.DrawLatex(0.1,0.8,Form("Percentage of Events in First Gaussian: %f Events", Gaussian->GetParameter(0)));
   Tl.DrawLatex(0.1,0.75,Form("Error: %f Events", Gaussian->GetParError(0)));
   Tl.DrawLatex(0.1,0.65,Form("Mean Value: %f MeV", Gaussian->GetParameter(2)));
   Tl.DrawLatex(0.1,0.6,Form("Error: %f MeV", Gaussian->GetParError(2)));
   Tl.DrawLatex(0.1,0.5,Form("Sigma of First Gaussian: %f MeV", Gaussian->GetParameter(3)));
   Tl.DrawLatex(0.1,0.45,Form("Error: %f MeV", Gaussian->GetParError(3)));
   Tl.DrawLatex(0.1,0.35,Form("Sigma of Second Gaussian: %f MeV", Gaussian->GetParameter(4)));
   Tl.DrawLatex(0.1,0.3,Form("Error: %f MeV", Gaussian->GetParError(4)));
   Tl.DrawLatex(0.1,0.2,Form("Bins Between -1 & 1 %f Bins", count1));
   Tl.DrawLatex(0.1,0.15,Form("Bins Between -2 & 2 %f Bins", count2));
   Tl.DrawLatex(0.1,0.1,Form("Bins Between -3 & 3 %f Bins", count3));
   
   ex1->Write("Fit Values");
c1->cd();
   
File->Close();
}
