//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Detector Construction (source)
//  Building FSS-A detector in Geant4
//      Geometry: Box
//      Size: 1m * 1m * 1m
//      World Material: AIR
//      Substructures: 19 layers (Plastic -> Metal -> Plastic Det.)
//      Size: 50.8 mm * 50.8 mm * (Variable Thickness) (2 inch)
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

// A pointer to the Construct function
G4VPhysicalVolume *DetectorConstruction::Construct()
{
    // Overlap prevention
    G4bool checkOverlaps = true;

    //....oooOO0OOooo........oooOO0OOooo.... MATERIALS ....oooOO0OOooo........oooOO0OOooo......
    G4NistManager *nist = G4NistManager::Instance();
    
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *detMat   = nist->FindOrBuildMaterial("G4_POLYSTYRENE"); // Plastic
    
    // Metals
    G4Material *alMat = nist->FindOrBuildMaterial("G4_Al");
    G4Material *cuMat = nist->FindOrBuildMaterial("G4_Cu");
    G4Material *snMat = nist->FindOrBuildMaterial("G4_Sn");
    G4Material *pbMat = nist->FindOrBuildMaterial("G4_Pb");

    //....oooOO0OOooo........oooOO0OOooo.... THE AIR BOX ....oooOO0OOooo........oooOO0OOooo......
    G4double xWorld = 1. * m;
    G4double yWorld = 1. * m; 
    G4double zWorld = 1. * m;

    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * xWorld, 0.5 * yWorld, 0.5 * zWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.),
                                                    logicWorld, "physWorld",
                                                    0, false, 0, checkOverlaps);

    //....oooOO0OOooo........oooOO0OOooo.... FSS-A SETUP ....oooOO0OOooo........oooOO0OOooo......
    
    // Arrays defining the FSS-A metal stack thicknesses (19 layers)
    const G4int numLayers = 19;
    G4double metalThicknesses[numLayers] = {
        500.*um, 500.*um, 1500.*um,                                     // 1-3: Al
        500.*um, 500.*um, 1000.*um, 1000.*um, 1500.*um, 2000.*um,       // 4-9: Cu
        850.*um, 850.*um,                                               // 10-11: Sn
        1000.*um, 1000.*um, 1000.*um, 1000.*um, 1000.*um, 1000.*um, 3000.*um, 3000.*um // 12-19: Pb
    };

    // Global X/Y size for all plates
    G4double xySize = 50.8 * mm;
    
    // PLASTIC THICKNESS
    G4double plasticThickness = 1. * mm; 

    // Create shared Logical Volumes for the plastics (saves memory & simplifies SD assignment)
    G4Box *solidPlastic = new G4Box("solidPlastic", 0.5 * xySize, 0.5 * xySize, 0.5 * plasticThickness);
    
    G4LogicalVolume *logicPlasticLayer = new G4LogicalVolume(solidPlastic, detMat, "logicPlasticLayer");
    logicDetector = new G4LogicalVolume(solidPlastic, detMat, "logicDetector");

    // Plastic Visuals (Cyan for passive layer, Yellow for detector)
    G4VisAttributes *plastVis = new G4VisAttributes(G4Color(0.0, 1.0, 1.0, 0.3));
    plastVis->SetForceSolid(true);
    logicPlasticLayer->SetVisAttributes(plastVis);

    G4VisAttributes *detVis = new G4VisAttributes(G4Color(1.0, 1.0, 0.0, 0.5));
    detVis->SetForceSolid(true);
    logicDetector->SetVisAttributes(detVis);

    // Start building the stack
    G4double currentZ = 5.0 * cm; 

    //....oooOO0OOooo........oooOO0OOooo.... BUILDING THE STACK ....oooOO0OOooo........oooOO0OOooo......
    
    for (G4int i = 0; i < numLayers; i++) {
        
        // 1. Plastic Detector
        G4double zPosDet = currentZ + (0.5 * plasticThickness);
        new G4PVPlacement(0, G4ThreeVector(0., 0., zPosDet),
                          logicDetector, "physDetector",
                          logicWorld, false, i, checkOverlaps); // Copy number 'i' distinguishes the layers
        currentZ += plasticThickness;

        // 2. Metal Plate (Filter)
        G4double mThick = metalThicknesses[i];
        G4Material* mMat;
        G4Color mColor;

        // Assign Material and Color based on layer index
        if (i < 3)       { mMat = alMat; mColor = G4Color(0.6, 0.6, 0.6, 0.5); } // Aluminum: Gray
        else if (i < 9)  { mMat = cuMat; mColor = G4Color(0.8, 0.5, 0.2, 0.5); } // Copper: Orange
        else if (i < 11) { mMat = snMat; mColor = G4Color(0.9, 0.9, 0.9, 0.5); } // Tin: Light Gray
        else             { mMat = pbMat; mColor = G4Color(0.3, 0.3, 0.3, 0.5); } // Lead: Dark Gray

        // define a new solid/logical volume
        G4Box *solidMetal = new G4Box("solidMetal", 0.5 * xySize, 0.5 * xySize, 0.5 * mThick);
        G4LogicalVolume *logicMetal = new G4LogicalVolume(solidMetal, mMat, "logicMetal");
        
        G4VisAttributes *mVis = new G4VisAttributes(mColor);
        mVis->SetForceSolid(true);
        logicMetal->SetVisAttributes(mVis);

        G4double zPosMetal = currentZ + (0.5 * mThick);
        new G4PVPlacement(0, G4ThreeVector(0., 0., zPosMetal),
                          logicMetal, "physMetal",
                          logicWorld, false, i, checkOverlaps);
        currentZ += mThick;

        // 3. Plastic Layer
        G4double zPosPlast = currentZ + (0.5 * plasticThickness);
        new G4PVPlacement(0, G4ThreeVector(0., 0., zPosPlast),
                          logicPlasticLayer, "physPlasticLayer",
                          logicWorld, false, i, checkOverlaps);
        currentZ += plasticThickness;
    }

    return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo.... SENSITIVE DETECTOR ....oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
    // Apply this sensitive detector to our shared detector logical volume
    SensitiveDetector *sensDet = new SensitiveDetector("SensitiveDetector");
    logicDetector->SetSensitiveDetector(sensDet); 

    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
}