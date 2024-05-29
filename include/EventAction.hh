/*
#ifndef EVENTACTION_HH
#define EVENTACTION_HH
*/

#ifndef EVEACT_h
#define EVEACT_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
//#include "G4SDManager.hh"

class G4Event;

class EventAction : public G4UserEventAction
{
public:
    EventAction();
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event *);
    virtual void EndOfEventAction(const G4Event *);


	void AddScint();
	void AddCeren();

private:
	G4int m_NScint;
	G4int m_NCeren;
	G4int fHCID;
};

#endif // EVENTACTION_HH
