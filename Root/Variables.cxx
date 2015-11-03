#include "MultibjetsTruthAnalysis/Variables.h"
//2#include "MultibjetsAnalysis/HelperFunctions.h"

// P4Helpers
#include <FourMomUtils/xAODP4Helpers.h>

// for static casting
#include <xAODBase/IParticleContainer.h>

#define MEV 1000

//------------------------------------------------------------------------------------------------------------------
  
// Meff calculated with all jets with pt > 30 GeV and leptons with pt > 25 GeV
Float_t Variables::Meff_incl(const xAOD::MissingET* v_met, const xAOD::JetContainer* v_jets, const xAOD::MuonContainer*  v_muons, const xAOD::ElectronContainer*  v_electrons){

  Float_t meff = v_met->met() / MEV;
  
  for (auto jet : *v_jets) {
    if(jet->pt() / MEV <30.) continue;
    meff += jet->pt() / MEV;
  }
 
  for (auto muon : *v_muons) {
    if(muon->pt() / MEV < 25.) continue;
    meff += muon->pt() / MEV;
  }

  for (auto elec : *v_electrons) {
    if(elec->pt() / MEV < 25.) continue;
    meff += elec->pt() / MEV;
  }

  return meff;
}

Float_t Variables::Meff_incl(const xAOD::MissingET* v_met, const xAOD::JetContainer* v_jets, const xAOD::TruthParticleContainer*  v_muons, const xAOD::TruthParticleContainer*  v_electrons){

  Float_t meff = v_met->met() / MEV;

  for (auto jet : *v_jets) {
    if(jet->pt() / MEV <30.) continue;
    meff += jet->pt() / MEV;
  }

  for (auto muon : *v_muons) {
    if(muon->pt() / MEV < 25.) continue;
    meff += muon->pt() / MEV;
  }

  for (auto elec : *v_electrons) {
    if(elec->pt() / MEV < 25.) continue;
    meff += elec->pt() / MEV;
  }

  return meff;
}

//-----------------------------------------------------------------------------------------------------------------
  
// Meff calculated with the n leading jets with pt > 30 GeV. The 4 leading jets are used by default
Float_t Variables::Meff_4j(const xAOD::MissingET* v_met, const xAOD::JetContainer* v_jets, u_int njets) {

  Float_t meff = v_met->met() / MEV;
  
  u_int n = 0;
  
  for (auto jet : *v_jets) {
    n++;
    if(n>njets) break;
    if(jet->pt() / MEV <30.) continue;
    meff += jet->pt() / MEV;
  }
  
  return meff;
}

//-----------------------------------------------------------------------------------------------------------------
  
// Ht calculated with all jets with pt > 30 GeV and leptons with pt > 25 GeV
Float_t Variables::Ht(const xAOD::JetContainer* v_jets, const xAOD::MuonContainer*  v_muons,  const xAOD::ElectronContainer*  v_electrons){

  Float_t ht = 0;
  
  for (auto jet : *v_jets) {
    if(jet->pt() / MEV <30.) continue;
    ht += jet->pt() / MEV;
  }
  
  for (auto muon : *v_muons) {
    if(muon->pt() / MEV < 25.) continue;
    ht += muon->pt() / MEV;
  }
  
  for (auto elec : *v_electrons) {
    if(elec->pt() / MEV < 25.) continue;
    ht += elec->pt() / MEV;
  }

  return ht;
}

Float_t Variables::Ht(const xAOD::JetContainer* v_jets, const xAOD::TruthParticleContainer*  v_muons,  const xAOD::TruthParticleContainer* v_electrons){

  Float_t ht = 0;

  for (auto jet : *v_jets) {
    if(jet->pt() / MEV <30.) continue;
    ht += jet->pt() / MEV;
  }

  for (auto muon : *v_muons) {
    if(muon->pt() / MEV < 25.) continue;
    ht += muon->pt() / MEV;
  }

  for (auto elec : *v_electrons) {
    if(elec->pt() / MEV < 25.) continue;
    ht += elec->pt() / MEV;
  }

  return ht;
}

