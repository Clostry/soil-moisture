#ifndef GeometryMessenger_h
#define GeometryMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class GeometryConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWith3Vector;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class GeometryMessenger: public G4UImessenger
{
public:
  GeometryMessenger(GeometryConstruction* );
  virtual ~GeometryMessenger();

  virtual void SetNewValue(G4UIcommand*, G4String);

private:
  GeometryConstruction*      fGeometry;

  G4UIdirectory*             fTestemDir;
  G4UIdirectory*             fDetDir;  
  G4UIcmdWithAString*        fMaterCmd;
  G4UIcmdWith3Vector*        fLBinCmd;
  G4UIcmdWith3Vector*        fRBinCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

