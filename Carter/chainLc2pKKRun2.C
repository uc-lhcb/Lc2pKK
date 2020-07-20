// TChains Four Ntuples from 2017
// Used With "root -l chainLc2pKKRun2.C"

{
TChain chain("Lc2pKKTuple/DecayTree");
chain.Add("/share/lazy/Lc2pKK/2017/Lc2pKK_MagDown2017.root");
chain.Add("/share/lazy/Lc2pKK/2017/Lc2pKK_MagUp2017.root");
//chain.Add("/share/lazy/Lc2pKK/2018/Lc2pKK_MagDown2018.root");
//chain.Add("/share/lazy/Lc2pKK/2018/Lc2pKK_MagUp2018.root");  
}
