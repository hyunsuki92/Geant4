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
/// \file radioactivedecay/rdecay01/src/PhysicsList.cc
/// \brief Implementation of the PhysicsList class
//
//
// $Id: PhysicsList.cc 78307 2013-12-11 10:55:57Z gcosmo $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PhysicsList.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
////////////////////////////////////added////////////////
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4HadronPhysicsINCLXX.hh"
#include "G4IonElasticPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4IonINCLXXPhysics.hh"
#include "GammaPhysics.hh"
// particles

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
//physics

#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4RayleighScattering.hh"
#include "G4KleinNishinaModel.hh"

#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuMultipleScattering.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"

#include "G4ionIonisation.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4NuclearStopping.hh"

#include "G4EmProcessOptions.hh"
#include "G4MscStepLimitType.hh"

////////////////////////////////////////////////////////////////////
#include "G4ParticleTypes.hh"
#include "G4IonConstructor.hh"

#include "G4RadioactiveDecay.hh"

#include "G4PhysicsListHelper.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4LossTableManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::PhysicsList()
: //G4VUserPhysicsList(), 
G4VModularPhysicsList()
{
  //add new units for radioActive decays
  // 
  const G4double minute = 60*second;
  const G4double hour   = 60*minute;
  const G4double day    = 24*hour;
  const G4double year   = 365*day;
  new G4UnitDefinition("minute", "min", "Time", minute);
  new G4UnitDefinition("hour",   "h",   "Time", hour);
  new G4UnitDefinition("day",    "d",   "Time", day);
  new G4UnitDefinition("year",   "y",   "Time", year);   

//////////////////////////added///////////////////////////////
  G4int verb = 1;
  SetVerboseLevel(verb); 
 
  // EM physics
  RegisterPhysics(new G4EmStandardPhysics());
  
  // Decay
  RegisterPhysics(new G4DecayPhysics());

  // Radioactive decay
  RegisterPhysics(new G4RadioactiveDecayPhysics());
            
  // Hadron Elastic scattering
  RegisterPhysics( new G4HadronElasticPhysicsHP(verb) );
  
  // Hadron Inelastic physics
  RegisterPhysics( new G4HadronPhysicsFTFP_BERT_HP(verb));
  //RegisterPhysics( new G4HadronPhysicsQGSP_BIC_HP(verb));
  //RegisterPhysics( new G4HadronInelasticQBBC(verb));        
  //RegisterPhysics( new G4HadronPhysicsINCLXX(verb));
  
  // Ion Elastic scattering
  RegisterPhysics( new G4IonElasticPhysics(verb));
      
  // Ion Inelastic physics
  RegisterPhysics( new G4IonPhysics(verb));
  ////RegisterPhysics( new G4IonINCLXXPhysics(verb));
    
  // Gamma-Nuclear Physics
  RegisterPhysics( new GammaPhysics("gamma"));     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::~PhysicsList()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructParticle()
{
//////////////////////////////////added/////////////////////////////////////
  G4BosonConstructor  pBosonConstructor;
  pBosonConstructor.ConstructParticle();

  G4LeptonConstructor pLeptonConstructor;
  pLeptonConstructor.ConstructParticle();

  G4MesonConstructor pMesonConstructor;
  pMesonConstructor.ConstructParticle();

  G4BaryonConstructor pBaryonConstructor;
  pBaryonConstructor.ConstructParticle();

  G4IonConstructor pIonConstructor;
  pIonConstructor.ConstructParticle();

  G4ShortLivedConstructor pShortLivedConstructor;
  pShortLivedConstructor.ConstructParticle();  
////////////////////////////////////////////////////////////////////////////////
/*
  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  
  // gamma
  G4Gamma::GammaDefinition();

  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();

  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  
  // baryons
  G4Proton::ProtonDefinition();
  G4Neutron::NeutronDefinition();  

  // ions
  G4IonConstructor iConstructor;
  iConstructor.ConstructParticle();  
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructProcess()
{
  AddTransportation();
  
  G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();

  radioactiveDecay->SetICM(true);                //Internal Conversion
  radioactiveDecay->SetARM(false);               //Atomic Rearangement
  
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();  
  ph->RegisterProcess(radioactiveDecay, G4GenericIon::GenericIon());
  /////////////////////////////////added////////////////////////////////////////////
     theParticleIterator->reset();
while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4String particleName = particle->GetParticleName();
     
    if (particleName == "gamma") {

      ph->RegisterProcess(new G4PhotoElectricEffect, particle);      
      ph->RegisterProcess(new G4ComptonScattering,   particle);
      ph->RegisterProcess(new G4GammaConversion,     particle);
       
    } else if (particleName == "e-") {
    
      ph->RegisterProcess(new G4eMultipleScattering(), particle);
      ph->RegisterProcess(new G4eIonisation,           particle);
      ph->RegisterProcess(new G4eBremsstrahlung(),     particle);      
            
    } else if (particleName == "e+") {
    
      ph->RegisterProcess(new G4eMultipleScattering(), particle);
      ph->RegisterProcess(new G4eIonisation,           particle);
      ph->RegisterProcess(new G4eBremsstrahlung(),     particle);
      ph->RegisterProcess(new G4eplusAnnihilation(),   particle);    
                  
    } else if (particleName == "mu+" || 
               particleName == "mu-"    ) {

      ph->RegisterProcess(new G4MuMultipleScattering(), particle);
      ph->RegisterProcess(new G4MuIonisation,           particle);
      ph->RegisterProcess(new G4MuBremsstrahlung(),     particle);
      ph->RegisterProcess(new G4MuPairProduction(),     particle);
                   
    } else if( particleName == "proton" ||
               particleName == "pi-" ||
               particleName == "pi+"    ) {

      ph->RegisterProcess(new G4hMultipleScattering(), particle);      
      ph->RegisterProcess(new G4hIonisation,           particle);
     
    } else if( particleName == "alpha" || 
               particleName == "He3"    ) {

      ph->RegisterProcess(new G4hMultipleScattering(), particle);           
      ph->RegisterProcess(new G4ionIonisation,         particle);
      ph->RegisterProcess(new G4NuclearStopping(),     particle);      
            
    } else if( particleName == "GenericIon" ) {

      ph->RegisterProcess(new G4hMultipleScattering(), particle);          
      G4ionIonisation* ionIoni = new G4ionIonisation();
      ionIoni->SetEmModel(new G4IonParametrisedLossModel());
      ph->RegisterProcess(ionIoni,                    particle);
      ph->RegisterProcess(new G4NuclearStopping(),    particle);
      //ph->RegisterProcess(new G4radioactiveDecay(),   particle);

    } else if ((!particle->IsShortLived()) &&
               (particle->GetPDGCharge() != 0.0) && 
               (particle->GetParticleName() != "chargedgeantino")) {
               
      //all others charged particles except geantino
      ph->RegisterProcess(new G4hMultipleScattering(), particle);
      ph->RegisterProcess(new G4hIonisation(),         particle);
    }
  }
  // Em options
  //
  // Main options and setting parameters are shown here.
  // Several of them have default values.
  
  G4EmProcessOptions emOptions;
  
  //ionisation
  //
  emOptions.SetStepFunction(1., 1*mm);  //default= 0.1, 100*um

////////////////////////////////////////////////////////////////////////////////////////
   /*   ph->RegisterProcess(new G4PhotoElectricEffect, G4Gamma::Gamma());      
      ph->RegisterProcess(new G4ComptonScattering,   G4Gamma::Gamma());
      ph->RegisterProcess(new G4GammaConversion,     G4Gamma::Gamma());


      ph->RegisterProcess(new G4eMultipleScattering(), G4Electron::Electron());
      ph->RegisterProcess(new G4eIonisation,           G4Electron::Electron());
      ph->RegisterProcess(new G4eBremsstrahlung(),     G4Electron::Electron());      
    
      ph->RegisterProcess(new G4eMultipleScattering(), G4Positron::Positron());
      ph->RegisterProcess(new G4eIonisation,           G4Positron::Positron());
      ph->RegisterProcess(new G4eBremsstrahlung(),     G4Positron::Positron());
      ph->RegisterProcess(new G4eplusAnnihilation(),   G4Positron::Positron());
    */
//////////////////////////////////////////////////////////////////////////////////////////

  // Deexcitation (in case of Atomic Rearangement)
  //
  G4UAtomicDeexcitation* de = new G4UAtomicDeexcitation();
  de->SetFluo(true);
  de->SetAuger(true);   
  de->SetPIXE(false);  
  G4LossTableManager::Instance()->SetAtomDeexcitation(de);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetCuts()
{
  SetCutsWithDefault();/*
  SetCutValue(0*mm, "proton");
  SetCutValue(1*km, "e-");
  SetCutValue(1*km, "e+");
  SetCutValue(1*km, "gamma");
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
