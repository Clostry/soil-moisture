#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "GeometryConstruction.hh"
#include "ActionInitialization.hh"

#include "Randomize.hh"
#include "G4PhysListFactory.hh"
#include "G4ScoringManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

int main(int argc,char** argv) {

  //random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);

  // Construct the default run manager
#ifdef G4MULTITHREADED
  G4MTRunManager * runManager = new G4MTRunManager;
  G4int nThreads = G4Threading::G4GetNumberOfCores();
  if (argc==3) nThreads = G4UIcommand::ConvertToInt(argv[2]);   
  runManager->SetNumberOfThreads(nThreads);
#else
  G4RunManager * runManager = new G4RunManager;
#endif

  // activate scoring manager
  G4ScoringManager::GetScoringManager();

  // set mandatory initialization classes
  GeometryConstruction* geometry = new GeometryConstruction;
  runManager->SetUserInitialization(geometry);

  // Physics list
  G4PhysListFactory factory;
  G4VModularPhysicsList* physlist_neut = factory.GetReferencePhysList("QGSP_BERT_HP");
  physlist_neut->SetVerboseLevel(0);
  runManager->SetUserInitialization(physlist_neut);

//  runManager->SetUserInitialization(new PhysicsList);
  
  runManager->SetUserInitialization(new ActionInitialization(geometry));

  runManager->Initialize();
    
#ifdef G4VIS_USE
  // visualization manager
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif
    
  // get the pointer to the User Interface manager 
  G4UImanager* UImanager = G4UImanager::GetUIpointer();  

  if (argc!=1)   // batch mode
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);    
    }
  else          // interactive mode : define UI session
    {
#ifdef G4UI_USE
     G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
     UImanager->ApplyCommand("/control/execute vis.mac");
#endif             
     ui->SessionStart();
     delete ui;
#endif
     
#ifdef G4VIS_USE
     delete visManager;
#endif    
    }

  // job termination
  //
  delete runManager;
  
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..... 
