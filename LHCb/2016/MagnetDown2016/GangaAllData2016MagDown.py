j = Job(name='Lc+ ganga job - All 2016 Data MagDown')
myApp = GaudiExec()
myApp.directory = "./DaVinciDev"
j.application = myApp
j.application.options = ['DaVinci2016MagDown.py']
j.application.platform = 'x86_64-centos7-gcc8-opt'
bkPath = '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagDown/Real Data/Turbo03a/94000000/CHARMCHARGED.MDST'
data  = BKQuery(bkPath, dqflag=['OK']).getDataset()
j.inputdata = data
j.backend = Dirac()
j.splitter = SplitByFiles(filesPerJob=5, ignoremissing = True)
j.outputfiles = [DiracFile('*.root'), LocalFile('stdout')]
j.submit()
