#pragma once

#include "TMath.h"
#include <iostream>

Double_t CrystalBall(Double_t *v, Double_t *par) {

// var[0] = x, par[0] = mu, par[1] = sigma, 
// par[2] = decay constant 'kl', par [3] = decay constant 'kh'
// par[4] = Linear Background Intercept, par[5] = Linear Background Slope

Double_t arg = 0;
  if (par[1] != 0)
    arg = (v[0] - par[0])/par[1];

 //Low Shoulder Exponential
  Double_t LEXP = TMath::Exp(0.5*par[2]*par[2] + par[2]*arg);
 
//Gaussian
Double_t Gauss = TMath::Exp(-0.5*arg*arg);

  
//High Shoulder Exponential
Double_t HEXP = TMath::Exp(0.5*par[3]*par[3] - par[3]*arg);
  
  if (arg <= -(par[2])) fitval = LEXP + par[4] + v[0]*par[5];
else if (arg > par[3]) fitval = HEXP + par[4] + v[0]*par[5];
else fitval = Gauss + par[4] + v[0]*par[5];

    return fitval;
}
