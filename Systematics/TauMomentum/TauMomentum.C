#define TauMomentum_cxx
#include "TauMomentum.h"

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

TH2D * TAUMomentumSignal = nullptr;
TH2D * TAUMomentumSignalEstimate = nullptr;
TH2D * TAUMomentumBackground = nullptr;

TH1D * LcPTau1 = nullptr;
TH1D * LcPTau2 = nullptr;
TH1D * LcPTau3 = nullptr;
TH1D * LcPTau4 = nullptr;
TH1D * LcPTau5 = nullptr;
TH1D * LcPTau6 = nullptr;
TH1D * LcPTau7 = nullptr;
TH1D * LcPTau8 = nullptr;
TH1D * LcPTau9 = nullptr;
TH1D * LcPTau10 = nullptr;
TH1D * LcPTau11 = nullptr;
TH1D * LcPTau12 = nullptr;

TMultiGraph * gLcPTauMulti = nullptr;
TGraphErrors * g0 = nullptr;
TGraphErrors * g1 = nullptr;
TGraphErrors * g2 = nullptr;
TGraphErrors * g3 = nullptr;
TGraphErrors * g4 = nullptr;

TFile * File = nullptr;
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

void TauMomentum::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void TauMomentum::SlaveBegin(TTree * /*tree*/)
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

   TAUMomentumSignal = new TH2D("", "", 100, 0.0003, 0.0013, 100, 20000., 110000);
   TAUMomentumSignal->GetXaxis()->SetTitle("#TAU[ns]");
   TAUMomentumSignal->GetYaxis()->SetTitle("#Lambda_{c} Momentum[MeV]");
   TAUMomentumSignal->GetZaxis()->SetTitle("Events");

   TAUMomentumBackground = new TH2D("", "", 100, 0.0003, 0.0013, 100, 20000., 110000);
   TAUMomentumBackground->GetXaxis()->SetTitle("#TAU[ns]");
   TAUMomentumBackground->GetYaxis()->SetTitle("#Lambda_{c} Momentum[MeV]");
   TAUMomentumBackground->GetZaxis()->SetTitle("Events");

   TAUMomentumSignalEstimate = new TH2D("", "", 100, 0, 0.0013, 100, 20000., 110000);
   TAUMomentumSignalEstimate->GetXaxis()->SetTitle("#TAU[ns]");
   TAUMomentumSignalEstimate->GetYaxis()->SetTitle("#Lambda_{c} Momentum[MeV]");
   TAUMomentumSignalEstimate->GetZaxis()->SetTitle("Events");

   LcPTau1 = new TH1D("", "", 260, 2222, 2352);
   LcPTau1->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
   LcPTau1->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   LcPTau2 = new TH1D("", "", 260, 2222, 2352);
   LcPTau2->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
   LcPTau2->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   LcPTau3 = new TH1D("", "", 260, 2222, 2352);
   LcPTau3->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
   LcPTau3->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   LcPTau4 = new TH1D("", "", 260, 2222, 2352);
   LcPTau4->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
   LcPTau4->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   LcPTau5 = new TH1D("", "", 260, 2222, 2352);
   LcPTau5->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
   LcPTau5->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   LcPTau6 = new TH1D("", "", 260, 2222, 2352);
   LcPTau6->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
   LcPTau6->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   LcPTau7 = new TH1D("", "", 260, 2222, 2352);
   LcPTau7->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
   LcPTau7->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   LcPTau8 = new TH1D("", "", 260, 2222, 2352);
   LcPTau8->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
   LcPTau8->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   LcPTau9 = new TH1D("", "", 260, 2222, 2352);
   LcPTau9->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
   LcPTau9->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   LcPTau10 = new TH1D("", "", 260, 2222, 2352);
   LcPTau10->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
   LcPTau10->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   LcPTau11 = new TH1D("", "", 260, 2222, 2352);
   LcPTau11->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
   LcPTau11->GetYaxis()->SetTitle("Entries / (0.5 MeV)");
   LcPTau12 = new TH1D("", "", 260, 2222, 2352);
   LcPTau12->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
   LcPTau12->GetYaxis()->SetTitle("Entries / (0.5 MeV)");

   File = new TFile("TauMomentum.root", "RECREATE");
   gFile = File;

    c1 = new TCanvas("canvas", "Test Canvas");
      grid = new TCanvas("grid", "Grid Canvas");
}

Bool_t TauMomentum::Process(Long64_t entry)
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


         bool LcP1Req = (
           (*Lc_P < 51000)
         );

         bool LcP2Req = (
           (*Lc_P > 51000) && (*Lc_P < 69000)
         );

         bool LcP3Req = (
           (*Lc_P > 69000) && (*Lc_P < 97000)
         );

         bool LcP4Req = (
         (*Lc_P > 97000)
         );

         bool LcTau1Req = (
          (*Lc_TAU < 0.00057)
         );

         bool LcTau2Req = (
         (*Lc_TAU > 0.00057) && (*Lc_TAU < 0.00076)
         );

         bool LcTau3Req = (
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

           bool SignalRegion = *Lc_M > 2275.4 && *Lc_M < 2299.4;
           bool BackgroundRegion = (*Lc_M > 2222. && *Lc_M < 2270.) || (*Lc_M > 2304. && *Lc_M < 2352.);

           if(SignalRegion){
             TAUMomentumSignal->Fill(*Lc_TAU, *Lc_P);
           }

           if(BackgroundRegion){
             TAUMomentumBackground->Fill(*Lc_TAU, *Lc_P);
           }

           if(LcP1Req && LcTau1Req){
             LcPTau1->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
           }

           if(LcP1Req && LcTau2Req){
             LcPTau2->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
           }

           if(LcP1Req && LcTau3Req){
             LcPTau3->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
           }

           if(LcP2Req && LcTau1Req){
             LcPTau4->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
           }

           if(LcP2Req && LcTau2Req){
             LcPTau5->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
           }

           if(LcP2Req && LcTau3Req){
             LcPTau6->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
           }

           if(LcP3Req && LcTau1Req){
             LcPTau7->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
           }

           if(LcP3Req && LcTau2Req){
             LcPTau8->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
           }

           if(LcP3Req && LcTau3Req){
             LcPTau9->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
           }

           if(LcP4Req && LcTau1Req){
             LcPTau10->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
           }

           if(LcP4Req && LcTau2Req){
             LcPTau11->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
           }

           if(LcP4Req && LcTau3Req){
             LcPTau12->Fill(TMath::Sqrt(*Lc_M * *Lc_M + deltaMSq[0] + deltaMSq[1] + deltaMSq[2] + deltaMSq[3]));
           }
         }

   return kTRUE;
}

void TauMomentum::SlaveTerminate()
{
}

void TauMomentum::Terminate()
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

TAUMomentumSignalEstimate->Add(TAUMomentumSignal,TAUMomentumBackground,1.0,-0.25);

c1->SetBottomMargin(0.2);
c1->SetLeftMargin(0.15);
c1->SetRightMargin(0.15);

gStyle->SetOptStat(0);

TAUMomentumSignalEstimate->GetXaxis()->CenterTitle(true);
TAUMomentumSignalEstimate->GetXaxis()->SetTitleSize(20);
TAUMomentumSignalEstimate->GetXaxis()->SetTitleFont(43);
TAUMomentumSignalEstimate->GetXaxis()->SetTitleOffset(1.5);
TAUMomentumSignalEstimate->GetXaxis()->SetLabelSize(0.05);
TAUMomentumSignalEstimate->GetYaxis()->SetTitleSize(20);
TAUMomentumSignalEstimate->GetYaxis()->SetTitleFont(43);
TAUMomentumSignalEstimate->GetYaxis()->SetLabelSize(0.05);
TAUMomentumSignalEstimate->GetXaxis()->SetNdivisions(-6);
TAUMomentumSignalEstimate->GetZaxis()->SetTitleOffset(1);
TAUMomentumSignalEstimate->GetZaxis()->SetTitle("Signal Events");

