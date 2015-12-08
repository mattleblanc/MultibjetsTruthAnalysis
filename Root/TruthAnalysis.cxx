#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>

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

#include <MultibjetsTruthAnalysis/TruthAnalysis.h>

#include "TRandom3.h"
#include "TFile.h"
#include "TSystem.h"

// chiara: including the TRF package
#include <BtaggingTRFandRW/TRFinterface.h>

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

#define MEV 1000.0

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

  out_tree = new TTree("out_tree", "output tree");
  out_cutflow = new TH1F("out_cutflow", "output cutflow",20,1,21);
  // chiara: initialize TRF tool
  const std::string pathToConf = gSystem->Getenv("ROOTCOREBIN");
  m_TRF = new TRFinterface(pathToConf+"/data/BtaggingTRFandRW/calibConfig_MultiBTrurh_MV2c20_v1.txt",-0.7887,"AntiKt4EMTopoJets");
  m_probTag = true;
  m_myRand = new TRandom3();


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

  // outputs
  EL::OutputStream outTree ("outTree");
  job.outputAdd (outTree);

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

  m_all_events = 1;
  mc_channel=-1;
  mc_weight=0.0;
  isPreselect_Gbb=false;
  isPreselect_Gtt_1l=false;
  isPreselect_Gtt_0l=false;
  isPreselect=false;
  isGbbSRA1=false;
  isGbbSRB1=false;
  isGbbSRA2=false;
  isGbbSRB2=false;
  isGbbSRC2=false;
  isGbbSRA4=false;
  isGbbSRB4=false;
  isGtt1LSRA2=false;
  isGtt1LSRB2=false;
  isGtt1LSRC2=false;
  isGtt1LSRA4=false;
  isGtt1LSRB4=false;
  isGtt1LSRC4=false;
  isGtt0LSRA=false;
  isGtt0LSRB=false;
  isGtt0LSRC=false;
  isGtt0LSRD=false;
  isGbbCRA2 = 0;
  isGbbCRB2 = 0;
  isGbbCRC2 = 0;
  isGbbCRA4 = 0;
  isGbbCRB4 = 0;
  isGtt1LCRA2 = 0;
  isGtt1LCRB2 = 0;
  isGtt1LCRC2 = 0;
  isGtt1LCRA4 = 0;
  isGtt1LCRB4 = 0;
  isGtt1LCRC4 = 0;
  isGtt0LCRA = 0;
  isGtt0LCRB = 0;
  isGtt0LCRC = 0;
  isGtt0LCRD = 0;

  isGbbVRI2 = 0;
  isGbbVRII2 = 0;
  isGbbVRIII2 = 0;
  isGbbVRI4 = 0;
  isGbbVRII4 = 0;
  isVR1LGtt0LI = 0;
  isVR1LGtt0LII = 0;
  isVR1LGtt0LIII = 0;
  isVR1LGtt0LIV = 0;
  isVR0LGtt0LI = 0;
  isVR0LGtt0LII = 0;
  isVR0LGtt0LIII = 0;
  isVR0LGtt0LIV = 0;
  isVRGtt1LI2mT2b = 0;
  isVRGtt1LII2mT2b = 0;
  isVRGtt1LI4mT2b = 0;
  isVRGtt1LII4mT2b = 0;
  isVRGtt1LI2mT3b = 0;
  isVRGtt1LII2mT3b = 0;
  isVRGtt1LI4mT3b = 0; 
  isVRGtt1LII4mT3b = 0;
  isVRGtt1LI2mTb2b = 0;
  isVRGtt1LII2mTb2b = 0;
  isVRGtt1LI4mTb2b = 0;
  isVRGtt1LII4mTb2b = 0;
  isVRGtt1LI2mTb3b = 0;
  isVRGtt1LII2mTb3b = 0;
  isVRGtt1LI4mTb3b = 0;
  isVRGtt1LII4mTb3b = 0;
  isVRGtt1LI2mT4b = 0;
  isVRGtt1LII2mT4b = 0;
  isVRGtt1LIII22b = 0;
  isVRGtt1LIII42b = 0;
  isVRGtt1LIII23b = 0;
  isVRGtt1LIII43b = 0;
  isVRGtt1LIII24b = 0;
  isVRGtt1LIII44b = 0;

  var_dPhiMin = 0;
  var_Meff = 0;
  var_Meff_4j = 0;
  var_mT = 0;
  var_mTb = 0;
  var_HT = 0;
  var_Met = 0;
  var_MetSig = 0;

  var_rcjet_pt_1 = 0;
  var_rcjet_pt_2 = 0;
  var_rcjet_pt_3 = 0;
  var_rcjet_pt_4 = 0;
  var_rcjet_eta_1 = 0;
  var_rcjet_eta_2 = 0;
  var_rcjet_eta_3 = 0;
  var_rcjet_eta_4 = 0;
  var_rcjet_phi_1 = 0;
  var_rcjet_phi_2 = 0;
  var_rcjet_phi_3 = 0;
  var_rcjet_phi_4 = 0;
  var_rcjet_mass_1 = 0;
  var_rcjet_mass_2 = 0;
  var_rcjet_mass_3 = 0;
  var_rcjet_mass_4 = 0;

  var_bjet_pt_1 = 0;
  var_bjet_pt_2 = 0;
  var_bjet_pt_3 = 0;
  var_bjet_pt_4 = 0;
  var_bjet_eta_1 = 0;
  var_bjet_eta_2 = 0;
  var_bjet_eta_3 = 0;
  var_bjet_eta_4 = 0;
  var_bjet_phi_1 = 0;
  var_bjet_phi_2 = 0;
  var_bjet_phi_3 = 0;
  var_bjet_phi_4 = 0;
  var_bjet_e_1 = 0;
  var_bjet_e_2 = 0;
  var_bjet_e_3 = 0;
  var_bjet_e_4 = 0;

  var_jet_pt_1 = 0;
  var_jet_pt_2 = 0;
  var_jet_pt_3 = 0;
  var_jet_pt_4 = 0;
  var_jet_eta_1 = 0;
  var_jet_eta_2 = 0;
  var_jet_eta_3 = 0;
  var_jet_eta_4 = 0;
  var_jet_phi_1 = 0;
  var_jet_phi_2 = 0;
  var_jet_phi_3 = 0;
  var_jet_phi_4 = 0;
  var_jet_e_1 = 0;
  var_jet_e_2 = 0;
  var_jet_e_3 = 0;
  var_jet_e_4 = 0;

  var_mu_pt = 0;
  var_mu_eta = 0;
  var_mu_phi = 0;
  var_mu_e = 0;

  var_el_pt = 0;
  var_el_eta = 0;
  var_el_phi = 0;
  var_el_e = 0;

  NSignalElectrons = 0;
  NSignalMuons = 0;
  NBaseElectrons = 0;
  NBaseMuons = 0;
  NJets = 0;
  NBJets = 0;
  NBJets_TRF = 0;
  NTopJets = 0;

  NSignalLeptons = 0;
  NBaseLeptons = 0;

  m_isTRF = false;
  m_isTRF_incl = false;

  m_TRF_wgt = 0;

  m_TRFweight_2excl = 0.;              
  m_TRFweight_2incl = 0.; 
  m_TRFweight_3excl = 0.; 
  m_TRFweight_3incl = 0.; 
  m_TRFweight_4incl = 0.; 

  // chiara: clear TRF verctors (these are the ones taken as input )
  m_TRFweight_in.clear();
  m_TRFweight_ex.clear();
  m_TRFPerm_in.clear();
  m_TRFPerm_ex.clear();
  m_jets_isb_85_TRF_2excl.clear();
  m_jets_isb_85_TRF_2incl.clear();
  m_jets_isb_85_TRF_3excl.clear();
  m_jets_isb_85_TRF_3incl.clear();
  m_jets_isb_85_TRF_4incl.clear();


  //TTree* out_tree; out_tree = new TTree("out_tree","output tree");
  TFile *file = wk()->getOutputFile ("outTree");
  out_tree->SetDirectory(file);
  out_cutflow->SetDirectory(file);
  
  out_tree->Branch("all_events",&m_all_events,"all_events/I");
  out_tree->Branch("mc_channel",&mc_channel,"mc_channel/I");
  out_tree->Branch("mc_weight",&mc_weight,"mc_weight/F");
  out_tree->Branch("isPreselect_Gbb",&isPreselect_Gbb,"isPreselect_Gbb/I");
  out_tree->Branch("isPreselect_Gtt_1l",&isPreselect_Gtt_1l,"isPreselect_Gtt_1l/I");
  out_tree->Branch("isPreselect_Gtt_0l",&isPreselect_Gtt_0l,"isPreselect_Gtt_0l/I");
  out_tree->Branch("isPreselect",&isPreselect,"isPreselect/I");
  out_tree->Branch("isGbbSRA1",&isGbbSRA1,"isGbbSRA1/I");
  out_tree->Branch("isGbbSRB1",&isGbbSRB1,"isGbbSRB1/I");
  out_tree->Branch("isGbbSRA2",&isGbbSRA2,"isGbbSRA2/I");
  out_tree->Branch("isGbbSRB2",&isGbbSRB2,"isGbbSRB2/I");
  out_tree->Branch("isGbbSRC2",&isGbbSRC2,"isGbbSRC2/I");
  out_tree->Branch("isGbbSRA4",&isGbbSRA4,"isGbbSRA4/I");
  out_tree->Branch("isGbbSRB4",&isGbbSRB4,"isGbbSRB4/I");
  out_tree->Branch("isGtt1LSRA2",&isGtt1LSRA2,"isGtt1LSRA2/I");
  out_tree->Branch("isGtt1LSRB2",&isGtt1LSRB2,"isGtt1LSRB2/I");
  out_tree->Branch("isGtt1LSRC2",&isGtt1LSRC2,"isGtt1LSRC2/I");
  out_tree->Branch("isGtt1LSRA4",&isGtt1LSRA4,"isGtt1LSRA4/I");
  out_tree->Branch("isGtt1LSRB4",&isGtt1LSRB4,"isGtt1LSRB4/I");
  out_tree->Branch("isGtt1LSRC4",&isGtt1LSRC4,"isGtt1LSRC4/I");
  out_tree->Branch("isGtt0LSRA",&isGtt0LSRA,"isGtt0LSRA/I");
  out_tree->Branch("isGtt0LSRB",&isGtt0LSRB,"isGtt0LSRB/I");
  out_tree->Branch("isGtt0LSRC",&isGtt0LSRC,"isGtt0LSRC/I");
  out_tree->Branch("isGtt0LSRD",&isGtt0LSRD,"isGtt0LSRD/I");

  out_tree->Branch("isGbbCRA2",&isGbbCRA2,"isGbbCRA2/I");
  out_tree->Branch("isGbbCRB2",&isGbbCRB2,"isGbbCRB2/I");
  out_tree->Branch("isGbbCRC2",&isGbbCRC2,"isGbbCRC2/I");
  out_tree->Branch("isGbbCRA4",&isGbbCRA4,"isGbbCRA4/I");
  out_tree->Branch("isGbbCRB4",&isGbbCRB4,"isGbbCRB4/I");
  out_tree->Branch("isGtt1LCRA2",&isGtt1LCRA2,"isGtt1LCRA2/I");
  out_tree->Branch("isGtt1LCRB2",&isGtt1LCRB2,"isGtt1LCRB2/I");
  out_tree->Branch("isGtt1LCRC2",&isGtt1LCRC2,"isGtt1LCRC2/I");
  out_tree->Branch("isGtt1LCRA4",&isGtt1LCRA4,"isGtt1LCRA4/I");
  out_tree->Branch("isGtt1LCRB4",&isGtt1LCRB4,"isGtt1LCRB4/I");
  out_tree->Branch("isGtt1LCRC4",&isGtt1LCRC4,"isGtt1LCRC4/I");
  out_tree->Branch("isGtt0LCRA",&isGtt0LCRA,"isGtt0LCRA/I");
  out_tree->Branch("isGtt0LCRB",&isGtt0LCRB,"isGtt0LCRB/I");
  out_tree->Branch("isGtt0LCRC",&isGtt0LCRC,"isGtt0LCRC/I");
  out_tree->Branch("isGtt0LCRD",&isGtt0LCRD,"isGtt0LCRD/I");

  out_tree->Branch("isGbbVRI2",&isGbbVRI2,"isGbbVRI2/I");
  out_tree->Branch("isGbbVRII2",&isGbbVRII2,"isGbbVRII2/I");
  out_tree->Branch("isGbbVRIII2",&isGbbVRIII2,"isGbbVRIII2/I");
  out_tree->Branch("isGbbVRI4",&isGbbVRI4,"isGbbVRI4/I");
  out_tree->Branch("isGbbVRII4",&isGbbVRII4,"isGbbVRII4/I");
  out_tree->Branch("isVR1LGtt0LI",&isVR1LGtt0LI,"isVR1LGtt0LI/I");
  out_tree->Branch("isVR1LGtt0LII",&isVR1LGtt0LII,"isVR1LGtt0LII/I");
  out_tree->Branch("isVR1LGtt0LIII",&isVR1LGtt0LIII,"isVR1LGtt0LIII/I");
  out_tree->Branch("isVR1LGtt0LIV",&isVR1LGtt0LIV,"isVR1LGtt0LIV/I");
  out_tree->Branch("isVR0LGtt0LI",&isVR0LGtt0LI,"isVR0LGtt0LI/I");
  out_tree->Branch("isVR0LGtt0LII",&isVR0LGtt0LII,"isVR0LGtt0LII/I");
  out_tree->Branch("isVR0LGtt0LIII",&isVR0LGtt0LIII,"isVR0LGtt0LIII/I");
  out_tree->Branch("isVR0LGtt0LIV",&isVR0LGtt0LIV,"isVR0LGtt0LIV/I");
  out_tree->Branch("isVRGtt1LI2mT2b",&isVRGtt1LI2mT2b,"isVRGtt1LI2mT2b/I");
  out_tree->Branch("isVRGtt1LII2mT2b",&isVRGtt1LII2mT2b,"isVRGtt1LII2mT2b/I");
  out_tree->Branch("isVRGtt1LI4mT2b",&isVRGtt1LI4mT2b,"isVRGtt1LI4mT2b/I");
  out_tree->Branch("isVRGtt1LII4mT2b",&isVRGtt1LII4mT2b,"isVRGtt1LII4mT2b/I");
  out_tree->Branch("isVRGtt1LI2mT3b",&isVRGtt1LI2mT3b,"isVRGtt1LI2mT3b/I");
  out_tree->Branch("isVRGtt1LII2mT3b",&isVRGtt1LII2mT3b,"isVRGtt1LII2mT3b/I");
  out_tree->Branch("isVRGtt1LI4mT3b",&isVRGtt1LI4mT3b,"isVRGtt1LI4mT3b/I"); 
  out_tree->Branch("isVRGtt1LII4mT3b",&isVRGtt1LII4mT3b,"isVRGtt1LII4mT3b/I");
  out_tree->Branch("isVRGtt1LI2mTb2b",&isVRGtt1LI2mTb2b,"isVRGtt1LI2mTb2b/I");
  out_tree->Branch("isVRGtt1LII2mTb2b",&isVRGtt1LII2mTb2b,"isVRGtt1LII2mTb2b/I");
  out_tree->Branch("isVRGtt1LI4mTb2b",&isVRGtt1LI4mTb2b,"isVRGtt1LI4mTb2b/I");
  out_tree->Branch("isVRGtt1LII4mTb2b",&isVRGtt1LII4mTb2b,"isVRGtt1LII4mTb2b/I");
  out_tree->Branch("isVRGtt1LI2mTb3b",&isVRGtt1LI2mTb3b,"isVRGtt1LI2mTb3b/I");
  out_tree->Branch("isVRGtt1LII2mTb3b",&isVRGtt1LII2mTb3b,"isVRGtt1LII2mTb3b/I");
  out_tree->Branch("isVRGtt1LI4mTb3b",&isVRGtt1LI4mTb3b,"isVRGtt1LI4mTb3b/I");
  out_tree->Branch("isVRGtt1LII4mTb3b",&isVRGtt1LII4mTb3b,"isVRGtt1LII4mTb3b/I");
  out_tree->Branch("isVRGtt1LI2mT4b",&isVRGtt1LI2mT4b,"isVRGtt1LI2mT4b/I");
  out_tree->Branch("isVRGtt1LII2mT4b",&isVRGtt1LII2mT4b,"isVRGtt1LII2mT4b/I");
  out_tree->Branch("isVRGtt1LIII22b",&isVRGtt1LIII22b,"isVRGtt1LIII22b/I");
  out_tree->Branch("isVRGtt1LIII42b",&isVRGtt1LIII42b,"isVRGtt1LIII42b/I");
  out_tree->Branch("isVRGtt1LIII23b",&isVRGtt1LIII23b,"isVRGtt1LIII23b/I");
  out_tree->Branch("isVRGtt1LIII43b",&isVRGtt1LIII43b,"isVRGtt1LIII43b/I");
  out_tree->Branch("isVRGtt1LIII24b",&isVRGtt1LIII24b,"isVRGtt1LIII24b/I");
  out_tree->Branch("isVRGtt1LIII44b",&isVRGtt1LIII44b,"isVRGtt1LIII44b/I");

  out_tree->Branch("var_dPhiMin",&var_dPhiMin, "var_dPhiMin/F");
  out_tree->Branch("var_Meff",&var_Meff, "var_Meff/F");
  out_tree->Branch("var_Meff_4j",&var_Meff_4j, "var_Meff_4j/F");
  out_tree->Branch("var_mT",&var_mT, "var_mT/F");
  out_tree->Branch("var_mTb",&var_mTb, "var_mTb/F");
  out_tree->Branch("var_HT",&var_HT, "var_HT/F");
  out_tree->Branch("var_Met",&var_Met, "var_Met/F");
  out_tree->Branch("var_MetSig",&var_MetSig, "var_MetSig/F");

  out_tree->Branch("var_rcjet_pt_1",&var_rcjet_pt_1,"var_rcjet_pt_1/F");
  out_tree->Branch("var_rcjet_pt_2",&var_rcjet_pt_2,"var_rcjet_pt_2/F");
  out_tree->Branch("var_rcjet_pt_3",&var_rcjet_pt_3,"var_rcjet_pt_3/F");
  out_tree->Branch("var_rcjet_pt_4",&var_rcjet_pt_4,"var_rcjet_pt_4/F");
  out_tree->Branch("var_rcjet_eta_1",&var_rcjet_eta_1,"var_rcjet_eta_1/F");
  out_tree->Branch("var_rcjet_eta_2",&var_rcjet_eta_2,"var_rcjet_eta_2/F");
  out_tree->Branch("var_rcjet_eta_3",&var_rcjet_eta_3,"var_rcjet_eta_3/F");
  out_tree->Branch("var_rcjet_eta_4",&var_rcjet_eta_4,"var_rcjet_eta_4/F");
  out_tree->Branch("var_rcjet_phi_1",&var_rcjet_phi_1,"var_rcjet_phi_1/F");
  out_tree->Branch("var_rcjet_phi_2",&var_rcjet_phi_2,"var_rcjet_phi_2/F");
  out_tree->Branch("var_rcjet_phi_3",&var_rcjet_phi_3,"var_rcjet_phi_3/F");
  out_tree->Branch("var_rcjet_phi_4",&var_rcjet_phi_4,"var_rcjet_phi_4/F");
  out_tree->Branch("var_rcjet_mass_1",&var_rcjet_mass_1,"var_rcjet_mass_1/F");
  out_tree->Branch("var_rcjet_mass_2",&var_rcjet_mass_2,"var_rcjet_mass_2/F");
  out_tree->Branch("var_rcjet_mass_3",&var_rcjet_mass_3,"var_rcjet_mass_3/F");
  out_tree->Branch("var_rcjet_mass_4",&var_rcjet_mass_4,"var_rcjet_mass_4/F");

  out_tree->Branch("var_bjet_pt_1",&var_bjet_pt_1,"var_bjet_pt_1/F");
  out_tree->Branch("var_bjet_pt_2",&var_bjet_pt_2,"var_bjet_pt_2/F");
  out_tree->Branch("var_bjet_pt_3",&var_bjet_pt_3,"var_bjet_pt_3/F");
  out_tree->Branch("var_bjet_pt_4",&var_bjet_pt_4,"var_bjet_pt_4/F");
  out_tree->Branch("var_bjet_eta_1",&var_bjet_eta_1,"var_bjet_eta_1/F");
  out_tree->Branch("var_bjet_eta_2",&var_bjet_eta_2,"var_bjet_eta_2/F");
  out_tree->Branch("var_bjet_eta_3",&var_bjet_eta_3,"var_bjet_eta_3/F");
  out_tree->Branch("var_bjet_eta_4",&var_bjet_eta_4,"var_bjet_eta_4/F");
  out_tree->Branch("var_bjet_phi_1",&var_bjet_phi_1,"var_bjet_phi_1/F");
  out_tree->Branch("var_bjet_phi_2",&var_bjet_phi_2,"var_bjet_phi_2/F");
  out_tree->Branch("var_bjet_phi_3",&var_bjet_phi_3,"var_bjet_phi_3/F");
  out_tree->Branch("var_bjet_phi_4",&var_bjet_phi_4,"var_bjet_phi_4/F");
  out_tree->Branch("var_bjet_e_1",&var_bjet_e_1,"var_bjet_e_1/F");
  out_tree->Branch("var_bjet_e_2",&var_bjet_e_2,"var_bjet_e_2/F");
  out_tree->Branch("var_bjet_e_3",&var_bjet_e_3,"var_bjet_e_3/F");
  out_tree->Branch("var_bjet_e_4",&var_bjet_e_4,"var_bjet_e_4/F");

  out_tree->Branch("var_jet_pt_1",&var_jet_pt_1,"var_jet_pt_1/F");
  out_tree->Branch("var_jet_pt_2",&var_jet_pt_2,"var_jet_pt_2/F");
  out_tree->Branch("var_jet_pt_3",&var_jet_pt_3,"var_jet_pt_3/F");
  out_tree->Branch("var_jet_pt_4",&var_jet_pt_4,"var_jet_pt_4/F");
  out_tree->Branch("var_jet_eta_1",&var_jet_eta_1,"var_jet_eta_1/F");
  out_tree->Branch("var_jet_eta_2",&var_jet_eta_2,"var_jet_eta_2/F");
  out_tree->Branch("var_jet_eta_3",&var_jet_eta_3,"var_jet_eta_3/F");
  out_tree->Branch("var_jet_eta_4",&var_jet_eta_4,"var_jet_eta_4/F");
  out_tree->Branch("var_jet_phi_1",&var_jet_phi_1,"var_jet_phi_1/F");
  out_tree->Branch("var_jet_phi_2",&var_jet_phi_2,"var_jet_phi_2/F");
  out_tree->Branch("var_jet_phi_3",&var_jet_phi_3,"var_jet_phi_3/F");
  out_tree->Branch("var_jet_phi_4",&var_jet_phi_4,"var_jet_phi_4/F");
  out_tree->Branch("var_jet_e_1",&var_jet_e_1,"var_jet_e_1/F");
  out_tree->Branch("var_jet_e_2",&var_jet_e_2,"var_jet_e_2/F");
  out_tree->Branch("var_jet_e_3",&var_jet_e_3,"var_jet_e_3/F");
  out_tree->Branch("var_jet_e_4",&var_jet_e_4,"var_jet_e_4/F");

  out_tree->Branch("var_mu_pt",&var_mu_pt,"var_mu_pt/F");
  out_tree->Branch("var_mu_eta",&var_mu_eta,"var_mu_eta/F");
  out_tree->Branch("var_mu_phi",&var_mu_phi,"var_mu_phi/F");
  out_tree->Branch("var_mu_e",&var_mu_e,"var_mu_e/F");

  out_tree->Branch("var_el_pt",&var_el_pt,"var_el_pt/F");
  out_tree->Branch("var_el_eta",&var_el_eta,"var_el_eta/F");
  out_tree->Branch("var_el_phi",&var_el_phi,"var_el_phi/F");
  out_tree->Branch("var_el_e",&var_el_e,"var_el_e/F");

  out_tree->Branch("NSignalElectrons",&NSignalElectrons, "NSignalElectrons/I");
  out_tree->Branch("NSignalMuons",&NSignalMuons, "NSignalMuons/I");
  out_tree->Branch("NBaseElectrons",&NBaseElectrons, "NBaseElectrons/I");
  out_tree->Branch("NBaseMuons",&NBaseMuons, "NBaseMuons/I");
  out_tree->Branch("NJets",&NJets, "NJets/I");
  out_tree->Branch("NBJets",&NBJets, "NBJets/I");
  out_tree->Branch("NTopJets",&NTopJets, "NTopJets/I");

  out_tree->Branch("NSignalLeptons",&NSignalLeptons, "NSignalLeptons/I");
  out_tree->Branch("NBaseLeptons",&NBaseLeptons, "NBaseLeptons/I");

  if(m_probTag){

    out_tree->Branch("NBJets_TRF",&NBJets_TRF, "NBJets_TRF/I");
    out_tree->Branch("isTRF", &m_isTRF, "isTRF/O");
    out_tree->Branch("isTRF_incl", &m_isTRF_incl, "isTRF/O");
    out_tree->Branch("TRF_wgt", &m_TRF_wgt, "TRF_wgt/D");


    // chiara: this part can be removed if the variables are built all at this stage and not offline
    // chiara: it is useful to keep oit for offline caclulations only if all the elements of SelectedBJets_TRF are stored as well (keeping the ordering)
    // chiara: adding branches permutation (for each jet, is is b-tagged or not)

    out_tree->Branch("jets_isb_85_TRF_2excl", &m_out_jets_isb_85_TRF_2excl);
    out_tree->Branch("jets_isb_85_TRF_2incl", &m_out_jets_isb_85_TRF_2incl);
    out_tree->Branch("jets_isb_85_TRF_3excl", &m_out_jets_isb_85_TRF_3excl);
    out_tree->Branch("jets_isb_85_TRF_3incl", &m_out_jets_isb_85_TRF_3incl);
    out_tree->Branch("jets_isb_85_TRF_4incl", &m_out_jets_isb_85_TRF_4incl);
    // chiara: adding branches for TRFweights
    out_tree->Branch("TRFweight_2excl", &m_TRFweight_2excl);
    out_tree->Branch("TRFweight_2incl", &m_TRFweight_2incl);
    out_tree->Branch("TRFweight_3excl", &m_TRFweight_3excl);
    out_tree->Branch("TRFweight_3incl", &m_TRFweight_3incl);
    out_tree->Branch("TRFweight_4incl", &m_TRFweight_4incl);
    out_tree->Branch("TRFjets_pt", &m_out_sel_jets_pt);
    out_tree->Branch("TRFjets_eta", &m_out_sel_jets_eta);
    out_tree->Branch("TRFjets_phi", &m_out_sel_jets_phi);

  }
  /*
  if(TruthJets->empty()){
    Error("initialize()", "Cannot do reclustering if the input jet container is empty");
    return EL::StatusCode::FAILURE;
  }
  */

  // reclustering jets
  m_reclusteringTool = new JetReclusteringTool("MBJTruth_JetReclusteringTool");
  m_reclusteringTool->setProperty("InputJetContainer",  "AntiKt4TruthJets");
  m_reclusteringTool->setProperty("OutputJetContainer", "RC10TruthJets");
  m_reclusteringTool->setProperty("ReclusterRadius",    1.0);
  m_reclusteringTool->setProperty("InputJetPtMin",      10.0);
  m_reclusteringTool->setProperty("RCJetPtFrac",        0.05);
  m_reclusteringTool->initialize();

  return EL::StatusCode::SUCCESS;
}



