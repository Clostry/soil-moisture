// GeometryMessenger.cc

#include "GeometryMessenger.hh"

#include "GeometryConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GeometryMessenger::GeometryMessenger(GeometryConstruction * Det)
:G4UImessenger(),fGeometry(Det)
{
/*  fTestemDir = new G4UIdirectory("/testem/");
  fTestemDir->SetGuidance(" detector control.");
  
  fDetDir = new G4UIdirectory("/testem/det/");
  fDetDir->SetGuidance("detector construction commands");

  fMaterCmd = new G4UIcmdWithAString("/testem/det/setMat",this);
  fMaterCmd->SetGuidance("Select Material.");
  fMaterCmd->SetParameterName("material",false);
  fMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fMaterCmd->SetToBeBroadcasted(false);

  fLBinCmd = new G4UIcmdWith3Vector("/testem/det/setLbin",this);
  fLBinCmd->SetGuidance("set longitudinal bining");
  fLBinCmd->SetGuidance("nb of bins; bin thickness (in radl)");
  fLBinCmd->SetParameterName("nLtot","dLradl"," ",true);
  fLBinCmd->SetRange("nLtot>=1 && dLradl>0");
  fLBinCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fLBinCmd->SetToBeBroadcasted(false);

  fRBinCmd = new G4UIcmdWith3Vector("/testem/det/setRbin",this);
  fRBinCmd->SetGuidance("set radial bining");
  fRBinCmd->SetGuidance("nb of bins; bin thickness (in radl)");
  fRBinCmd->SetParameterName("nRtot","dRradl"," ",true);
  fRBinCmd->SetRange("nRtot>=1 && dRradl>0");
  fRBinCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fRBinCmd->SetToBeBroadcasted(false);
  */  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GeometryMessenger::~GeometryMessenger()
{
  /*
  delete fMaterCmd;
  delete fLBinCmd;
  delete fRBinCmd;
  delete fDetDir;
  delete fTestemDir;
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GeometryMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  /*
  if( command == fMaterCmd )
   { fGeometry->SetMaterial(newValue);}
   
  if( command == fLBinCmd )
   { fGeometry->SetLBining(fLBinCmd->GetNew3VectorValue(newValue));}

  if( command == fRBinCmd )
   { fGeometry->SetRBining(fRBinCmd->GetNew3VectorValue(newValue));}
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
