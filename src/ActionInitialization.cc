#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization()
: G4VUserActionInitialization(), fNLayers(20) {}

ActionInitialization::ActionInitialization(int nLayers)
: G4VUserActionInitialization(), fNLayers(nLayers) {}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::Build() const {
    auto runAction = new RunAction(fNLayers);
    SetUserAction(runAction);
    SetUserAction(new PrimaryGeneratorAction());
    SetUserAction(new SteppingAction(runAction));
}
