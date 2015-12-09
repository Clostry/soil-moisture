// HistoManager.cc

#include "HistoManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
 :fFileName("moisture"),
  fFactoryOn(false)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::FillNtuple1(G4double x, G4double y, G4double e)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Fill 1st ntuple ( id = 0)
  analysisManager->FillNtupleDColumn(0, 0, x);
  analysisManager->FillNtupleDColumn(0, 1, y);
  analysisManager->FillNtupleDColumn(0, 2, e);
  analysisManager->AddNtupleRow(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::FillNtuple2(G4double x, G4double y, G4double z, G4double e)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Fill 2nd ntuple ( id = 1)
  analysisManager->FillNtupleDColumn(1, 0, x);
  analysisManager->FillNtupleDColumn(1, 1, y);
  analysisManager->FillNtupleDColumn(1, 2, z);
  analysisManager->FillNtupleDColumn(1, 3, e);
  analysisManager->AddNtupleRow(1);
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
void HistoManager::Book()
{ 
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);

  // Create directories 
//  analysisManager->SetHistoDirectoryName("histo");
//  analysisManager->SetNtupleDirectoryName("ntuple");

  // Open an output file
  //
  G4bool fileOpen = analysisManager->OpenFile(fFileName);
  if (! fileOpen) {
    G4cerr << "\n---> HistoManager::Book(): cannot open "
           << analysisManager->GetFileName() << G4endl;
    return;
  }

  // Create 1st ntuple (id = 0)
  analysisManager->CreateNtuple("Ntuple1", "Neutroni primari");
  analysisManager->CreateNtupleDColumn("x");    // column Id = 0
  analysisManager->CreateNtupleDColumn("y");    // column Id = 1
  analysisManager->CreateNtupleDColumn("Ekin"); // column Id = 2
  analysisManager->FinishNtuple();

  // Create 2nd ntuple (id = 1)
  analysisManager->CreateNtuple("Ntuple2", "Neutroni rimbalzati");
  analysisManager->CreateNtupleDColumn("x");    // column Id = 0
  analysisManager->CreateNtupleDColumn("y");    // column Id = 1
  analysisManager->CreateNtupleDColumn("z");    // column Id = 2
  analysisManager->CreateNtupleDColumn("Ekin"); // column Id = 3
  analysisManager->FinishNtuple();

  fFactoryOn = true;
  
  G4cout << "\n----> Output file is open in " 
         << analysisManager->GetFileName() << "." 
         << analysisManager->GetFileType() << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Save()
{
 if (! fFactoryOn) return;

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

  G4cout << "\n----> Histograms and ntuples are saved\n" << G4endl;

  delete G4AnalysisManager::Instance();
  fFactoryOn = false;
}
