#include <DetectorConstruction.hh>
#include "RunAction.hh"
#include "TH1D.h"
#include "TTree.h"
#include "TFile.h"

using namespace CLHEP;

void RunAction::BeginOfRunAction(const G4Run *aRun) {
    G4UserRunAction::BeginOfRunAction(aRun);
    Angle45 = new TTree("Angle 45", "Angle 45");
    Angle45->Branch("angle 45", &energy, "energy/D");

    Angle90 = new TTree("Angle 90", "Angle 90");
    Angle90->Branch("angle 90", &energy, "energy/D");

    Angle135 = new TTree("Angle 135", "Angle 135");
    Angle135->Branch("angle 135", &energy, "energy/D");

    outFile = new TFile("500MeVRun.root", "RECREATE");
}
void RunAction::EndOfRunAction(const G4Run *aRun) {
    G4UserRunAction::EndOfRunAction(aRun);
    Angle45->Write();
    Angle90->Write();
    Angle135->Write();
    delete outFile;
}
RunAction::RunAction() {

}