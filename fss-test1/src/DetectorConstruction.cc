//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Detector Construction (source)
//  Building a detector in Geant4
//      Geometry: Box
//      Size: 1m * 1m * 1m
//      Material: AIR
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"

// The Constructor
DetectorConstruction::DetectorConstruction()
{

}

// The Destructor
DetectorConstruction::~DetectorConstruction()
{
    
}

// a pointer to Construct function
G4VPhysicalVolume *DetectorConstruction::Construct()
{
    // overlap prevention
    G4bool checkOverlaps = true;

    // Material of the world
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR"); // the built-in material, e.g. air

    // Size of our volume
    G4double xWorld = 1. * m;
    G4double yWorld = 1. * m; 
    G4double zWorld = 1. * m;

    // SOLID VOLUME
    G4Box *solidWorld = new G4Box("solidWorld",
                                0.5 * xWorld, 0.5 * yWorld, 0.5 * zWorld);
    // "<NAME>", length, height, width
    // The length parameters ALWAYS take half, so multiply by 0.5

    // LOGICAL VOLUME
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    // Solid Volume, Material, "<NAME>"

    // PHYSICAL VOLUME
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.),
                                                    logicWorld, "physWorld",
                                                    0, false,
                                                    0,
                                                    checkOverlaps);
    // Rotation, Position(3-vector), logical Volume, "<NAME>"
    // Mother Volume outside (no, then 0), Use boolean calculation?
    // Copy Number (may have several physical volume with same logical volume
    // Overlap detection

    return physWorld;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
//  Geant4 Vocab for Volumes
//      Solid: shape of the volume
//      Logical: volume filled in with material
//      Physical: volume placed in our world
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......