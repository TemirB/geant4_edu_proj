#pragma once
#include <G4UserEventAction.hh>
#include <vector>
#include <fstream>

class EventAction : public G4UserEventAction {
public:
    EventAction(int nLayers, double layerXY, double binSize);
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event*) override;
    virtual void EndOfEventAction(const G4Event*) override;

    void AddEdep(int layer, double x, double y, double edep);

private:
    int fNLayers;
    double fLayerXY;
    double fBinSize;
    std::vector<double> fLayerEdeps;
    std::vector<std::vector<double>> fRadialEdepBins;
    std::ofstream fOutLayer, fOutRadial;
    int fNBins;

    void WriteLayerEdeps();
    void WriteRadialProfile();
};
