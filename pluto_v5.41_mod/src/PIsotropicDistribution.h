// same header file as used in PBeamSmearing
// used here for PIsotropicDistribution
//
// Author:  L.Witthauer, M.Dieterle
// Written: 04.02.2010
// Revised: 

#ifndef _PISOTROPICDISTRIBUTION_H_
#define _PISOTROPICDISTRIBUTION_H_



#include "TF1.h"
#include "TF2.h"
#include "TH1F.h"
#include "PDistribution.h"


class PIsotropicDistribution : public PDistribution  {
  
 public:
    PIsotropicDistribution();
    ~PIsotropicDistribution();
    PIsotropicDistribution(Char_t *id, Char_t *de);
    
    PDistribution* Clone(const char*delme=NULL) const;

    Bool_t Init(void);
    Bool_t Prepare(void);
    
    void Print(const Option_t* delme=NULL) const;  //Debug info
    
    void SetEnergyDistribution(TF1 * f) {e_dist=f;};
    //A function stretching the beam momentum (x=1 means no modification)
    
    void SetParticle(char * part);


 private:

    PParticle * particle, * myparticle;

    TF1     *e_dist;
    ClassDef(PIsotropicDistribution,0)  // General purpose beam smearing models
};

#endif