void TruthAnalysis::processEventPerBMultiplicity(ConstDataVector<xAOD::JetContainer> * SelectedBJets, ConstDataVector<xAOD::JetContainer> * SelectedJets
						 , xAOD::MissingET* TruthMET_NonInt, bool isTRF, bool isTRF_incl, int nbjets_TRF){

  Bool_t debug = false;

  m_isTRF = isTRF;
  m_isTRF_incl = isTRF_incl;

  // Trisha: Final variables to be stored in the tree
  m_out_jets_isb_85_TRF_2excl.clear();
  m_out_jets_isb_85_TRF_2incl.clear();
  m_out_jets_isb_85_TRF_3excl.clear();
  m_out_jets_isb_85_TRF_3incl.clear();
  m_out_jets_isb_85_TRF_4incl.clear();


  m_out_sel_jets_pt.clear();
  m_out_sel_jets_eta.clear();
  m_out_sel_jets_phi.clear();

  //copying everything by value - horrible technique!
  if(!isTRF){
    m_out_jets_isb_85_TRF_2excl = m_jets_isb_85_TRF_2excl;
    m_out_jets_isb_85_TRF_2incl = m_jets_isb_85_TRF_2incl;
    m_out_jets_isb_85_TRF_3excl = m_jets_isb_85_TRF_3excl;
    m_out_jets_isb_85_TRF_3incl = m_jets_isb_85_TRF_3incl;
    m_out_jets_isb_85_TRF_4incl = m_jets_isb_85_TRF_4incl;

    m_out_sel_jets_pt = m_sel_jets_pt;
    m_out_sel_jets_eta = m_sel_jets_eta;
    m_out_sel_jets_phi = m_sel_jets_phi;
  }



  m_TRF_wgt = 1.;
  if( isTRF && (nbjets_TRF == 2) && isTRF_incl ){ m_TRF_wgt = m_TRFweight_2incl;}
  else if( isTRF && (nbjets_TRF == 2) && !isTRF_incl ){ m_TRF_wgt = m_TRFweight_2excl;}

  else if( isTRF && (nbjets_TRF == 3) && isTRF_incl ){ m_TRF_wgt = m_TRFweight_3incl;}
  else if( isTRF && (nbjets_TRF == 3) && !isTRF_incl ){ m_TRF_wgt = m_TRFweight_3excl;}

  else if( isTRF && (nbjets_TRF == 4) && isTRF_incl ){ m_TRF_wgt = m_TRFweight_4incl;}


  NBJets = SelectedBJets->size();
  NBJets_TRF = nbjets_TRF;

  //std::cout<<" isTRF = "<<isTRF<<" isTRF_incl = "<<isTRF_incl<<" NBJets = "<<NBJets<<" NBJets_TRF = "<<NBJets_TRF<<" NJets = "<<NJets<<std::endl;
  if(SelectedBJets->size()>0) var_bjet_pt_1 = SelectedBJets->at(0)->pt() / MEV;
  if(SelectedBJets->size()>1) var_bjet_pt_2 = SelectedBJets->at(1)->pt() / MEV;
  if(SelectedBJets->size()>2) var_bjet_pt_3 = SelectedBJets->at(2)->pt() / MEV;
  if(SelectedBJets->size()>3) var_bjet_pt_4 = SelectedBJets->at(3)->pt() / MEV;
  if(SelectedBJets->size()>0) var_bjet_eta_1 = SelectedBJets->at(0)->eta();
  if(SelectedBJets->size()>1) var_bjet_eta_2 = SelectedBJets->at(1)->eta();
  if(SelectedBJets->size()>2) var_bjet_eta_3 = SelectedBJets->at(2)->eta();
  if(SelectedBJets->size()>3) var_bjet_eta_4 = SelectedBJets->at(3)->eta();
  if(SelectedBJets->size()>0) var_bjet_phi_1 = SelectedBJets->at(0)->phi();
  if(SelectedBJets->size()>1) var_bjet_phi_2 = SelectedBJets->at(1)->phi();
  if(SelectedBJets->size()>2) var_bjet_phi_3 = SelectedBJets->at(2)->phi();
  if(SelectedBJets->size()>3) var_bjet_phi_4 = SelectedBJets->at(3)->phi();
  if(SelectedBJets->size()>0) var_bjet_e_1 = SelectedBJets->at(0)->e() / MEV;
  if(SelectedBJets->size()>1) var_bjet_e_2 = SelectedBJets->at(1)->e() / MEV;
  if(SelectedBJets->size()>2) var_bjet_e_3 = SelectedBJets->at(2)->e() / MEV;
  if(SelectedBJets->size()>3) var_bjet_e_4 = SelectedBJets->at(3)->e() / MEV;

  var_mTb = Variables::mT_min_bjets(TruthMET_NonInt, SelectedBJets->asDataVector(), false );

  // debug variables
  if(debug)
    {
      std::cout << "var_dPhiMin is " << var_dPhiMin << std::endl;
      std::cout << "var_Meff is " << var_Meff << std::endl;
      std::cout << "var_Meff_4j is " << var_Meff_4j << std::endl;
      std::cout << "var_mT is " << var_mT << std::endl;
      std::cout << "var_mTb is " << var_mTb << std::endl;
      std::cout << "var_HT is " << var_HT << std::endl;
      std::cout << "var_Met is " << var_Met << std::endl;
      std::cout << "var_MetSig is " << var_MetSig << std::endl;
      std::cout << "NJets is " << NJets << std::endl;
      std::cout << "NBJets is " << NBJets << std::endl;
      std::cout << "NTopJets is " << NTopJets << std::endl;
    }

  /*
    Commented lines such as 'configMgr.cutsDict*' are taken from the HistFitter config file ... it can be found here:
    https://svnweb.cern.ch/trac/atlasphys-susy/browser/Physics/SUSY/Analyses/MultiBJets/HistFitter/trunk/ananlisis_multib/python/My3bGtt.py
    ... they're just for my own reference, so don't please don't fuss about them too much.
  */

  isPreselect_Gbb=false;
  isPreselect_Gtt_1l=false;
  isPreselect_Gtt_0l=false;
  isPreselect=false;
  isGbbSRA1=false;
  isGbbSRB1=false;
  isGbbSRA2=false;
  isGbbSRB2=false;
  isGbbSRC2=false;
  isGbbSRA4=false;
  isGbbSRB4=false;
  isGtt1LSRA2=false;
  isGtt1LSRB2=false;
  isGtt1LSRC2=false;
  isGtt1LSRA4=false;
  isGtt1LSRB4=false;
  isGtt1LSRC4=false;
  isGtt0LSRA=false;
  isGtt0LSRB=false;
  isGtt0LSRC=false;
  isGtt0LSRD=false;
  isGbbCRA2 = 0;
  isGbbCRB2 = 0;
  isGbbCRC2 = 0;
  isGbbCRA4 = 0;
  isGbbCRB4 = 0;
  isGtt1LCRA2 = 0;
  isGtt1LCRB2 = 0;
  isGtt1LCRC2 = 0;
  isGtt1LCRA4 = 0;
  isGtt1LCRB4 = 0;
  isGtt1LCRC4 = 0;
  isGtt0LCRA = 0;
  isGtt0LCRB = 0;
  isGtt0LCRC = 0;
  isGtt0LCRD = 0;
  isGbbVRI2 = 0;
  isGbbVRII2 = 0;
  isGbbVRIII2 = 0;
  isGbbVRI4 = 0;
  isGbbVRII4 = 0;
  isVR1LGtt0LI = 0;
  isVR1LGtt0LII = 0;
  isVR1LGtt0LIII = 0;
  isVR1LGtt0LIV = 0;
  isVR0LGtt0LI = 0;
  isVR0LGtt0LII = 0;
  isVR0LGtt0LIII = 0;
  isVR0LGtt0LIV = 0;
  isVRGtt1LI2mT2b = 0;
  isVRGtt1LII2mT2b = 0;
  isVRGtt1LI4mT2b = 0;
  isVRGtt1LII4mT2b = 0;
  isVRGtt1LI2mT3b = 0;
  isVRGtt1LII2mT3b = 0;
  isVRGtt1LI4mT3b = 0; 
  isVRGtt1LII4mT3b = 0;
  isVRGtt1LI2mTb2b = 0;
  isVRGtt1LII2mTb2b = 0;
  isVRGtt1LI4mTb2b = 0;
  isVRGtt1LII4mTb2b = 0;
  isVRGtt1LI2mTb3b = 0;
  isVRGtt1LII2mTb3b = 0;
  isVRGtt1LI4mTb3b = 0;
  isVRGtt1LII4mTb3b = 0;
  isVRGtt1LI2mT4b = 0;
  isVRGtt1LII2mT4b = 0;
  isVRGtt1LIII22b = 0;
  isVRGtt1LIII42b = 0;
  isVRGtt1LIII23b = 0;
  isVRGtt1LIII43b = 0;
  isVRGtt1LIII24b = 0;
  isVRGtt1LIII44b = 0;

  bool doMCNLO=true;

  bool pass2bexcl = (NBJets == 2) && (!isTRF || ( isTRF &&  (nbjets_TRF == 2) && !isTRF_incl) );
  bool pass2bincl = (NBJets >= 2) && (!isTRF || ( isTRF &&  (nbjets_TRF == 2) && isTRF_incl) );
  bool pass3bexcl = (NBJets == 3) && (!isTRF || ( isTRF &&  (nbjets_TRF == 3) && !isTRF_incl) );
  bool pass3bincl = (NBJets >= 3) && (!isTRF || ( isTRF &&  (nbjets_TRF == 3) && isTRF_incl) );
  bool pass4bincl = (NBJets >= 4) && (!isTRF || ( isTRF &&  (nbjets_TRF == 4) && isTRF_incl) );

  if(!doMCNLO)
{
  // Gtt 1 lepton region
  //configMgr.cutsDict["Presel_Gtt_1l"] = "(signal_electrons_n + signal_muons_n)>=1 && jets_n>=6 && bjets_n>=3 && met>200 && meff_incl<1000."
  
  if(NSignalLeptons >= 1
     && NJets >= 4
     && pass3bincl
     && var_Met > 200.0) // Gtt 1L preselection
    {
      isPreselect_Gtt_1l = true;
      if(debug) std::cout << "DEBUG::PRESEL\tisGtt1L" << std::endl;
    }
  else isPreselect_Gtt_1l = false;


  // Gbb preselection and Gtt 0 lepton preselection regions
  //configMgr.cutsDict["Presel_Gbb"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && jets_n>=4 && bjets_n>=3 && met>200 && meff_4j < 1000."
  if(NBaseLeptons == 0
     && var_dPhiMin > 0.4
     && NJets >= 4
     && pass3bincl
     && var_Met > 200.0) // Gbb 0L preselection
    {
      isPreselect_Gbb = true;
      if(debug) std::cout << "DEBUG::PRESEL\tisGbb" << std::endl;
    }
  else isPreselect_Gbb = false;
  
  //configMgr.cutsDict["Presel_Gtt_0l"] = "(signal_electrons_n + signal_muons_n)==0 && jets_n>=6 && bjets_n>=3 && met>200 && meff_incl<1000."
  if(NSignalLeptons == 0
     && NJets >= 4
     && pass3bincl
     && var_Met > 200.0) // Gtt 0L Preselection
    {
      isPreselect_Gtt_0l = true;
      if(debug) std::cout << "DEBUG::PRESEL\tisGtt0L" << std::endl;
    }
  else isPreselect_Gtt_0l = false;
  
  isPreselect = (isPreselect_Gbb || isPreselect_Gtt_0l || isPreselect_Gtt_1l);

  // Gbb SR flags
  //configMgr.cutsDict["SR_Gbb_A_1"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>50 && pt_bjet_3>50 && met>300 && meff_4j>1600"
  if(NBaseLeptons == 0
     && pass3bincl
     &&var_dPhiMin > 0.4
     && SelectedJets->size() >= 4
     && SelectedJets->at(3)->pt()/MEV > 50.0
     && SelectedBJets->at(2)->pt()/MEV > 50.0
     && var_Met > 300.0
     && var_Meff_4j > 1600.0)
    {
      isGbbSRA1=true;
      if(debug) std::cout << "DEBUG::SR\tisGbbSRA1" << std::endl;
    }
  else isGbbSRA1=false;

  //configMgr.cutsDict["SR_Gbb_B_1"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>70 && pt_bjet_3>70 && met>400 && meff_4j>800"
  if(NBaseLeptons == 0
     && pass3bincl
     && var_dPhiMin > 0.4
     && SelectedJets->size() >= 4
     && SelectedJets->at(3)->pt()/MEV > 70.0
     && SelectedBJets->at(2)->pt()/MEV > 70.0
     && var_Met > 400.0
     && var_Meff_4j > 800.0)
    {
      isGbbSRB1=true;
      if(debug) std::cout << "DEBUG::SR\tisGbbSRB1" << std::endl;
    }
  else isGbbSRB1=false;

  //configMgr.cutsDict["SR_Gbb_A_2"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>90 && pt_bjet_3>90 && met>350 && meff_4j>1400"
  if(NBaseLeptons == 0
     && pass3bincl
     && var_dPhiMin > 0.4
     && SelectedJets->size() >= 4
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && SelectedBJets->at(2)->pt()/MEV > 90.0
     && var_Met > 350.0
     && var_Meff_4j > 1400.0)
    {
      isGbbSRA2=true;
      if(debug) std::cout << "DEBUG::SR\tisGbbSRA2" << std::endl;
    }
  else isGbbSRA2=false;
  
  //configMgr.cutsDict["SR_Gbb_B_2"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>90 && pt_bjet_3>90 && met>400 && meff_4j>1200"
  if(NBaseLeptons == 0
     && pass3bincl
     && var_dPhiMin > 0.4
     && SelectedJets->size() >= 4
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && SelectedBJets->at(2)->pt()/MEV > 90.0
     && var_Met > 400.0
     && var_Meff_4j > 1200.0)
    {
      isGbbSRB2=true;
      if(debug) std::cout << "DEBUG::SR\tisGbbSRB2" << std::endl;
    }
  else isGbbSRB2=false;
  
  //configMgr.cutsDict["SR_Gbb_C_2"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>30 && pt_bjet_3>30 && met>500 && meff_4j>1400"
  if(NBaseLeptons == 0
     && pass3bincl
     && var_dPhiMin > 0.4
     && SelectedJets->size() >= 4
     && SelectedJets->at(3)->pt()/MEV > 30.0
     && SelectedBJets->at(2)->pt()/MEV > 30.0
     && var_Met > 500.0
     && var_Meff_4j > 1400.0)
    {
      isGbbSRC2=true;
      if(debug) std::cout << "DEBUG::SR\tisGbbSRC2" << std::endl;
    }
  else isGbbSRC2=false;

  //configMgr.cutsDict["SR_Gbb_A_4"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>90 && pt_bjet_3>90 && met>350 && meff_4j>1600"
  if(NBaseLeptons == 0
     && pass3bincl
     && var_dPhiMin > 0.4
     && SelectedJets->size() >= 4
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && SelectedBJets->at(2)->pt()/MEV > 90.0
     && var_Met > 350.0
     && var_Meff_4j > 1600.0)
    {
      isGbbSRA4=true;
      if(debug) std::cout << "DEBUG::SR\tisGbbSRA4" << std::endl;
    }
  else isGbbSRA4=false;
  
  //configMgr.cutsDict["SR_Gbb_B_4"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>90 && pt_bjet_3>90 && met>450 && meff_4j>1400"
  if(NBaseLeptons == 0
     && var_dPhiMin > 0.4
     && SelectedJets->size() >= 4
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && SelectedBJets->at(2)->pt()/MEV > 90.0
     && var_Met > 450.0
     && var_Meff_4j > 1400.0)
    {
      isGbbSRB4=true;
      if(debug) std::cout << "DEBUG::SR\tisGbbSRB4" << std::endl;
    }
  else isGbbSRB4=false;


  // Gtt 1L SR flags
  // And here, the various one-lepton signal regions ...
  
  //configMgr.cutsDict["SR_Gtt_1l_A_2"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>160 && jets_n>=6 && bjets_n>=3 && top_n>=1 && met>200 && meff_incl>1100"
  if(NSignalLeptons >= 1
     && var_mT > 150
     && var_mTb > 160
     && NJets >= 6
     && pass3bincl
     //NBJets >= 3
     && NTopJets >= 1
     && var_Met > 200.0
     && var_Meff > 1100.0)
    {
      isGtt1LSRA2=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt1LSRA2" << std::endl;
    }
  else isGtt1LSRA2=false;
  
  //configMgr.cutsDict["SR_Gtt_1l_B_2"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>160 && jets_n>=6 && bjets_n>=3 && top_n>=0 && met>300 && meff_incl>900"
  if(NSignalLeptons >= 1
     && var_mT > 150
     && var_mTb > 160
     && NJets >= 6
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 0
     && var_Met > 300.0
     && var_Meff > 900.0)
    {
      isGtt1LSRB2=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt1LSRB2" << std::endl;
    }
  else isGtt1LSRB2=false;
  
  //configMgr.cutsDict["SR_Gtt_1l_C_2"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>0   && jets_n>=6 && bjets_n>=4 && top_n>=0 && met>200 && meff_incl>600"
  if(NSignalLeptons >= 1
     && var_mT > 150
     && NJets >= 6
     && pass4bincl
     //&& NBJets >= 4
     && NTopJets >= 0
     && var_Met > 200.0
     && var_Meff > 600.0)
    {
      isGtt1LSRC2=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt1LSRC2" << std::endl;
    }
  else isGtt1LSRC2=false;
  
  //configMgr.cutsDict["SR_Gtt_1l_A_4"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>160 && jets_n>=6 && bjets_n>=3 && top_n>=1 && met>250 && meff_incl>1600"
  if(NSignalLeptons >= 1
     && var_mT > 150
     && var_mTb > 160
     && NJets >= 6
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 1
     && var_Met > 250.0
     && var_Meff > 1600.0)
    {
      isGtt1LSRA4=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt1LSRA4" << std::endl;
    }
  else isGtt1LSRA4=false;
  
  //configMgr.cutsDict["SR_Gtt_1l_B_4"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>160 && jets_n>=6 && bjets_n>=3 && top_n>=0 && met>350 && meff_incl>1100"
  if(NSignalLeptons >= 1
     && var_mT > 150
     && var_mTb > 160
     && NJets >= 6
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 0
     && var_Met > 350.0
     && var_Meff > 1100.0)
    {
      isGtt1LSRB4=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt1LSRB4" << std::endl;
    }
  else isGtt1LSRB4=false;
  
  //configMgr.cutsDict["SR_Gtt_1l_C_4"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>0   && jets_n>=6 && bjets_n>=4 && top_n>=0 && met>250 && meff_incl>700"
  if(NSignalLeptons >= 1
     && var_mT > 150
     && NJets >= 6
     && pass4bincl
     //&& NBJets >= 4
     && NTopJets >= 0
     && var_Met > 250.0
     && var_Meff > 700.0)
   {
     isGtt1LSRC4=true;
     if(debug) std::cout << "DEBUG::SR\tisGtt1LSRC4" << std::endl;
   }
  else isGtt1LSRC4=false;
 
  // Gtt 0L signal region flags
  // And here, the various zero-lepton signal regions ...
  
  //configMgr.cutsDict["SR_Gtt_0l_A"] = "(signal_electrons_n + signal_muons_n)==0 && dphi_min>0.4 && mTb_min>80 && jets_n>=8 && bjets_n>=4 && top_n>=0 && met>350 && meff_incl>1250
  if(NSignalLeptons == 0
     && var_dPhiMin > 0.4
     && var_mTb > 80
     && NJets >= 8
     && pass4bincl
     //&& NBJets >= 4
     && NTopJets >= 0
     && var_Met > 350.0
     && var_Meff > 1250.0)
    {
      isGtt0LSRA=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt0LSRA" << std::endl;
    }
  else isGtt0LSRA=false;
  
  //configMgr.cutsDict["SR_Gtt_0l_B"] = "(signal_electrons_n + signal_muons_n)==0 && dphi_min>0.4 && mTb_min>80 && jets_n>=8 && bjets_n>=4 && top_n>=1 && met>350 && meff_incl>1250"
  if(NSignalLeptons == 0
     && var_dPhiMin > 0.4
     && var_mTb > 80
     && NJets >= 8
     && pass4bincl
     //&& NBJets >= 4
     && NTopJets >= 1
     && var_Met > 350.0
     && var_Meff > 1250.0)
    {
      isGtt0LSRB=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt0LSRB" << std::endl;
    }
  else isGtt0LSRB=false;
  
  //configMgr.cutsDict["SR_Gtt_0l_C"] = "(signal_electrons_n + signal_muons_n)==0 && dphi_min>0.4 && mTb_min>80 && jets_n>=8 && bjets_n>=3 && top_n>=1 && met>400 && meff_incl>1700"
  if(NSignalLeptons == 0
     && var_dPhiMin > 0.4
     && var_mTb > 80
     && NJets >= 8
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 1
     && var_Met > 400.0
     && var_Meff > 1700.0)
    {
      isGtt0LSRC=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt0LSRC" << std::endl;
    }
  else isGtt0LSRC=false;
  
  //configMgr.cutsDict["SR_Gtt_0l_D"] = "(signal_electrons_n + signal_muons_n)==0 && dphi_min>0.4 && mTb_min>80 && jets_n>=8 && bjets_n>=3 && top_n>=2 && met>400 && meff_incl>1700"
  if(NSignalLeptons == 0
     && var_dPhiMin > 0.4
     && var_mTb > 80
     && NJets >= 8
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 2
     && var_Met > 400.0
     && var_Meff > 1700.0)
    {
      isGtt0LSRD=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt0LSRD" << std::endl;
    }
  else isGtt0LSRD=false;

  // Gbb CRs
  if( NSignalLeptons == 1
     && NJets >= 4
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && pass3bincl
     //&& NBJets >= 3
     && var_mT < 150
     && var_Met > 250
     && var_Meff_4j > 1100)
    {
      isGbbCRA2=true;
    }
  else isGbbCRA2=false;

  if(NSignalLeptons==1
     &&    NJets >= 4
     &&    SelectedJets->at(3)->pt()/MEV > 90.0
     && pass3bincl
     //&&    NBJets >= 3
     &&    var_mT < 150
     && var_Met > 250
     && var_Meff_4j > 900)
    {
      isGbbCRB2=true;
    }
  else isGbbCRB2=false;

  if(NSignalLeptons==1
     &&    NJets >= 4     
     &&    SelectedJets->at(3)->pt()/MEV > 30.0
     && pass3bincl
     //&&    NBJets >= 3
     &&    var_mT < 150
     && var_Met > 400
     && var_Meff_4j > 1200)
    //&& var_Met > 250
    //&& var_Meff_4j > 900)
    {
      isGbbCRC2=true;
    }
  else isGbbCRC2=false;
  
  if( NSignalLeptons==1
     &&    NJets >= 4
     &&    SelectedJets->at(3)->pt()/MEV > 90.0
     && pass3bincl
     //&&    NBJets >= 3
     &&    var_mT < 150 
     && var_Met > 250
     && var_Meff_4j > 1200)
    {
      isGbbCRA4=true;
    }
  else isGbbCRA4=false;
  
  if(NSignalLeptons==1
     &&    NJets >= 4
     &&    SelectedJets->at(3)->pt()/MEV > 90.0
     && pass3bincl
     //&&    NBJets >= 3
     &&    var_mT < 150
     && var_Met > 300
     && var_Meff_4j > 1100)
    {
      isGbbCRB4=true;
    }
  else isGbbCRB4=false;
  
  // Gtt 1L control regions
  if(NSignalLeptons>=1
     && NJets >= 6
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 1
     && var_mT < 150
     && var_Met >= 200
     && var_Meff >= 1100)
    {
      isGtt1LCRA2=true;
    }
  else isGtt1LCRA2=false;

  if( NSignalLeptons >=1
     && NJets >= 6
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 0
     && var_mT < 150
     && var_Met >= 300
     && var_Meff >= 900)
    {
      isGtt1LCRB2=true;
    }
  else isGtt1LCRB2=false;

  if( NSignalLeptons >= 1
     && NJets >= 6
     && pass4bincl
     //&& NBJets >= 4
     && NTopJets >= 0
     && var_mT < 80
     && var_Met >= 200
     //&& var_Meff >= 900)
     && var_Meff >= 600)
    {
      isGtt1LCRC2=true;
    }
  else isGtt1LCRC2=false;

  if( NSignalLeptons >= 1
     && NJets >= 6
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 1
     && var_mT < 150
     && var_Met >= 250
     && var_Meff >= 1600)
    {
      isGtt1LCRA4=true;
    }
  else isGtt1LCRA4=false;

  if( NSignalLeptons >=1
     && NJets >= 6
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 0
     && var_mT < 150
     && var_Met >= 350
     && var_Meff >= 1100)
    {
      isGtt1LCRB4=true;
    }
  else isGtt1LCRB4=false;

  if( NSignalLeptons >= 1
     && NJets >= 6
     && pass4bincl
     //&& NBJets >= 4
     && NTopJets >= 0
     && var_mT < 80
     && var_Met >= 250
     && var_Meff >= 700)
    {
      isGtt1LCRC4=true;
    }
  else isGtt1LCRC4=false;
  
  // Gtt 0L control regions
  if( NSignalLeptons == 1
     && NJets >= 7
     && pass4bincl
     //&& NBJets >= 4
     &&	NTopJets >= 0
     && var_mT < 150
     && var_Met >= 200
     && var_Meff >= 1000)
    {
      isGtt0LCRA=true;
    }
  else isGtt0LCRA=false;
  
  if( NSignalLeptons == 1
     && NJets >= 7
     && pass4bincl
     //&& NBJets >= 4
     && NTopJets >=1
     && var_mT < 150
     && var_Met >= 200
     && var_Meff >= 1000)
    {
      isGtt0LCRB=true;
    }
  else isGtt0LCRB=false;
  
  if( NSignalLeptons == 1
     && NJets >= 7
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >=1
     && var_mT < 150
     && var_Met >= 250
     && var_Meff >= 1350)
    {
      isGtt0LCRC=true;
    }
  else isGtt0LCRC=false;
  
  if( NSignalLeptons == 1
     && NJets >= 7
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >=2
     && var_mT < 150
     && var_Met >= 200
     && var_Meff >= 1200)
    {
      isGtt0LCRD=true;
    }
  else isGtt0LCRD=false;
  
  // gbb 0l vrs
  if(NBaseLeptons == 0
     && var_dPhiMin > 0.4
     && NJets >= 4
     && pass3bincl
     //&& NBJets >= 3
     && var_mTb < 160.0
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && var_Met > 200.0
     && var_Meff_4j < 1200.0)
    {
      isGbbVRI2=true;
    }
  else isGbbVRI2 = false;

  if(NBaseLeptons == 0
     && var_dPhiMin > 0.4
     && NJets >= 4
     && pass3bincl
     //&& NBJets >= 3
     && var_mTb < 160.0
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && var_Met > 250.0
     && var_Meff_4j < 1200.0)
    {
      isGbbVRII2=true;
    }
  else isGbbVRII2 = false;

  if(NBaseLeptons == 0
     && var_dPhiMin > 0.4
     && NJets >= 4
     && pass3bincl
     //&& NBJets >= 3
     && var_mTb < 160.0
     && SelectedJets->at(3)->pt()/MEV > 30.0
     && var_Met > 400.0
     && var_Meff_4j < 1400.0)
    {
      isGbbVRIII2=true;
    }
  else isGbbVRIII2 = false;

  if(NBaseLeptons == 0
     && var_dPhiMin > 0.4
     && NJets >= 4
     && pass3bincl
     //&& NBJets >= 3
     && var_mTb < 160.0
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && var_Met > 250.0
     && var_Meff_4j < 1400.0)
    {
      isGbbVRI4=true;
    }
  else isGbbVRI4 = false;

  if(NBaseLeptons == 0
     && var_dPhiMin > 0.4
     && NJets >= 4
     && pass3bincl
     //&& NBJets >= 3
     && var_mTb < 160.0
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && var_Met > 300.0
     && var_Meff_4j < 1400.0)
    {
      isGbbVRII4=true;
    }
  else isGbbVRII4 = false;

  // gtt 0l vrs
  if(NSignalLeptons == 1
    && var_Meff >= 1000
    && var_Met >= 200
    && NJets >= 7
    & pass3bincl
     //&& NBJets >= 3
    && NTopJets >= 2
    && var_mT <= 150
    && var_mTb >= 80)
    {
      isVR1LGtt0LI=true;
    }
  else isVR1LGtt0LI = false;

  if(NSignalLeptons == 1
    && var_Meff >= 1350
    && var_Met >= 250
    && NJets >= 7
    & pass3bincl
     //&& NBJets >= 3
    && NTopJets >= 1
    && var_mT <= 150
    && var_mTb >= 80)
    {
      isVR1LGtt0LII=true;
    }
  else isVR1LGtt0LII = false;

  if(NSignalLeptons == 1
    && var_Meff >= 1000
    && var_Met >= 200
    && NJets >= 7
    && pass4bincl
     //&& NBJets >= 4
    && NTopJets >= 1
    && var_mT <= 150
    && var_mTb >= 80)
    {
      isVR1LGtt0LIII=true;
    }
  else isVR1LGtt0LIII = false;

  if(NSignalLeptons == 1
    && var_Meff >= 1000
    && var_Met >= 200
    && NJets >= 7
    && pass4bincl
     //&& NBJets >= 4
    && NTopJets >= 0
    && var_mT <= 125
    && var_mTb >= 80)
    {
      isVR1LGtt0LIV=true;
    }
  else isVR1LGtt0LIV = false;

  if(NSignalLeptons == 0
    && var_Meff >= 1100
    && var_Met >= 200
    && NJets >= 8
    && pass2bincl
     //&& NBJets >= 2
    && NTopJets >= 2
    && var_mTb < 80)
    {
      isVR0LGtt0LI=true;
    }
  else isVR0LGtt0LI = false;

  if(NSignalLeptons == 0
    && var_Meff >= 1400
    && var_Met >= 200
    && NJets >= 8
    && pass2bincl
     //&& NBJets >= 2
    && NTopJets >= 1
    && var_mTb < 80)
    {
      isVR0LGtt0LII=true;
    }
  else isVR0LGtt0LII = false;

  if(NSignalLeptons == 0
    && var_Meff >= 1100
    && var_Met >= 200
    && NJets >= 8
    & pass3bincl
     //&& NBJets >= 3
    && NTopJets >= 1
    && var_mTb < 80)
    {
      isVR0LGtt0LIII=true;
    }
  else isVR0LGtt0LIII = false;

  if(NSignalLeptons == 0
    && var_Meff >= 1250
    && var_Met >= 200
    && NJets >= 8
    & pass3bincl
     //&& NBJets >= 3
    && NTopJets >= 0
    && var_mTb < 80)
    {
      isVR0LGtt0LIV=true;
    }
  else isVR0LGtt0LIV = false;

  // gtt 1L vrs
  if( NSignalLeptons >= 1
     && NJets >= 6
     && pass2bexcl
     //&& NBJets == 2
     && NTopJets >=1
     && var_Met >= 200
     && var_Meff >= 1100
     && var_mT > 150
     && var_mTb < 160)
    {
      isVRGtt1LI2mT2b=true;
    }
    else isVRGtt1LI2mT2b=false;

  if( NSignalLeptons >= 1
     && NJets >= 6
     && pass2bexcl
     //&& NBJets == 2
     && NTopJets >=0
     && var_Met >= 300
     && var_Meff >= 900
     && var_mT > 150
     && var_mTb < 160)
    {
      isVRGtt1LII2mT2b=true;
    }
  else isVRGtt1LII2mT2b = false;
  
  if( NSignalLeptons >= 1
     && NJets >= 6
     && pass2bexcl
     //&& NBJets == 2
     && NTopJets >=1
     && var_Met >= 250
     && var_Meff >= 1500
     && var_mT > 150
     && var_mTb < 160)
    {
      isVRGtt1LI4mT2b=true;
    }
  else isVRGtt1LI4mT2b = false;
  
  if( NSignalLeptons >= 1
     && NJets >= 5
     && pass2bexcl
      //&& NBJets == 2
     && NTopJets >= 0
     && var_Met >= 350
     && var_Meff >= 1100
     && var_mT > 150
     && var_mTb < 160)
    {
      isVRGtt1LII4mT2b=true;
    }
  else isVRGtt1LII4mT2b = false;

   if( NSignalLeptons >= 1
     && NJets >= 5
     && pass3bexcl
      //&& NBJets == 3
     && NTopJets >= 1
     && var_Met >= 200
     && var_Meff >= 600
     && var_mT > 150
     && var_mTb < 160)
    {
      isVRGtt1LI2mT3b=true;
    }
  else isVRGtt1LI2mT3b = false;
   
   if( NSignalLeptons >= 1
     && NJets >= 5
     && pass3bexcl
      //&& NBJets == 3
     && NTopJets >= 0
     && var_Met >= 200
     && var_Meff >= 600
     && var_mT > 150
     && var_mTb < 160)
    {
      isVRGtt1LII2mT3b=true;
    }
  else isVRGtt1LII2mT3b = false;
  
   if( NSignalLeptons >= 1
     && NJets >= 5
     && pass3bexcl
      //&& NBJets == 3
     && NTopJets >= 1
     && var_Met >= 200
     && var_Meff >= 700
     && var_Meff <= 1500
     && var_mT > 150
     && var_mTb < 160)
    {
      isVRGtt1LI4mT3b=true;
    }
  else isVRGtt1LI4mT3b = false; 

  if( NSignalLeptons >= 1
    && NJets >= 5
     && pass3bexcl
     //&& NBJets == 3
    && NTopJets >= 0
    && var_Met >= 200
    && var_Meff >= 800
    && var_mT > 150
    && var_mTb < 160)
   {
     isVRGtt1LII4mT3b=true;
   } 
  else isVRGtt1LII4mT3b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass2bexcl
     //&& NBJets == 2
    && NTopJets >= 1
    && var_Met >= 200
    && var_Meff >= 1100
    && var_mT < 150
    && var_mTb > 160)
    {
      isVRGtt1LI2mTb2b=true;
    }
  else isVRGtt1LI2mTb2b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass2bexcl
     //&& NBJets == 2
    && NTopJets >= 0
    && var_Met >= 300
    && var_Meff >= 900
    && var_mT < 150
    && var_mTb > 160)
    {
      isVRGtt1LII2mTb2b=true;
    }
  else isVRGtt1LII2mTb2b = false;
  
  if( NSignalLeptons >= 1
    && NJets >= 6
    && pass2bexcl
     //&& NBJets == 2
    && NTopJets >= 1
    && var_Met >= 250
    && var_Meff >= 1500
    && var_mT < 150
    && var_mTb > 160)
    {
      isVRGtt1LI4mTb2b=true;
    }
  else isVRGtt1LI4mTb2b = false;
       
  if( NSignalLeptons >= 1 
    && NJets >= 6
    && pass2bexcl
     //&& NBJets == 2
    && NTopJets >= 0
    && var_Met >= 350
    && var_Meff >= 1100
    && var_mT < 150
    && var_mTb > 160)
    {
      isVRGtt1LII4mTb2b=true;
    }
  else isVRGtt1LII4mTb2b = false;
      
  if( NSignalLeptons >= 1
    && NJets >= 6
    && pass3bexcl
     //&& NBJets == 3
    && NTopJets >= 1
    && var_Met >= 200
    && var_Meff >= 600
    && var_mT < 150
    && var_mTb > 140)
    {
     isVRGtt1LI2mTb3b =true;
    }
  else isVRGtt1LI2mTb3b = false;
  
  if( NSignalLeptons >= 1
    && NJets >= 6
    && pass3bexcl
     //&& NBJets == 3
    && NTopJets >= 0
    && var_Met >= 200
    && var_Meff >= 600
    && var_mT < 150
    && var_mTb > 160)
    {
      isVRGtt1LII2mTb3b=true;
    }
  else isVRGtt1LII2mTb3b = false;
   
  if( NSignalLeptons >= 1
    && NJets >= 6
    && pass3bexcl
     //&& NBJets == 3
    && NTopJets >= 1
    && var_Met >= 200
    && var_Meff >= 700
    && var_Meff <= 1500
    && var_mT < 150
    && var_mTb > 140)
    {
      isVRGtt1LI4mTb3b=true;
    }
  else isVRGtt1LI4mTb3b = false;
   
  if( NSignalLeptons >= 1
    && NJets >= 6
    && pass3bexcl
     //&& NBJets == 3
    && NTopJets >= 0
    && var_Met >= 250
    && var_Meff >= 800
    && var_mT < 150
    && var_mTb > 160)
    {
      isVRGtt1LII4mTb3b=true;
    }
  else isVRGtt1LII4mTb3b = false;
  
  if( NSignalLeptons >= 1
    && NJets >= 5
    && pass4bincl
     //&& NBJets == 4
    && NTopJets >= 1
    && var_Met >= 200
    && var_Meff >= 600
    && var_mT < 150
    && var_mTb > 140)
    {
      isVRGtt1LI2mT4b=true;
    }
  else isVRGtt1LI2mT4b = false;
  
  if( NSignalLeptons >= 1
    && NJets >= 6
    && pass4bincl
     //&& NBJets == 4
    && NTopJets >= 0
    && var_Met >= 200
    && var_Meff >= 600
    && var_mT < 150
    && var_mTb > 140)
    {
      isVRGtt1LII2mT4b=true;
    }
  else isVRGtt1LII2mT4b = false;
  
  if( NSignalLeptons >= 1
    && NJets >= 6
    && pass2bexcl
     //&& NBJets == 2
    && NTopJets >= 0
    && var_Met >= 200
    && var_Meff >= 600
    && var_mT > 80
    && var_mT < 110)
    {
      isVRGtt1LIII22b=true;
    }
  else isVRGtt1LIII22b = false;
  
  if( NSignalLeptons >= 1
    && NJets >= 6
    && pass2bexcl
     //&& NBJets == 2
    && NTopJets >= 0
    && var_Met >= 250
    && var_Meff >= 700
    && var_mT > 80
    && var_mT < 110)
    {
      isVRGtt1LIII42b=true;
    }
  else isVRGtt1LIII42b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass3bexcl
     //&& NBJets == 3
    && NTopJets >= 0
    && var_Met >= 200
    && var_Meff >= 600
    && var_mT > 80
    && var_mT < 110)
    {
      isVRGtt1LIII23b=true;
    }
  else isVRGtt1LIII23b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass3bexcl
     //&& NBJets == 3
    && NTopJets >= 0
    && var_Met >= 250
    && var_Meff >= 700
    && var_mT > 80
    && var_mT < 110)
    {
      isVRGtt1LIII43b=true;
    }
  else isVRGtt1LIII43b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 5
    && pass4bincl
     //&& NBJets == 4
    && NTopJets >= 0
    && var_Met >= 200
    && var_Meff >= 600
    && var_mT > 80
    && var_mT < 110)
    {
      isVRGtt1LIII24b=true;
    }
  else isVRGtt1LIII24b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 5
    && pass4bincl
     //&& NBJets == 4
    && NTopJets >= 0
    && var_Met >= 250
    && var_Meff >= 700
    && var_mT > 80
    && var_mT < 110)
    {
      isVRGtt1LIII44b=true;
    }
  else isVRGtt1LIII44b = false;
}
else // ELSE YOU'RE DOING MCNLO SO FIX THAT MET UP YO
{
  // Gtt 1 lepton region
  //configMgr.cutsDict["Presel_Gtt_1l"] = "(signal_electrons_n + signal_muons_n)>=1 && jets_n>=6 && bjets_n>=3 && met>200 && meff_incl<1000."
  
  if(NSignalLeptons >= 1
     && NJets >= 4
     && pass3bincl
     //&& NBJets >= 3
     && var_Met > 0.0) // Gtt 1L preselection
    {
      isPreselect_Gtt_1l = true;
      if(debug) std::cout << "DEBUG::PRESEL\tisGtt1L" << std::endl;
    }
  else isPreselect_Gtt_1l = false;


  // Gbb preselection and Gtt 0 lepton preselection regions
  //configMgr.cutsDict["Presel_Gbb"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && jets_n>=4 && bjets_n>=3 && met>200 && meff_4j < 1000."
  if(NBaseLeptons == 0
     && var_dPhiMin > 0.4
     && NJets >= 4
     && pass3bincl
     //&& NBJets >= 3
     && var_Met > 0.0) // Gbb 0L preselection
    {
      isPreselect_Gbb = true;
      if(debug) std::cout << "DEBUG::PRESEL\tisGbb" << std::endl;
    }
  else isPreselect_Gbb = false;
  
  //configMgr.cutsDict["Presel_Gtt_0l"] = "(signal_electrons_n + signal_muons_n)==0 && jets_n>=6 && bjets_n>=3 && met>200 && meff_incl<1000."
  if(NSignalLeptons == 0
     && NJets >= 4
     && pass3bincl
     //&& NBJets >= 3
     && var_Met > 0.0) // Gtt 0L Preselection
    {
      isPreselect_Gtt_0l = true;
      if(debug) std::cout << "DEBUG::PRESEL\tisGtt0L" << std::endl;
    }
  else isPreselect_Gtt_0l = false;
  
  isPreselect = (isPreselect_Gbb || isPreselect_Gtt_0l || isPreselect_Gtt_1l);
  
  // Gbb SR flags
  //configMgr.cutsDict["SR_Gbb_A_1"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>50 && pt_bjet_3>50 && met>300 && meff_4j>1600"
  if(NSignalLeptons == 0
     && pass3bincl
     &&var_dPhiMin > 0.4
     && SelectedJets->size() >= 4
     && SelectedJets->at(3)->pt()/MEV > 50.0
     && SelectedBJets->at(2)->pt()/MEV > 50.0
     && var_Met > 0.0
     && var_Meff_4j > 1300.0)
    {
      isGbbSRA1=true;
      if(debug) std::cout << "DEBUG::SR\tisGbbSRA1" << std::endl;
    }
  else isGbbSRA1=false;

  //configMgr.cutsDict["SR_Gbb_B_1"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>70 && pt_bjet_3>70 && met>400 && meff_4j>800"
  if(NSignalLeptons == 0
     && pass3bincl
     && var_dPhiMin > 0.4
     && SelectedJets->size() >= 4
     && SelectedJets->at(3)->pt()/MEV > 70.0
     && SelectedBJets->at(2)->pt()/MEV > 70.0
     && var_Met > 0.0
     && var_Meff_4j > 400.0)
    {
      isGbbSRB1=true;
      if(debug) std::cout << "DEBUG::SR\tisGbbSRB1" << std::endl;
    }
  else isGbbSRB1=false;

  //configMgr.cutsDict["SR_Gbb_A_2"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>90 && pt_bjet_3>90 && met>350 && meff_4j>1400"
  if(NSignalLeptons == 0
     && pass3bincl
     && var_dPhiMin > 0.4
     && SelectedJets->size() >= 4
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && SelectedBJets->at(2)->pt()/MEV > 90.0
     && var_Met > 0.0
     && var_Meff_4j > 1050.0)
    {
      isGbbSRA2=true;
      if(debug) std::cout << "DEBUG::SR\tisGbbSRA2" << std::endl;
    }
  else isGbbSRA2=false;
  
  //configMgr.cutsDict["SR_Gbb_B_2"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>90 && pt_bjet_3>90 && met>400 && meff_4j>1200"
  if(NSignalLeptons == 0
     && pass3bincl
     &&var_dPhiMin > 0.4
     && SelectedJets->size() >= 4
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && SelectedBJets->at(2)->pt()/MEV > 90.0
     && var_Met > 0.0
     && var_Meff_4j > 800.0)
    {
      isGbbSRB2=true;
      if(debug) std::cout << "DEBUG::SR\tisGbbSRB2" << std::endl;
    }
  else isGbbSRB2=false;
  
  //configMgr.cutsDict["SR_Gbb_C_2"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>30 && pt_bjet_3>30 && met>500 && meff_4j>1400"
  if(NSignalLeptons == 0
     && pass3bincl
     &&var_dPhiMin > 0.4
     && SelectedJets->size() >= 4
     && SelectedJets->at(3)->pt()/MEV > 30.0
     && SelectedBJets->at(2)->pt()/MEV > 30.0
     && var_Met > 0.0
     && var_Meff_4j > 900.0)
    {
      isGbbSRC2=true;
      if(debug) std::cout << "DEBUG::SR\tisGbbSRC2" << std::endl;
    }
  else isGbbSRC2=false;

  //configMgr.cutsDict["SR_Gbb_A_4"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>90 && pt_bjet_3>90 && met>350 && meff_4j>1600"
  if(NSignalLeptons == 0
     && pass3bincl
     && var_dPhiMin > 0.4
     && SelectedJets->size() >= 4
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && SelectedBJets->at(2)->pt()/MEV > 90.0
     && var_Met > 0.0
     && var_Meff_4j > 1250.0)
    {
      isGbbSRA4=true;
      if(debug) std::cout << "DEBUG::SR\tisGbbSRA4" << std::endl;
    }
  else isGbbSRA4=false;
  
  //configMgr.cutsDict["SR_Gbb_B_4"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>90 && pt_bjet_3>90 && met>450 && meff_4j>1400"
  if(NSignalLeptons == 0
     && pass3bincl
     && var_dPhiMin > 0.4
     && SelectedJets->size() >= 4
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && SelectedBJets->at(2)->pt()/MEV > 90.0
     && var_Met > 0.0
     && var_Meff_4j > 950.0)
    {
      isGbbSRB4=true;
      if(debug) std::cout << "DEBUG::SR\tisGbbSRB4" << std::endl;
    }
  else isGbbSRB4=false;


  // Gtt 1L SR flags
  // And here, the various one-lepton signal regions ...
  
  //configMgr.cutsDict["SR_Gtt_1l_A_2"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>160 && jets_n>=6 && bjets_n>=3 && top_n>=1 && met>200 && meff_incl>1100"
  if(NSignalLeptons >= 1
     && var_mT > 150
     && var_mTb > 160
     && NJets >= 6
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 1
     && var_Met > 0.0
     && var_Meff > 900.0)
    {
      isGtt1LSRA2=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt1LSRA2" << std::endl;
    }
  else isGtt1LSRA2=false;
  
  //configMgr.cutsDict["SR_Gtt_1l_B_2"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>160 && jets_n>=6 && bjets_n>=3 && top_n>=0 && met>300 && meff_incl>900"
  if(NSignalLeptons >= 1
     && var_mT > 150
     && var_mTb > 160
     && NJets >= 6
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 0
     && var_Met > 0.0
     && var_Meff > 600.0)
    {
      isGtt1LSRB2=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt1LSRB2" << std::endl;
    }
  else isGtt1LSRB2=false;
  
  //configMgr.cutsDict["SR_Gtt_1l_C_2"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>0   && jets_n>=6 && bjets_n>=4 && top_n>=0 && met>200 && meff_incl>600"
  if(NSignalLeptons >= 1
     && var_mT > 150
     && NJets >= 6
     && pass4bincl
     //&& NBJets >= 4
     && NTopJets >= 0
     && var_Met > 0.0
     && var_Meff > 400.0)
    {
      isGtt1LSRC2=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt1LSRC2" << std::endl;
    }
  else isGtt1LSRC2=false;
  
  //configMgr.cutsDict["SR_Gtt_1l_A_4"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>160 && jets_n>=6 && bjets_n>=3 && top_n>=1 && met>250 && meff_incl>1600"
  if(NSignalLeptons >= 1
     && var_mT > 150
     && var_mTb > 160
     && NJets >= 6
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 1
     && var_Met > 0.0
     && var_Meff > 1350.0)
    {
      isGtt1LSRA4=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt1LSRA4" << std::endl;
    }
  else isGtt1LSRA4=false;
  
  //configMgr.cutsDict["SR_Gtt_1l_B_4"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>160 && jets_n>=6 && bjets_n>=3 && top_n>=0 && met>350 && meff_incl>1100"
  if(NSignalLeptons >=1 
     && var_mT > 150
     && var_mTb > 160
     && NJets >= 6
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 0
     && var_Met > 0.0
     && var_Meff > 750.0)
    {
      isGtt1LSRB4=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt1LSRB4" << std::endl;
    }
  else isGtt1LSRB4=false;
  
  //configMgr.cutsDict["SR_Gtt_1l_C_4"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>0   && jets_n>=6 && bjets_n>=4 && top_n>=0 && met>250 && meff_incl>700"
  if(NSignalLeptons >= 1
     && var_mT > 150
     && NJets >= 6
     && pass4bincl
     //&& NBJets >= 4
     && NTopJets >= 0
     && var_Met > 0.0
     && var_Meff > 450.0)
   {
     isGtt1LSRC4=true;
     if(debug) std::cout << "DEBUG::SR\tisGtt1LSRC4" << std::endl;
   }
  else isGtt1LSRC4=false;
 
  // Gtt 0L signal region flags
  // And here, the various zero-lepton signal regions ...
  
  //configMgr.cutsDict["SR_Gtt_0l_A"] = "(signal_electrons_n + signal_muons_n)==0 && dphi_min>0.4 && mTb_min>80 && jets_n>=8 && bjets_n>=4 && top_n>=0 && met>350 && meff_incl>1250
  if(NSignalLeptons == 0
     && var_dPhiMin > 0.4
     && var_mTb > 80
     && NJets >= 8
     && pass4bincl
     //&& NBJets >= 4
     && NTopJets >= 0
     && var_Met > 0.0
     && var_Meff > 900.0)
    {
      isGtt0LSRA=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt0LSRA" << std::endl;
    }
  else isGtt0LSRA=false;
  
  //configMgr.cutsDict["SR_Gtt_0l_B"] = "(signal_electrons_n + signal_muons_n)==0 && dphi_min>0.4 && mTb_min>80 && jets_n>=8 && bjets_n>=4 && top_n>=1 && met>350 && meff_incl>1250"
  if(NSignalLeptons == 0
     && var_dPhiMin > 0.4
     && var_mTb > 80
     && NJets >= 8
     && pass4bincl
     //&& NBJets >= 4
     && NTopJets >= 1
     && var_Met > 0.0
     && var_Meff > 900.0)
    {
      isGtt0LSRB=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt0LSRB" << std::endl;
    }
  else isGtt0LSRB=false;
  
  //configMgr.cutsDict["SR_Gtt_0l_C"] = "(signal_electrons_n + signal_muons_n)==0 && dphi_min>0.4 && mTb_min>80 && jets_n>=8 && bjets_n>=3 && top_n>=1 && met>400 && meff_incl>1700"
  if(NSignalLeptons == 0
     && var_dPhiMin > 0.4
     && var_mTb > 80
     && NJets >= 8
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 1
     && var_Met > 0.0
     && var_Meff > 1300.0)
    {
      isGtt0LSRC=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt0LSRC" << std::endl;
    }
  else isGtt0LSRC=false;
  
  //configMgr.cutsDict["SR_Gtt_0l_D"] = "(signal_electrons_n + signal_muons_n)==0 && dphi_min>0.4 && mTb_min>80 && jets_n>=8 && bjets_n>=3 && top_n>=2 && met>400 && meff_incl>1700"
  if(NSignalLeptons == 0
     && var_dPhiMin > 0.4
     && var_mTb > 80
     && NJets >= 8
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 2
     && var_Met > 0.0
     && var_Meff > 1300.0)
    {
      isGtt0LSRD=true;
      if(debug) std::cout << "DEBUG::SR\tisGtt0LSRD" << std::endl;
    }
  else isGtt0LSRD=false;

  // Gbb CRs
  if( NSignalLeptons == 1
     && NJets >= 4
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && pass3bincl
     //&& NBJets >= 3
     && var_mT < 150
     && var_Met > 0.0
     && var_Meff_4j > 850)
    {
      isGbbCRA2=true;
    }
  else isGbbCRA2=false;

  if( NSignalLeptons == 1
     &&    NJets >= 4
     &&    SelectedJets->at(3)->pt()/MEV > 90.0
     && pass3bincl
     //&&    NBJets >= 3
     &&    var_mT < 150
     && var_Met > 0.0
     && var_Meff_4j > 650.0)
    {
      isGbbCRB2=true;
    }
  else isGbbCRB2=false;

  if( NSignalLeptons == 1
     &&    NJets >= 4     
     &&    SelectedJets->at(3)->pt()/MEV > 30.0
     && pass3bincl
     //&&    NBJets >= 3
     &&    var_mT < 150
     && var_Met > 0.0
     && var_Meff_4j > 800.0)
    //&& var_Meff_4j > 650.0)
    {
      isGbbCRC2=true;
    }
  else isGbbCRC2=false;
  
  if( NSignalLeptons == 1
     &&    NJets >= 4
     &&    SelectedJets->at(3)->pt()/MEV > 90.0
     && pass3bincl
     //&&    NBJets >= 3
     &&    var_mT < 150 
     && var_Met > 0.0
     && var_Meff_4j > 950.0)
    {
      isGbbCRA4=true;
    }
  else isGbbCRA4=false;
  
  if( NSignalLeptons == 1
     &&    NJets >= 4
     &&    SelectedJets->at(3)->pt()/MEV > 90.0
     && pass3bincl
     //&&    NBJets >= 3
     &&    var_mT < 150
     && var_Met > 0.0
     && var_Meff_4j > 800.0)
    {
      isGbbCRB4=true;
    }
  else isGbbCRB4=false;
  
  // Gtt 1L control regions
  if( NSignalLeptons >= 1
     && NJets >= 6
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 1
     && var_mT < 150
     && var_Met >= 0.0
     && var_Meff >= 900.0)
    {
      isGtt1LCRA2=true;
    }
  else isGtt1LCRA2=false;

  if( NSignalLeptons >= 1
     && NJets >= 6
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 0
     && var_mT < 150
     && var_Met >= 0.0
     && var_Meff >= 600.0)
    {
      isGtt1LCRB2=true;
    }
  else isGtt1LCRB2=false;

  if( NSignalLeptons >= 1
     && NJets >= 6
     && pass4bincl
     //&& NBJets >= 4
     && NTopJets >= 0
     && var_mT < 80
     && var_Met >= 0.0
     && var_Meff >= 400.0)
    //&& var_Meff >= 700.0)
    {
      isGtt1LCRC2=true;
    }
  else isGtt1LCRC2=false;

  if( NSignalLeptons >= 1
     && NJets >= 6
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 1
     && var_mT < 150
     && var_Met >= 0.0
     && var_Meff >= 1250.0)
    {
      isGtt1LCRA4=true;
    }
  else isGtt1LCRA4=false;

  if( NSignalLeptons >= 1
     && NJets >= 6
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >= 0
     && var_mT < 150
     && var_Met >= 0.0
     && var_Meff >= 750.0)
    {
      isGtt1LCRB4=true;
    }
  else isGtt1LCRB4=false;

  if( NSignalLeptons >=1
     && NJets >= 6
     && pass4bincl
     //&& NBJets >= 4
     && NTopJets >= 0
     && var_mT < 80
     && var_Met >= 0.0
     && var_Meff >= 450.0)
    {
      isGtt1LCRC4=true;
    }
  else isGtt1LCRC4=false;
  
  // Gtt 0L control regions
  if( NSignalLeptons == 1
     && NJets >= 7
     && pass4bincl
     //&& NBJets >= 4
     && NTopJets >= 0
     && var_mT < 150
     && var_Met >= 0.0
     && var_Meff >= 800.0)
    {
      isGtt0LCRA=true;
    }
  else isGtt0LCRA=false;
  
  if( NSignalLeptons ==1
     && NJets >= 7
     && pass4bincl
     //&& NBJets >= 4
     && NTopJets >=1
     && var_mT < 150
     && var_Met >= 0.0
     && var_Meff >= 800.0)
    {
      isGtt0LCRB=true;
    }
  else isGtt0LCRB=false;
  
  if( NSignalLeptons==1
     && NJets >= 7
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >=1
     && var_mT < 150
     && var_Met >= 0.0
     && var_Meff >= 1100.0)
    {
      isGtt0LCRC=true;
    }
  else isGtt0LCRC=false;
  
  if( NSignalLeptons == 1
     && NJets >= 7
     && pass3bincl
     //&& NBJets >= 3
     && NTopJets >=2
     && var_mT < 150
     && var_Met >= 0.0
     && var_Meff >= 1000.0)
    {
      isGtt0LCRD=true;
    }
  else isGtt0LCRD=false;
  
  // gbb 0l vrs
  if(NBaseLeptons == 0
     && var_dPhiMin > 0.4
     && NJets >= 4
     && pass3bincl
     //&& NBJets >= 3
     && var_mTb < 160.0
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && var_Met > 0.0
     && var_Meff_4j < 1000.0)
    {
      isGbbVRI2=true;
    }
  else isGbbVRI2 = false;

  if(NBaseLeptons == 0
     && var_dPhiMin > 0.4
     && NJets >= 4
     && pass3bincl
     //&& NBJets >= 3
     && var_mTb < 160.0
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && var_Met > 0.0
     && var_Meff_4j < 950.0)
    {
      isGbbVRII2=true;
    }
  else isGbbVRII2 = false;

  if(NBaseLeptons == 0
     && var_dPhiMin > 0.4
     && NJets >= 4
     && pass3bincl
     //&& NBJets >= 3
     && var_mTb < 160.0
     && SelectedJets->at(3)->pt()/MEV > 30.0
     && var_Met > 0.0
     && var_Meff_4j < 1000.0)
    {
      isGbbVRIII2=true;
    }
  else isGbbVRIII2 = false;

  if(NBaseLeptons == 0
     && var_dPhiMin > 0.4
     && NJets >= 4
     && pass3bincl
     //&& NBJets >= 3
     && var_mTb < 160.0
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && var_Met > 0.0
     && var_Meff_4j < 1150.0)
    {
      isGbbVRI4=true;
    }
  else isGbbVRI4 = false;

  if(NBaseLeptons == 0
     && var_dPhiMin > 0.4
     && NJets >= 4
     && pass3bincl
     //&& NBJets >= 3
     && var_mTb < 160.0
     && SelectedJets->at(3)->pt()/MEV > 90.0
     && var_Met > 0.0
     && var_Meff_4j < 1100.0)
    {
      isGbbVRII4=true;
    }
  else isGbbVRII4 = false;

  // gtt 0l vrs
  if(NSignalLeptons == 1
    && var_Meff >= 800.0
    && var_Met >= 0.0
    && NJets >= 7
    & pass3bincl
     //&& NBJets >= 3
    && NTopJets >= 2
    && var_mT <= 150
    && var_mTb >= 80)
    {
      isVR1LGtt0LI=true;
    }
  else isVR1LGtt0LI = false;

  if(NSignalLeptons == 1
    && var_Meff >= 1150.0
    && var_Met >= 0.0
    && NJets >= 7
    & pass3bincl
     //&& NBJets >= 3
    && NTopJets >= 1
    && var_mT <= 150
    && var_mTb >= 80)
    {
      isVR1LGtt0LII=true;
    }
  else isVR1LGtt0LII = false;

  if(NSignalLeptons == 1
    && var_Meff >= 800.0
    && var_Met >= 0.0
    && NJets >= 7
    && pass4bincl
     //&& NBJets >= 4
    && NTopJets >= 1
    && var_mT <= 150
    && var_mTb >= 80)
    {
      isVR1LGtt0LIII=true;
    }
  else isVR1LGtt0LIII = false;

  if(NSignalLeptons == 1
    && var_Meff >= 800.0
    && var_Met >= 0.0
    && NJets >= 7
    && pass4bincl
     //&& NBJets >= 4
    && NTopJets >= 0
    && var_mT <= 125
    && var_mTb >= 80)
    {
      isVR1LGtt0LIV=true;
    }
  else isVR1LGtt0LIV = false;

  if(NSignalLeptons == 0
    && var_Meff >= 900.0
    && var_Met >= 0.0
    && NJets >= 8
    && pass2bincl
     //&& NBJets >= 2
    && NTopJets >= 2
    && var_mTb < 80)
    {
      isVR0LGtt0LI=true;
    }
  else isVR0LGtt0LI = false;

  if(NSignalLeptons == 0
    && var_Meff >= 1200.0
    && var_Met >= 0.0
    && NJets >= 8
    && pass2bincl
     //&& NBJets >= 2
    && NTopJets >= 1
    && var_mTb < 80)
    {
      isVR0LGtt0LII=true;
    }
  else isVR0LGtt0LII = false;

  if(NSignalLeptons == 0
    && var_Meff >= 900.0
    && var_Met >= 0.0
    && NJets >= 8
    & pass3bincl
     //&& NBJets >= 3
    && NTopJets >= 1
    && var_mTb < 80)
    {
      isVR0LGtt0LIII=true;
    }
  else isVR0LGtt0LIII = false;

  if(NSignalLeptons == 0
    && var_Meff >= 1050.0
    && var_Met >= 0.0
    && NJets >= 8
    & pass3bincl
     //&& NBJets >= 3
    && NTopJets >= 0
    && var_mTb < 80)
    {
      isVR0LGtt0LIV=true;
    }
  else isVR0LGtt0LIV = false;

  // gtt 1L vrs
  if( NSignalLeptons >=1
     && NJets >= 6
     && pass2bexcl
     //&& NBJets == 2
     && NTopJets >=1
     && var_Met >= 0.0
     && var_Meff >= 900.0
     && var_mT > 150
     && var_mTb < 160)
    {
      isVRGtt1LI2mT2b=true;
    }
    else isVRGtt1LI2mT2b=false;

  if( NSignalLeptons >=1
     && NJets >= 6
     && pass2bexcl
     //&& NBJets == 2
     && NTopJets >=0
     && var_Met >= 0.0
     && var_Meff >= 600.0
     && var_mT > 150
     && var_mTb < 160)
    {
      isVRGtt1LII2mT2b=true;
    }
  else isVRGtt1LII2mT2b = false;
  
  if( NSignalLeptons >=1
     && NJets >= 6
     && pass2bexcl
     //&& NBJets == 2
     && NTopJets >=1
     && var_Met >= 0.0
     && var_Meff >= 1250.0
     && var_mT > 150
     && var_mTb < 160)
    {
      isVRGtt1LI4mT2b=true;
    }
  else isVRGtt1LI4mT2b = false;
  
   if( NSignalLeptons >=1
     && NJets >= 5
     && pass2bexcl
      //&& NBJets == 2
     && NTopJets >= 0
     && var_Met >= 0.0
     && var_Meff >= 750.0
     && var_mT > 150
     && var_mTb < 160)
    {
      isVRGtt1LII4mT2b=true;
    }
  else isVRGtt1LII4mT2b = false;

   if( NSignalLeptons >=1
     && NJets >= 5
     && pass3bexcl
      //&& NBJets == 3
     && NTopJets >= 1
     && var_Met >= 0.0
     && var_Meff >= 400.0
     && var_mT > 150
     && var_mTb < 160)
    {
      isVRGtt1LI2mT3b=true;
    }
  else isVRGtt1LI2mT3b = false;
   
   if( NSignalLeptons >=1
     && NJets >= 5
     && pass3bexcl
      //&& NBJets == 3
     && NTopJets >= 0
     && var_Met >= 0.0
     && var_Meff >= 400.0
     && var_mT > 150
     && var_mTb < 160)
    {
      isVRGtt1LII2mT3b=true;
    }
  else isVRGtt1LII2mT3b = false;
  
   if( NSignalLeptons >=1
     && NJets >= 5
     && pass3bexcl
      //&& NBJets == 3
     && NTopJets >= 1
     && var_Met >= 0.0
     && var_Meff >= 500
     && var_Meff <= 1300
     && var_mT > 150
     && var_mTb < 160)
    {
      isVRGtt1LI4mT3b=true;
    }
  else isVRGtt1LI4mT3b = false; 

  if( NSignalLeptons >=1
    && NJets >= 5
    && pass3bexcl
     //&& NBJets == 3
    && NTopJets >= 0
    && var_Met >= 0.0
    && var_Meff >= 600.0
    && var_mT > 150
    && var_mTb < 160)
   {
     isVRGtt1LII4mT3b=true;
   } 
  else isVRGtt1LII4mT3b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass2bexcl
     //&& NBJets == 2
    && NTopJets >= 1
    && var_Met >= 0.0
    && var_Meff >= 900.
    && var_mT < 150
    && var_mTb > 160)
    {
      isVRGtt1LI2mTb2b=true;
    }
  else isVRGtt1LI2mTb2b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass2bexcl
     //&& NBJets == 2
    && NTopJets >= 0
    && var_Met >= 0.0
    && var_Meff >= 600.0
    && var_mT < 150
    && var_mTb > 160)
    {
      isVRGtt1LII2mTb2b=true;
    }
  else isVRGtt1LII2mTb2b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass2bexcl
     //&& NBJets == 2
    && NTopJets >= 1
    && var_Met >= 0.0
    && var_Meff >= 1250.0
    && var_mT < 150
    && var_mTb > 160)
    {
      isVRGtt1LI4mTb2b=true;
    }
  else isVRGtt1LI4mTb2b = false;
       
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass2bexcl
     //&& NBJets == 2
    && NTopJets >= 0
    && var_Met >= 0.0
    && var_Meff >= 750.0
    && var_mT < 150
    && var_mTb > 160)
    {
      isVRGtt1LII4mTb2b=true;
    }
  else isVRGtt1LII4mTb2b = false;
      
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass3bexcl
     //&& NBJets == 3
    && NTopJets >= 1
    && var_Met >= 0.0
    && var_Meff >= 400.0
    && var_mT < 150
    && var_mTb > 140)
    {
     isVRGtt1LI2mTb3b =true;
    }
  else isVRGtt1LI2mTb3b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass3bexcl
     //&& NBJets == 3
    && NTopJets >= 0
    && var_Met >= 0.0
    && var_Meff >= 400.0
    && var_mT < 150
    && var_mTb > 160)
    {
      isVRGtt1LII2mTb3b=true;
    }
  else isVRGtt1LII2mTb3b = false;
   
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass3bexcl
     //&& NBJets == 3
    && NTopJets >= 1
    && var_Met >= 0.0
    && var_Meff >= 500.0
    && var_Meff <= 1300.0
    && var_mT < 150
    && var_mTb > 140)
    {
      isVRGtt1LI4mTb3b=true;
    }
  else isVRGtt1LI4mTb3b = false;
   
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass3bexcl
     //&& NBJets == 3
    && NTopJets >= 0
    && var_Met >= 0.0
    && var_Meff >= 550.0
    && var_mT < 150
    && var_mTb > 160)
    {
      isVRGtt1LII4mTb3b=true;
    }
  else isVRGtt1LII4mTb3b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 5
    && pass4bincl
     //&& NBJets == 4
    && NTopJets >= 1
    && var_Met >= 0.0
    && var_Meff >= 400.0
    && var_mT < 150
    && var_mTb > 140)
    {
      isVRGtt1LI2mT4b=true;
    }
  else isVRGtt1LI2mT4b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass4bincl
     //&& NBJets == 4
    && NTopJets >= 0
    && var_Met >= 0.0
    && var_Meff >= 400.0
    && var_mT < 150
    && var_mTb > 140)
    {
      isVRGtt1LII2mT4b=true;
    }
  else isVRGtt1LII2mT4b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass2bexcl
     //&& NBJets == 2
    && NTopJets >= 0
    && var_Met >= 0.0
    && var_Meff >= 400.0
    && var_mT > 80
    && var_mT < 110)
    {
      isVRGtt1LIII22b=true;
    }
  else isVRGtt1LIII22b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass2bexcl
     //&& NBJets == 2
    && NTopJets >= 0
    && var_Met >= 0.0
    && var_Meff >= 450.0
    && var_mT > 80
    && var_mT < 110)
    {
      isVRGtt1LIII42b=true;
    }
  else isVRGtt1LIII42b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass3bexcl
     //&& NBJets == 3
    && NTopJets >= 0
    && var_Met >= 0.0
    && var_Meff >= 400.0
    && var_mT > 80
    && var_mT < 110)
    {
      isVRGtt1LIII23b=true;
    }
  else isVRGtt1LIII23b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 6
    && pass3bexcl
     //&& NBJets == 3
    && NTopJets >= 0
    && var_Met >= 0.0
    && var_Meff >= 450.0
    && var_mT > 80
    && var_mT < 110)
    {
      isVRGtt1LIII43b=true;
    }
  else isVRGtt1LIII43b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 5
    && pass4bincl
     //&& NBJets == 4
    && NTopJets >= 0
    && var_Met >= 0.0
    && var_Meff >= 400.0
    && var_mT > 80
    && var_mT < 110)
    {
      isVRGtt1LIII24b=true;
    }
  else isVRGtt1LIII24b = false;
  
  if( NSignalLeptons >=1
    && NJets >= 5
    && pass4bincl
     //&& NBJets == 4
    && NTopJets >= 0
    && var_Met >= 0.0
    && var_Meff >= 450.0
    && var_mT > 80
    && var_mT < 110)
    {
      isVRGtt1LIII44b=true;
    }
  else isVRGtt1LIII44b = false;
 }


  int nb_cf = isTRF ? nbjets_TRF : NBJets;
  TruthAnalysis::cutflow(out_cutflow,
			 NJets,
			 NBJets,
			 NTopJets,
			 NSignalElectrons,
			 NSignalMuons,
			 NBaseElectrons,
			 NBaseMuons,
			 var_dPhiMin,
			 var_Meff,
			 var_Meff_4j,
			 var_mT,
			 var_mTb,
			 var_HT,
			 var_Met,
			 var_MetSig,
			 debug);

  out_tree->Fill();

  return;
} 

