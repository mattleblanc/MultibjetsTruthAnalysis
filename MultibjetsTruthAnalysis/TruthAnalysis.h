#ifndef MultibjetsTruthAnalysis_TruthAnalysis_H
#define MultibjetsTruthAnalysis_TruthAnalysis_H

#include <EventLoop/Algorithm.h>

#include "MultibjetsTruthAnalysis/Variables.h"

#include "EventLoop/OutputStream.h"

#include "TTree.h"
#include "TH1F.h"

// reclustering forward declaration
class JetReclusteringTool;

// chiara
class TRFinterface;

//Trisha
class TRandom3;
// chiara: including the TRF package   
// #include "BtaggingTRFandRW/TRFinterface.h"
#include <vector>

namespace xAOD{ 
  class TEvent;
}

class TruthAnalysis : public EL::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:
  // float cutValue;

  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
public:
  // Tree *myTree; //!
  // TH1 *myHist; //!

  TRandom3* m_myRand;
  xAOD::TEvent*  m_event; //!

  // this is a standard constructor
  TruthAnalysis ();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  // this is needed to distribute the algorithm to the workers
  ClassDef(TruthAnalysis, 1);

  // cutflow
  EL::StatusCode cutflow(TH1F*& hist,
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
			 Bool_t debug);

 private:
  JetReclusteringTool* m_reclusteringTool = nullptr; //!

  //Trisha:
  void processEventPerBMultiplicity(ConstDataVector<xAOD::JetContainer> * SelectedBJets
				    , ConstDataVector<xAOD::JetContainer> * SelectedJets
				    , xAOD::MissingET* TruthMET_NonInt
				    , bool isTRF=false, bool isTRF_incl=false, int nbjets_TRF=0);
  bool m_probTag;

  // chiara: function to compute TRF
  //Float compute_TRF(ConstDataVector<xAOD::JetContainer> * SelectedBJets_TRF);
  Float_t compute_TRF();
  // chiara: TRF interface
#ifndef __CINT__
  TRFinterface * m_TRF; //!
