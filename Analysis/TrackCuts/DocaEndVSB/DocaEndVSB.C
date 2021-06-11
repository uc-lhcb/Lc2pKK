#define DocaEndVSB_cxx
#include "DocaEndVSB.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

#include "DGOneMuOneTotalHalfMeV.C"

TH1D * FinalMass = nullptr;

TH1D * DOCASignal = nullptr;
TH1D * DOCABackground = nullptr;
TH1D * DOCASignalEstimate = nullptr;
TH1D * ENDVSignal = nullptr;
TH1D * ENDVBackground = nullptr;
TH1D * ENDVSignalEstimate = nullptr;

TH2D * ENDVDOCAEvents = nullptr;
TH2D * ENDVDOCASignal = nullptr;
TH2D * ENDVDOCASignalEstimate = nullptr;
TH2D * ENDVDOCABackground = nullptr;


TFile * File = nullptr;
TCanvas * c1 = nullptr;

void DocaEndVSB::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void DocaEndVSB::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

   FinalMass = new TH1D("", "", 260, 2222, 2352);
   FinalMass->GetXaxis()->SetTitle("MeV(p^{+}K^{+}K^{-})");
   FinalMass->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   DOCASignal= new TH1D("", "Signal Region", 100, 0., 0.2);
   DOCABackground = new TH1D("", "Background Region", 100, 0., 0.2);
   DOCASignalEstimate = new TH1D("", "Signal Estimate", 100, 0., 0.2);
   DOCASignal->SetLineColor(kBlue);
   DOCABackground->SetLineColor(kRed);
   DOCASignalEstimate->SetLineColor(kGreen+3);

   ENDVSignal= new TH1D("", "Signal Region", 100, 0, 1.5);
   ENDVBackground = new TH1D("", "Background Region", 100, 0, 1.5);
   ENDVSignalEstimate = new TH1D("", "Signal Estimate", 100, 0, 1.5);
   ENDVSignal->SetLineColor(kBlue);
   ENDVBackground->SetLineColor(kRed);
   ENDVSignalEstimate->SetLineColor(kGreen+3);

   ENDVDOCAEvents = new TH2D("", "", 100, 0., 0.2, 100, 0., 1.5);
   ENDVDOCAEvents->GetZaxis()->SetTitle("Events");

   ENDVDOCASignal = new TH2D("", "", 100, 0., 0.2, 100, 0., 1.5);
   ENDVDOCASignal->GetZaxis()->SetTitle("Events");

   ENDVDOCABackground = new TH2D("", "", 100, 0., 0.2, 100, 0., 1.5);
   ENDVDOCABackground->GetZaxis()->SetTitle("Events");

   ENDVDOCASignalEstimate = new TH2D("", "", 100, 0., 0.2, 100, 0., 1.5);
   ENDVDOCASignalEstimate->GetZaxis()->SetTitle("Events");

   File = new TFile("TrackCuts.root", "RECREATE");
   gFile = File;

    c1 = new TCanvas("canvas", "Test Canvas");

}

