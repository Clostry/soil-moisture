// ActionInitialization.cc
#include "ActionInitialization.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "TrackingAction.hh"
#include "SteppingAction.hh"
#include "HistoManager.hh"
#include "GeometryConstruction.hh"


ActionInitialization::ActionInitialization(GeometryConstruction* geometry)
  :G4VUserActionInitialization(),
   fGeometry(geometry)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::BuildForMaster() const
{
  HistoManager*  histo = new HistoManager();

  SetUserAction(new RunAction(histo));    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{
  HistoManager*  histo = new HistoManager();

  SetUserAction(new PrimaryGeneratorAction(histo));

  RunAction* runAction = new RunAction(histo);
  SetUserAction(runAction);

//  TrackingAction* trackingAction = new TrackingAction(fGeometry,histo);
//  SetUserAction(trackingAction);

  SteppingAction* steppingAction = new SteppingAction(fGeometry,histo);
  SetUserAction(steppingAction);
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
