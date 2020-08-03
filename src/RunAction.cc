#include "RunAction.hh"
#include "g4analysis.hh"


void RunAction::BeginOfRunAction(const G4Run *aRun) {
    G4AnalysisManager *analysisManager = G4Analysis::ManagerInstance("root");
    analysisManager->OpenFile("JpsiRun");
    tupleId->analysisManager = analysisManager;

    int JpsiId = analysisManager->CreateNtuple("JpsiMomentum", "JpsiRunJpsi");
    analysisManager->CreateNtupleDColumn("TransverseMomentum");
    analysisManager->CreateNtupleDColumn("ParallelMomentum");
    analysisManager->FinishNtuple(JpsiId);
    tupleId->JpsiId = JpsiId;

    int MuPlusId = analysisManager->CreateNtuple("MuonPlusMomentum", "JpsiRunMuonPlus");
    analysisManager->CreateNtupleDColumn("TransverseMomentumBefore");
    analysisManager->CreateNtupleDColumn("ParallelMomentumBefore");
    analysisManager->CreateNtupleDColumn("TransverseMomentumAfter");
    analysisManager->CreateNtupleDColumn("ParallelMomentumAfter");
    analysisManager->FinishNtuple(MuPlusId);
    tupleId->MuPlusId = MuPlusId;

    int MuMinusId = analysisManager->CreateNtuple("MuonMinusMomentum", "JpsiRunMuonMinus");
    analysisManager->CreateNtupleDColumn("TransverseMomentumBefore");
    analysisManager->CreateNtupleDColumn("ParallelMomentumBefore");
    analysisManager->CreateNtupleDColumn("TransverseMomentumAfter");
    analysisManager->CreateNtupleDColumn("ParallelMomentumAfter");
    analysisManager->FinishNtuple(MuMinusId);
    tupleId->MuMinusId = MuMinusId;
}

void RunAction::EndOfRunAction(const G4Run *aRun) {
    G4UserRunAction::EndOfRunAction(aRun);
    G4AnalysisManager* analysisManager = G4Analysis::ManagerInstance("root");
    analysisManager->Write();
    analysisManager->CloseFile(true);
}

RunAction::RunAction(TupleId *tupleId) : tupleId(tupleId) {

}