#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include <G4GeneralParticleSource.hh>
#include "G4DecayTable.hh"
#include "G4DecayProducts.hh"
#include "G4IonTable.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    explicit PrimaryGeneratorAction();
    void GeneratePrimaries(G4Event *anEvent) override;

    ~PrimaryGeneratorAction() {
        delete fParticleGun;
    }
    double x = 0, y = 0, z = 0, z1 = 0, z2 = 0;
    double x3, y3, z3;
    double z4;
    double Pmax = 0.664;
    double GammaCMS = 1.621;
    double Ppar = 0;
    double Pperp = 0;
    double JpsiMass = 3.097;
    double JpsiEnergy = 0;
    double Beta = 0;
    double JpsiMomentum = 0;
    double MuonMomentum = 0;
    double MuonMass = 0.105;
    double JpsiX = 0;
    double JpsiY = 0;
private:
    G4ParticleGun* fParticleGun;
};