#endif

  TTree* out_tree; // !
  TH1F* out_cutflow; //!

  Int_t m_all_events; //!

  Int_t mc_channel; //!
  float mc_weight; //!

  Int_t isPreselect_Gbb; //!
  Int_t isPreselect_Gtt_1l; //!
  Int_t isPreselect_Gtt_0l; //!
  Int_t isPreselect; //!

  // SRs
  Int_t isGbbSRA1; //!
  Int_t isGbbSRB1; //!
  Int_t isGbbSRA2; //!
  Int_t isGbbSRB2; //!
  Int_t isGbbSRC2; //!
  Int_t isGbbSRA4; //!
  Int_t isGbbSRB4; //!

  Int_t isGtt1LSRA2; //!
  Int_t isGtt1LSRB2; //!
  Int_t isGtt1LSRC2; //!
  Int_t isGtt1LSRA4; //!
  Int_t isGtt1LSRB4; //!
  Int_t isGtt1LSRC4; //!

  Int_t isGtt0LSRA; //!
  Int_t isGtt0LSRB; //!
  Int_t isGtt0LSRC; //!
  Int_t isGtt0LSRD; //!
  
  // CRs
  Int_t isGbbCRA2; //!
  Int_t isGbbCRB2; //!
  Int_t isGbbCRC2; //!
  Int_t isGbbCRA4; //!
  Int_t isGbbCRB4; //!

  Int_t isGtt1LCRA2; //!
  Int_t isGtt1LCRB2; //!
  Int_t isGtt1LCRC2; //!
  Int_t isGtt1LCRA4; //!
  Int_t isGtt1LCRB4; //!
  Int_t isGtt1LCRC4; //!

  Int_t isGtt0LCRA; //!
  Int_t isGtt0LCRB; //!
  Int_t isGtt0LCRC; //!
  Int_t isGtt0LCRD; //!

  // VRs
  Int_t isGbbVRI2; //!
  Int_t isGbbVRII2; //!
  Int_t isGbbVRIII2; //!
  Int_t isGbbVRI4; //!
  Int_t isGbbVRII4; //!
  Int_t isVR1LGtt0LI; //!
  Int_t isVR1LGtt0LII; //!
  Int_t isVR1LGtt0LIII; //!
  Int_t isVR1LGtt0LIV; //!
  Int_t isVR0LGtt0LI; //!
  Int_t isVR0LGtt0LII; //!
  Int_t isVR0LGtt0LIII; //!
  Int_t isVR0LGtt0LIV; //!
  Int_t isVRGtt1LI2mT2b; //!
  Int_t isVRGtt1LII2mT2b; //!
  Int_t isVRGtt1LI4mT2b; //!
  Int_t isVRGtt1LII4mT2b; //!
  Int_t isVRGtt1LI2mT3b; //!
  Int_t isVRGtt1LII2mT3b; //!
  Int_t isVRGtt1LI4mT3b; //! 
  Int_t isVRGtt1LII4mT3b; //!
  Int_t isVRGtt1LI2mTb2b; //!
  Int_t isVRGtt1LII2mTb2b; //!
  Int_t isVRGtt1LI4mTb2b; //!
  Int_t isVRGtt1LII4mTb2b; //!
  Int_t isVRGtt1LI2mTb3b; //!
  Int_t isVRGtt1LII2mTb3b; //!
  Int_t isVRGtt1LI4mTb3b; //!
  Int_t isVRGtt1LII4mTb3b; //!
  Int_t isVRGtt1LI2mT4b; //!
  Int_t isVRGtt1LII2mT4b; //!
  Int_t isVRGtt1LIII22b; //!
  Int_t isVRGtt1LIII42b; //!
  Int_t isVRGtt1LIII23b; //!
  Int_t isVRGtt1LIII43b; //!
  Int_t isVRGtt1LIII24b; //!
  Int_t isVRGtt1LIII44b; //!

  // Observables
  float var_dPhiMin;
  float var_Meff;
  float var_Meff_4j;
  float var_mT;
  float var_mTb;
  float var_HT;
  float var_Met;
  float var_Met_x;
  float var_Met_y;
  float var_MetSig;

  float var_mu_pt;
  float var_mu_eta;
  float var_mu_phi;
  float var_mu_e;
  float var_el_pt;
  float var_el_eta;
  float var_el_phi;
  float var_el_e;

  float var_rcjet_pt_1;
  float var_rcjet_pt_2;
  float var_rcjet_pt_3;
  float var_rcjet_pt_4;
  float var_rcjet_eta_1;
  float var_rcjet_eta_2;
  float var_rcjet_eta_3;
  float var_rcjet_eta_4;
  float var_rcjet_phi_1;
  float var_rcjet_phi_2;
  float var_rcjet_phi_3;
  float var_rcjet_phi_4;
  float var_rcjet_mass_1;
  float var_rcjet_mass_2;
  float var_rcjet_mass_3;
  float var_rcjet_mass_4;

  float var_bjet_pt_1;
  float var_bjet_pt_2;
  float var_bjet_pt_3;
  float var_bjet_pt_4;
  float var_bjet_eta_1;
  float var_bjet_eta_2;
  float var_bjet_eta_3;
  float var_bjet_eta_4;
  float var_bjet_phi_1;
  float var_bjet_phi_2;
  float var_bjet_phi_3;
  float var_bjet_phi_4;
  float var_bjet_e_1;
  float var_bjet_e_2;
  float var_bjet_e_3;
  float var_bjet_e_4;

  float var_jet_pt_1;
  float var_jet_pt_2;
  float var_jet_pt_3;
  float var_jet_pt_4;
  float var_jet_eta_1;
  float var_jet_eta_2;
  float var_jet_eta_3;
  float var_jet_eta_4;
  float var_jet_phi_1;
  float var_jet_phi_2;
  float var_jet_phi_3;
  float var_jet_phi_4;
  float var_jet_e_1;
  float var_jet_e_2;
  float var_jet_e_3;
  float var_jet_e_4;

  int NSignalElectrons;
  int NSignalMuons;
  int NBaseElectrons;
  int NBaseMuons;
  int NJets;
  int NBJets; //Number of b-jets in direct-tagging or in permutation of TRF
  int NBJets_TRF; //Number of bjet multiplicity in this event of TRF (i.e. 2 for 2bin, even if permutation contains 3 bjets) 
  int NTopJets;

  int NSignalLeptons;
  int NBaseLeptons;

  bool m_isTRF;
  bool m_isTRF_incl;
  double m_TRF_wgt;

  // chiara: variables to calculate the TRF weight for TRF weights
  std::vector<double>  m_TRFweight_in; //! 
  std::vector<double>  m_TRFweight_ex; //!
  std::vector<std::vector<bool> > m_TRFPerm_in; //! 
  std::vector<std::vector<bool> > m_TRFPerm_ex; //! 

  // chiara: variables to be stored in the tree
  //Trisha - slight modification so these are copied 
  //to final output variables for direct tagging events only
  std::vector<int> m_jets_isb_85_TRF_2excl; //!
  std::vector<int> m_jets_isb_85_TRF_2incl; //!
  std::vector<int> m_jets_isb_85_TRF_3excl; //!
  std::vector<int> m_jets_isb_85_TRF_3incl; //!
  std::vector<int> m_jets_isb_85_TRF_4incl; //!
  Double_t m_TRFweight_2excl; //!              
  Double_t m_TRFweight_2incl; //! 
  Double_t m_TRFweight_3excl; //! 
  Double_t m_TRFweight_3incl; //! 
  Double_t m_TRFweight_4incl; //! 
  // vectros to be used for TRF
  std::vector<double> m_sel_jets_pt;  //!  
  std::vector<double> m_sel_jets_eta; //!  
  std::vector<double> m_sel_jets_phi; //!  
  std::vector<int> m_sel_jets_truthLabel; //!  
  std::vector<double> m_sel_jets_btag_weight; //!  
  std::vector<int> m_sel_jets_index; //!  


  // Trisha: Final variables to be stored in the tree
  std::vector<int> m_out_jets_isb_85_TRF_2excl; //!
  std::vector<int> m_out_jets_isb_85_TRF_2incl; //!
  std::vector<int> m_out_jets_isb_85_TRF_3excl; //!
  std::vector<int> m_out_jets_isb_85_TRF_3incl; //!
  std::vector<int> m_out_jets_isb_85_TRF_4incl; //!

  // vectros to be used for TRF
  std::vector<double> m_out_sel_jets_pt;  //!  
  std::vector<double> m_out_sel_jets_eta; //!  
  std::vector<double> m_out_sel_jets_phi; //!  



};

#endif
