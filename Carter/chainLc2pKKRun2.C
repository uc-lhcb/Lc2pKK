// TChains Four Ntuples from 2017
// Used With "root -l chainLc2pKKRun2.C"

{
TChain chain("Lc2pKKTuple/DecayTree");
chain.Add("/share/lazy/Lc2pKK/Ntuples/Lc2pKK_MagDown2017.root");
chain.Add("/share/lazy/Lc2pKK/Ntuples/LcMagUp1.root");
chain.Add("/share/lazy/Lc2pKK/Ntuples/LcMagUp2.root");
chain.Add("/share/lazy/Lc2pKK/Ntuples/LcMagUp3.root");
chain.Add("/share/lazy/Lc2pKK/Ntuples/LcMagUp4.root");
chain.Add("/share/lazy/Lc2pKK/Ntuples/LcMagUp5.root");
}
