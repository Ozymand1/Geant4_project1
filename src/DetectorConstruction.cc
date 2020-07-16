#include "DetectorConstruction.hh"
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4SDManager.hh>
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include <G4Tubs.hh>

G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4bool checkOverlaps = true;

    G4double world_sizeXY = 2 * meter;
    G4double world_sizeZ = 2 * meter;

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
                               G4ThreeVector(0, 0, 0),
                               logicWorld,
                               "World",
                               0,
                               false,
                               0,
                               checkOverlaps);

    detector_logic = CreateDetector();

    auto cylinder =
            new G4PVPlacement(0,
                              G4ThreeVector(0, 0, -40 * cm),
                              detector_logic,
                              "cylinder",
                              logicWorld,
                              false,
                              0);

    return physWorld;
}

G4LogicalVolume* DetectorConstruction::CreateDetector() {
    auto detectorSolid =
            new G4Tubs("Detector",
                        0,
                        0.5 *  cylinder_diameter,
                        0.5 * cylinder_lenght,
                        0,
                        2 * pi);

    auto detector_logic =
            new G4LogicalVolume(detectorSolid,
                                vacuum,
                                "detector");

    auto cylinder_with_hole_solid =
            new G4Tubs("cylinder",
                       0.5 * hole_diameter,
                       0.5 * cylinder_diameter,
                       0.5 * hole_lenght,
                       0,
                       2 * pi);

    auto cylinder_with_hole_logic =
            new G4LogicalVolume(cylinder_with_hole_solid,
                                wolfram,
                                "cylinder");

    auto cylinder_with_hole_phys =
            new G4PVPlacement(0,
                              G4ThreeVector(0, 0, 45 * cm),
                              cylinder_with_hole_logic,
                              "cylinder",
                              detector_logic,
                              false,
                              0);

    auto cylinder_solid =
            new G4Tubs("cylinder",
                       0,
                       0.5 * cylinder_diameter,
                       0.5 * (cylinder_lenght - hole_lenght),
                       0,
                       2 * pi);

    auto cylinder_logic =
            new G4LogicalVolume(cylinder_solid,
                                wolfram,
                                "cylinder");

    auto cylinder_phys =
            new G4PVPlacement(0,
                              G4ThreeVector(0, 0, -5 * cm),
                              cylinder_logic,
                              "cylinder_with_hole",
                              detector_logic,
                              false,
                              0);

    return detector_logic;

}

void DetectorConstruction::InitializeMaterials() {
    auto nist = G4NistManager::Instance();
    vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    wolfram = nist->FindOrBuildMaterial("G4_W");
}