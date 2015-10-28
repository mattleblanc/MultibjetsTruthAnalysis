#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <MultibjetsTruthAnalysis/TruthAnalysis.h>

#include "xAODRootAccess/tools/Message.h"

#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"

#include "xAODEventInfo/EventInfo.h"

#include "xAODTruth/TruthEventContainer.h"
#include "xAODMissingET/MissingETContainer.h"
#include "xAODMissingET/MissingETAuxContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthParticleAuxContainer.h"


#include "xAODBase/IParticleHelpers.h"
#include "AthContainers/ConstDataVector.h"

#include <xAODJetReclustering/JetReclusteringTool.h>

#include "TRandom3.h"

/// Helper macro for checking xAOD::TReturnCode return values
#define EL_RETURN_CHECK( CONTEXT, EXP )                     \
   do {                                                     \
      if( ! EXP.isSuccess() ) {                             \
         Error( CONTEXT,                                    \
                XAOD_MESSAGE( "Failed to execute: %s" ),    \
                #EXP );                                     \
         return EL::StatusCode::FAILURE;                    \
      }                                                     \
   } while( false )

#define MEV 1000

// this is needed to distribute the algorithm to the workers
ClassImp(TruthAnalysis)



TruthAnalysis :: TruthAnalysis ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
}



