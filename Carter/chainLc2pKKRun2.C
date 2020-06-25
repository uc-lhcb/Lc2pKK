// TChains Four Ntuples from 2017
// Used With "root -l chainLc2pKKRun2.C"

{
TChain chain("Lc2pKKTuple/DecayTree");
chain.Add("/share/lazy/Lc2pKK/2017/LcTopKK.MagDown2017.root");
chain.Add("/share/lazy/Lc2pKK/2017/LcTopKK.MagUp2017.root");
}
