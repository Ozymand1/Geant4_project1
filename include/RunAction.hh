#include <G4UserRunAction.hh>
#include "TTree.h"
#include "TFile.h"

class RunAction : public G4UserRunAction{
public:
    explicit RunAction();
    void BeginOfRunAction(const G4Run* aRun) override;
    void EndOfRunAction(const G4Run* aRun) override;

private:
    double_t energy;
    TTree* Angle45;
    TTree* Angle90;
    TTree* Angle135;
    TFile* outFile;
};
