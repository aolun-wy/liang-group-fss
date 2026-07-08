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
    
    // Merging N Tuples in multi-thread
    man->SetVerboseLevel(1);
    man->SetNtupleMerging(true);


    //....oooOO0OOooo........oooOO0OOooo.... The Output ....oooOO0OOooo........oooOO0OOooo......
    // ___=== = #1 Histogram = ===___
    
    man->CreateH1("EnergyDep", "Energy Deposited", 100, 0., 1.1 * MeV); // create 1-dim'l histogram
    // <NAME>, <TITLE>, number of bins, lower bound, upper bound

    // ___=== = #2 Ntuple = ===___

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

RunAction::~RunAction()
{

}

void RunAction::BeginOfRunAction(const G4Run *run)
{

    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID << runID;

    G4cout << "Start Running ID:  "<< strRunID.str() << G4endl;
    
    G4AnalysisManager *man = G4AnalysisManager::Instance(); 
    // a singleton, so no "new"
    //man->OpenFile("output.root");

    G4bool ok = man->OpenFile("output" + strRunID.str() + ".root");

    G4cout << "OpenFile returned " << ok << G4endl;

}

void RunAction::EndOfRunAction(const G4Run *run)
{

    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID << runID;

    G4AnalysisManager *man = G4AnalysisManager::Instance(); 
    // a singleton, so no "new"

    man->Write(); // write the root file
    man->CloseFile(); // close it
    
    G4cout << "End Running ID: " << strRunID.str() << G4endl;
}

