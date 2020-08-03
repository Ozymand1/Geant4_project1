#ifndef TUPLEID_HH
#define TUPLEID_HH
#include "g4analysis.hh"

struct TupleId{
    G4AnalysisManager* analysisManager;
    int JpsiId = -1;
    int MuPlusId = -1;
    int MuMinusId = -1;
};
#endif