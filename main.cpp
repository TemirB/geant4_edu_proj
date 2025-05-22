#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4SteppingVerbose.hh"
#include "FTFP_BERT.hh"

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

int main(int argc, char** argv) {
    // [1] Создаем и парсим основные парамметры
    G4bool verboseBestUnits = true;
    if (verboseBestUnits) {
        G4int precision = 4;
        G4SteppingVerbose::UseBestUnit(precision);
    }

    int nofLayers = 20;
    G4bool useVisualization = true;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-novis") {
            useVisualization = false;
        } else {
            nofLayers = std::atoi(argv[i]);
            std::cout << "[INFO] Set nofLayers " << argv[i] << std::endl;
        }
    }

    std::cout << "[INFO] Using " << nofLayers << " layers." << std::endl;

    // [2] Создание и иннициализация runManager
    auto* runManager = G4RunManagerFactory::CreateRunManager();
    runManager->SetUserInitialization(new DetectorConstruction(nofLayers));
    runManager->SetUserInitialization(new FTFP_BERT());
    runManager->SetUserInitialization(new ActionInitialization());

    runManager->Initialize();

    // [3] Визуализация
    G4UImanager::GetUIpointer()->ApplyCommand("/tracking/verbose 0");

    if (useVisualization) {
        auto visManager = new G4VisExecutive;
        visManager->Initialize();

        auto ui = new G4UIExecutive(argc, argv);
        G4UImanager::GetUIpointer()->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();

        delete ui;
        delete visManager;
    } else {
        runManager->BeamOn(100);
    }

    delete runManager;
    return 0;
}
