#include <iostream>

// Include Files from Geant4
#include "G4RunManager.hh" // heart of Geant4
#include "G4UIExecutive.hh" // User Interface
#include "G4UImanager.hh" // UI Manager

// number of argument, and argument vectors (defined as array of strings)
int main(int argc, char** argv)
{
    G4RunManager *runManager = new G4RunManager(); 
    // runManager is a pointer to RunManager, which is already built
    
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    // No Visualization availiable for Expanse SDSC

    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    // UIManager is a singleton

    ui->SessionStart(); // will not end session unless you type "exit"


    return 0;
}