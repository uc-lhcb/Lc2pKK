#define Efficiency_cxx
#include "Efficiency.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

#include "DoubleGaussQuadNewHalf.C"

TH1D * Uncut = nullptr;
TH1D * Cut1 = nullptr;
TH1D * Cut2 = nullptr;
TH1D * Cut3 = nullptr;
TH1D * Cut4 = nullptr;
TH1D * Cut5 = nullptr;
TH1D * Cut6 = nullptr;

TCanvas * c1 = nullptr;

void Efficiency::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void Efficiency::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

   Uncut = new TH1D("", "", 260, 2222, 2352);
   Uncut->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
   Uncut->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   Cut1 = new TH1D("", "", 260, 2222, 2352);
   Cut1->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
   Cut1->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   Cut2 = new TH1D("", "", 260, 2222, 2352);
   Cut2->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
   Cut2->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   Cut3 = new TH1D("", "", 260, 2222, 2352);
   Cut3->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
   Cut3->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   Cut4 = new TH1D("", "", 260, 2222, 2352);
   Cut4->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
   Cut4->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   Cut5 = new TH1D("", "", 260, 2222, 2352);
   Cut5->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
   Cut5->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   Cut6 = new TH1D("", "", 260, 2222, 2352);
   Cut6->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
   Cut6->GetYaxis()->SetTitle("Entries / (0.5 MeV)");

       c1 = new TCanvas("canvas", "Test Canvas");

}

Bool_t Efficiency::Process(Long64_t entry)
{

  GetEntry(entry);
  fReader.SetLocalEntry(entry);

  bool MassRange= (
  (*Lc_M > 2222 && *Lc_M < 2352)
  );

if (MassRange){
  Uncut->Fill(*Lc_M);
}

bool ProtonPID=(
(*Proton_ProbNNp > 0.9)
);

if (MassRange && ProtonPID){
  Cut1->Fill(*Lc_M);
}

double prodProbNNx = (*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp);
bool ProdPID=(
(prodProbNNx > 0.8)
);

if (MassRange && ProtonPID && ProdPID){
  Cut2->Fill(*Lc_M);
}

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

double DalitzLow = (1.019455-0.012)*(1.019455-0.012);
double DalitzHigh = (1.019455+0.012)*(1.019455+0.012);

  bool DalitzCuts= (
    M2_KpKm > DalitzLow
&&  M2_KpKm < DalitzHigh
  );

  if (MassRange && ProtonPID && ProdPID && DalitzCuts){
    Cut3->Fill(*Lc_M);
  }

  bool LcENDVERTEX= (
  TMath::Log10(*Lc_ENDVERTEX_CHI2) < 1.2
  );

  if (MassRange && ProtonPID && ProdPID && DalitzCuts && LcENDVERTEX){
    Cut4->Fill(*Lc_M);
  }

  bool LcENDVDOCA= (
  TMath::Log10(*Lc_ENDVERTEX_CHI2) > (10*(*Lc_Loki_DOCAMAX) - 0.5)
  );

  if (MassRange && ProtonPID && ProdPID && DalitzCuts && LcENDVERTEX && LcENDVDOCA){
    Cut5->Fill(*Lc_M);
  }

  bool LcTauIP= (
    ((1/0.9)*(1/0.9)*TMath::Log10(*Lc_IPCHI2_OWNPV)*TMath::Log10(*Lc_IPCHI2_OWNPV) + (1/0.0010)*(1/0.0010)*(*Lc_TAU - 0.0003)*(*Lc_TAU - 0.0003)) < 1
  );

  if (MassRange && ProtonPID && ProdPID && DalitzCuts && LcENDVERTEX && LcENDVDOCA && LcTauIP){
    Cut6->Fill(*Lc_M);
  }

   return kTRUE;
}

void Efficiency::SlaveTerminate()
{
}

