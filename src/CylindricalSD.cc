#include "CylindricalSD.hh"
#include "G4MuonMinus.hh"
#include "G4JPsi.hh"

using namespace CLHEP;

G4bool CylindricalSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
    if (aStep->GetTrack()->GetParentID() == 0 && aStep->GetTrack()->GetParticleDefinition() == G4JPsi::Definition()) {
        if (flag1) {
            momentumAbs = aStep->GetPreStepPoint()->GetMomentum().mag() / GeV;
            momentumTheta = aStep->GetPreStepPoint()->GetMomentumDirection().theta() / degree;
            JpsiMP = momentumAbs * cos(momentumTheta);
            JpsiMT = momentumAbs * sin(momentumTheta);
            flag1 = false;
            arr[0] = true;
            std::cout<<"Jpsi"<<std::endl;
            std::cout<<aStep->GetTrack()->GetTrackID()<<std::endl;

        }
    }

    if (aStep->GetTrack()->GetParentID() == 0 && aStep->GetTrack()->GetParticleDefinition()->GetAntiPDGEncoding() == -13) {
        std::cout<<aStep->GetTrack()->GetVolume()->GetName()<<std::endl;
        if (flag2 && aStep->GetTrack()->GetVolume()->GetName() == "cylinder") {
            auto momentum = aStep->GetPreStepPoint()->GetMomentum().mag() / GeV;
            auto theta = aStep->GetPreStepPoint()->GetMomentumDirection().theta() / degree;
            MuMinusMPB = momentum * cos(theta);
            MuMinusMTB = momentum * sin(theta);
            cosThetaMMT = cos(theta);
            flag2 = false;
            arr[1] = true;
        }

        if (aStep->IsLastStepInVolume() == 1 && aStep->GetTrack()->GetNextVolume()->GetName() == "World"){
            auto momentum = aStep->GetTrack()->GetMomentum().mag() / GeV;
            auto theta = aStep->GetTrack()->GetMomentumDirection().theta() / degree;
            MuMinusMPA = momentum * cos(theta);
            MuMinusMTA = momentum * sin(theta);
            cosThetaMMG = cos(theta);
            arr[2] = true;
        }
    }

    if (aStep->GetTrack()->GetParentID() == 0 && aStep->GetTrack()->GetParticleDefinition()->GetAntiPDGEncoding() == 13) {
        std::cout<<aStep->GetTrack()->GetVolume()->GetName()<<std::endl;
        if (flag3 && aStep->GetTrack()->GetVolume()->GetName() == "cylinder"){
            auto momentum = aStep->GetPreStepPoint()->GetMomentum().mag() / GeV;
            auto theta = aStep->GetPreStepPoint()->GetMomentumDirection().theta() / degree;
            MuPlusMPB = momentum * cos(theta);
            MuPlusMTB = momentum * sin(theta);
            cosThetaMPT = cos(theta);
            next[0] = MuPlusMPB;
            next[1] = MuPlusMTB;
            next[2] = cosThetaMPT;
            std::cout<<MuPlusMPB<<std::endl;
            flag3 = false;
            arr[3] = true;
            numberAnti++;
            std::cout<<"antibro"<<std::endl;
            /*std::cout<<aStep->GetTrack()->GetTrackID()<<std::endl;
            std::cout<<cosThetaMPT<<std::endl;*/
        }

        if (flag3 && aStep->GetTrack()->GetVolume()->GetName() == "cylinder_with_hole"){
            MuPlusMPB = next[0];
            MuPlusMTB = next[1];
            cosThetaMPT = next[2];
            std::cout<<MuPlusMPB<<std::endl;
            flag3 = false;
            arr[3] = true;
            numberAnti++;
            std::cout<<"antibro12"<<std::endl;
            /*std::cout<<aStep->GetTrack()->GetTrackID()<<std::endl;
            std::cout<<cosThetaMPT<<std::endl;*/
        }

        if (aStep->IsLastStepInVolume() == 1 && aStep->GetTrack()->GetNextVolume()->GetName() == "World"){
            auto momentum = aStep->GetTrack()->GetMomentum().mag() / GeV;
            auto theta = aStep->GetTrack()->GetMomentumDirection().theta() / radian;
            MuPlusMPA = momentum * cos(theta);
            MuPlusMTA = momentum * sin(theta);
            cosThetaMPG = cos(theta);
            arr[4] = true;
        }
    }

    return false;
}

CylindricalSD::~CylindricalSD() = default;

void CylindricalSD::Initialize(G4HCofThisEvent *event) {
    G4VSensitiveDetector::Initialize(event);
    std::cout<<"reborn"<<std::endl;
    MuPlusMTB = 0;
    MuPlusMPB = 0;
    MuPlusMTA = 0;
    MuPlusMPA = 0;
    MuMinusMTB = 0;
    MuMinusMPB = 0;
    MuMinusMTA = 0;
    MuMinusMPA = 0;
    cosThetaMMT = 0;
    cosThetaMMG = 0;
    cosThetaMPT = 0;
    cosThetaMPG = 0;
    JpsiMT = 0;
    JpsiMP = 0;
    flag1 = true;
    flag2 = true;
    flag3 = true;
    for (bool & j : arr) {
        j = false;
    }
}

