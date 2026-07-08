#include <iostream>

// Include Files from Geant4
#include "G4RunManager.hh" // heart of Geant4
#include "G4MTRunManager.hh" // multi-thread mode
#include "G4UIExecutive.hh" // User Interface
#include "G4UImanager.hh" // UI Manager
// NOTE: No Visualization availiable for Expanse SDSC
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

// The Header Files
#include "PhysicsList.hh"
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

// number of argument, and argument vectors (defined as array of strings)
int main(int argc, char** argv)
{
    
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    // define a RunManager, multi of single thread
    #ifdef G4MULTITHREADED
        G4MTRunManager *runManager = new G4MTRunManager(); 
    #else
        G4RunManager *runManager = new G4RunManager(); 
        // runManager is a pointer to RunManager, which is already built
    #endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    // Register the Physics List
    runManager->SetUserInitialization(new PhysicsList());

    // Construct the Detector
    runManager->SetUserInitialization(new DetectorConstruction()); 

    // Shoot the Particle (via Action Initialization)
    runManager->SetUserInitialization(new ActionInitialization());     

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    // No Visualization availiable for Expanse SDSC
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    // UIManager is a singleton, so no "new"

    // Command using .mac file
    // 1. Visual
    //UImanager->ApplyCommand("/control/execute vrml.mac");   

    // 2. Default
    UImanager->ApplyCommand("/control/execute default.mac");   

    ui->SessionStart(); // will not end session unless you type "exit"


    return 0;
}