void Efficiency::Terminate()
{
  gStyle->SetOptStat(11);
  gStyle->SetStatW(0.25);
  gStyle->SetStatH(0.25);

  auto lt = new TLatex();
  lt->SetTextSize(0.048);

  Uncut->SetLineWidth(2);
  Cut1->SetLineWidth(2);
  Cut2->SetLineWidth(2);
  Cut3->SetLineWidth(2);
  Cut4->SetLineWidth(2);
  Cut5->SetLineWidth(2);
  Cut6->SetLineWidth(2);

  c1->cd();

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

  TF1 *UncutFit = new TF1("UncutFit",DoubleGaussQuadNew,2222, 2352,8);
  UncutFit->SetParameter(0, 0.4);
  UncutFit->SetParLimits(0, 0.01, 0.99);
  UncutFit->SetParameter(1, 500000);
    UncutFit->SetParLimits(1, 10000, 10000000);
  UncutFit->SetParameter(2, 2287.);
  UncutFit->SetParameter(3, 4);
  UncutFit->SetParameter(4, 7);
  UncutFit->SetParLimits(3, 2, 10);
  UncutFit->SetParLimits(4, 2, 10);
  UncutFit->SetParameter(5, 10000);
  UncutFit->SetParameter(6, 0.0001);

  pad1->cd();
  pad1->Clear();
  Uncut->SetMinimum(0.0001);
  Uncut->SetLineWidth(2);
  Uncut->GetXaxis()->CenterTitle(true);
  Uncut->GetXaxis()->SetTitleSize(20);
  Uncut->GetXaxis()->SetTitleFont(43);
  Uncut->GetXaxis()->SetTitleOffset(1.5);
  Uncut->GetXaxis()->SetLabelSize(0.05);
  Uncut->GetYaxis()->SetTitleSize(20);
  Uncut->GetYaxis()->SetTitleFont(43);
  Uncut->GetYaxis()->SetLabelSize(0.05);
  Uncut->Fit("UncutFit", "E");

  TString SignalDGH;
  TString SignalErDGH;
  SignalDGH.Form("%5.0f\n", UncutFit->GetParameter(1));
  SignalErDGH.Form("%5.0f\n", UncutFit->GetParError(1));
  TString FractionDGH;
  TString FractionErDGH;
  FractionDGH.Form("%5.3f\n", UncutFit->GetParameter(0));
  FractionErDGH.Form("%5.3f\n", UncutFit->GetParError(0));
  TString muDGH;
  TString muErDGH;
  muDGH.Form("%5.3f\n", UncutFit->GetParameter(2));
  muErDGH.Form("%5.3f\n", UncutFit->GetParError(2));
  TString sigma1DGH;
  TString sigma1ErDGH;
  sigma1DGH.Form("%5.3f\n", UncutFit->GetParameter(3));
  sigma1ErDGH.Form("%5.3f\n", UncutFit->GetParError(3));
  TString rmsDGH;
  TString rmsErDGH;
  rmsDGH.Form("%5.3f\n", UncutFit->GetParameter(4));
  rmsErDGH.Form("%5.3f\n", UncutFit->GetParError(4));

  lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
  lt->DrawLatexNDC(0.58, 0.45, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
  lt->DrawLatexNDC(0.58, 0.40, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
  lt->DrawLatexNDC(0.58, 0.35, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
  lt->DrawLatexNDC(0.58, 0.30, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
  lt->DrawLatexNDC(0.58, 0.25, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

  pad2->cd();
  pad2->Clear();
  TH1D* UncutPull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
  UncutPull->SetStats(0);
  UncutPull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
  UncutPull->GetXaxis()->SetTitleSize(20);
  UncutPull->GetXaxis()->SetTitleFont(43);
  UncutPull->GetXaxis()->SetTitleOffset(4);
  UncutPull->GetXaxis()->SetLabelSize(0.1);
  UncutPull->GetYaxis()->SetTitle("Pull");
  UncutPull->GetYaxis()->CenterTitle(true);
  UncutPull->GetXaxis()->CenterTitle(true);
  UncutPull->GetYaxis()->SetTitleSize(20);
  UncutPull->GetYaxis()->SetTitleFont(43);
  UncutPull->GetYaxis()->SetLabelSize(0.1);
  UncutPull->SetFillColor(kBlue);
  UncutPull->SetLineColor(kBlue);
  UncutPull->SetBit(TH1::kNoTitle);

  for (Int_t i=1;i<260;i++) {
  Double_t x = Uncut->GetBinCenter(i);
  Double_t val = UncutFit->Eval(x);
  Double_t sigma = sqrt(val);
  Double_t pull = (Uncut->GetBinContent(i)-val)/sigma;
  UncutPull->SetBinContent(i,pull);
    }
  UncutPull->Draw();

  c1->SaveAs("LcMUncut.pdf");

TF1 *Cut1Fit = new TF1("Cut1Fit",DoubleGaussQuadNew,2222, 2352,8);
Cut1Fit->SetParameter(0, 0.4);
Cut1Fit->SetParLimits(0, 0.01, 0.99);
Cut1Fit->SetParameter(1, 100000);
Cut1Fit->SetParLimits(1, 50000, 1000000);
Cut1Fit->SetParameter(2, 2287.);
Cut1Fit->SetParameter(3, 4);
Cut1Fit->SetParameter(4, 7);
Cut1Fit->SetParLimits(3, 2, 10);
Cut1Fit->SetParLimits(4, 2, 10);
Cut1Fit->SetParameter(5, 100);
Cut1Fit->SetParameter(6, 0.001);

pad1->cd();
pad1->Clear();
Cut1->SetMinimum(0.0001);
Cut1->SetLineWidth(2);
Cut1->GetXaxis()->CenterTitle(true);
Cut1->GetXaxis()->SetTitleSize(20);
Cut1->GetXaxis()->SetTitleFont(43);
Cut1->GetXaxis()->SetTitleOffset(1.5);
Cut1->GetXaxis()->SetLabelSize(0.05);
Cut1->GetYaxis()->SetTitleSize(20);
Cut1->GetYaxis()->SetTitleFont(43);
Cut1->GetYaxis()->SetLabelSize(0.05);
Cut1->Fit("Cut1Fit", "E");

SignalDGH.Form("%5.0f\n", Cut1Fit->GetParameter(1));
SignalErDGH.Form("%5.0f\n", Cut1Fit->GetParError(1));
FractionDGH.Form("%5.3f\n", Cut1Fit->GetParameter(0));
FractionErDGH.Form("%5.3f\n", Cut1Fit->GetParError(0));
muDGH.Form("%5.3f\n", Cut1Fit->GetParameter(2));
muErDGH.Form("%5.3f\n", Cut1Fit->GetParError(2));
sigma1DGH.Form("%5.3f\n", Cut1Fit->GetParameter(3));
sigma1ErDGH.Form("%5.3f\n", Cut1Fit->GetParError(3));
rmsDGH.Form("%5.3f\n", Cut1Fit->GetParameter(4));
rmsErDGH.Form("%5.3f\n", Cut1Fit->GetParError(4));

lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

pad2->cd();
pad2->Clear();
TH1D* Cut1Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
Cut1Pull->SetStats(0);
Cut1Pull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
Cut1Pull->GetXaxis()->SetTitleSize(20);
Cut1Pull->GetXaxis()->SetTitleFont(43);
Cut1Pull->GetXaxis()->SetTitleOffset(4);
Cut1Pull->GetXaxis()->SetLabelSize(0.1);
Cut1Pull->GetYaxis()->SetTitle("Pull");
Cut1Pull->GetYaxis()->CenterTitle(true);
Cut1Pull->GetXaxis()->CenterTitle(true);
Cut1Pull->GetYaxis()->SetTitleSize(20);
Cut1Pull->GetYaxis()->SetTitleFont(43);
Cut1Pull->GetYaxis()->SetLabelSize(0.1);
Cut1Pull->SetFillColor(kBlue);
Cut1Pull->SetLineColor(kBlue);
Cut1Pull->SetBit(TH1::kNoTitle);

for (Int_t i=1;i<260;i++) {
Double_t x = Cut1->GetBinCenter(i);
Double_t val = Cut1Fit->Eval(x);
Double_t sigma = sqrt(val);
Double_t pull = (Cut1->GetBinContent(i)-val)/sigma;
Cut1Pull->SetBinContent(i,pull);
  }
Cut1Pull->Draw();

c1->SaveAs("LcMCut1.pdf");


    TF1 *Cut2Fit = new TF1("Cut2Fit",DoubleGaussQuadNew,2222, 2352,8);
    Cut2Fit->SetParameter(0, 0.4);
    Cut2Fit->SetParLimits(0, 0.01, 0.99);
    Cut2Fit->SetParameter(1, 10000);
    Cut2Fit->SetParameter(2, 2287.);
    Cut2Fit->SetParameter(3, 4);
    Cut2Fit->SetParameter(4, 7);
    Cut2Fit->SetParLimits(3, 0, 15);
    Cut2Fit->SetParLimits(4, 0, 15);
    Cut2Fit->SetParameter(5, 100);
    Cut2Fit->SetParameter(6, 0.001);

    pad1->cd();
    pad1->Clear();
    Cut2->SetMinimum(0.0001);
    Cut2->SetLineWidth(2);
    Cut2->GetXaxis()->CenterTitle(true);
    Cut2->GetXaxis()->SetTitleSize(20);
    Cut2->GetXaxis()->SetTitleFont(43);
    Cut2->GetXaxis()->SetTitleOffset(1.5);
    Cut2->GetXaxis()->SetLabelSize(0.05);
    Cut2->GetYaxis()->SetTitleSize(20);
    Cut2->GetYaxis()->SetTitleFont(43);
    Cut2->GetYaxis()->SetLabelSize(0.05);
    Cut2->Fit("Cut2Fit", "E");

    SignalDGH.Form("%5.0f\n", Cut2Fit->GetParameter(1));
    SignalErDGH.Form("%5.0f\n", Cut2Fit->GetParError(1));
    FractionDGH.Form("%5.3f\n", Cut2Fit->GetParameter(0));
    FractionErDGH.Form("%5.3f\n", Cut2Fit->GetParError(0));
    muDGH.Form("%5.3f\n", Cut2Fit->GetParameter(2));
    muErDGH.Form("%5.3f\n", Cut2Fit->GetParError(2));
    sigma1DGH.Form("%5.3f\n", Cut2Fit->GetParameter(3));
    sigma1ErDGH.Form("%5.3f\n", Cut2Fit->GetParError(3));
    rmsDGH.Form("%5.3f\n", Cut2Fit->GetParameter(4));
    rmsErDGH.Form("%5.3f\n", Cut2Fit->GetParError(4));

    lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
    lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
    lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
    lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

    pad2->cd();
    pad2->Clear();
    TH1D* Cut2Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
    Cut2Pull->SetStats(0);
    Cut2Pull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
    Cut2Pull->GetXaxis()->SetTitleSize(20);
    Cut2Pull->GetXaxis()->SetTitleFont(43);
    Cut2Pull->GetXaxis()->SetTitleOffset(4);
    Cut2Pull->GetXaxis()->SetLabelSize(0.1);
    Cut2Pull->GetYaxis()->SetTitle("Pull");
    Cut2Pull->GetYaxis()->CenterTitle(true);
    Cut2Pull->GetXaxis()->CenterTitle(true);
    Cut2Pull->GetYaxis()->SetTitleSize(20);
    Cut2Pull->GetYaxis()->SetTitleFont(43);
    Cut2Pull->GetYaxis()->SetLabelSize(0.1);
    Cut2Pull->SetFillColor(kBlue);
    Cut2Pull->SetLineColor(kBlue);
    Cut2Pull->SetBit(TH1::kNoTitle);

    for (Int_t i=1;i<260;i++) {
    Double_t x = Cut2->GetBinCenter(i);
    Double_t val = Cut2Fit->Eval(x);
    Double_t sigma = sqrt(val);
    Double_t pull = (Cut2->GetBinContent(i)-val)/sigma;
    Cut2Pull->SetBinContent(i,pull);
}
    Cut2Pull->Draw();

    c1->SaveAs("LcMCut2.pdf");

    TF1 *Cut3Fit = new TF1("Cut3Fit",DoubleGaussQuadNew,2222, 2352,8);
    Cut3Fit->SetParameter(0, 0.4);
    Cut3Fit->SetParLimits(0, 0.01, 0.99);
    Cut3Fit->SetParameter(1, 10000);
    Cut3Fit->SetParameter(2, 2287.);
    Cut3Fit->SetParameter(3, 4);
    Cut3Fit->SetParameter(4, 7);
    Cut3Fit->SetParLimits(3, 0, 15);
    Cut3Fit->SetParLimits(4, 0, 15);
    Cut3Fit->SetParameter(5, 100);
    Cut3Fit->SetParameter(6, 0.001);

    pad1->cd();
    pad1->Clear();
    Cut3->SetMinimum(0.0001);
    Cut3->SetLineWidth(2);
    Cut3->GetXaxis()->CenterTitle(true);
    Cut3->GetXaxis()->SetTitleSize(20);
    Cut3->GetXaxis()->SetTitleFont(43);
    Cut3->GetXaxis()->SetTitleOffset(1.5);
    Cut3->GetXaxis()->SetLabelSize(0.05);
    Cut3->GetYaxis()->SetTitleSize(20);
    Cut3->GetYaxis()->SetTitleFont(43);
    Cut3->GetYaxis()->SetLabelSize(0.05);
    Cut3->Fit("Cut3Fit", "E");

    SignalDGH.Form("%5.0f\n", Cut3Fit->GetParameter(1));
    SignalErDGH.Form("%5.0f\n", Cut3Fit->GetParError(1));
    FractionDGH.Form("%5.3f\n", Cut3Fit->GetParameter(0));
    FractionErDGH.Form("%5.3f\n", Cut3Fit->GetParError(0));
    muDGH.Form("%5.3f\n", Cut3Fit->GetParameter(2));
    muErDGH.Form("%5.3f\n", Cut3Fit->GetParError(2));
    sigma1DGH.Form("%5.3f\n", Cut3Fit->GetParameter(3));
    sigma1ErDGH.Form("%5.3f\n", Cut3Fit->GetParError(3));
    rmsDGH.Form("%5.3f\n", Cut3Fit->GetParameter(4));
    rmsErDGH.Form("%5.3f\n", Cut3Fit->GetParError(4));

    lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
    lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
    lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
    lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

    pad2->cd();
    pad2->Clear();
    TH1D* Cut3Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
    Cut3Pull->SetStats(0);
    Cut3Pull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
    Cut3Pull->GetXaxis()->SetTitleSize(20);
    Cut3Pull->GetXaxis()->SetTitleFont(43);
    Cut3Pull->GetXaxis()->SetTitleOffset(4);
    Cut3Pull->GetXaxis()->SetLabelSize(0.1);
    Cut3Pull->GetYaxis()->SetTitle("Pull");
    Cut3Pull->GetYaxis()->CenterTitle(true);
    Cut3Pull->GetXaxis()->CenterTitle(true);
    Cut3Pull->GetYaxis()->SetTitleSize(20);
    Cut3Pull->GetYaxis()->SetTitleFont(43);
    Cut3Pull->GetYaxis()->SetLabelSize(0.1);
    Cut3Pull->SetFillColor(kBlue);
    Cut3Pull->SetLineColor(kBlue);
    Cut3Pull->SetBit(TH1::kNoTitle);

    for (Int_t i=1;i<260;i++) {
    Double_t x = Cut3->GetBinCenter(i);
    Double_t val = Cut3Fit->Eval(x);
    Double_t sigma = sqrt(val);
    Double_t pull = (Cut3->GetBinContent(i)-val)/sigma;
    Cut3Pull->SetBinContent(i,pull);
    }
    Cut3Pull->Draw();

    c1->SaveAs("LcMCut3.pdf");

    TF1 *Cut4Fit = new TF1("Cut4Fit",DoubleGaussQuadNew,2222, 2352,8);
    Cut4Fit->SetParameter(0, 0.4);
    Cut4Fit->SetParLimits(0, 0.01, 0.99);
    Cut4Fit->SetParameter(1, 10000);
    Cut4Fit->SetParameter(2, 2287.);
    Cut4Fit->SetParameter(3, 4);
    Cut4Fit->SetParameter(4, 7);
    Cut4Fit->SetParLimits(3, 0, 15);
    Cut4Fit->SetParLimits(4, 0, 15);
    Cut4Fit->SetParameter(5, 100);
    Cut4Fit->SetParameter(6, 0.001);

    pad1->cd();
    pad1->Clear();
    Cut4->SetMinimum(0.0001);
    Cut4->SetLineWidth(2);
    Cut4->GetXaxis()->CenterTitle(true);
    Cut4->GetXaxis()->SetTitleSize(20);
    Cut4->GetXaxis()->SetTitleFont(43);
    Cut4->GetXaxis()->SetTitleOffset(1.5);
    Cut4->GetXaxis()->SetLabelSize(0.05);
    Cut4->GetYaxis()->SetTitleSize(20);
    Cut4->GetYaxis()->SetTitleFont(43);
    Cut4->GetYaxis()->SetLabelSize(0.05);
    Cut4->Fit("Cut4Fit", "E");

    SignalDGH.Form("%5.0f\n", Cut4Fit->GetParameter(1));
    SignalErDGH.Form("%5.0f\n", Cut4Fit->GetParError(1));
    FractionDGH.Form("%5.3f\n", Cut4Fit->GetParameter(0));
    FractionErDGH.Form("%5.3f\n", Cut4Fit->GetParError(0));
    muDGH.Form("%5.3f\n", Cut4Fit->GetParameter(2));
    muErDGH.Form("%5.3f\n", Cut4Fit->GetParError(2));
    sigma1DGH.Form("%5.3f\n", Cut4Fit->GetParameter(3));
    sigma1ErDGH.Form("%5.3f\n", Cut4Fit->GetParError(3));
    rmsDGH.Form("%5.3f\n", Cut4Fit->GetParameter(4));
    rmsErDGH.Form("%5.3f\n", Cut4Fit->GetParError(4));

    lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
    lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
    lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
    lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

    pad2->cd();
    pad2->Clear();
    TH1D* Cut4Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
    Cut4Pull->SetStats(0);
    Cut4Pull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
    Cut4Pull->GetXaxis()->SetTitleSize(20);
    Cut4Pull->GetXaxis()->SetTitleFont(43);
    Cut4Pull->GetXaxis()->SetTitleOffset(4);
    Cut4Pull->GetXaxis()->SetLabelSize(0.1);
    Cut4Pull->GetYaxis()->SetTitle("Pull");
    Cut4Pull->GetYaxis()->CenterTitle(true);
    Cut4Pull->GetXaxis()->CenterTitle(true);
    Cut4Pull->GetYaxis()->SetTitleSize(20);
    Cut4Pull->GetYaxis()->SetTitleFont(43);
    Cut4Pull->GetYaxis()->SetLabelSize(0.1);
    Cut4Pull->SetFillColor(kBlue);
    Cut4Pull->SetLineColor(kBlue);
    Cut4Pull->SetBit(TH1::kNoTitle);

    for (Int_t i=1;i<260;i++) {
    Double_t x = Cut4->GetBinCenter(i);
    Double_t val = Cut4Fit->Eval(x);
    Double_t sigma = sqrt(val);
    Double_t pull = (Cut4->GetBinContent(i)-val)/sigma;
    Cut4Pull->SetBinContent(i,pull);
    }
    Cut4Pull->Draw();

    c1->SaveAs("LcMCut4.pdf");

    TF1 *Cut5Fit = new TF1("Cut5Fit",DoubleGaussQuadNew,2222, 2352,8);
    Cut5Fit->SetParameter(0, 0.4);
    Cut5Fit->SetParLimits(0, 0.01, 0.99);
    Cut5Fit->SetParameter(1, 10000);
    Cut5Fit->SetParameter(2, 2287.);
    Cut5Fit->SetParameter(3, 4);
    Cut5Fit->SetParameter(4, 7);
    Cut5Fit->SetParLimits(3, 0, 15);
    Cut5Fit->SetParLimits(4, 0, 15);
    Cut5Fit->SetParameter(5, 100);
    Cut5Fit->SetParameter(6, 0.001);

    pad1->cd();
    pad1->Clear();
    Cut5->SetMinimum(0.0001);
    Cut5->SetLineWidth(2);
    Cut5->GetXaxis()->CenterTitle(true);
    Cut5->GetXaxis()->SetTitleSize(20);
    Cut5->GetXaxis()->SetTitleFont(43);
    Cut5->GetXaxis()->SetTitleOffset(1.5);
    Cut5->GetXaxis()->SetLabelSize(0.05);
    Cut5->GetYaxis()->SetTitleSize(20);
    Cut5->GetYaxis()->SetTitleFont(43);
    Cut5->GetYaxis()->SetLabelSize(0.05);
    Cut5->Fit("Cut5Fit", "E");

    SignalDGH.Form("%5.0f\n", Cut5Fit->GetParameter(1));
    SignalErDGH.Form("%5.0f\n", Cut5Fit->GetParError(1));
    FractionDGH.Form("%5.3f\n", Cut5Fit->GetParameter(0));
    FractionErDGH.Form("%5.3f\n", Cut5Fit->GetParError(0));
    muDGH.Form("%5.3f\n", Cut5Fit->GetParameter(2));
    muErDGH.Form("%5.3f\n", Cut5Fit->GetParError(2));
    sigma1DGH.Form("%5.3f\n", Cut5Fit->GetParameter(3));
    sigma1ErDGH.Form("%5.3f\n", Cut5Fit->GetParError(3));
    rmsDGH.Form("%5.3f\n", Cut5Fit->GetParameter(4));
    rmsErDGH.Form("%5.3f\n", Cut5Fit->GetParError(4));

    lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
    lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
    lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
    lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

    pad2->cd();
    pad2->Clear();
    TH1D* Cut5Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
    Cut5Pull->SetStats(0);
    Cut5Pull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
    Cut5Pull->GetXaxis()->SetTitleSize(20);
    Cut5Pull->GetXaxis()->SetTitleFont(43);
    Cut5Pull->GetXaxis()->SetTitleOffset(4);
    Cut5Pull->GetXaxis()->SetLabelSize(0.1);
    Cut5Pull->GetYaxis()->SetTitle("Pull");
    Cut5Pull->GetYaxis()->CenterTitle(true);
    Cut5Pull->GetXaxis()->CenterTitle(true);
    Cut5Pull->GetYaxis()->SetTitleSize(20);
    Cut5Pull->GetYaxis()->SetTitleFont(43);
    Cut5Pull->GetYaxis()->SetLabelSize(0.1);
    Cut5Pull->SetFillColor(kBlue);
    Cut5Pull->SetLineColor(kBlue);
    Cut5Pull->SetBit(TH1::kNoTitle);

    for (Int_t i=1;i<260;i++) {
    Double_t x = Cut5->GetBinCenter(i);
    Double_t val = Cut5Fit->Eval(x);
    Double_t sigma = sqrt(val);
    Double_t pull = (Cut5->GetBinContent(i)-val)/sigma;
    Cut5Pull->SetBinContent(i,pull);
    }
    Cut5Pull->Draw();

    c1->SaveAs("LcMCut5.pdf");

    TF1 *Cut6Fit = new TF1("Cut6Fit",DoubleGaussQuadNew,2222, 2352,8);
    Cut6Fit->SetParameter(0, 0.4);
    Cut6Fit->SetParLimits(0, 0.01, 0.99);
    Cut6Fit->SetParameter(1, 10000);
    Cut6Fit->SetParameter(2, 2287.);
    Cut6Fit->SetParameter(3, 4);
    Cut6Fit->SetParameter(4, 7);
    Cut6Fit->SetParLimits(3, 0, 15);
    Cut6Fit->SetParLimits(4, 0, 15);
    Cut6Fit->SetParameter(5, 100);
    Cut6Fit->SetParameter(6, 0.001);

    pad1->cd();
    pad1->Clear();
    Cut6->SetMinimum(0.0001);
    Cut6->SetLineWidth(2);
    Cut6->GetXaxis()->CenterTitle(true);
    Cut6->GetXaxis()->SetTitleSize(20);
    Cut6->GetXaxis()->SetTitleFont(43);
    Cut6->GetXaxis()->SetTitleOffset(1.5);
    Cut6->GetXaxis()->SetLabelSize(0.05);
    Cut6->GetYaxis()->SetTitleSize(20);
    Cut6->GetYaxis()->SetTitleFont(43);
    Cut6->GetYaxis()->SetLabelSize(0.05);
    Cut6->Fit("Cut6Fit", "E");

    SignalDGH.Form("%5.0f\n", Cut6Fit->GetParameter(1));
    SignalErDGH.Form("%5.0f\n", Cut6Fit->GetParError(1));
    FractionDGH.Form("%5.3f\n", Cut6Fit->GetParameter(0));
    FractionErDGH.Form("%5.3f\n", Cut6Fit->GetParError(0));
    muDGH.Form("%5.3f\n", Cut6Fit->GetParameter(2));
    muErDGH.Form("%5.3f\n", Cut6Fit->GetParError(2));
    sigma1DGH.Form("%5.3f\n", Cut6Fit->GetParameter(3));
    sigma1ErDGH.Form("%5.3f\n", Cut6Fit->GetParError(3));
    rmsDGH.Form("%5.3f\n", Cut6Fit->GetParameter(4));
    rmsErDGH.Form("%5.3f\n", Cut6Fit->GetParError(4));

    lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
    lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
    lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
    lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

    pad2->cd();
    pad2->Clear();
    TH1D* Cut6Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
    Cut6Pull->SetStats(0);
    Cut6Pull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
    Cut6Pull->GetXaxis()->SetTitleSize(20);
    Cut6Pull->GetXaxis()->SetTitleFont(43);
    Cut6Pull->GetXaxis()->SetTitleOffset(4);
    Cut6Pull->GetXaxis()->SetLabelSize(0.1);
    Cut6Pull->GetYaxis()->SetTitle("Pull");
    Cut6Pull->GetYaxis()->CenterTitle(true);
    Cut6Pull->GetXaxis()->CenterTitle(true);
    Cut6Pull->GetYaxis()->SetTitleSize(20);
    Cut6Pull->GetYaxis()->SetTitleFont(43);
    Cut6Pull->GetYaxis()->SetLabelSize(0.1);
    Cut6Pull->SetFillColor(kBlue);
    Cut6Pull->SetLineColor(kBlue);
    Cut6Pull->SetBit(TH1::kNoTitle);

    for (Int_t i=1;i<260;i++) {
    Double_t x = Cut6->GetBinCenter(i);
    Double_t val = Cut6Fit->Eval(x);
    Double_t sigma = sqrt(val);
    Double_t pull = (Cut6->GetBinContent(i)-val)/sigma;
    Cut6Pull->SetBinContent(i,pull);
    }
    Cut6Pull->Draw();

    c1->SaveAs("LcMCut6.pdf");
}
