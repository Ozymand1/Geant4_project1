#include "CylindricalSD.hh"
#include "G4MuonMinus.hh"
using namespace CLHEP;

G4bool CylindricalSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
    if (aStep->GetTrack()->GetParentID() == 0 && aStep->GetTrack()->GetDefinition() == G4MuonMinus::Definition()){
       if (aStep->IsLastStepInVolume()){
           auto particle = aStep->GetTrack()->GetDynamicParticle();
           auto momentum = particle->GetMomentumDirection();
           auto theta = momentum.theta() / radian;
           if (theta >= 0.698132 && theta <= 0.872665){
               angular[0] = 1;
           }
           if (theta >= 1.48353 && theta <= 1.65806){
               angular[1] = 1;
           }
           if (theta >= 2.26893 && theta <= 2.44346){
               angular[2] = 1;
           }
       }
    energy += aStep->GetTotalEnergyDeposit();
    }
    return 0;
}

CylindricalSD::~CylindricalSD() = default;

void CylindricalSD::Initialize(G4HCofThisEvent *event) {
    G4VSensitiveDetector::Initialize(event);
    energy = 0;
    for (int i = 0; i < 3; ++i) {
        angular[i] = 0;

    }
}

void CylindricalSD::EndOfEvent(G4HCofThisEvent *event) {
    G4VSensitiveDetector::EndOfEvent(event);


    auto analysisManager = tupleId->analysisManager;

    if (angular[0] == 1){
        analysisManager->FillNtupleDColumn(tupleId->FortyFiveId, 0, 1 - 0.001 * energy);
        analysisManager->AddNtupleRow(tupleId->FortyFiveId);
    }

    if (angular[1] == 1){
        analysisManager->FillNtupleDColumn(tupleId->NinetyId, 0, 1 - 0.001 * energy);
        analysisManager->AddNtupleRow(tupleId->NinetyId);
    }

    if (angular[2] == 1){
        analysisManager->FillNtupleDColumn(tupleId->HundredThirtyFiveId, 0, 1 - 0.001 * energy);
        analysisManager->AddNtupleRow(tupleId->HundredThirtyFiveId);
    }

}