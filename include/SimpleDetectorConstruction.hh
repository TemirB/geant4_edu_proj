#pragma once
#include <G4VUserDetectorConstruction.hh>
#include <G4Material.hh>

class SimpleDetectorConstruction : public G4VUserDetectorConstruction {
public:
    SimpleDetectorConstruction(int nLayers);
    virtual ~SimpleDetectorConstruction() = default;
    virtual G4VPhysicalVolume* Construct();
    int GetNLayers() const { return fNLayers; }
    double GetLayerXY() const { return fLayerXY; }
private:
    int fNLayers;
    G4Material* fScintillator;
    G4Material* fTungsten;
    void DefineMaterials();
    double fLayerXY = 100.; // mm (размер по X и Y)
};
