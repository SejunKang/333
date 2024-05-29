#include <iostream>

#include "OriginOfParticle.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"


OriginOfParticle::OriginOfParticle()
{
}

OriginOfParticle::~OriginOfParticle()
{
}

void OriginOfParticle::UserSteppingAction(const G4Step* step)
{
	if ( step -> GetTrack() -> GetTrackID() != 1 )
	{
	std::cout
		<< "Particle: "
		<< step -> GetTrack() -> GetParticleDefinition() -> GetParticleName()
		<< "  From: "

		<<step -> GetTrack() -> GetCreatorProcess() -> GetProcessName() 
		<< std::endl;
	}
}