EL::StatusCode TruthAnalysis :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  static int count = 0;
  if(count==0) std::cout << "TruthAnalysis::execute() BEGIN" << std::endl;
  count++;
  if(count % 1000 == 0) std::cout << "TruthAnalysis::execute()\tProcessed " << count << " events."  << std::endl;;

  // TODO: Seed this properly
  const xAOD::JetContainer* TruthJets = 0;
  EL_RETURN_CHECK("Get jets", m_event->retrieve( TruthJets, "AntiKt4TruthJets" ) );

  static SG::AuxElement::ConstAccessor< int > GhostTaus("GhostTausFinalCount");
  static SG::AuxElement::ConstAccessor< int > GhostBHadrons("GhostBHadronsFinalCount");
  static SG::AuxElement::ConstAccessor< int > GhostCHadrons("GhostCHadronsFinalCount");

  static SG::AuxElement::ConstAccessor< float > Tau2("Tau2_wta");
  static SG::AuxElement::ConstAccessor< float > Tau3("Tau3_wta");

  ConstDataVector<xAOD::JetContainer> * SelectedJets   =  new ConstDataVector<xAOD::JetContainer>(SG::VIEW_ELEMENTS);
  ConstDataVector<xAOD::JetContainer> * SelectedBJets  =  new ConstDataVector<xAOD::JetContainer>(SG::VIEW_ELEMENTS);

  // chiara: adding vector of jets with |eta|<2.5 and pt>30. These are the ones to use to apply TRF
  //Trisha : modifying name
  ConstDataVector<xAOD::JetContainer> * InputJets_TRF  =  m_probTag ? new ConstDataVector<xAOD::JetContainer>(SG::VIEW_ELEMENTS) : NULL;

  int TruthBNum = 0;
  int TruthCNum = 0;
  int TruthTauNum = 0;

  //Trisha - input vectors for TRF
  m_sel_jets_pt.clear(); 
  m_sel_jets_eta.clear();
  m_sel_jets_phi.clear();
  m_sel_jets_truthLabel.clear();
  m_sel_jets_btag_weight.clear();
  //m_sel_jets_index.clear();

  for(const auto jet : *TruthJets){
    if(fabs(jet->eta()) < 2.8 && jet->pt() / MEV > 30.){
      SelectedJets->push_back(jet);
    }

    // handle b-jets now

    if(fabs(jet->eta()) > 2.5 || jet->pt() / MEV < 30.){
      continue;
    }
    if(m_probTag){
      // chiara: 
      InputJets_TRF->push_back(jet); //Trisha : still needed because index will refer to this vector

      //input vectors
      m_sel_jets_pt.push_back(jet->pt() / MEV); 
      m_sel_jets_eta.push_back(jet->eta());
      m_sel_jets_phi.push_back(jet->phi());
      m_sel_jets_btag_weight.push_back(0); // chiara: not really needed for out scopes, but needed for the code to compile :)
    }

    bool HasB = (GhostBHadrons(*jet) >= 1);
    bool HasC = (GhostCHadrons(*jet) >= 1);
    bool HasTau = (GhostTaus(*jet) >= 1);
    // Should we look at taus as well?
    /*
    if(HasB)
      TruthBNum++;
    if(HasC)
      TruthCNum++;

    if(HasTau)
      TruthTauNum++;
    */

    if(HasB){
      if(m_probTag){ m_sel_jets_truthLabel.push_back(5); }

      double randB = m_myRand->Rndm();
      if(randB <= 0.85){
        // then it counts as a B
        SelectedBJets->push_back(jet);
      }
    }
    else if(HasC){
      if(m_probTag){ m_sel_jets_truthLabel.push_back(4); }
      double randC = m_myRand->Rndm();
      if(randC < 0.38){
        // then it counts as a B still
        SelectedBJets->push_back(jet);
      }
    }
    else if(HasTau){
      if(m_probTag){ m_sel_jets_truthLabel.push_back(15); }
      double randTau = m_myRand->Rndm();
      if(randTau < 0.26){
	// it's  b, even so
	SelectedBJets->push_back(jet);
	}
    }
    else{ // it's a light jet in truth
      if(m_probTag){ m_sel_jets_truthLabel.push_back(0); }
      double randL = m_myRand->Rndm();
      if(randL < 0.036){
        SelectedBJets->push_back(jet);
      }
    }
  }//jet loop


  // Jet Reclustering!
  ConstDataVector<xAOD::JetContainer> * SelectedRCJets   =  new ConstDataVector<xAOD::JetContainer>(SG::VIEW_ELEMENTS);
  ConstDataVector<xAOD::JetContainer> * SelectedTopJets   =  new ConstDataVector<xAOD::JetContainer>(SG::VIEW_ELEMENTS);

  m_reclusteringTool->execute();
  const xAOD::JetContainer* RC10TruthJets = 0;
  m_event->retrieve( RC10TruthJets, "RC10TruthJets");
  for(const auto jet : *RC10TruthJets)
    {
      if(fabs(jet->eta()) < 2.0 && (jet->pt() / MEV) > 300.0)
	{
	  SelectedRCJets->push_back(jet);
	  	 
	  if((jet->m() / MEV) > 100.0)
	    {
	      SelectedTopJets->push_back(jet);
	    }
	}
    }

  const xAOD::TruthParticleContainer* TruthElectrons = 0;
  EL_RETURN_CHECK("Get electrons", m_event->retrieve( TruthElectrons, "TruthElectrons" ) );

  // check pt cut on leptons; susytools defaults to 10.
  ConstDataVector<xAOD::TruthParticleContainer> * SignalElectrons    =  new ConstDataVector<xAOD::TruthParticleContainer>(SG::VIEW_ELEMENTS);
  ConstDataVector<xAOD::TruthParticleContainer> * BaselineElectrons  =  new ConstDataVector<xAOD::TruthParticleContainer>(SG::VIEW_ELEMENTS);

  for(const auto electron : *TruthElectrons)
    {
     if(fabs(electron->eta()) < 2.47 && electron->pt() / MEV > 20.)
	{
	  SignalElectrons->push_back(electron);
	}
      if(fabs(electron->eta()) < 2.47 && electron->pt() / MEV > 20.)
	{
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
    if(fabs(muon->eta()) < 2.5 && muon->pt() / MEV > 20.){
      BaselineMuons->push_back(muon);
    }
  }

  const xAOD::MissingETContainer* TruthMET = 0;
  EL_RETURN_CHECK("Get MET", m_event->retrieve( TruthMET, "MET_Truth" ) );
  
  xAOD::MissingETContainer::const_iterator TruthMET_it = TruthMET->find("NonInt");
  if (TruthMET_it == TruthMET->end()) std::cout << "No NonINT inside MET container" << std::endl;  
  xAOD::MissingET* TruthMET_NonInt = *TruthMET_it;

  TruthMET_it = TruthMET->find("Int");
  if (TruthMET_it == TruthMET->end()) std::cout << "No INT inside MET container" << std::endl;
  xAOD::MissingET* TruthMET_Int = *TruthMET_it;

  //std::cout << "MET " << TruthMET_NonInt->met()/1000.0 << "\t" << TruthMET_Int->met()/1000.0 << std::endl;

  var_dPhiMin = Variables::delta_phi_nj(TruthMET_NonInt, SelectedJets->asDataVector(), SelectedJets->size()); // Should it be this MET?
  var_Meff = Variables::Meff_incl(TruthMET_NonInt, SelectedJets->asDataVector(), SignalMuons->asDataVector(), SignalElectrons->asDataVector());
  var_Meff_4j = Variables::Meff_4j(TruthMET_NonInt, SelectedJets->asDataVector(), 4 /* How many jets to use? */);
  var_mT = Variables::mT(TruthMET_NonInt, SignalMuons->asDataVector(), SignalElectrons->asDataVector());
  var_HT = Variables::Ht(SelectedJets->asDataVector(), SignalMuons->asDataVector(), SignalElectrons->asDataVector());
  var_Met = TruthMET_NonInt->met()/1000.0;
  //var_Met = TruthMET_Int->met()/1000.0;
  var_MetSig = Variables::Met_significance(TruthMET_NonInt, SelectedJets->asDataVector(), 4 /* How many jets to use in HT? */);

  var_dPhiMin = 1.0; // REMOVED TO TEST, MLB ON 11-11-15

  NSignalElectrons = SignalElectrons->size();
  NSignalMuons     = SignalMuons->size();
  NBaseElectrons   = BaselineElectrons->size();
  NBaseMuons       = BaselineMuons->size();
  NJets	  	       = SelectedJets->size();
  //NBJets           = SelectedBJets->size();
  NTopJets	       = SelectedTopJets->size();
  
  NSignalLeptons   = NSignalElectrons + NSignalMuons;
  NBaseLeptons     = NBaseElectrons + NBaseMuons;

  if(SignalMuons->size()>0) var_mu_pt = SignalMuons->at(0)->pt() / MEV;
  if(SignalMuons->size()>0) var_mu_eta = SignalMuons->at(0)->eta();
  if(SignalMuons->size()>0) var_mu_phi = SignalMuons->at(0)->phi();
  if(SignalMuons->size()>0) var_mu_e = SignalMuons->at(0)->e() / MEV;

  if(SignalElectrons->size()>0) var_el_pt = SignalElectrons->at(0)->pt() / MEV;
  if(SignalElectrons->size()>0) var_el_eta = SignalElectrons->at(0)->eta();
  if(SignalElectrons->size()>0) var_el_phi = SignalElectrons->at(0)->phi();
  if(SignalElectrons->size()>0) var_el_e = SignalElectrons->at(0)->e() / MEV;

  if(SelectedJets->size()>0) var_jet_pt_1 = SelectedJets->at(0)->pt() / MEV;
  if(SelectedJets->size()>1) var_jet_pt_2 = SelectedJets->at(1)->pt() / MEV;
  if(SelectedJets->size()>2) var_jet_pt_3 = SelectedJets->at(2)->pt() / MEV;
  if(SelectedJets->size()>3) var_jet_pt_4 = SelectedJets->at(3)->pt() / MEV;
  if(SelectedJets->size()>0) var_jet_eta_1 = SelectedJets->at(0)->eta();
  if(SelectedJets->size()>1) var_jet_eta_2 = SelectedJets->at(1)->eta();
  if(SelectedJets->size()>2) var_jet_eta_3 = SelectedJets->at(2)->eta();
  if(SelectedJets->size()>3) var_jet_eta_4 = SelectedJets->at(3)->eta();
  if(SelectedJets->size()>0) var_jet_phi_1 = SelectedJets->at(0)->phi();
  if(SelectedJets->size()>1) var_jet_phi_2 = SelectedJets->at(1)->phi();
  if(SelectedJets->size()>2) var_jet_phi_3 = SelectedJets->at(2)->phi();
  if(SelectedJets->size()>3) var_jet_phi_4 = SelectedJets->at(3)->phi();
  if(SelectedJets->size()>0) var_jet_e_1 = SelectedJets->at(0)->e() / MEV;
  if(SelectedJets->size()>1) var_jet_e_2 = SelectedJets->at(1)->e() / MEV;
  if(SelectedJets->size()>2) var_jet_e_3 = SelectedJets->at(2)->e() / MEV;
  if(SelectedJets->size()>3) var_jet_e_4 = SelectedJets->at(3)->e() / MEV;

  if(SelectedRCJets->size()>0) var_rcjet_pt_1 = SelectedRCJets->at(0)->pt() / MEV;
  if(SelectedRCJets->size()>1) var_rcjet_pt_2 = SelectedRCJets->at(1)->pt() / MEV;
  if(SelectedRCJets->size()>2) var_rcjet_pt_3 = SelectedRCJets->at(2)->pt() / MEV;
  if(SelectedRCJets->size()>3) var_rcjet_pt_4 = SelectedRCJets->at(3)->pt() / MEV;
  if(SelectedRCJets->size()>0) var_rcjet_eta_1 = SelectedRCJets->at(0)->eta();
  if(SelectedRCJets->size()>1) var_rcjet_eta_2 = SelectedRCJets->at(1)->eta();
  if(SelectedRCJets->size()>2) var_rcjet_eta_3 = SelectedRCJets->at(2)->eta();
  if(SelectedRCJets->size()>3) var_rcjet_eta_4 = SelectedRCJets->at(3)->eta();
  if(SelectedRCJets->size()>0) var_rcjet_phi_1 = SelectedRCJets->at(0)->phi();
  if(SelectedRCJets->size()>1) var_rcjet_phi_2 = SelectedRCJets->at(1)->phi();
  if(SelectedRCJets->size()>2) var_rcjet_phi_3 = SelectedRCJets->at(2)->phi();
  if(SelectedRCJets->size()>3) var_rcjet_phi_4 = SelectedRCJets->at(3)->phi();
  if(SelectedRCJets->size()>0) var_rcjet_mass_1 = SelectedRCJets->at(0)->m() / MEV;
  if(SelectedRCJets->size()>1) var_rcjet_mass_2 = SelectedRCJets->at(1)->m() / MEV;
  if(SelectedRCJets->size()>2) var_rcjet_mass_3 = SelectedRCJets->at(2)->m() / MEV;
  if(SelectedRCJets->size()>3) var_rcjet_mass_4 = SelectedRCJets->at(3)->m() / MEV;
  
  Bool_t isOneLepton=false; isOneLepton = (NSignalLeptons == 1);
  Bool_t isZeroLepton=false; isZeroLepton = (NBaseLeptons == 0);

  const xAOD::EventInfo* EventInfo = 0;
  m_event->retrieve(EventInfo, "EventInfo");
  
  mc_channel=-1.0;
  mc_weight = EventInfo->mcEventWeights().at(0);


  //--------------- All of the above do not need bjets --------------------
  //Only var_mTb has to be recalculated


  if(m_probTag){
    // chiara
    float TRF_weight_appo = compute_TRF();
    //float TRF_weight_appo = compute_TRF();

    //Trisha
    //2bex, 3bex, 4bex, 5bin 
    
    for( int i = 2; i <=4; i++ ){
      ConstDataVector<xAOD::JetContainer> * SelectedBJets_TRF_in = new ConstDataVector<xAOD::JetContainer>(SG::VIEW_ELEMENTS);
      ConstDataVector<xAOD::JetContainer> * SelectedBJets_TRF_ex = new ConstDataVector<xAOD::JetContainer>(SG::VIEW_ELEMENTS);
      int jind = 0;

      for(const auto jet : *InputJets_TRF){
	bool isB_ex = false;
	bool isB_in = false;
	if(i == 2){ 
	  isB_ex = m_jets_isb_85_TRF_2excl.at(jind); 
	  isB_in = m_jets_isb_85_TRF_2incl.at(jind); 
	}
	else if(i == 3){
	  isB_ex = m_jets_isb_85_TRF_3excl.at(jind); 
	  isB_in = m_jets_isb_85_TRF_3incl.at(jind); 
	}
	else if(i == 4){
	  isB_in = m_jets_isb_85_TRF_4incl.at(jind); 
	}
	if(isB_in){ SelectedBJets_TRF_in->push_back(jet);}
	if(isB_ex){ SelectedBJets_TRF_ex->push_back(jet);}
	jind++;
      }//jet loop
      //std::cout<<"i = "<<i<<" SelectedBJets_TRF_in.size() = "<<SelectedBJets_TRF_in->size()
      //<<" SelectedBJets_TRF_ex.size() = "<<SelectedBJets_TRF_ex->size()<<" InputJets_TRF.size() = "<<InputJets_TRF->size()<<std::endl;
      processEventPerBMultiplicity(SelectedBJets_TRF_in, SelectedJets, TruthMET_NonInt, true, true, i);
      if(i < 4){ processEventPerBMultiplicity(SelectedBJets_TRF_ex, SelectedJets, TruthMET_NonInt, true, false, i); }
      
      delete SelectedBJets_TRF_in;
      delete SelectedBJets_TRF_ex;
      
    }//b-multiplicity
    
  } //if TRF-tagging

  processEventPerBMultiplicity(SelectedBJets, SelectedJets, TruthMET_NonInt); 

  /*
  delete InputJets_TRF;
  delete SelectedJets;
  delete SelectedBJets;
  delete SelectedRCJets;
  delete SelectedTopJets;

  delete SignalElectrons;
  delete SignalMuons;
  delete BaselineElectrons;
  delete BaselineMuons;
  */
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

EL::StatusCode TruthAnalysis :: cutflow (TH1F*& hist,
					 Int_t v_NJets,
					 Int_t v_NBJets,
					 Int_t v_NTopJets,
					 Int_t v_NSigEl,
					 Int_t v_NSigMu,
					 Int_t v_NBaseEl,
                                         Int_t v_NBaseMu,
					 Float_t v_dPhiMin,
					 Float_t v_Meff,
					 Float_t v_Meff_4j,
					 Float_t v_mT,
					 Float_t v_mTb,
					 Float_t v_HT,
					 Float_t v_Met,
					 Float_t v_MetSig,
					 Bool_t debug)
{
  hist->Fill("all",1.0);

  // Want to match e.g. https://twiki.cern.ch/twiki/pub/AtlasProtected/SusyMultibjetAnalysis/cut_flow_2015_09_16.pdf

  /*
    Initial 3815132
    met_truth_filter>200 3798844
    HLT_xe70 3738328
    >=4 signal jets with pT > 30 GeV 2477655
    >=1 signal electron (pt>20 GeV) 420495
    >=1 signal muon 420331
    ==0 baseline lepton 1556221
    met > 250 GeV 1063291
    dphi(met,jets)>0.4 1577063
    >=3 b-jets (85% OP) 391194
    meff > 1000 GeV 648457
    mtmin(b,MET)>160 GeV 650960
    >=1 top-tagged loose 785494
    >=1 top-tagged tight 502097
    >=1 top-tagged looser 718243
  */

  if(v_Met>200.0) hist->Fill("MET_200",1.0);
  else return EL::StatusCode::SUCCESS;

  if(v_NJets>=4)  hist->Fill("jets4",1.0);
  else return EL::StatusCode::SUCCESS;

  if(v_NSigEl>=1)  hist->Fill("NSigEl1",1.0);
  if(v_NSigMu>=1)  hist->Fill("NSigMu1",1.0);
  if((v_NBaseMu+v_NBaseEl)==0)  hist->Fill("ZeroLep",1.0);

  if(v_Met>250.0) hist->Fill("MET_250",1.0);

  //if(v_dPhiMin>0.4) hist->Fill("dPhiMin04",1.0);

  if(v_NBJets>=3) hist->Fill("bjets3",1.0);

  if(v_Meff>1000.0) hist->Fill("MEFF_1000",1.0);

  if(v_mTb>160.0) hist->Fill("MTB_160",1.0);

  if(v_NTopJets>=1) hist->Fill("VLooseTop",1.0);
  
  return EL::StatusCode::SUCCESS;
}

//Float_t TruthAnalysis :: compute_TRF(ConstDataVector<xAOD::JetContainer> * SelectedBJets_TRF){
Float_t TruthAnalysis :: compute_TRF(){

  // chiara: clear TRF verctors Trisha : output vectors
  m_TRFweight_in.clear();
  m_TRFweight_ex.clear();
  m_TRFPerm_in.clear();
  m_TRFPerm_ex.clear();
  m_jets_isb_85_TRF_2excl.clear();
  m_jets_isb_85_TRF_2incl.clear();
  m_jets_isb_85_TRF_3excl.clear();
  m_jets_isb_85_TRF_3incl.clear();
  m_jets_isb_85_TRF_4incl.clear();

  for(int i = 0; i < m_sel_jets_truthLabel.size(); i++){
    m_jets_isb_85_TRF_2excl.push_back(0);
    m_jets_isb_85_TRF_2incl.push_back(0);
    m_jets_isb_85_TRF_3excl.push_back(0);
    m_jets_isb_85_TRF_3incl.push_back(0);
    m_jets_isb_85_TRF_4incl.push_back(0);
  }

  /*
  for(const auto jet : *SelectedBJets_TRF){
    // chiara: typically pt needs to be in MeV, for this firs iteration is in GeV because I used GeV for CDI file. 
    // In this case, GeV or MeV does not change anythig as there is only one val in the map
    m_sel_jets_pt.push_back(jet->pt() / MEV); 
    m_sel_jets_eta.push_back(jet->eta());
    m_sel_jets_phi.push_back(jet->phi());
    sel_jets_btag_weight.push_back(0); // chiara: not really needed for out scopes, but needed for the code to compile :)
    bool HasB = (GhostBHadrons(*jet) >= 1);
    bool HasC = (GhostCHadrons(*jet) >= 1);
    bool HasTau = (GhostTaus(*jet) >= 1);
    if(HasB) m_sel_jets_truthLabel.push_back(5);
    else 
      if(HasC) m_sel_jets_truthLabel.push_back(4);
      else 
	if(HasTau) m_sel_jets_truthLabel.push_back(15);
	else
	  m_sel_jets_truthLabel.push_back(0);

    m_jets_isb_85_TRF_2excl.push_back(0);
    m_jets_isb_85_TRF_2incl.push_back(0);
    m_jets_isb_85_TRF_3excl.push_back(0);
    m_jets_isb_85_TRF_3incl.push_back(0);
    m_jets_isb_85_TRF_4incl.push_back(0);
  }
  */

  if(m_sel_jets_truthLabel.size()>0){
    m_TRF->setSeed(m_sel_jets_pt.at(0) + m_sel_jets_pt.size());
    m_TRF->setJets(m_sel_jets_pt, m_sel_jets_eta, m_sel_jets_truthLabel, m_sel_jets_btag_weight);
    m_TRF->getTRFweights("CumDef",4,m_TRFweight_ex,m_TRFweight_in);

    m_TRF->chooseTagPermutation("CumDef",4,m_TRFPerm_ex,m_TRFPerm_in);

    for(size_t i=0; i<m_sel_jets_pt.size(); i++){
      if(m_TRFPerm_ex.at(2).size()>0)   if(m_TRFPerm_ex.at(2).at(i)) m_jets_isb_85_TRF_2excl.at(i)=1;
      if(m_TRFPerm_in.at(2).size()>0)   if(m_TRFPerm_in.at(2).at(i)) m_jets_isb_85_TRF_2incl.at(i)=1;
      if(m_TRFPerm_ex.at(3).size()>0)   if(m_TRFPerm_ex.at(3).at(i)) m_jets_isb_85_TRF_3excl.at(i)=1;
      if(m_TRFPerm_in.at(3).size()>0)   if(m_TRFPerm_in.at(3).at(i)) m_jets_isb_85_TRF_3incl.at(i)=1;
      if(m_TRFPerm_in.at(4).size()>0)   if(m_TRFPerm_in.at(4).at(i)) m_jets_isb_85_TRF_4incl.at(i)=1;
    }


    m_TRFweight_2excl = m_TRFweight_ex.at(2);
    m_TRFweight_2incl = m_TRFweight_in.at(2);
    m_TRFweight_3excl = m_TRFweight_ex.at(3);
    m_TRFweight_3incl = m_TRFweight_in.at(3);
    m_TRFweight_4incl = m_TRFweight_in.at(4);
  }
  else{
    m_TRFweight_2excl = 0;
    m_TRFweight_2incl = 0;
    m_TRFweight_3excl = 0;
    m_TRFweight_3incl = 0;
    m_TRFweight_4incl = 0;
  }

  return m_TRFweight_2excl;

}
