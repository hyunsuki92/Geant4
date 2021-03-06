//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file radioactivedecay/rdecay01/src/EventAction.cc
/// \brief Implementation of the EventAction class
//
// $Id: EventAction.cc 68030 2013-03-13 13:51:27Z gcosmo $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "EventAction.hh"
#include "EventMessenger.hh"

#include "Run.hh"
#include "HistoManager.hh"

#include "G4Event.hh"
#include <iomanip>
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
:G4UserEventAction(),
 fPrintModulo(10000),fDecayChain(),fEventMessenger(0),fEdep1(0.), fEdep2(0.), fWeight1(0.), fWeight2(0.),
 fTime0(-1*s)
{
  fEventMessenger = new EventMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{
  delete fEventMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
 fDecayChain = " ";
fEdep1 = fEdep2 = fWeight1 = fWeight2 = 0.;
  fTime0 = -1*s;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::AddEdep(G4int iVol, G4double edep,
                                      G4double time, G4double weight)
{

  // initialize t0
  if (fTime0 < 0.) fTime0 = time;
  
  // out of time window ?
  const G4double TimeWindow (1*microsecond);
  //if (std::fabs(time - fTime0) > TimeWindow) return;

  //G4cout<<"edep in event ="<<edep<<"ivol ="<<iVol<<G4endl;
  if (iVol == 1) { fEdep1 += edep; fWeight1 += edep*weight; }
  //if (iVol == 2) { fEdep2 += edep; fWeight2 += edep*weight;}  

//G4cout<<"iVol = "<<iVol<<"\n"<<"edep = "<<fEdep1<<" feight1= "<<fWeight1<<G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* evt)
{
 G4int evtNb = evt->GetEventID(); 
 //printing survey
 //
 if (evtNb%fPrintModulo == 0) 
   G4cout << "\n end of event " << std::setw(6) << evtNb 
          << " :" + fDecayChain << G4endl;
//////////////////////////////////////////////////////////////////////////////////
G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

 // pulse height in detector
    
 if (fEdep1 > 0.) {
   fWeight1 /= fEdep1;
   analysisManager->FillH1(0, fEdep1, fWeight1); //G4cout<<"fedep1 = "<<fEdep1<<G4endl;
 }


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