Bool_t DocaEndVSB::Process(Long64_t entry)
{
  GetEntry(entry);
  fReader.SetLocalEntry(entry);

  TLorentzVector P_vec(*Proton_PX, *Proton_PY, *Proton_PZ, *Proton_PE);
  TLorentzVector Kp_vec(*Kplus_PX, *Kplus_PY, *Kplus_PZ, *Kplus_PE);
  TLorentzVector Km_vec(*Kminus_PX, *Kminus_PY, *Kminus_PZ, *Kminus_PE);
  TLorentzVector LcVec;

  TLorentzVector PKp_vec;
  TLorentzVector PKm_vec;
  TLorentzVector KpKm_vec;

  PKp_vec = P_vec+Kp_vec;
  PKm_vec = P_vec+Km_vec;
  KpKm_vec = Kp_vec+Km_vec;

  double M2_PKp = PKp_vec.Mag2()/(1000*1000);
  double M2_PKm  = PKm_vec.Mag2()/(1000*1000);
  double M2_KpKm = KpKm_vec.Mag2()/(1000*1000);

double prodProbNNx = (*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp);
double DalitzLow = (1.019455-0.012)*(1.019455-0.012);
double DalitzHigh = (1.019455+0.012)*(1.019455+0.012);

  bool  PIDBSubbedCuts= (
       (prodProbNNx > 0.8)
    && (*Proton_ProbNNp > 0.9)
        );

  bool DalitzCuts= (
    M2_KpKm > DalitzLow
&&  M2_KpKm < DalitzHigh
  );

 bool MomentumCut= (
   (*Lc_P < 110000)
 );

bool DOCAENDVCut= (
TMath::Log10(*Lc_ENDVERTEX_CHI2) > (10*(*Lc_Loki_DOCAMAX) - 0.5)
&& TMath::Log10(*Lc_ENDVERTEX_CHI2) < 1.2
);


 bool SignalRegion = *Lc_M > 2275.4 && *Lc_M < 2299.4;
 bool BackgroundRegion = (*Lc_M > 2222. && *Lc_M < 2270.) || (*Lc_M > 2304. && *Lc_M < 2352.);

 if(PIDBSubbedCuts && DalitzCuts && MomentumCut){

ENDVDOCAEvents->Fill(*Lc_Loki_DOCAMAX, TMath::Log10(*Lc_ENDVERTEX_CHI2));

 if(SignalRegion){
   DOCASignal->Fill(*Lc_Loki_DOCAMAX);
   ENDVSignal->Fill(TMath::Log10(*Lc_ENDVERTEX_CHI2));
   ENDVDOCASignal->Fill(*Lc_Loki_DOCAMAX, TMath::Log10(*Lc_ENDVERTEX_CHI2));
 }

 if(BackgroundRegion){
   DOCABackground->Fill(*Lc_Loki_DOCAMAX);
   ENDVBackground->Fill(TMath::Log10(*Lc_ENDVERTEX_CHI2));
   ENDVDOCABackground->Fill(*Lc_Loki_DOCAMAX, TMath::Log10(*Lc_ENDVERTEX_CHI2));
 }
 if (DOCAENDVCut){
   FinalMass->Fill(*Lc_M);
 }
}

   return kTRUE;
}

void DocaEndVSB::SlaveTerminate()
{

}

