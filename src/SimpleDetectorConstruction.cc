#include "SimpleDetectorConstruction.hh"
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4SystemOfUnits.hh>

SimpleDetectorConstruction::SimpleDetectorConstruction(int nLayers)
    : G4VUserDetectorConstruction(), fNLayers(nLayers) {}

void SimpleDetectorConstruction::DefineMaterials() {
    auto nist = G4NistManager::Instance();
    fScintillator = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    fTungsten = nist->FindOrBuildMaterial("G4_W");
}

G4VPhysicalVolume* SimpleDetectorConstruction::Construct() {
    DefineMaterials();

    double layerXY = 100*mm;
    double scintThick = 1*mm;
    double wThick = 3.5*mm;
    double totalThick = fNLayers * (scintThick + wThick);

    auto worldS = new G4Box("World", layerXY, layerXY, totalThick);
    auto worldLV = new G4LogicalVolume(worldS, G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR"), "World");
    auto worldPV = new G4PVPlacement(nullptr, {}, worldLV, "World", nullptr, false, 0);

    double z = -totalThick + (scintThick + wThick) / 2;
    for (int i = 0; i < fNLayers; ++i) {
        auto wS = new G4Box("W", layerXY, layerXY, wThick/2);
        auto wLV = new G4LogicalVolume(wS, fTungsten, "WLV");
        new G4PVPlacement(nullptr, G4ThreeVector(0,0,z), wLV, "W", worldLV, false, i);

        z += wThick/2 + scintThick/2;
        auto scS = new G4Box("SC", layerXY, layerXY, scintThick/2);
        auto scLV = new G4LogicalVolume(scS, fScintillator, "SCLV");
        new G4PVPlacement(nullptr, G4ThreeVector(0,0,z), scLV, "SC", worldLV, false, i);

        z += scintThick/2 + wThick/2;
    }
    return worldPV;
}
