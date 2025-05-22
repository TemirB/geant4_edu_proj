#include "DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"

DetectorConstruction::DetectorConstruction(G4int nofLayers)
    : G4VUserDetectorConstruction(),
      fNLayers(nofLayers),
      fScintThickness(1.0*mm),
      fTungThickness(3.5*mm)
{}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();

    G4Material* worldMat = nist->FindOrBuildMaterial("G4_Galactic");
    G4Material* scintMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    G4Material* tungMat = nist->FindOrBuildMaterial("G4_W");

    double worldXY = 500.0*mm;
    double depth = fNLayers * (fScintThickness + fTungThickness);
    double worldZ = depth + 100*mm;
    G4bool checkOverlaps = true;

    auto solidWorld = new G4Box("World", worldXY/2, worldXY/2, worldZ/2);
    auto logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
    auto physWorld = new G4PVPlacement(0, G4ThreeVector{}, logicWorld, "World", 0, false, 0, checkOverlaps);
    
    double z0 = -depth/2 + fScintThickness/2;
    double z = z0;
    // Построение секционного калориметра
    for(int i=0; i<fNLayers; ++i) {
        // Сцинтиллятор
        auto solidS = new G4Box("Scint", worldXY/2, worldXY/2, fScintThickness/2);
        auto logicS = new G4LogicalVolume(solidS, scintMat, "ScintLV");
        new G4PVPlacement(0, {0,0,z}, logicS, "Scintillator", logicWorld, false, i);
        z += fScintThickness/2 + fTungThickness/2;
        // Вольфрам
        auto solidT = new G4Box("Tung", worldXY/2, worldXY/2, fTungThickness/2);
        auto logicT = new G4LogicalVolume(solidT, tungMat, "TungLV");
        new G4PVPlacement(0, {0,0,z}, logicT, "Tungsten", logicWorld, false, i);
        z += fTungThickness/2 + fScintThickness/2;
    }
    return physWorld;
}
