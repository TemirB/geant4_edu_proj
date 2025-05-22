#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include <vector>

class RunAction : public G4UserRunAction {
public:
    RunAction();
    virtual ~RunAction();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
    void FillRadial(double r, double edep);
private:
    std::vector<double> fRadialE;
    int fNBins;
    double fBinWidth;
};

#endif
