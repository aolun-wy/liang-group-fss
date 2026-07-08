//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Run Action (header)
//  Managing the data gathered from shooting particles
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"

//#include "g4root.hh"
#include "G4AnalysisManager.hh"

class RunAction : public G4UserRunAction
{
public:
    RunAction();
    ~RunAction();

    // Begain and End of Run data gathering
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

};

#endif