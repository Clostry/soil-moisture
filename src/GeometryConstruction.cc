//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: GeometryConstruction.cc 67272 2013-02-13 12:05:47Z ihrivnac $
//
/// \file eventgenerator/exgps/src/GeometryConstruction.cc
/// \brief Implementation of the GeometryConstruction class
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "GeometryConstruction.hh"

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

  G4double water_volvol_ratio = 0.1;
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

  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
