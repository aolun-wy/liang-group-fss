//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Action Initialization (header)
//  To help start the particle gun.
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// avoid implementing several times
#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "PrimaryGenerator.hh"

#include "RunAction.hh"

class ActionInitialization : public G4VUserActionInitialization
{
public:
    ActionInitialization();
    ~ActionInitialization();

    virtual void BuildForMaster() const; // master thread, for manage the threads
    virtual void Build() const; // single thread, for giving out particle guns
    // stay constant to avoid problem
};


#endif