//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Detector Construction (source)
//  Building a detector in Geant4
//      Geometry: Box
//      Size: 1m * 1m * 1m
//      World Material: AIR
//      Detector: Plastic
//      Metal Plate: Al
//      Size: 10 cm * 10 cm * 500 um
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

    G4Material *alMat = nist->FindOrBuildMaterial("G4_Al"); // Al
    G4Material *detMat = nist->FindOrBuildMaterial("G4_POLYSTYRENE"); // Plastic

    //....oooOO0OOooo........oooOO0OOooo.... THE AIR BOX ....oooOO0OOooo........oooOO0OOooo......
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

    //....oooOO0OOooo........oooOO0OOooo.... THE LEAD BOX ....oooOO0OOooo........oooOO0OOooo......
    G4double alThickness = 500. * um; 
    G4double alSize = 10. * cm;

    G4Box *solidAl = new G4Box("solidAl", 0.5 * alSize, 0.5 * alSize, 0.5 * alThickness);

    G4LogicalVolume *logicAl = new G4LogicalVolume(solidAl, alMat, "logicAl");

    G4double zAl = 5.0 * cm;

    G4VPhysicalVolume *physAl = new G4PVPlacement(0, G4ThreeVector(0., 0., zAl),
                                                    logicAl, "physAl",
                                                    logicWorld, false,
                                                    0,
                                                    checkOverlaps);

    // Color: gray
    G4VisAttributes *alVisAtt = new G4VisAttributes(G4Color(0.6, 0.6, 0.6, 0.5));
    alVisAtt->SetForceSolid(true);
    logicAl->SetVisAttributes(alVisAtt);

    //....oooOO0OOooo........oooOO0OOooo.... THE DETECTOR ....oooOO0OOooo........oooOO0OOooo......
    // same size
    G4Box *solidDetector = new G4Box("solidDetector", 0.5 * alSize, 0.5 * alSize, 0.5 * alThickness);
    
    logicDetector = new G4LogicalVolume(solidDetector, detMat, "logicDetector");

    G4double zDet = zAl + alThickness;

    G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0. ,0., zDet),
                                                    logicDetector, "physDetector",
                                                    logicWorld, false,
                                                    0, checkOverlaps);

    G4VisAttributes *detVisAtt = new G4VisAttributes(G4Color(1.0, 1.0, 0.0, 0.5));
    detVisAtt->SetForceSolid(true);
    logicDetector->SetVisAttributes(detVisAtt);

    return physWorld;


}

void DetectorConstruction::ConstructSDandField()
{
    SensitiveDetector *sensDet = new SensitiveDetector("SensitiveDetector");
    logicDetector->SetSensitiveDetector(sensDet); // Applys this sensitive detector to our detector

    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
    // needed because we want initialization
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
//  Geant4 Vocab for Volumes
//      Solid: shape of the volume
//      Logical: volume filled in with material
//      Physical: volume placed in our world
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......