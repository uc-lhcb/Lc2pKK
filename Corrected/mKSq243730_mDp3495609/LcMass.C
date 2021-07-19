#define LcMass_cxx
#include "LcMass.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

const TString files_dir_magup = "/share/lazy/D2KKPi_MomentumScaled/D2KKPi_MagUp_mKSq243730_mDpSq3495609_Files/";
const TString files_dir_magdown = "/share/lazy/D2KKPi_MomentumScaled/D2KKPi_MagDown_mKSq243730_mDpSq3495609_Files/";

//mKSq mass is dependent on which correction hists we use.
const double mKSq = 243730/1.0E6; // GeV^2
const double mPSq = (938.272)*(938.272)/1.0E6; // GeV^2

TH1D * FinalMass = nullptr;
TH1D * PolarityMagUp = nullptr;
TH1D * PolarityMagDown = nullptr;
TH1D * Particle = nullptr;
TH1D * AntiParticle = nullptr;
TH1D * LcP1 = nullptr;
TH1D * LcP2 = nullptr;
TH1D * LcP3 = nullptr;
TH1D * LcP4 = nullptr;
TH1D * LcTau1 = nullptr;
TH1D * LcTau2 = nullptr;
TH1D * LcTau3 = nullptr;

TFile * File = nullptr;
TCanvas * c1 = nullptr;

const int NDau = 3;
const int NCorr = 4;

TH2D *ref_alpha_magup[NCorr];
TH2D *ref_epsilon_magup[NCorr];
TFile *fref_magup[NCorr];

TH2D *ref_alpha_magdown[NCorr];
TH2D *ref_epsilon_magdown[NCorr];
TFile *fref_magdown[NCorr];

TString str;

void LcMass::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void LcMass::SlaveBegin(TTree * /*tree*/)
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

   FinalMass = new TH1D("", "", 260, 2222, 2352);
   FinalMass->GetXaxis()->SetTitle("Mass of p^{+}K^{+}K^{-} [MeV]");
   FinalMass->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   PolarityMagUp = new TH1D("", "", 260, 2222, 2352);
   PolarityMagUp->GetXaxis()->SetTitle("Mass of p^{+}K^{+}K^{-} [MeV]");
   PolarityMagUp->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   PolarityMagDown = new TH1D("", "", 260, 2222, 2352);
   PolarityMagDown->GetXaxis()->SetTitle("Mass of p^{+}K^{+}K^{-} [MeV]");
   PolarityMagDown->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   Particle = new TH1D("", "", 260, 2222, 2352);
   Particle->GetXaxis()->SetTitle("Mass of p^{+}K^{+}K^{-} [MeV]");
   Particle->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   AntiParticle = new TH1D("", "", 260, 2222, 2352);
   AntiParticle->GetXaxis()->SetTitle("Mass of p^{+}K^{+}K^{-} [MeV]");
   AntiParticle->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   LcP1 = new TH1D("", "", 260, 2222, 2352);
   LcP1->GetXaxis()->SetTitle("Mass of p^{+}K^{+}K^{-} [MeV]");
   LcP1->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   LcP2 = new TH1D("", "", 260, 2222, 2352);
   LcP2->GetXaxis()->SetTitle("Mass of p^{+}K^{+}K^{-} [MeV]");
   LcP2->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   LcP3 = new TH1D("", "", 260, 2222, 2352);
   LcP3->GetXaxis()->SetTitle("Mass of p^{+}K^{+}K^{-} [MeV]");
   LcP3->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   LcP4 = new TH1D("", "", 260, 2222, 2352);
   LcP4->GetXaxis()->SetTitle("Mass of p^{+}K^{+}K^{-} [MeV]");
   LcP4->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   LcTau1 = new TH1D("", "", 260, 2222, 2352);
   LcTau1->GetXaxis()->SetTitle("Mass of p^{+}K^{+}K^{-} [MeV]");
   LcTau1->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   LcTau2 = new TH1D("", "", 260, 2222, 2352);
   LcTau2->GetXaxis()->SetTitle("Mass of p^{+}K^{+}K^{-} [MeV]");
   LcTau2->GetYaxis()->SetTitle("Events Per 1/2 MeV");

   LcTau3 = new TH1D("", "", 260, 2222, 2352);
   LcTau3->GetXaxis()->SetTitle("Mass of p^{+}K^{+}K^{-} [MeV]");
   LcTau3->GetYaxis()->SetTitle("Events Per 1/2 MeV");

     File = new TFile("LcMass.root", "RECREATE");
     gFile = File;
      c1 = new TCanvas("canvas", "Test Canvas");
}

