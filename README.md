# Lc->pKK Mass Analysis
Analysis of the Lc invariant mass using Lc->pKK decays. This repository includes the '.py' scripts used for data collection from the LHCb software and the '.C' scripts used for data analysis using the MakeSelector class.

Some relevant links: 
 * [A precision measurement of the Lc+ baryon mass](https://inspirehep.net/literature/686570 "Lc+ measurement")
 * [PDG Live - Lc+](https://pdglive.lbl.gov/Particle.action?init=0&node=S033&home=BXXX040 "Lc+ PDG")
 * [LHCb StarterKit Lessons](https://lhcb.github.io/starterkit-lessons/ "lhcb starterkit")

## Data Collection
The scripts used for data collection are stored in [`/LHCb/`](https://github.com/uc-lhcb/Lc2pKK/tree/master/LHCb) subdirectory. Because each run period requires slight modifications to the '.py' scripts, the scripts are stored in seperate directories based on year and magnet orientation `/LHCb/YEAR/MAG`. Each of these subdirectories has four python scripts. For example, within [`/LHCb/2017/MagnetDown2017`](https://github.com/uc-lhcb/Lc2pKK/tree/master/LHCb/2017/MagnetDown2017) there is:

 * [`DaVinci2017MagDown.py`](https://github.com/uc-lhcb/Lc2pKK/blob/master/LHCb/2017/MagnetDown2017/DaVinci2017MagDown.py): Davinci options file for 2017 MagnetDown Lc->pKK data.
 * [`GangaTestData2017MagDown.py`](https://github.com/uc-lhcb/Lc2pKK/blob/master/LHCb/2017/MagnetDown2017/GangaTestData2017MagDown.py): Ganga job that runs over 10 '.mdst' data files.
 * [`GangaAllData2017MagDown.py`](https://github.com/uc-lhcb/Lc2pKK/blob/master/LHCb/2017/MagnetDown2017/GangaAllData2017MagDown.py): Ganga job that runs over all '.mdst' data files.
 * [`ListLFNs.py`](https://github.com/uc-lhcb/Lc2pKK/blob/master/LHCb/2017/MagnetDown2017/ListLFNs.py): Python script to organize grid lfns into a '.txt' list.

### Initial Steps
* These data files will be fairly large, so you might want to increase your grid space through the LHCb [website](https://resources.web.cern.ch/resources/Help/?kbid=067040).
* These data files will be created on the ‘grid’, therefore, you will need to [upload your grid certificate](https://twiki.cern.ch/twiki/bin/view/LHCb/FAQ/Certificate) to lxplus. 
