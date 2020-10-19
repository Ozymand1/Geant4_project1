#ifndef TUPLEID_HH
#define TUPLEID_HH
#include "g4analysis.hh"

struct TupleId{
    G4AnalysisManager* analysisManager;
    int JpsiId = -1;
    int MuPlusId = -1;
    int MuMinusId = -1;
    int MuonMCosTargetId = -1;
    int MuonMCosGenId = -1;
    int MuonPCosTargetId = -1;
    int MuonPCosGenId = -1;
    int histId[18] = {-1};
    int histId1[18] = {-1};
};
#endif