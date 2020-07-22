//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul 22 14:06:09 2020 by ROOT version 6.18/00
// from TChain Lc2pKKTuple/DecayTree/
//////////////////////////////////////////////////////////

#ifndef BSubExample_h
#define BSubExample_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class BSubExample : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Double_t> Lcplus_ETA = {fReader, "Lcplus_ETA"};
   TTreeReaderValue<Double_t> Lcplus_PHI = {fReader, "Lcplus_PHI"};
   TTreeReaderValue<Double_t> Lcplus_ENDVERTEX_X = {fReader, "Lcplus_ENDVERTEX_X"};
   TTreeReaderValue<Double_t> Lcplus_ENDVERTEX_Y = {fReader, "Lcplus_ENDVERTEX_Y"};
   TTreeReaderValue<Double_t> Lcplus_ENDVERTEX_Z = {fReader, "Lcplus_ENDVERTEX_Z"};
   TTreeReaderValue<Double_t> Lcplus_ENDVERTEX_XERR = {fReader, "Lcplus_ENDVERTEX_XERR"};
   TTreeReaderValue<Double_t> Lcplus_ENDVERTEX_YERR = {fReader, "Lcplus_ENDVERTEX_YERR"};
   TTreeReaderValue<Double_t> Lcplus_ENDVERTEX_ZERR = {fReader, "Lcplus_ENDVERTEX_ZERR"};
   TTreeReaderValue<Double_t> Lcplus_ENDVERTEX_CHI2 = {fReader, "Lcplus_ENDVERTEX_CHI2"};
   TTreeReaderValue<Int_t> Lcplus_ENDVERTEX_NDOF = {fReader, "Lcplus_ENDVERTEX_NDOF"};
   TTreeReaderValue<Double_t> Lcplus_OWNPV_X = {fReader, "Lcplus_OWNPV_X"};
   TTreeReaderValue<Double_t> Lcplus_OWNPV_Y = {fReader, "Lcplus_OWNPV_Y"};
   TTreeReaderValue<Double_t> Lcplus_OWNPV_Z = {fReader, "Lcplus_OWNPV_Z"};
   TTreeReaderValue<Double_t> Lcplus_OWNPV_XERR = {fReader, "Lcplus_OWNPV_XERR"};
   TTreeReaderValue<Double_t> Lcplus_OWNPV_YERR = {fReader, "Lcplus_OWNPV_YERR"};
   TTreeReaderValue<Double_t> Lcplus_OWNPV_ZERR = {fReader, "Lcplus_OWNPV_ZERR"};
   TTreeReaderValue<Double_t> Lcplus_OWNPV_CHI2 = {fReader, "Lcplus_OWNPV_CHI2"};
   TTreeReaderValue<Int_t> Lcplus_OWNPV_NDOF = {fReader, "Lcplus_OWNPV_NDOF"};
   TTreeReaderValue<Double_t> Lcplus_IP_OWNPV = {fReader, "Lcplus_IP_OWNPV"};
   TTreeReaderValue<Double_t> Lcplus_IPCHI2_OWNPV = {fReader, "Lcplus_IPCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Lcplus_FD_OWNPV = {fReader, "Lcplus_FD_OWNPV"};
   TTreeReaderValue<Double_t> Lcplus_FDCHI2_OWNPV = {fReader, "Lcplus_FDCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Lcplus_DIRA_OWNPV = {fReader, "Lcplus_DIRA_OWNPV"};
   TTreeReaderValue<Double_t> Lcplus_P = {fReader, "Lcplus_P"};
   TTreeReaderValue<Double_t> Lcplus_PT = {fReader, "Lcplus_PT"};
   TTreeReaderValue<Double_t> Lcplus_PE = {fReader, "Lcplus_PE"};
   TTreeReaderValue<Double_t> Lcplus_PX = {fReader, "Lcplus_PX"};
   TTreeReaderValue<Double_t> Lcplus_PY = {fReader, "Lcplus_PY"};
   TTreeReaderValue<Double_t> Lcplus_PZ = {fReader, "Lcplus_PZ"};
   TTreeReaderValue<Double_t> Lcplus_MM = {fReader, "Lcplus_MM"};
   TTreeReaderValue<Double_t> Lcplus_MMERR = {fReader, "Lcplus_MMERR"};
   TTreeReaderValue<Double_t> Lcplus_M = {fReader, "Lcplus_M"};
   TTreeReaderValue<Int_t> Lcplus_ID = {fReader, "Lcplus_ID"};
   TTreeReaderValue<Bool_t> Lcplus_L0Global_Dec = {fReader, "Lcplus_L0Global_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_L0Global_TIS = {fReader, "Lcplus_L0Global_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_L0Global_TOS = {fReader, "Lcplus_L0Global_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1Global_Dec = {fReader, "Lcplus_Hlt1Global_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1Global_TIS = {fReader, "Lcplus_Hlt1Global_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1Global_TOS = {fReader, "Lcplus_Hlt1Global_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1Phys_Dec = {fReader, "Lcplus_Hlt1Phys_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1Phys_TIS = {fReader, "Lcplus_Hlt1Phys_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1Phys_TOS = {fReader, "Lcplus_Hlt1Phys_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2Global_Dec = {fReader, "Lcplus_Hlt2Global_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2Global_TIS = {fReader, "Lcplus_Hlt2Global_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2Global_TOS = {fReader, "Lcplus_Hlt2Global_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2Phys_Dec = {fReader, "Lcplus_Hlt2Phys_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2Phys_TIS = {fReader, "Lcplus_Hlt2Phys_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2Phys_TOS = {fReader, "Lcplus_Hlt2Phys_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_L0MuonDecision_Dec = {fReader, "Lcplus_L0MuonDecision_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_L0MuonDecision_TIS = {fReader, "Lcplus_L0MuonDecision_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_L0MuonDecision_TOS = {fReader, "Lcplus_L0MuonDecision_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_L0DiMuonDecisionL0HadronDecision_Dec = {fReader, "Lcplus_L0DiMuonDecisionL0HadronDecision_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_L0DiMuonDecisionL0HadronDecision_TIS = {fReader, "Lcplus_L0DiMuonDecisionL0HadronDecision_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_L0DiMuonDecisionL0HadronDecision_TOS = {fReader, "Lcplus_L0DiMuonDecisionL0HadronDecision_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_L0ElectronDecision_Dec = {fReader, "Lcplus_L0ElectronDecision_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_L0ElectronDecision_TIS = {fReader, "Lcplus_L0ElectronDecision_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_L0ElectronDecision_TOS = {fReader, "Lcplus_L0ElectronDecision_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_L0PhotonDecision_Dec = {fReader, "Lcplus_L0PhotonDecision_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_L0PhotonDecision_TIS = {fReader, "Lcplus_L0PhotonDecision_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_L0PhotonDecision_TOS = {fReader, "Lcplus_L0PhotonDecision_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TrackMVADecision_Dec = {fReader, "Lcplus_Hlt1TrackMVADecision_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TrackMVADecision_TIS = {fReader, "Lcplus_Hlt1TrackMVADecision_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TrackMVADecision_TOS = {fReader, "Lcplus_Hlt1TrackMVADecision_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TwoTrackMVADecision_Dec = {fReader, "Lcplus_Hlt1TwoTrackMVADecision_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TwoTrackMVADecision_TIS = {fReader, "Lcplus_Hlt1TwoTrackMVADecision_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TwoTrackMVADecision_TOS = {fReader, "Lcplus_Hlt1TwoTrackMVADecision_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TrackMVATightDecision_Dec = {fReader, "Lcplus_Hlt1TrackMVATightDecision_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TrackMVATightDecision_TIS = {fReader, "Lcplus_Hlt1TrackMVATightDecision_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TrackMVATightDecision_TOS = {fReader, "Lcplus_Hlt1TrackMVATightDecision_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TwoTrackMVATightDecision_Dec = {fReader, "Lcplus_Hlt1TwoTrackMVATightDecision_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TwoTrackMVATightDecision_TIS = {fReader, "Lcplus_Hlt1TwoTrackMVATightDecision_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TwoTrackMVATightDecision_TOS = {fReader, "Lcplus_Hlt1TwoTrackMVATightDecision_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TrackMuonDecision_Dec = {fReader, "Lcplus_Hlt1TrackMuonDecision_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TrackMuonDecision_TIS = {fReader, "Lcplus_Hlt1TrackMuonDecision_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TrackMuonDecision_TOS = {fReader, "Lcplus_Hlt1TrackMuonDecision_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TrackMuonMVADecision_Dec = {fReader, "Lcplus_Hlt1TrackMuonMVADecision_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TrackMuonMVADecision_TIS = {fReader, "Lcplus_Hlt1TrackMuonMVADecision_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt1TrackMuonMVADecision_TOS = {fReader, "Lcplus_Hlt1TrackMuonMVADecision_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2Topo2BodyDecision_Dec = {fReader, "Lcplus_Hlt2Topo2BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2Topo2BodyDecision_TIS = {fReader, "Lcplus_Hlt2Topo2BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2Topo2BodyDecision_TOS = {fReader, "Lcplus_Hlt2Topo2BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2Topo3BodyDecision_Dec = {fReader, "Lcplus_Hlt2Topo3BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2Topo3BodyDecision_TIS = {fReader, "Lcplus_Hlt2Topo3BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2Topo3BodyDecision_TOS = {fReader, "Lcplus_Hlt2Topo3BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2Topo4BodyDecision_Dec = {fReader, "Lcplus_Hlt2Topo4BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2Topo4BodyDecision_TIS = {fReader, "Lcplus_Hlt2Topo4BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2Topo4BodyDecision_TOS = {fReader, "Lcplus_Hlt2Topo4BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2TopoMu2BodyDecision_Dec = {fReader, "Lcplus_Hlt2TopoMu2BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2TopoMu2BodyDecision_TIS = {fReader, "Lcplus_Hlt2TopoMu2BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2TopoMu2BodyDecision_TOS = {fReader, "Lcplus_Hlt2TopoMu2BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2TopoMu3BodyDecision_Dec = {fReader, "Lcplus_Hlt2TopoMu3BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2TopoMu3BodyDecision_TIS = {fReader, "Lcplus_Hlt2TopoMu3BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2TopoMu3BodyDecision_TOS = {fReader, "Lcplus_Hlt2TopoMu3BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2TopoMu4BodyDecision_Dec = {fReader, "Lcplus_Hlt2TopoMu4BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2TopoMu4BodyDecision_TIS = {fReader, "Lcplus_Hlt2TopoMu4BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Lcplus_Hlt2TopoMu4BodyDecision_TOS = {fReader, "Lcplus_Hlt2TopoMu4BodyDecision_TOS"};
   TTreeReaderValue<Double_t> Lcplus_Loki_BPVCOV_XX = {fReader, "Lcplus_Loki_BPVCOV_XX"};
   TTreeReaderValue<Double_t> Lcplus_Loki_BPVCOV_XY = {fReader, "Lcplus_Loki_BPVCOV_XY"};
   TTreeReaderValue<Double_t> Lcplus_Loki_BPVCOV_XZ = {fReader, "Lcplus_Loki_BPVCOV_XZ"};
   TTreeReaderValue<Double_t> Lcplus_Loki_BPVCOV_YY = {fReader, "Lcplus_Loki_BPVCOV_YY"};
   TTreeReaderValue<Double_t> Lcplus_Loki_BPVCOV_YZ = {fReader, "Lcplus_Loki_BPVCOV_YZ"};
   TTreeReaderValue<Double_t> Lcplus_Loki_BPVCOV_ZZ = {fReader, "Lcplus_Loki_BPVCOV_ZZ"};
   TTreeReaderValue<Double_t> Lcplus_Loki_BPVLTIME = {fReader, "Lcplus_Loki_BPVLTIME"};
   TTreeReaderValue<Double_t> Lcplus_Loki_BPVX = {fReader, "Lcplus_Loki_BPVX"};
   TTreeReaderValue<Double_t> Lcplus_Loki_BPVY = {fReader, "Lcplus_Loki_BPVY"};
   TTreeReaderValue<Double_t> Lcplus_Loki_BPVZ = {fReader, "Lcplus_Loki_BPVZ"};
   TTreeReaderValue<Double_t> Lcplus_Loki_DOCACHI2MAX = {fReader, "Lcplus_Loki_DOCACHI2MAX"};
   TTreeReaderValue<Double_t> Lcplus_Loki_DOCAMAX = {fReader, "Lcplus_Loki_DOCAMAX"};
   TTreeReaderValue<Double_t> Lcplus_Loki_SUMPT = {fReader, "Lcplus_Loki_SUMPT"};
   TTreeReaderValue<Int_t> Lcplus_ConsLc_nPV = {fReader, "Lcplus_ConsLc_nPV"};
   TTreeReaderArray<Float_t> Lcplus_ConsLc_M = {fReader, "Lcplus_ConsLc_M"};
   TTreeReaderArray<Float_t> Lcplus_ConsLc_MERR = {fReader, "Lcplus_ConsLc_MERR"};
   TTreeReaderArray<Float_t> Lcplus_ConsLc_P = {fReader, "Lcplus_ConsLc_P"};
   TTreeReaderArray<Float_t> Lcplus_ConsLc_PERR = {fReader, "Lcplus_ConsLc_PERR"};
   TTreeReaderArray<Float_t> Lcplus_ConsLc_PV_X = {fReader, "Lcplus_ConsLc_PV_X"};
   TTreeReaderArray<Float_t> Lcplus_ConsLc_PV_Y = {fReader, "Lcplus_ConsLc_PV_Y"};
   TTreeReaderArray<Float_t> Lcplus_ConsLc_PV_Z = {fReader, "Lcplus_ConsLc_PV_Z"};
   TTreeReaderArray<Float_t> Lcplus_ConsLc_PV_key = {fReader, "Lcplus_ConsLc_PV_key"};
   TTreeReaderArray<Float_t> Lcplus_ConsLc_chi2 = {fReader, "Lcplus_ConsLc_chi2"};
   TTreeReaderArray<Float_t> Lcplus_ConsLc_ctau = {fReader, "Lcplus_ConsLc_ctau"};
   TTreeReaderArray<Float_t> Lcplus_ConsLc_ctauErr = {fReader, "Lcplus_ConsLc_ctauErr"};
   TTreeReaderArray<Float_t> Lcplus_ConsLc_decayLength = {fReader, "Lcplus_ConsLc_decayLength"};
   TTreeReaderArray<Float_t> Lcplus_ConsLc_decayLengthErr = {fReader, "Lcplus_ConsLc_decayLengthErr"};
   TTreeReaderArray<Float_t> Lcplus_ConsLc_nDOF = {fReader, "Lcplus_ConsLc_nDOF"};
   TTreeReaderArray<Float_t> Lcplus_ConsLc_nIter = {fReader, "Lcplus_ConsLc_nIter"};
   TTreeReaderArray<Float_t> Lcplus_ConsLc_status = {fReader, "Lcplus_ConsLc_status"};
   TTreeReaderValue<Double_t> Lcplus_TAU = {fReader, "Lcplus_TAU"};
   TTreeReaderValue<Double_t> Lcplus_TAUERR = {fReader, "Lcplus_TAUERR"};
   TTreeReaderValue<Double_t> Lcplus_TAUCHI2 = {fReader, "Lcplus_TAUCHI2"};
   TTreeReaderValue<Double_t> Proton_ETA = {fReader, "Proton_ETA"};
   TTreeReaderValue<Double_t> Proton_PHI = {fReader, "Proton_PHI"};
   TTreeReaderValue<Double_t> Proton_OWNPV_X = {fReader, "Proton_OWNPV_X"};
   TTreeReaderValue<Double_t> Proton_OWNPV_Y = {fReader, "Proton_OWNPV_Y"};
   TTreeReaderValue<Double_t> Proton_OWNPV_Z = {fReader, "Proton_OWNPV_Z"};
   TTreeReaderValue<Double_t> Proton_OWNPV_XERR = {fReader, "Proton_OWNPV_XERR"};
   TTreeReaderValue<Double_t> Proton_OWNPV_YERR = {fReader, "Proton_OWNPV_YERR"};
   TTreeReaderValue<Double_t> Proton_OWNPV_ZERR = {fReader, "Proton_OWNPV_ZERR"};
   TTreeReaderValue<Double_t> Proton_OWNPV_CHI2 = {fReader, "Proton_OWNPV_CHI2"};
   TTreeReaderValue<Int_t> Proton_OWNPV_NDOF = {fReader, "Proton_OWNPV_NDOF"};
   TTreeReaderValue<Double_t> Proton_IP_OWNPV = {fReader, "Proton_IP_OWNPV"};
   TTreeReaderValue<Double_t> Proton_IPCHI2_OWNPV = {fReader, "Proton_IPCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Proton_ORIVX_X = {fReader, "Proton_ORIVX_X"};
   TTreeReaderValue<Double_t> Proton_ORIVX_Y = {fReader, "Proton_ORIVX_Y"};
   TTreeReaderValue<Double_t> Proton_ORIVX_Z = {fReader, "Proton_ORIVX_Z"};
   TTreeReaderValue<Double_t> Proton_ORIVX_XERR = {fReader, "Proton_ORIVX_XERR"};
   TTreeReaderValue<Double_t> Proton_ORIVX_YERR = {fReader, "Proton_ORIVX_YERR"};
   TTreeReaderValue<Double_t> Proton_ORIVX_ZERR = {fReader, "Proton_ORIVX_ZERR"};
   TTreeReaderValue<Double_t> Proton_ORIVX_CHI2 = {fReader, "Proton_ORIVX_CHI2"};
   TTreeReaderValue<Int_t> Proton_ORIVX_NDOF = {fReader, "Proton_ORIVX_NDOF"};
   TTreeReaderValue<Double_t> Proton_P = {fReader, "Proton_P"};
   TTreeReaderValue<Double_t> Proton_PT = {fReader, "Proton_PT"};
   TTreeReaderValue<Double_t> Proton_PE = {fReader, "Proton_PE"};
   TTreeReaderValue<Double_t> Proton_PX = {fReader, "Proton_PX"};
   TTreeReaderValue<Double_t> Proton_PY = {fReader, "Proton_PY"};
   TTreeReaderValue<Double_t> Proton_PZ = {fReader, "Proton_PZ"};
   TTreeReaderValue<Double_t> Proton_M = {fReader, "Proton_M"};
   TTreeReaderValue<Int_t> Proton_ID = {fReader, "Proton_ID"};
   TTreeReaderValue<Double_t> Proton_PIDe = {fReader, "Proton_PIDe"};
   TTreeReaderValue<Double_t> Proton_PIDmu = {fReader, "Proton_PIDmu"};
   TTreeReaderValue<Double_t> Proton_PIDK = {fReader, "Proton_PIDK"};
   TTreeReaderValue<Double_t> Proton_PIDp = {fReader, "Proton_PIDp"};
   TTreeReaderValue<Double_t> Proton_PIDd = {fReader, "Proton_PIDd"};
   TTreeReaderValue<Double_t> Proton_ProbNNe = {fReader, "Proton_ProbNNe"};
   TTreeReaderValue<Double_t> Proton_ProbNNk = {fReader, "Proton_ProbNNk"};
   TTreeReaderValue<Double_t> Proton_ProbNNp = {fReader, "Proton_ProbNNp"};
   TTreeReaderValue<Double_t> Proton_ProbNNpi = {fReader, "Proton_ProbNNpi"};
   TTreeReaderValue<Double_t> Proton_ProbNNmu = {fReader, "Proton_ProbNNmu"};
   TTreeReaderValue<Double_t> Proton_ProbNNd = {fReader, "Proton_ProbNNd"};
   TTreeReaderValue<Double_t> Proton_ProbNNghost = {fReader, "Proton_ProbNNghost"};
   TTreeReaderValue<Bool_t> Proton_hasMuon = {fReader, "Proton_hasMuon"};
   TTreeReaderValue<Bool_t> Proton_isMuon = {fReader, "Proton_isMuon"};
   TTreeReaderValue<Bool_t> Proton_hasRich = {fReader, "Proton_hasRich"};
   TTreeReaderValue<Bool_t> Proton_UsedRichAerogel = {fReader, "Proton_UsedRichAerogel"};
   TTreeReaderValue<Bool_t> Proton_UsedRich1Gas = {fReader, "Proton_UsedRich1Gas"};
   TTreeReaderValue<Bool_t> Proton_UsedRich2Gas = {fReader, "Proton_UsedRich2Gas"};
   TTreeReaderValue<Bool_t> Proton_RichAboveElThres = {fReader, "Proton_RichAboveElThres"};
   TTreeReaderValue<Bool_t> Proton_RichAboveMuThres = {fReader, "Proton_RichAboveMuThres"};
   TTreeReaderValue<Bool_t> Proton_RichAbovePiThres = {fReader, "Proton_RichAbovePiThres"};
   TTreeReaderValue<Bool_t> Proton_RichAboveKaThres = {fReader, "Proton_RichAboveKaThres"};
   TTreeReaderValue<Bool_t> Proton_RichAbovePrThres = {fReader, "Proton_RichAbovePrThres"};
   TTreeReaderValue<Bool_t> Proton_hasCalo = {fReader, "Proton_hasCalo"};
   TTreeReaderValue<Bool_t> Proton_L0Global_Dec = {fReader, "Proton_L0Global_Dec"};
   TTreeReaderValue<Bool_t> Proton_L0Global_TIS = {fReader, "Proton_L0Global_TIS"};
   TTreeReaderValue<Bool_t> Proton_L0Global_TOS = {fReader, "Proton_L0Global_TOS"};
   TTreeReaderValue<Bool_t> Proton_Hlt1Global_Dec = {fReader, "Proton_Hlt1Global_Dec"};
   TTreeReaderValue<Bool_t> Proton_Hlt1Global_TIS = {fReader, "Proton_Hlt1Global_TIS"};
   TTreeReaderValue<Bool_t> Proton_Hlt1Global_TOS = {fReader, "Proton_Hlt1Global_TOS"};
   TTreeReaderValue<Bool_t> Proton_Hlt1Phys_Dec = {fReader, "Proton_Hlt1Phys_Dec"};
   TTreeReaderValue<Bool_t> Proton_Hlt1Phys_TIS = {fReader, "Proton_Hlt1Phys_TIS"};
   TTreeReaderValue<Bool_t> Proton_Hlt1Phys_TOS = {fReader, "Proton_Hlt1Phys_TOS"};
   TTreeReaderValue<Bool_t> Proton_Hlt2Global_Dec = {fReader, "Proton_Hlt2Global_Dec"};
   TTreeReaderValue<Bool_t> Proton_Hlt2Global_TIS = {fReader, "Proton_Hlt2Global_TIS"};
   TTreeReaderValue<Bool_t> Proton_Hlt2Global_TOS = {fReader, "Proton_Hlt2Global_TOS"};
   TTreeReaderValue<Bool_t> Proton_Hlt2Phys_Dec = {fReader, "Proton_Hlt2Phys_Dec"};
   TTreeReaderValue<Bool_t> Proton_Hlt2Phys_TIS = {fReader, "Proton_Hlt2Phys_TIS"};
   TTreeReaderValue<Bool_t> Proton_Hlt2Phys_TOS = {fReader, "Proton_Hlt2Phys_TOS"};
   TTreeReaderValue<Bool_t> Proton_L0MuonDecision_Dec = {fReader, "Proton_L0MuonDecision_Dec"};
   TTreeReaderValue<Bool_t> Proton_L0MuonDecision_TIS = {fReader, "Proton_L0MuonDecision_TIS"};
   TTreeReaderValue<Bool_t> Proton_L0MuonDecision_TOS = {fReader, "Proton_L0MuonDecision_TOS"};
   TTreeReaderValue<Bool_t> Proton_L0DiMuonDecisionL0HadronDecision_Dec = {fReader, "Proton_L0DiMuonDecisionL0HadronDecision_Dec"};
   TTreeReaderValue<Bool_t> Proton_L0DiMuonDecisionL0HadronDecision_TIS = {fReader, "Proton_L0DiMuonDecisionL0HadronDecision_TIS"};
   TTreeReaderValue<Bool_t> Proton_L0DiMuonDecisionL0HadronDecision_TOS = {fReader, "Proton_L0DiMuonDecisionL0HadronDecision_TOS"};
   TTreeReaderValue<Bool_t> Proton_L0ElectronDecision_Dec = {fReader, "Proton_L0ElectronDecision_Dec"};
   TTreeReaderValue<Bool_t> Proton_L0ElectronDecision_TIS = {fReader, "Proton_L0ElectronDecision_TIS"};
   TTreeReaderValue<Bool_t> Proton_L0ElectronDecision_TOS = {fReader, "Proton_L0ElectronDecision_TOS"};
   TTreeReaderValue<Bool_t> Proton_L0PhotonDecision_Dec = {fReader, "Proton_L0PhotonDecision_Dec"};
   TTreeReaderValue<Bool_t> Proton_L0PhotonDecision_TIS = {fReader, "Proton_L0PhotonDecision_TIS"};
   TTreeReaderValue<Bool_t> Proton_L0PhotonDecision_TOS = {fReader, "Proton_L0PhotonDecision_TOS"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TrackMVADecision_Dec = {fReader, "Proton_Hlt1TrackMVADecision_Dec"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TrackMVADecision_TIS = {fReader, "Proton_Hlt1TrackMVADecision_TIS"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TrackMVADecision_TOS = {fReader, "Proton_Hlt1TrackMVADecision_TOS"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TwoTrackMVADecision_Dec = {fReader, "Proton_Hlt1TwoTrackMVADecision_Dec"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TwoTrackMVADecision_TIS = {fReader, "Proton_Hlt1TwoTrackMVADecision_TIS"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TwoTrackMVADecision_TOS = {fReader, "Proton_Hlt1TwoTrackMVADecision_TOS"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TrackMVATightDecision_Dec = {fReader, "Proton_Hlt1TrackMVATightDecision_Dec"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TrackMVATightDecision_TIS = {fReader, "Proton_Hlt1TrackMVATightDecision_TIS"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TrackMVATightDecision_TOS = {fReader, "Proton_Hlt1TrackMVATightDecision_TOS"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TwoTrackMVATightDecision_Dec = {fReader, "Proton_Hlt1TwoTrackMVATightDecision_Dec"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TwoTrackMVATightDecision_TIS = {fReader, "Proton_Hlt1TwoTrackMVATightDecision_TIS"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TwoTrackMVATightDecision_TOS = {fReader, "Proton_Hlt1TwoTrackMVATightDecision_TOS"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TrackMuonDecision_Dec = {fReader, "Proton_Hlt1TrackMuonDecision_Dec"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TrackMuonDecision_TIS = {fReader, "Proton_Hlt1TrackMuonDecision_TIS"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TrackMuonDecision_TOS = {fReader, "Proton_Hlt1TrackMuonDecision_TOS"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TrackMuonMVADecision_Dec = {fReader, "Proton_Hlt1TrackMuonMVADecision_Dec"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TrackMuonMVADecision_TIS = {fReader, "Proton_Hlt1TrackMuonMVADecision_TIS"};
   TTreeReaderValue<Bool_t> Proton_Hlt1TrackMuonMVADecision_TOS = {fReader, "Proton_Hlt1TrackMuonMVADecision_TOS"};
   TTreeReaderValue<Bool_t> Proton_Hlt2Topo2BodyDecision_Dec = {fReader, "Proton_Hlt2Topo2BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Proton_Hlt2Topo2BodyDecision_TIS = {fReader, "Proton_Hlt2Topo2BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Proton_Hlt2Topo2BodyDecision_TOS = {fReader, "Proton_Hlt2Topo2BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Proton_Hlt2Topo3BodyDecision_Dec = {fReader, "Proton_Hlt2Topo3BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Proton_Hlt2Topo3BodyDecision_TIS = {fReader, "Proton_Hlt2Topo3BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Proton_Hlt2Topo3BodyDecision_TOS = {fReader, "Proton_Hlt2Topo3BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Proton_Hlt2Topo4BodyDecision_Dec = {fReader, "Proton_Hlt2Topo4BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Proton_Hlt2Topo4BodyDecision_TIS = {fReader, "Proton_Hlt2Topo4BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Proton_Hlt2Topo4BodyDecision_TOS = {fReader, "Proton_Hlt2Topo4BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Proton_Hlt2TopoMu2BodyDecision_Dec = {fReader, "Proton_Hlt2TopoMu2BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Proton_Hlt2TopoMu2BodyDecision_TIS = {fReader, "Proton_Hlt2TopoMu2BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Proton_Hlt2TopoMu2BodyDecision_TOS = {fReader, "Proton_Hlt2TopoMu2BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Proton_Hlt2TopoMu3BodyDecision_Dec = {fReader, "Proton_Hlt2TopoMu3BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Proton_Hlt2TopoMu3BodyDecision_TIS = {fReader, "Proton_Hlt2TopoMu3BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Proton_Hlt2TopoMu3BodyDecision_TOS = {fReader, "Proton_Hlt2TopoMu3BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Proton_Hlt2TopoMu4BodyDecision_Dec = {fReader, "Proton_Hlt2TopoMu4BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Proton_Hlt2TopoMu4BodyDecision_TIS = {fReader, "Proton_Hlt2TopoMu4BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Proton_Hlt2TopoMu4BodyDecision_TOS = {fReader, "Proton_Hlt2TopoMu4BodyDecision_TOS"};
   TTreeReaderValue<Int_t> Proton_TRACK_Type = {fReader, "Proton_TRACK_Type"};
   TTreeReaderValue<Int_t> Proton_TRACK_Key = {fReader, "Proton_TRACK_Key"};
   TTreeReaderValue<Double_t> Proton_TRACK_CHI2NDOF = {fReader, "Proton_TRACK_CHI2NDOF"};
   TTreeReaderValue<Double_t> Proton_TRACK_PCHI2 = {fReader, "Proton_TRACK_PCHI2"};
   TTreeReaderValue<Double_t> Proton_TRACK_MatchCHI2 = {fReader, "Proton_TRACK_MatchCHI2"};
   TTreeReaderValue<Double_t> Proton_TRACK_GhostProb = {fReader, "Proton_TRACK_GhostProb"};
   TTreeReaderValue<Double_t> Proton_TRACK_CloneDist = {fReader, "Proton_TRACK_CloneDist"};
   TTreeReaderValue<Double_t> Proton_TRACK_Likelihood = {fReader, "Proton_TRACK_Likelihood"};
   TTreeReaderValue<Double_t> Kminus_ETA = {fReader, "Kminus_ETA"};
   TTreeReaderValue<Double_t> Kminus_PHI = {fReader, "Kminus_PHI"};
   TTreeReaderValue<Double_t> Kminus_OWNPV_X = {fReader, "Kminus_OWNPV_X"};
   TTreeReaderValue<Double_t> Kminus_OWNPV_Y = {fReader, "Kminus_OWNPV_Y"};
   TTreeReaderValue<Double_t> Kminus_OWNPV_Z = {fReader, "Kminus_OWNPV_Z"};
   TTreeReaderValue<Double_t> Kminus_OWNPV_XERR = {fReader, "Kminus_OWNPV_XERR"};
   TTreeReaderValue<Double_t> Kminus_OWNPV_YERR = {fReader, "Kminus_OWNPV_YERR"};
   TTreeReaderValue<Double_t> Kminus_OWNPV_ZERR = {fReader, "Kminus_OWNPV_ZERR"};
   TTreeReaderValue<Double_t> Kminus_OWNPV_CHI2 = {fReader, "Kminus_OWNPV_CHI2"};
   TTreeReaderValue<Int_t> Kminus_OWNPV_NDOF = {fReader, "Kminus_OWNPV_NDOF"};
   TTreeReaderValue<Double_t> Kminus_IP_OWNPV = {fReader, "Kminus_IP_OWNPV"};
   TTreeReaderValue<Double_t> Kminus_IPCHI2_OWNPV = {fReader, "Kminus_IPCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Kminus_ORIVX_X = {fReader, "Kminus_ORIVX_X"};
   TTreeReaderValue<Double_t> Kminus_ORIVX_Y = {fReader, "Kminus_ORIVX_Y"};
   TTreeReaderValue<Double_t> Kminus_ORIVX_Z = {fReader, "Kminus_ORIVX_Z"};
   TTreeReaderValue<Double_t> Kminus_ORIVX_XERR = {fReader, "Kminus_ORIVX_XERR"};
   TTreeReaderValue<Double_t> Kminus_ORIVX_YERR = {fReader, "Kminus_ORIVX_YERR"};
   TTreeReaderValue<Double_t> Kminus_ORIVX_ZERR = {fReader, "Kminus_ORIVX_ZERR"};
   TTreeReaderValue<Double_t> Kminus_ORIVX_CHI2 = {fReader, "Kminus_ORIVX_CHI2"};
   TTreeReaderValue<Int_t> Kminus_ORIVX_NDOF = {fReader, "Kminus_ORIVX_NDOF"};
   TTreeReaderValue<Double_t> Kminus_P = {fReader, "Kminus_P"};
   TTreeReaderValue<Double_t> Kminus_PT = {fReader, "Kminus_PT"};
   TTreeReaderValue<Double_t> Kminus_PE = {fReader, "Kminus_PE"};
   TTreeReaderValue<Double_t> Kminus_PX = {fReader, "Kminus_PX"};
   TTreeReaderValue<Double_t> Kminus_PY = {fReader, "Kminus_PY"};
   TTreeReaderValue<Double_t> Kminus_PZ = {fReader, "Kminus_PZ"};
   TTreeReaderValue<Double_t> Kminus_M = {fReader, "Kminus_M"};
   TTreeReaderValue<Int_t> Kminus_ID = {fReader, "Kminus_ID"};
   TTreeReaderValue<Double_t> Kminus_PIDe = {fReader, "Kminus_PIDe"};
   TTreeReaderValue<Double_t> Kminus_PIDmu = {fReader, "Kminus_PIDmu"};
   TTreeReaderValue<Double_t> Kminus_PIDK = {fReader, "Kminus_PIDK"};
   TTreeReaderValue<Double_t> Kminus_PIDp = {fReader, "Kminus_PIDp"};
   TTreeReaderValue<Double_t> Kminus_PIDd = {fReader, "Kminus_PIDd"};
   TTreeReaderValue<Double_t> Kminus_ProbNNe = {fReader, "Kminus_ProbNNe"};
   TTreeReaderValue<Double_t> Kminus_ProbNNk = {fReader, "Kminus_ProbNNk"};
   TTreeReaderValue<Double_t> Kminus_ProbNNp = {fReader, "Kminus_ProbNNp"};
   TTreeReaderValue<Double_t> Kminus_ProbNNpi = {fReader, "Kminus_ProbNNpi"};
   TTreeReaderValue<Double_t> Kminus_ProbNNmu = {fReader, "Kminus_ProbNNmu"};
   TTreeReaderValue<Double_t> Kminus_ProbNNd = {fReader, "Kminus_ProbNNd"};
   TTreeReaderValue<Double_t> Kminus_ProbNNghost = {fReader, "Kminus_ProbNNghost"};
   TTreeReaderValue<Bool_t> Kminus_hasMuon = {fReader, "Kminus_hasMuon"};
   TTreeReaderValue<Bool_t> Kminus_isMuon = {fReader, "Kminus_isMuon"};
   TTreeReaderValue<Bool_t> Kminus_hasRich = {fReader, "Kminus_hasRich"};
   TTreeReaderValue<Bool_t> Kminus_UsedRichAerogel = {fReader, "Kminus_UsedRichAerogel"};
   TTreeReaderValue<Bool_t> Kminus_UsedRich1Gas = {fReader, "Kminus_UsedRich1Gas"};
   TTreeReaderValue<Bool_t> Kminus_UsedRich2Gas = {fReader, "Kminus_UsedRich2Gas"};
   TTreeReaderValue<Bool_t> Kminus_RichAboveElThres = {fReader, "Kminus_RichAboveElThres"};
   TTreeReaderValue<Bool_t> Kminus_RichAboveMuThres = {fReader, "Kminus_RichAboveMuThres"};
   TTreeReaderValue<Bool_t> Kminus_RichAbovePiThres = {fReader, "Kminus_RichAbovePiThres"};
   TTreeReaderValue<Bool_t> Kminus_RichAboveKaThres = {fReader, "Kminus_RichAboveKaThres"};
   TTreeReaderValue<Bool_t> Kminus_RichAbovePrThres = {fReader, "Kminus_RichAbovePrThres"};
   TTreeReaderValue<Bool_t> Kminus_hasCalo = {fReader, "Kminus_hasCalo"};
   TTreeReaderValue<Bool_t> Kminus_L0Global_Dec = {fReader, "Kminus_L0Global_Dec"};
   TTreeReaderValue<Bool_t> Kminus_L0Global_TIS = {fReader, "Kminus_L0Global_TIS"};
   TTreeReaderValue<Bool_t> Kminus_L0Global_TOS = {fReader, "Kminus_L0Global_TOS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1Global_Dec = {fReader, "Kminus_Hlt1Global_Dec"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1Global_TIS = {fReader, "Kminus_Hlt1Global_TIS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1Global_TOS = {fReader, "Kminus_Hlt1Global_TOS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1Phys_Dec = {fReader, "Kminus_Hlt1Phys_Dec"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1Phys_TIS = {fReader, "Kminus_Hlt1Phys_TIS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1Phys_TOS = {fReader, "Kminus_Hlt1Phys_TOS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2Global_Dec = {fReader, "Kminus_Hlt2Global_Dec"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2Global_TIS = {fReader, "Kminus_Hlt2Global_TIS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2Global_TOS = {fReader, "Kminus_Hlt2Global_TOS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2Phys_Dec = {fReader, "Kminus_Hlt2Phys_Dec"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2Phys_TIS = {fReader, "Kminus_Hlt2Phys_TIS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2Phys_TOS = {fReader, "Kminus_Hlt2Phys_TOS"};
   TTreeReaderValue<Bool_t> Kminus_L0MuonDecision_Dec = {fReader, "Kminus_L0MuonDecision_Dec"};
   TTreeReaderValue<Bool_t> Kminus_L0MuonDecision_TIS = {fReader, "Kminus_L0MuonDecision_TIS"};
   TTreeReaderValue<Bool_t> Kminus_L0MuonDecision_TOS = {fReader, "Kminus_L0MuonDecision_TOS"};
   TTreeReaderValue<Bool_t> Kminus_L0DiMuonDecisionL0HadronDecision_Dec = {fReader, "Kminus_L0DiMuonDecisionL0HadronDecision_Dec"};
   TTreeReaderValue<Bool_t> Kminus_L0DiMuonDecisionL0HadronDecision_TIS = {fReader, "Kminus_L0DiMuonDecisionL0HadronDecision_TIS"};
   TTreeReaderValue<Bool_t> Kminus_L0DiMuonDecisionL0HadronDecision_TOS = {fReader, "Kminus_L0DiMuonDecisionL0HadronDecision_TOS"};
   TTreeReaderValue<Bool_t> Kminus_L0ElectronDecision_Dec = {fReader, "Kminus_L0ElectronDecision_Dec"};
   TTreeReaderValue<Bool_t> Kminus_L0ElectronDecision_TIS = {fReader, "Kminus_L0ElectronDecision_TIS"};
   TTreeReaderValue<Bool_t> Kminus_L0ElectronDecision_TOS = {fReader, "Kminus_L0ElectronDecision_TOS"};
   TTreeReaderValue<Bool_t> Kminus_L0PhotonDecision_Dec = {fReader, "Kminus_L0PhotonDecision_Dec"};
   TTreeReaderValue<Bool_t> Kminus_L0PhotonDecision_TIS = {fReader, "Kminus_L0PhotonDecision_TIS"};
   TTreeReaderValue<Bool_t> Kminus_L0PhotonDecision_TOS = {fReader, "Kminus_L0PhotonDecision_TOS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TrackMVADecision_Dec = {fReader, "Kminus_Hlt1TrackMVADecision_Dec"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TrackMVADecision_TIS = {fReader, "Kminus_Hlt1TrackMVADecision_TIS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TrackMVADecision_TOS = {fReader, "Kminus_Hlt1TrackMVADecision_TOS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TwoTrackMVADecision_Dec = {fReader, "Kminus_Hlt1TwoTrackMVADecision_Dec"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TwoTrackMVADecision_TIS = {fReader, "Kminus_Hlt1TwoTrackMVADecision_TIS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TwoTrackMVADecision_TOS = {fReader, "Kminus_Hlt1TwoTrackMVADecision_TOS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TrackMVATightDecision_Dec = {fReader, "Kminus_Hlt1TrackMVATightDecision_Dec"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TrackMVATightDecision_TIS = {fReader, "Kminus_Hlt1TrackMVATightDecision_TIS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TrackMVATightDecision_TOS = {fReader, "Kminus_Hlt1TrackMVATightDecision_TOS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TwoTrackMVATightDecision_Dec = {fReader, "Kminus_Hlt1TwoTrackMVATightDecision_Dec"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TwoTrackMVATightDecision_TIS = {fReader, "Kminus_Hlt1TwoTrackMVATightDecision_TIS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TwoTrackMVATightDecision_TOS = {fReader, "Kminus_Hlt1TwoTrackMVATightDecision_TOS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TrackMuonDecision_Dec = {fReader, "Kminus_Hlt1TrackMuonDecision_Dec"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TrackMuonDecision_TIS = {fReader, "Kminus_Hlt1TrackMuonDecision_TIS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TrackMuonDecision_TOS = {fReader, "Kminus_Hlt1TrackMuonDecision_TOS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TrackMuonMVADecision_Dec = {fReader, "Kminus_Hlt1TrackMuonMVADecision_Dec"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TrackMuonMVADecision_TIS = {fReader, "Kminus_Hlt1TrackMuonMVADecision_TIS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt1TrackMuonMVADecision_TOS = {fReader, "Kminus_Hlt1TrackMuonMVADecision_TOS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2Topo2BodyDecision_Dec = {fReader, "Kminus_Hlt2Topo2BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2Topo2BodyDecision_TIS = {fReader, "Kminus_Hlt2Topo2BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2Topo2BodyDecision_TOS = {fReader, "Kminus_Hlt2Topo2BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2Topo3BodyDecision_Dec = {fReader, "Kminus_Hlt2Topo3BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2Topo3BodyDecision_TIS = {fReader, "Kminus_Hlt2Topo3BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2Topo3BodyDecision_TOS = {fReader, "Kminus_Hlt2Topo3BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2Topo4BodyDecision_Dec = {fReader, "Kminus_Hlt2Topo4BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2Topo4BodyDecision_TIS = {fReader, "Kminus_Hlt2Topo4BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2Topo4BodyDecision_TOS = {fReader, "Kminus_Hlt2Topo4BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2TopoMu2BodyDecision_Dec = {fReader, "Kminus_Hlt2TopoMu2BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2TopoMu2BodyDecision_TIS = {fReader, "Kminus_Hlt2TopoMu2BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2TopoMu2BodyDecision_TOS = {fReader, "Kminus_Hlt2TopoMu2BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2TopoMu3BodyDecision_Dec = {fReader, "Kminus_Hlt2TopoMu3BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2TopoMu3BodyDecision_TIS = {fReader, "Kminus_Hlt2TopoMu3BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2TopoMu3BodyDecision_TOS = {fReader, "Kminus_Hlt2TopoMu3BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2TopoMu4BodyDecision_Dec = {fReader, "Kminus_Hlt2TopoMu4BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2TopoMu4BodyDecision_TIS = {fReader, "Kminus_Hlt2TopoMu4BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Kminus_Hlt2TopoMu4BodyDecision_TOS = {fReader, "Kminus_Hlt2TopoMu4BodyDecision_TOS"};
   TTreeReaderValue<Int_t> Kminus_TRACK_Type = {fReader, "Kminus_TRACK_Type"};
   TTreeReaderValue<Int_t> Kminus_TRACK_Key = {fReader, "Kminus_TRACK_Key"};
   TTreeReaderValue<Double_t> Kminus_TRACK_CHI2NDOF = {fReader, "Kminus_TRACK_CHI2NDOF"};
   TTreeReaderValue<Double_t> Kminus_TRACK_PCHI2 = {fReader, "Kminus_TRACK_PCHI2"};
   TTreeReaderValue<Double_t> Kminus_TRACK_MatchCHI2 = {fReader, "Kminus_TRACK_MatchCHI2"};
   TTreeReaderValue<Double_t> Kminus_TRACK_GhostProb = {fReader, "Kminus_TRACK_GhostProb"};
   TTreeReaderValue<Double_t> Kminus_TRACK_CloneDist = {fReader, "Kminus_TRACK_CloneDist"};
   TTreeReaderValue<Double_t> Kminus_TRACK_Likelihood = {fReader, "Kminus_TRACK_Likelihood"};
   TTreeReaderValue<Double_t> Kplus_ETA = {fReader, "Kplus_ETA"};
   TTreeReaderValue<Double_t> Kplus_PHI = {fReader, "Kplus_PHI"};
   TTreeReaderValue<Double_t> Kplus_OWNPV_X = {fReader, "Kplus_OWNPV_X"};
   TTreeReaderValue<Double_t> Kplus_OWNPV_Y = {fReader, "Kplus_OWNPV_Y"};
   TTreeReaderValue<Double_t> Kplus_OWNPV_Z = {fReader, "Kplus_OWNPV_Z"};
   TTreeReaderValue<Double_t> Kplus_OWNPV_XERR = {fReader, "Kplus_OWNPV_XERR"};
   TTreeReaderValue<Double_t> Kplus_OWNPV_YERR = {fReader, "Kplus_OWNPV_YERR"};
   TTreeReaderValue<Double_t> Kplus_OWNPV_ZERR = {fReader, "Kplus_OWNPV_ZERR"};
   TTreeReaderValue<Double_t> Kplus_OWNPV_CHI2 = {fReader, "Kplus_OWNPV_CHI2"};
   TTreeReaderValue<Int_t> Kplus_OWNPV_NDOF = {fReader, "Kplus_OWNPV_NDOF"};
   TTreeReaderValue<Double_t> Kplus_IP_OWNPV = {fReader, "Kplus_IP_OWNPV"};
   TTreeReaderValue<Double_t> Kplus_IPCHI2_OWNPV = {fReader, "Kplus_IPCHI2_OWNPV"};
   TTreeReaderValue<Double_t> Kplus_ORIVX_X = {fReader, "Kplus_ORIVX_X"};
   TTreeReaderValue<Double_t> Kplus_ORIVX_Y = {fReader, "Kplus_ORIVX_Y"};
   TTreeReaderValue<Double_t> Kplus_ORIVX_Z = {fReader, "Kplus_ORIVX_Z"};
   TTreeReaderValue<Double_t> Kplus_ORIVX_XERR = {fReader, "Kplus_ORIVX_XERR"};
   TTreeReaderValue<Double_t> Kplus_ORIVX_YERR = {fReader, "Kplus_ORIVX_YERR"};
   TTreeReaderValue<Double_t> Kplus_ORIVX_ZERR = {fReader, "Kplus_ORIVX_ZERR"};
   TTreeReaderValue<Double_t> Kplus_ORIVX_CHI2 = {fReader, "Kplus_ORIVX_CHI2"};
   TTreeReaderValue<Int_t> Kplus_ORIVX_NDOF = {fReader, "Kplus_ORIVX_NDOF"};
   TTreeReaderValue<Double_t> Kplus_P = {fReader, "Kplus_P"};
   TTreeReaderValue<Double_t> Kplus_PT = {fReader, "Kplus_PT"};
   TTreeReaderValue<Double_t> Kplus_PE = {fReader, "Kplus_PE"};
   TTreeReaderValue<Double_t> Kplus_PX = {fReader, "Kplus_PX"};
   TTreeReaderValue<Double_t> Kplus_PY = {fReader, "Kplus_PY"};
   TTreeReaderValue<Double_t> Kplus_PZ = {fReader, "Kplus_PZ"};
   TTreeReaderValue<Double_t> Kplus_M = {fReader, "Kplus_M"};
   TTreeReaderValue<Int_t> Kplus_ID = {fReader, "Kplus_ID"};
   TTreeReaderValue<Double_t> Kplus_PIDe = {fReader, "Kplus_PIDe"};
   TTreeReaderValue<Double_t> Kplus_PIDmu = {fReader, "Kplus_PIDmu"};
   TTreeReaderValue<Double_t> Kplus_PIDK = {fReader, "Kplus_PIDK"};
   TTreeReaderValue<Double_t> Kplus_PIDp = {fReader, "Kplus_PIDp"};
   TTreeReaderValue<Double_t> Kplus_PIDd = {fReader, "Kplus_PIDd"};
   TTreeReaderValue<Double_t> Kplus_ProbNNe = {fReader, "Kplus_ProbNNe"};
   TTreeReaderValue<Double_t> Kplus_ProbNNk = {fReader, "Kplus_ProbNNk"};
   TTreeReaderValue<Double_t> Kplus_ProbNNp = {fReader, "Kplus_ProbNNp"};
   TTreeReaderValue<Double_t> Kplus_ProbNNpi = {fReader, "Kplus_ProbNNpi"};
   TTreeReaderValue<Double_t> Kplus_ProbNNmu = {fReader, "Kplus_ProbNNmu"};
   TTreeReaderValue<Double_t> Kplus_ProbNNd = {fReader, "Kplus_ProbNNd"};
   TTreeReaderValue<Double_t> Kplus_ProbNNghost = {fReader, "Kplus_ProbNNghost"};
   TTreeReaderValue<Bool_t> Kplus_hasMuon = {fReader, "Kplus_hasMuon"};
   TTreeReaderValue<Bool_t> Kplus_isMuon = {fReader, "Kplus_isMuon"};
   TTreeReaderValue<Bool_t> Kplus_hasRich = {fReader, "Kplus_hasRich"};
   TTreeReaderValue<Bool_t> Kplus_UsedRichAerogel = {fReader, "Kplus_UsedRichAerogel"};
   TTreeReaderValue<Bool_t> Kplus_UsedRich1Gas = {fReader, "Kplus_UsedRich1Gas"};
   TTreeReaderValue<Bool_t> Kplus_UsedRich2Gas = {fReader, "Kplus_UsedRich2Gas"};
   TTreeReaderValue<Bool_t> Kplus_RichAboveElThres = {fReader, "Kplus_RichAboveElThres"};
   TTreeReaderValue<Bool_t> Kplus_RichAboveMuThres = {fReader, "Kplus_RichAboveMuThres"};
   TTreeReaderValue<Bool_t> Kplus_RichAbovePiThres = {fReader, "Kplus_RichAbovePiThres"};
   TTreeReaderValue<Bool_t> Kplus_RichAboveKaThres = {fReader, "Kplus_RichAboveKaThres"};
   TTreeReaderValue<Bool_t> Kplus_RichAbovePrThres = {fReader, "Kplus_RichAbovePrThres"};
   TTreeReaderValue<Bool_t> Kplus_hasCalo = {fReader, "Kplus_hasCalo"};
   TTreeReaderValue<Bool_t> Kplus_L0Global_Dec = {fReader, "Kplus_L0Global_Dec"};
   TTreeReaderValue<Bool_t> Kplus_L0Global_TIS = {fReader, "Kplus_L0Global_TIS"};
   TTreeReaderValue<Bool_t> Kplus_L0Global_TOS = {fReader, "Kplus_L0Global_TOS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1Global_Dec = {fReader, "Kplus_Hlt1Global_Dec"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1Global_TIS = {fReader, "Kplus_Hlt1Global_TIS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1Global_TOS = {fReader, "Kplus_Hlt1Global_TOS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1Phys_Dec = {fReader, "Kplus_Hlt1Phys_Dec"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1Phys_TIS = {fReader, "Kplus_Hlt1Phys_TIS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1Phys_TOS = {fReader, "Kplus_Hlt1Phys_TOS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2Global_Dec = {fReader, "Kplus_Hlt2Global_Dec"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2Global_TIS = {fReader, "Kplus_Hlt2Global_TIS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2Global_TOS = {fReader, "Kplus_Hlt2Global_TOS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2Phys_Dec = {fReader, "Kplus_Hlt2Phys_Dec"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2Phys_TIS = {fReader, "Kplus_Hlt2Phys_TIS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2Phys_TOS = {fReader, "Kplus_Hlt2Phys_TOS"};
   TTreeReaderValue<Bool_t> Kplus_L0MuonDecision_Dec = {fReader, "Kplus_L0MuonDecision_Dec"};
   TTreeReaderValue<Bool_t> Kplus_L0MuonDecision_TIS = {fReader, "Kplus_L0MuonDecision_TIS"};
   TTreeReaderValue<Bool_t> Kplus_L0MuonDecision_TOS = {fReader, "Kplus_L0MuonDecision_TOS"};
   TTreeReaderValue<Bool_t> Kplus_L0DiMuonDecisionL0HadronDecision_Dec = {fReader, "Kplus_L0DiMuonDecisionL0HadronDecision_Dec"};
   TTreeReaderValue<Bool_t> Kplus_L0DiMuonDecisionL0HadronDecision_TIS = {fReader, "Kplus_L0DiMuonDecisionL0HadronDecision_TIS"};
   TTreeReaderValue<Bool_t> Kplus_L0DiMuonDecisionL0HadronDecision_TOS = {fReader, "Kplus_L0DiMuonDecisionL0HadronDecision_TOS"};
   TTreeReaderValue<Bool_t> Kplus_L0ElectronDecision_Dec = {fReader, "Kplus_L0ElectronDecision_Dec"};
   TTreeReaderValue<Bool_t> Kplus_L0ElectronDecision_TIS = {fReader, "Kplus_L0ElectronDecision_TIS"};
   TTreeReaderValue<Bool_t> Kplus_L0ElectronDecision_TOS = {fReader, "Kplus_L0ElectronDecision_TOS"};
   TTreeReaderValue<Bool_t> Kplus_L0PhotonDecision_Dec = {fReader, "Kplus_L0PhotonDecision_Dec"};
   TTreeReaderValue<Bool_t> Kplus_L0PhotonDecision_TIS = {fReader, "Kplus_L0PhotonDecision_TIS"};
   TTreeReaderValue<Bool_t> Kplus_L0PhotonDecision_TOS = {fReader, "Kplus_L0PhotonDecision_TOS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TrackMVADecision_Dec = {fReader, "Kplus_Hlt1TrackMVADecision_Dec"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TrackMVADecision_TIS = {fReader, "Kplus_Hlt1TrackMVADecision_TIS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TrackMVADecision_TOS = {fReader, "Kplus_Hlt1TrackMVADecision_TOS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TwoTrackMVADecision_Dec = {fReader, "Kplus_Hlt1TwoTrackMVADecision_Dec"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TwoTrackMVADecision_TIS = {fReader, "Kplus_Hlt1TwoTrackMVADecision_TIS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TwoTrackMVADecision_TOS = {fReader, "Kplus_Hlt1TwoTrackMVADecision_TOS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TrackMVATightDecision_Dec = {fReader, "Kplus_Hlt1TrackMVATightDecision_Dec"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TrackMVATightDecision_TIS = {fReader, "Kplus_Hlt1TrackMVATightDecision_TIS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TrackMVATightDecision_TOS = {fReader, "Kplus_Hlt1TrackMVATightDecision_TOS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TwoTrackMVATightDecision_Dec = {fReader, "Kplus_Hlt1TwoTrackMVATightDecision_Dec"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TwoTrackMVATightDecision_TIS = {fReader, "Kplus_Hlt1TwoTrackMVATightDecision_TIS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TwoTrackMVATightDecision_TOS = {fReader, "Kplus_Hlt1TwoTrackMVATightDecision_TOS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TrackMuonDecision_Dec = {fReader, "Kplus_Hlt1TrackMuonDecision_Dec"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TrackMuonDecision_TIS = {fReader, "Kplus_Hlt1TrackMuonDecision_TIS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TrackMuonDecision_TOS = {fReader, "Kplus_Hlt1TrackMuonDecision_TOS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TrackMuonMVADecision_Dec = {fReader, "Kplus_Hlt1TrackMuonMVADecision_Dec"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TrackMuonMVADecision_TIS = {fReader, "Kplus_Hlt1TrackMuonMVADecision_TIS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt1TrackMuonMVADecision_TOS = {fReader, "Kplus_Hlt1TrackMuonMVADecision_TOS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2Topo2BodyDecision_Dec = {fReader, "Kplus_Hlt2Topo2BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2Topo2BodyDecision_TIS = {fReader, "Kplus_Hlt2Topo2BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2Topo2BodyDecision_TOS = {fReader, "Kplus_Hlt2Topo2BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2Topo3BodyDecision_Dec = {fReader, "Kplus_Hlt2Topo3BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2Topo3BodyDecision_TIS = {fReader, "Kplus_Hlt2Topo3BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2Topo3BodyDecision_TOS = {fReader, "Kplus_Hlt2Topo3BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2Topo4BodyDecision_Dec = {fReader, "Kplus_Hlt2Topo4BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2Topo4BodyDecision_TIS = {fReader, "Kplus_Hlt2Topo4BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2Topo4BodyDecision_TOS = {fReader, "Kplus_Hlt2Topo4BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2TopoMu2BodyDecision_Dec = {fReader, "Kplus_Hlt2TopoMu2BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2TopoMu2BodyDecision_TIS = {fReader, "Kplus_Hlt2TopoMu2BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2TopoMu2BodyDecision_TOS = {fReader, "Kplus_Hlt2TopoMu2BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2TopoMu3BodyDecision_Dec = {fReader, "Kplus_Hlt2TopoMu3BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2TopoMu3BodyDecision_TIS = {fReader, "Kplus_Hlt2TopoMu3BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2TopoMu3BodyDecision_TOS = {fReader, "Kplus_Hlt2TopoMu3BodyDecision_TOS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2TopoMu4BodyDecision_Dec = {fReader, "Kplus_Hlt2TopoMu4BodyDecision_Dec"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2TopoMu4BodyDecision_TIS = {fReader, "Kplus_Hlt2TopoMu4BodyDecision_TIS"};
   TTreeReaderValue<Bool_t> Kplus_Hlt2TopoMu4BodyDecision_TOS = {fReader, "Kplus_Hlt2TopoMu4BodyDecision_TOS"};
   TTreeReaderValue<Int_t> Kplus_TRACK_Type = {fReader, "Kplus_TRACK_Type"};
   TTreeReaderValue<Int_t> Kplus_TRACK_Key = {fReader, "Kplus_TRACK_Key"};
   TTreeReaderValue<Double_t> Kplus_TRACK_CHI2NDOF = {fReader, "Kplus_TRACK_CHI2NDOF"};
   TTreeReaderValue<Double_t> Kplus_TRACK_PCHI2 = {fReader, "Kplus_TRACK_PCHI2"};
   TTreeReaderValue<Double_t> Kplus_TRACK_MatchCHI2 = {fReader, "Kplus_TRACK_MatchCHI2"};
   TTreeReaderValue<Double_t> Kplus_TRACK_GhostProb = {fReader, "Kplus_TRACK_GhostProb"};
   TTreeReaderValue<Double_t> Kplus_TRACK_CloneDist = {fReader, "Kplus_TRACK_CloneDist"};
   TTreeReaderValue<Double_t> Kplus_TRACK_Likelihood = {fReader, "Kplus_TRACK_Likelihood"};
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
   TTreeReaderValue<Int_t> L0Global = {fReader, "L0Global"};
   TTreeReaderValue<UInt_t> Hlt1Global = {fReader, "Hlt1Global"};
   TTreeReaderValue<UInt_t> Hlt2Global = {fReader, "Hlt2Global"};
   TTreeReaderValue<Int_t> L0MuonDecision = {fReader, "L0MuonDecision"};
   TTreeReaderValue<Int_t> L0DiMuonDecisionL0HadronDecision = {fReader, "L0DiMuonDecisionL0HadronDecision"};
   TTreeReaderValue<Int_t> L0ElectronDecision = {fReader, "L0ElectronDecision"};
   TTreeReaderValue<Int_t> L0PhotonDecision = {fReader, "L0PhotonDecision"};
   TTreeReaderValue<UInt_t> L0nSelections = {fReader, "L0nSelections"};
   TTreeReaderValue<Int_t> Hlt1TrackMVADecision = {fReader, "Hlt1TrackMVADecision"};
   TTreeReaderValue<Int_t> Hlt1TwoTrackMVADecision = {fReader, "Hlt1TwoTrackMVADecision"};
   TTreeReaderValue<Int_t> Hlt1TrackMVATightDecision = {fReader, "Hlt1TrackMVATightDecision"};
   TTreeReaderValue<Int_t> Hlt1TwoTrackMVATightDecision = {fReader, "Hlt1TwoTrackMVATightDecision"};
   TTreeReaderValue<Int_t> Hlt1TrackMuonDecision = {fReader, "Hlt1TrackMuonDecision"};
   TTreeReaderValue<Int_t> Hlt1TrackMuonMVADecision = {fReader, "Hlt1TrackMuonMVADecision"};
   TTreeReaderValue<UInt_t> Hlt1nSelections = {fReader, "Hlt1nSelections"};
   TTreeReaderValue<Int_t> Hlt2Topo2BodyDecision = {fReader, "Hlt2Topo2BodyDecision"};
   TTreeReaderValue<Int_t> Hlt2Topo3BodyDecision = {fReader, "Hlt2Topo3BodyDecision"};
   TTreeReaderValue<Int_t> Hlt2Topo4BodyDecision = {fReader, "Hlt2Topo4BodyDecision"};
   TTreeReaderValue<Int_t> Hlt2TopoMu2BodyDecision = {fReader, "Hlt2TopoMu2BodyDecision"};
   TTreeReaderValue<Int_t> Hlt2TopoMu3BodyDecision = {fReader, "Hlt2TopoMu3BodyDecision"};
   TTreeReaderValue<Int_t> Hlt2TopoMu4BodyDecision = {fReader, "Hlt2TopoMu4BodyDecision"};
   TTreeReaderValue<UInt_t> Hlt2nSelections = {fReader, "Hlt2nSelections"};
   TTreeReaderValue<Int_t> MaxRoutingBits = {fReader, "MaxRoutingBits"};
   TTreeReaderArray<Float_t> RoutingBits = {fReader, "RoutingBits"};


   BSubExample(TTree * /*tree*/ =0) { }
   virtual ~BSubExample() { }
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

   ClassDef(BSubExample,0);

};

#endif

#ifdef BSubExample_cxx
void BSubExample::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t BSubExample::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef BSubExample_cxx
