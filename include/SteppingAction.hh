#pragma once
#include <G4UserSteppingAction.hh>
#include "EventAction.hh"

class SteppingAction : public G4UserSteppingAction {
public:
    SteppingAction(EventAction* evt, int nLayers, double layerXY);
    virtual ~SteppingAction() = default;
    virtual void UserSteppingAction(const G4Step*) override;
private:
    EventAction* fEventAction;
    int fNLayers;
    double fLayerXY;
};
