//Background Subtracting Data To Observe Patterns in Daughter Variables

#define BSubAnalysis_cxx
#include "BSubAnalysis.h"

#include <TH2.h>
#include <TStyle.h>

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
