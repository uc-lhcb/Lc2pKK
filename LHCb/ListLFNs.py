#Creates .txt file with list of LFNs for all subjobs of job argument, "ganga ListLFNs.py 73"

import sys
jobNumber = int(sys.argv[1])
length = len(jobs(jobNumber).subjobs)
file = open('LFNs.txt','w')
for i in range(0,length):
    output = jobs(jobNumber).subjobs(i).backend.getOutputDataLFNs()
    if( output.hasLFNs() == True):
        s = str(jobs(jobNumber).subjobs(i).outputfiles[0].accessURL())
        print s
        file.write(s)
        file.write('\n')
file.close()
