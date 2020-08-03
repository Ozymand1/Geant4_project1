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
    bool flag1 = true;
    bool flag2 = true;
    bool flag3 = true;
    TupleId* tupleId;
    double MuPlusMTB = 0;
    double MuPlusMPB = 0;
    double MuPlusMTA = 0;
    double MuPlusMPA = 0;
    double MuMinusMTB = 0;
    double MuMinusMPB = 0;
    double MuMinusMTA = 0;
    double MuMinusMPA = 0;
    double JpsiMT = 0;
    double JpsiMP = 0;
    double momentumAbs = 0;
    double momentumTheta = 0;
    bool arr[5] = {false, false, false, false, false};
    long i = 0, k = 0;
};