void DocaEndVSB::Terminate()
{
  gStyle->SetOptStat(11);
  c1->SetBottomMargin(0.2);
  c1->SetLeftMargin(0.15);
  auto lt = new TLatex();
  lt->SetTextSize(0.04);

DOCASignalEstimate->Add(DOCASignal,DOCABackground,1.0,-0.25);
ENDVSignalEstimate->Add(ENDVSignal,ENDVBackground,1.0,-0.25);
ENDVDOCASignalEstimate->Add(ENDVDOCASignal,ENDVDOCABackground,1.0,-0.25);

FinalMass->SetMinimum(0.0001);
FinalMass->GetXaxis()->CenterTitle(true);
FinalMass->GetXaxis()->SetTitleSize(20);
FinalMass->GetXaxis()->SetTitleFont(43);
FinalMass->GetXaxis()->SetTitleOffset(1.5);
FinalMass->GetXaxis()->SetLabelSize(0.05);
FinalMass->GetYaxis()->SetTitleSize(20);
FinalMass->GetYaxis()->SetTitleFont(43);
FinalMass->GetYaxis()->SetLabelSize(0.05);
FinalMass->Draw();
c1->SaveAs("LcMDocaEnd.pdf");

gStyle->SetOptStat(0);

DOCASignal->GetYaxis()->SetTitle("Events / 0.01 mm");
DOCASignal->GetXaxis()->SetTitle("#Lambda_{c}_DOCA_Max [mm]");
DOCASignal->SetMinimum(0);
DOCASignal->GetXaxis()->CenterTitle(true);
DOCASignal->GetXaxis()->SetTitleSize(20);
DOCASignal->GetXaxis()->SetTitleFont(43);
DOCASignal->GetXaxis()->SetTitleOffset(1.5);
DOCASignal->GetXaxis()->SetLabelSize(0.05);
DOCASignal->GetYaxis()->SetTitleSize(20);
DOCASignal->GetYaxis()->SetTitleFont(43);
DOCASignal->GetYaxis()->SetLabelSize(0.05);
DOCASignal->Draw();
DOCASignalEstimate->Draw("SAME");
DOCABackground->Draw("SAME");
gPad->BuildLegend(0.65,0.65,0.85,0.85);
lt->DrawLatexNDC(0.65, 0.60, "LHCb Preliminary");
DOCASignal->SetTitle("");
c1->SaveAs("DOCABsub.pdf");

ENDVSignal->GetYaxis()->SetTitle("Events / 0.015 ");
ENDVSignal->GetXaxis()->SetTitle("#chi^2_{Vertex} on Log10 Scale");
ENDVSignal->SetMinimum(0);
ENDVSignal->GetXaxis()->CenterTitle(true);
ENDVSignal->GetXaxis()->SetTitleSize(20);
ENDVSignal->GetXaxis()->SetTitleFont(43);
ENDVSignal->GetXaxis()->SetTitleOffset(1.5);
ENDVSignal->GetXaxis()->SetLabelSize(0.05);
ENDVSignal->GetYaxis()->SetTitleSize(20);
ENDVSignal->GetYaxis()->SetTitleFont(43);
ENDVSignal->GetYaxis()->SetLabelSize(0.05);
ENDVSignal->GetXaxis()->SetNdivisions(6);
ENDVSignal->Draw();
ENDVSignalEstimate->Draw("SAME");
ENDVBackground->Draw("SAME");
gPad->BuildLegend(0.65,0.65,0.85,0.85);
lt->DrawLatexNDC(0.65, 0.60, "LHCb Preliminary");
ENDVSignal->SetTitle("");
c1->SaveAs("ENDVBsub.pdf");

c1->SetRightMargin(0.15);

ENDVDOCAEvents->GetYaxis()->SetTitle("#chi^2_{Vertex} on Log10 Scale");
ENDVDOCAEvents->GetXaxis()->SetTitle("Lc_DOCA_Max [mm]");
ENDVDOCAEvents->GetXaxis()->CenterTitle(true);
ENDVDOCAEvents->GetXaxis()->SetTitleSize(20);
ENDVDOCAEvents->GetXaxis()->SetTitleFont(43);
ENDVDOCAEvents->GetXaxis()->SetTitleOffset(1.5);
ENDVDOCAEvents->GetXaxis()->SetLabelSize(0.05);
ENDVDOCAEvents->GetYaxis()->SetTitleSize(20);
ENDVDOCAEvents->GetYaxis()->SetTitleFont(43);
ENDVDOCAEvents->GetYaxis()->SetLabelSize(0.05);
ENDVDOCAEvents->GetXaxis()->SetNdivisions(6);
ENDVDOCAEvents->GetZaxis()->SetTitleOffset(1);
ENDVDOCAEvents->SetTitle("DOCA_Max vs #chi^{2}_{Vertex} - All Events");
ENDVDOCAEvents->Draw("COLZ");
TF1 *f1 = new TF1("f1","10*x - 0.5",0.05,0.17);
TF1 *f2 = new TF1("f2","1.2",0,0.17);
f1->SetLineColor(kRed);
f2->SetLineColor(kRed);
f1->SetLineWidth(3);
f2->SetLineWidth(3);
f1->Draw("SAME");
f2->Draw("SAME");
c1->SaveAs("ENDVDOCAEvents.pdf");

ENDVDOCASignal->GetYaxis()->SetTitle("#chi^2_{Vertex} on Log10 Scale");
ENDVDOCASignal->GetXaxis()->SetTitle("Lc_DOCA_Max [mm]");
ENDVDOCASignal->GetXaxis()->CenterTitle(true);
ENDVDOCASignal->GetXaxis()->SetTitleSize(20);
ENDVDOCASignal->GetXaxis()->SetTitleFont(43);
ENDVDOCASignal->GetXaxis()->SetTitleOffset(1.5);
ENDVDOCASignal->GetXaxis()->SetLabelSize(0.05);
ENDVDOCASignal->GetYaxis()->SetTitleSize(20);
ENDVDOCASignal->GetYaxis()->SetTitleFont(43);
ENDVDOCASignal->GetYaxis()->SetLabelSize(0.05);
ENDVDOCASignal->GetXaxis()->SetNdivisions(6);
ENDVDOCASignal->GetZaxis()->SetTitleOffset(1);
ENDVDOCASignal->Draw("CONTZ");
  c1->SaveAs("ENDVDOCASignal.pdf");

  ENDVDOCASignalEstimate->GetYaxis()->SetTitle("#chi^2_{Vertex} on Log10 Scale");
  ENDVDOCASignalEstimate->GetXaxis()->SetTitle("Lc_DOCA_Max [mm]");
  ENDVDOCASignalEstimate->GetXaxis()->CenterTitle(true);
  ENDVDOCASignalEstimate->GetXaxis()->SetTitleSize(20);
  ENDVDOCASignalEstimate->GetXaxis()->SetTitleFont(43);
  ENDVDOCASignalEstimate->GetXaxis()->SetTitleOffset(1.5);
  ENDVDOCASignalEstimate->GetXaxis()->SetLabelSize(0.05);
  ENDVDOCASignalEstimate->GetYaxis()->SetTitleSize(20);
  ENDVDOCASignalEstimate->GetYaxis()->SetTitleFont(43);
  ENDVDOCASignalEstimate->GetYaxis()->SetLabelSize(0.05);
  ENDVDOCASignalEstimate->GetXaxis()->SetNdivisions(6);
  ENDVDOCASignalEstimate->GetZaxis()->SetTitleOffset(1);
  ENDVDOCASignalEstimate->Draw("CONTZ");
    c1->SaveAs("ENDVDOCASignalEstimate.pdf");

ENDVDOCABackground->GetYaxis()->SetTitle("#chi^2_{Vertex} on Log10 Scale");
ENDVDOCABackground->GetXaxis()->SetTitle("Lc_DOCA_Max [mm]");
ENDVDOCABackground->GetXaxis()->CenterTitle(true);
ENDVDOCABackground->GetXaxis()->SetTitleSize(20);
ENDVDOCABackground->GetXaxis()->SetTitleFont(43);
ENDVDOCABackground->GetXaxis()->SetTitleOffset(1.5);
ENDVDOCABackground->GetXaxis()->SetLabelSize(0.05);
ENDVDOCABackground->GetYaxis()->SetTitleSize(20);
ENDVDOCABackground->GetYaxis()->SetTitleFont(43);
ENDVDOCABackground->GetYaxis()->SetLabelSize(0.05);
ENDVDOCABackground->GetXaxis()->SetNdivisions(6);
ENDVDOCABackground->GetZaxis()->SetTitleOffset(1);
ENDVDOCABackground->Draw("CONTZ");
  c1->SaveAs("ENDVDOCABackground.pdf");

ENDVDOCASignalEstimate->Divide(ENDVDOCABackground);
ENDVDOCASignalEstimate->SetTitle("DOCA_Max vs #chi^{2}_{Vertex} - S/B Scatterplot");
ENDVDOCASignalEstimate->Draw("CONTZ");
ENDVDOCASignalEstimate->GetZaxis()->SetTitle("S/B");
c1->SaveAs("ENDVDOCASB.pdf");
f1->Draw("SAME");
f2->Draw("SAME");
c1->SaveAs("ENDVDOCASBCut.pdf");

}
