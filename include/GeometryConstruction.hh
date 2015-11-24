#ifndef GeometryConstruction1_h
#define GeometryConstruction1_h 1

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class GeometryConstruction : public G4VUserDetectorConstruction
{
  public:
    GeometryConstruction ();
   ~GeometryConstruction ();

    virtual G4VPhysicalVolume* Construct();

  private:
    G4VPhysicalVolume* physWorld;
    G4VPhysicalVolume* physSoil;
};
    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

