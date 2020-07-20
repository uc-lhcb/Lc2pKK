
#pragma once

#include "TMath.h"
#include <iostream>

Double_t GaussCrystal1MeV(Double_t *v, Double_t *par) {

// var[0] = x, par[0] = Central Value, par[1] = Sigma of Gaussian, par[2] = Signal Total of Gaussian
// par[3] = Signal Total of Crystal Ball
// par[4] = Sigma of Crystal Ball
// par[5] = decay constant 'kl', par [6] = decay constant 'kh'
// par[7] = Linear Background Intercept, par[8] = Linear Background Slope

//Gaussian Function
    Double_t argGau = 0;
    if (par[1] != 0)
        argGau = (v[0] - par[0])/par[1];

    Double_t Gaussian = 0;
        Gaussian = par[2]*TMath::Exp(-0.5*argGau*argGau);

    Gaussian = (Gaussian)*(1.0)/(TMath::Sqrt(TMath::TwoPi())*par[1]);

//Crystal Ball Function
Double_t argCry = 0;
  if (par[4] != 0)
    argCry = (v[0] - par[0])/par[4];

  //1.0 MeV Bin Width Scaling Factor
  Double_t Scale = par[3]*(1.0)/(TMath::Sqrt(TMath::TwoPi())*par[4]);
  
 //Low Shoulder Exponential
  Double_t LEXP = Scale*TMath::Exp(0.5*par[5]*par[5] + par[5]*argCry);
 
//Gaussian
Double_t Gauss = Scale*TMath::Exp(-0.5*argCry*argCry);

//High Shoulder Exponential
Double_t HEXP = Scale*TMath::Exp(0.5*par[6]*par[6] - par[6]*argCry);
  
Double_t fitval = 0;
  
     if (argCry <= -(par[5])) fitval = LEXP + Gaussian + par[7] + v[0]*par[8];
else if (argCry > par[6]) fitval = HEXP + Gaussian + par[7] + v[0]*par[8];
else if (argCry > -(par[5]) && argCry <= par[6]) fitval = Gauss + Gaussian + par[7] + v[0]*par[8];

    return fitval;
}
