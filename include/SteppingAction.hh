#ifndef SteppingAction_H
#define SteppingAction_H 1

#include "globals.hh"
#include "G4UserSteppingAction.hh"

class GeometryConstruction;
class HistoManager;

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(GeometryConstruction* geometry, HistoManager *histo);
    virtual ~SteppingAction();
    static SteppingAction* Instance();
    virtual void UserSteppingAction(const G4Step*);
    G4int GetCounts();

  private:
    G4int fCounts;
    GeometryConstruction *fGeom;
    HistoManager *fHisto;
    static SteppingAction* fgInstance;
};

#endif