Bool_t LcMass::Process(Long64_t entry)
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

       bool LcP1Reg = (
       (*Lc_P < 47500)
       );

       bool LcP2Reg = (
       (*Lc_P > 47500) && (*Lc_P < 62500)
       );

       bool LcP3Reg = (
       (*Lc_P > 62500) && (*Lc_P < 81000)
       );

       bool LcP4Reg = (
       (*Lc_P > 81000) && (*Lc_P < 110000)
       );

       bool LcTau1Reg = (
        (*Lc_TAU < 0.00057)
       );

       bool LcTau2Reg = (
       (*Lc_TAU > 0.00057) && (*Lc_TAU < 0.00076)
       );

       bool LcTau3Reg = (
       (*Lc_TAU > 0.00076) && (*Lc_TAU < 0.0013)
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

FinalMass->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));

         if(MagDown){
 PolarityMagDown->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
         }
         if(MagUp){
 PolarityMagUp->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
         }

         if(Particles){
 Particle->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
         }

         if(AntiParticles){
 AntiParticle->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
         }

         if(LcP1Reg){
 LcP1->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
         }

         if(LcP2Reg){
 LcP2->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
         }

         if(LcP3Reg){
 LcP3->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
         }

         if(LcP4Reg){
 LcP4->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
         }

         if(LcTau1Reg){
 LcTau1->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
         }

         if(LcTau2Reg){
 LcTau2->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
         }

         if(LcTau3Reg){
 LcTau3->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
         }
       }

   return kTRUE;
}

void LcMass::SlaveTerminate()
{

}

