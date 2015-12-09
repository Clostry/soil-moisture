#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"

#include "g4root.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoManager
{
  public:
   HistoManager();
  ~HistoManager();

   void Book();
   void Save();

   void FillNtuple1(G4double x, G4double y, G4double e);
   void FillNtuple2(G4double x, G4double y, G4double z, G4double e);

  private:
    G4String fFileName;
    G4bool fFactoryOn;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

