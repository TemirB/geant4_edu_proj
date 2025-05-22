#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization(int nLayers, double layerXY, double binSize)
    : fNLayers(nLayers), fLayerXY(layerXY), fBinSize(binSize) {}

void ActionInitialization::Build() const {
    SetUserAction(new PrimaryGeneratorAction());
    auto eventAction = new EventAction(fNLayers, fLayerXY, fBinSize);
    SetUserAction(eventAction);
    SetUserAction(new SteppingAction(eventAction, fNLayers, fLayerXY));
}
