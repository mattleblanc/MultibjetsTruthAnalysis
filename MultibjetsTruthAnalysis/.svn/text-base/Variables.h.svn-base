#ifndef MultibjetsTruthAnalysis_Variables_H
#define MultibjetsTruthAnalysis_Variables_H


#include <xAODMissingET/MissingET.h>

#include "xAODMissingET/MissingETContainer.h"
#include "xAODMissingET/MissingETAuxContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODEgamma/ElectronContainer.h"


class Variables {

 public:
  Variables();
  ~Variables();
  
  // Meff calculated with all jets with pt > 30 GeV and leptons with pt > 25 GeV
  static Float_t Meff_incl(const xAOD::MissingET* v_met, 
                            const xAOD::JetContainer*       v_jets, 
                            const xAOD::MuonContainer*      v_muons,
                            const xAOD::ElectronContainer*  v_electrons);
  
  // Meff calculated with the n leading jets with pt > 30 GeV. The 4 leading jets are used by default
  static Float_t Meff_4j(const xAOD::MissingET* v_met,  const xAOD::JetContainer* v_jets, u_int njets=4);
  
  // Ht calculated with all jets with pt > 30 GeV and leptons with pt > 25 GeV
  static Float_t Ht(const xAOD::JetContainer*        v_jets, 
                    const xAOD::MuonContainer*       v_muons,
                    const xAOD::ElectronContainer*   v_electrons);

  // Met significance calculated with the n leading jets with pt > 30 GeV. The 4 leading jets are used by default
  static Float_t Met_significance(const xAOD::MissingET* v_met, const xAOD::JetContainer* v_jets, u_int njets=4);

  // Transverse mass calculated with the leading lepton and the met
  static Float_t mT(const xAOD::MissingET* v_met, 
                    const xAOD::MuonContainer*       v_muons,
                    const xAOD::ElectronContainer*   v_electrons);

  // Minimum transverse mass of b-jets and the met with a mass set at 0 (default) or m(W)
  static Float_t mT_min_bjets( const xAOD::MissingET* v_met, const xAOD::JetContainer* v_jets, bool set_mw=false);

  // delta phi min between met and the n leading jets
  static Float_t delta_phi_nj(const xAOD::MissingET* v_met, const xAOD::JetContainer* v_jets, u_int njets=4);
    
};

#endif