void LcMass::Terminate()
{
c1->cd();

FinalMass->SetMinimum(0.0001);
FinalMass->GetXaxis()->CenterTitle(true);
FinalMass->GetXaxis()->SetTitleSize(20);
FinalMass->GetXaxis()->SetTitleFont(43);
FinalMass->GetXaxis()->SetTitleOffset(1.5);
FinalMass->GetXaxis()->SetLabelSize(0.05);
FinalMass->GetYaxis()->SetTitleSize(20);
FinalMass->GetYaxis()->SetTitleFont(43);
FinalMass->GetYaxis()->SetLabelSize(0.05);
FinalMass->Write("Lc_M");

PolarityMagDown->SetMinimum(0.0001);
PolarityMagDown->GetXaxis()->CenterTitle(true);
PolarityMagDown->GetXaxis()->SetTitleSize(20);
PolarityMagDown->GetXaxis()->SetTitleFont(43);
PolarityMagDown->GetXaxis()->SetTitleOffset(1.5);
PolarityMagDown->GetXaxis()->SetLabelSize(0.05);
PolarityMagDown->GetYaxis()->SetTitleSize(20);
PolarityMagDown->GetYaxis()->SetTitleFont(43);
PolarityMagDown->GetYaxis()->SetLabelSize(0.05);
PolarityMagDown->Write("Lc_M_MagDown");

PolarityMagUp->SetMinimum(0.0001);
PolarityMagUp->GetXaxis()->CenterTitle(true);
PolarityMagUp->GetXaxis()->SetTitleSize(20);
PolarityMagUp->GetXaxis()->SetTitleFont(43);
PolarityMagUp->GetXaxis()->SetTitleOffset(1.5);
PolarityMagUp->GetXaxis()->SetLabelSize(0.05);
PolarityMagUp->GetYaxis()->SetTitleSize(20);
PolarityMagUp->GetYaxis()->SetTitleFont(43);
PolarityMagUp->GetYaxis()->SetLabelSize(0.05);
PolarityMagUp->Write("Lc_M_MagUp");

Particle->SetMinimum(0.0001);
Particle->GetXaxis()->CenterTitle(true);
Particle->GetXaxis()->SetTitleSize(20);
Particle->GetXaxis()->SetTitleFont(43);
Particle->GetXaxis()->SetTitleOffset(1.5);
Particle->GetXaxis()->SetLabelSize(0.05);
Particle->GetYaxis()->SetTitleSize(20);
Particle->GetYaxis()->SetTitleFont(43);
Particle->GetYaxis()->SetLabelSize(0.05);
Particle->Write("Lc_M_Particle");

AntiParticle->SetMinimum(0.0001);
AntiParticle->GetXaxis()->CenterTitle(true);
AntiParticle->GetXaxis()->SetTitleSize(20);
AntiParticle->GetXaxis()->SetTitleFont(43);
AntiParticle->GetXaxis()->SetTitleOffset(1.5);
AntiParticle->GetXaxis()->SetLabelSize(0.05);
AntiParticle->GetYaxis()->SetTitleSize(20);
AntiParticle->GetYaxis()->SetTitleFont(43);
AntiParticle->GetYaxis()->SetLabelSize(0.05);
AntiParticle->Write("Lc_M_AntiParticle");

LcP1->SetMinimum(0.0001);
LcP1->GetXaxis()->CenterTitle(true);
LcP1->GetXaxis()->SetTitleSize(20);
LcP1->GetXaxis()->SetTitleFont(43);
LcP1->GetXaxis()->SetTitleOffset(1.5);
LcP1->GetXaxis()->SetLabelSize(0.05);
LcP1->GetYaxis()->SetTitleSize(20);
LcP1->GetYaxis()->SetTitleFont(43);
LcP1->GetYaxis()->SetLabelSize(0.05);
LcP1->Write("Lc_M_LcP1");

LcP2->SetMinimum(0.0001);
LcP2->GetXaxis()->CenterTitle(true);
LcP2->GetXaxis()->SetTitleSize(20);
LcP2->GetXaxis()->SetTitleFont(43);
LcP2->GetXaxis()->SetTitleOffset(1.5);
LcP2->GetXaxis()->SetLabelSize(0.05);
LcP2->GetYaxis()->SetTitleSize(20);
LcP2->GetYaxis()->SetTitleFont(43);
LcP2->GetYaxis()->SetLabelSize(0.05);
LcP2->Write("Lc_M_LcP2");

LcP3->SetMinimum(0.0001);
LcP3->GetXaxis()->CenterTitle(true);
LcP3->GetXaxis()->SetTitleSize(20);
LcP3->GetXaxis()->SetTitleFont(43);
LcP3->GetXaxis()->SetTitleOffset(1.5);
LcP3->GetXaxis()->SetLabelSize(0.05);
LcP3->GetYaxis()->SetTitleSize(20);
LcP3->GetYaxis()->SetTitleFont(43);
LcP3->GetYaxis()->SetLabelSize(0.05);
LcP3->Write("Lc_M_LcP3");

LcP4->SetMinimum(0.0001);
LcP4->GetXaxis()->CenterTitle(true);
LcP4->GetXaxis()->SetTitleSize(20);
LcP4->GetXaxis()->SetTitleFont(43);
LcP4->GetXaxis()->SetTitleOffset(1.5);
LcP4->GetXaxis()->SetLabelSize(0.05);
LcP4->GetYaxis()->SetTitleSize(20);
LcP4->GetYaxis()->SetTitleFont(43);
LcP4->GetYaxis()->SetLabelSize(0.05);
LcP4->Write("Lc_M_LcP4");

LcTau1->SetMinimum(0.0001);
LcTau1->GetXaxis()->CenterTitle(true);
LcTau1->GetXaxis()->SetTitleSize(20);
LcTau1->GetXaxis()->SetTitleFont(43);
LcTau1->GetXaxis()->SetTitleOffset(1.5);
LcTau1->GetXaxis()->SetLabelSize(0.05);
LcTau1->GetYaxis()->SetTitleSize(20);
LcTau1->GetYaxis()->SetTitleFont(43);
LcTau1->GetYaxis()->SetLabelSize(0.05);
LcTau1->Write("Lc_M_LcTau1");

LcTau2->SetMinimum(0.0001);
LcTau2->GetXaxis()->CenterTitle(true);
LcTau2->GetXaxis()->SetTitleSize(20);
LcTau2->GetXaxis()->SetTitleFont(43);
LcTau2->GetXaxis()->SetTitleOffset(1.5);
LcTau2->GetXaxis()->SetLabelSize(0.05);
LcTau2->GetYaxis()->SetTitleSize(20);
LcTau2->GetYaxis()->SetTitleFont(43);
LcTau2->GetYaxis()->SetLabelSize(0.05);
LcTau2->Write("Lc_M_LcTau2");

LcTau3->SetMinimum(0.0001);
LcTau3->GetXaxis()->CenterTitle(true);
LcTau3->GetXaxis()->SetTitleSize(20);
LcTau3->GetXaxis()->SetTitleFont(43);
LcTau3->GetXaxis()->SetTitleOffset(1.5);
LcTau3->GetXaxis()->SetLabelSize(0.05);
LcTau3->GetYaxis()->SetTitleSize(20);
LcTau3->GetYaxis()->SetTitleFont(43);
LcTau3->GetYaxis()->SetLabelSize(0.05);
LcTau3->Write("Lc_M_LcTau3");

}
