// TrackingAction.cc

#include "TrackingAction.hh"
#include "HistoManager.hh"

#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

TrackingAction::TrackingAction()
:G4UserTrackingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
  if (track->GetParentID() == 0)
  {
  G4int pid               = track->GetDynamicParticle()->GetPDGcode();
  G4double ekin           = track->GetKineticEnergy();
  G4ThreeVector vertex    = track->GetPosition();
  G4ThreeVector direction = track->GetMomentumDirection();
  G4double weight         = track->GetWeight();

//  G4cout << track->GetParentID() << " " << track->GetTrackID() << G4endl;
   
  G4double x = vertex.x(), y = vertex.y(), z = vertex.z();
  G4double theta = direction.theta(), phi = direction.phi();
  if (phi < 0.) phi += twopi;
  G4double cost = std::cos(theta);
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
  G4double r = vertex.mag();
  G4double dr = analysisManager->GetH1Width(2);
  G4double dv = 2*twopi*r*r*dr;  

  // fill histograms    
  analysisManager->FillH1(1,ekin);
  if (dv > 0.) analysisManager->FillH1(2, r, 1./dv);  
  analysisManager->FillH1(3,cost);  
  analysisManager->FillH1(4,phi);    
  analysisManager->FillH2(1,x,y);
  analysisManager->FillH2(2,y,z);
  analysisManager->FillH2(3,z,x);      
  analysisManager->FillH2(4,phi,cost);
  analysisManager->FillH2(5,phi,theta);
  
  // fill ntuple  
  analysisManager->FillNtupleIColumn(0,pid);
  analysisManager->FillNtupleDColumn(1,ekin);
  analysisManager->FillNtupleDColumn(2,x);
  analysisManager->FillNtupleDColumn(3,y);
  analysisManager->FillNtupleDColumn(4,z);
  analysisManager->FillNtupleDColumn(5,theta);
  analysisManager->FillNtupleDColumn(6,phi);
  analysisManager->FillNtupleDColumn(7,weight);
  analysisManager->AddNtupleRow();  
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....






