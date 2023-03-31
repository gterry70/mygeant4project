#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  MyDetectorConstruction(); //= default;
    ~MyDetectorConstruction(); //override = default;

  G4VPhysicalVolume* Construct() override;

  G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  protected:
    G4LogicalVolume* fScoringVolume = nullptr;

  //virtual G4VPhysicalVolume* Construct();
};

#endif
