#ifndef ORIGINOFPARTICLE_HH
#define ORIGINOFPARTICLE_HH

#include "G4UserSteppingAction.hh"

class OriginOfParticle : public G4UserSteppingAction
{
public:
    OriginOfParticle();
    ~OriginOfParticle() override;

    virtual void UserSteppingAction(const G4Step *) override;

private:
};

#endif // EVENTACTION_HH
