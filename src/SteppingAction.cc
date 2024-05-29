#include "SteppingAction.hh"

#include "G4String.hh"
#include "G4VPhysicalVolume.hh"
#include "G4TrackStatus.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4RootAnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

SteppingAction::SteppingAction(EventAction* EA): G4UserSteppingAction(), m_EA(EA)
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{

	// Particle name
	G4String parName = step -> GetTrack() -> GetDefinition() -> GetParticleName();

	// Process name
	const G4VProcess* creProc = step -> GetTrack() -> GetCreatorProcess();

	G4String namePostPV;
	G4VPhysicalVolume* postPV = step -> GetPostStepPoint() -> GetPhysicalVolume();
	if ( postPV != 0 ) namePostPV = postPV -> GetName();
	else namePostPV = "outside";

	G4double postKinEgy = step -> GetPostStepPoint() -> GetKineticEnergy();

//	if ( namePostPV == "PMTPV" && parName == "opticalphoton" && creProc -> GetProcessName() == "Scintillation")
	if ( namePostPV == "PMTPV" && parName == "opticalphoton")
	{
		auto AM = G4RootAnalysisManager::Instance();
		AM -> FillNtupleIColumn(0, G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID());
		AM -> FillNtupleDColumn(1, postKinEgy / eV);
		AM -> AddNtupleRow();

		step -> GetTrack() -> SetTrackStatus(fStopAndKill);

	}

}
