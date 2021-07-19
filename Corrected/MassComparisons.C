{
auto File = new TFile("Deviations.root", "RECREATE");
auto grid = new TCanvas("grid1","A Simple Graph", 900,500);
grid->SetGridx();
grid->SetLeftMargin(0.1);
grid->SetBottomMargin(0.15);
grid->SetRightMargin(0.2);

Double_t xblack[2] = {2287.523,2287.423};
Double_t yblack[2] = {1,4};
Double_t exblack[2] = {0.044,0.033};
Double_t eyblack[2] = {0,0};

Double_t xred[2] = {2287.422,2287.420};
Double_t yred[2] = {2,6};
Double_t exred[2] = {0.032,0.032};
Double_t eyred[2] = {0,0};

Double_t xblue[2] = {2287.393,2287.453};
Double_t yblue[2] = {3,5};
Double_t exblue[2] = {0.032,0.032};
Double_t eyblue[2] = {0,0};

auto g1 = new TGraphErrors(2,xblack,yblack,exblack,eyblack);
auto g2 = new TGraphErrors(2,xred,yred,exred,eyred);
auto g3 = new TGraphErrors(2,xblue,yblue,exblue,eyblue);

g1->SetMarkerColor(1);
g2->SetMarkerColor(2);
g3->SetMarkerColor(4);

 g1->GetXaxis()->CenterTitle(true);
 g1->GetXaxis()->SetTitleSize(20);
 g1->GetXaxis()->SetTitleFont(43);
 g1->GetXaxis()->SetTitleOffset(1.5);
 g1->GetXaxis()->SetLabelSize(0.025);
 g1->GetYaxis()->SetTitleSize(20);
 g1->GetYaxis()->SetTitleFont(43);
 g1->GetYaxis()->SetLabelSize(0);
 g1->SetMarkerStyle(20);
 g2->SetMarkerStyle(20);
 g3->SetMarkerStyle(20);
 g1->GetXaxis()->SetNdivisions(10);
 g1->SetTitle("");
 g1->GetXaxis()->SetTitle("m(pK^{-}K^{+}) Measurements [MeV]");
g1->GetXaxis()->SetRangeUser(2286.2,2287.6);
g1->SetMaximum(6.5);

g1->GetXaxis()->SetLimits(2287.35,2287.58);
g1->GetYaxis()->SetTickLength(0);
g1->Draw("ap");
g2->Draw("PSAME");
g3->Draw("PSAME");

TLine *line1 = new TLine(2287.39,4,2287.456,4);
line1->SetLineWidth(10);
line1->SetLineColor(5);
line1->Draw("SAME");

g1->Draw("PSAME");
auto lt = new TLatex();
lt->SetTextSize(0.03);

lt->DrawLatexNDC(0.81, 0.19, "Without Momentum");
lt->DrawLatexNDC(0.83, 0.17, "Corrections");

lt->DrawLatexNDC(0.81, 0.32, "D^{+} Mass = 1869.65 MeV");
lt->DrawLatexNDC(0.81, 0.30, "#color[2]{Kaon Mass = 493.664 MeV}");

lt->DrawLatexNDC(0.81, 0.45, "#color[4]{D^{+} Mass = 1869.60 MeV}");
lt->DrawLatexNDC(0.81, 0.43, "Kaon Mass = 493.677 MeV");

lt->DrawLatexNDC(0.81, 0.58, "D^{+} Mass = 1869.65 MeV");
lt->DrawLatexNDC(0.81, 0.56, "Kaon Mass = 493.677 MeV");

lt->DrawLatexNDC(0.81, 0.71, "#color[4]{D^{+} Mass = 1869.70 MeV}");
lt->DrawLatexNDC(0.81, 0.69, "Kaon Mass = 493.677 MeV");

lt->DrawLatexNDC(0.81, 0.83, "D^{+} Mass = 1869.65 MeV");
lt->DrawLatexNDC(0.81, 0.81, "#color[2]{Kaon Mass = 493.690 MeV}");

grid->SaveAs("MassComparisons.pdf");
}
