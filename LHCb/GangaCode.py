#Run With, For Example, 'ganga -i GangaCode.py 2017 MagDown --test'

import argparse

VALID_POLARITIES = ['MagUp', 'MagDown']
VALID_YEARS = [2017, 2018]

BEAM_ENERGY = 6500

stream = 'CHARMCHARGED.MDST'

parser = argparse.ArgumentParser(description="Make my DaVinci job.")
parser.add_argument('year', type=int, choices=[2017, 2018],
                    help='Year of data-taking to run over')
parser.add_argument('polarity', choices=['MagUp', 'MagDown'],
                    help='Polarity of data-taking to run over')
parser.add_argument('--test', action='store_true',
                    help='Run over one file locally')

args = parser.parse_args()
year = args.year
polarity = args.polarity
test = args.test

Turbo_VERSION = 'Turbo0{0}'
turbo = Turbo_VERSION.format('4' if year == 2017 else '5')

def bookkeeping_path(polarity, year, turbo):
    """Return the bookkeeping path for the given parameters."""
    bkq_path = (
        '/LHCb/Collision{year}/Beam{energy}GeV-VeloClosed-{polarity}/Real Data/{turbo}/94000000/{stream}'
    )
    return bkq_path.format(
        # Only use last two digits of the year
        year=(year - 2000),
        energy=BEAM_ENERGY,
        polarity=polarity,
        turbo=turbo,
        stream=stream
    )
  
title = 'Creating job for charm production ntuples using {0} {1} data'
title = title.format(
    polarity, year
)
print('='*len(title))
print(title)
print('='*len(title))

bkq = BKQuery(bookkeeping_path(polarity, year, turbo), dqflag=['OK'])
dataset = bkq.getDataset()

j = Job(name='Lc2pKK_{0}_{1}'.format(
    year, polarity
))

outputfile='Lc2pKK_{0}_{1}.root'.format(
    year, polarity
)

j.comment = title
myApp = GaudiExec()
myApp.directory = "./DaVinciDev_v45r1"
j.application = myApp
j.application.options = ['NewDavinciCode.py']
j.application.platform = 'x86_64-centos7-gcc8-opt'

if args.test:
    j.inputdata = dataset[0:5]
    j.backend = Dirac()
    j.name = 'TEST_{0}'.format(j.name)
    j.splitter = SplitByFiles(filesPerJob=1)
    j.outputfiles = [LocalFile(outputfile), LocalFile('stdout')]
    j.submit()
else:
    j.inputdata = dataset
    j.backend = Dirac()
    j.do_auto_resubmit = True
    j.splitter = SplitByFiles(filesPerJob=1)
    j.postprocessors = [Notifier(address='carter.eikenbary@cern.ch')]
    j.outputfiles = [DiracFile(outputfile), LocalFile('stdout')]
    j.submit()

