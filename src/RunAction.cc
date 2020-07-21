#include "RunAction.hh"
#include "g4analysis.hh"


void RunAction::BeginOfRunAction(const G4Run *aRun) {
    G4AnalysisManager *analysisManager = G4Analysis::ManagerInstance("root");
    analysisManager->OpenFile("4GeVnAuRun");
    tupleId->analysisManager = analysisManager;

    int PosId = analysisManager->CreateNtuple("Z_position", "4Gev/n Au Run");
    analysisManager->CreateNtupleDColumn("Z, cm");
    analysisManager->FinishNtuple(PosId);
    tupleId->PosId = PosId;
    /*analysisManager->OpenFile("500MeVRunData");
    tupleId->analysisManager = analysisManager;

    int FortyFiveId = analysisManager->CreateNtuple("FortyFive", "0.5 Run data");
    analysisManager->CreateNtupleDColumn("A" + std::to_string(45));
    analysisManager->FinishNtuple(FortyFiveId);
    tupleId->FortyFiveId = FortyFiveId;

    int NinetyId = analysisManager->CreateNtuple("Ninety", "0.5 Run data");
    analysisManager->CreateNtupleDColumn("A" + std::to_string(90));
    analysisManager->FinishNtuple(NinetyId);
    tupleId->NinetyId = NinetyId;

    int HundredThirtyFiveId = analysisManager->CreateNtuple("HundredAndFive", "0.5 Run data");
    analysisManager->CreateNtupleDColumn("A" + std::to_string(135));
    analysisManager->FinishNtuple(HundredThirtyFiveId);
    tupleId->HundredThirtyFiveId = HundredThirtyFiveId;*/
}

void RunAction::EndOfRunAction(const G4Run *aRun) {
    G4UserRunAction::EndOfRunAction(aRun);
    G4AnalysisManager* analysisManager = G4Analysis::ManagerInstance("root");
    analysisManager->Write();
    analysisManager->CloseFile(true);
}

RunAction::RunAction(TupleId *tupleId) : tupleId(tupleId) {

}