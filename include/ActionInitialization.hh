#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization();
    ActionInitialization(int);
    virtual ~ActionInitialization();
    virtual void Build() const override;
private:
    int fNLayers = 20;
};

#endif
