#define DalitzPlot_cxx
#include "DalitzPlot.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>

TH2D * DalitzPlot = nullptr;

void DalitzPlot::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
         DalitzPlot = new TH2D("Figures of Merit", "Color Plot of LambdaC Mass - One Dimensional Projections", 50, 0.7, 4.2, 50, 0.25, 1.0);
         DalitzPlot->GetXaxis()->SetTitle(""m^{2}(K^{-}K^{+})[GeV^{2}/c^{4}]");
         DalitzPlot->GetYaxis()->SetTitle("m^{2}(pK^{-})[GeV^{2}/c^{4}]");
         DalitzPlot->GetZaxis()->SetTitle(Entries);
}

void DalitzPlot::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
}

Bool_t DalitzPlot::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   fReader.SetLocalEntry(entry);

   return kTRUE;
}

void DalitzPlot::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void DalitzPlot::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
