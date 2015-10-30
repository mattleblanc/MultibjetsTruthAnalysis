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
#include "TFile.h"

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

  out_tree = new TTree("out_tree", "output tree");
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

  //TTree* out_tree; out_tree = new TTree("out_tree","output tree");
  TFile *file = wk()->getOutputFile ("outTree");
  out_tree->SetDirectory (file);
  
  out_tree->Branch("all_events",&m_all_events,"all_events/I");
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
  out_tree->Branch("isGtt0LSRB",&isGtt0LSRA,"isGtt0LSRB/I");
  out_tree->Branch("isGtt0LSRC",&isGtt0LSRA,"isGtt0LSRC/I");
  out_tree->Branch("isGtt0LSRD",&isGtt0LSRA,"isGtt0LSRD/I");

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

  //std::cout << " Measured " << SelectedBJets->size() << " truth number " << TruthBNum << std::endl;

  // Jet Reclustering!
  ConstDataVector<xAOD::JetContainer> * SelectedRCJets   =  new ConstDataVector<xAOD::JetContainer>(SG::VIEW_ELEMENTS);
  ConstDataVector<xAOD::JetContainer> * SelectedTopJets   =  new ConstDataVector<xAOD::JetContainer>(SG::VIEW_ELEMENTS);

  m_reclusteringTool->execute();
  const xAOD::JetContainer* RC10TruthJets = 0;
  m_event->retrieve( RC10TruthJets, "RC10TruthJets");
  for(const auto jet : *RC10TruthJets)
    {
      if(fabs(jet->eta()) < 2.0 && jet->pt() / MEV > 300.0)
	{
	  SelectedRCJets->push_back(jet);

	  if(jet->m() / MEV > 100.0)
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
      if(fabs(electron->eta()) < 2.47 && electron->pt() / MEV > 10.)
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
    if(fabs(muon->eta()) < 2.5 && muon->pt() / MEV > 10.){
      BaselineMuons->push_back(muon);
    }
  }

  const xAOD::MissingETContainer* TruthMET = 0;
  EL_RETURN_CHECK("Get MET", m_event->retrieve( TruthMET, "MET_Truth" ) );

  xAOD::MissingETContainer::const_iterator TruthMET_it = TruthMET->find("NonInt");
  if (TruthMET_it == TruthMET->end()) std::cout << "No NonINT inside MET container" << std::endl;
  xAOD::MissingET* TruthMET_NonInt = *TruthMET_it;

  float var_dPhiMin = Variables::delta_phi_nj(TruthMET_NonInt, TruthJets, TruthJets->size()); // Should it be this MET?
  float var_Meff = Variables::Meff_incl(TruthMET_NonInt, TruthJets, TruthMuons, TruthElectrons);
  float var_Meff_4j = Variables::Meff_4j(TruthMET_NonInt, TruthJets, 4 /* How many jets to use? */);
  float var_mT = Variables::mT(TruthMET_NonInt, TruthMuons, TruthElectrons);
  float var_mTb = Variables::mT_min_bjets(TruthMET_NonInt, TruthJets, false /* set_mw? */);
  float var_HT = Variables::Ht(TruthJets, TruthMuons, TruthElectrons);
  float var_Met = TruthMET_NonInt->met()/1000.0;
  float var_MetSig = Variables::Met_significance(TruthMET_NonInt, TruthJets, 4 /* How many jets to use in HT? */);


  int NSignalElectrons = SignalElectrons->size();
  int NSignalMuons     = SignalMuons->size();
  int NBaseElectrons   = BaselineElectrons->size();
  int NBaseMuons       = BaselineMuons->size();
  int NJets	       = SelectedJets->size();
  int NBJets           = SelectedBJets->size();
  int NTopJets	       = SelectedTopJets->size();

  int NSignalLeptons   = NSignalElectrons + NSignalMuons;
  int NBaseLeptons     = NBaseElectrons + NBaseMuons;

  bool isOneLepton; isOneLepton = (NSignalLeptons == 1);
  bool isZeroLepton; isZeroLepton = (NBaseLeptons == 0);
  
  // debug variables
  /*
  std::cout << "var_dPhiMin is " << var_dPhiMin << std::endl;
  std::cout << "var_Meff is " << var_Meff << std::endl;
  std::cout << "var_mT is " << var_mT << std::endl;
  std::cout << "var_HT is " << var_HT << std::endl;
  std::cout << "var_Met is " << var_Met << std::endl;
  std::cout << "var_MetSig is " << var_MetSig << std::endl;
  std::cout << "NJets is " << NJets << std::endl;
  std::cout << "NBJets is " << NBJets << std::endl;
  */

  /*
    Commented lines such as 'configMgr.cutsDict*' are taken from the HistFitter config file ... it can be found here:
    https://svnweb.cern.ch/trac/atlasphys-susy/browser/Physics/SUSY/Analyses/MultiBJets/HistFitter/trunk/ananlisis_multib/python/My3bGtt.py
    ... they're just for my own reference, so don't please don't fuss about them too much.
  */

  // Gtt 1 lepton region
  if(isOneLepton)
    {
      //configMgr.cutsDict["Presel_Gtt_1l"] = "(signal_electrons_n + signal_muons_n)>=1 && jets_n>=6 && bjets_n>=3 && met>200 && meff_incl<1000."
      if(NSignalLeptons >= 1
         && NJets >= 6
         && NBJets >= 3
         && var_Met > 200.0
         && var_Meff < 1000.0) // Gtt 1L preselection
	{
	  isPreselect_Gtt_1l = true;
	}
      else isPreselect_Gtt_1l = false;
    }

  // Gbb preselection and Gtt 0 lepton preselection regions
  if(isZeroLepton)
    {
      //configMgr.cutsDict["Presel_Gbb"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && jets_n>=4 && bjets_n>=3 && met>200 && meff_4j < 1000."
      if(NBaseLeptons == 0
         && var_dPhiMin > 0.4
         && NJets >= 4
         && NBJets >= 3
         && var_Met > 200.0
         && var_Meff_4j < 1000.0) // Gbb 0L preselection
	{
          isPreselect_Gbb = true;
        }
      else isPreselect_Gbb = false;

      //configMgr.cutsDict["Presel_Gtt_0l"] = "(signal_electrons_n + signal_muons_n)==0 && jets_n>=6 && bjets_n>=3 && met>200 && meff_incl<1000."
      if(NBaseLeptons == 0
         && NJets >= 6
         && NBJets >= 3
         && var_Met > 200.0
         && var_Meff < 1000.0) // Gtt 0L Preselection
	{
	  isPreselect_Gtt_0l = true;
	}
      else isPreselect_Gtt_0l = false;
    }

  isPreselect = (isPreselect_Gbb || isPreselect_Gtt_0l || isPreselect_Gtt_1l);
  //if(!isPreselect) continue;

  // Gbb SR flags
  //bool isGbbSRA1=false, isGbbSRB1=false, isGbbSRA2=false, isGbbSRB2=false, isGbbSRC2=false, isGbbSRA4=false, isGbbSRB4=false;
  if(isPreselect_Gbb)
    {
      //configMgr.cutsDict["SR_Gbb_A_1"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>50 && pt_bjet_3>50 && met>300 && meff_4j>1600"
      if(var_dPhiMin > 0.4
	 && SelectedJets->size() >= 4
	 && SelectedJets->at(3)->pt()/MEV > 50.0
	 && SelectedBJets->at(2)->pt()/MEV > 50.0
	 && var_Met > 300.0
	 && var_Meff_4j > 1600.0)
	{
	  isGbbSRA1=true;
	}
      else isGbbSRA1=false;

      //configMgr.cutsDict["SR_Gbb_B_1"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>70 && pt_bjet_3>70 && met>400 && meff_4j>800"
      if(var_dPhiMin > 0.4
	 && SelectedJets->size() >= 4
         && SelectedJets->at(3)->pt()/MEV > 70.0
         && SelectedBJets->at(2)->pt()/MEV > 70.0
         && var_Met > 400.0
         && var_Meff_4j > 800.0)
        {
          isGbbSRB1=true;
        }
      else isGbbSRB1=false;


      //configMgr.cutsDict["SR_Gbb_A_2"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>90 && pt_bjet_3>90 && met>350 && meff_4j>1400"
      if(var_dPhiMin > 0.4
	 && SelectedJets->size() >= 4
         && SelectedJets->at(3)->pt()/MEV > 90.0
         && SelectedBJets->at(2)->pt()/MEV > 90.0
         && var_Met > 350.0
         && var_Meff_4j > 1400.0)
        {
          isGbbSRA2=true;
        }
      else isGbbSRA2=false;

      //configMgr.cutsDict["SR_Gbb_B_2"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>90 && pt_bjet_3>90 && met>400 && meff_4j>1200"
      if(var_dPhiMin > 0.4
	 && SelectedJets->size() >= 4
         && SelectedJets->at(3)->pt()/MEV > 90.0
         && SelectedBJets->at(2)->pt()/MEV > 90.0
         && var_Met > 400.0
         && var_Meff_4j > 1200.0)
        {
          isGbbSRB2=true;
        }
      else isGbbSRB2=false;

      //configMgr.cutsDict["SR_Gbb_C_2"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>30 && pt_bjet_3>30 && met>500 && meff_4j>1400"
      if(var_dPhiMin > 0.4
	 && SelectedJets->size() >= 4
         && SelectedJets->at(3)->pt()/MEV > 50.0
         && SelectedBJets->at(2)->pt()/MEV > 50.0
         && var_Met > 300.0
         && var_Meff_4j > 1600.0)
        {
          isGbbSRC2=true;
        }
      else isGbbSRC2=false;

      //configMgr.cutsDict["SR_Gbb_A_4"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>90 && pt_bjet_3>90 && met>350 && meff_4j>1600"
      if(var_dPhiMin > 0.4
	 && SelectedJets->size() >= 4
         && SelectedJets->at(3)->pt()/MEV > 90.0
         && SelectedBJets->at(2)->pt()/MEV > 90.0
         && var_Met > 350.0
         && var_Meff_4j > 1600.0)
        {
          isGbbSRA4=true;
        }
      else isGbbSRA4=false;

      //configMgr.cutsDict["SR_Gbb_B_4"] = "(baseline_electrons_n + baseline_muons_n)==0 && dphi_min>0.4 && pt_jet_4>90 && pt_bjet_3>90 && met>450 && meff_4j>1400"
      if(var_dPhiMin > 0.4
	 && SelectedJets->size() >= 4
         && SelectedJets->at(3)->pt()/MEV > 90.0
         && SelectedBJets->at(2)->pt()/MEV > 90.0
         && var_Met > 450.0
         && var_Meff_4j > 1400.0)
        {
          isGbbSRB4=true;
        }
      else isGbbSRB4=false;
    }

  // Gtt 1L SR flags
  //bool isGtt1LSRA2=false, isGtt1LSRB2=false, isGtt1LSRC2=false, isGtt1LSRA4=false, isGtt1LSRB4=false, isGtt1LSRC4=false;
  if(isPreselect_Gtt_1l)
    {
      // And here, the various one-lepton signal regions ...

      //configMgr.cutsDict["SR_Gtt_1l_A_2"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>160 && jets_n>=6 && bjets_n>=3 && top_n>=1 && met>200 && meff_incl>1100"
      if(var_mT > 150
         && var_mTb > 160
	 && NJets >= 6
	 && NBJets >= 3
	 && NTopJets >= 1
         && var_Met > 200.0
         && var_Meff > 1100.0)
        {
          isGtt1LSRA2=true;
        }
      else isGtt1LSRA2=false;

      //configMgr.cutsDict["SR_Gtt_1l_B_2"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>160 && jets_n>=6 && bjets_n>=3 && top_n>=0 && met>300 && meff_incl>900"
      if(var_mT > 150
         && var_mTb > 160
	 && NJets >= 6
         && NBJets >= 3
	 && NTopJets >= 0
         && var_Met > 300.0
         && var_Meff > 900.0)
        {
          isGtt1LSRB2=true;
        }
      else isGtt1LSRB2=false;

      //configMgr.cutsDict["SR_Gtt_1l_C_2"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>0   && jets_n>=6 && bjets_n>=4 && top_n>=0 && met>200 && meff_incl>600"
      if(var_mT > 150
	 && NJets >= 6
         && NBJets >= 4
         && NTopJets >= 0
         && var_Met > 200.0
         && var_Meff > 600.0)
        {
          isGtt1LSRC2=true;
        }
      else isGtt1LSRC2=false;

      //configMgr.cutsDict["SR_Gtt_1l_A_4"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>160 && jets_n>=6 && bjets_n>=3 && top_n>=1 && met>250 && meff_incl>1600"
      if(var_mT > 150
         && var_mTb > 160
          && NJets >= 6
         && NBJets >= 3
         && NTopJets >= 1
         && var_Met > 250.0
         && var_Meff > 1600.0)
        {
          isGtt1LSRA4=true;
        }
      else isGtt1LSRA4=false;

      //configMgr.cutsDict["SR_Gtt_1l_B_4"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>160 && jets_n>=6 && bjets_n>=3 && top_n>=0 && met>350 && meff_incl>1100"
      if(var_mT > 150
         && var_mTb > 160
	 && NJets >= 6
         && NBJets >= 3
         && NTopJets >= 0
         && var_Met > 350.0
         && var_Meff > 1100.0)
        {
          isGtt1LSRB4=true;
        }
      else isGtt1LSRB4=false;

      //configMgr.cutsDict["SR_Gtt_1l_C_4"] = "(signal_electrons_n + signal_muons_n)>=1 && mT>150 && mTb_min>0   && jets_n>=6 && bjets_n>=4 && top_n>=0 && met>250 && meff_incl>700"
      if(var_mT > 150
	 && NJets >= 6
         && NBJets >= 4
         && NTopJets >= 0
         && var_Met > 250.0
         && var_Meff > 700.0)
        {
          isGtt1LSRC4=true;
        }
      else isGtt1LSRC4=false;

   }

  // Gtt 0L signal region flags
  //bool isGtt0LSRA=false, isGtt0LSRB=false, isGtt0LSRC=false, isGtt0LSRD=false;
  if(isPreselect_Gtt_0l)
    {
      // And here, the various zero-lepton signal regions ...

      //configMgr.cutsDict["SR_Gtt_0l_A"] = "(signal_electrons_n + signal_muons_n)==0 && dphi_min>0.4 && mTb_min>80 && jets_n>=8 && bjets_n>=4 && top_n>=0 && met>350 && meff_incl>1250
      if(var_dPhiMin > 0.4
	 && var_mTb > 80
         && NJets >= 8
         && NBJets >= 4
         && NTopJets >= 0
         && var_Met > 350.0
         && var_Meff > 1250.0)
        {
          isGtt0LSRA=true;
        }
      else isGtt0LSRA=false;

      //configMgr.cutsDict["SR_Gtt_0l_B"] = "(signal_electrons_n + signal_muons_n)==0 && dphi_min>0.4 && mTb_min>80 && jets_n>=8 && bjets_n>=4 && top_n>=1 && met>350 && meff_incl>1250"
      if(var_dPhiMin > 0.4
	 && var_mTb > 80
         && NJets >= 8
         && NBJets >= 4
         && NTopJets >= 1
         && var_Met > 350.0
         && var_Meff > 1250.0)
        {
          isGtt0LSRB=true;
        }
      else isGtt0LSRB=false;

      //configMgr.cutsDict["SR_Gtt_0l_C"] = "(signal_electrons_n + signal_muons_n)==0 && dphi_min>0.4 && mTb_min>80 && jets_n>=8 && bjets_n>=3 && top_n>=1 && met>400 && meff_incl>1700"
      if(var_dPhiMin > 0.4
	 && var_mTb > 80
         && NJets >= 8
         && NBJets >= 3
         && NTopJets >= 1
         && var_Met > 400.0
         && var_Meff > 1700.0)
        {
          isGtt0LSRC=true;
        }
      else isGtt0LSRC=false;

      //configMgr.cutsDict["SR_Gtt_0l_D"] = "(signal_electrons_n + signal_muons_n)==0 && dphi_min>0.4 && mTb_min>80 && jets_n>=8 && bjets_n>=3 && top_n>=2 && met>400 && meff_incl>1700"
      if(var_dPhiMin > 0.4
	 && var_mTb > 80
         && NJets >= 8
         && NBJets >= 3
         && NTopJets >= 2
         && var_Met > 400.0
         && var_Meff > 1700.0)
        {
          isGtt0LSRD=true;
        }
      else isGtt0LSRD=false;
    }

  if(isGbbSRA1 || isGbbSRB1 || isGbbSRA2 || isGbbSRB2 || isGbbSRC2 || isGbbSRA4 || isGbbSRB4)
    std::cout << "Gbb 0L SR" << std::endl;

  if(isGtt1LSRA2 || isGtt1LSRB2 || isGtt1LSRC2 || isGtt1LSRA4 || isGtt1LSRB4 || isGtt1LSRC4)
    std::cout << "Gtt 1L SR" << std::endl;

  if(isGtt0LSRA || isGtt0LSRB || isGtt0LSRC || isGtt0LSRD)
    std::cout << "Gtt 0L SR" << std::endl;

  out_tree->Fill();

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
