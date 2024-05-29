/*
#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH
*/
#ifndef ACTINI_h
#define ACTINI_h 1

#include "G4VUserActionInitialization.hh"
#include "G4String.hh"

class ActionInitialization : public G4VUserActionInitialization
{
	public:
    	ActionInitialization();
    	virtual ~ActionInitialization();

    	virtual void BuildForMaster() const;
    	virtual void Build() const;
	private:
};

#endif
