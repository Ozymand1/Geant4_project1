#include "DetectorConstruction.hh"
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4SDManager.hh>
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "GeometrySize.hh"
#include <G4Tubs.hh>

G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4bool checkOverlaps = true;

    G4double world_sizeXY = 20 * cm;
    G4double world_sizeZ = 1.2 * meter;

    auto solidWorld =
            new G4Box("World",
                      0.5 * world_sizeXY,
                      0.5 * world_sizeXY,
                      0.5 * world_sizeZ);

    auto logicWorld =
            new G4LogicalVolume(solidWorld,
                                vacuum,
                                "World");

    auto physWorld =
            new G4PVPlacement(0,
                               G4ThreeVector(0, 0, 1),
                               logicWorld,
                               "World",
                               0,
                               false,
                               0,
                               checkOverlaps);

    detector_logic = CreateDetector();

}

G4LogicalVolume* DetectorConstruction::CreateDetector() {
    auto detectorSolid =
            new G4Tubs("Detector",
                        0,
                        0.5 *  cylinder_diameter,
                        0.5 * cylinder_lenght,
                        0,
                        2 * pi);

    auto detector =
            new G4LogicalVolume(detectorSolid,
                                vaccum,
                                "detector");

    auto cylinder_with_hole_logic = CreateCylinderWithHole();
    auto cylinder_logic = CreateCylinder();
}

G4LogicalVolume* DetectorConstruction::CreateCylinderWithHole() {
    auto c_with_hole_solid =
            new G4Tubs("cylinder_with_hole",
                        0.5 * hole_diameter,
                        0.5 * cylinder_diameter,
                        0.5 * hole_lenght);

    auto c_with_hole_logic =
            new G4LogicalVolume(c_with_hole_solid,
                                wolfram,
                                "c_with_hole");

    auto c_with_hole_phys =
            new G4PVPlacement(0,
                              G4ThreeVector(0, 0, hole_lenght),
                              c_with_hole_logic,
                              "c_with_hole",
                              detector);

}

void DetectorConstruction::InitializeMaterials() {
    auto nist = G4NistManager::Instance();
    vaccum = nist->FindOrBuildMaterial("G4_Galactic");
    wolfram = nist->FindOrBuildMaterial("G4_W");
}