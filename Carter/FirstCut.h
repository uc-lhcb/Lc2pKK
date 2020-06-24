//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jun 19 15:04:19 2020 by ROOT version 6.18/00
// from TChain TupleLbToLcmu_LcTopKK/DecayTree/
//////////////////////////////////////////////////////////

#ifndef FirstCut_h
#define FirstCut_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class FirstCut : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Double_t> Lb_ETA = {fReader, "Lb_ETA"};
   TTreeReaderValue<Double_t> Lb_PHI = {fReader, "Lb_PHI"};
   TTreeReaderValue<Double_t> Lb_ENDVERTEX_X = {fReader, "Lb_ENDVERTEX_X"};
   TTreeReaderValue<Double_t> Lb_ENDVERTEX_Y = {fReader, "Lb_ENDVERTEX_Y"};
   TTreeReaderValue<Double_t> Lb_ENDVERTEX_Z = {fReader, "Lb_ENDVERTEX_Z"};
   TTreeReaderValue<Double_t> Lb_ENDVERTEX_XERR = {fReader, "Lb_ENDVERTEX_XERR"};
   TTreeReaderValue<Double_t> Lb_ENDVERTEX_YERR = {fReader, "Lb_ENDVERTEX_YERR"};
   TTreeReaderValue<Double_t> Lb_ENDVERTEX_ZERR = {fReader, "Lb_ENDVERTEX_ZERR"};
   TTreeReaderValue<Double_t> Lb_ENDVERTEX_CHI2 = {fReader, "Lb_ENDVERTEX_CHI2"};
   TTreeReaderValue<Int_t> Lb_ENDVERTEX_NDOF = {fReader, "Lb_ENDVERTEX_NDOF"};
   TTreeReaderValue<Double_t> Lb_OWNPV_X = {fReader, "Lb_OWNPV_X"};
   TTreeReaderValue<Double_t> Lb_OWNPV_Y = {fReader, "Lb_OWNPV_Y"};
   TTreeReaderValue<Double_t> Lb_OWNPV_Z = {fReader, "Lb_OWNPV_Z"};
   TTreeReaderValue<Double_t> Lb_OWNPV_XERR = {fReader, "Lb_OWNPV_XERR"};
   TTreeReaderValue<Double_t> Lb_OWNPV_YERR = {fReader, "Lb_OWNPV_YERR"};
   TTreeReaderValue<Double_t> Lb_OWNPV_ZERR = {fReader, "Lb_OWNPV_ZERR"};
   TTreeReaderValue<Double_t> Lb_OWNPV_CHI2 = {fReader, "Lb_OWNPV_CHI2"};
   TTreeReaderValue<Int_t> Lb_OWNPV_NDOF = {fReader, "Lb_OWNPV_NDOF"};
   TTreeReaderValue<Double_t> Lb_IP_OWNPV = {fReader, "Lb_IP_OWNPV"};
   TTreeReaderValue<Double_t> Lb_IPCHI2_OWNPV = {fReader, "Lb_IPCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Lb_FD_OWNPV = {fReader, "Lb_FD_OWNPV"};
   TTreeReaderValue<Double_t> Lb_FDCHI2_OWNPV = {fReader, "Lb_FDCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Lb_DIRA_OWNPV = {fReader, "Lb_DIRA_OWNPV"};
   TTreeReaderValue<Double_t> Lb_P = {fReader, "Lb_P"};
   TTreeReaderValue<Double_t> Lb_PT = {fReader, "Lb_PT"};
   TTreeReaderValue<Double_t> Lb_PE = {fReader, "Lb_PE"};
   TTreeReaderValue<Double_t> Lb_PX = {fReader, "Lb_PX"};
   TTreeReaderValue<Double_t> Lb_PY = {fReader, "Lb_PY"};
   TTreeReaderValue<Double_t> Lb_PZ = {fReader, "Lb_PZ"};
   TTreeReaderValue<Double_t> Lb_MM = {fReader, "Lb_MM"};
   TTreeReaderValue<Double_t> Lb_MMERR = {fReader, "Lb_MMERR"};
   TTreeReaderValue<Double_t> Lb_M = {fReader, "Lb_M"};
   TTreeReaderValue<Int_t> Lb_ID = {fReader, "Lb_ID"};
   TTreeReaderValue<Double_t> Lb_DTFConst_CHI2 = {fReader, "Lb_DTFConst_CHI2"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_ETA = {fReader, "Lb_DTFConst_Lb_ETA"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_ID = {fReader, "Lb_DTFConst_Lb_ID"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_M = {fReader, "Lb_DTFConst_Lb_M"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_MM = {fReader, "Lb_DTFConst_Lb_MM"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_P = {fReader, "Lb_DTFConst_Lb_P"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_PT = {fReader, "Lb_DTFConst_Lb_PT"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_PX = {fReader, "Lb_DTFConst_Lb_PX"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_PY = {fReader, "Lb_DTFConst_Lb_PY"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_PZ = {fReader, "Lb_DTFConst_Lb_PZ"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_mu_ETA = {fReader, "Lb_DTFConst_Lb_mu_ETA"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_mu_ID = {fReader, "Lb_DTFConst_Lb_mu_ID"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_mu_M = {fReader, "Lb_DTFConst_Lb_mu_M"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_mu_MM = {fReader, "Lb_DTFConst_Lb_mu_MM"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_mu_P = {fReader, "Lb_DTFConst_Lb_mu_P"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_mu_PT = {fReader, "Lb_DTFConst_Lb_mu_PT"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_mu_PX = {fReader, "Lb_DTFConst_Lb_mu_PX"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_mu_PY = {fReader, "Lb_DTFConst_Lb_mu_PY"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lb_mu_PZ = {fReader, "Lb_DTFConst_Lb_mu_PZ"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_ETA = {fReader, "Lb_DTFConst_Lc_ETA"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_ID = {fReader, "Lb_DTFConst_Lc_ID"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_M = {fReader, "Lb_DTFConst_Lc_M"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_MM = {fReader, "Lb_DTFConst_Lc_MM"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_P = {fReader, "Lb_DTFConst_Lc_P"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_PT = {fReader, "Lb_DTFConst_Lc_PT"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_PX = {fReader, "Lb_DTFConst_Lc_PX"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_PY = {fReader, "Lb_DTFConst_Lc_PY"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_PZ = {fReader, "Lb_DTFConst_Lc_PZ"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h1_ETA = {fReader, "Lb_DTFConst_Lc_h1_ETA"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h1_ID = {fReader, "Lb_DTFConst_Lc_h1_ID"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h1_M = {fReader, "Lb_DTFConst_Lc_h1_M"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h1_MM = {fReader, "Lb_DTFConst_Lc_h1_MM"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h1_P = {fReader, "Lb_DTFConst_Lc_h1_P"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h1_PT = {fReader, "Lb_DTFConst_Lc_h1_PT"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h1_PX = {fReader, "Lb_DTFConst_Lc_h1_PX"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h1_PY = {fReader, "Lb_DTFConst_Lc_h1_PY"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h1_PZ = {fReader, "Lb_DTFConst_Lc_h1_PZ"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h1_h2_M = {fReader, "Lb_DTFConst_Lc_h1_h2_M"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h2_ETA = {fReader, "Lb_DTFConst_Lc_h2_ETA"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h2_ID = {fReader, "Lb_DTFConst_Lc_h2_ID"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h2_M = {fReader, "Lb_DTFConst_Lc_h2_M"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h2_MM = {fReader, "Lb_DTFConst_Lc_h2_MM"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h2_P = {fReader, "Lb_DTFConst_Lc_h2_P"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h2_PT = {fReader, "Lb_DTFConst_Lc_h2_PT"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h2_PX = {fReader, "Lb_DTFConst_Lc_h2_PX"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h2_PY = {fReader, "Lb_DTFConst_Lc_h2_PY"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_h2_PZ = {fReader, "Lb_DTFConst_Lc_h2_PZ"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_p_ETA = {fReader, "Lb_DTFConst_Lc_p_ETA"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_p_ID = {fReader, "Lb_DTFConst_Lc_p_ID"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_p_M = {fReader, "Lb_DTFConst_Lc_p_M"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_p_MM = {fReader, "Lb_DTFConst_Lc_p_MM"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_p_P = {fReader, "Lb_DTFConst_Lc_p_P"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_p_PT = {fReader, "Lb_DTFConst_Lc_p_PT"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_p_PX = {fReader, "Lb_DTFConst_Lc_p_PX"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_p_PY = {fReader, "Lb_DTFConst_Lc_p_PY"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_p_PZ = {fReader, "Lb_DTFConst_Lc_p_PZ"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_p_h1_M = {fReader, "Lb_DTFConst_Lc_p_h1_M"};
   TTreeReaderValue<Double_t> Lb_DTFConst_Lc_p_h2_M = {fReader, "Lb_DTFConst_Lc_p_h2_M"};
   TTreeReaderValue<Double_t> Lb_DTFConst_NDOF = {fReader, "Lb_DTFConst_NDOF"};
   TTreeReaderValue<Double_t> Lb_DTF_CHI2 = {fReader, "Lb_DTF_CHI2"};
   TTreeReaderValue<Double_t> Lb_DTF_Lc_M = {fReader, "Lb_DTF_Lc_M"};
   TTreeReaderValue<Double_t> Lb_DTF_NDOF = {fReader, "Lb_DTF_NDOF"};
   TTreeReaderValue<Double_t> Lb_Loki_BPVLTIME = {fReader, "Lb_Loki_BPVLTIME"};
   TTreeReaderValue<Double_t> Lb_Loki_DOCACHI2MAX = {fReader, "Lb_Loki_DOCACHI2MAX"};
   TTreeReaderValue<Double_t> Lb_Loki_DOCAMAX = {fReader, "Lb_Loki_DOCAMAX"};
   TTreeReaderValue<Double_t> Lb_Loki_SUMPT = {fReader, "Lb_Loki_SUMPT"};
   TTreeReaderValue<Bool_t> Lb_L0Global_Dec = {fReader, "Lb_L0Global_Dec"};
   TTreeReaderValue<Bool_t> Lb_L0Global_TIS = {fReader, "Lb_L0Global_TIS"};
   TTreeReaderValue<Bool_t> Lb_L0Global_TOS = {fReader, "Lb_L0Global_TOS"};
   TTreeReaderValue<Bool_t> Lb_Hlt1Global_Dec = {fReader, "Lb_Hlt1Global_Dec"};
   TTreeReaderValue<Bool_t> Lb_Hlt1Global_TIS = {fReader, "Lb_Hlt1Global_TIS"};
   TTreeReaderValue<Bool_t> Lb_Hlt1Global_TOS = {fReader, "Lb_Hlt1Global_TOS"};
   TTreeReaderValue<Bool_t> Lb_Hlt1Phys_Dec = {fReader, "Lb_Hlt1Phys_Dec"};
   TTreeReaderValue<Bool_t> Lb_Hlt1Phys_TIS = {fReader, "Lb_Hlt1Phys_TIS"};
   TTreeReaderValue<Bool_t> Lb_Hlt1Phys_TOS = {fReader, "Lb_Hlt1Phys_TOS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2Global_Dec = {fReader, "Lb_Hlt2Global_Dec"};
   TTreeReaderValue<Bool_t> Lb_Hlt2Global_TIS = {fReader, "Lb_Hlt2Global_TIS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2Global_TOS = {fReader, "Lb_Hlt2Global_TOS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2Phys_Dec = {fReader, "Lb_Hlt2Phys_Dec"};
   TTreeReaderValue<Bool_t> Lb_Hlt2Phys_TIS = {fReader, "Lb_Hlt2Phys_TIS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2Phys_TOS = {fReader, "Lb_Hlt2Phys_TOS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2SingleMuonDecision_Dec = {fReader, "Lb_Hlt2SingleMuonDecision_Dec"};
   TTreeReaderValue<Bool_t> Lb_Hlt2SingleMuonDecision_TIS = {fReader, "Lb_Hlt2SingleMuonDecision_TIS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2SingleMuonDecision_TOS = {fReader, "Lb_Hlt2SingleMuonDecision_TOS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2Topo2BodyBBDTDecision_Dec = {fReader, "Lb_Hlt2Topo2BodyBBDTDecision_Dec"};
   TTreeReaderValue<Bool_t> Lb_Hlt2Topo2BodyBBDTDecision_TIS = {fReader, "Lb_Hlt2Topo2BodyBBDTDecision_TIS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2Topo2BodyBBDTDecision_TOS = {fReader, "Lb_Hlt2Topo2BodyBBDTDecision_TOS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2Topo3BodyBBDTDecision_Dec = {fReader, "Lb_Hlt2Topo3BodyBBDTDecision_Dec"};
   TTreeReaderValue<Bool_t> Lb_Hlt2Topo3BodyBBDTDecision_TIS = {fReader, "Lb_Hlt2Topo3BodyBBDTDecision_TIS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2Topo3BodyBBDTDecision_TOS = {fReader, "Lb_Hlt2Topo3BodyBBDTDecision_TOS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2Topo4BodyBBDTDecision_Dec = {fReader, "Lb_Hlt2Topo4BodyBBDTDecision_Dec"};
   TTreeReaderValue<Bool_t> Lb_Hlt2Topo4BodyBBDTDecision_TIS = {fReader, "Lb_Hlt2Topo4BodyBBDTDecision_TIS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2Topo4BodyBBDTDecision_TOS = {fReader, "Lb_Hlt2Topo4BodyBBDTDecision_TOS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2TopoMu2BodyBBDTDecision_Dec = {fReader, "Lb_Hlt2TopoMu2BodyBBDTDecision_Dec"};
   TTreeReaderValue<Bool_t> Lb_Hlt2TopoMu2BodyBBDTDecision_TIS = {fReader, "Lb_Hlt2TopoMu2BodyBBDTDecision_TIS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2TopoMu2BodyBBDTDecision_TOS = {fReader, "Lb_Hlt2TopoMu2BodyBBDTDecision_TOS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2TopoMu3BodyBBDTDecision_Dec = {fReader, "Lb_Hlt2TopoMu3BodyBBDTDecision_Dec"};
   TTreeReaderValue<Bool_t> Lb_Hlt2TopoMu3BodyBBDTDecision_TIS = {fReader, "Lb_Hlt2TopoMu3BodyBBDTDecision_TIS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2TopoMu3BodyBBDTDecision_TOS = {fReader, "Lb_Hlt2TopoMu3BodyBBDTDecision_TOS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2TopoMu4BodyBBDTDecision_Dec = {fReader, "Lb_Hlt2TopoMu4BodyBBDTDecision_Dec"};
   TTreeReaderValue<Bool_t> Lb_Hlt2TopoMu4BodyBBDTDecision_TIS = {fReader, "Lb_Hlt2TopoMu4BodyBBDTDecision_TIS"};
   TTreeReaderValue<Bool_t> Lb_Hlt2TopoMu4BodyBBDTDecision_TOS = {fReader, "Lb_Hlt2TopoMu4BodyBBDTDecision_TOS"};
   TTreeReaderValue<Double_t> Lc_ETA = {fReader, "Lc_ETA"};
   TTreeReaderValue<Double_t> Lc_PHI = {fReader, "Lc_PHI"};
   TTreeReaderValue<Double_t> Lc_ENDVERTEX_X = {fReader, "Lc_ENDVERTEX_X"};
   TTreeReaderValue<Double_t> Lc_ENDVERTEX_Y = {fReader, "Lc_ENDVERTEX_Y"};
   TTreeReaderValue<Double_t> Lc_ENDVERTEX_Z = {fReader, "Lc_ENDVERTEX_Z"};
   TTreeReaderValue<Double_t> Lc_ENDVERTEX_XERR = {fReader, "Lc_ENDVERTEX_XERR"};
   TTreeReaderValue<Double_t> Lc_ENDVERTEX_YERR = {fReader, "Lc_ENDVERTEX_YERR"};
   TTreeReaderValue<Double_t> Lc_ENDVERTEX_ZERR = {fReader, "Lc_ENDVERTEX_ZERR"};
   TTreeReaderValue<Double_t> Lc_ENDVERTEX_CHI2 = {fReader, "Lc_ENDVERTEX_CHI2"};
   TTreeReaderValue<Int_t> Lc_ENDVERTEX_NDOF = {fReader, "Lc_ENDVERTEX_NDOF"};
   TTreeReaderValue<Double_t> Lc_OWNPV_X = {fReader, "Lc_OWNPV_X"};
   TTreeReaderValue<Double_t> Lc_OWNPV_Y = {fReader, "Lc_OWNPV_Y"};
   TTreeReaderValue<Double_t> Lc_OWNPV_Z = {fReader, "Lc_OWNPV_Z"};
   TTreeReaderValue<Double_t> Lc_OWNPV_XERR = {fReader, "Lc_OWNPV_XERR"};
   TTreeReaderValue<Double_t> Lc_OWNPV_YERR = {fReader, "Lc_OWNPV_YERR"};
   TTreeReaderValue<Double_t> Lc_OWNPV_ZERR = {fReader, "Lc_OWNPV_ZERR"};
   TTreeReaderValue<Double_t> Lc_OWNPV_CHI2 = {fReader, "Lc_OWNPV_CHI2"};
   TTreeReaderValue<Int_t> Lc_OWNPV_NDOF = {fReader, "Lc_OWNPV_NDOF"};
   TTreeReaderValue<Double_t> Lc_IP_OWNPV = {fReader, "Lc_IP_OWNPV"};
   TTreeReaderValue<Double_t> Lc_IPCHI2_OWNPV = {fReader, "Lc_IPCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Lc_FD_OWNPV = {fReader, "Lc_FD_OWNPV"};
   TTreeReaderValue<Double_t> Lc_FDCHI2_OWNPV = {fReader, "Lc_FDCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Lc_DIRA_OWNPV = {fReader, "Lc_DIRA_OWNPV"};
   TTreeReaderValue<Double_t> Lc_ORIVX_X = {fReader, "Lc_ORIVX_X"};
   TTreeReaderValue<Double_t> Lc_ORIVX_Y = {fReader, "Lc_ORIVX_Y"};
   TTreeReaderValue<Double_t> Lc_ORIVX_Z = {fReader, "Lc_ORIVX_Z"};
   TTreeReaderValue<Double_t> Lc_ORIVX_XERR = {fReader, "Lc_ORIVX_XERR"};
   TTreeReaderValue<Double_t> Lc_ORIVX_YERR = {fReader, "Lc_ORIVX_YERR"};
   TTreeReaderValue<Double_t> Lc_ORIVX_ZERR = {fReader, "Lc_ORIVX_ZERR"};
   TTreeReaderValue<Double_t> Lc_ORIVX_CHI2 = {fReader, "Lc_ORIVX_CHI2"};
   TTreeReaderValue<Int_t> Lc_ORIVX_NDOF = {fReader, "Lc_ORIVX_NDOF"};
   TTreeReaderValue<Double_t> Lc_FD_ORIVX = {fReader, "Lc_FD_ORIVX"};
   TTreeReaderValue<Double_t> Lc_FDCHI2_ORIVX = {fReader, "Lc_FDCHI2_ORIVX"};
   TTreeReaderValue<Double_t> Lc_DIRA_ORIVX = {fReader, "Lc_DIRA_ORIVX"};
   TTreeReaderValue<Double_t> Lc_P = {fReader, "Lc_P"};
   TTreeReaderValue<Double_t> Lc_PT = {fReader, "Lc_PT"};
   TTreeReaderValue<Double_t> Lc_PE = {fReader, "Lc_PE"};
   TTreeReaderValue<Double_t> Lc_PX = {fReader, "Lc_PX"};
   TTreeReaderValue<Double_t> Lc_PY = {fReader, "Lc_PY"};
   TTreeReaderValue<Double_t> Lc_PZ = {fReader, "Lc_PZ"};
   TTreeReaderValue<Double_t> Lc_MM = {fReader, "Lc_MM"};
   TTreeReaderValue<Double_t> Lc_MMERR = {fReader, "Lc_MMERR"};
   TTreeReaderValue<Double_t> Lc_M = {fReader, "Lc_M"};
   TTreeReaderValue<Int_t> Lc_ID = {fReader, "Lc_ID"};
   TTreeReaderValue<Double_t> Lc_Loki_BPVLTIME = {fReader, "Lc_Loki_BPVLTIME"};
   TTreeReaderValue<Double_t> Lc_Loki_DOCACHI2MAX = {fReader, "Lc_Loki_DOCACHI2MAX"};
   TTreeReaderValue<Double_t> Lc_Loki_DOCAMAX = {fReader, "Lc_Loki_DOCAMAX"};
   TTreeReaderValue<Double_t> Lc_Loki_SUMPT = {fReader, "Lc_Loki_SUMPT"};
   TTreeReaderValue<Double_t> Lc_h1_h2_M = {fReader, "Lc_h1_h2_M"};
   TTreeReaderValue<Double_t> Lc_p_h1_M = {fReader, "Lc_p_h1_M"};
   TTreeReaderValue<Double_t> Lc_p_h2_M = {fReader, "Lc_p_h2_M"};
   TTreeReaderValue<Double_t> Lc_p_ETA = {fReader, "Lc_p_ETA"};
   TTreeReaderValue<Double_t> Lc_p_PHI = {fReader, "Lc_p_PHI"};
   TTreeReaderValue<Double_t> Lc_p_MC12TuneV4_ProbNNe = {fReader, "Lc_p_MC12TuneV4_ProbNNe"};
   TTreeReaderValue<Double_t> Lc_p_MC12TuneV4_ProbNNmu = {fReader, "Lc_p_MC12TuneV4_ProbNNmu"};
   TTreeReaderValue<Double_t> Lc_p_MC12TuneV4_ProbNNpi = {fReader, "Lc_p_MC12TuneV4_ProbNNpi"};
   TTreeReaderValue<Double_t> Lc_p_MC12TuneV4_ProbNNk = {fReader, "Lc_p_MC12TuneV4_ProbNNk"};
   TTreeReaderValue<Double_t> Lc_p_MC12TuneV4_ProbNNp = {fReader, "Lc_p_MC12TuneV4_ProbNNp"};
   TTreeReaderValue<Double_t> Lc_p_MC12TuneV4_ProbNNghost = {fReader, "Lc_p_MC12TuneV4_ProbNNghost"};
   TTreeReaderValue<Double_t> Lc_p_OWNPV_X = {fReader, "Lc_p_OWNPV_X"};
   TTreeReaderValue<Double_t> Lc_p_OWNPV_Y = {fReader, "Lc_p_OWNPV_Y"};
   TTreeReaderValue<Double_t> Lc_p_OWNPV_Z = {fReader, "Lc_p_OWNPV_Z"};
   TTreeReaderValue<Double_t> Lc_p_OWNPV_XERR = {fReader, "Lc_p_OWNPV_XERR"};
   TTreeReaderValue<Double_t> Lc_p_OWNPV_YERR = {fReader, "Lc_p_OWNPV_YERR"};
   TTreeReaderValue<Double_t> Lc_p_OWNPV_ZERR = {fReader, "Lc_p_OWNPV_ZERR"};
   TTreeReaderValue<Double_t> Lc_p_OWNPV_CHI2 = {fReader, "Lc_p_OWNPV_CHI2"};
   TTreeReaderValue<Int_t> Lc_p_OWNPV_NDOF = {fReader, "Lc_p_OWNPV_NDOF"};
   TTreeReaderValue<Double_t> Lc_p_IP_OWNPV = {fReader, "Lc_p_IP_OWNPV"};
   TTreeReaderValue<Double_t> Lc_p_IPCHI2_OWNPV = {fReader, "Lc_p_IPCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Lc_p_ORIVX_X = {fReader, "Lc_p_ORIVX_X"};
   TTreeReaderValue<Double_t> Lc_p_ORIVX_Y = {fReader, "Lc_p_ORIVX_Y"};
   TTreeReaderValue<Double_t> Lc_p_ORIVX_Z = {fReader, "Lc_p_ORIVX_Z"};
   TTreeReaderValue<Double_t> Lc_p_ORIVX_XERR = {fReader, "Lc_p_ORIVX_XERR"};
   TTreeReaderValue<Double_t> Lc_p_ORIVX_YERR = {fReader, "Lc_p_ORIVX_YERR"};
   TTreeReaderValue<Double_t> Lc_p_ORIVX_ZERR = {fReader, "Lc_p_ORIVX_ZERR"};
   TTreeReaderValue<Double_t> Lc_p_ORIVX_CHI2 = {fReader, "Lc_p_ORIVX_CHI2"};
   TTreeReaderValue<Int_t> Lc_p_ORIVX_NDOF = {fReader, "Lc_p_ORIVX_NDOF"};
   TTreeReaderValue<Double_t> Lc_p_P = {fReader, "Lc_p_P"};
   TTreeReaderValue<Double_t> Lc_p_PT = {fReader, "Lc_p_PT"};
   TTreeReaderValue<Double_t> Lc_p_PE = {fReader, "Lc_p_PE"};
   TTreeReaderValue<Double_t> Lc_p_PX = {fReader, "Lc_p_PX"};
   TTreeReaderValue<Double_t> Lc_p_PY = {fReader, "Lc_p_PY"};
   TTreeReaderValue<Double_t> Lc_p_PZ = {fReader, "Lc_p_PZ"};
   TTreeReaderValue<Double_t> Lc_p_M = {fReader, "Lc_p_M"};
   TTreeReaderValue<Int_t> Lc_p_ID = {fReader, "Lc_p_ID"};
   TTreeReaderValue<Double_t> Lc_p_PIDe = {fReader, "Lc_p_PIDe"};
   TTreeReaderValue<Double_t> Lc_p_PIDmu = {fReader, "Lc_p_PIDmu"};
   TTreeReaderValue<Double_t> Lc_p_PIDK = {fReader, "Lc_p_PIDK"};
   TTreeReaderValue<Double_t> Lc_p_PIDp = {fReader, "Lc_p_PIDp"};
   TTreeReaderValue<Double_t> Lc_p_ProbNNe = {fReader, "Lc_p_ProbNNe"};
   TTreeReaderValue<Double_t> Lc_p_ProbNNk = {fReader, "Lc_p_ProbNNk"};
   TTreeReaderValue<Double_t> Lc_p_ProbNNp = {fReader, "Lc_p_ProbNNp"};
   TTreeReaderValue<Double_t> Lc_p_ProbNNpi = {fReader, "Lc_p_ProbNNpi"};
   TTreeReaderValue<Double_t> Lc_p_ProbNNmu = {fReader, "Lc_p_ProbNNmu"};
   TTreeReaderValue<Double_t> Lc_p_ProbNNghost = {fReader, "Lc_p_ProbNNghost"};
   TTreeReaderValue<Bool_t> Lc_p_hasMuon = {fReader, "Lc_p_hasMuon"};
   TTreeReaderValue<Bool_t> Lc_p_isMuon = {fReader, "Lc_p_isMuon"};
   TTreeReaderValue<Bool_t> Lc_p_hasRich = {fReader, "Lc_p_hasRich"};
   TTreeReaderValue<Bool_t> Lc_p_hasCalo = {fReader, "Lc_p_hasCalo"};
   TTreeReaderValue<Int_t> Lc_p_TRACK_Type = {fReader, "Lc_p_TRACK_Type"};
   TTreeReaderValue<Int_t> Lc_p_TRACK_Key = {fReader, "Lc_p_TRACK_Key"};
   TTreeReaderValue<Double_t> Lc_p_TRACK_CHI2NDOF = {fReader, "Lc_p_TRACK_CHI2NDOF"};
   TTreeReaderValue<Double_t> Lc_p_TRACK_PCHI2 = {fReader, "Lc_p_TRACK_PCHI2"};
   TTreeReaderValue<Double_t> Lc_p_TRACK_MatchCHI2 = {fReader, "Lc_p_TRACK_MatchCHI2"};
   TTreeReaderValue<Double_t> Lc_p_TRACK_GhostProb = {fReader, "Lc_p_TRACK_GhostProb"};
   TTreeReaderValue<Double_t> Lc_p_TRACK_CloneDist = {fReader, "Lc_p_TRACK_CloneDist"};
   TTreeReaderValue<Double_t> Lc_p_TRACK_Likelihood = {fReader, "Lc_p_TRACK_Likelihood"};
   TTreeReaderValue<Double_t> Lc_h1_ETA = {fReader, "Lc_h1_ETA"};
   TTreeReaderValue<Double_t> Lc_h1_PHI = {fReader, "Lc_h1_PHI"};
   TTreeReaderValue<Double_t> Lc_h1_MC12TuneV4_ProbNNe = {fReader, "Lc_h1_MC12TuneV4_ProbNNe"};
   TTreeReaderValue<Double_t> Lc_h1_MC12TuneV4_ProbNNmu = {fReader, "Lc_h1_MC12TuneV4_ProbNNmu"};
   TTreeReaderValue<Double_t> Lc_h1_MC12TuneV4_ProbNNpi = {fReader, "Lc_h1_MC12TuneV4_ProbNNpi"};
   TTreeReaderValue<Double_t> Lc_h1_MC12TuneV4_ProbNNk = {fReader, "Lc_h1_MC12TuneV4_ProbNNk"};
   TTreeReaderValue<Double_t> Lc_h1_MC12TuneV4_ProbNNp = {fReader, "Lc_h1_MC12TuneV4_ProbNNp"};
   TTreeReaderValue<Double_t> Lc_h1_MC12TuneV4_ProbNNghost = {fReader, "Lc_h1_MC12TuneV4_ProbNNghost"};
   TTreeReaderValue<Double_t> Lc_h1_OWNPV_X = {fReader, "Lc_h1_OWNPV_X"};
   TTreeReaderValue<Double_t> Lc_h1_OWNPV_Y = {fReader, "Lc_h1_OWNPV_Y"};
   TTreeReaderValue<Double_t> Lc_h1_OWNPV_Z = {fReader, "Lc_h1_OWNPV_Z"};
   TTreeReaderValue<Double_t> Lc_h1_OWNPV_XERR = {fReader, "Lc_h1_OWNPV_XERR"};
   TTreeReaderValue<Double_t> Lc_h1_OWNPV_YERR = {fReader, "Lc_h1_OWNPV_YERR"};
   TTreeReaderValue<Double_t> Lc_h1_OWNPV_ZERR = {fReader, "Lc_h1_OWNPV_ZERR"};
   TTreeReaderValue<Double_t> Lc_h1_OWNPV_CHI2 = {fReader, "Lc_h1_OWNPV_CHI2"};
   TTreeReaderValue<Int_t> Lc_h1_OWNPV_NDOF = {fReader, "Lc_h1_OWNPV_NDOF"};
   TTreeReaderValue<Double_t> Lc_h1_IP_OWNPV = {fReader, "Lc_h1_IP_OWNPV"};
   TTreeReaderValue<Double_t> Lc_h1_IPCHI2_OWNPV = {fReader, "Lc_h1_IPCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Lc_h1_ORIVX_X = {fReader, "Lc_h1_ORIVX_X"};
   TTreeReaderValue<Double_t> Lc_h1_ORIVX_Y = {fReader, "Lc_h1_ORIVX_Y"};
   TTreeReaderValue<Double_t> Lc_h1_ORIVX_Z = {fReader, "Lc_h1_ORIVX_Z"};
   TTreeReaderValue<Double_t> Lc_h1_ORIVX_XERR = {fReader, "Lc_h1_ORIVX_XERR"};
   TTreeReaderValue<Double_t> Lc_h1_ORIVX_YERR = {fReader, "Lc_h1_ORIVX_YERR"};
   TTreeReaderValue<Double_t> Lc_h1_ORIVX_ZERR = {fReader, "Lc_h1_ORIVX_ZERR"};
   TTreeReaderValue<Double_t> Lc_h1_ORIVX_CHI2 = {fReader, "Lc_h1_ORIVX_CHI2"};
   TTreeReaderValue<Int_t> Lc_h1_ORIVX_NDOF = {fReader, "Lc_h1_ORIVX_NDOF"};
   TTreeReaderValue<Double_t> Lc_h1_P = {fReader, "Lc_h1_P"};
   TTreeReaderValue<Double_t> Lc_h1_PT = {fReader, "Lc_h1_PT"};
   TTreeReaderValue<Double_t> Lc_h1_PE = {fReader, "Lc_h1_PE"};
   TTreeReaderValue<Double_t> Lc_h1_PX = {fReader, "Lc_h1_PX"};
   TTreeReaderValue<Double_t> Lc_h1_PY = {fReader, "Lc_h1_PY"};
   TTreeReaderValue<Double_t> Lc_h1_PZ = {fReader, "Lc_h1_PZ"};
   TTreeReaderValue<Double_t> Lc_h1_M = {fReader, "Lc_h1_M"};
   TTreeReaderValue<Int_t> Lc_h1_ID = {fReader, "Lc_h1_ID"};
   TTreeReaderValue<Double_t> Lc_h1_PIDe = {fReader, "Lc_h1_PIDe"};
   TTreeReaderValue<Double_t> Lc_h1_PIDmu = {fReader, "Lc_h1_PIDmu"};
   TTreeReaderValue<Double_t> Lc_h1_PIDK = {fReader, "Lc_h1_PIDK"};
   TTreeReaderValue<Double_t> Lc_h1_PIDp = {fReader, "Lc_h1_PIDp"};
   TTreeReaderValue<Double_t> Lc_h1_ProbNNe = {fReader, "Lc_h1_ProbNNe"};
   TTreeReaderValue<Double_t> Lc_h1_ProbNNk = {fReader, "Lc_h1_ProbNNk"};
   TTreeReaderValue<Double_t> Lc_h1_ProbNNp = {fReader, "Lc_h1_ProbNNp"};
   TTreeReaderValue<Double_t> Lc_h1_ProbNNpi = {fReader, "Lc_h1_ProbNNpi"};
   TTreeReaderValue<Double_t> Lc_h1_ProbNNmu = {fReader, "Lc_h1_ProbNNmu"};
   TTreeReaderValue<Double_t> Lc_h1_ProbNNghost = {fReader, "Lc_h1_ProbNNghost"};
   TTreeReaderValue<Bool_t> Lc_h1_hasMuon = {fReader, "Lc_h1_hasMuon"};
   TTreeReaderValue<Bool_t> Lc_h1_isMuon = {fReader, "Lc_h1_isMuon"};
   TTreeReaderValue<Bool_t> Lc_h1_hasRich = {fReader, "Lc_h1_hasRich"};
   TTreeReaderValue<Bool_t> Lc_h1_hasCalo = {fReader, "Lc_h1_hasCalo"};
   TTreeReaderValue<Int_t> Lc_h1_TRACK_Type = {fReader, "Lc_h1_TRACK_Type"};
   TTreeReaderValue<Int_t> Lc_h1_TRACK_Key = {fReader, "Lc_h1_TRACK_Key"};
   TTreeReaderValue<Double_t> Lc_h1_TRACK_CHI2NDOF = {fReader, "Lc_h1_TRACK_CHI2NDOF"};
   TTreeReaderValue<Double_t> Lc_h1_TRACK_PCHI2 = {fReader, "Lc_h1_TRACK_PCHI2"};
   TTreeReaderValue<Double_t> Lc_h1_TRACK_MatchCHI2 = {fReader, "Lc_h1_TRACK_MatchCHI2"};
   TTreeReaderValue<Double_t> Lc_h1_TRACK_GhostProb = {fReader, "Lc_h1_TRACK_GhostProb"};
   TTreeReaderValue<Double_t> Lc_h1_TRACK_CloneDist = {fReader, "Lc_h1_TRACK_CloneDist"};
   TTreeReaderValue<Double_t> Lc_h1_TRACK_Likelihood = {fReader, "Lc_h1_TRACK_Likelihood"};
   TTreeReaderValue<Double_t> Lc_h2_ETA = {fReader, "Lc_h2_ETA"};
   TTreeReaderValue<Double_t> Lc_h2_PHI = {fReader, "Lc_h2_PHI"};
   TTreeReaderValue<Double_t> Lc_h2_MC12TuneV4_ProbNNe = {fReader, "Lc_h2_MC12TuneV4_ProbNNe"};
   TTreeReaderValue<Double_t> Lc_h2_MC12TuneV4_ProbNNmu = {fReader, "Lc_h2_MC12TuneV4_ProbNNmu"};
   TTreeReaderValue<Double_t> Lc_h2_MC12TuneV4_ProbNNpi = {fReader, "Lc_h2_MC12TuneV4_ProbNNpi"};
   TTreeReaderValue<Double_t> Lc_h2_MC12TuneV4_ProbNNk = {fReader, "Lc_h2_MC12TuneV4_ProbNNk"};
   TTreeReaderValue<Double_t> Lc_h2_MC12TuneV4_ProbNNp = {fReader, "Lc_h2_MC12TuneV4_ProbNNp"};
   TTreeReaderValue<Double_t> Lc_h2_MC12TuneV4_ProbNNghost = {fReader, "Lc_h2_MC12TuneV4_ProbNNghost"};
   TTreeReaderValue<Double_t> Lc_h2_OWNPV_X = {fReader, "Lc_h2_OWNPV_X"};
   TTreeReaderValue<Double_t> Lc_h2_OWNPV_Y = {fReader, "Lc_h2_OWNPV_Y"};
   TTreeReaderValue<Double_t> Lc_h2_OWNPV_Z = {fReader, "Lc_h2_OWNPV_Z"};
   TTreeReaderValue<Double_t> Lc_h2_OWNPV_XERR = {fReader, "Lc_h2_OWNPV_XERR"};
   TTreeReaderValue<Double_t> Lc_h2_OWNPV_YERR = {fReader, "Lc_h2_OWNPV_YERR"};
   TTreeReaderValue<Double_t> Lc_h2_OWNPV_ZERR = {fReader, "Lc_h2_OWNPV_ZERR"};
   TTreeReaderValue<Double_t> Lc_h2_OWNPV_CHI2 = {fReader, "Lc_h2_OWNPV_CHI2"};
   TTreeReaderValue<Int_t> Lc_h2_OWNPV_NDOF = {fReader, "Lc_h2_OWNPV_NDOF"};
   TTreeReaderValue<Double_t> Lc_h2_IP_OWNPV = {fReader, "Lc_h2_IP_OWNPV"};
   TTreeReaderValue<Double_t> Lc_h2_IPCHI2_OWNPV = {fReader, "Lc_h2_IPCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Lc_h2_ORIVX_X = {fReader, "Lc_h2_ORIVX_X"};
   TTreeReaderValue<Double_t> Lc_h2_ORIVX_Y = {fReader, "Lc_h2_ORIVX_Y"};
   TTreeReaderValue<Double_t> Lc_h2_ORIVX_Z = {fReader, "Lc_h2_ORIVX_Z"};
   TTreeReaderValue<Double_t> Lc_h2_ORIVX_XERR = {fReader, "Lc_h2_ORIVX_XERR"};
   TTreeReaderValue<Double_t> Lc_h2_ORIVX_YERR = {fReader, "Lc_h2_ORIVX_YERR"};
   TTreeReaderValue<Double_t> Lc_h2_ORIVX_ZERR = {fReader, "Lc_h2_ORIVX_ZERR"};
   TTreeReaderValue<Double_t> Lc_h2_ORIVX_CHI2 = {fReader, "Lc_h2_ORIVX_CHI2"};
   TTreeReaderValue<Int_t> Lc_h2_ORIVX_NDOF = {fReader, "Lc_h2_ORIVX_NDOF"};
   TTreeReaderValue<Double_t> Lc_h2_P = {fReader, "Lc_h2_P"};
   TTreeReaderValue<Double_t> Lc_h2_PT = {fReader, "Lc_h2_PT"};
   TTreeReaderValue<Double_t> Lc_h2_PE = {fReader, "Lc_h2_PE"};
   TTreeReaderValue<Double_t> Lc_h2_PX = {fReader, "Lc_h2_PX"};
   TTreeReaderValue<Double_t> Lc_h2_PY = {fReader, "Lc_h2_PY"};
   TTreeReaderValue<Double_t> Lc_h2_PZ = {fReader, "Lc_h2_PZ"};
   TTreeReaderValue<Double_t> Lc_h2_M = {fReader, "Lc_h2_M"};
   TTreeReaderValue<Int_t> Lc_h2_ID = {fReader, "Lc_h2_ID"};
   TTreeReaderValue<Double_t> Lc_h2_PIDe = {fReader, "Lc_h2_PIDe"};
   TTreeReaderValue<Double_t> Lc_h2_PIDmu = {fReader, "Lc_h2_PIDmu"};
   TTreeReaderValue<Double_t> Lc_h2_PIDK = {fReader, "Lc_h2_PIDK"};
   TTreeReaderValue<Double_t> Lc_h2_PIDp = {fReader, "Lc_h2_PIDp"};
   TTreeReaderValue<Double_t> Lc_h2_ProbNNe = {fReader, "Lc_h2_ProbNNe"};
   TTreeReaderValue<Double_t> Lc_h2_ProbNNk = {fReader, "Lc_h2_ProbNNk"};
   TTreeReaderValue<Double_t> Lc_h2_ProbNNp = {fReader, "Lc_h2_ProbNNp"};
   TTreeReaderValue<Double_t> Lc_h2_ProbNNpi = {fReader, "Lc_h2_ProbNNpi"};
   TTreeReaderValue<Double_t> Lc_h2_ProbNNmu = {fReader, "Lc_h2_ProbNNmu"};
   TTreeReaderValue<Double_t> Lc_h2_ProbNNghost = {fReader, "Lc_h2_ProbNNghost"};
   TTreeReaderValue<Bool_t> Lc_h2_hasMuon = {fReader, "Lc_h2_hasMuon"};
   TTreeReaderValue<Bool_t> Lc_h2_isMuon = {fReader, "Lc_h2_isMuon"};
   TTreeReaderValue<Bool_t> Lc_h2_hasRich = {fReader, "Lc_h2_hasRich"};
   TTreeReaderValue<Bool_t> Lc_h2_hasCalo = {fReader, "Lc_h2_hasCalo"};
   TTreeReaderValue<Int_t> Lc_h2_TRACK_Type = {fReader, "Lc_h2_TRACK_Type"};
   TTreeReaderValue<Int_t> Lc_h2_TRACK_Key = {fReader, "Lc_h2_TRACK_Key"};
   TTreeReaderValue<Double_t> Lc_h2_TRACK_CHI2NDOF = {fReader, "Lc_h2_TRACK_CHI2NDOF"};
   TTreeReaderValue<Double_t> Lc_h2_TRACK_PCHI2 = {fReader, "Lc_h2_TRACK_PCHI2"};
   TTreeReaderValue<Double_t> Lc_h2_TRACK_MatchCHI2 = {fReader, "Lc_h2_TRACK_MatchCHI2"};
   TTreeReaderValue<Double_t> Lc_h2_TRACK_GhostProb = {fReader, "Lc_h2_TRACK_GhostProb"};
   TTreeReaderValue<Double_t> Lc_h2_TRACK_CloneDist = {fReader, "Lc_h2_TRACK_CloneDist"};
   TTreeReaderValue<Double_t> Lc_h2_TRACK_Likelihood = {fReader, "Lc_h2_TRACK_Likelihood"};
   TTreeReaderValue<Double_t> Lb_mu_ETA = {fReader, "Lb_mu_ETA"};
   TTreeReaderValue<Double_t> Lb_mu_PHI = {fReader, "Lb_mu_PHI"};
   TTreeReaderValue<Double_t> Lb_mu_MC12TuneV4_ProbNNe = {fReader, "Lb_mu_MC12TuneV4_ProbNNe"};
   TTreeReaderValue<Double_t> Lb_mu_MC12TuneV4_ProbNNmu = {fReader, "Lb_mu_MC12TuneV4_ProbNNmu"};
   TTreeReaderValue<Double_t> Lb_mu_MC12TuneV4_ProbNNpi = {fReader, "Lb_mu_MC12TuneV4_ProbNNpi"};
   TTreeReaderValue<Double_t> Lb_mu_MC12TuneV4_ProbNNk = {fReader, "Lb_mu_MC12TuneV4_ProbNNk"};
   TTreeReaderValue<Double_t> Lb_mu_MC12TuneV4_ProbNNp = {fReader, "Lb_mu_MC12TuneV4_ProbNNp"};
   TTreeReaderValue<Double_t> Lb_mu_MC12TuneV4_ProbNNghost = {fReader, "Lb_mu_MC12TuneV4_ProbNNghost"};
   TTreeReaderValue<Double_t> Lb_mu_OWNPV_X = {fReader, "Lb_mu_OWNPV_X"};
   TTreeReaderValue<Double_t> Lb_mu_OWNPV_Y = {fReader, "Lb_mu_OWNPV_Y"};
   TTreeReaderValue<Double_t> Lb_mu_OWNPV_Z = {fReader, "Lb_mu_OWNPV_Z"};
   TTreeReaderValue<Double_t> Lb_mu_OWNPV_XERR = {fReader, "Lb_mu_OWNPV_XERR"};
   TTreeReaderValue<Double_t> Lb_mu_OWNPV_YERR = {fReader, "Lb_mu_OWNPV_YERR"};
   TTreeReaderValue<Double_t> Lb_mu_OWNPV_ZERR = {fReader, "Lb_mu_OWNPV_ZERR"};
   TTreeReaderValue<Double_t> Lb_mu_OWNPV_CHI2 = {fReader, "Lb_mu_OWNPV_CHI2"};
   TTreeReaderValue<Int_t> Lb_mu_OWNPV_NDOF = {fReader, "Lb_mu_OWNPV_NDOF"};
   TTreeReaderValue<Double_t> Lb_mu_IP_OWNPV = {fReader, "Lb_mu_IP_OWNPV"};
   TTreeReaderValue<Double_t> Lb_mu_IPCHI2_OWNPV = {fReader, "Lb_mu_IPCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Lb_mu_ORIVX_X = {fReader, "Lb_mu_ORIVX_X"};
   TTreeReaderValue<Double_t> Lb_mu_ORIVX_Y = {fReader, "Lb_mu_ORIVX_Y"};
   TTreeReaderValue<Double_t> Lb_mu_ORIVX_Z = {fReader, "Lb_mu_ORIVX_Z"};
   TTreeReaderValue<Double_t> Lb_mu_ORIVX_XERR = {fReader, "Lb_mu_ORIVX_XERR"};
   TTreeReaderValue<Double_t> Lb_mu_ORIVX_YERR = {fReader, "Lb_mu_ORIVX_YERR"};
   TTreeReaderValue<Double_t> Lb_mu_ORIVX_ZERR = {fReader, "Lb_mu_ORIVX_ZERR"};
   TTreeReaderValue<Double_t> Lb_mu_ORIVX_CHI2 = {fReader, "Lb_mu_ORIVX_CHI2"};
   TTreeReaderValue<Int_t> Lb_mu_ORIVX_NDOF = {fReader, "Lb_mu_ORIVX_NDOF"};
   TTreeReaderValue<Double_t> Lb_mu_P = {fReader, "Lb_mu_P"};
   TTreeReaderValue<Double_t> Lb_mu_PT = {fReader, "Lb_mu_PT"};
   TTreeReaderValue<Double_t> Lb_mu_PE = {fReader, "Lb_mu_PE"};
   TTreeReaderValue<Double_t> Lb_mu_PX = {fReader, "Lb_mu_PX"};
   TTreeReaderValue<Double_t> Lb_mu_PY = {fReader, "Lb_mu_PY"};
   TTreeReaderValue<Double_t> Lb_mu_PZ = {fReader, "Lb_mu_PZ"};
   TTreeReaderValue<Double_t> Lb_mu_M = {fReader, "Lb_mu_M"};
   TTreeReaderValue<Int_t> Lb_mu_ID = {fReader, "Lb_mu_ID"};
   TTreeReaderValue<Double_t> Lb_mu_PIDe = {fReader, "Lb_mu_PIDe"};
   TTreeReaderValue<Double_t> Lb_mu_PIDmu = {fReader, "Lb_mu_PIDmu"};
   TTreeReaderValue<Double_t> Lb_mu_PIDK = {fReader, "Lb_mu_PIDK"};
   TTreeReaderValue<Double_t> Lb_mu_PIDp = {fReader, "Lb_mu_PIDp"};
   TTreeReaderValue<Double_t> Lb_mu_ProbNNe = {fReader, "Lb_mu_ProbNNe"};
   TTreeReaderValue<Double_t> Lb_mu_ProbNNk = {fReader, "Lb_mu_ProbNNk"};
   TTreeReaderValue<Double_t> Lb_mu_ProbNNp = {fReader, "Lb_mu_ProbNNp"};
   TTreeReaderValue<Double_t> Lb_mu_ProbNNpi = {fReader, "Lb_mu_ProbNNpi"};
   TTreeReaderValue<Double_t> Lb_mu_ProbNNmu = {fReader, "Lb_mu_ProbNNmu"};
   TTreeReaderValue<Double_t> Lb_mu_ProbNNghost = {fReader, "Lb_mu_ProbNNghost"};
   TTreeReaderValue<Bool_t> Lb_mu_hasMuon = {fReader, "Lb_mu_hasMuon"};
   TTreeReaderValue<Bool_t> Lb_mu_isMuon = {fReader, "Lb_mu_isMuon"};
   TTreeReaderValue<Bool_t> Lb_mu_hasRich = {fReader, "Lb_mu_hasRich"};
   TTreeReaderValue<Bool_t> Lb_mu_hasCalo = {fReader, "Lb_mu_hasCalo"};
   TTreeReaderValue<Int_t> Lb_mu_TRACK_Type = {fReader, "Lb_mu_TRACK_Type"};
   TTreeReaderValue<Int_t> Lb_mu_TRACK_Key = {fReader, "Lb_mu_TRACK_Key"};
   TTreeReaderValue<Double_t> Lb_mu_TRACK_CHI2NDOF = {fReader, "Lb_mu_TRACK_CHI2NDOF"};
   TTreeReaderValue<Double_t> Lb_mu_TRACK_PCHI2 = {fReader, "Lb_mu_TRACK_PCHI2"};
   TTreeReaderValue<Double_t> Lb_mu_TRACK_MatchCHI2 = {fReader, "Lb_mu_TRACK_MatchCHI2"};
   TTreeReaderValue<Double_t> Lb_mu_TRACK_GhostProb = {fReader, "Lb_mu_TRACK_GhostProb"};
   TTreeReaderValue<Double_t> Lb_mu_TRACK_CloneDist = {fReader, "Lb_mu_TRACK_CloneDist"};
   TTreeReaderValue<Double_t> Lb_mu_TRACK_Likelihood = {fReader, "Lb_mu_TRACK_Likelihood"};
   TTreeReaderValue<Bool_t> Lb_mu_L0Global_Dec = {fReader, "Lb_mu_L0Global_Dec"};
   TTreeReaderValue<Bool_t> Lb_mu_L0Global_TIS = {fReader, "Lb_mu_L0Global_TIS"};
   TTreeReaderValue<Bool_t> Lb_mu_L0Global_TOS = {fReader, "Lb_mu_L0Global_TOS"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt1Global_Dec = {fReader, "Lb_mu_Hlt1Global_Dec"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt1Global_TIS = {fReader, "Lb_mu_Hlt1Global_TIS"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt1Global_TOS = {fReader, "Lb_mu_Hlt1Global_TOS"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt1Phys_Dec = {fReader, "Lb_mu_Hlt1Phys_Dec"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt1Phys_TIS = {fReader, "Lb_mu_Hlt1Phys_TIS"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt1Phys_TOS = {fReader, "Lb_mu_Hlt1Phys_TOS"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt2Global_Dec = {fReader, "Lb_mu_Hlt2Global_Dec"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt2Global_TIS = {fReader, "Lb_mu_Hlt2Global_TIS"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt2Global_TOS = {fReader, "Lb_mu_Hlt2Global_TOS"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt2Phys_Dec = {fReader, "Lb_mu_Hlt2Phys_Dec"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt2Phys_TIS = {fReader, "Lb_mu_Hlt2Phys_TIS"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt2Phys_TOS = {fReader, "Lb_mu_Hlt2Phys_TOS"};
   TTreeReaderValue<Bool_t> Lb_mu_L0MuonDecision_Dec = {fReader, "Lb_mu_L0MuonDecision_Dec"};
   TTreeReaderValue<Bool_t> Lb_mu_L0MuonDecision_TIS = {fReader, "Lb_mu_L0MuonDecision_TIS"};
   TTreeReaderValue<Bool_t> Lb_mu_L0MuonDecision_TOS = {fReader, "Lb_mu_L0MuonDecision_TOS"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt1TrackMuonDecision_Dec = {fReader, "Lb_mu_Hlt1TrackMuonDecision_Dec"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt1TrackMuonDecision_TIS = {fReader, "Lb_mu_Hlt1TrackMuonDecision_TIS"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt1TrackMuonDecision_TOS = {fReader, "Lb_mu_Hlt1TrackMuonDecision_TOS"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt1TrackAllL0Decision_Dec = {fReader, "Lb_mu_Hlt1TrackAllL0Decision_Dec"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt1TrackAllL0Decision_TIS = {fReader, "Lb_mu_Hlt1TrackAllL0Decision_TIS"};
   TTreeReaderValue<Bool_t> Lb_mu_Hlt1TrackAllL0Decision_TOS = {fReader, "Lb_mu_Hlt1TrackAllL0Decision_TOS"};
   TTreeReaderValue<UInt_t> nCandidate = {fReader, "nCandidate"};
   TTreeReaderValue<ULong64_t> totCandidates = {fReader, "totCandidates"};
   TTreeReaderValue<ULong64_t> EventInSequence = {fReader, "EventInSequence"};
   TTreeReaderValue<UInt_t> runNumber = {fReader, "runNumber"};
   TTreeReaderValue<ULong64_t> eventNumber = {fReader, "eventNumber"};
   TTreeReaderValue<UInt_t> BCID = {fReader, "BCID"};
   TTreeReaderValue<Int_t> BCType = {fReader, "BCType"};
   TTreeReaderValue<UInt_t> OdinTCK = {fReader, "OdinTCK"};
   TTreeReaderValue<UInt_t> L0DUTCK = {fReader, "L0DUTCK"};
   TTreeReaderValue<UInt_t> HLT1TCK = {fReader, "HLT1TCK"};
   TTreeReaderValue<UInt_t> HLT2TCK = {fReader, "HLT2TCK"};
   TTreeReaderValue<ULong64_t> GpsTime = {fReader, "GpsTime"};
   TTreeReaderValue<Short_t> Polarity = {fReader, "Polarity"};
   TTreeReaderValue<Int_t> nPV = {fReader, "nPV"};
   TTreeReaderArray<Float_t> PVX = {fReader, "PVX"};
   TTreeReaderArray<Float_t> PVY = {fReader, "PVY"};
   TTreeReaderArray<Float_t> PVZ = {fReader, "PVZ"};
   TTreeReaderArray<Float_t> PVXERR = {fReader, "PVXERR"};
   TTreeReaderArray<Float_t> PVYERR = {fReader, "PVYERR"};
   TTreeReaderArray<Float_t> PVZERR = {fReader, "PVZERR"};
   TTreeReaderArray<Float_t> PVCHI2 = {fReader, "PVCHI2"};
   TTreeReaderArray<Float_t> PVNDOF = {fReader, "PVNDOF"};
   TTreeReaderArray<Float_t> PVNTRACKS = {fReader, "PVNTRACKS"};
   TTreeReaderValue<Int_t> nPVs = {fReader, "nPVs"};
   TTreeReaderValue<Int_t> nTracks = {fReader, "nTracks"};
   TTreeReaderValue<Int_t> nLongTracks = {fReader, "nLongTracks"};
   TTreeReaderValue<Int_t> nDownstreamTracks = {fReader, "nDownstreamTracks"};
   TTreeReaderValue<Int_t> nUpstreamTracks = {fReader, "nUpstreamTracks"};
   TTreeReaderValue<Int_t> nVeloTracks = {fReader, "nVeloTracks"};
   TTreeReaderValue<Int_t> nTTracks = {fReader, "nTTracks"};
   TTreeReaderValue<Int_t> nBackTracks = {fReader, "nBackTracks"};
   TTreeReaderValue<Int_t> nRich1Hits = {fReader, "nRich1Hits"};
   TTreeReaderValue<Int_t> nRich2Hits = {fReader, "nRich2Hits"};
   TTreeReaderValue<Int_t> nVeloClusters = {fReader, "nVeloClusters"};
   TTreeReaderValue<Int_t> nITClusters = {fReader, "nITClusters"};
   TTreeReaderValue<Int_t> nTTClusters = {fReader, "nTTClusters"};
   TTreeReaderValue<Int_t> nOTClusters = {fReader, "nOTClusters"};
   TTreeReaderValue<Int_t> nSPDHits = {fReader, "nSPDHits"};
   TTreeReaderValue<Int_t> nMuonCoordsS0 = {fReader, "nMuonCoordsS0"};
   TTreeReaderValue<Int_t> nMuonCoordsS1 = {fReader, "nMuonCoordsS1"};
   TTreeReaderValue<Int_t> nMuonCoordsS2 = {fReader, "nMuonCoordsS2"};
   TTreeReaderValue<Int_t> nMuonCoordsS3 = {fReader, "nMuonCoordsS3"};
   TTreeReaderValue<Int_t> nMuonCoordsS4 = {fReader, "nMuonCoordsS4"};
   TTreeReaderValue<Int_t> nMuonTracks = {fReader, "nMuonTracks"};


   FirstCut(TTree * /*tree*/ =0) { }
   virtual ~FirstCut() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(FirstCut,0);

};

#endif

#ifdef FirstCut_cxx
void FirstCut::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t FirstCut::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef FirstCut_cxx
