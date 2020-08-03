#include "CylindricalSD.hh"
#include "G4MuonMinus.hh"
#include "G4JPsi.hh"

using namespace CLHEP;

G4bool CylindricalSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
    if (aStep->GetTrack()->GetParentID() == 0 && aStep->GetTrack()->GetParticleDefinition() == G4JPsi::Definition()){
        if (flag1) {
            momentumAbs = aStep->GetPreStepPoint()->GetMomentum().mag() / GeV;
            momentumTheta = aStep->GetPreStepPoint()->GetMomentumDirection().theta() / radian;

            JpsiMP = momentumAbs * cos(momentumTheta);
            JpsiMT = momentumAbs * sin(momentumTheta);
            if (aStep->GetPreStepPoint()->GetMomentumDirection().y() < 0) {
                JpsiMT = -1 * JpsiMT;
            }
            flag1 = false;
            arr[0] = true;
        }
    }

    if (aStep->GetTrack()->GetParentID() == 0 && aStep->GetTrack()->GetParticleDefinition() == G4MuonMinus::Definition()){
        if (flag2) {
            momentumAbs = aStep->GetPreStepPoint()->GetMomentum().mag() / GeV;
            momentumTheta = aStep->GetPreStepPoint()->GetMomentumDirection().theta() / radian;

            MuMinusMPB = momentumAbs * cos(momentumTheta);
            MuMinusMTB = momentumAbs * sin(momentumTheta);
            if (aStep->GetPreStepPoint()->GetMomentumDirection().y() < 0) {
                MuMinusMTB = -1 * MuMinusMTB;
            }

            momentumAbs = aStep->GetPostStepPoint()->GetMomentum().mag() / GeV;
            momentumTheta = aStep->GetPostStepPoint()->GetMomentumDirection().theta() / radian;

            MuMinusMPA = momentumAbs * cos(momentumTheta);
            MuMinusMTA = momentumAbs * sin(momentumTheta);
            if (aStep->GetPreStepPoint()->GetMomentumDirection().y() < 0) {
                MuMinusMTA = -1 * MuMinusMTA;
            }
            flag2 = false;

        }

        if (aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "cylinder" &&
            aStep->GetTrack()->GetPosition().z() > 0)
        {
            arr[3] = true;
            arr[4] = false;
        }

        if (aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "cylinder_with_hole"&&
            aStep->GetTrack()->GetPosition().z() < 0)
        {
            arr[4] = true;
            arr[3] = false;
        }

    }

    if (aStep->GetTrack()->GetParentID() == 0 && aStep->GetTrack()->GetParticleDefinition()->GetAntiPDGEncoding() == 13){

        if (flag3) {
            momentumAbs = aStep->GetPreStepPoint()->GetMomentum().mag() / GeV;
            momentumTheta = aStep->GetPreStepPoint()->GetMomentumDirection().theta() / radian;

            MuPlusMPB = momentumAbs * cos(momentumTheta);
            MuPlusMTB = momentumAbs * sin(momentumTheta);
            if (aStep->GetPreStepPoint()->GetMomentumDirection().y() < 0) {
                MuPlusMTB = -1 * MuPlusMTB;
            }

            momentumAbs = aStep->GetPostStepPoint()->GetMomentum().mag() / GeV;
            momentumTheta = aStep->GetPostStepPoint()->GetMomentumDirection().theta() / radian;

            MuPlusMPA = momentumAbs * cos(momentumTheta);
            MuPlusMTA = momentumAbs * sin(momentumTheta);

            if (aStep->GetPreStepPoint()->GetMomentumDirection().y() < 0) {
                MuPlusMTA = -1 * MuPlusMTA;
            }
            flag3 = false;
        }

        if (aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "cylinder" &&
            aStep->GetTrack()->GetPosition().z() > 0)
        {

            arr[1] = true;
            arr[2] = false;
        }

        if (aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "cylinder_with_hole" &&
            aStep->GetTrack()->GetPosition().z() < 0)
        {
            arr[2] = true;
            arr[1] = false;
        }
    }

    return 0;
}

CylindricalSD::~CylindricalSD() = default;

void CylindricalSD::Initialize(G4HCofThisEvent *event) {
    G4VSensitiveDetector::Initialize(event);
    MuPlusMTB = 0;
    MuPlusMPB = 0;
    MuPlusMTA = 0;
    MuPlusMPA = 0;
    MuMinusMTB = 0;
    MuMinusMPB = 0;
    MuMinusMTA = 0;
    MuMinusMPA = 0;
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
        analysisManager->FillNtupleDColumn(tupleId->JpsiId, 0, JpsiMT);
        analysisManager->FillNtupleDColumn(tupleId->JpsiId, 1, JpsiMP);
        analysisManager->AddNtupleRow(tupleId->JpsiId);
        arr[0] = false;
    }
    if (arr[1] or arr[2]) {
        analysisManager->FillNtupleDColumn(tupleId->MuPlusId, 0, MuPlusMTB);
        analysisManager->FillNtupleDColumn(tupleId->MuPlusId, 1, MuPlusMPB);
        analysisManager->FillNtupleDColumn(tupleId->MuPlusId, 2, MuPlusMTA);
        analysisManager->FillNtupleDColumn(tupleId->MuPlusId, 3, MuPlusMPA);
        analysisManager->AddNtupleRow(tupleId->MuPlusId);
        arr[1] = false;
        arr[2] = false;
        i++;
        std::cout<<"Plus "<<i<<std::endl;
    }
    if (arr[3] or arr[4]) {
        analysisManager->FillNtupleDColumn(tupleId->MuMinusId, 0, MuMinusMTB);
        analysisManager->FillNtupleDColumn(tupleId->MuMinusId, 1, MuMinusMPB);
        analysisManager->FillNtupleDColumn(tupleId->MuMinusId, 2, MuMinusMTA);
        analysisManager->FillNtupleDColumn(tupleId->MuMinusId, 3, MuMinusMPA);
        analysisManager->AddNtupleRow(tupleId->MuMinusId);
        arr[3] = false;
        arr[4] = false;
        k++;
        std::cout<<"Minus "<<k<<std::endl;
    }

}