
#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "Run.hh"
#include "EventAction.hh"
#include "HistoManager.hh"

#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "G4ThreeVector.hh"
#include "G4Track.hh"

#include "globals.hh"
#include "G4SteppingManager.hh"
#include "G4ParticleDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(DetectorConstruction* det, EventAction* event)
: G4UserSteppingAction(), fDetector(det), fEventAction(event)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* fStep) 
{
/* 
 Run* run = static_cast<Run*>(
			       G4RunManager::GetRunManager()->GetNonConstCurrentRun());    
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  */
  //which volume ?
  //
  G4VPhysicalVolume* pVolume = fStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  G4int iVol = 0;
  if (pVolume->GetName() == "Detector") iVol = 1;
   
  // count processes
  /* 
  const G4StepPoint* endPoint = fStep->GetPostStepPoint();
  const G4VProcess* process   = endPoint->GetProcessDefinedStep();
  run->CountProcesses(process, iVol);
  */
  
  //energy deposit
  G4double edep = fStep->GetTotalEnergyDeposit(); //G4cout<<"edep ="<<edep<<"ivol = "<<iVol<<G4endl;
  G4double time = fStep->GetPreStepPoint()->GetGlobalTime();
  G4double weight =  fStep->GetPreStepPoint()->GetWeight();
  fEventAction->AddEdep(iVol, edep, time, weight); 

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