//-----------------------------------------------------------------------------------------------------------------
  
// Met significance calculated with the n leading jets with pt > 30 GeV. The 4 leading jets are used by default
Float_t Variables::Met_significance(const xAOD::MissingET* v_met, const xAOD::JetContainer* v_jets, u_int njets){
  

  Float_t met_sig = 0;

  Float_t ht = 0;
 
  u_int n = 0;
  
  for (auto jet : *v_jets) {
    n++;
    if(n>njets) break;
    if(jet->pt() / MEV <30.) continue;
    ht += jet->pt() / MEV;
  }

  float met = v_met->met() / MEV;

  if(ht!=0) met_sig = met / sqrt(ht);
  
  return met_sig;
  
}

//-----------------------------------------------------------------------------------------------------------------
  
// Transverse mass calculated with the leading lepton and the met
Float_t Variables::mT(const xAOD::MissingET* v_met, const xAOD::MuonContainer*  v_muons,  const xAOD::ElectronContainer*  v_electrons){


  //Removed old code.

  // Float_t mt = 0;

  // return mt; 
  // // find the leading lepton
  // TLorentzVector *v_lepton;
  // if(v_muons->size()==0 && v_electrons->size()==0) return mt;
  // // else if(v_muons.size()==0 && v_electrons->size()>0) v_lepton = (TLorentzVector*) v_electrons.at(0);  
  // // else if(v_muons->size()>0 && v_electrons->size()==0) v_lepton = (TLorentzVector*) v_muons.at(0);  
  // // else return mt; // this is a hack because the electrons are being changed
  // // else v_lepton = (v_muons.at(0)->Pt() > v_electrons->at(0)->Pt()) ? (TLorentzVector*) v_muons.at(0) : (TLorentzVector*) v_electrons->at(0);  
  
  // // mt = 2*v_lepton->Pt()*v_met.Pt()*(1-TMath::Cos(v_lepton->Phi() - v_met.Phi()));
  // // mt = (mt >= 0.) ? sqrt(mt) : sqrt(-mt);

  // return mt;
  float mt(0.0);

  bool els_exist = v_electrons && v_electrons->size() > 0;
  bool muons_exist = v_muons && v_muons->size() > 0;

  // get leading lepton
  const xAOD::IParticle* leadingLepton(nullptr);

  // if no leptons passed, return 0.0
  if     (!muons_exist && !els_exist)
    return mt;
  else if(muons_exist && !els_exist)
    leadingLepton = static_cast<const xAOD::IParticle*>(v_muons->at(0));
  else if(!muons_exist && els_exist)
    leadingLepton = static_cast<const xAOD::IParticle*>(v_electrons->at(0));
  else {
    // if muon pt > electron pt, then leading lepton is muon
    if(v_muons->at(0)->pt() > v_electrons->at(0)->pt())
      leadingLepton = static_cast<const xAOD::IParticle*>(v_muons->at(0));
    // otherwise it is electron
    else
      leadingLepton = static_cast<const xAOD::IParticle*>(v_electrons->at(0));
  }

  mt = 2*leadingLepton->pt()/MEV*v_met->met()/MEV*(1-cos(xAOD::P4Helpers::deltaPhi(leadingLepton, v_met)));
  return sqrt(fabs(mt));
}

