#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class GeometryConstruction;

class  ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization(GeometryConstruction* geometry);
   ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    GeometryConstruction* fGeometry;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
