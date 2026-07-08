//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Sensitive Detector (header)
//  For Sensitive Detector, energy, position, etc.
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef SENSITIVEDETECTOR_HH
#define SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"


class SensitiveDetector : public G4VSensitiveDetector
{
public:
    SensitiveDetector(G4String); // name of the detector
    ~SensitiveDetector();
private:
    G4double fTotalEnergyDeposited; // not changeble by other functions

    virtual void Initialize(G4HCofThisEvent *) override;
    virtual void EndOfEvent(G4HCofThisEvent *) override;
    // HC - Hit Collection

    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
    // during the event - calculate
    // Particle moves in Step, and calculate step by step
    // The detector where the particle is.
};


#endif