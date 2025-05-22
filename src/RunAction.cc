#include "RunAction.hh"
#include <fstream>
#include <algorithm>
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

RunAction::RunAction()
: G4UserRunAction(), fNBins(1000), fBinWidth(0.2*mm), fNLayers(20)
{ fRadialE.assign(fNBins, 0.0); }

RunAction::RunAction(int nLayers)
: G4UserRunAction(), fNBins(1000), fBinWidth(0.2*mm), fNLayers(nLayers)
{ fRadialE.assign(fNBins, 0.0); }

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run*) { std::fill(fRadialE.begin(), fRadialE.end(), 0.0); }

void RunAction::FillRadial(double r, double edep) {
    int bin = int(r/fBinWidth);
    if (bin >=0 && bin < fNBins) fRadialE[bin] += edep;
}

void RunAction::EndOfRunAction(const G4Run*) {
    double totalE = 0;
    for (auto e : fRadialE) totalE += e;
    if (totalE <= 0) return;
    double thr = 0.9*totalE; // порог
    double currentE = 0, r90 = 0; // currentE, r90 - текущая энергия и итоговый радиус
    for(size_t i=0; i<fRadialE.size(); ++i) {
        currentE += fRadialE[i];
        if(currentE >= thr) {
            r90 = (i+0.5)*fBinWidth;
            break;
        }
    }
    std::string name = "results/rm_vs_layers_" + std::to_string(fNLayers) + ".txt";
    std::ofstream out(name, std::ios::app);
    out << r90/mm << std::endl;
    out.close();
    G4cout << "Moliere radius (90% E): " << G4BestUnit(r90,"Length") << G4endl;
}
