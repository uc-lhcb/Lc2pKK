// TChains Four Ntuples from 2011/2012
// Used With "root -l chainLc2pKKRun1.C"

{
TChain chain("TupleLbToLcmu_LcTopKK/DecayTree");
chain.Add("/share/lazy/Lc2pKK/2011/Lc2pXX.2011.MagDown.root");
chain.Add("/share/lazy/Lc2pKK/2011/Lc2pXX.2011.MagUp.root");
chain.Add("/share/lazy/Lc2pKK/2012/Lc2pXX.2012.MagDown.root");
chain.Add("/share/lazy/Lc2pKK/2012/Lc2pXX.2012.MagUp.root");
}
