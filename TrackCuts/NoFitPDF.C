#define NoFitPDF_cxx
#include "NoFitPDF.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

TH1D * NoFitMass = nullptr;
TCanvas * c1 = nullptr;

void NoFitPDF::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void NoFitPDF::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

   NoFitMass = new TH1D("", "", 260, 2222, 2352);
   NoFitMass->GetXaxis()->SetTitle("m(pK^{-}K^{+}) [MeV]");
   NoFitMass->GetYaxis()->SetTitle("Entries / (0.5 MeV)");

       c1 = new TCanvas("canvas", "Test Canvas");
}

Bool_t NoFitPDF::Process(Long64_t entry)
{
      GetEntry(entry);
      fReader.SetLocalEntry(entry);


        bool MassRange= (
        (*Lc_M > 2222 && *Lc_M < 2352)
        );

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

      bool LcTrackCuts= (
        ((1/0.9)*(1/0.9)*TMath::Log10(*Lc_IPCHI2_OWNPV)*TMath::Log10(*Lc_IPCHI2_OWNPV) + (1/0.0010)*(1/0.0010)*(*Lc_TAU - 0.0003)*(*Lc_TAU - 0.0003)) < 1
     && TMath::Log10(*Lc_ENDVERTEX_CHI2) > (10*(*Lc_Loki_DOCAMAX) - 0.5)
     && TMath::Log10(*Lc_ENDVERTEX_CHI2) < 1.2
           );

         if(PIDBSubbedCuts && DalitzCuts && LcTrackCuts && MassRange){
NoFitMass->Fill(*Lc_M);
         }

   return kTRUE;
}

void NoFitPDF::SlaveTerminate()
{
}

void NoFitPDF::Terminate()
{
c1->cd();
c1->SetBottomMargin(0.2);
c1->SetLeftMargin(0.15);

  gStyle->SetOptStat(11);
  gStyle->SetStatW(0.25);
  gStyle->SetStatH(0.25);

auto lt = new TLatex();
lt->SetTextSize(0.04);

NoFitMass->SetMinimum(0.0001);
NoFitMass->GetXaxis()->CenterTitle(true);
NoFitMass->GetXaxis()->SetTitleSize(20);
NoFitMass->GetXaxis()->SetTitleFont(43);
NoFitMass->GetXaxis()->SetTitleOffset(1.5);
NoFitMass->GetXaxis()->SetLabelSize(0.05);
NoFitMass->GetYaxis()->SetTitleSize(20);
NoFitMass->GetYaxis()->SetTitleFont(43);
NoFitMass->GetYaxis()->SetLabelSize(0.05);
NoFitMass->Draw();
gPad->Update();
NoFitMass->SetLineWidth(2);
lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
c1->SaveAs("LcMNoFit.pdf");
}
