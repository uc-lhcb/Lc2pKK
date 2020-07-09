// TChains Four Ntuples from 2017
// Used With "root -l chainLc2pKKRun2.C"

{
TChain chain("Lc2pKKTuple/DecayTree");
chain.Add("/share/lazy/Lc2pKK/Ntuples/Lc2pKK_MagDown2017.root");
chain.Add("/share/lazy/Lc2pKK/Ntuples/LcMagUp8.root");
}
