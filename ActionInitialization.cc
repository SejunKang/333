#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "OriginOfParticle.hh"

ActionInitialization::ActionInitialization()
    : G4VUserActionInitialization()
{
}

ActionInitialization::~ActionInitialization()
{
}

void ActionInitialization::BuildForMaster() const
{
    SetUserAction(new RunAction());
}

void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction());

    SetUserAction(new RunAction());
    // SetUserAction(new EventAction); ?꾨옒???댁슜?쇰줈 ?섏젙??5.22)
	
	EventAction* EA = new EventAction();
	SetUserAction(EA);

	SetUserAction(new SteppingAction(EA)); // 5.22 異붽?

    //SetUserAction(new OriginOfParticle); 
}
