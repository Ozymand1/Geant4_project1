#include "RunAction.hh"
#include "g4analysis.hh"


void RunAction::BeginOfRunAction(const G4Run *aRun) {
    G4AnalysisManager *analysisManager = G4Analysis::ManagerInstance("root");
    analysisManager->OpenFile("JpsiRun1");
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

    int MuonMCosTargetId = analysisManager->CreateNtuple("CosOfMuonTarget", "JpsiRun");
    analysisManager->CreateNtupleDColumn("Muon");
    analysisManager->CreateNtupleDColumn("NumberOfEvent");
    analysisManager->FinishNtuple(MuonMCosTargetId);
    tupleId->MuonMCosTargetId = MuonMCosTargetId;

    int MuonMCosGenId = analysisManager->CreateNtuple("CosOfMuonGen", "JpsiRun");
    analysisManager->CreateNtupleDColumn("Muon");
    analysisManager->CreateNtupleDColumn("NumberOfEvent");
    analysisManager->FinishNtuple(MuonMCosGenId);
    tupleId->MuonMCosGenId = MuonMCosGenId;

    int MuonPCosTargetId = analysisManager->CreateNtuple("CosOfAntiMuonTarget", "JpsiRun");
    analysisManager->CreateNtupleDColumn("antiMuon");
    analysisManager->CreateNtupleDColumn("NumberOfEvent");
    analysisManager->FinishNtuple(MuonPCosTargetId);
    tupleId->MuonPCosTargetId = MuonPCosTargetId;

    int MuonPCosGenId = analysisManager->CreateNtuple("CosOfAntiMuonGen", "JpsiRun");
    analysisManager->CreateNtupleDColumn("antiMuon");
    analysisManager->CreateNtupleDColumn("NumberOfEvent");
    analysisManager->FinishNtuple(MuonPCosGenId);
    tupleId->MuonPCosGenId = MuonPCosGenId;

    int hist010Id = analysisManager->CreateH1("h0","momentum", 300 * 1.4, 0, 6.6);
    int hist1020Id = analysisManager->CreateH1("h1","momentum", 300 * 1.4, 0, 6.6);
    int hist2030Id = analysisManager->CreateH1("h2","momentum", 300 * 1.4, 0, 6.6);
    int hist3040Id = analysisManager->CreateH1("h3","momentum", 300 * 1.4, 0, 6.6);
    int hist4050Id = analysisManager->CreateH1("h4","momentum", 300 * 1.4, 0, 6.6);
    int hist5060Id = analysisManager->CreateH1("h5","momentum", 300 * 1.4, 0, 6.6);
    int hist6070Id = analysisManager->CreateH1("h6","momentum", 300 * 1.4, 0, 6.6);
    int hist7080Id = analysisManager->CreateH1("h7","momentum", 300 * 1.4, 0, 6.6);
    int hist8090Id = analysisManager->CreateH1("h8","momentum", 300 * 1.4, 0, 6.6);
    int hist90100Id = analysisManager->CreateH1("h9","momentum", 300 * 1.4, 0, 6.6);
    int hist100110Id = analysisManager->CreateH1("h10","momentum", 300 * 1.4, 0, 6.6);
    int hist110120Id = analysisManager->CreateH1("h11","momentum", 300 * 1.4, 0, 6.6);
    int hist120130Id = analysisManager->CreateH1("h12","momentum", 300 * 1.4, 0, 6.6);
    int hist130140Id = analysisManager->CreateH1("h13","momentum", 300 * 1.4, 0, 6.6);
    int hist140150Id = analysisManager->CreateH1("h14","momentum", 300 * 1.4, 0, 6.6);
    int hist150160Id = analysisManager->CreateH1("h15","momentum", 300 * 1.4, 0, 6.6);
    int hist160170Id = analysisManager->CreateH1("h16","momentum", 300 * 1.4, 0, 6.6);
    int hist170180Id = analysisManager->CreateH1("h17","momentum", 300 * 1.4, 0, 6.6);


    tupleId->histId[0] = hist010Id;
    tupleId->histId[1] = hist1020Id;
    tupleId->histId[2] = hist2030Id;
    tupleId->histId[3] = hist3040Id;
    tupleId->histId[4] = hist4050Id;
    tupleId->histId[5] = hist5060Id;
    tupleId->histId[6] = hist6070Id;
    tupleId->histId[7] = hist7080Id;
    tupleId->histId[8] = hist8090Id;
    tupleId->histId[9] = hist90100Id;
    tupleId->histId[10] = hist100110Id;
    tupleId->histId[11] = hist110120Id;
    tupleId->histId[12] = hist120130Id;
    tupleId->histId[13] = hist130140Id;
    tupleId->histId[14] = hist140150Id;
    tupleId->histId[15] = hist150160Id;
    tupleId->histId[16] = hist160170Id;
    tupleId->histId[17] = hist170180Id;



    int hist010Id1 = analysisManager->CreateH1("h0m","momentum", 300 * 1.4, 0, 6.6);
    int hist1020Id1 = analysisManager->CreateH1("h1m","momentum", 300 * 1.4, 0, 6.6);
    int hist2030Id1 = analysisManager->CreateH1("h2m","momentum", 300 * 1.4, 0, 6.6);
    int hist3040Id1 = analysisManager->CreateH1("h3m","momentum", 300 * 1.4, 0, 6.6);
    int hist4050Id1 = analysisManager->CreateH1("h4m","momentum", 300 * 1.4, 0, 6.6);
    int hist5060Id1 = analysisManager->CreateH1("h5m","momentum", 300 * 1.4, 0, 6.6);
    int hist6070Id1 = analysisManager->CreateH1("h6m","momentum", 300 * 1.4, 0, 6.6);
    int hist7080Id1 = analysisManager->CreateH1("h7m","momentum", 300 * 1.4, 0, 6.6);
    int hist8090Id1 = analysisManager->CreateH1("h8m","momentum", 300 * 1.4, 0, 6.6);
    int hist90100Id1 = analysisManager->CreateH1("h9m","momentum", 300 * 1.4, 0, 6.6);
    int hist100110Id1 = analysisManager->CreateH1("h10m","momentum", 300 * 1.4, 0, 6.6);
    int hist110120Id1 = analysisManager->CreateH1("h11m","momentum", 300 * 1.4, 0, 6.6);
    int hist120130Id1 = analysisManager->CreateH1("h12m","momentum", 300 * 1.4, 0, 6.6);
    int hist130140Id1 = analysisManager->CreateH1("h13m","momentum", 300 * 1.4, 0, 6.6);
    int hist140150Id1 = analysisManager->CreateH1("h14m","momentum", 300 * 1.4, 0, 6.6);
    int hist150160Id1 = analysisManager->CreateH1("h15m","momentum", 300 * 1.4, 0, 6.6);
    int hist160170Id1 = analysisManager->CreateH1("h16m","momentum", 300 * 1.4, 0, 6.6);
    int hist170180Id1 = analysisManager->CreateH1("h17m","momentum", 300 * 1.4, 0, 6.6);


    tupleId->histId1[0] = hist010Id1;
    tupleId->histId1[1] = hist1020Id1;
    tupleId->histId1[2] = hist2030Id1;
    tupleId->histId1[3] = hist3040Id1;
    tupleId->histId1[4] = hist4050Id1;
    tupleId->histId1[5] = hist5060Id1;
    tupleId->histId1[6] = hist6070Id1;
    tupleId->histId1[7] = hist7080Id1;
    tupleId->histId1[8] = hist8090Id1;
    tupleId->histId1[9] = hist90100Id1;
    tupleId->histId1[10] = hist100110Id1;
    tupleId->histId1[11] = hist110120Id1;
    tupleId->histId1[12] = hist120130Id1;
    tupleId->histId1[13] = hist130140Id1;
    tupleId->histId1[14] = hist140150Id1;
    tupleId->histId1[15] = hist150160Id1;
    tupleId->histId1[16] = hist160170Id1;
    tupleId->histId1[17] = hist170180Id1;

}

void RunAction::EndOfRunAction(const G4Run *aRun) {
    G4UserRunAction::EndOfRunAction(aRun);
    G4AnalysisManager* analysisManager = G4Analysis::ManagerInstance("root");
    analysisManager->Write();
    analysisManager->CloseFile(true);
}

RunAction::RunAction(TupleId *tupleId) : tupleId(tupleId) {

}