#ifndef MultibjetsTruthAnalysis_TruthAnalysis_H
#define MultibjetsTruthAnalysis_TruthAnalysis_H

#include <EventLoop/Algorithm.h>

#include "MultibjetsTruthAnalysis/Variables.h"

#include "EventLoop/OutputStream.h"

#include "TTree.h"

// reclustering forward declaration
class JetReclusteringTool;

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

 private:
  JetReclusteringTool* m_reclusteringTool = nullptr; //!

  TTree* out_tree; // !
  
  Int_t m_all_events; //!
  bool isGbbSRA1; //!
  bool isGbbSRB1; //!
  bool isGbbSRA2; //!
  bool isGbbSRB2; //!
  bool isGbbSRC2; //!
  bool isGbbSRA4; //!
  bool isGbbSRB4; //!
  bool isGtt1LSRA2; //!
  bool isGtt1LSRB2; //!
  bool isGtt1LSRC2; //!
  bool isGtt1LSRA4; //!
  bool isGtt1LSRB4; //!
  bool isGtt1LSRC4; //!
  bool isGtt0LSRA; //!
  bool isGtt0LSRB; //!
  bool isGtt0LSRC; //!
  bool isGtt0LSRD; //!
};

#endif
