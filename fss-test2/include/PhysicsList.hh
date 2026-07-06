//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Physics List (header)
//  Modular Physics and EM Physics required for this project
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// avoid implementing several times
#ifndef PHYSICSLIST_HH
#define PHYSICSLIST_HH

#include "G4VModularPhysicsList.hh" // The basic list required for physics
#include "G4EmStandardPhysics.hh"   // Standard EM Physics

// Class defined for Physics Matter, inherited from basic physics list
class PhysicsList : public G4VModularPhysicsList
{
// publicly defined, accessible by other functions
public:
    PhysicsList(); // Constructor, applying what we had in header file
    ~PhysicsList(); // Destructor
};


#endif