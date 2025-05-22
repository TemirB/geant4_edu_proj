#include "PrimaryGeneratorAction.hh"
#include <G4ParticleTable.hh>
#include <G4ParticleDefinition.hh>
#include <G4SystemOfUnits.hh>
#include <G4ThreeVector.hh>
#include <G4Event.hh>

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("e-");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(10.0 * GeV);
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -95.0 * mm));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() { delete fParticleGun; }

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
