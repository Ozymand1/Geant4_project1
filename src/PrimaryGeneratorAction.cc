#include <G4MuonMinus.hh>
#include <G4DynamicParticle.hh>
#include "PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "TRandom.h"
#include <random>
#include "TF2.h"
#include "G4DynamicParticle.hh"
#include "G4JPsi.hh"

using namespace CLHEP;

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {

    JpsiY = 0;
    auto particleTable = G4ParticleTable::GetParticleTable();
    std::random_device rd;
    std::uniform_int_distribution<long> uid(0, LONG_MAX);
    long seed = uid(rd);
    auto random = new TRandom;
    random->SetSeed(seed);
    auto func2 = new TF1("func2", "exp(-4002.11 * x)", 0, 0.002);
    auto func1 = new TF2("func1", "7.7*10^(-11)*(4 - x^2)^13 * e^(-2*y^2 / (4 - x^2)^2)", -1, 1, 0, 10);
    func1->GetRandom2(Ppar, Pperp);
    Ppar = Ppar * Pmax;
    Ppar1 = Ppar * Pmax;
    while (pow(Ppar, 2) + pow(Pperp, 2) > Pmax * Pmax){
        func1->GetRandom2(Ppar1, Pperp);
    }
    JpsiEnergy = sqrt(pow(Pperp, 2) + pow(Ppar, 2) + pow(JpsiMass, 2));
    Beta = sqrt(1 - 1 / pow(GammaCMS, 2));

    Ppar = GammaCMS * (Ppar + JpsiEnergy * Beta);
    JpsiMomentum = sqrt(pow(Ppar, 2) + pow(Pperp, 2));
    
    MuonMomentum = sqrt(pow(JpsiMass / 2, 2) - pow(MuonMass, 2));
    random->Sphere(x, y, z, MuonMomentum);
    random->Circle(JpsiX, JpsiY, Pperp);


    z4 = func2->GetRandom();
    fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, z4 * cm));
    fParticleGun->SetParticleDefinition(G4JPsi::Definition());
    fParticleGun->SetParticleMomentum(JpsiMomentum * GeV);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(JpsiX / JpsiMomentum, JpsiY / JpsiMomentum, Ppar / JpsiMomentum));
    fParticleGun->GeneratePrimaryVertex(anEvent);

    auto vector2 = new G4ThreeVector (JpsiX, JpsiY, Ppar);
    double gamma0 = sqrt(1 + pow(JpsiMomentum / JpsiMass, 2));
    z1 = gamma0 * (z + sqrt(1 - 1 /pow(gamma0, 2)) * JpsiMass / 2);
    auto vector1 = new G4ThreeVector(x, y, z1);
    vector1->rotateY(-vector2->theta());
    vector1->rotateZ(-vector2->phi());
    x3 = vector1->x();
    y3 = vector1->y();
    z3 = vector1->z();
    auto particle = particleTable->FindParticle(13);
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentum(vector1->r() * GeV);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x3, y3, z3));

    fParticleGun->GeneratePrimaryVertex(anEvent);

    z2 = gamma0 * (-z + sqrt(1 - 1 /pow(gamma0, 2)) * JpsiMass / 2);
    auto vector3 = new G4ThreeVector(-x, -y, z2);
    vector3->rotateY(-vector2->theta());
    vector3->rotateZ(-vector2->phi());
    particle = particleTable->FindParticle(-13);
    x3 = vector3->x();
    y3 = vector3->y();
    z3 = vector3->z();
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentum(vector3->r() * GeV);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x3, y3, z3));
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);
}