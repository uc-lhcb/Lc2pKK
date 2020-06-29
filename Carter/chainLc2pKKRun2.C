// TChains Four Ntuples from 2017
// Used With "root -l chainLc2pKKRun2.C"

{
TChain chain("Lc2pKKTuple/DecayTree");
chain.Add("/share/lazy/Lc2pKK/2017/Lc2pKK_2017MagDown0x11611708.root");
chain.Add("/share/lazy/Lc2pKK/2017/Lc2pKK_2017MagUp0x11611709.root");
chain.Add("/share/lazy/Lc2pKK/2017/Lc2pKK_2017MagDown0x11561707.root");
chain.Add("/share/lazy/Lc2pKK/2017/Lc2pKK_2017MagUp0x11561707.root")
}
