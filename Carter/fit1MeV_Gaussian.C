#pragma once

#include "TMath.h"
#include <iostream>

Double_t fit1MeV_Gaussian(Double_t *v, Double_t *par) {
   
    Double_t arg = 0;
    if (par[2] != 0)
        arg = (v[0] - par[1])/par[2];

    Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);

    fitval = (fitval*1.00)/(TMath::Sqrt(TMath::TwoPi())*par[2]);

    //  add a linear background
    fitval = fitval + par[3] + v[0]*par[4];

    //  we're done
    return fitval;
}
