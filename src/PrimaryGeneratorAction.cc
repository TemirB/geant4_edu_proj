#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction() {
    fParticleGun = new G4ParticleGun(1);
    auto table = G4ParticleTable::GetParticleTable();
    auto particle = table->FindParticle("e-");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleEnergy(10.0*GeV);
    fParticleGun->SetParticleMomentumDirection({0,0,1});
    fParticleGun->SetParticlePosition({0,0,-200*mm});
}
PrimaryGeneratorAction::~PrimaryGeneratorAction() { delete fParticleGun; }
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) { fParticleGun->GeneratePrimaryVertex(event); }
