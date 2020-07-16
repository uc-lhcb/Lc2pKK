#pragma once

#include "TMath.h"
#include <iostream>

Double_t CrystalBall1MeV(Double_t *v, Double_t *par) {

// var[0] = x, par[0] = mu, par[1] = sigma, par[2] = signal total
// par[3] = decay constant 'kl', par [4] = decay constant 'kh'
// par[4] = Linear Background Intercept, par[5] = Linear Background Slope

Double_t arg = 0;
  if (par[1] != 0)
    arg = (v[0] - par[0])/par[1];

  //1.0 MeV Bin Width Scaling Factor
  Double_t Scale = par[2]*(1.0)/(TMath::Sqrt(TMath::TwoPi())*par[1]);
  
 //Low Shoulder Exponential
  Double_t LEXP = Scale*TMath::Exp(0.5*par[3]*par[3] + par[3]*arg);
 
//Gaussian
Double_t Gauss = Scale*TMath::Exp(-0.5*arg*arg);

//High Shoulder Exponential
Double_t HEXP = Scale*TMath::Exp(0.5*par[4]*par[4] - par[4]*arg);
  
Double_t fitval = 0;
  
     if (arg <= -(par[3])) fitval = LEXP + par[5] + v[0]*par[6];
else if (arg > par[4]) fitval = HEXP + par[5] + v[0]*par[6];
else if (arg > -(par[3]) && arg <= par[4]) fitval = Gauss + par[5] + v[0]*par[6];

    return fitval;
}
