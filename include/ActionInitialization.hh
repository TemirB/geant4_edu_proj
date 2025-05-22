#pragma once
#include <G4VUserActionInitialization.hh>

class ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization(int nLayers, double layerXY, double binSize);
    virtual ~ActionInitialization() = default;
    virtual void Build() const override;
private:
    int fNLayers;
    double fLayerXY;
    double fBinSize;
};
