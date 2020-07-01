j = Job(name='Lc2pKKLumiFix')
myApp = GaudiExec()
myApp.directory = "./DaVinciDev_v45r1"
j.application = myApp
j.application.options = ['LambdaDavinci.py']
j.application.platform = 'x86_64-centos7-gcc8-opt'

inputLFN = [
"LFN:/lhcb/LHCb/Collision17/CHARMCHARGED.MDST/00064953/0000/00064953_00003046_1.charmcharged.mdst",
"LFN:/lhcb/LHCb/Collision17/CHARMCHARGED.MDST/00064953/0000/00064953_00003158_1.charmcharged.mdst",
"LFN:/lhcb/LHCb/Collision17/CHARMCHARGED.MDST/00064953/0000/00064953_00003156_1.charmcharged.mdst"
]

j.inputdata = inputLFN
j.backend = Dirac()
j.splitter = SplitByFiles(filesPerJob=1)
j.outputfiles = [DiracFile('*.root'), LocalFile('stdout')]
j.submit()
