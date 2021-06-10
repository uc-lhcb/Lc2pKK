j = Job(name='Lc+ ganga job - All 2018 Data MagDown')
myApp = GaudiExec()
myApp.directory = "./DaVinciDev"
j.application = myApp
j.application.options = ['DaVinci2018MagDown.py']
j.application.platform = 'x86_64-centos7-gcc8-opt'
bkPath = '/LHCb/Collision18/Beam6500GeV-VeloClosed-MagDown/Real Data/Turbo05/94000000/CHARMCHARGED.MDST'
data  = BKQuery(bkPath, dqflag=['OK']).getDataset()
j.inputdata = data
j.backend = Dirac()
j.splitter = SplitByFiles(filesPerJob=1)
j.outputfiles = [DiracFile('*.root'), LocalFile('stdout')]
j.submit()
