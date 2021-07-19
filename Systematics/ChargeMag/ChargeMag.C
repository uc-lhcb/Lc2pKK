#define ChargeMag_cxx
#include "ChargeMag.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

#include "DoubleGaussExpHalf.C"

const TString files_dir_magup = "/share/lazy/D2KKPi_MomentumScaled/D2KKPi_MagUp_mKSq243717_mDpSq3495609_Files/";
const TString files_dir_magdown = "/share/lazy/D2KKPi_MomentumScaled/D2KKPi_MagDown_mKSq243717_mDpSq3495609_Files/";

//mKSq mass is dependent on which correction hists we use.
const double mKSq = 243717/1.0E6; // GeV^2
const double mPSq = (938.272)*(938.272)/1.0E6; // GeV^2

TH1D * ChargeMag1 = nullptr;
TH1D * ChargeMag2 = nullptr;
TH1D * ChargeMag3 = nullptr;
TH1D * ChargeMag4 = nullptr;

TGraphErrors * g1 = nullptr;
TGraphErrors * g2 = nullptr;

TCanvas * c1 = nullptr;
TCanvas * grid = nullptr;

const int NDau = 3;
const int NCorr = 4;

TH2D *ref_alpha_magup[NCorr];
TH2D *ref_epsilon_magup[NCorr];
TFile *fref_magup[NCorr];

TH2D *ref_alpha_magdown[NCorr];
TH2D *ref_epsilon_magdown[NCorr];
TFile *fref_magdown[NCorr];

TString str;

void ChargeMag::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void ChargeMag::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

      for(int i = 0; i < NCorr; ++i){
          str.Form("%02d",i+1);
          fref_magdown[i] = new TFile(files_dir_magdown+"D2KKpi_RefHists_Order"+str+"_singlegrid.root");
          ref_alpha_magdown[i] = (TH2D*) fref_magdown[i]->Get("alpha_grid_order"+str);
          ref_epsilon_magdown[i] = (TH2D*) fref_magdown[i]->Get("epsilon_grid_order"+str);
          std::cout<<"Read in magdown alpha hist: "<<ref_alpha_magdown[i]->GetName()<<std::endl;
          fref_magup[i] = new TFile(files_dir_magup+"D2KKpi_RefHists_Order"+str+"_singlegrid.root");
          ref_alpha_magup[i] = (TH2D*) fref_magup[i]->Get("alpha_grid_order"+str);
          ref_epsilon_magup[i] = (TH2D*) fref_magup[i]->Get("epsilon_grid_order"+str);
          std::cout<<"Read in magup alpha hist: "<<ref_alpha_magup[i]->GetName()<<std::endl;
      }

      ChargeMag1 = new TH1D("", "", 260, 2222, 2352);
      ChargeMag1->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      ChargeMag1->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
      ChargeMag2 = new TH1D("", "", 260, 2222, 2352);
      ChargeMag2->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      ChargeMag2->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
      ChargeMag3 = new TH1D("", "", 260, 2222, 2352);
      ChargeMag3->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      ChargeMag3->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
      ChargeMag4 = new TH1D("", "", 260, 2222, 2352);
      ChargeMag4->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      ChargeMag4->GetYaxis()->SetTitle("Entries / (0.5 MeV)");

       c1 = new TCanvas("canvas", "Test Canvas");
         grid = new TCanvas("grid", "Grid Canvas");
}

