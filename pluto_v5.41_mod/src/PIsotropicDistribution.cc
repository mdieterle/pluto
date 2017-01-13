/////////////////////////////////////////////////////////////////////
//
// PIsotropicDistribution class
//
//                                  Author:  L. Witthauer
//                                           M. Dieterle
//                                  Written: 04.02.2010
//
/////////////////////////////////////////////////////////////////////


using namespace std;
#include <sstream>
#include <iostream>
#include <iomanip>

#include "PIsotropicDistribution.h"

ClassImp(PIsotropicDistribution)

PIsotropicDistribution::PIsotropicDistribution() {
} ;

PIsotropicDistribution::~PIsotropicDistribution() {
    if (myparticle) delete (myparticle);
} ;


PIsotropicDistribution::PIsotropicDistribution(Char_t *id, Char_t *de) :
    PDistribution(id, de) {

    Info("Constructor","You now arrived in your class!");

    particle   = NULL;
    myparticle = NULL;
    e_dist     = NULL;

} ;

PDistribution* PIsotropicDistribution::Clone(const char*delme) const {
    return new PIsotropicDistribution((const PIsotropicDistribution &)* this);
};


Bool_t PIsotropicDistribution:: Init(void) {
    //Read beam, target and parent

    particle = GetParticle("particle");

    if (!particle) {
	Error("Init","Particle not found");
	return kFALSE;
    }
    if (!myparticle)
	myparticle = new PParticle(particle);
    else
	*myparticle = *particle;

    Info("Init","Particle with ID %d found", particle->ID());

    if (e_dist){
        Info("Init","Energy distribution found");
    }

    if (!e_dist) {
	Warning("Init","No energy distribution found");
    }

    return kTRUE;
}

Bool_t PIsotropicDistribution:: Prepare(void) {
    //We use the prepare function for smearing since it might affect
    //the mass and momentum sampling done in the next steps

    Double_t m      = particle->M();
    Double_t px     = 0.;
    Double_t py     = 0.;
    Double_t pz     = 0.;
    Double_t pt     = 0.;
    Double_t energy = 1.;

    Info("Prepare","I am here");

    if (e_dist) energy = e_dist->GetRandom();
    pt = TMath::Sqrt( energy*energy - m*m ); 
    gRandom->Sphere(px,py,pz,pt);

    //restore saved particles
    *particle=*myparticle;

    particle->SetPxPyPzE(px,py,pz,energy);


    particle->Reconstruct();

//    parent->Print("scatter");

    return kTRUE;

}

void PIsotropicDistribution::SetParticle(char * part) {
//    char *array[2];
//    Int_t array_s=2; //max products
//    PUtils::Tokenize(reaction, "+", array, &array_s);
    Add(part,"grandparent","particle");
    Info("SetParticle","Particle %s chosen", part);
//    Add(array[0],"grandparent","beam");
//    Add(array[1],"grandparent","target");
//    NoDaughters();

}

void PIsotropicDistribution::Print(const Option_t* delme) const{

    PDistribution::Print();
}


