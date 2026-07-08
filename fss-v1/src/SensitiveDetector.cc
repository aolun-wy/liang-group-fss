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
    // ===== #1. Track the Particles =====
    // In reality, we will not able to gain information
    // on photons in experiments.
    G4Track *track = aStep->GetTrack();

    track->SetTrackStatus(fStopAndKill); // stop tracking when entered the detector

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint(); // before entering detector
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint(); // after entering detector

    // Position of Photon
    G4ThreeVector posPhoton = preStepPoint->GetPosition();
    G4cout << " Photon Position: " << posPhoton << G4endl;

    // ===== #2. Multiple Detector Position =====    
    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int copyNo = touchable->GetCopyNumber();

    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    G4cout<< "Detector Position: "<< posDetector << G4endl;

   // ===== #3. Track the Energy =====   

    G4double fEnergyDeposited = aStep->GetTotalEnergyDeposit();
    if (fEnergyDeposited > 0)
    {
        fTotalEnergyDeposited += fEnergyDeposited;
    }

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    man->FillNtupleIColumn(0, evt); // Event ID
    man->FillNtupleIColumn(1, copyNo); // copy Number, detector No.
    man->FillNtupleDColumn(2, fEnergyDeposited / MeV); // Energy Deposited, in MeV
    // position of Detector, in mm
    man->FillNtupleDColumn(3, posDetector[0] / mm);
    man->FillNtupleDColumn(4, posDetector[1] / mm);
    man->FillNtupleDColumn(5, posDetector[2] / mm);
    man->AddNtupleRow(0);

    return true; // Requires return, since it is boolean
}