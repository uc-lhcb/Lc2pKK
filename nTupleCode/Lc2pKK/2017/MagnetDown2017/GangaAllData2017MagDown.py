j = Job(name='Lc+ ganga job - All 2017 Data MagDown')
myApp = GaudiExec()
myApp.directory = "./DaVinciDev"
j.application = myApp
j.application.options = ['DaVinci2017MagDown.py']
j.application.platform = 'x86_64-centos7-gcc8-opt'
bkPath = '/LHCb/Collision17/Beam6500GeV-VeloClosed-MagDown/Real Data/Turbo04/94000000/CHARMCHARGED.MDST'
data  = BKQuery(bkPath, dqflag=['OK']).getDataset()
j.inputdata = data
j.backend = Dirac()
j.splitter = SplitByFiles(filesPerJob=10, ignoremissing = True)
j.outputfiles = [DiracFile('*.root'), LocalFile('stdout')]
j.submit()
