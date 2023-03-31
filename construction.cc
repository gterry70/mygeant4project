#include "construction.hh"
#include "G4Tubs.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXY = 5*m; //world parameters
  G4double world_sizeZ  = 5*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  auto solidWorld = new G4Box("World", world_sizeXY, world_sizeXY, world_sizeZ);
  auto logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
  auto physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0\
, checkOverlaps);


  //Box in the world
  //G4double xyz = 0.5*m;
  //G4Material* box_mat = nist->FindOrBuildMaterial("G4_WATER");

  //auto solidBox = new G4Box("Box", xyz, xyz, xyz);
  //auto logicBox = new G4LogicalVolume(solidBox, box_mat, "Box");
  //new G4PVPlacement(nullptr, G4ThreeVector(), logicBox, "Box", logicWorld, false, 0, checkOverlaps);

  //water
  G4double box6_sizeXY = 35*cm; //box parameters
  G4double box6_sizeZ  = 50*cm;
  G4Material* box6_mat = nist->FindOrBuildMaterial("G4_WATER");

  auto solidBox6 = new G4Box("box6",box6_sizeXY,box6_sizeXY,box6_sizeZ);
  auto logicBox6 = new G4LogicalVolume(solidBox6,box6_mat,"box6"); //its solid, material, name
  new G4PVPlacement(nullptr, G4ThreeVector(), logicBox6, "box6", logicWorld, false, 6, checkOverlaps); // rotation(none), position, its logicalvolume,nams,mother volume, no boolean, copy num, overlap


  ///Aluminum out
  G4double box5_sizeXY = 27*cm; //box parameters
  G4double box5_sizeZ  = 42*cm;
  G4Material* box5_mat = nist->FindOrBuildMaterial("G4_Al");

  auto solidBox5 = new G4Box("box5",box5_sizeXY,box5_sizeXY,box5_sizeZ);
  auto logicBox5 = new G4LogicalVolume(solidBox5,box5_mat,"box5"); 
  new G4PVPlacement(nullptr, G4ThreeVector(), logicBox5, "box5", logicBox6 , false, 5, checkOverlaps)
;


  ///Aluminum in
  G4double box4_sizeXY = 22*cm; //box parameters
  G4double box4_sizeZ  = 37*cm;
  G4Material* box4_mat = nist->FindOrBuildMaterial("G4_Al");

  auto solidBox4 = new G4Box("box4",box4_sizeXY,box4_sizeXY,box4_sizeZ);
  auto logicBox4 = new G4LogicalVolume(solidBox4,box4_mat,"box4");
  new G4PVPlacement(nullptr, G4ThreeVector(), logicBox4, "box4", logicBox5 , false, 4, checkOverlaps)
;


  ///Lead out
  G4double box3_sizeXY = 20*cm; //box parameters
  G4double box3_sizeZ  = 35*cm;
  G4Material* box3_mat = nist->FindOrBuildMaterial("G4_Pb");

  auto solidBox3 = new G4Box("box3",box3_sizeXY,box3_sizeXY,box3_sizeZ);
  auto logicBox3 = new G4LogicalVolume(solidBox3,box3_mat,"box3");
  new G4PVPlacement(nullptr, G4ThreeVector(), logicBox3, "box3", logicBox4 , false, 3, checkOverlaps) ;


  ///Lead in
  G4double box2_sizeXY = 12*cm; //box parameters
  G4double box2_sizeZ  = 27*cm;
  G4Material* box2_mat = nist->FindOrBuildMaterial("G4_Pb");

  auto solidBox2 = new G4Box("box2",box2_sizeXY,box2_sizeXY,box2_sizeZ);
  auto logicBox2 = new G4LogicalVolume(solidBox2,box2_mat,"box2");
  new G4PVPlacement(nullptr, G4ThreeVector(), logicBox2, "box2", logicBox3 , false, 2, checkOverlaps)\
 ;


  ///Plastic
  G4double box1_sizeXY = 10*cm; //box parameters
  G4double box1_sizeZ  = 25*cm;
  G4Material* box1_mat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

  auto solidBox1 = new G4Box("box1",box1_sizeXY,box1_sizeXY,box1_sizeZ);
  auto logicBox1 = new G4LogicalVolume(solidBox1,box1_mat,"box1");
  new G4PVPlacement(nullptr, G4ThreeVector(), logicBox1, "box1", logicBox2 , false, 1, checkOverlaps)\
\
 ;


  ///Csl
  G4double innerR = 0*cm; //Csl parameters
  G4double outerR  = 8*cm;
  G4double leng = 24*cm; G4double phis = 0*degree; G4double phif = 360*degree;
  G4Material* csl_mat = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");

  auto solidtubs = new G4Tubs("csl",innerR,outerR,leng,phis,phif);
  auto logictubs = new G4LogicalVolume(solidtubs,csl_mat,"csl");
  new G4PVPlacement(nullptr, G4ThreeVector(), logictubs, "csl", logicBox1 , false, 7, checkOverlaps)\

 ;

  //Scintillators
  G4Material* sci_mat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  G4RotationMatrix* rotm1 = new G4RotationMatrix();
  rotm1->rotateX(90.*deg);
  rotm1->rotateY(90.*deg);
  G4RotationMatrix* rotm2 = new G4RotationMatrix();
  rotm2->rotateZ(90.*deg);
  G4RotationMatrix* rotm3 = new G4RotationMatrix();
  rotm3->rotateY(90.*deg);
  rotm3->rotateY(90.*deg);
  
  auto solidSci = new G4Box("sci", 35*cm, 1.27*cm, 50*cm);
  auto logicSci = new G4LogicalVolume(solidSci,sci_mat,"sci");
  //top
  new G4PVPlacement(rotm1, G4ThreeVector(0,0,65*cm),logicSci,"sci",logicWorld,false,8,checkOverlaps);
  //
  new G4PVPlacement(rotm2, G4ThreeVector(50*cm,0,0),logicSci,"sci",logicWorld,false,8,checkOverlaps);
  new G4PVPlacement(rotm2, G4ThreeVector(-50*cm,0,0),logicSci,"sci",logicWorld,false,8,checkOverlaps);
  new G4PVPlacement(rotm3, G4ThreeVector(0,50*cm,0),logicSci,"sci",logicWorld,false,8,checkOverlaps);
  new G4PVPlacement(rotm3, G4ThreeVector(0,-50*cm,0),logicSci,"sci",logicWorld,false,8,checkOverlaps);

  
  
  return physWorld;

}
