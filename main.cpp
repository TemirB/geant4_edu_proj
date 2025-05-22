#include "G4RunManagerFactory.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "FTFP_BERT.hh"
#include "SimpleDetectorConstruction.hh"
#include "ActionInitialization.hh"

int main(int argc, char** argv)
{
    int nLayers = 20;
    if (argc > 1) nLayers = atoi(argv[1]);
    double layerXY = 100.0; // mm
    double binSize = 2.0;   // mm — радиальный размер бина

    auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);
    runManager->SetUserInitialization(new SimpleDetectorConstruction(nLayers));
    runManager->SetUserInitialization(new FTFP_BERT);
    runManager->SetUserInitialization(new ActionInitialization(nLayers, layerXY, binSize));

    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UIExecutive* ui = nullptr;
    if (argc == 1) ui = new G4UIExecutive(argc, argv);

    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    if (!ui) {
        UImanager->ApplyCommand("/run/initialize");
        UImanager->ApplyCommand("/run/beamOn 1000");
    } else {
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    }

    delete visManager;
    delete runManager;
    return 0;
}
