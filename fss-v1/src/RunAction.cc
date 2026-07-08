//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Run Action (header)
//  Managing the data gathered from shooting particles in a root file
//  The output file should consist
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "RunAction.hh"


RunAction::RunAction()
{
    G4AnalysisManager *man = G4AnalysisManager::Instance(); 

    man->SetVerboseLevel(1);
    man->SetNtupleMerging(true);
}

RunAction::~RunAction()
{

}

void RunAction::BeginOfRunAction(const G4Run*)
{
    G4cout << "BeginRunAction Called" << G4endl;
    
    G4AnalysisManager *man = G4AnalysisManager::Instance(); 
    // a singleton, so no "new"
    //man->OpenFile("output.root");

    G4bool ok = man->OpenFile("output.root");

    G4cout << "OpenFile returned " << ok << G4endl;

//....oooOO0OOooo........oooOO0OOooo.... The Output ....oooOO0OOooo........oooOO0OOooo......
// ___=== = #1 Ntuple = ===___
    man->CreateNtuple("Hits", "FilterStack"); // rows created
    man->CreateNtupleIColumn("EventID"); // integer, event number as columns
    man->CreateNtupleIColumn("DetectorID");
    man->CreateNtupleDColumn("EnergyDep"); // in MeV
    // doubles, position of the detector, as columns
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(0); // <Number of Ntuples>
}

void RunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance(); 
    // a singleton, so no "new"

    man->Write(); // write the root file
    man->CloseFile("output.root"); // close it
    
    G4cout << "EndRunAction Called" << G4endl;
}

