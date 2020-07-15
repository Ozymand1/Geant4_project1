#include <G4VUserDetectorConstruction.hh>
#include "G4LogicalVolume.hh"
#include "GeometrySize.hh"
#include "G4SystemOfUnits.hh"

using namespace CLHEP;

class DetectorConstruction : public G4VUserDetectorConstruction{
public:

    G4VPhysicalVolume* Construct() override;
    explicit DetectorConstruction(){
        InitializeMaterials();
    }
private:
    G4Material* vaccum;
    G4Material* wolfram;
    G4LogicalVolume* CreateDetector();
    G4LogicalVolume* CreateCylinderWithHole();
    G4LogicalVolume* CreateCylinder();
    G4LogicalVolume* wolfram_logic;
    G4LogicalVolume* detector_logic;

    void InitializeMaterials();
};