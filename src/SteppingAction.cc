#include "SteppingAction.hh"
#include "RunAction.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"

SteppingAction::SteppingAction(RunAction* runAction) : fRunAction(runAction) {}
SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    double edep = step->GetTotalEnergyDeposit();
    if(edep==0.) return;
    auto pos = step->GetPreStepPoint()->GetPosition();
    double r = std::sqrt(pos.x()*pos.x() + pos.y()*pos.y());
    fRunAction->FillRadial(r, edep);
}
