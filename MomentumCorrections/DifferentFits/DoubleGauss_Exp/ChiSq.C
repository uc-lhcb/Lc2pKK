#define ChiSq_cxx
#include "ChiSq.h"


#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

#include "DoubleGaussExpHalf.C"

TFile * MassHistograms;
TH1D * FinalMass;
TH1D * PolarityMagUp;
TH1D * PolarityMagDown;
TH1D * Particle;
TH1D * AntiParticle;
TH1D * LcP1;
TH1D * LcP2;
TH1D * LcP3;
TH1D * LcP4;
TH1D * LcTau1;
TH1D * LcTau2;
TH1D * LcTau3;

TGraphErrors * gPolarity = nullptr;
TGraphErrors * gCharge = nullptr;
TGraphErrors * gLcP = nullptr;
TGraphErrors * gLcTau = nullptr;

TCanvas * c1 = nullptr;
TCanvas * grid = nullptr;


void ChiSq::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void ChiSq::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

   MassHistograms = new TFile("LcMass.root");
   FinalMass = (TH1D*) MassHistograms->Get("Lc_M");
   PolarityMagUp = (TH1D*) MassHistograms->Get("Lc_M_MagUp");
   PolarityMagDown = (TH1D*) MassHistograms->Get("Lc_M_MagDown");
   Particle = (TH1D*) MassHistograms->Get("Lc_M_Particle");
   AntiParticle = (TH1D*) MassHistograms->Get("Lc_M_AntiParticle");
   LcP1 = (TH1D*) MassHistograms->Get("Lc_M_LcP1");
   LcP2 = (TH1D*) MassHistograms->Get("Lc_M_LcP2");
   LcP3 = (TH1D*) MassHistograms->Get("Lc_M_LcP3");
   LcP4 = (TH1D*) MassHistograms->Get("Lc_M_LcP4");
   LcTau1 = (TH1D*) MassHistograms->Get("Lc_M_LcTau1");
   LcTau2 = (TH1D*) MassHistograms->Get("Lc_M_LcTau2");
   LcTau3 = (TH1D*) MassHistograms->Get("Lc_M_LcTau3");

      c1 = new TCanvas("canvas", "Test Canvas");
      grid = new TCanvas("grid", "Grid Canvas");
}

Bool_t ChiSq::Process(Long64_t entry)
{
   fReader.SetLocalEntry(entry);

   return kTRUE;
}

void ChiSq::SlaveTerminate()
{
}