EL::StatusCode TruthAnalysis :: setupJob (EL::Job& job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.

  job.useXAOD ();
  EL_RETURN_CHECK( "setupJob()", xAOD::Init() ); // call before opening first file

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthAnalysis :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthAnalysis :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthAnalysis :: changeInput (bool firstFile)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthAnalysis :: initialize ()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.

  m_event = wk()->xaodEvent(); // you should have already added this as described before

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthAnalysis :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  // TODO: Seed this properly
  TRandom3* myRand = new TRandom3();

  const xAOD::JetContainer* TruthJets = 0;
  EL_RETURN_CHECK("Get jets", m_event->retrieve( TruthJets, "AntiKt4TruthJets" ) );
  
  static SG::AuxElement::ConstAccessor< int > GhostBHadrons("GhostBHadronsFinalCount");
  static SG::AuxElement::ConstAccessor< int > GhostCHadrons("GhostCHadronsFinalCount");
  
  static SG::AuxElement::ConstAccessor< float > Tau2("Tau2_wta");
  static SG::AuxElement::ConstAccessor< float > Tau3("Tau3_wta");

  ConstDataVector<xAOD::JetContainer> * SelectedJets   =  new ConstDataVector<xAOD::JetContainer>(SG::VIEW_ELEMENTS);
  ConstDataVector<xAOD::JetContainer> * SelectedBJets  =  new ConstDataVector<xAOD::JetContainer>(SG::VIEW_ELEMENTS);

  int TruthBNum = 0;

  for(const auto jet : *TruthJets){
    if(fabs(jet->eta()) < 2.8 && jet->pt() / MEV > 20.){
      SelectedJets->push_back(jet);
    }


    // handle b-jets now

    if(fabs(jet->eta()) > 2.5 || jet->pt() / MEV < 20.){
      continue;
    }
    bool HasB = (GhostBHadrons(*jet) >= 1);
    bool HasC = (GhostCHadrons(*jet) >= 1);
    // Should we look at taus as well?

    if(HasB)
      TruthBNum++;

    if(HasB){
      double randB = myRand->Rndm();
      if(randB <= 0.85){
        // then it counts as a B
        SelectedBJets->push_back(jet);
      }
    }
    else if(HasC){
      double randC = myRand->Rndm();
      if(randC < 0.38){
        // then it counts as a B still
        SelectedBJets->push_back(jet);
      }
    }
    else{ // it's a light jet in truth
      double randL = myRand->Rndm();
      if(randL < 0.036){
        SelectedBJets->push_back(jet);
      }
    }
  }

  // std::cout << " Measured " << SelectedBJets->size() << " truth number " << TruthBNum << std::endl;

  const xAOD::JetContainer* TruthLargeJets = 0;
  EL_RETURN_CHECK("Get jets", m_event->retrieve( TruthLargeJets, "TrimmedAntiKt10TruthJets" ) ); 
  ConstDataVector<xAOD::JetContainer> * SelectedLargeJets   =  new ConstDataVector<xAOD::JetContainer>(SG::VIEW_ELEMENTS);
  ConstDataVector<xAOD::JetContainer> * TaggedLargeJets     =  new ConstDataVector<xAOD::JetContainer>(SG::VIEW_ELEMENTS);

  for(const auto jet : *TruthLargeJets){
    if(fabs(jet->eta()) < 1.6 && jet->pt() / MEV > 300.){
      SelectedLargeJets->push_back(jet);

      float Tau32 = Tau3(*jet) / Tau2(*jet);
      bool TopTagged = false;

      //now tag
      if(jet->pt() / MEV < 500.){
        if(Tau32 < 0.77 && jet->m() / MEV > 75.){
          TopTagged = true;
        }
      }
      else{ // high pt region
        if(Tau32 < 0.69 && jet->m() / MEV > 71.){
          TopTagged = true;
        }
      }

      if(TopTagged){
        TaggedLargeJets->push_back(jet);
      }
    }
  }

    // else if (taggingShortCut == "FixedCut_LowPt_50") {
    //   return configSubstTagger(tagname, std::vector<std::string>{ "102000<m" , "Tau32_wta<0.64" } );
    // }                                   
    // else if (taggingShortCut == "FixedCut_LowPt_80") {
    //   return configSubstTagger(tagname, std::vector<std::string>{ "75000<m" , "Tau32_wta<0.77" } );
      
    // }                                   
    // else if (taggingShortCut == "FixedCut_HighPt_50") {
    //   return configSubstTagger(tagname, std::vector<std::string>{ "120000<m" , "Tau32_wta<0.57" } );
    // }                                   
    // else if (taggingShortCut == "FixedCut_HighPt_80") {
    //   return configSubstTagger(tagname, std::vector<std::string>{ "71000<m" , "Tau32_wta<0.69" } );      
    // }    


  const xAOD::TruthParticleContainer* TruthElectrons = 0;
  EL_RETURN_CHECK("Get electrons", m_event->retrieve( TruthElectrons, "TruthElectrons" ) );

  
  // check pt cut on leptons; susytools defaults to 10.
  ConstDataVector<xAOD::TruthParticleContainer> * SignalElectrons    =  new ConstDataVector<xAOD::TruthParticleContainer>(SG::VIEW_ELEMENTS);
  ConstDataVector<xAOD::TruthParticleContainer> * BaselineElectrons  =  new ConstDataVector<xAOD::TruthParticleContainer>(SG::VIEW_ELEMENTS);
  for(const auto electron : *TruthElectrons){
    if(fabs(electron->eta()) < 2.47 && electron->pt() / MEV > 20.){
      SignalElectrons->push_back(electron);
    }
    if(fabs(electron->eta()) < 2.47 && electron->pt() / MEV > 10.){
      BaselineElectrons->push_back(electron);
    }
  }


  const xAOD::TruthParticleContainer* TruthMuons = 0;
  EL_RETURN_CHECK("Get muons", m_event->retrieve( TruthMuons, "TruthMuons" ) );

  // check pt cut on leptons; susytools defaults to 10.
  ConstDataVector<xAOD::TruthParticleContainer> * SignalMuons    =  new ConstDataVector<xAOD::TruthParticleContainer>(SG::VIEW_ELEMENTS);
  ConstDataVector<xAOD::TruthParticleContainer> * BaselineMuons  =  new ConstDataVector<xAOD::TruthParticleContainer>(SG::VIEW_ELEMENTS);
  for(const auto muon : *TruthMuons){
    if(fabs(muon->eta()) < 2.5 && muon->pt() / MEV > 20.){
      SignalMuons->push_back(muon);
    }
    if(fabs(muon->eta()) < 2.5 && muon->pt() / MEV > 10.){
      BaselineMuons->push_back(muon);
    }
  }


  const xAOD::MissingETContainer* TruthMET = 0;
  EL_RETURN_CHECK("Get MET", m_event->retrieve( TruthMET, "MET_Truth" ) );

  xAOD::MissingETContainer::const_iterator TruthMET_it = TruthMET->find("NonInt");
  if (TruthMET_it == TruthMET->end()) std::cout << "No NonINT inside MET container" << std::endl;
  xAOD::MissingET* TruthMET_NonInt = *TruthMET_it;


  int NSignalElectrons = SignalElectrons->size();
  int NSignalMuons     = SignalMuons->size();
  int NBaseElectrons   = BaselineElectrons->size();
  int NBaseMuons       = BaselineMuons->size();

  int NSignalLeptons   = NSignalElectrons + NSignalMuons;
  int NBaseLeptons     = NBaseElectrons + NBaseMuons;




  // 1 lepton region
  if(NSignalLeptons == 1){

  }


  // 0 lepton region
  if(NBaseLeptons == 0){

  }



  
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthAnalysis :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthAnalysis :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthAnalysis :: histFinalize ()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.
  return EL::StatusCode::SUCCESS;
}
