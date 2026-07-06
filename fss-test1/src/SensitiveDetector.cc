//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Sensitive Detector (source)
//  For Sensitive Detector, energy, position, etc.
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
    fTotalEnergyDeposited = 0. ;
}

SensitiveDetector::~SensitiveDetector()
{
    
}

void SensitiveDetector::Initialize(G4HCofThisEvent *)
{
    fTotalEnergyDeposited = 0. ; 
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{
    G4cout << "Deposited Energy: " << fTotalEnergyDeposited <<G4endl;
}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *touchHist)
{
    G4double fEnergyDeposited = aStep->GetTotalEnergyDeposit();

    if (fEnergyDeposited > 0)
    {
        fTotalEnergyDeposited += fEnergyDeposited;
    }

    return true; // Requires return, since it is boolean
}