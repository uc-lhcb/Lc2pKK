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
1. Data files will be fairly large, so you might want to increase your grid space through the LHCb [website](https://resources.web.cern.ch/resources/Help/?kbid=067040).
2. Data files will be created on the ‘grid’, therefore, you will need to [upload your grid certificate](https://twiki.cern.ch/twiki/bin/view/LHCb/FAQ/Certificate) to lxplus. 

### Getting Setup
1. Log into lxplus with 'ssh username@lxplus.cern.ch -X -Y'.
2. cd to private directory.
(Most of the users available storage is in their 'private' directory which is located in '/afs/cern.ch/work/”first letter of username”/”username”/private')
3. proxy into grid servers using 'lhcb-proxy-init'.
(grid proxy password is created when grid certificate is uploaded)

```
$ ssh username@lxplus.cern.ch -X -Y
$ cd /afs/cern.ch/work/u/username/private
$ lhcb-proxy-init
```

4. Upload Lc2pKK GitHub repository into lxplus using 'rsync' through local terminal.

```
$ rsync -aP /Downloads/Lc2pKK username@lxplus.cern.ch:/afs/cern.ch/work/u/username/private
```
or clone the repository directly from GitHub.

5. Within each `/LHCb/YEAR/MAG` subdirectory, set up the DaVinci development environment.
```
$ lb-dev --name DaVinciDev DaVinci/v45r8
```
### Data Acquistion
Every login to lxplus requires a resubmission of the grid proxy.

```
$ lhcb-proxy-init
```
 Within a given `/LHCb/YEAR/MAG` subdirectory, run the relevant ganga script with
```
$ ganga GangaTestData2017MagDown.py
```
for a small test sample, or
```
$ ganga GangaAllData2017MagDown.py
```
for all data.

### Monitoring

* To monitor the status of a job with job-number n:
```
$ jobs(n)
```

* To monitor the status of a subjob with subjob-number m of a job with job-number n:
```
$ jobs(n).subjobs(m)
```

* To restart subjobs that are stuck in completing state with job-number n: 
```
$ jobs(n).subjobs.select(status=’completing’).backend.reset()
```

* To restart subjobs that failed with job-number n:
```
$ jobs(n).subjobs.select(status=’failed’).resubmit()
```