void ChiSq::Terminate()
{

      TString MassAVGPolarity;
      TString MassAVGCharge;
      TString MassAVGLcP;
      TString MassAVGLcTau;
        gStyle->SetOptStat(11);
        gStyle->SetStatW(0.25);
        gStyle->SetStatH(0.25);

        auto lt = new TLatex();
        lt->SetTextSize(0.048);

    FinalMass->SetLineWidth(2);
    PolarityMagUp->SetLineWidth(2);
    PolarityMagDown->SetLineWidth(2);
    Particle->SetLineWidth(2);
    AntiParticle->SetLineWidth(2);
    LcP1->SetLineWidth(2);
    LcP2->SetLineWidth(2);
    LcP3->SetLineWidth(2);
    LcP4->SetLineWidth(2);
    LcTau1->SetLineWidth(2);
    LcTau2->SetLineWidth(2);
    LcTau3->SetLineWidth(2);

      c1->cd();
      FinalMass->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
      PolarityMagUp->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
      PolarityMagDown->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
      Particle->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
      AntiParticle->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
      LcP1->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
      LcP2->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
      LcP3->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
      LcP4->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
      LcTau1->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
      LcTau2->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
      LcTau3->GetYaxis()->SetTitle("Entries / (0.5 MeV)");

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


        TF1 *FinalFit = new TF1("FinalFit",DoubleGaussExp,2222, 2352,7);
        FinalFit->SetParameter(0, 0.4);
        FinalFit->SetParLimits(0, 0.01, 0.99);
        FinalFit->SetParameter(1, 100000);
        FinalFit->SetParameter(2, 2287.);
        FinalFit->SetParameter(3, 4);
        FinalFit->SetParameter(4, 7);
        FinalFit->SetParLimits(3, 0, 15);
        FinalFit->SetParLimits(4, 0, 15);
        FinalFit->SetParameter(5, 10);
        FinalFit->SetParameter(6, -0.002);

        pad1->cd();
        pad1->Clear();
        FinalMass->SetMinimum(0.0001);
        FinalMass->SetLineWidth(2);
        FinalMass->GetXaxis()->CenterTitle(true);
        FinalMass->GetXaxis()->SetTitleSize(20);
        FinalMass->GetXaxis()->SetTitleFont(43);
        FinalMass->GetXaxis()->SetTitleOffset(1.5);
        FinalMass->GetXaxis()->SetLabelSize(0.05);
        FinalMass->GetYaxis()->SetTitleSize(20);
        FinalMass->GetYaxis()->SetTitleFont(43);
        FinalMass->GetYaxis()->SetLabelSize(0.05);
        FinalMass->Fit("FinalFit", "E");

        TString SignalDGH;
        TString SignalErDGH;
        SignalDGH.Form("%5.0f\n", FinalFit->GetParameter(1));
        SignalErDGH.Form("%5.0f\n", FinalFit->GetParError(1));
        TString FractionDGH;
        TString FractionErDGH;
        FractionDGH.Form("%5.3f\n", FinalFit->GetParameter(0));
        FractionErDGH.Form("%5.3f\n", FinalFit->GetParError(0));
        TString muDGH;
        TString muErDGH;
        muDGH.Form("%5.3f\n", FinalFit->GetParameter(2));
        muErDGH.Form("%5.3f\n", FinalFit->GetParError(2));
        TString sigma1DGH;
        TString sigma1ErDGH;
        sigma1DGH.Form("%5.3f\n", FinalFit->GetParameter(3));
        sigma1ErDGH.Form("%5.3f\n", FinalFit->GetParError(3));
        TString rmsDGH;
        TString rmsErDGH;
        rmsDGH.Form("%5.3f\n", FinalFit->GetParameter(4));
        rmsErDGH.Form("%5.3f\n", FinalFit->GetParError(4));

        lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
        lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
        lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
        lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
        lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
        lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

        pad2->cd();
        pad2->Clear();
        TH1D* FinalPull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
        FinalPull->SetStats(0);
        FinalPull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
        FinalPull->GetXaxis()->SetTitleSize(20);
        FinalPull->GetXaxis()->SetTitleFont(43);
        FinalPull->GetXaxis()->SetTitleOffset(4);
        FinalPull->GetXaxis()->SetLabelSize(0.1);
        FinalPull->GetYaxis()->SetTitle("Pull");
        FinalPull->GetYaxis()->CenterTitle(true);
        FinalPull->GetXaxis()->CenterTitle(true);
        FinalPull->GetYaxis()->SetTitleSize(20);
        FinalPull->GetYaxis()->SetTitleFont(43);
        FinalPull->GetYaxis()->SetLabelSize(0.1);
        FinalPull->SetFillColor(kBlue);
        FinalPull->SetLineColor(kBlue);
        FinalPull->SetBit(TH1::kNoTitle);

        for (Int_t i=1;i<260;i++) {
        Double_t x = FinalMass->GetBinCenter(i);
        Double_t val = FinalFit->Eval(x);
        Double_t sigma = sqrt(val);
        Double_t pull = (FinalMass->GetBinContent(i)-val)/sigma;
        FinalPull->SetBinContent(i,pull);
          }
        FinalPull->Draw();

        c1->SaveAs("LcMFinal.pdf");

      TF1 *MagUpFit = new TF1("MagUpFit",DoubleGaussExp,2222, 2352,7);
      MagUpFit->SetParameter(0, 0.4);
      MagUpFit->SetParLimits(0, 0.01, 0.99);
      MagUpFit->SetParameter(1, 10000);
      MagUpFit->SetParameter(2, 2287.);
      MagUpFit->SetParameter(3, 4);
      MagUpFit->SetParameter(4, 7);
      MagUpFit->SetParLimits(3, 0, 15);
      MagUpFit->SetParLimits(4, 0, 15);
      MagUpFit->SetParameter(5, 10);
      MagUpFit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      PolarityMagUp->SetMinimum(0.0001);
      PolarityMagUp->SetLineWidth(2);
      PolarityMagUp->GetXaxis()->CenterTitle(true);
      PolarityMagUp->GetXaxis()->SetTitleSize(20);
      PolarityMagUp->GetXaxis()->SetTitleFont(43);
      PolarityMagUp->GetXaxis()->SetTitleOffset(1.5);
      PolarityMagUp->GetXaxis()->SetLabelSize(0.05);
      PolarityMagUp->GetYaxis()->SetTitleSize(20);
      PolarityMagUp->GetYaxis()->SetTitleFont(43);
      PolarityMagUp->GetYaxis()->SetLabelSize(0.05);
      PolarityMagUp->Fit("MagUpFit", "E");

      SignalDGH.Form("%5.0f\n", MagUpFit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", MagUpFit->GetParError(1));
      FractionDGH.Form("%5.3f\n", MagUpFit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", MagUpFit->GetParError(0));
      muDGH.Form("%5.3f\n", MagUpFit->GetParameter(2));
      muErDGH.Form("%5.3f\n", MagUpFit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", MagUpFit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", MagUpFit->GetParError(3));
      rmsDGH.Form("%5.3f\n", MagUpFit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", MagUpFit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* MagUpPull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      MagUpPull->SetStats(0);
      MagUpPull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
      MagUpPull->GetXaxis()->SetTitleSize(20);
      MagUpPull->GetXaxis()->SetTitleFont(43);
      MagUpPull->GetXaxis()->SetTitleOffset(4);
      MagUpPull->GetXaxis()->SetLabelSize(0.1);
      MagUpPull->GetYaxis()->SetTitle("Pull");
      MagUpPull->GetYaxis()->CenterTitle(true);
      MagUpPull->GetXaxis()->CenterTitle(true);
      MagUpPull->GetYaxis()->SetTitleSize(20);
      MagUpPull->GetYaxis()->SetTitleFont(43);
      MagUpPull->GetYaxis()->SetLabelSize(0.1);
      MagUpPull->SetFillColor(kBlue);
      MagUpPull->SetLineColor(kBlue);
      MagUpPull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = PolarityMagUp->GetBinCenter(i);
      Double_t val = MagUpFit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (PolarityMagUp->GetBinContent(i)-val)/sigma;
      MagUpPull->SetBinContent(i,pull);
        }
      MagUpPull->Draw();

      c1->SaveAs("LcMMagUp.pdf");


          TF1 *MagDownFit = new TF1("MagDownFit",DoubleGaussExp,2222, 2352,7);
          MagDownFit->SetParameter(0, 0.4);
          MagDownFit->SetParLimits(0, 0.01, 0.99);
          MagDownFit->SetParameter(1, 10000);
          MagDownFit->SetParameter(2, 2287.);
          MagDownFit->SetParameter(3, 4);
          MagDownFit->SetParameter(4, 7);
          MagDownFit->SetParLimits(3, 0, 15);
          MagDownFit->SetParLimits(4, 0, 15);
          MagDownFit->SetParameter(5, 10);
          MagDownFit->SetParameter(6, -0.002);

          pad1->cd();
          pad1->Clear();
          PolarityMagDown->SetMinimum(0.0001);
          PolarityMagDown->SetLineWidth(2);
          PolarityMagDown->GetXaxis()->CenterTitle(true);
          PolarityMagDown->GetXaxis()->SetTitleSize(20);
          PolarityMagDown->GetXaxis()->SetTitleFont(43);
          PolarityMagDown->GetXaxis()->SetTitleOffset(1.5);
          PolarityMagDown->GetXaxis()->SetLabelSize(0.05);
          PolarityMagDown->GetYaxis()->SetTitleSize(20);
          PolarityMagDown->GetYaxis()->SetTitleFont(43);
          PolarityMagDown->GetYaxis()->SetLabelSize(0.05);
          PolarityMagDown->Fit("MagDownFit", "E");

          SignalDGH.Form("%5.0f\n", MagDownFit->GetParameter(1));
          SignalErDGH.Form("%5.0f\n", MagDownFit->GetParError(1));
          FractionDGH.Form("%5.3f\n", MagDownFit->GetParameter(0));
          FractionErDGH.Form("%5.3f\n", MagDownFit->GetParError(0));
          muDGH.Form("%5.3f\n", MagDownFit->GetParameter(2));
          muErDGH.Form("%5.3f\n", MagDownFit->GetParError(2));
          sigma1DGH.Form("%5.3f\n", MagDownFit->GetParameter(3));
          sigma1ErDGH.Form("%5.3f\n", MagDownFit->GetParError(3));
          rmsDGH.Form("%5.3f\n", MagDownFit->GetParameter(4));
          rmsErDGH.Form("%5.3f\n", MagDownFit->GetParError(4));

          lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
          lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
          lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
          lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
          lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
          lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

          pad2->cd();
          pad2->Clear();
          TH1D* MagDownPull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
          MagDownPull->SetStats(0);
          MagDownPull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
          MagDownPull->GetXaxis()->SetTitleSize(20);
          MagDownPull->GetXaxis()->SetTitleFont(43);
          MagDownPull->GetXaxis()->SetTitleOffset(4);
          MagDownPull->GetXaxis()->SetLabelSize(0.1);
          MagDownPull->GetYaxis()->SetTitle("Pull");
          MagDownPull->GetYaxis()->CenterTitle(true);
          MagDownPull->GetXaxis()->CenterTitle(true);
          MagDownPull->GetYaxis()->SetTitleSize(20);
          MagDownPull->GetYaxis()->SetTitleFont(43);
          MagDownPull->GetYaxis()->SetLabelSize(0.1);
          MagDownPull->SetFillColor(kBlue);
          MagDownPull->SetLineColor(kBlue);
          MagDownPull->SetBit(TH1::kNoTitle);

          for (Int_t i=1;i<260;i++) {
          Double_t x = PolarityMagDown->GetBinCenter(i);
          Double_t val = MagDownFit->Eval(x);
          Double_t sigma = sqrt(val);
          Double_t pull = (PolarityMagDown->GetBinContent(i)-val)/sigma;
          MagDownPull->SetBinContent(i,pull);
  }
          MagDownPull->Draw();

          c1->SaveAs("LcMMagDown.pdf");


    TF1 *ParticleFit = new TF1("ParticleFit",DoubleGaussExp,2222, 2352,7);
    ParticleFit->SetParameter(0, 0.4);
    ParticleFit->SetParLimits(0, 0.01, 0.99);
    ParticleFit->SetParameter(1, 10000);
    ParticleFit->SetParameter(2, 2287.);
    ParticleFit->SetParameter(3, 4);
    ParticleFit->SetParameter(4, 7);
    ParticleFit->SetParLimits(3, 0, 15);
    ParticleFit->SetParLimits(4, 0, 15);
    ParticleFit->SetParameter(5, 10);
    ParticleFit->SetParameter(6, -0.002);

    pad1->cd();
    pad1->Clear();
    Particle->SetMinimum(0.0001);
    Particle->SetLineWidth(2);
    Particle->GetXaxis()->CenterTitle(true);
    Particle->GetXaxis()->SetTitleSize(20);
    Particle->GetXaxis()->SetTitleFont(43);
    Particle->GetXaxis()->SetTitleOffset(1.5);
    Particle->GetXaxis()->SetLabelSize(0.05);
    Particle->GetYaxis()->SetTitleSize(20);
    Particle->GetYaxis()->SetTitleFont(43);
    Particle->GetYaxis()->SetLabelSize(0.05);
    Particle->Fit("ParticleFit", "E");

    SignalDGH.Form("%5.0f\n", ParticleFit->GetParameter(1));
    SignalErDGH.Form("%5.0f\n", ParticleFit->GetParError(1));
    FractionDGH.Form("%5.3f\n", ParticleFit->GetParameter(0));
    FractionErDGH.Form("%5.3f\n", ParticleFit->GetParError(0));
    muDGH.Form("%5.3f\n", ParticleFit->GetParameter(2));
    muErDGH.Form("%5.3f\n", ParticleFit->GetParError(2));
    sigma1DGH.Form("%5.3f\n", ParticleFit->GetParameter(3));
    sigma1ErDGH.Form("%5.3f\n", ParticleFit->GetParError(3));
    rmsDGH.Form("%5.3f\n", ParticleFit->GetParameter(4));
    rmsErDGH.Form("%5.3f\n", ParticleFit->GetParError(4));

    lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
    lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
    lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
    lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

    pad2->cd();
    pad2->Clear();
    TH1D* ParticlePull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
    ParticlePull->SetStats(0);
    ParticlePull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
    ParticlePull->GetXaxis()->SetTitleSize(20);
    ParticlePull->GetXaxis()->SetTitleFont(43);
    ParticlePull->GetXaxis()->SetTitleOffset(4);
    ParticlePull->GetXaxis()->SetLabelSize(0.1);
    ParticlePull->GetYaxis()->SetTitle("Pull");
    ParticlePull->GetYaxis()->CenterTitle(true);
    ParticlePull->GetXaxis()->CenterTitle(true);
    ParticlePull->GetYaxis()->SetTitleSize(20);
    ParticlePull->GetYaxis()->SetTitleFont(43);
    ParticlePull->GetYaxis()->SetLabelSize(0.1);
    ParticlePull->SetFillColor(kBlue);
    ParticlePull->SetLineColor(kBlue);
    ParticlePull->SetBit(TH1::kNoTitle);

    for (Int_t i=1;i<260;i++) {
    Double_t x = Particle->GetBinCenter(i);
    Double_t val = ParticleFit->Eval(x);
    Double_t sigma = sqrt(val);
    Double_t pull = (Particle->GetBinContent(i)-val)/sigma;
    ParticlePull->SetBinContent(i,pull);
      }
    ParticlePull->Draw();

    c1->SaveAs("LcMParticle.pdf");


        TF1 *AntiParticleFit = new TF1("AntiParticleFit",DoubleGaussExp,2222, 2352,7);
        AntiParticleFit->SetParameter(0, 0.4);
        AntiParticleFit->SetParLimits(0, 0.01, 0.99);
        AntiParticleFit->SetParameter(1, 10000);
        AntiParticleFit->SetParameter(2, 2287.);
        AntiParticleFit->SetParameter(3, 4);
        AntiParticleFit->SetParameter(4, 7);
        AntiParticleFit->SetParLimits(3, 0, 15);
        AntiParticleFit->SetParLimits(4, 0, 15);
        AntiParticleFit->SetParameter(5, 10);
        AntiParticleFit->SetParameter(6, -0.002);

        pad1->cd();
        pad1->Clear();
        AntiParticle->SetMinimum(0.0001);
        AntiParticle->SetLineWidth(2);
        AntiParticle->GetXaxis()->CenterTitle(true);
        AntiParticle->GetXaxis()->SetTitleSize(20);
        AntiParticle->GetXaxis()->SetTitleFont(43);
        AntiParticle->GetXaxis()->SetTitleOffset(1.5);
        AntiParticle->GetXaxis()->SetLabelSize(0.05);
        AntiParticle->GetYaxis()->SetTitleSize(20);
        AntiParticle->GetYaxis()->SetTitleFont(43);
        AntiParticle->GetYaxis()->SetLabelSize(0.05);
        AntiParticle->Fit("AntiParticleFit", "E");

        SignalDGH.Form("%5.0f\n", AntiParticleFit->GetParameter(1));
        SignalErDGH.Form("%5.0f\n", AntiParticleFit->GetParError(1));
        FractionDGH.Form("%5.3f\n", AntiParticleFit->GetParameter(0));
        FractionErDGH.Form("%5.3f\n", AntiParticleFit->GetParError(0));
        muDGH.Form("%5.3f\n", AntiParticleFit->GetParameter(2));
        muErDGH.Form("%5.3f\n", AntiParticleFit->GetParError(2));
        sigma1DGH.Form("%5.3f\n", AntiParticleFit->GetParameter(3));
        sigma1ErDGH.Form("%5.3f\n", AntiParticleFit->GetParError(3));
        rmsDGH.Form("%5.3f\n", AntiParticleFit->GetParameter(4));
        rmsErDGH.Form("%5.3f\n", AntiParticleFit->GetParError(4));

        lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
        lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
        lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
        lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
        lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
        lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

        pad2->cd();
        pad2->Clear();
        TH1D* AntiParticlePull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
        AntiParticlePull->SetStats(0);
        AntiParticlePull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
        AntiParticlePull->GetXaxis()->SetTitleSize(20);
        AntiParticlePull->GetXaxis()->SetTitleFont(43);
        AntiParticlePull->GetXaxis()->SetTitleOffset(4);
        AntiParticlePull->GetXaxis()->SetLabelSize(0.1);
        AntiParticlePull->GetYaxis()->SetTitle("Pull");
        AntiParticlePull->GetYaxis()->CenterTitle(true);
        AntiParticlePull->GetXaxis()->CenterTitle(true);
        AntiParticlePull->GetYaxis()->SetTitleSize(20);
        AntiParticlePull->GetYaxis()->SetTitleFont(43);
        AntiParticlePull->GetYaxis()->SetLabelSize(0.1);
        AntiParticlePull->SetFillColor(kBlue);
        AntiParticlePull->SetLineColor(kBlue);
        AntiParticlePull->SetBit(TH1::kNoTitle);

        for (Int_t i=1;i<260;i++) {
        Double_t x = AntiParticle->GetBinCenter(i);
        Double_t val = AntiParticleFit->Eval(x);
        Double_t sigma = sqrt(val);
        Double_t pull = (AntiParticle->GetBinContent(i)-val)/sigma;
        AntiParticlePull->SetBinContent(i,pull);
          }
        AntiParticlePull->Draw();

        c1->SaveAs("LcMAntiParticle.pdf");


  TF1 *LcP1Fit = new TF1("LcP1Fit",DoubleGaussExp,2222, 2352,7);
  LcP1Fit->SetParameter(0, 0.4);
  LcP1Fit->SetParLimits(0, 0.01, 0.99);
  LcP1Fit->SetParameter(1, 10000);
  LcP1Fit->SetParameter(2, 2287.);
  LcP1Fit->SetParameter(3, 4);
  LcP1Fit->SetParameter(4, 7);
  LcP1Fit->SetParLimits(3, 0, 15);
  LcP1Fit->SetParLimits(4, 0, 15);
  LcP1Fit->SetParameter(5, 10);
  LcP1Fit->SetParameter(6, -0.002);

  pad1->cd();
  pad1->Clear();
  LcP1->SetMinimum(0.0001);
  LcP1->SetLineWidth(2);
  LcP1->GetXaxis()->CenterTitle(true);
  LcP1->GetXaxis()->SetTitleSize(20);
  LcP1->GetXaxis()->SetTitleFont(43);
  LcP1->GetXaxis()->SetTitleOffset(1.5);
  LcP1->GetXaxis()->SetLabelSize(0.05);
  LcP1->GetYaxis()->SetTitleSize(20);
  LcP1->GetYaxis()->SetTitleFont(43);
  LcP1->GetYaxis()->SetLabelSize(0.05);
  LcP1->Fit("LcP1Fit", "E");

  SignalDGH.Form("%5.0f\n", LcP1Fit->GetParameter(1));
  SignalErDGH.Form("%5.0f\n", LcP1Fit->GetParError(1));
  FractionDGH.Form("%5.3f\n", LcP1Fit->GetParameter(0));
  FractionErDGH.Form("%5.3f\n", LcP1Fit->GetParError(0));
  muDGH.Form("%5.3f\n", LcP1Fit->GetParameter(2));
  muErDGH.Form("%5.3f\n", LcP1Fit->GetParError(2));
  sigma1DGH.Form("%5.3f\n", LcP1Fit->GetParameter(3));
  sigma1ErDGH.Form("%5.3f\n", LcP1Fit->GetParError(3));
  rmsDGH.Form("%5.3f\n", LcP1Fit->GetParameter(4));
  rmsErDGH.Form("%5.3f\n", LcP1Fit->GetParError(4));

  lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
  lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
  lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
  lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
  lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
  lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

  pad2->cd();
  pad2->Clear();
  TH1D* LcP1Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
  LcP1Pull->SetStats(0);
  LcP1Pull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
  LcP1Pull->GetXaxis()->SetTitleSize(20);
  LcP1Pull->GetXaxis()->SetTitleFont(43);
  LcP1Pull->GetXaxis()->SetTitleOffset(4);
  LcP1Pull->GetXaxis()->SetLabelSize(0.1);
  LcP1Pull->GetYaxis()->SetTitle("Pull");
  LcP1Pull->GetYaxis()->CenterTitle(true);
  LcP1Pull->GetXaxis()->CenterTitle(true);
  LcP1Pull->GetYaxis()->SetTitleSize(20);
  LcP1Pull->GetYaxis()->SetTitleFont(43);
  LcP1Pull->GetYaxis()->SetLabelSize(0.1);
  LcP1Pull->SetFillColor(kBlue);
  LcP1Pull->SetLineColor(kBlue);
  LcP1Pull->SetBit(TH1::kNoTitle);

  for (Int_t i=1;i<260;i++) {
  Double_t x = LcP1->GetBinCenter(i);
  Double_t val = LcP1Fit->Eval(x);
  Double_t sigma = sqrt(val);
  Double_t pull = (LcP1->GetBinContent(i)-val)/sigma;
  LcP1Pull->SetBinContent(i,pull);
  }
  LcP1Pull->Draw();

  c1->SaveAs("LcMLcP1.pdf");


    TF1 *LcP2Fit = new TF1("LcP2Fit",DoubleGaussExp,2222, 2352,7);
    LcP2Fit->SetParameter(0, 0.4);
    LcP2Fit->SetParLimits(0, 0.01, 0.99);
    LcP2Fit->SetParameter(1, 10000);
    LcP2Fit->SetParameter(2, 2287.);
    LcP2Fit->SetParameter(3, 4);
    LcP2Fit->SetParameter(4, 7);
    LcP2Fit->SetParLimits(3, 0, 15);
    LcP2Fit->SetParLimits(4, 0, 15);
    LcP2Fit->SetParameter(5, 10);
    LcP2Fit->SetParameter(6, -0.002);

    pad1->cd();
    pad1->Clear();
    LcP2->SetMinimum(0.0001);
    LcP2->SetLineWidth(2);
    LcP2->GetXaxis()->CenterTitle(true);
    LcP2->GetXaxis()->SetTitleSize(20);
    LcP2->GetXaxis()->SetTitleFont(43);
    LcP2->GetXaxis()->SetTitleOffset(1.5);
    LcP2->GetXaxis()->SetLabelSize(0.05);
    LcP2->GetYaxis()->SetTitleSize(20);
    LcP2->GetYaxis()->SetTitleFont(43);
    LcP2->GetYaxis()->SetLabelSize(0.05);
    LcP2->Fit("LcP2Fit", "E");

    SignalDGH.Form("%5.0f\n", LcP2Fit->GetParameter(1));
    SignalErDGH.Form("%5.0f\n", LcP2Fit->GetParError(1));
    FractionDGH.Form("%5.3f\n", LcP2Fit->GetParameter(0));
    FractionErDGH.Form("%5.3f\n", LcP2Fit->GetParError(0));
    muDGH.Form("%5.3f\n", LcP2Fit->GetParameter(2));
    muErDGH.Form("%5.3f\n", LcP2Fit->GetParError(2));
    sigma1DGH.Form("%5.3f\n", LcP2Fit->GetParameter(3));
    sigma1ErDGH.Form("%5.3f\n", LcP2Fit->GetParError(3));
    rmsDGH.Form("%5.3f\n", LcP2Fit->GetParameter(4));
    rmsErDGH.Form("%5.3f\n", LcP2Fit->GetParError(4));

    lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
    lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
    lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
    lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

    pad2->cd();
    pad2->Clear();
    TH1D* LcP2Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
    LcP2Pull->SetStats(0);
    LcP2Pull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
    LcP2Pull->GetXaxis()->SetTitleSize(20);
    LcP2Pull->GetXaxis()->SetTitleFont(43);
    LcP2Pull->GetXaxis()->SetTitleOffset(4);
    LcP2Pull->GetXaxis()->SetLabelSize(0.1);
    LcP2Pull->GetYaxis()->SetTitle("Pull");
    LcP2Pull->GetYaxis()->CenterTitle(true);
    LcP2Pull->GetXaxis()->CenterTitle(true);
    LcP2Pull->GetYaxis()->SetTitleSize(20);
    LcP2Pull->GetYaxis()->SetTitleFont(43);
    LcP2Pull->GetYaxis()->SetLabelSize(0.1);
    LcP2Pull->SetFillColor(kBlue);
    LcP2Pull->SetLineColor(kBlue);
    LcP2Pull->SetBit(TH1::kNoTitle);

    for (Int_t i=1;i<260;i++) {
    Double_t x = LcP2->GetBinCenter(i);
    Double_t val = LcP2Fit->Eval(x);
    Double_t sigma = sqrt(val);
    Double_t pull = (LcP2->GetBinContent(i)-val)/sigma;
    LcP2Pull->SetBinContent(i,pull);
      }
    LcP2Pull->Draw();

    c1->SaveAs("LcMLcP2.pdf");

        TF1 *LcP3Fit = new TF1("LcP3Fit",DoubleGaussExp,2222, 2352,7);
        LcP3Fit->SetParameter(0, 0.4);
        LcP3Fit->SetParLimits(0, 0.01, 0.99);
        LcP3Fit->SetParameter(1, 10000);
        LcP3Fit->SetParameter(2, 2287.);
        LcP3Fit->SetParameter(3, 4);
        LcP3Fit->SetParameter(4, 7);
        LcP3Fit->SetParLimits(3, 0, 15);
        LcP3Fit->SetParLimits(4, 0, 15);
        LcP3Fit->SetParameter(5, 10);
        LcP3Fit->SetParameter(6, -0.002);

        pad1->cd();
        pad1->Clear();
        LcP3->SetMinimum(0.0001);
        LcP3->SetLineWidth(2);
        LcP3->GetXaxis()->CenterTitle(true);
        LcP3->GetXaxis()->SetTitleSize(20);
        LcP3->GetXaxis()->SetTitleFont(43);
        LcP3->GetXaxis()->SetTitleOffset(1.5);
        LcP3->GetXaxis()->SetLabelSize(0.05);
        LcP3->GetYaxis()->SetTitleSize(20);
        LcP3->GetYaxis()->SetTitleFont(43);
        LcP3->GetYaxis()->SetLabelSize(0.05);
        LcP3->Fit("LcP3Fit", "E");

        SignalDGH.Form("%5.0f\n", LcP3Fit->GetParameter(1));
        SignalErDGH.Form("%5.0f\n", LcP3Fit->GetParError(1));
        FractionDGH.Form("%5.3f\n", LcP3Fit->GetParameter(0));
        FractionErDGH.Form("%5.3f\n", LcP3Fit->GetParError(0));
        muDGH.Form("%5.3f\n", LcP3Fit->GetParameter(2));
        muErDGH.Form("%5.3f\n", LcP3Fit->GetParError(2));
        sigma1DGH.Form("%5.3f\n", LcP3Fit->GetParameter(3));
        sigma1ErDGH.Form("%5.3f\n", LcP3Fit->GetParError(3));
        rmsDGH.Form("%5.3f\n", LcP3Fit->GetParameter(4));
        rmsErDGH.Form("%5.3f\n", LcP3Fit->GetParError(4));

        lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
        lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
        lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
        lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
        lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
        lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

        pad2->cd();
        pad2->Clear();
        TH1D* LcP3Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
        LcP3Pull->SetStats(0);
        LcP3Pull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
        LcP3Pull->GetXaxis()->SetTitleSize(20);
        LcP3Pull->GetXaxis()->SetTitleFont(43);
        LcP3Pull->GetXaxis()->SetTitleOffset(4);
        LcP3Pull->GetXaxis()->SetLabelSize(0.1);
        LcP3Pull->GetYaxis()->SetTitle("Pull");
        LcP3Pull->GetYaxis()->CenterTitle(true);
        LcP3Pull->GetXaxis()->CenterTitle(true);
        LcP3Pull->GetYaxis()->SetTitleSize(20);
        LcP3Pull->GetYaxis()->SetTitleFont(43);
        LcP3Pull->GetYaxis()->SetLabelSize(0.1);
        LcP3Pull->SetFillColor(kBlue);
        LcP3Pull->SetLineColor(kBlue);
        LcP3Pull->SetBit(TH1::kNoTitle);

        for (Int_t i=1;i<260;i++) {
        Double_t x = LcP3->GetBinCenter(i);
        Double_t val = LcP3Fit->Eval(x);
        Double_t sigma = sqrt(val);
        Double_t pull = (LcP3->GetBinContent(i)-val)/sigma;
        LcP3Pull->SetBinContent(i,pull);
          }
        LcP3Pull->Draw();

        c1->SaveAs("LcMLcP3.pdf");


  TF1 *LcP4Fit = new TF1("LcP4Fit",DoubleGaussExp,2222, 2352,7);
  LcP4Fit->SetParameter(0, 0.4);
  LcP4Fit->SetParLimits(0, 0.01, 0.99);
  LcP4Fit->SetParameter(1, 10000);
  LcP4Fit->SetParameter(2, 2287.);
  LcP4Fit->SetParameter(3, 4);
  LcP4Fit->SetParameter(4, 7);
  LcP4Fit->SetParLimits(3, 0, 15);
  LcP4Fit->SetParLimits(4, 0, 15);
  LcP4Fit->SetParameter(5, 10);
  LcP4Fit->SetParameter(6, -0.002);

  pad1->cd();
  pad1->Clear();
  LcP4->SetMinimum(0.0001);
  LcP4->SetLineWidth(2);
  LcP4->GetXaxis()->CenterTitle(true);
  LcP4->GetXaxis()->SetTitleSize(20);
  LcP4->GetXaxis()->SetTitleFont(43);
  LcP4->GetXaxis()->SetTitleOffset(1.5);
  LcP4->GetXaxis()->SetLabelSize(0.05);
  LcP4->GetYaxis()->SetTitleSize(20);
  LcP4->GetYaxis()->SetTitleFont(43);
  LcP4->GetYaxis()->SetLabelSize(0.05);
  LcP4->Fit("LcP4Fit", "E");

  SignalDGH.Form("%5.0f\n", LcP4Fit->GetParameter(1));
  SignalErDGH.Form("%5.0f\n", LcP4Fit->GetParError(1));
  FractionDGH.Form("%5.3f\n", LcP4Fit->GetParameter(0));
  FractionErDGH.Form("%5.3f\n", LcP4Fit->GetParError(0));
  muDGH.Form("%5.3f\n", LcP4Fit->GetParameter(2));
  muErDGH.Form("%5.3f\n", LcP4Fit->GetParError(2));
  sigma1DGH.Form("%5.3f\n", LcP4Fit->GetParameter(3));
  sigma1ErDGH.Form("%5.3f\n", LcP4Fit->GetParError(3));
  rmsDGH.Form("%5.3f\n", LcP4Fit->GetParameter(4));
  rmsErDGH.Form("%5.3f\n", LcP4Fit->GetParError(4));

  lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
  lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
  lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
  lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
  lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
  lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

  pad2->cd();
  pad2->Clear();
  TH1D* LcP4Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
  LcP4Pull->SetStats(0);
  LcP4Pull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
  LcP4Pull->GetXaxis()->SetTitleSize(20);
  LcP4Pull->GetXaxis()->SetTitleFont(43);
  LcP4Pull->GetXaxis()->SetTitleOffset(4);
  LcP4Pull->GetXaxis()->SetLabelSize(0.1);
  LcP4Pull->GetYaxis()->SetTitle("Pull");
  LcP4Pull->GetYaxis()->CenterTitle(true);
  LcP4Pull->GetXaxis()->CenterTitle(true);
  LcP4Pull->GetYaxis()->SetTitleSize(20);
  LcP4Pull->GetYaxis()->SetTitleFont(43);
  LcP4Pull->GetYaxis()->SetLabelSize(0.1);
  LcP4Pull->SetFillColor(kBlue);
  LcP4Pull->SetLineColor(kBlue);
  LcP4Pull->SetBit(TH1::kNoTitle);

  for (Int_t i=1;i<260;i++) {
  Double_t x = LcP4->GetBinCenter(i);
  Double_t val = LcP4Fit->Eval(x);
  Double_t sigma = sqrt(val);
  Double_t pull = (LcP4->GetBinContent(i)-val)/sigma;
  LcP4Pull->SetBinContent(i,pull);
    }
  LcP4Pull->Draw();

  c1->SaveAs("LcMLcP4.pdf");


    TF1 *LcTau1Fit = new TF1("LcTau1Fit",DoubleGaussExp,2222, 2352,7);
    LcTau1Fit->SetParameter(0, 0.4);
    LcTau1Fit->SetParLimits(0, 0.01, 0.99);
    LcTau1Fit->SetParameter(1, 10000);
    LcTau1Fit->SetParameter(2, 2287.);
    LcTau1Fit->SetParameter(3, 4);
    LcTau1Fit->SetParameter(4, 7);
    LcTau1Fit->SetParLimits(3, 0, 15);
    LcTau1Fit->SetParLimits(4, 0, 15);
    LcTau1Fit->SetParameter(5, 10);
    LcTau1Fit->SetParameter(6, -0.002);

    pad1->cd();
    pad1->Clear();
    LcTau1->SetMinimum(0.0001);
    LcTau1->SetLineWidth(2);
    LcTau1->GetXaxis()->CenterTitle(true);
    LcTau1->GetXaxis()->SetTitleSize(20);
    LcTau1->GetXaxis()->SetTitleFont(43);
    LcTau1->GetXaxis()->SetTitleOffset(1.5);
    LcTau1->GetXaxis()->SetLabelSize(0.05);
    LcTau1->GetYaxis()->SetTitleSize(20);
    LcTau1->GetYaxis()->SetTitleFont(43);
    LcTau1->GetYaxis()->SetLabelSize(0.05);
    LcTau1->Fit("LcTau1Fit", "E");

    SignalDGH.Form("%5.0f\n", LcTau1Fit->GetParameter(1));
    SignalErDGH.Form("%5.0f\n", LcTau1Fit->GetParError(1));
    FractionDGH.Form("%5.3f\n", LcTau1Fit->GetParameter(0));
    FractionErDGH.Form("%5.3f\n", LcTau1Fit->GetParError(0));
    muDGH.Form("%5.3f\n", LcTau1Fit->GetParameter(2));
    muErDGH.Form("%5.3f\n", LcTau1Fit->GetParError(2));
    sigma1DGH.Form("%5.3f\n", LcTau1Fit->GetParameter(3));
    sigma1ErDGH.Form("%5.3f\n", LcTau1Fit->GetParError(3));
    rmsDGH.Form("%5.3f\n", LcTau1Fit->GetParameter(4));
    rmsErDGH.Form("%5.3f\n", LcTau1Fit->GetParError(4));

    lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
    lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
    lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
    lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

    pad2->cd();
    pad2->Clear();
    TH1D* LcTau1Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
    LcTau1Pull->SetStats(0);
    LcTau1Pull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
    LcTau1Pull->GetXaxis()->SetTitleSize(20);
    LcTau1Pull->GetXaxis()->SetTitleFont(43);
    LcTau1Pull->GetXaxis()->SetTitleOffset(4);
    LcTau1Pull->GetXaxis()->SetLabelSize(0.1);
    LcTau1Pull->GetYaxis()->SetTitle("Pull");
    LcTau1Pull->GetYaxis()->CenterTitle(true);
    LcTau1Pull->GetXaxis()->CenterTitle(true);
    LcTau1Pull->GetYaxis()->SetTitleSize(20);
    LcTau1Pull->GetYaxis()->SetTitleFont(43);
    LcTau1Pull->GetYaxis()->SetLabelSize(0.1);
    LcTau1Pull->SetFillColor(kBlue);
    LcTau1Pull->SetLineColor(kBlue);
    LcTau1Pull->SetBit(TH1::kNoTitle);

    for (Int_t i=1;i<260;i++) {
    Double_t x = LcTau1->GetBinCenter(i);
    Double_t val = LcTau1Fit->Eval(x);
    Double_t sigma = sqrt(val);
    Double_t pull = (LcTau1->GetBinContent(i)-val)/sigma;
    LcTau1Pull->SetBinContent(i,pull);
    }
    LcTau1Pull->Draw();
    c1->Write("LcMLcTau1");
    c1->SaveAs("LcMLcTau1.pdf");

    TF1 *LcTau2Fit = new TF1("LcTau2Fit",DoubleGaussExp,2222, 2352,7);
    LcTau2Fit->SetParameter(0, 0.4);
    LcTau2Fit->SetParLimits(0, 0.01, 0.99);
    LcTau2Fit->SetParameter(1, 10000);
    LcTau2Fit->SetParameter(2, 2287.);
    LcTau2Fit->SetParameter(3, 4);
    LcTau2Fit->SetParameter(4, 7);
    LcTau2Fit->SetParLimits(3, 0, 15);
    LcTau2Fit->SetParLimits(4, 0, 15);
    LcTau2Fit->SetParameter(5, 10);
    LcTau2Fit->SetParameter(6, -0.002);

    pad1->cd();
    pad1->Clear();
    LcTau2->SetMinimum(0.0001);
    LcTau2->SetLineWidth(2);
    LcTau2->GetXaxis()->CenterTitle(true);
    LcTau2->GetXaxis()->SetTitleSize(20);
    LcTau2->GetXaxis()->SetTitleFont(43);
    LcTau2->GetXaxis()->SetTitleOffset(1.5);
    LcTau2->GetXaxis()->SetLabelSize(0.05);
    LcTau2->GetYaxis()->SetTitleSize(20);
    LcTau2->GetYaxis()->SetTitleFont(43);
    LcTau2->GetYaxis()->SetLabelSize(0.05);
    LcTau2->Fit("LcTau2Fit", "E");

    SignalDGH.Form("%5.0f\n", LcTau2Fit->GetParameter(1));
    SignalErDGH.Form("%5.0f\n", LcTau2Fit->GetParError(1));
    FractionDGH.Form("%5.3f\n", LcTau2Fit->GetParameter(0));
    FractionErDGH.Form("%5.3f\n", LcTau2Fit->GetParError(0));
    muDGH.Form("%5.3f\n", LcTau2Fit->GetParameter(2));
    muErDGH.Form("%5.3f\n", LcTau2Fit->GetParError(2));
    sigma1DGH.Form("%5.3f\n", LcTau2Fit->GetParameter(3));
    sigma1ErDGH.Form("%5.3f\n", LcTau2Fit->GetParError(3));
    rmsDGH.Form("%5.3f\n", LcTau2Fit->GetParameter(4));
    rmsErDGH.Form("%5.3f\n", LcTau2Fit->GetParError(4));

    lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
    lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
    lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
    lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

    pad2->cd();
    pad2->Clear();
    TH1D* LcTau2Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
    LcTau2Pull->SetStats(0);
    LcTau2Pull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
    LcTau2Pull->GetXaxis()->SetTitleSize(20);
    LcTau2Pull->GetXaxis()->SetTitleFont(43);
    LcTau2Pull->GetXaxis()->SetTitleOffset(4);
    LcTau2Pull->GetXaxis()->SetLabelSize(0.1);
    LcTau2Pull->GetYaxis()->SetTitle("Pull");
    LcTau2Pull->GetYaxis()->CenterTitle(true);
    LcTau2Pull->GetXaxis()->CenterTitle(true);
    LcTau2Pull->GetYaxis()->SetTitleSize(20);
    LcTau2Pull->GetYaxis()->SetTitleFont(43);
    LcTau2Pull->GetYaxis()->SetLabelSize(0.1);
    LcTau2Pull->SetFillColor(kBlue);
    LcTau2Pull->SetLineColor(kBlue);
    LcTau2Pull->SetBit(TH1::kNoTitle);

    for (Int_t i=1;i<260;i++) {
    Double_t x = LcTau2->GetBinCenter(i);
    Double_t val = LcTau2Fit->Eval(x);
    Double_t sigma = sqrt(val);
    Double_t pull = (LcTau2->GetBinContent(i)-val)/sigma;
    LcTau2Pull->SetBinContent(i,pull);
    }
    LcTau2Pull->Draw();
    c1->Write("LcMLcTau2");
    c1->SaveAs("LcMLcTau2.pdf");

    TF1 *LcTau3Fit = new TF1("LcTau3Fit",DoubleGaussExp,2222, 2352,7);
    LcTau3Fit->SetParameter(0, 0.4);
    LcTau3Fit->SetParLimits(0, 0.01, 0.99);
    LcTau3Fit->SetParameter(1, 10000);
    LcTau3Fit->SetParameter(2, 2287.);
    LcTau3Fit->SetParameter(3, 4);
    LcTau3Fit->SetParameter(4, 7);
    LcTau3Fit->SetParLimits(3, 0, 15);
    LcTau3Fit->SetParLimits(4, 0, 15);
    LcTau3Fit->SetParameter(5, 10);
    LcTau3Fit->SetParameter(6, -0.002);

    pad1->cd();
    pad1->Clear();
    LcTau3->SetMinimum(0.0001);
    LcTau3->SetLineWidth(2);
    LcTau3->GetXaxis()->CenterTitle(true);
    LcTau3->GetXaxis()->SetTitleSize(20);
    LcTau3->GetXaxis()->SetTitleFont(43);
    LcTau3->GetXaxis()->SetTitleOffset(1.5);
    LcTau3->GetXaxis()->SetLabelSize(0.05);
    LcTau3->GetYaxis()->SetTitleSize(20);
    LcTau3->GetYaxis()->SetTitleFont(43);
    LcTau3->GetYaxis()->SetLabelSize(0.05);
    LcTau3->Fit("LcTau3Fit", "E");

    SignalDGH.Form("%5.0f\n", LcTau3Fit->GetParameter(1));
    SignalErDGH.Form("%5.0f\n", LcTau3Fit->GetParError(1));
    FractionDGH.Form("%5.3f\n", LcTau3Fit->GetParameter(0));
    FractionErDGH.Form("%5.3f\n", LcTau3Fit->GetParError(0));
    muDGH.Form("%5.3f\n", LcTau3Fit->GetParameter(2));
    muErDGH.Form("%5.3f\n", LcTau3Fit->GetParError(2));
    sigma1DGH.Form("%5.3f\n", LcTau3Fit->GetParameter(3));
    sigma1ErDGH.Form("%5.3f\n", LcTau3Fit->GetParError(3));
    rmsDGH.Form("%5.3f\n", LcTau3Fit->GetParameter(4));
    rmsErDGH.Form("%5.3f\n", LcTau3Fit->GetParError(4));

    lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
    lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
    lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
    lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
    lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

    pad2->cd();
    pad2->Clear();
    TH1D* LcTau3Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
    LcTau3Pull->SetStats(0);
    LcTau3Pull->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
    LcTau3Pull->GetXaxis()->SetTitleSize(20);
    LcTau3Pull->GetXaxis()->SetTitleFont(43);
    LcTau3Pull->GetXaxis()->SetTitleOffset(4);
    LcTau3Pull->GetXaxis()->SetLabelSize(0.1);
    LcTau3Pull->GetYaxis()->SetTitle("Pull");
    LcTau3Pull->GetYaxis()->CenterTitle(true);
    LcTau3Pull->GetXaxis()->CenterTitle(true);
    LcTau3Pull->GetYaxis()->SetTitleSize(20);
    LcTau3Pull->GetYaxis()->SetTitleFont(43);
    LcTau3Pull->GetYaxis()->SetLabelSize(0.1);
    LcTau3Pull->SetFillColor(kBlue);
    LcTau3Pull->SetLineColor(kBlue);
    LcTau3Pull->SetBit(TH1::kNoTitle);

    for (Int_t i=1;i<260;i++) {
    Double_t x = LcTau3->GetBinCenter(i);
    Double_t val = LcTau3Fit->Eval(x);
    Double_t sigma = sqrt(val);
    Double_t pull = (LcTau3->GetBinContent(i)-val)/sigma;
    LcTau3Pull->SetBinContent(i,pull);
    }
    LcTau3Pull->Draw();
    c1->Write("LcMLcTau3");
    c1->SaveAs("LcMLcTau3.pdf");

  ///////////////////////////////
  const Int_t m = 2;
  const Int_t v = 3;
  const Int_t n = 4;
  Double_t x[n] = {1,2,3,4};
  Double_t xerr[n] = {0,0,0,0};
  TString magchi2val;
  TString chargechi2val;
  TString lcpchi2val;
  TString lctauchi2val;

  grid->cd();
  grid->SetGridy();
  grid->SetLeftMargin(0.15);
  grid->SetBottomMargin(0.15);
  lt->SetTextSize(0.04);
  lt->SetTextColor(2);

  double mag1 = MagDownFit->GetParameter(2);
  double mag2 = MagUpFit->GetParameter(2);
  double magerr1 = MagDownFit->GetParError(2);
  double magerr2 = MagUpFit->GetParError(2);
  double PolarityAvG = ((mag1 + mag2)/m);
  Double_t mag[m] = {mag1 - PolarityAvG,mag2 - PolarityAvG};
  Double_t magerr[m] = {magerr1,magerr2};

  double magchi2pdf = ((abs(mag[0])/magerr[0])*(abs(mag[0])/magerr[0]) + (abs(mag[1])/magerr[1])*(abs(mag[1])/magerr[1]))/(m-1);
  magchi2val.Form("%5.3f\n", magchi2pdf);
  double MagError = 0;
  if (magchi2pdf > 1){
  MagError = FinalFit->GetParError(2) * TMath::Sqrt(magchi2pdf - 1);
  }

  double charge1 = ParticleFit->GetParameter(2);
  double charge2 = AntiParticleFit->GetParameter(2);
  double chargeerr1 = ParticleFit->GetParError(2);
  double chargeerr2 = AntiParticleFit->GetParError(2);
  double ChargeAvG = ((charge1 + charge2)/m);
  Double_t charge[m] = {charge1 - ChargeAvG,charge2 - ChargeAvG};
  Double_t chargeerr[m] = {chargeerr1,chargeerr2};

  double chargechi2pdf = ((abs(charge[0])/chargeerr[0])*(abs(charge[0])/chargeerr[0]) + (abs(charge[1])/chargeerr[1])*(abs(charge[1])/chargeerr[1]))/(m-1);
  chargechi2val.Form("%5.3f\n", chargechi2pdf);
  double ChargeError = 0;
  if (chargechi2pdf > 1){
  ChargeError = FinalFit->GetParError(2) * TMath::Sqrt(chargechi2pdf - 1);
  }

  double lcp1 = LcP1Fit->GetParameter(2);
  double lcp2 = LcP2Fit->GetParameter(2);
  double lcp3 = LcP3Fit->GetParameter(2);
  double lcp4 = LcP4Fit->GetParameter(2);
  double lcperr1 = LcP1Fit->GetParError(2);
  double lcperr2 = LcP2Fit->GetParError(2);
  double lcperr3 = LcP3Fit->GetParError(2);
  double lcperr4 = LcP4Fit->GetParError(2);
  double LcpAvG = ((lcp1 + lcp2 + lcp3 + lcp4)/n);
  Double_t lcp[n] = {lcp1 - LcpAvG,lcp2 - LcpAvG, lcp3 - LcpAvG,lcp4 - LcpAvG};
  Double_t lcperr[n] = {lcperr1,lcperr2,lcperr3,lcperr4};

  double lcpchi2pdf = ((abs(lcp[0])/lcperr[0])*(abs(lcp[0])/lcperr[0]) + (abs(lcp[1])/lcperr[1])*(abs(lcp[1])/lcperr[1]) + (abs(lcp[2])/lcperr[2])*(abs(lcp[2])/lcperr[2]) + (abs(lcp[3])/lcperr[3])*(abs(lcp[3])/lcperr[3]))/(n-1);
  lcpchi2val.Form("%5.3f\n", lcpchi2pdf);
  double LcPError = 0;
  if (lcpchi2pdf > 1){
  LcPError = FinalFit->GetParError(2) * TMath::Sqrt(lcpchi2pdf - 1);
  }

  double lctau1 = LcTau1Fit->GetParameter(2);
  double lctau2 = LcTau2Fit->GetParameter(2);
  double lctau3 = LcTau3Fit->GetParameter(2);
  double lctau1err = LcTau1Fit->GetParError(2);
  double lctau2err  = LcTau2Fit->GetParError(2);
  double lctau3err  = LcTau3Fit->GetParError(2);
  double LctauAvG = ((lctau1 + lctau2 + lctau3)/v);
  Double_t lctau[v] = {lctau1 - LctauAvG,lctau2 - LctauAvG, lctau3 - LctauAvG};
  Double_t lctauerr[v] = {lctau1err,lctau2err,lctau3err};

  double lctauchi2pdf = ((abs(lctau[0])/lctauerr[0])*(abs(lctau[0])/lctauerr[0]) + (abs(lctau[1])/lctauerr[1])*(abs(lctau[1])/lctauerr[1]) + (abs(lctau[2])/lctauerr[2])*(abs(lctau[2])/lctauerr[2]))/(v-1);
  lctauchi2val.Form("%5.3f\n", lctauchi2pdf);
  double LctauError = 0;
  if (lctauchi2pdf > 1){
  LctauError = FinalFit->GetParError(2) * TMath::Sqrt(lctauchi2pdf - 1);
  }

  ///////////////////////////////////

  grid->cd();

  gPolarity = new TGraphErrors(m,x,mag,xerr,magerr);
  gPolarity->GetXaxis()->CenterTitle(true);
  gPolarity->GetXaxis()->SetTitleSize(20);
  gPolarity->GetXaxis()->SetTitleFont(43);
  gPolarity->GetXaxis()->SetTitleOffset(1.5);
  gPolarity->GetXaxis()->SetLabelSize(0.075);
  gPolarity->GetYaxis()->SetTitleSize(20);
  gPolarity->GetYaxis()->SetTitleFont(43);
  gPolarity->GetYaxis()->SetLabelSize(0.05);
  gPolarity->SetMarkerColor(2);
  gPolarity->SetMarkerStyle(20);
  gPolarity->GetXaxis()->SetNdivisions(2);
  gPolarity->GetXaxis()->SetTitle("Magnetic Field Orientation");
  MassAVGPolarity.Form("%4.3f\n", PolarityAvG);
  gPolarity->GetYaxis()->SetTitle("Measured Mass - "+MassAVGPolarity+" [MeV]");
  gPolarity->GetXaxis()->SetAlphanumeric();
  gPolarity->GetXaxis()->SetBinLabel(9, "Magnet-Down");
  gPolarity->GetXaxis()->SetBinLabel(92, "Magnet-Up");
  gPolarity->GetXaxis()->LabelsOption("h");
  gPolarity->SetTitle("");
  gPolarity->Draw("ap");
  lt->DrawLatexNDC(0.25, 0.75, "LHCb Preliminary");
  lt->DrawLatexNDC(0.25, 0.70, "#chi^2/NDF ="+magchi2val);
  grid->Write("Polarity Statistics");
  grid->SaveAs("gPolarity.pdf");

  gCharge = new TGraphErrors(m,x,charge,xerr,chargeerr);
  gCharge->GetXaxis()->CenterTitle(true);
  gCharge->GetXaxis()->SetTitleSize(20);
  gCharge->GetXaxis()->SetTitleFont(43);
  gCharge->GetXaxis()->SetTitleOffset(1.5);
  gCharge->GetXaxis()->SetLabelSize(0.075);
  gCharge->GetYaxis()->SetTitleSize(20);
  gCharge->GetYaxis()->SetTitleFont(43);
  gCharge->GetYaxis()->SetLabelSize(0.05);
  gCharge->SetMarkerColor(2);
  gCharge->SetMarkerStyle(20);
  gCharge->GetXaxis()->SetNdivisions(2);
  gCharge->GetXaxis()->SetTitle("Charge");
  MassAVGCharge.Form("%4.3f\n", ChargeAvG);
  gCharge->GetYaxis()->SetTitle("Measured Mass - "+MassAVGCharge+" [MeV]");
  gCharge->GetXaxis()->SetAlphanumeric();
  gCharge->GetXaxis()->SetBinLabel(9, "#Lambda_{c}^{+}");
  gCharge->GetXaxis()->SetBinLabel(92, "#Lambda_{c}^{-}");
  gCharge->GetXaxis()->LabelsOption("h");
  gCharge->SetTitle("");
  gCharge->Draw("ap");
  lt->DrawLatexNDC(0.25, 0.75, "LHCb Preliminary");
  lt->DrawLatexNDC(0.25, 0.70, "#chi^2/NDF ="+chargechi2val);
  grid->Write("Charge Statistics");
  grid->SaveAs("gCharge.pdf");

  gLcP = new TGraphErrors(n,x,lcp,xerr,lcperr);
  gLcP->GetXaxis()->CenterTitle(true);
  gLcP->GetXaxis()->SetTitleSize(20);
  gLcP->GetXaxis()->SetTitleFont(43);
  gLcP->GetXaxis()->SetTitleOffset(1.5);
  gLcP->GetXaxis()->SetLabelSize(0.075);
  gLcP->GetYaxis()->SetTitleSize(20);
  gLcP->GetYaxis()->SetTitleFont(43);
  gLcP->GetYaxis()->SetLabelSize(0.05);
  gLcP->SetMarkerColor(2);
  gLcP->SetMarkerStyle(20);
  gLcP->GetXaxis()->SetNdivisions(4);
  gLcP->GetXaxis()->SetTitle("Momentum Regions [GeV]");
  MassAVGLcP.Form("%4.3f\n", LcpAvG);
  gLcP->GetYaxis()->SetTitle("Measured Mass - "+MassAVGLcP+" [MeV]");
  gLcP->GetXaxis()->SetAlphanumeric();
  gLcP->GetXaxis()->SetBinLabel(9, "(0-47.5)");
  gLcP->GetXaxis()->SetBinLabel(36, "(47.5-62.5)");
  gLcP->GetXaxis()->SetBinLabel(63, "(62.5-81)");
  gLcP->GetXaxis()->SetBinLabel(90, "(81-110)");
  gLcP->GetXaxis()->LabelsOption("h");
  gLcP->SetTitle("");
  gLcP->Draw("ap");
  lt->DrawLatexNDC(0.25, 0.75, "LHCb Preliminary");
  lt->DrawLatexNDC(0.25, 0.70, "#chi^2/NDF ="+lcpchi2val);
  grid->Write("LcP Statistics");
  grid->SaveAs("gLcP.pdf");

  gLcTau = new TGraphErrors(v,x,lctau,xerr,lctauerr);
  gLcTau->GetXaxis()->CenterTitle(true);
  gLcTau->GetXaxis()->SetTitleSize(20);
  gLcTau->GetXaxis()->SetTitleFont(43);
  gLcTau->GetXaxis()->SetTitleOffset(1.5);
  gLcTau->GetXaxis()->SetLabelSize(0.075);
  gLcTau->GetYaxis()->SetTitleSize(20);
  gLcTau->GetYaxis()->SetTitleFont(43);
  gLcTau->GetYaxis()->SetLabelSize(0.05);
  gLcTau->SetMarkerColor(2);
  gLcTau->SetMarkerStyle(20);
  gLcTau->GetXaxis()->SetNdivisions(4);
  gLcTau->GetXaxis()->SetTitle("Decay Time Regions [ps]");
  MassAVGLcTau.Form("%4.3f\n", LctauAvG);
  gLcTau->GetYaxis()->SetTitle("Measured Mass - "+MassAVGLcTau+" [MeV]");
  gLcTau->GetXaxis()->SetAlphanumeric();
  gLcTau->GetXaxis()->SetBinLabel(10, "(0.0-0.57)");
  gLcTau->GetXaxis()->SetBinLabel(50, "(0.57-0.76)");
  gLcTau->GetXaxis()->SetBinLabel(90, "(0.76-1.3)");
  gLcTau->GetXaxis()->LabelsOption("h");
  gLcTau->SetTitle("");
  gLcTau->Draw("ap");
  lt->DrawLatexNDC(0.25, 0.75, "LHCb Preliminary");
  lt->DrawLatexNDC(0.25, 0.70, "#chi^2/NDF ="+lctauchi2val);
  grid->Write("LcTau Statistics");
  grid->SaveAs("gLcTau.pdf");

  cout << "Magnet Chi2 =" << magchi2pdf << endl;
  cout << "Magnet Error =" << MagError << endl;
  cout << "Charge Chi2 =" << chargechi2pdf << endl;
  cout << "Charge Error =" << ChargeError << endl;
  cout << "Momentum Chi2 =" << lcpchi2pdf << endl;
  cout << "Momentum Error =" << LcPError << endl;
  cout << "Tau Chi2 =" << lctauchi2pdf << endl;
  cout << "Tau Error =" << LctauError << endl;
}
