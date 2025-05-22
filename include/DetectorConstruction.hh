#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction(G4int nofLayers);
    virtual ~DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();

private:
    int fNLayers;
    double fScintThickness;
    double fTungThickness;
};

#endif
