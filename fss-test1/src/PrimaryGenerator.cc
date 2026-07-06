//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Partical Gun (source)
//  Shooting Positrons, with a particle gun fParticleGun
//
// NOTE: We CAN'T hand this directly to the main function, we need to define another class
// i.e. "Action Initialization" to run this.
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PrimaryGenerator.hh"

// The Constructor
PrimaryGenerator::PrimaryGenerator()
{
    // The Particle Gun
    fParticleGun = new G4ParticleGun(1); // only 1 particle per event

    // === The Particle Position ===
    G4double x = 0. * m;
    G4double y = 0. * m;
    G4double z = 0. * m;

    G4ThreeVector pos(x, y, z); // The Position Three-vector

    // === The Particle Direction ===
    G4double px = 0. ;
    G4double py = 0. ;
    G4double pz = 0. ;
    
    G4ThreeVector mom(px, py, pz); // The Momentum Three-vector 
    
    // === The Particle Type === 
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("e+"); // positron


   // === The Initial Setting of Particle Gun ===
   fParticleGun->SetParticlePosition(pos);          // POSITION
   fParticleGun->SetParticleMomentumDirection(mom); // DIRECTION
   fParticleGun->SetParticleEnergy(1. * GeV);       // ENERGY (insert your own value)
   fParticleGun->SetParticleDefinition(particle);   // TYPE
}

// The Destructor
PrimaryGenerator::~PrimaryGenerator()
{
    delete fParticleGun;
}

// The function to shoot the particle
void PrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

