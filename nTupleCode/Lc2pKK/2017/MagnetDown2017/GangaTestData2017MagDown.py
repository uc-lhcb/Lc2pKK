j = Job(name='Lc+ ganga job - 10 Files of 2017 Data MagDown')
myApp = GaudiExec()
myApp.directory = "./DaVinciDev_v45r1"
j.application = myApp
j.application.options = ['Davinci2017MagDown.py']
j.application.platform = 'x86_64-centos7-gcc8-opt'
bkPath = '/LHCb/Collision17/Beam6500GeV-VeloClosed-MagDown/Real Data/Turbo04/94000000/CHARMCHARGED.MDST'
data  = BKQuery(bkPath, dqflag=['OK']).getDataset()
j.inputdata = data[0:10]
j.backend = Dirac()
j.splitter = SplitByFiles(filesPerJob=1)
j.outputfiles = [DiracFile('*.root'), LocalFile('stdout')]
j.submit()
