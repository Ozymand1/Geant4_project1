#include <G4VSensitiveDetector.hh>
//#include "DetectorConstruction.hh"
#include "g4analysis.hh"
#include "TupleId.hh"
class TTree;

class CylindricalSD : public G4VSensitiveDetector{
public:
    explicit CylindricalSD(std::string name, TupleId* tupleId) : G4VSensitiveDetector(name), tupleId(tupleId){

    };
    G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override;

    ~CylindricalSD() override;

    void Initialize(G4HCofThisEvent *event) override;

    void EndOfEvent(G4HCofThisEvent *event) override;

private:
    int angular[3] = {0, 0, 0};
    double energy;
    double z;
    long i = 1;
    TupleId* tupleId;
};