void CylindricalSD::EndOfEvent(G4HCofThisEvent *event) {
    G4VSensitiveDetector::EndOfEvent(event);
    auto analysisManager = tupleId->analysisManager;
    if (arr[0]) {
        //std::cout<<"Here0 "<<arr[1]<<arr[2]<<std::endl;
        analysisManager->FillNtupleDColumn(tupleId->JpsiId, 0, JpsiMT);
        analysisManager->FillNtupleDColumn(tupleId->JpsiId, 1, JpsiMP);
        analysisManager->AddNtupleRow(tupleId->JpsiId);
        arr[0] = false;
    }
  /*  if (arr[3]) {
        analysisManager->FillNtupleDColumn(tupleId->MuPlusId, 0, MuPlusMTB);
        analysisManager->FillNtupleDColumn(tupleId->MuPlusId, 1, MuPlusMPB);
        arr[3] = false;

    }*/
    if (arr[4]){
        //std::cout<<"Here1 "<<arr[2]<<std::endl;
        analysisManager->FillNtupleDColumn(tupleId->MuPlusId, 0, MuPlusMTB);
        analysisManager->FillNtupleDColumn(tupleId->MuPlusId, 1, MuPlusMPB);
        analysisManager->FillNtupleDColumn(tupleId->MuPlusId, 2, MuPlusMTA);
        analysisManager->FillNtupleDColumn(tupleId->MuPlusId, 3, MuPlusMPA);
        analysisManager->AddNtupleRow(tupleId->MuPlusId);
        analysisManager->FillNtupleDColumn(tupleId->MuonPCosTargetId, 0, cosThetaMPT);
        analysisManager->FillNtupleDColumn(tupleId->MuonPCosTargetId, 1, numberAnti);
        analysisManager->FillNtupleDColumn(tupleId->MuonPCosGenId, 0, cosThetaMPG);
        analysisManager->FillNtupleDColumn(tupleId->MuonPCosGenId, 1, numberAnti);
        analysisManager->AddNtupleRow(tupleId->MuonPCosGenId);
        analysisManager->AddNtupleRow(tupleId->MuonPCosTargetId);
        if (cosThetaMPT == 0){
            std::cout<<"zero1"<<std::endl;
        }
        }
        for (int j = 0; j < 13; ++j) {
            if (cosThetaMPT < cos(j * 10 * degree) && cosThetaMPT > cos((j+1) * 10 * degree)){
                analysisManager->FillH1(tupleId->histId[j], sqrt(pow(MuPlusMTB, 2)+pow(MuPlusMPB, 2)));
                }
            }

        for (int j = 0; j < 13; ++j) {
            if (cosThetaMPG < cos(j * 10 * degree) && cosThetaMPG > cos((j+1) * 10 * degree)){
                analysisManager->FillH1(tupleId->histId1[j], sqrt(pow(MuPlusMTA, 2)+pow(MuPlusMPA, 2)));
            }

        arr[4] = false;
            }
    /*if (arr[1]) {
        analysisManager->FillNtupleDColumn(tupleId->MuMinusId, 0, MuMinusMTB);
        analysisManager->FillNtupleDColumn(tupleId->MuMinusId, 1, MuMinusMPB);
        arr[1] = false;
    }*/
    if (arr[2]){
        //std::cout<<"Here2 "<<arr[4]<<std::endl;
        analysisManager->FillNtupleDColumn(tupleId->MuMinusId, 0, MuMinusMTB);
        analysisManager->FillNtupleDColumn(tupleId->MuMinusId, 1, MuMinusMPB);
        analysisManager->FillNtupleDColumn(tupleId->MuMinusId, 2, MuMinusMTA);
        analysisManager->FillNtupleDColumn(tupleId->MuMinusId, 3, MuMinusMPA);
        if (cosThetaMMT == 0){
            std::cout<<"zero"<<std::endl;
        }
        analysisManager->FillNtupleDColumn(tupleId->MuonMCosTargetId, 0, cosThetaMMT);
        analysisManager->FillNtupleDColumn(tupleId->MuonMCosTargetId, 1, number);
        analysisManager->FillNtupleDColumn(tupleId->MuonMCosGenId, 0, cosThetaMMG);
        analysisManager->FillNtupleDColumn(tupleId->MuonMCosGenId, 1, number);
        analysisManager->AddNtupleRow(tupleId->MuonMCosGenId);
        analysisManager->AddNtupleRow(tupleId->MuonMCosTargetId);

        analysisManager->AddNtupleRow(tupleId->MuMinusId);

        arr[2] = false;
    }

}