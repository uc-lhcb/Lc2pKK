#define BSubExample_cxx
#include "BSubExample.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

/* For this example I will use the Proton_IPCHI2_OWNPV variable
because there is a good region to make a cut on. */

/* For example purposes I am only showing one variable
but you will want a macro that does this for all interesting variables
at once to save time. */

/*For each variable you will need to make 3 histograms,
one for the events in the signal region and the background region,
as well as a histogram where you subtract the background histogram from
the signal histogram. This is because there is still background in the signal region. */

TH1D * SignalHistogram = nullptr;
TH1D * BackgroundHistogram = nullptr;
TH1D * SignalEstimateHistogram = nullptr;


/* Creating TCanvas [c1] and TFile [File] */
TCanvas * c1 = nullptr;
TFile * File = nullptr;

void BSubExample::Begin(TTree * /*tree*/)
{
   TString option = GetOption();

// Defining c1 TCanvas
c1 = new TCanvas("canvas", "Test Canvas");

/* Defining Output File which will be called 'BackgroundSubtractionExample.root'.
Once this macro is done running, you can use 'root -l BackgroundSubtractionExample.root'
to observe the results. */
File = new TFile("BackgroundSubtractionExample.root", "RECREATE");
gFile = File;

//Sets Histogram to Draw with Error Bars
   TH1::SetDefaultSumw2(kTRUE);

//Defines Variable Names, Histogram Names, and Ranges for 3 Histograms
SignalHistogram = new TH1D("Log(IPCHI2)", "Signal Region", 170, 0.75, 5.);
BackgroundHistogram = new TH1D("Log(IPCHI2)", "Background Region", 170, 0.75, 5.);
SignalEstimateHistogram = new TH1D("Log(IPCHI2)", "Signal Estimation", 170, 0.75, 5.);

//Sets the color of each histogram so that they can be easily distinguished
SignalHistogram->SetLineColor(kBlue);
BackgroundHistogram->SetLineColor(kRed);
SignalEstimateHistogram->SetLineColor(kGreen+3);
}

void BSubExample::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
}

Bool_t BSubExample::Process(Long64_t entry)
{
   GetEntry(entry);
   fReader.SetLocalEntry(entry);

/* These are the best cuts that I found from my Dalitz Plot analysis.
They should be left in so that you start off with a good signal/background ratio. */
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

bool  BestCuts= (
     ((*Kminus_ProbNNk)*(*Kplus_ProbNNk)*(*Proton_ProbNNp) > 0.87)
  && ((*Kminus_ProbNNk)*(*Kplus_ProbNNk) > 0.9)
  && (M2_KpKm > 1.024)
  && (M2_KpKm < 1.057)
      );
// End of My Dalitz Plot Cuts



 /* Now we need to determine whether an event is signal or background.
Since we are trying to fit the LambdaC Mass, we know that signal events occur
around the large spike in the mass (around 2286 MeV). Background Events occur at
mass values far away from 2286. We define the signal region between 2274 and 2300 MeV.
We want signal and background regions to be scaled identically so because there is a
range of 26 MeV in signal we want a range of 26 MeV of background. I do this by requiring the
background region between 2220 and 2233 or 2341 and 2354. */
   bool SignalRegion = *Lcplus_M > 2274. && *Lcplus_M < 2300.;
   bool BackgroundRegion = (*Lcplus_M > 2220. && *Lcplus_M < 2233.) || (*Lcplus_M > 2341. && *Lcplus_M < 2354.);



//Filling the Signal Histogram with Proton Log(IPCHI2)from the signal region of LambdaC Mass
if (BestCuts & SignalRegion){
  SignalHistogram->Fill(TMath::Log10(*Proton_IPCHI2_OWNPV));
}

//Filling the Background Histogram  with Proton Log(IPCHI2)from the background region of LambdaC Mass
if (BestCuts & BackgroundRegion){
  BackgroundHistogram->Fill(TMath::Log10(*Proton_IPCHI2_OWNPV));
}

//Subtracting the Signal and Background Histograms To Create an Estimate of only the Signal
SignalEstimateHistogram->Add(SignalHistogram,BackgroundHistogram,1.0,-1.0);


   return kTRUE;
}

void BSubExample::SlaveTerminate()
{
}

void BSubExample::Terminate()
{

gStyle->SetOptTitle(0);
c1->cd();

//Sets Axis Labels
SignalHistogram->GetYaxis()->SetTitle("Events per 1/40 Log10(mm)");
SignalHistogram->GetXaxis()->SetTitle("Log10(mm)");

//Requires Minimum y value to be 0
SignalHistogram->SetMinimum(0);

//Draws all three histograms on same canvas
SignalHistogram->Draw();
SignalEstimateHistogram->Draw("SAME");
BackgroundHistogram->Draw("SAME");

//Builds Legend So that we know what color is associated to which histogram
gPad->BuildLegend(0.78,0.75,0.98,0.95);

//Sets Histogram Title
SignalHistogram->SetTitle("Proton_IPCHI2_OWNPV Signal Estimates");

//Writes Result into Root File
c1->Write("PrChi2 Estimations");

//Ends Program
   File->Close();
}
