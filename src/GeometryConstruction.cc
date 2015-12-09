// GeometryConstruction.cc

#include "GeometryConstruction.hh"
//#include "ScorerSD.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
//#include "G4SDManager.hh"

G4double water_volvol_ratio = 0.1;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GeometryConstruction::GeometryConstruction()
: G4VUserDetectorConstruction(),
  physWorld(0),
  physSoil(0)
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GeometryConstruction::~GeometryConstruction()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VPhysicalVolume* GeometryConstruction::Construct()
{

  G4NistManager* nist = G4NistManager::Instance();

  G4bool checkOverlaps = true;

// Dimensions

  G4double world_sizeXY = 5.*m;
  G4double world_sizeZ  = 5.*m;

  G4double soil_sizeXY = 5.*m;
  G4double soil_sizeZ = 3.*m;

// Materials

  G4Material* air = nist->FindOrBuildMaterial("G4_AIR");

  G4double densitySoil = 2.70*g/cm3; 
  G4Material* SiO2 = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
  G4Material* H2O = nist->FindOrBuildMaterial("G4_WATER");

  G4Material* materialSoil = new G4Material("Soil",densitySoil
		  ,2);  //number of components

  G4double densityWater = 1*g/cm3;
  G4double water_mass_ratio =
	  densityWater * water_volvol_ratio / 
	  (densitySoil*(1-water_volvol_ratio)+densityWater*water_volvol_ratio);

  materialSoil->AddMaterial(SiO2, 
		  (1-water_mass_ratio)); //fraction mass
  materialSoil->AddMaterial(H2O, water_mass_ratio);

  // Volumes

  G4Box* solidWorld =
	  new G4Box("World",                       //its name
			  world_sizeXY, world_sizeXY, world_sizeZ);      //its size

  G4LogicalVolume* logicWorld =
	  new G4LogicalVolume(solidWorld, air, "World");      

  physWorld =
	  new G4PVPlacement(0,                     //no rotation
			  G4ThreeVector(),       //at (0,0,0)
			  logicWorld,            //its logical volume
			  "World",               //its name
			  0,                     //its mother  volume
			  false,                 //no boolean operation
			  0,                     //copy number
			  checkOverlaps);        //overlaps checking

  G4Box* solidSoil =
	  new G4Box("Soil", soil_sizeXY, soil_sizeXY, soil_sizeZ);

  G4LogicalVolume* logicSoil =
	  new G4LogicalVolume(solidSoil, materialSoil, "Soil");

  physSoil = 
	  new G4PVPlacement(0,
			  G4ThreeVector(0,0,soil_sizeZ-world_sizeZ),
			  logicSoil,
			  "Soil",
			  logicWorld,
			  0,
			  false,
			  checkOverlaps);

  G4double scorer_sizeZ = 5.*cm;
  G4double scorer_sizeXY = soil_sizeXY;
  //distance from soil
  G4double scorer_h = 2.*m;
  G4double scorer_z = 2*soil_sizeZ - world_sizeZ + scorer_h + scorer_sizeZ;

  G4Box* solidScorer =
	  new G4Box("Soil", scorer_sizeXY,scorer_sizeXY, scorer_sizeZ);

  G4LogicalVolume* logicScorer =
	  new G4LogicalVolume(solidScorer, air, "Scorer");

  physSoil = 
	  new G4PVPlacement(0,
			  G4ThreeVector(0,0,scorer_z),
			  logicScorer,
			  "Scorer",
			  logicWorld,
			  0,
			  false,
			  checkOverlaps);

// DETECTOR
/*  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  ScorerSD* aScorerSD = new ScorerSD("moisture/scorer");
  SDman->AddNewDetector( aScorerSD );
  SetSensitiveDetector("Scorer", aScorerSD, true);
  */

  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
