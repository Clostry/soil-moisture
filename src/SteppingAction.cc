#include "SteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "HistoManager.hh"

SteppingAction* SteppingAction::fgInstance = 0;


SteppingAction::SteppingAction(GeometryConstruction* geometry, HistoManager* histo)
  :fCounts(0),
   fGeom(geometry), fHisto(histo)
{
  fgInstance = this;
}

SteppingAction::~SteppingAction()
{
  fgInstance = 0;
}

SteppingAction* SteppingAction::Instance()
{
  return fgInstance;
}   
G4int SteppingAction::GetCounts()
{
  return fCounts;
}

void SteppingAction::UserSteppingAction(const G4Step * theStep)
{
  G4Track * theTrack = theStep->GetTrack();

  // check if it is alive
  if(theTrack->GetTrackStatus()!=fAlive) { return; }

  // check if it is not primary
  if(theTrack->GetParentID()==0) { return; }

  // check if it is Neutron
  G4ParticleDefinition * particleType = theTrack->GetDefinition();
  if(particleType!=G4Neutron::NeutronDefinition())
  { return; }

  //check boundary
  G4StepPoint * thePostPoint = theStep->GetPostStepPoint();
  if(thePostPoint->GetStepStatus()!=fGeomBoundary){return;}

/*  G4StepPoint * thePrePoint = theStep->GetPreStepPoint();
  G4VPhysicalVolume * thePrePV = thePrePoint->GetPhysicalVolume();
  G4String thePrePVname = thePrePV->GetName();
  if(thePrePVname=="Scorer") { return; }
  */

  // check if it is entering to the volume
  G4VPhysicalVolume * thePostPV = thePostPoint->GetPhysicalVolume();
  G4String thePostPVname = thePostPV->GetName();
  if(thePostPVname!="Scorer") { return; }
 
  G4ThreeVector direction = thePostPoint->GetMomentumDirection();
  //check if it's reflected
  if(direction.z()<0) {return;}

  //increment counter
  fCounts++;

/*  
  G4cout << "***************************************** ECCOLA *******************************\n";
  G4cout << thePostPoint->GetPosition() << G4endl;
  G4cout << "********************************************************************************\n";
*/

  G4double ekin           = thePostPoint->GetKineticEnergy();
  G4ThreeVector vertex    = thePostPoint->GetPosition();

  G4double x = vertex.x(), y = vertex.y(), z = vertex.z();

  fHisto->FillNtuple2(x,y,z,ekin);
    
  // then suspend the track
  theTrack->SetTrackStatus(fSuspend);
  return;
}


