//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Action Initialization (source)
//  To help start the particle gun.
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization()
{

}

ActionInitialization::~ActionInitialization()
{

}

void ActionInitialization::BuildForMaster() const
{
    RunAction *runAction = new RunAction();
    SetUserAction(runAction);
}

void ActionInitialization::Build() const
{
    // hand over primary generator
    PrimaryGenerator *generator = new PrimaryGenerator();
    // giving out the particle gun
    SetUserAction(generator);

    RunAction *runAction = new RunAction(); //our own run, created and declared
    SetUserAction(runAction);
}