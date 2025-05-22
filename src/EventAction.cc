#include "EventAction.hh"
#include <G4Event.hh>
#include <G4SystemOfUnits.hh>
#include <cmath>
#include <iostream>

EventAction::EventAction(int nLayers, double layerXY, double binSize)
    : fNLayers(nLayers), fLayerXY(layerXY), fBinSize(binSize)
{
    fLayerEdeps.resize(fNLayers, 0.0);

    // Радиальная разбивка (0...layerXY)
    fNBins = static_cast<int>(fLayerXY / fBinSize);
    fRadialEdepBins.resize(fNLayers, std::vector<double>(fNBins, 0.0));

    fOutLayer.open("layer_energy.csv");
    fOutRadial.open("radial_profile.csv");
}

EventAction::~EventAction() {
    if (fOutLayer.is_open()) fOutLayer.close();
    if (fOutRadial.is_open()) fOutRadial.close();
}

void EventAction::BeginOfEventAction(const G4Event*) {
    std::fill(fLayerEdeps.begin(), fLayerEdeps.end(), 0.0);
    for (auto& v : fRadialEdepBins) std::fill(v.begin(), v.end(), 0.0);
}

void EventAction::EndOfEventAction(const G4Event*) {
    WriteLayerEdeps();
    WriteRadialProfile();
}

void EventAction::AddEdep(int layer, double x, double y, double edep) {
    if (layer < 0 || layer >= fNLayers) return;
    fLayerEdeps[layer] += edep;

    // Радиальный бин
    double r = std::sqrt(x*x + y*y);
    int bin = static_cast<int>(r / fBinSize);
    if (bin >= 0 && bin < fNBins) {
        fRadialEdepBins[layer][bin] += edep;
    }
}

// Пишет энергию по слоям для каждого события
void EventAction::WriteLayerEdeps() {
    for (int i = 0; i < fNLayers; ++i) {
        fOutLayer << fLayerEdeps[i] / MeV << (i+1 < fNLayers ? "," : "\n");
    }
}

// Пишет радиальные профили для каждого слоя и события
void EventAction::WriteRadialProfile() {
    for (int i = 0; i < fNLayers; ++i) {
        for (int b = 0; b < fNBins; ++b) {
            fOutRadial << fRadialEdepBins[i][b] / MeV;
            if (b+1 < fNBins) fOutRadial << ",";
        }
        fOutRadial << "\n";
    }
}
