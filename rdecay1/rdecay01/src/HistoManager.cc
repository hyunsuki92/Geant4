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
//
// $Id: HistoManager.cc 72249 2013-07-12 08:57:49Z gcosmo $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#include "HistoManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
  : fFileName("rdecay01")
{
  Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;
  
  analysisManager->SetFileName(fFileName);
  analysisManager->SetVerboseLevel(1);
//  analysisManager->SetNtupleMerging(true);
/*  analysisManager->SetActivation(true);     //enable inactivation of histograms

*/
//histograms

 analysisManager->SetActivation(true);     //enable inactivation of histograms

 // Default values (to be reset via /analysis/h1/set command)               

  G4int nbins = 100;
  G4double vmin = 0.;
  G4double vmax = 100.;
  
  G4int id = analysisManager->CreateH1("h0","Energy deposit (keV) in the Detector",
                       nbins, vmin, vmax);

analysisManager->SetH1Activation(id, false);

  id = analysisManager->CreateH1("h1","gamma energy (keV)",
                       nbins, vmin, vmax);
analysisManager->SetH1Activation(id, false);

// ntuples
/*
  analysisManager->CreateNtuple("t1", "Particle ID=1");//id=0 
  analysisManager->CreateNtupleIColumn("PID");  //column 0
  analysisManager->CreateNtupleIColumn("Z");    //column 1:
  analysisManager->CreateNtupleIColumn("A");    //column 2
  analysisManager->CreateNtupleDColumn("Ekin"); //column 3
  analysisManager->CreateNtupleDColumn("time"); //4
  analysisManager->CreateNtupleDColumn("weight"); //5
  analysisManager->FinishNtuple();
*/
//  analysisManager->SetNtupleActivation(false); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
