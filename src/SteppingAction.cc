#include "SteppingAction.hh"
#include <G4Step.hh>
#include <G4VPhysicalVolume.hh>
#include <G4TouchableHistory.hh>
#include <G4LogicalVolume.hh>
#include <G4SystemOfUnits.hh>

SteppingAction::SteppingAction(EventAction* evt, int nLayers, double layerXY)
    : fEventAction(evt), fNLayers(nLayers), fLayerXY(layerXY) {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    auto edep = step->GetTotalEnergyDeposit();
    if (edep <= 0) return;

    auto touch = step->GetPreStepPoint()->GetTouchable();
    auto volName = touch->GetVolume()->GetName();
    if (volName == "SCLV") {
        int layer = touch->GetCopyNumber();
        auto pos = step->GetPreStepPoint()->GetPosition();
        fEventAction->AddEdep(layer, pos.x()/mm, pos.y()/mm, edep);
    }
}
