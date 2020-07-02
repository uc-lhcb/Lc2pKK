from GaudiConf import IOHelper
from Configurables import (DaVinci, LoKi__Hybrid__TupleTool, LoKi__Hybrid__DictOfFunctors, LoKi__Hybrid__DTFDict, LoKi__Hybrid__DictValue, LoKi__Hybrid__Dict2Tuple,
                           LoKi__Hybrid__EvtTupleTool, TupleToolKinematic, TupleToolGeometry, TupleToolPid, TupleToolAllTracks)
from DecayTreeTuple.Configuration import *
import math

stream = 'Charmcharged'
line = 'Hlt2CharmHadLcpToPpKmKpTurbo'

dtt = DecayTreeTuple('Lc2pKKTuple')
dtt.Inputs = ['{0}/Particles'.format(line)]
dtt.Decay = '[Lambda_c+ -> ^p+ ^K- ^K+]CC'
tuple_tools = [
        "TupleToolEventInfo",
        "TupleToolGeometry",
        "TupleToolKinematic",
        "TupleToolPid",
        "TupleToolPrimaries",
        "TupleToolTrackInfo"
]

dtt.ToolList = tuple_tools
dtt.addTupleTool("TupleToolRecoStats").Verbose = True
ttt = dtt.addTupleTool("TupleToolTrigger")
ttt.Verbose = True

triggerList = [
    #L0 TCKsh
    "L0MuonDecision",
    "L0DiMuonDecision"
    "L0HadronDecision",
    "L0ElectronDecision",
    "L0PhotonDecision",
    #Hlt1 lines TCKsh
    "Hlt1TrackMVADecision",
    "Hlt1TwoTrackMVADecision",
    "Hlt1TrackMVATightDecision",
    "Hlt1TwoTrackMVATightDecision",
    "Hlt1TrackMuonDecision",
    "Hlt1TrackMuonMVADecision",
    #Hlt2 lines TCKsh
    "Hlt2Topo2BodyDecision",
    "Hlt2Topo3BodyDecision",
    "Hlt2Topo4BodyDecision",
    "Hlt2TopoMu2BodyDecision",
    "Hlt2TopoMu3BodyDecision",
    "Hlt2TopoMu4BodyDecision"
]
ttt.TriggerList = triggerList

tttt = dtt.addTupleTool("TupleToolTISTOS")
tttt.Verbose = True #To decisions from all trigger stages
tttt.TriggerList = triggerList

basic_loki_vars = {
"PHI" : "PHI",
"ETA" : "ETA"
}

dtt.addTupleTool(
"LoKi::Hybrid::TupleTool/basicLokiTT"
).Variables = basic_loki_vars

dtt.addBranches({
        'Lcplus' : '([Lambda_c+ -> p+ K- K+]CC)',
        'Proton' : '([Lambda_c+ -> ^p+ K- K+]CC)',
        'Kminus' : '([Lambda_c+ -> p+ ^K- K+]CC)',
        'Kplus' : '([Lambda_c+ -> p+ K- ^K+]CC)'
})

dtt.Lcplus.addTupleTool('TupleToolDecayTreeFitter/ConsLc')
dtt.Lcplus.ConsLc.constrainToOriginVertex = True
dtt.Lcplus.ConsLc.Verbose = True
dtt.Lcplus.ConsLc.daughtersToConstrain = ['Lambda_c+']

dtt.Lcplus.addTupleTool('TupleToolPropertime')

Lc_hybrid = dtt.Lcplus.addTupleTool('LoKi::Hybrid::TupleTool/LoKi_Lc')
Pp_hybrid = dtt.Proton.addTupleTool('LoKi::Hybrid::TupleTool/LoKi_Pp')
Km_hybrid = dtt.Kminus.addTupleTool('LoKi::Hybrid::TupleTool/LoKi_Km')
Kp_hybrid = dtt.Kplus.addTupleTool('LoKi::Hybrid::TupleTool/LoKi_Kp')

Lc_hybrid.Variables = {
        "Loki_DOCAMAX"        : "DOCAMAX",
        "Loki_DOCACHI2MAX"    : "DOCACHI2MAX",
        "Loki_SUMPT"          : "SUMTREE(PT,  ISBASIC)",
        "Loki_BPVLTIME"       : "BPVLTIME()",
        "Loki_BPVX"           : "BPV(VX)",
        "Loki_BPVY"           : "BPV(VY)",
        "Loki_BPVZ"           : "BPV(VZ)",
        "Loki_BPVCOV_XX"      : "BPV(VCOV2(0,0))",
        "Loki_BPVCOV_XY"      : "BPV(VCOV2(0,1))",
        "Loki_BPVCOV_XZ"      : "BPV(VCOV2(0,2))",
        "Loki_BPVCOV_YY"      : "BPV(VCOV2(1,1))",
        "Loki_BPVCOV_YZ"      : "BPV(VCOV2(1,2))",
        "Loki_BPVCOV_ZZ"      : "BPV(VCOV2(2,2))"
}

DaVinci().UserAlgorithms += [dtt]

DaVinci().Turbo = True
DaVinci().RootInTES = '/Event/Charmcharged/Turbo'
DaVinci().InputType = 'MDST'
DaVinci().DDDBtag = 'dddb-20171030-3'
DaVinci().Simulation = False
DaVinci().TupleFile = 'Lc2pKKTest.root'
DaVinci().PrintFreq = 10000
DaVinci().DataType = '2017'
DaVinci().Lumi = True
DaVinci().EvtMax = -1

#IOHelper().inputFiles([
#    'root://hake1.grid.surfsara.nl:1094/pnfs/grid.sara.nl/data/lhcb/LHCb/Collision17/CHARMCHARGED.MDST/00067727/0001/00067727_00012788_1.charmcharged.mdst'], clear=True)