Float_t Variables::mT(const xAOD::MissingET* v_met, const xAOD::TruthParticleContainer*  v_muons,  const xAOD::TruthParticleContainer*  v_electrons){
  

  //Removed old code.

  // Float_t mt = 0;

  // return mt;
  // // find the leading lepton
  // TLorentzVector *v_lepton;
  // if(v_muons->size()==0 && v_electrons->size()==0) return mt;
  // // else if(v_muons.size()==0 && v_electrons->size()>0) v_lepton = (TLorentzVector*) v_electrons.at(0);
  // // else if(v_muons->size()>0 && v_electrons->size()==0) v_lepton = (TLorentzVector*) v_muons.at(0);
  // // else return mt; // this is a hack because the electrons are being changed
  // // else v_lepton = (v_muons.at(0)->Pt() > v_electrons->at(0)->Pt()) ? (TLorentzVector*) v_muons.at(0) : (TLorentzVector*) v_electrons->at(0);

// // mt = 2*v_lepton->Pt()*v_met.Pt()*(1-TMath::Cos(v_lepton->Phi() - v_met.Phi()));
// // mt = (mt >= 0.) ? sqrt(mt) : sqrt(-mt);

// return mt;
float mt(0.0);

bool els_exist = v_electrons && v_electrons->size() > 0;
bool muons_exist = v_muons && v_muons->size() > 0;

// get leading lepton
const xAOD::IParticle* leadingLepton(nullptr);

// if no leptons passed, return 0.0
if     (!muons_exist && !els_exist)
  return mt;
 else if(muons_exist && !els_exist)
   leadingLepton = static_cast<const xAOD::IParticle*>(v_muons->at(0));
 else if(!muons_exist && els_exist)
   leadingLepton = static_cast<const xAOD::IParticle*>(v_electrons->at(0));
 else {
   // if muon pt > electron pt, then leading lepton is muon
   if(v_muons->at(0)->pt() > v_electrons->at(0)->pt())
     leadingLepton = static_cast<const xAOD::IParticle*>(v_muons->at(0));
   // otherwise it is electron
   else
     leadingLepton = static_cast<const xAOD::IParticle*>(v_electrons->at(0));
 }

mt = 2*leadingLepton->pt()/MEV*v_met->met()/MEV*(1-cos(xAOD::P4Helpers::deltaPhi(leadingLepton, v_met)));
return sqrt(fabs(mt));
}

//-----------------------------------------------------------------------------------------------------------------
  
// Minimum transverse mass of b-jets and the met with a mass set at 0 (default) or m(W)
Float_t Variables::mT_min_bjets(const xAOD::MissingET* v_met, const xAOD::JetContainer* v_jets, bool set_mw){
  
  Float_t mt_min = 100000.;
  Int_t   nb_bjets = 0;
  Float_t mw = 80.403;

  Float_t etw = v_met->met() / MEV;
  if(set_mw) etw = TMath::Hypot(v_met->met() / MEV, mw);
  
  static SG::AuxElement::ConstAccessor< char > bjet("bjet");

  for (auto jet : *v_jets) {
    
    //if(!bjet.isAvailable(*jet) || bjet(*jet) == 0) continue;

    nb_bjets ++;
    if(nb_bjets>3) break;
    
    Float_t mt = 0;

    // FIXME TOO
    mt = pow(etw+jet->pt() / MEV,2) - pow(v_met->mpx() / MEV + jet->p4().Px() / MEV, 2) - pow(v_met->mpy() / MEV + jet->p4().Py() / MEV, 2);
    mt = (mt >= 0.) ? sqrt(mt) : sqrt(-mt);
    
    if(mt<mt_min) mt_min = mt;
  }
  
  if(nb_bjets==0) return 0;
  else return mt_min;
}

//-----------------------------------------------------------------------------------------------------------------
 

// delta phi min between met and the n leading jets
Float_t Variables::delta_phi_nj(const xAOD::MissingET* v_met, const xAOD::JetContainer* v_jets, u_int njets){
 
    Float_t dphi_min = 1000.;
    
    u_int n = 0;
    
    for (auto jet : *v_jets) {
        n++;
        if(n>njets) break;
	
	const xAOD::IParticle* IP_jet = static_cast<const xAOD::IParticle*>(jet);
	Float_t dphi_j = xAOD::P4Helpers::deltaPhi(IP_jet, v_met);
        if(fabs(dphi_j)<dphi_min) dphi_min = fabs(dphi_j);
    }
    
    return dphi_min;
}