Bool_t ChargeMag::Process(Long64_t entry)
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

           bool MagDown = (
           (*Polarity < 0.)
           );

           bool MagUp = (
           (*Polarity > 0.)
           );

           bool Particles = (
           (*Lc_ID > 0.)
           );

           bool AntiParticles = (
           (*Lc_ID < 0.)
           );

           double xCoords[NDau]={*Proton_X,*Kplus_X,*Kminus_X};
           double yCoords[NDau]={*Proton_Y,*Kplus_Y,*Kminus_Y};

               double deltaMSq[NCorr];

           if(PIDBSubbedCuts && DalitzCuts && LcTrackCuts && MassRange){
           if(MagUp){
               for(int kk=0; kk < NCorr; ++kk){
                 double pxz;
                 pxz = sqrt(P_vec.Px()*P_vec.Px() + P_vec.Pz()*P_vec.Pz());
                 pxz /= 1000.0;
                 pxz = *Proton_ID > 0 ? pxz : -pxz;
                 double pfac_P = (1.0 + ref_epsilon_magup[kk]->Interpolate(xCoords[0],yCoords[0]))
                   * (1.0 + ref_alpha_magup[kk]->Interpolate(xCoords[0],yCoords[0]) * pxz);

                      pxz = sqrt(Kp_vec.Px()*Kp_vec.Px() + Kp_vec.Pz()*Kp_vec.Pz());
                 pxz /= 1000.0;
                 pxz = *Kplus_ID > 0 ? pxz : -pxz;
                 double pfac_Kp = (1.0 + ref_epsilon_magup[kk]->Interpolate(xCoords[1],yCoords[1]))
                   *(1.0 + ref_alpha_magup[kk]->Interpolate(xCoords[1],yCoords[1]) * pxz);

                   pxz = sqrt(Km_vec.Px()*Km_vec.Px() + Km_vec.Pz()*Km_vec.Pz());
              pxz /= 1000.0;
              pxz = *Kminus_ID > 0 ? pxz : -pxz;
              double pfac_Km = (1.0 + ref_epsilon_magup[kk]->Interpolate(xCoords[2],yCoords[2]))
                *(1.0 + ref_alpha_magup[kk]->Interpolate(xCoords[2],yCoords[2]) * pxz);

                 Km_vec.SetPxPyPzE(pfac_Km*Km_vec.Px(),pfac_Km*Km_vec.Py(),pfac_Km*Km_vec.Pz(),
                                 sqrt( pfac_Km*pfac_Km*Km_vec.Vect().Mag2() + (*Kminus_M * *Kminus_M)) );

                 Kp_vec.SetPxPyPzE(pfac_Kp*Kp_vec.Px(),pfac_Kp*Kp_vec.Py(),pfac_Kp*Kp_vec.Pz(),
                                   sqrt( pfac_Kp*pfac_Kp*Kp_vec.Vect().Mag2() + (*Kplus_M * *Kplus_M)) );

                 P_vec.SetPxPyPzE(pfac_P*P_vec.Px(),pfac_P*P_vec.Py(),pfac_P*P_vec.Pz(),
                                   sqrt( pfac_P*pfac_P*P_vec.Vect().Mag2() + (*Proton_M * *Proton_M)) );

                 LcVec = Km_vec + Kp_vec + P_vec;

                 double delta_Km   = pfac_Km   - 1.0;
                 double delta_Kp = pfac_Kp - 1.0;
                 double delta_P = pfac_P - 1.0;

                 Double_t Theta_KmKp = acos( (Km_vec.Px()*Kp_vec.Px() + Km_vec.Py()*Kp_vec.Py()
                                             + Km_vec.Pz()*Kp_vec.Pz())/(Km_vec.P()*Kp_vec.P()));

                 Double_t Theta_KmP = acos( (Km_vec.Px()*P_vec.Px() + Km_vec.Py()*P_vec.Py()
                                             + Km_vec.Pz()*P_vec.Pz())/(Km_vec.P()*P_vec.P()));

                 Double_t Theta_KpP = acos( (Kp_vec.Px()*P_vec.Px() + Kp_vec.Py()*P_vec.Py()
                                             + Kp_vec.Pz()*P_vec.Pz())/(Kp_vec.P()*P_vec.P()));

                 double sq_KmKp_term = (mKSq * Km_vec.P()/Kp_vec.P() - mKSq * Kp_vec.P()/Km_vec.P()) * (delta_Km - delta_Kp)
                   + Km_vec.P() * Kp_vec.P() * (delta_Kp + delta_Km) * Theta_KmKp * Theta_KmKp;

                 double sq_KmP_term = (mPSq * Km_vec.P()/P_vec.P() - mKSq * P_vec.P()/Km_vec.P()) * (delta_Km - delta_P)
                   + Km_vec.P() * P_vec.P() * (delta_P + delta_Km) * Theta_KmP * Theta_KmP;

                 double sq_KpP_term = (mPSq * Kp_vec.P()/P_vec.P() - mKSq * P_vec.P()/Kp_vec.P()) * (delta_Kp - delta_P)
                   + Kp_vec.P() * P_vec.P() * (delta_P + delta_Kp) * Theta_KpP * Theta_KpP;

                 deltaMSq[kk] = sq_KmKp_term + sq_KmP_term + sq_KpP_term;
               }
           }

           if(MagDown){
             for(int kk=0; kk < NCorr; ++kk){
               double pxz;
               pxz = sqrt(P_vec.Px()*P_vec.Px() + P_vec.Pz()*P_vec.Pz());
               pxz /= 1000.0;
               pxz = *Proton_ID > 0 ? pxz : -pxz;
               double pfac_P = (1.0 + ref_epsilon_magdown[kk]->Interpolate(xCoords[0],yCoords[0]))
                 * (1.0 + ref_alpha_magdown[kk]->Interpolate(xCoords[0],yCoords[0]) * pxz);

                    pxz = sqrt(Kp_vec.Px()*Kp_vec.Px() + Kp_vec.Pz()*Kp_vec.Pz());
               pxz /= 1000.0;
               pxz = *Kplus_ID > 0 ? pxz : -pxz;
               double pfac_Kp = (1.0 + ref_epsilon_magdown[kk]->Interpolate(xCoords[1],yCoords[1]))
                 *(1.0 + ref_alpha_magdown[kk]->Interpolate(xCoords[1],yCoords[1]) * pxz);

                 pxz = sqrt(Km_vec.Px()*Km_vec.Px() + Km_vec.Pz()*Km_vec.Pz());
            pxz /= 1000.0;
            pxz = *Kminus_ID > 0 ? pxz : -pxz;
            double pfac_Km = (1.0 + ref_epsilon_magdown[kk]->Interpolate(xCoords[2],yCoords[2]))
              *(1.0 + ref_alpha_magdown[kk]->Interpolate(xCoords[2],yCoords[2]) * pxz);

               Km_vec.SetPxPyPzE(pfac_Km*Km_vec.Px(),pfac_Km*Km_vec.Py(),pfac_Km*Km_vec.Pz(),
                               sqrt( pfac_Km*pfac_Km*Km_vec.Vect().Mag2() + (*Kminus_M * *Kminus_M)) );

               Kp_vec.SetPxPyPzE(pfac_Kp*Kp_vec.Px(),pfac_Kp*Kp_vec.Py(),pfac_Kp*Kp_vec.Pz(),
                                 sqrt( pfac_Kp*pfac_Kp*Kp_vec.Vect().Mag2() + (*Kplus_M * *Kplus_M)) );

               P_vec.SetPxPyPzE(pfac_P*P_vec.Px(),pfac_P*P_vec.Py(),pfac_P*P_vec.Pz(),
                                 sqrt( pfac_P*pfac_P*P_vec.Vect().Mag2() + (*Proton_M * *Proton_M)) );

               LcVec = Km_vec + Kp_vec + P_vec;

               double delta_Km   = pfac_Km   - 1.0;
               double delta_Kp = pfac_Kp - 1.0;
               double delta_P = pfac_P - 1.0;

               Double_t Theta_KmKp = acos( (Km_vec.Px()*Kp_vec.Px() + Km_vec.Py()*Kp_vec.Py()
                                           + Km_vec.Pz()*Kp_vec.Pz())/(Km_vec.P()*Kp_vec.P()));

               Double_t Theta_KmP = acos( (Km_vec.Px()*P_vec.Px() + Km_vec.Py()*P_vec.Py()
                                           + Km_vec.Pz()*P_vec.Pz())/(Km_vec.P()*P_vec.P()));

               Double_t Theta_KpP = acos( (Kp_vec.Px()*P_vec.Px() + Kp_vec.Py()*P_vec.Py()
                                           + Kp_vec.Pz()*P_vec.Pz())/(Kp_vec.P()*P_vec.P()));

               double sq_KmKp_term = (mKSq * Km_vec.P()/Kp_vec.P() - mKSq * Kp_vec.P()/Km_vec.P()) * (delta_Km - delta_Kp)
                 + Km_vec.P() * Kp_vec.P() * (delta_Kp + delta_Km) * Theta_KmKp * Theta_KmKp;

               double sq_KmP_term = (mPSq * Km_vec.P()/P_vec.P() - mKSq * P_vec.P()/Km_vec.P()) * (delta_Km - delta_P)
                 + Km_vec.P() * P_vec.P() * (delta_P + delta_Km) * Theta_KmP * Theta_KmP;

               double sq_KpP_term = (mPSq * Kp_vec.P()/P_vec.P() - mKSq * P_vec.P()/Kp_vec.P()) * (delta_Kp - delta_P)
                 + Kp_vec.P() * P_vec.P() * (delta_P + delta_Kp) * Theta_KpP * Theta_KpP;

               deltaMSq[kk] = sq_KmKp_term + sq_KmP_term + sq_KpP_term;
             }}

             if(MagDown && Particles){
               ChargeMag1->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
             }

             if(MagDown && AntiParticles){
               ChargeMag2->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
             }

             if(MagUp && Particles){
               ChargeMag3->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
             }

             if(MagUp && AntiParticles){
               ChargeMag4->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
             }


           }

   return kTRUE;
}

