//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Detector Construction (header)
//  Building a detector in Geant4
//      Geometry: Box
//      Other Necessities are included
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

// The construction and geometry
#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
// Logical and Physical Volume
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
// Placement of the detector
#include "G4PVPlacement.hh"
// Materials used for detector Construction
#include "G4Material.hh"
#include "G4NistManager.hh"
// System of Units
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"


class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction(); // Constructor
    // The Destructor is already defined, so we need virtual in front
    virtual ~DetectorConstruction();

    // overide a defination
    virtual G4VPhysicalVolume *Construct();
};


#endif