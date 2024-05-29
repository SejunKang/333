#include "G4Event.hh"
#include "EventAction.hh"

#include <ctime>
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4RootAnalysisManager.hh"


EventAction::EventAction()
{
	m_NScint = 0;
	m_NCeren = 0;
}

EventAction::~EventAction()
{
}


void EventAction::BeginOfEventAction(const G4Event *)
{

	m_NScint = 0;
	m_NCeren = 0;
}

void EventAction::EndOfEventAction(const G4Event* anEvent)
{

	// Get event ID
//	G4int eventID = anEvent -> GetEventID();
	/*
    auto HCE = anEvent->GetHCofThisEvent();
    if (!HCE)
        return;
	*/

	// Get analysis manager
//	auto AM = G4RootAnalysisManager::Instance();

//	AM -> FillNtupleIColumn(0, eventID);
//	AM -> FillNtupleIColumn(1, m_NScint);
//	AM -> FillNtupleIColumn(2, m_NCeren);
//	AM -> AddNtupleRow();

}

void EventAction::AddScint()
{
	m_NScint++;
}

void EventAction::AddCeren()
{
	m_NCeren++;
}
