#include "PrimaryGeneratorAction.hh"
#include "G4MuonMinus.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
	fPrimary = new G4ParticleGun(1);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fPrimary;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
//	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
//	G4String particleName = "proton";
//	G4ParticleDefinition *particle = particleTable->FindParticle("prton");
//	G4String particleName = "muon";
//	G4ParticleDefinition *particle = particleTable->FindParticle("muon");

	G4ThreeVector pos(0., 0., 0.);
	G4ThreeVector mom(0., 0., 1.);

	fPrimary->SetParticleDefinition(G4MuonMinus::Definition());
	fPrimary->SetParticlePosition(pos);
	fPrimary->SetParticleMomentumDirection(mom);
	fPrimary->SetParticleMomentum(5.*GeV);
//	fPrimary->SetParticleDefinition(particle);

	fPrimary->GeneratePrimaryVertex(anEvent);
}