TAUMomentumSignalEstimate->Draw("COLZ");
  c1->SaveAs("TAUMomentumSCOLZ.pdf");

TAUMomentumSignalEstimate->Draw("CONTZ");
  c1->SaveAs("TAUMomentumSCONTZ.pdf");

TAUMomentumSignalEstimate->Divide(TAUMomentumBackground);
TAUMomentumSignalEstimate->GetZaxis()->SetTitle("S/B");

TAUMomentumSignalEstimate->Draw("COLZ");
  c1->SaveAs("TAUMomentumSBCOLZ.pdf");

TAUMomentumSignalEstimate->Draw("CONTZ");
  c1->SaveAs("TAUMomentumSBCONTZ.pdf");

  c1->Clear();

    gStyle->SetOptStat(11);
    gStyle->SetStatW(0.25);
    gStyle->SetStatH(0.25);

    auto lt = new TLatex();
    lt->SetTextSize(0.048);

LcPTau1->SetLineWidth(2);
LcPTau2->SetLineWidth(2);
LcPTau3->SetLineWidth(2);
LcPTau4->SetLineWidth(2);
LcPTau5->SetLineWidth(2);
LcPTau6->SetLineWidth(2);
LcPTau7->SetLineWidth(2);
LcPTau8->SetLineWidth(2);
LcPTau9->SetLineWidth(2);
LcPTau10->SetLineWidth(2);
LcPTau11->SetLineWidth(2);
LcPTau12->SetLineWidth(2);

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

      TF1 *LcPTau1Fit = new TF1("LcPTau1Fit",DoubleGaussExp,2222, 2352,7);
      LcPTau1Fit->SetParameter(0, 0.4);
      LcPTau1Fit->SetParLimits(0, 0.01, 0.99);
      LcPTau1Fit->SetParameter(1, 8000);
      LcPTau1Fit->SetParameter(2, 2287.);
      LcPTau1Fit->SetParameter(3, 4);
      LcPTau1Fit->SetParameter(4, 7);
      LcPTau1Fit->SetParLimits(3, 0, 20);
      LcPTau1Fit->SetParLimits(4, 0, 20);
      LcPTau1Fit->SetParameter(5, 10);
      LcPTau1Fit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      LcPTau1->SetMinimum(0.0001);
      LcPTau1->GetXaxis()->CenterTitle(true);
      LcPTau1->GetXaxis()->SetTitleSize(20);
      LcPTau1->GetXaxis()->SetTitleFont(43);
      LcPTau1->GetXaxis()->SetTitleOffset(1.5);
      LcPTau1->GetXaxis()->SetLabelSize(0.05);
      LcPTau1->GetYaxis()->SetTitleSize(20);
      LcPTau1->GetYaxis()->SetTitleFont(43);
      LcPTau1->GetYaxis()->SetLabelSize(0.05);
      LcPTau1->Fit("LcPTau1Fit", "E");

      SignalDGH.Form("%5.0f\n", LcPTau1Fit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", LcPTau1Fit->GetParError(1));
      FractionDGH.Form("%5.3f\n", LcPTau1Fit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", LcPTau1Fit->GetParError(0));
      muDGH.Form("%5.3f\n", LcPTau1Fit->GetParameter(2));
      muErDGH.Form("%5.3f\n", LcPTau1Fit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", LcPTau1Fit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", LcPTau1Fit->GetParError(3));
      rmsDGH.Form("%5.3f\n", LcPTau1Fit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", LcPTau1Fit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* LcPTau1Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      LcPTau1Pull->SetStats(0);
      LcPTau1Pull->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      LcPTau1Pull->GetXaxis()->SetTitleSize(20);
      LcPTau1Pull->GetXaxis()->SetTitleFont(43);
      LcPTau1Pull->GetXaxis()->SetTitleOffset(4);
      LcPTau1Pull->GetXaxis()->SetLabelSize(0.1);
      LcPTau1Pull->GetYaxis()->SetTitle("Pull");
      LcPTau1Pull->GetYaxis()->CenterTitle(true);
      LcPTau1Pull->GetXaxis()->CenterTitle(true);
      LcPTau1Pull->GetYaxis()->SetTitleSize(20);
      LcPTau1Pull->GetYaxis()->SetTitleFont(43);
      LcPTau1Pull->GetYaxis()->SetLabelSize(0.1);
      LcPTau1Pull->SetMinimum(-5.1);
      LcPTau1Pull->SetMaximum(5.1);
      LcPTau1Pull->SetFillColor(kBlue);
      LcPTau1Pull->SetLineColor(kBlue);
      LcPTau1Pull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = LcPTau1->GetBinCenter(i);
      Double_t val = LcPTau1Fit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (LcPTau1->GetBinContent(i)-val)/sigma;
      LcPTau1Pull->SetBinContent(i,pull);
      }
      LcPTau1Pull->Draw();

      c1->SaveAs("LcMLcPTau1.pdf");

      TF1 *LcPTau2Fit = new TF1("LcPTau2Fit",DoubleGaussExp,2222, 2352,7);
      LcPTau2Fit->SetParameter(0, 0.4);
      LcPTau2Fit->SetParLimits(0, 0.01, 0.99);
      LcPTau2Fit->SetParameter(1, 8000);
      LcPTau2Fit->SetParameter(2, 2287.);
      LcPTau2Fit->SetParameter(3, 4);
      LcPTau2Fit->SetParameter(4, 7);
      LcPTau2Fit->SetParLimits(3, 0, 20);
      LcPTau2Fit->SetParLimits(4, 0, 20);
      LcPTau2Fit->SetParameter(5, 10);
      LcPTau2Fit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      LcPTau2->SetMinimum(0.0001);
      LcPTau2->GetXaxis()->CenterTitle(true);
      LcPTau2->GetXaxis()->SetTitleSize(20);
      LcPTau2->GetXaxis()->SetTitleFont(43);
      LcPTau2->GetXaxis()->SetTitleOffset(1.5);
      LcPTau2->GetXaxis()->SetLabelSize(0.05);
      LcPTau2->GetYaxis()->SetTitleSize(20);
      LcPTau2->GetYaxis()->SetTitleFont(43);
      LcPTau2->GetYaxis()->SetLabelSize(0.05);
      LcPTau2->Fit("LcPTau2Fit", "E");

      SignalDGH.Form("%5.0f\n", LcPTau2Fit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", LcPTau2Fit->GetParError(1));
      FractionDGH.Form("%5.3f\n", LcPTau2Fit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", LcPTau2Fit->GetParError(0));
      muDGH.Form("%5.3f\n", LcPTau2Fit->GetParameter(2));
      muErDGH.Form("%5.3f\n", LcPTau2Fit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", LcPTau2Fit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", LcPTau2Fit->GetParError(3));
      rmsDGH.Form("%5.3f\n", LcPTau2Fit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", LcPTau2Fit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* LcPTau2Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      LcPTau2Pull->SetStats(0);
      LcPTau2Pull->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      LcPTau2Pull->GetXaxis()->SetTitleSize(20);
      LcPTau2Pull->GetXaxis()->SetTitleFont(43);
      LcPTau2Pull->GetXaxis()->SetTitleOffset(4);
      LcPTau2Pull->GetXaxis()->SetLabelSize(0.1);
      LcPTau2Pull->GetYaxis()->SetTitle("Pull");
      LcPTau2Pull->GetYaxis()->CenterTitle(true);
      LcPTau2Pull->GetXaxis()->CenterTitle(true);
      LcPTau2Pull->GetYaxis()->SetTitleSize(20);
      LcPTau2Pull->GetYaxis()->SetTitleFont(43);
      LcPTau2Pull->GetYaxis()->SetLabelSize(0.1);
      LcPTau2Pull->SetMinimum(-5.1);
      LcPTau2Pull->SetMaximum(5.1);
      LcPTau2Pull->SetFillColor(kBlue);
      LcPTau2Pull->SetLineColor(kBlue);
      LcPTau2Pull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = LcPTau2->GetBinCenter(i);
      Double_t val = LcPTau2Fit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (LcPTau2->GetBinContent(i)-val)/sigma;
      LcPTau2Pull->SetBinContent(i,pull);
      }
      LcPTau2Pull->Draw();

      c1->SaveAs("LcMLcPTau2.pdf");

      TF1 *LcPTau3Fit = new TF1("LcPTau3Fit",DoubleGaussExp,2222, 2352,7);
      LcPTau3Fit->SetParameter(0, 0.4);
      LcPTau3Fit->SetParLimits(0, 0.01, 0.99);
      LcPTau3Fit->SetParameter(1, 8000);
      LcPTau3Fit->SetParameter(2, 2287.);
      LcPTau3Fit->SetParameter(3, 4);
      LcPTau3Fit->SetParameter(4, 7);
      LcPTau3Fit->SetParLimits(3, 0, 20);
      LcPTau3Fit->SetParLimits(4, 0, 20);
      LcPTau3Fit->SetParameter(5, 10);
      LcPTau3Fit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      LcPTau3->SetMinimum(0.0001);
      LcPTau3->GetXaxis()->CenterTitle(true);
      LcPTau3->GetXaxis()->SetTitleSize(20);
      LcPTau3->GetXaxis()->SetTitleFont(43);
      LcPTau3->GetXaxis()->SetTitleOffset(1.5);
      LcPTau3->GetXaxis()->SetLabelSize(0.05);
      LcPTau3->GetYaxis()->SetTitleSize(20);
      LcPTau3->GetYaxis()->SetTitleFont(43);
      LcPTau3->GetYaxis()->SetLabelSize(0.05);
      LcPTau3->Fit("LcPTau3Fit", "E");

      SignalDGH.Form("%5.0f\n", LcPTau3Fit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", LcPTau3Fit->GetParError(1));
      FractionDGH.Form("%5.3f\n", LcPTau3Fit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", LcPTau3Fit->GetParError(0));
      muDGH.Form("%5.3f\n", LcPTau3Fit->GetParameter(2));
      muErDGH.Form("%5.3f\n", LcPTau3Fit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", LcPTau3Fit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", LcPTau3Fit->GetParError(3));
      rmsDGH.Form("%5.3f\n", LcPTau3Fit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", LcPTau3Fit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* LcPTau3Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      LcPTau3Pull->SetStats(0);
      LcPTau3Pull->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      LcPTau3Pull->GetXaxis()->SetTitleSize(20);
      LcPTau3Pull->GetXaxis()->SetTitleFont(43);
      LcPTau3Pull->GetXaxis()->SetTitleOffset(4);
      LcPTau3Pull->GetXaxis()->SetLabelSize(0.1);
      LcPTau3Pull->GetYaxis()->SetTitle("Pull");
      LcPTau3Pull->GetYaxis()->CenterTitle(true);
      LcPTau3Pull->GetXaxis()->CenterTitle(true);
      LcPTau3Pull->GetYaxis()->SetTitleSize(20);
      LcPTau3Pull->GetYaxis()->SetTitleFont(43);
      LcPTau3Pull->GetYaxis()->SetLabelSize(0.1);
      LcPTau3Pull->SetMinimum(-5.1);
      LcPTau3Pull->SetMaximum(5.1);
      LcPTau3Pull->SetFillColor(kBlue);
      LcPTau3Pull->SetLineColor(kBlue);
      LcPTau3Pull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = LcPTau3->GetBinCenter(i);
      Double_t val = LcPTau3Fit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (LcPTau3->GetBinContent(i)-val)/sigma;
      LcPTau3Pull->SetBinContent(i,pull);
      }
      LcPTau3Pull->Draw();

      c1->SaveAs("LcMLcPTau3.pdf");

      TF1 *LcPTau4Fit = new TF1("LcPTau4Fit",DoubleGaussExp,2222, 2352,7);
      LcPTau4Fit->SetParameter(0, 0.4);
      LcPTau4Fit->SetParLimits(0, 0.01, 0.99);
      LcPTau4Fit->SetParameter(1, 8000);
      LcPTau4Fit->SetParameter(2, 2287.);
      LcPTau4Fit->SetParameter(3, 4);
      LcPTau4Fit->SetParameter(4, 7);
      LcPTau4Fit->SetParLimits(3, 0, 20);
      LcPTau4Fit->SetParLimits(4, 0, 20);
      LcPTau4Fit->SetParameter(5, 10);
      LcPTau4Fit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      LcPTau4->SetMinimum(0.0001);
      LcPTau4->GetXaxis()->CenterTitle(true);
      LcPTau4->GetXaxis()->SetTitleSize(20);
      LcPTau4->GetXaxis()->SetTitleFont(43);
      LcPTau4->GetXaxis()->SetTitleOffset(1.5);
      LcPTau4->GetXaxis()->SetLabelSize(0.05);
      LcPTau4->GetYaxis()->SetTitleSize(20);
      LcPTau4->GetYaxis()->SetTitleFont(43);
      LcPTau4->GetYaxis()->SetLabelSize(0.05);
      LcPTau4->Fit("LcPTau4Fit", "E");

      SignalDGH.Form("%5.0f\n", LcPTau4Fit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", LcPTau4Fit->GetParError(1));
      FractionDGH.Form("%5.3f\n", LcPTau4Fit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", LcPTau4Fit->GetParError(0));
      muDGH.Form("%5.3f\n", LcPTau4Fit->GetParameter(2));
      muErDGH.Form("%5.3f\n", LcPTau4Fit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", LcPTau4Fit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", LcPTau4Fit->GetParError(3));
      rmsDGH.Form("%5.3f\n", LcPTau4Fit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", LcPTau4Fit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* LcPTau4Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      LcPTau4Pull->SetStats(0);
      LcPTau4Pull->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      LcPTau4Pull->GetXaxis()->SetTitleSize(20);
      LcPTau4Pull->GetXaxis()->SetTitleFont(43);
      LcPTau4Pull->GetXaxis()->SetTitleOffset(4);
      LcPTau4Pull->GetXaxis()->SetLabelSize(0.1);
      LcPTau4Pull->GetYaxis()->SetTitle("Pull");
      LcPTau4Pull->GetYaxis()->CenterTitle(true);
      LcPTau4Pull->GetXaxis()->CenterTitle(true);
      LcPTau4Pull->GetYaxis()->SetTitleSize(20);
      LcPTau4Pull->GetYaxis()->SetTitleFont(43);
      LcPTau4Pull->GetYaxis()->SetLabelSize(0.1);
      LcPTau4Pull->SetMinimum(-5.1);
      LcPTau4Pull->SetMaximum(5.1);
      LcPTau4Pull->SetFillColor(kBlue);
      LcPTau4Pull->SetLineColor(kBlue);
      LcPTau4Pull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = LcPTau4->GetBinCenter(i);
      Double_t val = LcPTau4Fit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (LcPTau4->GetBinContent(i)-val)/sigma;
      LcPTau4Pull->SetBinContent(i,pull);
      }
      LcPTau4Pull->Draw();

      c1->SaveAs("LcMLcPTau4.pdf");

      TF1 *LcPTau5Fit = new TF1("LcPTau5Fit",DoubleGaussExp,2222, 2352,7);
      LcPTau5Fit->SetParameter(0, 0.4);
      LcPTau5Fit->SetParLimits(0, 0.01, 0.99);
      LcPTau5Fit->SetParameter(1, 8000);
      LcPTau5Fit->SetParameter(2, 2287.);
      LcPTau5Fit->SetParameter(3, 4);
      LcPTau5Fit->SetParameter(4, 7);
      LcPTau5Fit->SetParLimits(3, 0, 20);
      LcPTau5Fit->SetParLimits(4, 0, 20);
      LcPTau5Fit->SetParameter(5, 10);
      LcPTau5Fit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      LcPTau5->SetMinimum(0.0001);
      LcPTau5->GetXaxis()->CenterTitle(true);
      LcPTau5->GetXaxis()->SetTitleSize(20);
      LcPTau5->GetXaxis()->SetTitleFont(43);
      LcPTau5->GetXaxis()->SetTitleOffset(1.5);
      LcPTau5->GetXaxis()->SetLabelSize(0.05);
      LcPTau5->GetYaxis()->SetTitleSize(20);
      LcPTau5->GetYaxis()->SetTitleFont(43);
      LcPTau5->GetYaxis()->SetLabelSize(0.05);
      LcPTau5->Fit("LcPTau5Fit", "E");

      SignalDGH.Form("%5.0f\n", LcPTau5Fit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", LcPTau5Fit->GetParError(1));
      FractionDGH.Form("%5.3f\n", LcPTau5Fit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", LcPTau5Fit->GetParError(0));
      muDGH.Form("%5.3f\n", LcPTau5Fit->GetParameter(2));
      muErDGH.Form("%5.3f\n", LcPTau5Fit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", LcPTau5Fit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", LcPTau5Fit->GetParError(3));
      rmsDGH.Form("%5.3f\n", LcPTau5Fit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", LcPTau5Fit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* LcPTau5Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      LcPTau5Pull->SetStats(0);
      LcPTau5Pull->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      LcPTau5Pull->GetXaxis()->SetTitleSize(20);
      LcPTau5Pull->GetXaxis()->SetTitleFont(43);
      LcPTau5Pull->GetXaxis()->SetTitleOffset(4);
      LcPTau5Pull->GetXaxis()->SetLabelSize(0.1);
      LcPTau5Pull->GetYaxis()->SetTitle("Pull");
      LcPTau5Pull->GetYaxis()->CenterTitle(true);
      LcPTau5Pull->GetXaxis()->CenterTitle(true);
      LcPTau5Pull->GetYaxis()->SetTitleSize(20);
      LcPTau5Pull->GetYaxis()->SetTitleFont(43);
      LcPTau5Pull->GetYaxis()->SetLabelSize(0.1);
      LcPTau5Pull->SetMinimum(-5.1);
      LcPTau5Pull->SetMaximum(5.1);
      LcPTau5Pull->SetFillColor(kBlue);
      LcPTau5Pull->SetLineColor(kBlue);
      LcPTau5Pull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = LcPTau5->GetBinCenter(i);
      Double_t val = LcPTau5Fit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (LcPTau5->GetBinContent(i)-val)/sigma;
      LcPTau5Pull->SetBinContent(i,pull);
      }
      LcPTau5Pull->Draw();

      c1->SaveAs("LcMLcPTau5.pdf");

      TF1 *LcPTau6Fit = new TF1("LcPTau6Fit",DoubleGaussExp,2222, 2352,7);
      LcPTau6Fit->SetParameter(0, 0.4);
      LcPTau6Fit->SetParLimits(0, 0.01, 0.99);
      LcPTau6Fit->SetParameter(1, 8000);
      LcPTau6Fit->SetParameter(2, 2287.);
      LcPTau6Fit->SetParameter(3, 4);
      LcPTau6Fit->SetParameter(4, 7);
      LcPTau6Fit->SetParLimits(3, 0, 20);
      LcPTau6Fit->SetParLimits(4, 0, 20);
      LcPTau6Fit->SetParameter(5, 10);
      LcPTau6Fit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      LcPTau6->SetMinimum(0.0001);
      LcPTau6->GetXaxis()->CenterTitle(true);
      LcPTau6->GetXaxis()->SetTitleSize(20);
      LcPTau6->GetXaxis()->SetTitleFont(43);
      LcPTau6->GetXaxis()->SetTitleOffset(1.5);
      LcPTau6->GetXaxis()->SetLabelSize(0.05);
      LcPTau6->GetYaxis()->SetTitleSize(20);
      LcPTau6->GetYaxis()->SetTitleFont(43);
      LcPTau6->GetYaxis()->SetLabelSize(0.05);
      LcPTau6->Fit("LcPTau6Fit", "E");

      SignalDGH.Form("%5.0f\n", LcPTau6Fit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", LcPTau6Fit->GetParError(1));
      FractionDGH.Form("%5.3f\n", LcPTau6Fit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", LcPTau6Fit->GetParError(0));
      muDGH.Form("%5.3f\n", LcPTau6Fit->GetParameter(2));
      muErDGH.Form("%5.3f\n", LcPTau6Fit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", LcPTau6Fit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", LcPTau6Fit->GetParError(3));
      rmsDGH.Form("%5.3f\n", LcPTau6Fit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", LcPTau6Fit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* LcPTau6Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      LcPTau6Pull->SetStats(0);
      LcPTau6Pull->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      LcPTau6Pull->GetXaxis()->SetTitleSize(20);
      LcPTau6Pull->GetXaxis()->SetTitleFont(43);
      LcPTau6Pull->GetXaxis()->SetTitleOffset(4);
      LcPTau6Pull->GetXaxis()->SetLabelSize(0.1);
      LcPTau6Pull->GetYaxis()->SetTitle("Pull");
      LcPTau6Pull->GetYaxis()->CenterTitle(true);
      LcPTau6Pull->GetXaxis()->CenterTitle(true);
      LcPTau6Pull->GetYaxis()->SetTitleSize(20);
      LcPTau6Pull->GetYaxis()->SetTitleFont(43);
      LcPTau6Pull->GetYaxis()->SetLabelSize(0.1);
      LcPTau6Pull->SetMinimum(-5.1);
      LcPTau6Pull->SetMaximum(5.1);
      LcPTau6Pull->SetFillColor(kBlue);
      LcPTau6Pull->SetLineColor(kBlue);
      LcPTau6Pull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = LcPTau6->GetBinCenter(i);
      Double_t val = LcPTau6Fit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (LcPTau6->GetBinContent(i)-val)/sigma;
      LcPTau6Pull->SetBinContent(i,pull);
      }
      LcPTau6Pull->Draw();

      c1->SaveAs("LcMLcPTau6.pdf");

      TF1 *LcPTau7Fit = new TF1("LcPTau7Fit",DoubleGaussExp,2222, 2352,7);
      LcPTau7Fit->SetParameter(0, 0.4);
      LcPTau7Fit->SetParLimits(0, 0.01, 0.99);
      LcPTau7Fit->SetParameter(1, 8000);
      LcPTau7Fit->SetParameter(2, 2287.);
      LcPTau7Fit->SetParameter(3, 4);
      LcPTau7Fit->SetParameter(4, 7);
      LcPTau7Fit->SetParLimits(3, 0, 20);
      LcPTau7Fit->SetParLimits(4, 0, 20);
      LcPTau7Fit->SetParameter(5, 10);
      LcPTau7Fit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      LcPTau7->SetMinimum(0.0001);
      LcPTau7->GetXaxis()->CenterTitle(true);
      LcPTau7->GetXaxis()->SetTitleSize(20);
      LcPTau7->GetXaxis()->SetTitleFont(43);
      LcPTau7->GetXaxis()->SetTitleOffset(1.5);
      LcPTau7->GetXaxis()->SetLabelSize(0.05);
      LcPTau7->GetYaxis()->SetTitleSize(20);
      LcPTau7->GetYaxis()->SetTitleFont(43);
      LcPTau7->GetYaxis()->SetLabelSize(0.05);
      LcPTau7->Fit("LcPTau7Fit", "E");

      SignalDGH.Form("%5.0f\n", LcPTau7Fit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", LcPTau7Fit->GetParError(1));
      FractionDGH.Form("%5.3f\n", LcPTau7Fit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", LcPTau7Fit->GetParError(0));
      muDGH.Form("%5.3f\n", LcPTau7Fit->GetParameter(2));
      muErDGH.Form("%5.3f\n", LcPTau7Fit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", LcPTau7Fit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", LcPTau7Fit->GetParError(3));
      rmsDGH.Form("%5.3f\n", LcPTau7Fit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", LcPTau7Fit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* LcPTau7Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      LcPTau7Pull->SetStats(0);
      LcPTau7Pull->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      LcPTau7Pull->GetXaxis()->SetTitleSize(20);
      LcPTau7Pull->GetXaxis()->SetTitleFont(43);
      LcPTau7Pull->GetXaxis()->SetTitleOffset(4);
      LcPTau7Pull->GetXaxis()->SetLabelSize(0.1);
      LcPTau7Pull->GetYaxis()->SetTitle("Pull");
      LcPTau7Pull->GetYaxis()->CenterTitle(true);
      LcPTau7Pull->GetXaxis()->CenterTitle(true);
      LcPTau7Pull->GetYaxis()->SetTitleSize(20);
      LcPTau7Pull->GetYaxis()->SetTitleFont(43);
      LcPTau7Pull->GetYaxis()->SetLabelSize(0.1);
      LcPTau7Pull->SetMinimum(-5.1);
      LcPTau7Pull->SetMaximum(5.1);
      LcPTau7Pull->SetFillColor(kBlue);
      LcPTau7Pull->SetLineColor(kBlue);
      LcPTau7Pull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = LcPTau7->GetBinCenter(i);
      Double_t val = LcPTau7Fit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (LcPTau7->GetBinContent(i)-val)/sigma;
      LcPTau7Pull->SetBinContent(i,pull);
      }
      LcPTau7Pull->Draw();

      c1->SaveAs("LcMLcPTau7.pdf");

      TF1 *LcPTau8Fit = new TF1("LcPTau8Fit",DoubleGaussExp,2222, 2352,7);
      LcPTau8Fit->SetParameter(0, 0.4);
      LcPTau8Fit->SetParLimits(0, 0.01, 0.99);
      LcPTau8Fit->SetParameter(1, 8000);
      LcPTau8Fit->SetParameter(2, 2287.);
      LcPTau8Fit->SetParameter(3, 4);
      LcPTau8Fit->SetParameter(4, 7);
      LcPTau8Fit->SetParLimits(3, 0, 20);
      LcPTau8Fit->SetParLimits(4, 0, 20);
      LcPTau8Fit->SetParameter(5, 10);
      LcPTau8Fit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      LcPTau8->SetMinimum(0.0001);
      LcPTau8->GetXaxis()->CenterTitle(true);
      LcPTau8->GetXaxis()->SetTitleSize(20);
      LcPTau8->GetXaxis()->SetTitleFont(43);
      LcPTau8->GetXaxis()->SetTitleOffset(1.5);
      LcPTau8->GetXaxis()->SetLabelSize(0.05);
      LcPTau8->GetYaxis()->SetTitleSize(20);
      LcPTau8->GetYaxis()->SetTitleFont(43);
      LcPTau8->GetYaxis()->SetLabelSize(0.05);
      LcPTau8->Fit("LcPTau8Fit", "E");

      SignalDGH.Form("%5.0f\n", LcPTau8Fit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", LcPTau8Fit->GetParError(1));
      FractionDGH.Form("%5.3f\n", LcPTau8Fit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", LcPTau8Fit->GetParError(0));
      muDGH.Form("%5.3f\n", LcPTau8Fit->GetParameter(2));
      muErDGH.Form("%5.3f\n", LcPTau8Fit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", LcPTau8Fit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", LcPTau8Fit->GetParError(3));
      rmsDGH.Form("%5.3f\n", LcPTau8Fit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", LcPTau8Fit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* LcPTau8Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      LcPTau8Pull->SetStats(0);
      LcPTau8Pull->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      LcPTau8Pull->GetXaxis()->SetTitleSize(20);
      LcPTau8Pull->GetXaxis()->SetTitleFont(43);
      LcPTau8Pull->GetXaxis()->SetTitleOffset(4);
      LcPTau8Pull->GetXaxis()->SetLabelSize(0.1);
      LcPTau8Pull->GetYaxis()->SetTitle("Pull");
      LcPTau8Pull->GetYaxis()->CenterTitle(true);
      LcPTau8Pull->GetXaxis()->CenterTitle(true);
      LcPTau8Pull->GetYaxis()->SetTitleSize(20);
      LcPTau8Pull->GetYaxis()->SetTitleFont(43);
      LcPTau8Pull->GetYaxis()->SetLabelSize(0.1);
      LcPTau8Pull->SetMinimum(-5.1);
      LcPTau8Pull->SetMaximum(5.1);
      LcPTau8Pull->SetFillColor(kBlue);
      LcPTau8Pull->SetLineColor(kBlue);
      LcPTau8Pull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = LcPTau8->GetBinCenter(i);
      Double_t val = LcPTau8Fit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (LcPTau8->GetBinContent(i)-val)/sigma;
      LcPTau8Pull->SetBinContent(i,pull);
      }
      LcPTau8Pull->Draw();

      c1->SaveAs("LcMLcPTau8.pdf");

      TF1 *LcPTau9Fit = new TF1("LcPTau9Fit",DoubleGaussExp,2222, 2352,7);
      LcPTau9Fit->SetParameter(0, 0.4);
      LcPTau9Fit->SetParLimits(0, 0.01, 0.99);
      LcPTau9Fit->SetParameter(1, 8000);
      LcPTau9Fit->SetParameter(2, 2287.);
      LcPTau9Fit->SetParameter(3, 4);
      LcPTau9Fit->SetParameter(4, 7);
      LcPTau9Fit->SetParLimits(3, 0, 20);
      LcPTau9Fit->SetParLimits(4, 0, 20);
      LcPTau9Fit->SetParameter(5, 10);
      LcPTau9Fit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      LcPTau9->SetMinimum(0.0001);
      LcPTau9->GetXaxis()->CenterTitle(true);
      LcPTau9->GetXaxis()->SetTitleSize(20);
      LcPTau9->GetXaxis()->SetTitleFont(43);
      LcPTau9->GetXaxis()->SetTitleOffset(1.5);
      LcPTau9->GetXaxis()->SetLabelSize(0.05);
      LcPTau9->GetYaxis()->SetTitleSize(20);
      LcPTau9->GetYaxis()->SetTitleFont(43);
      LcPTau9->GetYaxis()->SetLabelSize(0.05);
      LcPTau9->Fit("LcPTau9Fit", "E");

      SignalDGH.Form("%5.0f\n", LcPTau9Fit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", LcPTau9Fit->GetParError(1));
      FractionDGH.Form("%5.3f\n", LcPTau9Fit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", LcPTau9Fit->GetParError(0));
      muDGH.Form("%5.3f\n", LcPTau9Fit->GetParameter(2));
      muErDGH.Form("%5.3f\n", LcPTau9Fit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", LcPTau9Fit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", LcPTau9Fit->GetParError(3));
      rmsDGH.Form("%5.3f\n", LcPTau9Fit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", LcPTau9Fit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* LcPTau9Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      LcPTau9Pull->SetStats(0);
      LcPTau9Pull->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      LcPTau9Pull->GetXaxis()->SetTitleSize(20);
      LcPTau9Pull->GetXaxis()->SetTitleFont(43);
      LcPTau9Pull->GetXaxis()->SetTitleOffset(4);
      LcPTau9Pull->GetXaxis()->SetLabelSize(0.1);
      LcPTau9Pull->GetYaxis()->SetTitle("Pull");
      LcPTau9Pull->GetYaxis()->CenterTitle(true);
      LcPTau9Pull->GetXaxis()->CenterTitle(true);
      LcPTau9Pull->GetYaxis()->SetTitleSize(20);
      LcPTau9Pull->GetYaxis()->SetTitleFont(43);
      LcPTau9Pull->GetYaxis()->SetLabelSize(0.1);
      LcPTau9Pull->SetMinimum(-5.1);
      LcPTau9Pull->SetMaximum(5.1);
      LcPTau9Pull->SetFillColor(kBlue);
      LcPTau9Pull->SetLineColor(kBlue);
      LcPTau9Pull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = LcPTau9->GetBinCenter(i);
      Double_t val = LcPTau9Fit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (LcPTau9->GetBinContent(i)-val)/sigma;
      LcPTau9Pull->SetBinContent(i,pull);
      }
      LcPTau9Pull->Draw();

      c1->SaveAs("LcMLcPTau9.pdf");

      TF1 *LcPTau10Fit = new TF1("LcPTau10Fit",DoubleGaussExp,2222, 2352,7);
      LcPTau10Fit->SetParameter(0, 0.4);
      LcPTau10Fit->SetParLimits(0, 0.01, 0.99);
      LcPTau10Fit->SetParameter(1, 8000);
      LcPTau10Fit->SetParameter(2, 2287.);
      LcPTau10Fit->SetParameter(3, 4);
      LcPTau10Fit->SetParameter(4, 7);
      LcPTau10Fit->SetParLimits(3, 0, 20);
      LcPTau10Fit->SetParLimits(4, 0, 20);
      LcPTau10Fit->SetParameter(5, 10);
      LcPTau10Fit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      LcPTau10->SetMinimum(0.0001);
      LcPTau10->GetXaxis()->CenterTitle(true);
      LcPTau10->GetXaxis()->SetTitleSize(20);
      LcPTau10->GetXaxis()->SetTitleFont(43);
      LcPTau10->GetXaxis()->SetTitleOffset(1.5);
      LcPTau10->GetXaxis()->SetLabelSize(0.05);
      LcPTau10->GetYaxis()->SetTitleSize(20);
      LcPTau10->GetYaxis()->SetTitleFont(43);
      LcPTau10->GetYaxis()->SetLabelSize(0.05);
      LcPTau10->Fit("LcPTau10Fit", "E");

      SignalDGH.Form("%5.0f\n", LcPTau10Fit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", LcPTau10Fit->GetParError(1));
      FractionDGH.Form("%5.3f\n", LcPTau10Fit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", LcPTau10Fit->GetParError(0));
      muDGH.Form("%5.3f\n", LcPTau10Fit->GetParameter(2));
      muErDGH.Form("%5.3f\n", LcPTau10Fit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", LcPTau10Fit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", LcPTau10Fit->GetParError(3));
      rmsDGH.Form("%5.3f\n", LcPTau10Fit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", LcPTau10Fit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* LcPTau10Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      LcPTau10Pull->SetStats(0);
      LcPTau10Pull->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      LcPTau10Pull->GetXaxis()->SetTitleSize(20);
      LcPTau10Pull->GetXaxis()->SetTitleFont(43);
      LcPTau10Pull->GetXaxis()->SetTitleOffset(4);
      LcPTau10Pull->GetXaxis()->SetLabelSize(0.1);
      LcPTau10Pull->GetYaxis()->SetTitle("Pull");
      LcPTau10Pull->GetYaxis()->CenterTitle(true);
      LcPTau10Pull->GetXaxis()->CenterTitle(true);
      LcPTau10Pull->GetYaxis()->SetTitleSize(20);
      LcPTau10Pull->GetYaxis()->SetTitleFont(43);
      LcPTau10Pull->GetYaxis()->SetLabelSize(0.1);
      LcPTau10Pull->SetMinimum(-5.1);
      LcPTau10Pull->SetMaximum(5.1);
      LcPTau10Pull->SetFillColor(kBlue);
      LcPTau10Pull->SetLineColor(kBlue);
      LcPTau10Pull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = LcPTau10->GetBinCenter(i);
      Double_t val = LcPTau10Fit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (LcPTau10->GetBinContent(i)-val)/sigma;
      LcPTau10Pull->SetBinContent(i,pull);
      }
      LcPTau10Pull->Draw();

      c1->SaveAs("LcMLcPTau10.pdf");

      TF1 *LcPTau11Fit = new TF1("LcPTau11Fit",DoubleGaussExp,2222, 2352,7);
      LcPTau11Fit->SetParameter(0, 0.4);
      LcPTau11Fit->SetParLimits(0, 0.01, 0.99);
      LcPTau11Fit->SetParameter(1, 8000);
      LcPTau11Fit->SetParameter(2, 2287.);
      LcPTau11Fit->SetParameter(3, 4);
      LcPTau11Fit->SetParameter(4, 7);
      LcPTau11Fit->SetParLimits(3, 0, 20);
      LcPTau11Fit->SetParLimits(4, 0, 20);
      LcPTau11Fit->SetParameter(5, 10);
      LcPTau11Fit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      LcPTau11->SetMinimum(0.0001);
      LcPTau11->GetXaxis()->CenterTitle(true);
      LcPTau11->GetXaxis()->SetTitleSize(20);
      LcPTau11->GetXaxis()->SetTitleFont(43);
      LcPTau11->GetXaxis()->SetTitleOffset(1.5);
      LcPTau11->GetXaxis()->SetLabelSize(0.05);
      LcPTau11->GetYaxis()->SetTitleSize(20);
      LcPTau11->GetYaxis()->SetTitleFont(43);
      LcPTau11->GetYaxis()->SetLabelSize(0.05);
      LcPTau11->Fit("LcPTau11Fit", "E");

      SignalDGH.Form("%5.0f\n", LcPTau11Fit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", LcPTau11Fit->GetParError(1));
      FractionDGH.Form("%5.3f\n", LcPTau11Fit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", LcPTau11Fit->GetParError(0));
      muDGH.Form("%5.3f\n", LcPTau11Fit->GetParameter(2));
      muErDGH.Form("%5.3f\n", LcPTau11Fit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", LcPTau11Fit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", LcPTau11Fit->GetParError(3));
      rmsDGH.Form("%5.3f\n", LcPTau11Fit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", LcPTau11Fit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* LcPTau11Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      LcPTau11Pull->SetStats(0);
      LcPTau11Pull->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      LcPTau11Pull->GetXaxis()->SetTitleSize(20);
      LcPTau11Pull->GetXaxis()->SetTitleFont(43);
      LcPTau11Pull->GetXaxis()->SetTitleOffset(4);
      LcPTau11Pull->GetXaxis()->SetLabelSize(0.1);
      LcPTau11Pull->GetYaxis()->SetTitle("Pull");
      LcPTau11Pull->GetYaxis()->CenterTitle(true);
      LcPTau11Pull->GetXaxis()->CenterTitle(true);
      LcPTau11Pull->GetYaxis()->SetTitleSize(20);
      LcPTau11Pull->GetYaxis()->SetTitleFont(43);
      LcPTau11Pull->GetYaxis()->SetLabelSize(0.1);
      LcPTau11Pull->SetMinimum(-5.1);
      LcPTau11Pull->SetMaximum(5.1);
      LcPTau11Pull->SetFillColor(kBlue);
      LcPTau11Pull->SetLineColor(kBlue);
      LcPTau11Pull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = LcPTau11->GetBinCenter(i);
      Double_t val = LcPTau11Fit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (LcPTau11->GetBinContent(i)-val)/sigma;
      LcPTau11Pull->SetBinContent(i,pull);
      }
      LcPTau11Pull->Draw();

      c1->SaveAs("LcMLcPTau11.pdf");

      TF1 *LcPTau12Fit = new TF1("LcPTau12Fit",DoubleGaussExp,2222, 2352,7);
      LcPTau12Fit->SetParameter(0, 0.4);
      LcPTau12Fit->SetParLimits(0, 0.01, 0.99);
      LcPTau12Fit->SetParameter(1, 8000);
      LcPTau12Fit->SetParameter(2, 2287.);
      LcPTau12Fit->SetParameter(3, 4);
      LcPTau12Fit->SetParameter(4, 7);
      LcPTau12Fit->SetParLimits(3, 0, 20);
      LcPTau12Fit->SetParLimits(4, 0, 20);
      LcPTau12Fit->SetParameter(5, 10);
      LcPTau12Fit->SetParameter(6, -0.002);

      pad1->cd();
      pad1->Clear();
      LcPTau12->SetMinimum(0.0001);
      LcPTau12->GetXaxis()->CenterTitle(true);
      LcPTau12->GetXaxis()->SetTitleSize(20);
      LcPTau12->GetXaxis()->SetTitleFont(43);
      LcPTau12->GetXaxis()->SetTitleOffset(1.5);
      LcPTau12->GetXaxis()->SetLabelSize(0.05);
      LcPTau12->GetYaxis()->SetTitleSize(20);
      LcPTau12->GetYaxis()->SetTitleFont(43);
      LcPTau12->GetYaxis()->SetLabelSize(0.05);
      LcPTau12->Fit("LcPTau12Fit", "E");

      SignalDGH.Form("%5.0f\n", LcPTau12Fit->GetParameter(1));
      SignalErDGH.Form("%5.0f\n", LcPTau12Fit->GetParError(1));
      FractionDGH.Form("%5.3f\n", LcPTau12Fit->GetParameter(0));
      FractionErDGH.Form("%5.3f\n", LcPTau12Fit->GetParError(0));
      muDGH.Form("%5.3f\n", LcPTau12Fit->GetParameter(2));
      muErDGH.Form("%5.3f\n", LcPTau12Fit->GetParError(2));
      sigma1DGH.Form("%5.3f\n", LcPTau12Fit->GetParameter(3));
      sigma1ErDGH.Form("%5.3f\n", LcPTau12Fit->GetParError(3));
      rmsDGH.Form("%5.3f\n", LcPTau12Fit->GetParameter(4));
      rmsErDGH.Form("%5.3f\n", LcPTau12Fit->GetParError(4));

      lt->DrawLatexNDC(0.25, 0.70, "LHCb Preliminary");
      lt->DrawLatexNDC(0.58, 0.70, "Signal = "+SignalDGH+" #pm "+SignalErDGH+"");
      lt->DrawLatexNDC(0.58, 0.65, "Fraction in #sigma_{1} = "+FractionDGH+" #pm "+FractionErDGH+"");
      lt->DrawLatexNDC(0.58, 0.60, "#mu = "+muDGH+" #pm "+muErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.55, "#sigma_{1} = "+sigma1DGH+" #pm "+sigma1ErDGH+" MeV");
      lt->DrawLatexNDC(0.58, 0.50, "#sigma_{2} = "+rmsDGH+" #pm "+rmsErDGH+" MeV");

      pad2->cd();
      pad2->Clear();
      TH1D* LcPTau12Pull = new TH1D("Mass [MeV]", "Lc Mass", 260, 2222, 2352);
      LcPTau12Pull->SetStats(0);
      LcPTau12Pull->GetXaxis()->SetTitle("m(pK^{+}K^{-}) [MeV]");
      LcPTau12Pull->GetXaxis()->SetTitleSize(20);
      LcPTau12Pull->GetXaxis()->SetTitleFont(43);
      LcPTau12Pull->GetXaxis()->SetTitleOffset(4);
      LcPTau12Pull->GetXaxis()->SetLabelSize(0.1);
      LcPTau12Pull->GetYaxis()->SetTitle("Pull");
      LcPTau12Pull->GetYaxis()->CenterTitle(true);
      LcPTau12Pull->GetXaxis()->CenterTitle(true);
      LcPTau12Pull->GetYaxis()->SetTitleSize(20);
      LcPTau12Pull->GetYaxis()->SetTitleFont(43);
      LcPTau12Pull->GetYaxis()->SetLabelSize(0.1);
      LcPTau12Pull->SetMinimum(-5.1);
      LcPTau12Pull->SetMaximum(5.1);
      LcPTau12Pull->SetFillColor(kBlue);
      LcPTau12Pull->SetLineColor(kBlue);
      LcPTau12Pull->SetBit(TH1::kNoTitle);

      for (Int_t i=1;i<260;i++) {
      Double_t x = LcPTau12->GetBinCenter(i);
      Double_t val = LcPTau12Fit->Eval(x);
      Double_t sigma = sqrt(val);
      Double_t pull = (LcPTau12->GetBinContent(i)-val)/sigma;
      LcPTau12Pull->SetBinContent(i,pull);
      }
      LcPTau12Pull->Draw();

      c1->SaveAs("LcMLcPTau12.pdf");

      const Int_t n = 12;
      Double_t x[n] = {1,2,3,4,5,6,7,8,9,10,11,12};
      Double_t xerr[n] = {0,0,0,0,0,0,0,0,0,0,0,0};
      TString lcptauchi2val;

      grid->cd();
      grid->SetGridy();
      grid->SetLeftMargin(0.15);
      grid->SetBottomMargin(0.15);
      lt->SetTextSize(0.04);
      lt->SetTextColor(2);

      double lcptau1 = LcPTau1Fit->GetParameter(2);
      double lcptau2 = LcPTau2Fit->GetParameter(2);
      double lcptau3 = LcPTau3Fit->GetParameter(2);
      double lcptau4 = LcPTau4Fit->GetParameter(2);
      double lcptau5 = LcPTau5Fit->GetParameter(2);
      double lcptau6 = LcPTau6Fit->GetParameter(2);
      double lcptau7 = LcPTau7Fit->GetParameter(2);
      double lcptau8 = LcPTau8Fit->GetParameter(2);
      double lcptau9 = LcPTau9Fit->GetParameter(2);
      double lcptau10 = LcPTau10Fit->GetParameter(2);
      double lcptau11 = LcPTau11Fit->GetParameter(2);
      double lcptau12 = LcPTau12Fit->GetParameter(2);

      double lcptauerr1 = LcPTau1Fit->GetParError(2);
      double lcptauerr2 = LcPTau2Fit->GetParError(2);
      double lcptauerr3 = LcPTau3Fit->GetParError(2);
      double lcptauerr4 = LcPTau4Fit->GetParError(2);
      double lcptauerr5 = LcPTau5Fit->GetParError(2);
      double lcptauerr6 = LcPTau6Fit->GetParError(2);
      double lcptauerr7 = LcPTau7Fit->GetParError(2);
      double lcptauerr8 = LcPTau8Fit->GetParError(2);
      double lcptauerr9 = LcPTau9Fit->GetParError(2);
      double lcptauerr10 = LcPTau10Fit->GetParError(2);
      double lcptauerr11 = LcPTau11Fit->GetParError(2);
      double lcptauerr12 = LcPTau12Fit->GetParError(2);

      double LcptauAvG = ((lcptau1 + lcptau2 + lcptau3 + lcptau4 + lcptau5 + lcptau6 + lcptau7 + lcptau8 + lcptau9 + lcptau10 + lcptau11 + lcptau12)/n);
      Double_t lcptau[n] = {lcptau1 - LcptauAvG,lcptau2 - LcptauAvG, lcptau3 - LcptauAvG,lcptau4 - LcptauAvG, lcptau5 - LcptauAvG,lcptau6 - LcptauAvG, lcptau7 - LcptauAvG,lcptau8 - LcptauAvG, lcptau9 - LcptauAvG,lcptau10 - LcptauAvG, lcptau11 - LcptauAvG,lcptau12 - LcptauAvG};
      Double_t lcptauerr[n] = {lcptauerr1,lcptauerr2,lcptauerr3,lcptauerr4,lcptauerr5,lcptauerr6,lcptauerr7,lcptauerr8,lcptauerr9,lcptauerr10,lcptauerr11,lcptauerr12};

      double lcptauchi2pdf = ((abs(lcptau[0])/lcptauerr[0])*(abs(lcptau[0])/lcptauerr[0]) + (abs(lcptau[1])/lcptauerr[1])*(abs(lcptau[1])/lcptauerr[1]) + (abs(lcptau[2])/lcptauerr[2])*(abs(lcptau[2])/lcptauerr[2]) + (abs(lcptau[3])/lcptauerr[3])*(abs(lcptau[3])/lcptauerr[3]) + (abs(lcptau[4])/lcptauerr[4])*(abs(lcptau[4])/lcptauerr[4]) + (abs(lcptau[5])/lcptauerr[5])*(abs(lcptau[5])/lcptauerr[5]) + (abs(lcptau[6])/lcptauerr[6])*(abs(lcptau[6])/lcptauerr[6]) + (abs(lcptau[7])/lcptauerr[7])*(abs(lcptau[7])/lcptauerr[7]) + (abs(lcptau[8])/lcptauerr[8])*(abs(lcptau[8])/lcptauerr[8]) + (abs(lcptau[9])/lcptauerr[9])*(abs(lcptau[9])/lcptauerr[9]) + (abs(lcptau[10])/lcptauerr[10])*(abs(lcptau[10])/lcptauerr[10]) + (abs(lcptau[11])/lcptauerr[11])*(abs(lcptau[11])/lcptauerr[11]))/(n-1);
      lcptauchi2val.Form("%5.3f\n", lcptauchi2pdf);
      double LcPTauError = 0;
      if (lcptauchi2pdf > 1){
      LcPTauError = 0.013 * TMath::Sqrt(lcptauchi2pdf - 1);
      }

Double_t D1[3] = {0.90,1.90,2.90};
Double_t lcptauD1[3] = {lcptau[0], lcptau[1], lcptau[2]};
Double_t lcptauD1Err[3] = {lcptauerr[0], lcptauerr[1], lcptauerr[2]};
Double_t D2[3] = {0.95,1.95,2.95};
Double_t lcptauD2[3] = {lcptau[3], lcptau[4], lcptau[5]};
Double_t lcptauD2Err[3] = {lcptauerr[3], lcptauerr[4], lcptauerr[5]};
Double_t D3[3] = {1.0,2.0,3.0};
Double_t lcptauD3[3] = {lcptau[6], lcptau[7], lcptau[8]};
Double_t lcptauD3Err[3] = {lcptauerr[6], lcptauerr[7], lcptauerr[8]};
Double_t D4[3] = {1.05,2.05,3.05};
Double_t lcptauD4[3] = {lcptau[9], lcptau[10], lcptau[11]};
Double_t lcptauD4Err[3] = {lcptauerr[9], lcptauerr[10], lcptauerr[11]};

g1 = new TGraphErrors(3, D1, lcptauD1, xerr, lcptauD1Err);
g2 = new TGraphErrors(3, D2, lcptauD2, xerr, lcptauD2Err);
g3 = new TGraphErrors(3, D3, lcptauD3, xerr, lcptauD3Err);
g4 = new TGraphErrors(3, D4, lcptauD4, xerr, lcptauD4Err);
g1->SetTitle("#Lambda_{c} Momentum (<51)GeV");
g2->SetTitle("#Lambda_{c} Momentum (51-69)GeV");
g3->SetTitle("#Lambda_{c} Momentum (69-97)GeV");
g4->SetTitle("#Lambda_{c} Momentum (>97)GeV");
g1->SetMarkerColor(kRed); g1->SetMarkerStyle(20); g1->SetMarkerSize(1);
g2->SetMarkerColor(kBlue); g2->SetMarkerStyle(21); g2->SetMarkerSize(1);
g3->SetMarkerColor(kGreen+3); g3->SetMarkerStyle(22); g3->SetMarkerSize(1.5);
g4->SetMarkerColor(kOrange+7); g4->SetMarkerStyle(33); g4->SetMarkerSize(1.5);
g1->GetXaxis()->CenterTitle(true);
g1->GetXaxis()->SetTitleSize(20);
g1->GetXaxis()->SetTitleFont(43);
g1->GetXaxis()->SetTitleOffset(1.5);
g1->GetXaxis()->SetLabelSize(0.075);
g1->GetYaxis()->SetTitleSize(20);
g1->GetYaxis()->SetTitleFont(43);
g1->GetYaxis()->SetLabelSize(0.05);
g1->GetXaxis()->SetNdivisions(12);
g1->GetXaxis()->SetTitle("Momentum Regions [GeV] / Tau Regions [ps]");
MassAVG.Form("%4.3f\n", LcptauAvG);
g1->GetYaxis()->SetTitle("Measured Mass - "+MassAVG+" [MeV]");
g1->GetXaxis()->SetAlphanumeric();
g1->GetXaxis()->SetBinLabel(15, "(<0.57) ps");
g1->GetXaxis()->SetBinLabel(55, "(0.57-0.76) ps");
g1->GetXaxis()->SetBinLabel(90, "(>0.76) ps");
g1->GetXaxis()->LabelsOption("h");

g1->SetMinimum(-0.30);
g1->SetMaximum(0.2);
g1->Draw("ap");
g2->Draw("PSAME");
g3->Draw("PSAME");
g4->Draw("PSAME");
//gLcPTauMulti->Add(g1);
//gLcPTauMulti->Add(g2);
//gLcPTauMulti->Add(g3);
//gLcPTauMulti->Add(g4);
//gLcPTauMulti->Draw("ap");
//gLcPTauMulti->GetXaxis()->SetAlphanumeric();
//gLcPTauMulti->GetXaxis()->SetBinLabel(10, "(0.0-0.57)");
//gLcPTauMulti->GetXaxis()->SetBinLabel(50, "(0.57-0.76)");
//gLcPTauMulti->GetXaxis()->SetBinLabel(90, "(0.76-1.3)");
gPad->BuildLegend(0.55,0.20,0.90,0.45);

      lt->DrawLatexNDC(0.25, 0.83, "LHCb Preliminary");
      lt->DrawLatexNDC(0.25, 0.78, "#chi^2/NDF ="+lcptauchi2val);
      g1->SetTitle("");
      grid->Write("LcPTau Statistics");
      grid->SaveAs("gLcPTauMulti.pdf");
}
