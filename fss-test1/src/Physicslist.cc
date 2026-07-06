//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Physics List (source)
//  EM Physics List registered for the project
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PhysicsList.hh"

// The Constructor, defined as a class PMPhysicsList
PhysicsList::PhysicsList()
{
    // Only Need EM Physics for the experiment
    RegisterPhysics(new G4EmStandardPhysics());
}

// The Destructor
PhysicsList::~PhysicsList()
{
    // empty, as Geant4 automatically cleans out
}