void ChargeMag::SlaveTerminate()
{
}

void ChargeMag::Terminate()
{

    c1->cd();

    TString SignalDGH;
    TString SignalErDGH;
    TString FractionDGH;
    TString FractionErDGH;
    TString muDGH;
    TString muErDGH;
    TString sigma1DGH;
    TString sigma1ErDGH;
    TString rmsDGH;
    TString rmsErDGH;

    TString MassAVG;


    c1->SetBottomMargin(0.2);
    c1->SetLeftMargin(0.15);
    c1->SetRightMargin(0.15);

      gStyle->SetOptStat(11);
      gStyle->SetStatW(0.25);
      gStyle->SetStatH(0.25);

      auto lt = new TLatex();
      lt->SetTextSize(0.048);

      ChargeMag1->SetLineWidth(2);
      ChargeMag2->SetLineWidth(2);
      ChargeMag3->SetLineWidth(2);
      ChargeMag4->SetLineWidth(2);

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

      TF1 *ChargeMag1Fit = new TF1("ChargeMag1Fit",DoubleGaussExp,2222, 2352,7);
      ChargeMag1Fit->SetParameter(0, 0.4);
      ChargeMag1Fit->SetParLimits(0, 0.01, 0.99);
      ChargeMag1Fit->SetParameter(1, 8000);
      ChargeMag1Fit->SetParameter(2, 2287.);
      ChargeMag1Fit->SetParameter(3, 4);
      ChargeMag1Fit->SetParameter(4, 7);
      ChargeMag1Fit->SetParLimits(3, 0, 20);
      ChargeMag1Fit->SetParLimits(4, 0, 20);
      ChargeMag1Fit->SetParameter(5, 10);
      ChargeMag1Fit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      ChargeMag1->SetMinimum(0.0001);
      ChargeMag1->GetXaxis()->CenterTitle(true);
      ChargeMag1->GetXaxis()->SetTitleSize(20);
      ChargeMag1->GetXaxis()->SetTitleFont(43);
      ChargeMag1->GetXaxis()->SetTitleOffset(1.5);
      ChargeMag1->GetXaxis()->SetLabelSize(0.05);
      ChargeMag1->GetYaxis()->SetTitleSize(20);
      ChargeMag1->GetYaxis()->SetTitleFont(43);
      ChargeMag1->GetYaxis()->SetLabelSize(0.05);
      ChargeMag1->Fit("ChargeMag1Fit", "E");

      SignalDGH.Form("%5.0f\n", ChargeMag1Fit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", ChargeMag1Fit->GetParError(1));
      FractionDGH.Form("%5.3f\n", ChargeMag1Fit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", ChargeMag1Fit->GetParError(0));
      muDGH.Form("%5.3f\n", ChargeMag1Fit->GetParameter(2));
      muErDGH.Form("%5.3f\n", ChargeMag1Fit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", ChargeMag1Fit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", ChargeMag1Fit->GetParError(3));
      rmsDGH.Form("%5.3f\n", ChargeMag1Fit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", ChargeMag1Fit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* ChargeMag1Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      ChargeMag1Pull->SetStats(0);
      ChargeMag1Pull->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      ChargeMag1Pull->GetXaxis()->SetTitleSize(20);
      ChargeMag1Pull->GetXaxis()->SetTitleFont(43);
      ChargeMag1Pull->GetXaxis()->SetTitleOffset(4);
      ChargeMag1Pull->GetXaxis()->SetLabelSize(0.1);
      ChargeMag1Pull->GetYaxis()->SetTitle("Pull");
      ChargeMag1Pull->GetYaxis()->CenterTitle(true);
      ChargeMag1Pull->GetXaxis()->CenterTitle(true);
      ChargeMag1Pull->GetYaxis()->SetTitleSize(20);
      ChargeMag1Pull->GetYaxis()->SetTitleFont(43);
      ChargeMag1Pull->GetYaxis()->SetLabelSize(0.1);
      ChargeMag1Pull->SetMinimum(-5.1);
      ChargeMag1Pull->SetMaximum(5.1);
      ChargeMag1Pull->SetFillColor(kBlue);
      ChargeMag1Pull->SetLineColor(kBlue);
      ChargeMag1Pull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = ChargeMag1->GetBinCenter(i);
      Double_t val = ChargeMag1Fit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (ChargeMag1->GetBinContent(i)-val)/sigma;
      ChargeMag1Pull->SetBinContent(i,pull);
      }
      ChargeMag1Pull->Draw();

      c1->SaveAs("LcMChargeMag1.pdf");

      TF1 *ChargeMag2Fit = new TF1("ChargeMag2Fit",DoubleGaussExp,2222, 2352,7);
      ChargeMag2Fit->SetParameter(0, 0.4);
      ChargeMag2Fit->SetParLimits(0, 0.01, 0.99);
      ChargeMag2Fit->SetParameter(1, 8000);
      ChargeMag2Fit->SetParameter(2, 2287.);
      ChargeMag2Fit->SetParameter(3, 4);
      ChargeMag2Fit->SetParameter(4, 7);
      ChargeMag2Fit->SetParLimits(3, 0, 20);
      ChargeMag2Fit->SetParLimits(4, 0, 20);
      ChargeMag2Fit->SetParameter(5, 10);
      ChargeMag2Fit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      ChargeMag2->SetMinimum(0.0001);
      ChargeMag2->GetXaxis()->CenterTitle(true);
      ChargeMag2->GetXaxis()->SetTitleSize(20);
      ChargeMag2->GetXaxis()->SetTitleFont(43);
      ChargeMag2->GetXaxis()->SetTitleOffset(1.5);
      ChargeMag2->GetXaxis()->SetLabelSize(0.05);
      ChargeMag2->GetYaxis()->SetTitleSize(20);
      ChargeMag2->GetYaxis()->SetTitleFont(43);
      ChargeMag2->GetYaxis()->SetLabelSize(0.05);
      ChargeMag2->Fit("ChargeMag2Fit", "E");

      SignalDGH.Form("%5.0f\n", ChargeMag2Fit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", ChargeMag2Fit->GetParError(1));
      FractionDGH.Form("%5.3f\n", ChargeMag2Fit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", ChargeMag2Fit->GetParError(0));
      muDGH.Form("%5.3f\n", ChargeMag2Fit->GetParameter(2));
      muErDGH.Form("%5.3f\n", ChargeMag2Fit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", ChargeMag2Fit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", ChargeMag2Fit->GetParError(3));
      rmsDGH.Form("%5.3f\n", ChargeMag2Fit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", ChargeMag2Fit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* ChargeMag2Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      ChargeMag2Pull->SetStats(0);
      ChargeMag2Pull->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      ChargeMag2Pull->GetXaxis()->SetTitleSize(20);
      ChargeMag2Pull->GetXaxis()->SetTitleFont(43);
      ChargeMag2Pull->GetXaxis()->SetTitleOffset(4);
      ChargeMag2Pull->GetXaxis()->SetLabelSize(0.1);
      ChargeMag2Pull->GetYaxis()->SetTitle("Pull");
      ChargeMag2Pull->GetYaxis()->CenterTitle(true);
      ChargeMag2Pull->GetXaxis()->CenterTitle(true);
      ChargeMag2Pull->GetYaxis()->SetTitleSize(20);
      ChargeMag2Pull->GetYaxis()->SetTitleFont(43);
      ChargeMag2Pull->GetYaxis()->SetLabelSize(0.1);
      ChargeMag2Pull->SetMinimum(-5.1);
      ChargeMag2Pull->SetMaximum(5.1);
      ChargeMag2Pull->SetFillColor(kBlue);
      ChargeMag2Pull->SetLineColor(kBlue);
      ChargeMag2Pull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = ChargeMag2->GetBinCenter(i);
      Double_t val = ChargeMag2Fit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (ChargeMag2->GetBinContent(i)-val)/sigma;
      ChargeMag2Pull->SetBinContent(i,pull);
      }
      ChargeMag2Pull->Draw();

      c1->SaveAs("LcMChargeMag2.pdf");

      TF1 *ChargeMag3Fit = new TF1("ChargeMag3Fit",DoubleGaussExp,2222, 2352,7);
      ChargeMag3Fit->SetParameter(0, 0.4);
      ChargeMag3Fit->SetParLimits(0, 0.01, 0.99);
      ChargeMag3Fit->SetParameter(1, 8000);
      ChargeMag3Fit->SetParameter(2, 2287.);
      ChargeMag3Fit->SetParameter(3, 4);
      ChargeMag3Fit->SetParameter(4, 7);
      ChargeMag3Fit->SetParLimits(3, 0, 20);
      ChargeMag3Fit->SetParLimits(4, 0, 20);
      ChargeMag3Fit->SetParameter(5, 10);
      ChargeMag3Fit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      ChargeMag3->SetMinimum(0.0001);
      ChargeMag3->GetXaxis()->CenterTitle(true);
      ChargeMag3->GetXaxis()->SetTitleSize(20);
      ChargeMag3->GetXaxis()->SetTitleFont(43);
      ChargeMag3->GetXaxis()->SetTitleOffset(1.5);
      ChargeMag3->GetXaxis()->SetLabelSize(0.05);
      ChargeMag3->GetYaxis()->SetTitleSize(20);
      ChargeMag3->GetYaxis()->SetTitleFont(43);
      ChargeMag3->GetYaxis()->SetLabelSize(0.05);
      ChargeMag3->Fit("ChargeMag3Fit", "E");

      SignalDGH.Form("%5.0f\n", ChargeMag3Fit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", ChargeMag3Fit->GetParError(1));
      FractionDGH.Form("%5.3f\n", ChargeMag3Fit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", ChargeMag3Fit->GetParError(0));
      muDGH.Form("%5.3f\n", ChargeMag3Fit->GetParameter(2));
      muErDGH.Form("%5.3f\n", ChargeMag3Fit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", ChargeMag3Fit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", ChargeMag3Fit->GetParError(3));
      rmsDGH.Form("%5.3f\n", ChargeMag3Fit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", ChargeMag3Fit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* ChargeMag3Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      ChargeMag3Pull->SetStats(0);
      ChargeMag3Pull->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      ChargeMag3Pull->GetXaxis()->SetTitleSize(20);
      ChargeMag3Pull->GetXaxis()->SetTitleFont(43);
      ChargeMag3Pull->GetXaxis()->SetTitleOffset(4);
      ChargeMag3Pull->GetXaxis()->SetLabelSize(0.1);
      ChargeMag3Pull->GetYaxis()->SetTitle("Pull");
      ChargeMag3Pull->GetYaxis()->CenterTitle(true);
      ChargeMag3Pull->GetXaxis()->CenterTitle(true);
      ChargeMag3Pull->GetYaxis()->SetTitleSize(20);
      ChargeMag3Pull->GetYaxis()->SetTitleFont(43);
      ChargeMag3Pull->GetYaxis()->SetLabelSize(0.1);
      ChargeMag3Pull->SetMinimum(-5.1);
      ChargeMag3Pull->SetMaximum(5.1);
      ChargeMag3Pull->SetFillColor(kBlue);
      ChargeMag3Pull->SetLineColor(kBlue);
      ChargeMag3Pull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = ChargeMag3->GetBinCenter(i);
      Double_t val = ChargeMag3Fit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (ChargeMag3->GetBinContent(i)-val)/sigma;
      ChargeMag3Pull->SetBinContent(i,pull);
      }
      ChargeMag3Pull->Draw();

      c1->SaveAs("LcMChargeMag3.pdf");

      TF1 *ChargeMag4Fit = new TF1("ChargeMag4Fit",DoubleGaussExp,2222, 2352,7);
      ChargeMag4Fit->SetParameter(0, 0.4);
      ChargeMag4Fit->SetParLimits(0, 0.01, 0.99);
      ChargeMag4Fit->SetParameter(1, 8000);
      ChargeMag4Fit->SetParameter(2, 2287.);
      ChargeMag4Fit->SetParameter(3, 4);
      ChargeMag4Fit->SetParameter(4, 7);
      ChargeMag4Fit->SetParLimits(3, 0, 20);
      ChargeMag4Fit->SetParLimits(4, 0, 20);
      ChargeMag4Fit->SetParameter(5, 10);
      ChargeMag4Fit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      ChargeMag4->SetMinimum(0.0001);
      ChargeMag4->GetXaxis()->CenterTitle(true);
      ChargeMag4->GetXaxis()->SetTitleSize(20);
      ChargeMag4->GetXaxis()->SetTitleFont(43);
      ChargeMag4->GetXaxis()->SetTitleOffset(1.5);
      ChargeMag4->GetXaxis()->SetLabelSize(0.05);
      ChargeMag4->GetYaxis()->SetTitleSize(20);
      ChargeMag4->GetYaxis()->SetTitleFont(43);
      ChargeMag4->GetYaxis()->SetLabelSize(0.05);
      ChargeMag4->Fit("ChargeMag4Fit", "E");

      SignalDGH.Form("%5.0f\n", ChargeMag4Fit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", ChargeMag4Fit->GetParError(1));
      FractionDGH.Form("%5.3f\n", ChargeMag4Fit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", ChargeMag4Fit->GetParError(0));
      muDGH.Form("%5.3f\n", ChargeMag4Fit->GetParameter(2));
      muErDGH.Form("%5.3f\n", ChargeMag4Fit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", ChargeMag4Fit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", ChargeMag4Fit->GetParError(3));
      rmsDGH.Form("%5.3f\n", ChargeMag4Fit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", ChargeMag4Fit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* ChargeMag4Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      ChargeMag4Pull->SetStats(0);
      ChargeMag4Pull->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      ChargeMag4Pull->GetXaxis()->SetTitleSize(20);
      ChargeMag4Pull->GetXaxis()->SetTitleFont(43);
      ChargeMag4Pull->GetXaxis()->SetTitleOffset(4);
      ChargeMag4Pull->GetXaxis()->SetLabelSize(0.1);
      ChargeMag4Pull->GetYaxis()->SetTitle("Pull");
      ChargeMag4Pull->GetYaxis()->CenterTitle(true);
      ChargeMag4Pull->GetXaxis()->CenterTitle(true);
      ChargeMag4Pull->GetYaxis()->SetTitleSize(20);
      ChargeMag4Pull->GetYaxis()->SetTitleFont(43);
      ChargeMag4Pull->GetYaxis()->SetLabelSize(0.1);
      ChargeMag4Pull->SetMinimum(-5.1);
      ChargeMag4Pull->SetMaximum(5.1);
      ChargeMag4Pull->SetFillColor(kBlue);
      ChargeMag4Pull->SetLineColor(kBlue);
      ChargeMag4Pull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = ChargeMag4->GetBinCenter(i);
      Double_t val = ChargeMag4Fit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (ChargeMag4->GetBinContent(i)-val)/sigma;
      ChargeMag4Pull->SetBinContent(i,pull);
      }
      ChargeMag4Pull->Draw();

      c1->SaveAs("LcMChargeMag4.pdf");


            const Int_t n = 4;
            Double_t x[n] = {1,2,3,4};
            Double_t xerr[n] = {0,0,0,0};
            TString ChargeMagchi2val;

            grid->cd();
            grid->SetGridy();
            grid->SetLeftMargin(0.15);
            grid->SetBottomMargin(0.15);
            lt->SetTextSize(0.04);
            lt->SetTextColor(2);

            double ChargeMag1 = ChargeMag1Fit->GetParameter(2);
            double ChargeMag2 = ChargeMag2Fit->GetParameter(2);
            double ChargeMag3 = ChargeMag3Fit->GetParameter(2);
            double ChargeMag4 = ChargeMag4Fit->GetParameter(2);

            double ChargeMagerr1 = ChargeMag1Fit->GetParError(2);
            double ChargeMagerr2 = ChargeMag2Fit->GetParError(2);
            double ChargeMagerr3 = ChargeMag3Fit->GetParError(2);
            double ChargeMagerr4 = ChargeMag4Fit->GetParError(2);

            double ChargeMagAvG = ((ChargeMag1 + ChargeMag2 + ChargeMag3 + ChargeMag4)/n);
            Double_t ChargeMag[n] = {ChargeMag1 - ChargeMagAvG,ChargeMag2 - ChargeMagAvG, ChargeMag3 - ChargeMagAvG,ChargeMag4 - ChargeMagAvG};
            Double_t ChargeMagerr[n] = {ChargeMagerr1,ChargeMagerr2,ChargeMagerr3,ChargeMagerr4};

            double ChargeMagchi2pdf = ((abs(ChargeMag[0])/ChargeMagerr[0])*(abs(ChargeMag[0])/ChargeMagerr[0]) + (abs(ChargeMag[1])/ChargeMagerr[1])*(abs(ChargeMag[1])/ChargeMagerr[1]) + (abs(ChargeMag[2])/ChargeMagerr[2])*(abs(ChargeMag[2])/ChargeMagerr[2]) + (abs(ChargeMag[3])/ChargeMagerr[3])*(abs(ChargeMag[3])/ChargeMagerr[3]))/(n-1);
            ChargeMagchi2val.Form("%5.3f\n", ChargeMagchi2pdf);
            double ChargeMagError = 0;
            if (ChargeMagchi2pdf > 1){
            ChargeMagError = 0.013 * TMath::Sqrt(ChargeMagchi2pdf - 1);
            }

      Double_t D1[2] = {1,4.8};
      Double_t ChargeMagD1[2] = {ChargeMag[0], ChargeMag[2]};
      Double_t ChargeMagD1Err[2] = {ChargeMagerr[0], ChargeMagerr[2]};
      Double_t D2[2] = {1.2,5};
      Double_t ChargeMagD2[2] = {ChargeMag[1], ChargeMag[3]};
      Double_t ChargeMagD2Err[2] = {ChargeMagerr[1], ChargeMagerr[3]};

      g1 = new TGraphErrors(2, D1, ChargeMagD1, xerr, ChargeMagD1Err);
      g2 = new TGraphErrors(2, D2, ChargeMagD2, xerr, ChargeMagD2Err);

      g1->SetTitle("#Lambda_{c}^{+}");
      g2->SetTitle("#bar{#Lambda_{c}^{-}}");

      g1->SetMarkerColor(kRed); g1->SetMarkerStyle(20); g1->SetMarkerSize(1);
      g2->SetMarkerColor(kBlue); g2->SetMarkerStyle(21); g2->SetMarkerSize(1);
      g1->GetXaxis()->CenterTitle(true);
      g1->GetXaxis()->SetTitleSize(20);
      g1->GetXaxis()->SetTitleFont(43);
      g1->GetXaxis()->SetTitleOffset(1.5);
      g1->GetXaxis()->SetLabelSize(0.075);
      g1->GetYaxis()->SetTitleSize(20);
      g1->GetYaxis()->SetTitleFont(43);
      g1->GetYaxis()->SetLabelSize(0.05);
      g1->GetXaxis()->SetNdivisions(12);
      g1->GetXaxis()->SetTitle("#Lambda_{c}^{+}/#bar{#Lambda_{c}^{-}} & Magnet Orientation");
      MassAVG.Form("%4.3f\n", ChargeMagAvG);
      g1->GetYaxis()->SetTitle("Measured Mass - "+MassAVG+" [MeV]");
      g1->GetXaxis()->SetAlphanumeric();
      g1->GetXaxis()->SetBinLabel(10, "MagDown");
      g1->GetXaxis()->SetBinLabel(90, "MagUp");
      g1->GetXaxis()->LabelsOption("h");

      g1->SetMinimum(-0.08);
      g1->SetMaximum(0.08);
      g1->Draw("ap");
      g2->Draw("PSAME");
      gPad->BuildLegend(0.40,0.15,0.60,0.30);

            lt->DrawLatexNDC(0.25, 0.83, "LHCb Preliminary");
            lt->DrawLatexNDC(0.25, 0.78, "#chi^2/NDF ="+ChargeMagchi2val);
            g1->SetTitle("");
            grid->SaveAs("gChargeMagMulti.pdf");
}
