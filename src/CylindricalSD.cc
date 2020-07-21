#include "CylindricalSD.hh"
#include "G4MuonMinus.hh"
using namespace CLHEP;

G4bool CylindricalSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
    if (aStep->GetTrack()->GetParentID() == 0){
        if (aStep->IsFirstStepInVolume()) {
            z = aStep->GetTrack()->GetPosition().z() / cm;
            std::cout<<"# "<< i << std::endl;
            i++;
        }
    }
    return 0;
}

CylindricalSD::~CylindricalSD() = default;

void CylindricalSD::Initialize(G4HCofThisEvent *event) {
    G4VSensitiveDetector::Initialize(event);
    z = 0;
    energy = 0;
    for (int & i : angular) {
        i = 0;

    }
}

void CylindricalSD::EndOfEvent(G4HCofThisEvent *event) {
    G4VSensitiveDetector::EndOfEvent(event);
    auto analysisManager = tupleId->analysisManager;
    analysisManager->FillNtupleDColumn(tupleId->PosId, 0, z);
    analysisManager->AddNtupleRow(tupleId->PosId);

    /*auto analysisManager = tupleId->analysisManager;

    if (angular[0] == 1){
        analysisManager->FillNtupleDColumn(tupleId->FortyFiveId, 0, energy);
        analysisManager->AddNtupleRow(tupleId->FortyFiveId);
    }

    if (angular[1] == 1){
        analysisManager->FillNtupleDColumn(tupleId->NinetyId, 0, energy);
        analysisManager->AddNtupleRow(tupleId->NinetyId);
    }

    if (angular[2] == 1){
        analysisManager->FillNtupleDColumn(tupleId->HundredThirtyFiveId, 0, energy);
        analysisManager->AddNtupleRow(tupleId->HundredThirtyFiveId);
    }*/

}