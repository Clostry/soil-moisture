#ifndef TrackingAction_h
#define TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class GeometryConstruction;
class HistoManager;

class TrackingAction : public G4UserTrackingAction
{
  public:
    TrackingAction(GeometryConstruction* geometry, HistoManager *histo);
   ~TrackingAction();
    
    virtual void  PreUserTrackingAction(const G4Track*);

  private:
    GeometryConstruction* fGeom;
    HistoManager *fHisto;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
