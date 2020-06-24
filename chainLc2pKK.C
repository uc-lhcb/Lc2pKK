// TChains Four Ntuples from 2011/2012
// Used With "root -l chainLc2pKK.C"

{
TChain chain("TupleLbToLcmu_LcTopKK/DecayTree");
chain.Add("Lc2pXX.2011.MagDown.root");
chain.Add("Lc2pXX.2011.MagUp.root");
chain.Add("Lc2pXX.2012.MagDown.root");
chain.Add("Lc2pXX.2012.MagUp.root");
}
