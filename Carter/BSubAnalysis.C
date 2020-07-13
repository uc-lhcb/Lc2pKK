//Background Subtracting Data To Observe Patterns in ROOT Variables
//Check PT, IPCHI2_OWNPV, DOCAMAXCHI2MAX, & TAU

#define BSubAnalysis_cxx
#include "BSubAnalysis.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

#include "fit1MeV_Gaussian.C"
#include "fitHalfMeV_Gaussian.C"
#include "DGOneMuOneTotal1MeV.C"
#include "DGOneMuOneTotalHalfMeV.C"
#include "DGTwoMuOneTotal1MeV.C"
#include "DGTwoMuOneTotalHalfMeV.C"

TH1D * LcPT = nullptr;
TH1D * KpPT = nullptr;
TH1D * KmPT = nullptr;
TH1D * LcChi2 = nullptr;
TH1D * KpChi2 = nullptr;
TH1D * KmChi2 = nullptr;
TH1D * DOCAMax = nullptr;
TH1D * LcTAU = nullptr;

void BSubAnalysis::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
   
}

void BSubAnalysis::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

}

Bool_t BSubAnalysis::Process(Long64_t entry)
{
   fReader.SetLocalEntry(entry);

   return kTRUE;
}

void BSubAnalysis::SlaveTerminate()
{

}

void BSubAnalysis::Terminate()
{

}
