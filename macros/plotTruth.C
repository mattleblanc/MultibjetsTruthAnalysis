//
// plotTruth.C
// ATLAS 2015 SUSY Multi-b/t search truth analysis plotting macro.
// MLB [UVic] <matt.leblanc@cern.ch>
//

// Provided as-is for reference, but will probably require some modifications if you
// want to actually get it running. This macro makes plots out of the output produced by running
// the main truth analysis.

// I actually run this on my laptop, to where I also download the merged output of running the main
// truth analysis over US Connect's condor system. The output file is about 3 GB, which is managable for me.

// Run as e.g. > root -l -b -q 'plotTruth.C("all")'

// ... yes, this could probably be done in a more clever way, but I am not always a clever man, and I am extraordinarily picky
// about how my plots look ... so the fine-grained control over each one that this provides is nice, for me.

#include <iostream>
#include <sstream> 
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TColor.h"
#include "TLine.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TRandom.h"

void stampATLAS(const std::string &text, float x, float y);
void stampATLAS_ratio(const std::string &text, float x, float y);
void stampLumiText(float lumi, float x, float y, const std::string &text, float size);
void stampText(const std::string &text, float x, float y, float size);
void truthPlot(std::vector<pair<TTree*, Int_t>> treevec,
			   std::vector<TH1F*> histovec,
			   std::vector<TString> colourvec,
			   TLegend*& leg,
			   TCanvas*& c,
			   Bool_t doLog,
			   TString xLabel,
			   TString yLabel,
			   float xmin,
			   float xmax, 
			   float ymin,
			   float ymax,
			   int rebin,
			   const std::string atlasLabel,
			   const std::string extraText,
			   TString reg,
			   TString filename);

void plotTruth(TString reg)
{
	std::cout << "plotTruth.C\tWe can handle this." << std::endl;
	std::cout << "Making plots for region:\t" << reg << std::endl;

	//TString inDir = "/Users/mleblanc/susyGtt/20151101_truth/trfOut/";
	//TString inDir = "/Users/mleblanc/susyGtt/20151101_truth/testOut/";
	TString inDir2 = "/fetch/data-outTree/";

	//TFile* f_410000; f_410000 = new TFile(inDir+"410000"+inDir2+"410000.merge.root");
	// TFile* f_410001; f_410001 = new TFile(inDir+"410001"+inDir2+"410001.merge.root");
	// TFile* f_410002; f_410002 = new TFile(inDir+"410002"+inDir2+"410002.merge.root");
	TFile* f_410003; f_410003 = new TFile(inDir+"410003"+inDir2+"410003.merge.root");
	TFile* f_410004; f_410004 = new TFile(inDir+"410004"+inDir2+"410004.merge.root");
	// TFile* f_410006; f_410006 = new TFile(inDir+"410006"+inDir2+"410006.merge.root");
	TFile* f_407012; f_407012 = new TFile(inDir+"407012"+inDir2+"407012.merge.root");
	TFile* f_407032; f_407032 = new TFile(inDir+"407032"+inDir2+"407032.merge.root");
	TFile* f_407036; f_407036 = new TFile(inDir+"407036"+inDir2+"407036.merge.root");
	TFile* f_407040; f_407040 = new TFile(inDir+"407040"+inDir2+"407040.merge.root");
	//TFile* f_407044; f_407044 = new TFile(inDir+"407044"+inDir2+"407044.merge.root");


	////TTree* t_410000; t_410000 = (TTree*)f_410000->Get("out_tree");
	//// TTree* t_410001; t_410001 = (TTree*)f_410001->Get("out_tree");
	//// TTree* t_410002; t_410002 = (TTree*)f_410002->Get("out_tree");
	TTree* t_410003; t_410003 = (TTree*)f_410003->Get("out_tree");
	TTree* t_410004; t_410004 = (TTree*)f_410004->Get("out_tree");
	//// TTree* t_410006; t_410006 = (TTree*)f_410006->Get("out_tree");
	TTree* t_407012; t_407012 = (TTree*)f_407012->Get("out_tree");
	TTree* t_407032; t_407032 = (TTree*)f_407032->Get("out_tree");
	TTree* t_407036; t_407036 = (TTree*)f_407036->Get("out_tree");
	TTree* t_407040; t_407040 = (TTree*)f_407040->Get("out_tree");
	////TTree* t_407044; t_407044 = (TTree*)f_407044->Get("out_tree");

	std::vector<pair<TTree*, Int_t>> v_trees;
	//v_trees.push_back(std::make_pair(t_410000,410000));
	//v_trees.push_back(std::make_pair(t_410001,410001));
	// v_trees.push_back(std::make_pair(t_410002,410002));
	v_trees.push_back(std::make_pair(t_410003,410003));
	v_trees.push_back(std::make_pair(t_410004,410004));
	// v_trees.push_back(std::make_pair(t_410006,410006));
	v_trees.push_back(std::make_pair(t_407032,407032));
	v_trees.push_back(std::make_pair(t_407036,407036));
	v_trees.push_back(std::make_pair(t_407040,407040));
	//v_trees.push_back(std::make_pair(t_407044,407044));
	v_trees.push_back(std::make_pair(t_407012,407012));
	

	// std::vector<pair<TTree*, Int_t>> v_trees;

	// TFile* f_407012; f_407012 = new TFile(inDir+"407012"+inDir2+"407012.merge.root");
	// TTree* t_407012; t_407012 = (TTree*)f_407012->Get("out_tree");
	// v_trees.push_back(std::make_pair(t_407012,407012));

	// TFile* f_407040; f_407040 = new TFile(inDir+"407040"+inDir2+"407040.merge.root");
	// TTree* t_407040; t_407040 = (TTree*)f_407040->Get("out_tree");
	// v_trees.push_back(std::make_pair(t_407040,407040));

	// Declare histograms ...
	std::vector<TH1F*> v_truth_met;
	std::vector<TH1F*> v_truth_Meff;
	std::vector<TH1F*> v_truth_Meff_4j;
	std::vector<TH1F*> v_truth_mT;
	std::vector<TH1F*> v_truth_mTb;
	// std::vector<TH1F*> v_truth_m1;
	// std::vector<TH1F*> v_truth_m2;

	std::vector<TH1F*> v_mu_pt;
	std::vector<TH1F*> v_mu_eta;
	std::vector<TH1F*> v_mu_phi;
	std::vector<TH1F*> v_mu_e;

	std::vector<TH1F*> v_el_pt;
	std::vector<TH1F*> v_el_eta;
	std::vector<TH1F*> v_el_phi;
	std::vector<TH1F*> v_el_e;

	std::vector<TH1F*> v_rcjet_pt_1;
	std::vector<TH1F*> v_rcjet_pt_2;
	std::vector<TH1F*> v_rcjet_pt_3;
	std::vector<TH1F*> v_rcjet_pt_4;
	std::vector<TH1F*> v_rcjet_eta_1;
	std::vector<TH1F*> v_rcjet_eta_2;
	std::vector<TH1F*> v_rcjet_eta_3;
	std::vector<TH1F*> v_rcjet_eta_4;
	std::vector<TH1F*> v_rcjet_phi_1;
	std::vector<TH1F*> v_rcjet_phi_2;
	std::vector<TH1F*> v_rcjet_phi_3;
	std::vector<TH1F*> v_rcjet_phi_4;
	std::vector<TH1F*> v_rcjet_mass_1;
	std::vector<TH1F*> v_rcjet_mass_2;
	std::vector<TH1F*> v_rcjet_mass_3;
	std::vector<TH1F*> v_rcjet_mass_4;
	std::vector<TH1F*> v_bjet_pt_1;
	std::vector<TH1F*> v_bjet_pt_2;
	std::vector<TH1F*> v_bjet_pt_3;
	std::vector<TH1F*> v_bjet_pt_4;
	std::vector<TH1F*> v_bjet_eta_1;
	std::vector<TH1F*> v_bjet_eta_2;
	std::vector<TH1F*> v_bjet_eta_3;
	std::vector<TH1F*> v_bjet_eta_4;
	std::vector<TH1F*> v_bjet_phi_1;
	std::vector<TH1F*> v_bjet_phi_2;
	std::vector<TH1F*> v_bjet_phi_3;
	std::vector<TH1F*> v_bjet_phi_4;
	std::vector<TH1F*> v_bjet_e_1;
	std::vector<TH1F*> v_bjet_e_2;
	std::vector<TH1F*> v_bjet_e_3;
	std::vector<TH1F*> v_bjet_e_4;
	std::vector<TH1F*> v_jet_pt_1;
	std::vector<TH1F*> v_jet_pt_2;
	std::vector<TH1F*> v_jet_pt_3;
	std::vector<TH1F*> v_jet_pt_4;
	std::vector<TH1F*> v_jet_eta_1;
	std::vector<TH1F*> v_jet_eta_2;
	std::vector<TH1F*> v_jet_eta_3;
	std::vector<TH1F*> v_jet_eta_4;
	std::vector<TH1F*> v_jet_phi_1;
	std::vector<TH1F*> v_jet_phi_2;
	std::vector<TH1F*> v_jet_phi_3;
	std::vector<TH1F*> v_jet_phi_4;
	std::vector<TH1F*> v_jet_e_1;
	std::vector<TH1F*> v_jet_e_2;
	std::vector<TH1F*> v_jet_e_3;
	std::vector<TH1F*> v_jet_e_4;

	std::vector<TH1F*> v_baselepton_n;
	std::vector<TH1F*> v_jet_n;
	std::vector<TH1F*> v_bjet_n;
	std::vector<TH1F*> v_rcjet_n;

	for(unsigned int iHist=0; iHist<v_trees.size(); iHist++)
	{
		TString dsid;
		dsid.Form("%d", v_trees.at(iHist).second); 

		TH1F* tempHistMet; tempHistMet = new TH1F(dsid,dsid,100,0,2000);
		TH1F* tempHistMeff; tempHistMeff = new TH1F(dsid,dsid,100,0,2000);
		TH1F* tempHistMeff4j; tempHistMeff4j = new TH1F(dsid,dsid,100,0,2000);
		TH1F* tempHistMT; tempHistMT = new TH1F(dsid,dsid,70,0,700);
		TH1F* tempHistMTb; tempHistMTb = new TH1F(dsid,dsid,60,0,300);
		// TH1F* tempHistM1; tempHistM1 = new TH1F(dsid,dsid,300,0,300);
		// TH1F* tempHistM2; tempHistM2 = new TH1F(dsid,dsid,300,0,300);

		TH1F* h_mu_pt; h_mu_pt = new TH1F(dsid,dsid,40,0,400); 
  		TH1F* h_mu_eta; h_mu_eta = new TH1F(dsid,dsid,150,-3.0,3.0); 
  		TH1F* h_mu_phi; h_mu_phi = new TH1F(dsid,dsid,160,-3.2,3.2); 
  		TH1F* h_mu_e; h_mu_e = new TH1F(dsid,dsid,40,0,400);  

  		TH1F* h_el_pt; h_el_pt = new TH1F(dsid,dsid,40,0,400); 
  		TH1F* h_el_eta; h_el_eta = new TH1F(dsid,dsid,150,-3.2,3.2); 
  		TH1F* h_el_phi; h_el_phi = new TH1F(dsid,dsid,160,-3.2,3.2); 
  		TH1F* h_el_e; h_el_e = new TH1F(dsid,dsid,40,0,400);  

  		TH1F* h_rcjet_pt_1; h_rcjet_pt_1 = new TH1F(dsid,dsid,50,200,2200); 
  		TH1F* h_rcjet_pt_2; h_rcjet_pt_2 = new TH1F(dsid,dsid,50,200,2200); 
  		TH1F* h_rcjet_pt_3; h_rcjet_pt_3 = new TH1F(dsid,dsid,50,200,2200); 
  		TH1F* h_rcjet_pt_4; h_rcjet_pt_4 = new TH1F(dsid,dsid,50,200,2200); 
  		TH1F* h_rcjet_eta_1; h_rcjet_eta_1 = new TH1F(dsid,dsid,30,-3,3);  
  		TH1F* h_rcjet_eta_2; h_rcjet_eta_2 = new TH1F(dsid,dsid,30,-3,3);  
  		TH1F* h_rcjet_eta_3; h_rcjet_eta_3 = new TH1F(dsid,dsid,30,-3,3);  
  		TH1F* h_rcjet_eta_4; h_rcjet_eta_4 = new TH1F(dsid,dsid,30,-3,3);  
  		TH1F* h_rcjet_phi_1; h_rcjet_phi_1 = new TH1F(dsid,dsid,32,-3.14,3.14);  
  		TH1F* h_rcjet_phi_2; h_rcjet_phi_2 = new TH1F(dsid,dsid,32,-3.14,3.14);  
  		TH1F* h_rcjet_phi_3; h_rcjet_phi_3 = new TH1F(dsid,dsid,32,-3.14,3.14);  
  		TH1F* h_rcjet_phi_4; h_rcjet_phi_4 = new TH1F(dsid,dsid,32,-3.14,3.14);  
  		TH1F* h_rcjet_mass_1; h_rcjet_mass_1 = new TH1F(dsid,dsid,60,0,300); 
  		TH1F* h_rcjet_mass_2; h_rcjet_mass_2 = new TH1F(dsid,dsid,60,0,300); 
  		TH1F* h_rcjet_mass_3; h_rcjet_mass_3 = new TH1F(dsid,dsid,60,0,300); 
  		TH1F* h_rcjet_mass_4; h_rcjet_mass_4 = new TH1F(dsid,dsid,60,0,300); 

  		TH1F* h_bjet_pt_1; h_bjet_pt_1 = new TH1F(dsid,dsid,150,0,3000); 
  		TH1F* h_bjet_pt_2; h_bjet_pt_2 = new TH1F(dsid,dsid,150,0,3000); 
  		TH1F* h_bjet_pt_3; h_bjet_pt_3 = new TH1F(dsid,dsid,150,0,3000); 
  		TH1F* h_bjet_pt_4; h_bjet_pt_4 = new TH1F(dsid,dsid,150,0,3000); 
  		TH1F* h_bjet_eta_1; h_bjet_eta_1 = new TH1F(dsid,dsid,30,-3.0,3.0); 
  		TH1F* h_bjet_eta_2; h_bjet_eta_2 = new TH1F(dsid,dsid,30,-3.0,3.0); 
  		TH1F* h_bjet_eta_3; h_bjet_eta_3 = new TH1F(dsid,dsid,30,-3.0,3.0); 
  		TH1F* h_bjet_eta_4; h_bjet_eta_4 = new TH1F(dsid,dsid,30,-3.0,3.0); 
  		TH1F* h_bjet_phi_1; h_bjet_phi_1 = new TH1F(dsid,dsid,32,-3.2,3.2); 
  		TH1F* h_bjet_phi_2; h_bjet_phi_2 = new TH1F(dsid,dsid,32,-3.2,3.2); 
  		TH1F* h_bjet_phi_3; h_bjet_phi_3 = new TH1F(dsid,dsid,32,-3.2,3.2); 
  		TH1F* h_bjet_phi_4; h_bjet_phi_4 = new TH1F(dsid,dsid,32,-3.2,3.2); 
  		TH1F* h_bjet_e_1; h_bjet_e_1 = new TH1F(dsid,dsid,60,0,3000); 
  		TH1F* h_bjet_e_2; h_bjet_e_2 = new TH1F(dsid,dsid,60,0,3000); 
  		TH1F* h_bjet_e_3; h_bjet_e_3 = new TH1F(dsid,dsid,60,0,3000); 
  		TH1F* h_bjet_e_4; h_bjet_e_4 = new TH1F(dsid,dsid,60,0,3000); 

  		TH1F* h_jet_pt_1; h_jet_pt_1 = new TH1F(dsid,dsid,150,0,3000); 
  		TH1F* h_jet_pt_2; h_jet_pt_2 = new TH1F(dsid,dsid,150,0,3000); 
  		TH1F* h_jet_pt_3; h_jet_pt_3 = new TH1F(dsid,dsid,150,0,3000); 
  		TH1F* h_jet_pt_4; h_jet_pt_4 = new TH1F(dsid,dsid,150,0,3000); 
  		TH1F* h_jet_eta_1; h_jet_eta_1 = new TH1F(dsid,dsid,30,-3.0,3.0); 
  		TH1F* h_jet_eta_2; h_jet_eta_2 = new TH1F(dsid,dsid,30,-3.0,3.0);
  		TH1F* h_jet_eta_3; h_jet_eta_3 = new TH1F(dsid,dsid,30,-3.0,3.0);
  		TH1F* h_jet_eta_4; h_jet_eta_4 = new TH1F(dsid,dsid,30,-3.0,3.0);
  		TH1F* h_jet_phi_1; h_jet_phi_1 = new TH1F(dsid,dsid,32,-3.2,3.2); 
  		TH1F* h_jet_phi_2; h_jet_phi_2 = new TH1F(dsid,dsid,32,-3.2,3.2); 
  		TH1F* h_jet_phi_3; h_jet_phi_3 = new TH1F(dsid,dsid,32,-3.2,3.2); 
  		TH1F* h_jet_phi_4; h_jet_phi_4 = new TH1F(dsid,dsid,32,-3.2,3.2); 
  		TH1F* h_jet_e_1; h_jet_e_1 = new TH1F(dsid,dsid,60,0,3000);  
  		TH1F* h_jet_e_2; h_jet_e_2 = new TH1F(dsid,dsid,60,0,3000);  
  		TH1F* h_jet_e_3; h_jet_e_3 = new TH1F(dsid,dsid,60,0,3000); 
  		TH1F* h_jet_e_4; h_jet_e_4 = new TH1F(dsid,dsid,60,0,3000); 

  		TH1F* h_baselepton_n; h_baselepton_n = new TH1F(dsid,dsid,15,0,15);
  		TH1F* h_jet_n; h_jet_n = new TH1F(dsid,dsid,15,0,15);
  		TH1F* h_bjet_n; h_bjet_n = new TH1F(dsid,dsid,8,0,8);
  		TH1F* h_rcjet_n; h_rcjet_n = new TH1F(dsid,dsid,6,0,6);

		TH1F* tempHist; tempHist = new TH1F(dsid,dsid,100,0,2000);

		v_truth_met.push_back(tempHistMet);
		v_truth_Meff.push_back(tempHistMeff);		
		v_truth_Meff_4j.push_back(tempHistMeff4j);	
		v_truth_mT.push_back(tempHistMT);		
		v_truth_mTb.push_back(tempHistMTb);

		v_mu_pt.push_back(h_mu_pt);
		v_mu_eta.push_back(h_mu_eta);
		v_mu_phi.push_back(h_mu_phi);
		v_mu_e.push_back(h_mu_e);
		v_el_pt.push_back(h_el_pt);
		v_el_eta.push_back(h_el_eta);
		v_el_phi.push_back(h_el_phi);
		v_el_e.push_back(h_el_e);
		v_rcjet_pt_1.push_back(h_rcjet_pt_1);
		v_rcjet_pt_2.push_back(h_rcjet_pt_2);
		v_rcjet_pt_3.push_back(h_rcjet_pt_3);
		v_rcjet_pt_4.push_back(h_rcjet_pt_4);
		v_rcjet_eta_1.push_back(h_rcjet_eta_1);
		v_rcjet_eta_2.push_back(h_rcjet_eta_2);
		v_rcjet_eta_3.push_back(h_rcjet_eta_3);
		v_rcjet_eta_4.push_back(h_rcjet_eta_4);
		v_rcjet_phi_1.push_back(h_rcjet_phi_1);
		v_rcjet_phi_2.push_back(h_rcjet_phi_2);
		v_rcjet_phi_3.push_back(h_rcjet_phi_3);
		v_rcjet_phi_4.push_back(h_rcjet_phi_4);
		v_rcjet_mass_1.push_back(h_rcjet_mass_1);
		v_rcjet_mass_2.push_back(h_rcjet_mass_2);
		v_rcjet_mass_3.push_back(h_rcjet_mass_3);
		v_rcjet_mass_4.push_back(h_rcjet_mass_4);
		v_bjet_pt_1.push_back(h_bjet_pt_1);
		v_bjet_pt_2.push_back(h_bjet_pt_2);
		v_bjet_pt_3.push_back(h_bjet_pt_3);
		v_bjet_pt_4.push_back(h_bjet_pt_4);
		v_bjet_eta_1.push_back(h_bjet_eta_1);
		v_bjet_eta_2.push_back(h_bjet_eta_2);
		v_bjet_eta_3.push_back(h_bjet_eta_3);
		v_bjet_eta_4.push_back(h_bjet_eta_4);
		v_bjet_phi_1.push_back(h_bjet_phi_1);
		v_bjet_phi_2.push_back(h_bjet_phi_2);
		v_bjet_phi_3.push_back(h_bjet_phi_3);
		v_bjet_phi_4.push_back(h_bjet_phi_4);
		v_bjet_e_1.push_back(h_bjet_e_1);
		v_bjet_e_2.push_back(h_bjet_e_2);
		v_bjet_e_3.push_back(h_bjet_e_3);
		v_bjet_e_4.push_back(h_bjet_e_4);
		v_jet_pt_1.push_back(h_jet_pt_1);
		v_jet_pt_2.push_back(h_jet_pt_2);
		v_jet_pt_3.push_back(h_jet_pt_3);
		v_jet_pt_4.push_back(h_jet_pt_4);
		v_jet_eta_1.push_back(h_jet_eta_1);
		v_jet_eta_2.push_back(h_jet_eta_2);
		v_jet_eta_3.push_back(h_jet_eta_3);
		v_jet_eta_4.push_back(h_jet_eta_4);
		v_jet_phi_1.push_back(h_jet_phi_1);
		v_jet_phi_2.push_back(h_jet_phi_2);
		v_jet_phi_3.push_back(h_jet_phi_3);
		v_jet_phi_4.push_back(h_jet_phi_4);
		v_jet_e_1.push_back(h_jet_e_1);
		v_jet_e_2.push_back(h_jet_e_2);
		v_jet_e_3.push_back(h_jet_e_3);
		v_jet_e_4.push_back(h_jet_e_4);

		v_baselepton_n.push_back(h_baselepton_n);
		v_jet_n.push_back(h_jet_n);
		v_bjet_n.push_back(h_bjet_n);
		v_rcjet_n.push_back(h_rcjet_n);
	}

	for(unsigned int iTree=0; iTree<v_trees.size(); iTree++)
	{
		TString dsid;
		dsid.Form("%d", v_trees.at(iTree).second); 

		std::cout << "DSID: " << dsid << "\t" << v_trees.at(iTree).first->GetEntries() 
				  << " entries." << std::endl;


		// for each tree, load the branches.
		Float_t weight = 1.0;
		Float_t mc_weight=v_trees.at(iTree).first->SetBranchAddress("mc_weight",&mc_weight);

        // Always use nominal XS, k-factor.
        // Get these from SUSYTools:
        // https://svnweb.cern.ch/trac/atlasoff/browser/PhysicsAnalysis/SUSYPhys/SUSYTools/trunk/data/susy_crosssections_13TeV.txt
      	if(dsid=="410000" || dsid=="410001" || dsid=="410002" || dsid=="410003" || dsid=="410004" || dsid=="410006")
      		weight *= 831.76*1.*0.543*1.;

      	if(dsid=="407012" || dsid=="407032" || dsid=="407036" || dsid=="407040" || dsid=="407044")
      		weight *=  831.76*1.*0.0092194758*1.;

      	/*
      		Make sure to use the proper sum-of-weights per-sample, though.
      		Get these by opening up the merged files and running e.g.
      			root > TH1F* histo_temp = new TH1F("blah", "blah", boundaries)
				root > myTree->Draw("1>>blah", "(1)*mc_weight")
				root > std::cout << histo_temp->Integral() << std::endl
		*/

        //if(dsid=="410000") weight /= 1.67772e+07;//20099000.0;
        // if(dsid=="410001") weight /= 19995000.0;
        // if(dsid=="410002") weight /= 20000000.0;
        if(dsid=="410003") weight /= 2.85815e+06; //4910000.0;
        if(dsid=="410004") weight /= 9.82e+06; //9820000.0;
        // if(dsid=="410006") weight /= 10000000.0;

        if(dsid=="407012") weight /= 2.74497;
		if(dsid=="407032") weight /= 2.95191;
        if(dsid=="407036") weight /= 2.43458;
        if(dsid=="407040") weight /= 3.7725e6;
        //if(dsid=="407044") weight /= 2.85515e9; 

		weight*=1.e3; // pb to fb
		weight*=3.3; // 2015 lumi

		Int_t all; v_trees.at(iTree).first->SetBranchAddress("all_events",&all);

		Int_t isPreselect_Gbb; v_trees.at(iTree).first->SetBranchAddress("isPreselect_Gbb",&isPreselect_Gbb);
		Int_t isPreselect_Gtt_0l; v_trees.at(iTree).first->SetBranchAddress("isPreselect_Gtt_0l",&isPreselect_Gtt_0l);
		Int_t isPreselect_Gtt_1l; v_trees.at(iTree).first->SetBranchAddress("isPreselect_Gtt_1l",&isPreselect_Gtt_1l);
		Int_t isPreselect; v_trees.at(iTree).first->SetBranchAddress("isPreselect",&isPreselect);

		Int_t isGbbSRA1; v_trees.at(iTree).first->SetBranchAddress("isGbbSRA1",&isGbbSRA1);
		Int_t isGbbSRB1; v_trees.at(iTree).first->SetBranchAddress("isGbbSRB1",&isGbbSRB1);
		Int_t isGbbSRA2; v_trees.at(iTree).first->SetBranchAddress("isGbbSRA2",&isGbbSRA2);
		Int_t isGbbSRB2; v_trees.at(iTree).first->SetBranchAddress("isGbbSRB2",&isGbbSRB2);
		Int_t isGbbSRC2; v_trees.at(iTree).first->SetBranchAddress("isGbbSRC2",&isGbbSRC2);
		Int_t isGbbSRA4; v_trees.at(iTree).first->SetBranchAddress("isGbbSRA4",&isGbbSRA4);
		Int_t isGbbSRB4; v_trees.at(iTree).first->SetBranchAddress("isGbbSRB4",&isGbbSRB4);

		Int_t isGtt1LSRA2; v_trees.at(iTree).first->SetBranchAddress("isGtt1LSRA2",&isGtt1LSRA2);
		Int_t isGtt1LSRB2; v_trees.at(iTree).first->SetBranchAddress("isGtt1LSRB2",&isGtt1LSRB2);
		Int_t isGtt1LSRC2; v_trees.at(iTree).first->SetBranchAddress("isGtt1LSRC2",&isGtt1LSRC2);
		Int_t isGtt1LSRA4; v_trees.at(iTree).first->SetBranchAddress("isGtt1LSRA4",&isGtt1LSRA4);
		Int_t isGtt1LSRB4; v_trees.at(iTree).first->SetBranchAddress("isGtt1LSRB4",&isGtt1LSRB4);
		Int_t isGtt1LSRC4; v_trees.at(iTree).first->SetBranchAddress("isGtt1LSRC4",&isGtt1LSRC4);

		Int_t isGtt0LSRA; v_trees.at(iTree).first->SetBranchAddress("isGtt0LSRA",&isGtt0LSRA);
		Int_t isGtt0LSRB; v_trees.at(iTree).first->SetBranchAddress("isGtt0LSRB",&isGtt0LSRB);		
		Int_t isGtt0LSRC; v_trees.at(iTree).first->SetBranchAddress("isGtt0LSRC",&isGtt0LSRC);
		Int_t isGtt0LSRD; v_trees.at(iTree).first->SetBranchAddress("isGtt0LSRD",&isGtt0LSRD);

		Int_t isGbbCRA2; v_trees.at(iTree).first->SetBranchAddress("isGbbCRA2",&isGbbCRA2);
		Int_t isGbbCRB2; v_trees.at(iTree).first->SetBranchAddress("isGbbCRB2",&isGbbCRB2);
		Int_t isGbbCRC2; v_trees.at(iTree).first->SetBranchAddress("isGbbCRC2",&isGbbCRC2);
		Int_t isGbbCRA4; v_trees.at(iTree).first->SetBranchAddress("isGbbCRA4",&isGbbCRA4);
		Int_t isGbbCRB4; v_trees.at(iTree).first->SetBranchAddress("isGbbCRB4",&isGbbCRB4);

		Int_t isGtt1LCRA2; v_trees.at(iTree).first->SetBranchAddress("isGtt1LCRA2",&isGtt1LCRA2);
		Int_t isGtt1LCRB2; v_trees.at(iTree).first->SetBranchAddress("isGtt1LCRB2",&isGtt1LCRB2);
		Int_t isGtt1LCRC2; v_trees.at(iTree).first->SetBranchAddress("isGtt1LCRC2",&isGtt1LCRC2);
		Int_t isGtt1LCRA4; v_trees.at(iTree).first->SetBranchAddress("isGtt1LCRA4",&isGtt1LCRA4);
		Int_t isGtt1LCRB4; v_trees.at(iTree).first->SetBranchAddress("isGtt1LCRB4",&isGtt1LCRB4);
		Int_t isGtt1LCRC4; v_trees.at(iTree).first->SetBranchAddress("isGtt1LCRC4",&isGtt1LCRC4);

		Int_t isGtt0LCRA; v_trees.at(iTree).first->SetBranchAddress("isGtt0LCRA",&isGtt0LCRA);
		Int_t isGtt0LCRB; v_trees.at(iTree).first->SetBranchAddress("isGtt0LCRB",&isGtt0LCRB);
		Int_t isGtt0LCRC; v_trees.at(iTree).first->SetBranchAddress("isGtt0LCRC",&isGtt0LCRC);
		Int_t isGtt0LCRD; v_trees.at(iTree).first->SetBranchAddress("isGtt0LCRD",&isGtt0LCRD);

		// Also get the rest of the branches.
		Float_t var_Met;  	  v_trees.at(iTree).first->SetBranchAddress("var_Met",&var_Met);
		Float_t var_Meff;  	  v_trees.at(iTree).first->SetBranchAddress("var_Meff",&var_Meff);
		Float_t var_Meff_4j;  v_trees.at(iTree).first->SetBranchAddress("var_Meff_4j",&var_Meff_4j);
		Float_t var_mT;  	  v_trees.at(iTree).first->SetBranchAddress("var_mT",&var_mT);
		Float_t var_mTb;	  v_trees.at(iTree).first->SetBranchAddress("var_mTb",&var_mTb);

  		float var_mu_pt; 	v_trees.at(iTree).first->SetBranchAddress("var_mu_pt",&var_mu_pt);
  		float var_mu_eta; 	v_trees.at(iTree).first->SetBranchAddress("var_mu_eta",&var_mu_eta);
  		float var_mu_phi; 	v_trees.at(iTree).first->SetBranchAddress("var_mu_phi",&var_mu_phi);
  		float var_mu_e; 	v_trees.at(iTree).first->SetBranchAddress("var_mu_e",&var_mu_e);

  		float var_el_pt;		 v_trees.at(iTree).first->SetBranchAddress("var_el_pt",&var_el_pt);
  		float var_el_eta;		 v_trees.at(iTree).first->SetBranchAddress("var_el_eta",&var_el_eta);
  		float var_el_phi; 		 v_trees.at(iTree).first->SetBranchAddress("var_el_phi",&var_el_phi);
  		float var_el_e; 		 v_trees.at(iTree).first->SetBranchAddress("var_el_e",&var_el_e);

  		float var_rcjet_pt_1; 	v_trees.at(iTree).first->SetBranchAddress("var_rcjet_pt_1",&var_rcjet_pt_1);
  		float var_rcjet_pt_2; 	v_trees.at(iTree).first->SetBranchAddress("var_rcjet_pt_2",&var_rcjet_pt_2);
  		float var_rcjet_pt_3; 	v_trees.at(iTree).first->SetBranchAddress("var_rcjet_pt_3",&var_rcjet_pt_3);
  		float var_rcjet_pt_4; 	v_trees.at(iTree).first->SetBranchAddress("var_rcjet_pt_4",&var_rcjet_pt_4);
  		float var_rcjet_eta_1;	v_trees.at(iTree).first->SetBranchAddress("var_rcjet_eta_1",&var_rcjet_eta_1);
  		float var_rcjet_eta_2;  v_trees.at(iTree).first->SetBranchAddress("var_rcjet_eta_2",&var_rcjet_eta_2);
  		float var_rcjet_eta_3;  v_trees.at(iTree).first->SetBranchAddress("var_rcjet_eta_3",&var_rcjet_eta_3);
  		float var_rcjet_eta_4;  v_trees.at(iTree).first->SetBranchAddress("var_rcjet_eta_4",&var_rcjet_eta_4);
  		float var_rcjet_phi_1;  v_trees.at(iTree).first->SetBranchAddress("var_rcjet_phi_1",&var_rcjet_phi_1);
  		float var_rcjet_phi_2;  v_trees.at(iTree).first->SetBranchAddress("var_rcjet_phi_2",&var_rcjet_phi_2);
  		float var_rcjet_phi_3;  v_trees.at(iTree).first->SetBranchAddress("var_rcjet_phi_3",&var_rcjet_phi_3);
  		float var_rcjet_phi_4;  v_trees.at(iTree).first->SetBranchAddress("var_rcjet_phi_4",&var_rcjet_phi_4);
  		float var_rcjet_mass_1; v_trees.at(iTree).first->SetBranchAddress("var_rcjet_mass_1",&var_rcjet_mass_1);
  		float var_rcjet_mass_2; v_trees.at(iTree).first->SetBranchAddress("var_rcjet_mass_2",&var_rcjet_mass_2);
  		float var_rcjet_mass_3; v_trees.at(iTree).first->SetBranchAddress("var_rcjet_mass_3",&var_rcjet_mass_3);
  		float var_rcjet_mass_4; v_trees.at(iTree).first->SetBranchAddress("var_rcjet_mass_4",&var_rcjet_mass_4);

  		float var_bjet_pt_1;    v_trees.at(iTree).first->SetBranchAddress("var_bjet_pt_1",&var_bjet_pt_1);
  		float var_bjet_pt_2;    v_trees.at(iTree).first->SetBranchAddress("var_bjet_pt_2",&var_bjet_pt_2);
  		float var_bjet_pt_3;    v_trees.at(iTree).first->SetBranchAddress("var_bjet_pt_3",&var_bjet_pt_3);
  		float var_bjet_pt_4;    v_trees.at(iTree).first->SetBranchAddress("var_bjet_pt_4",&var_bjet_pt_4);
  		float var_bjet_eta_1;   v_trees.at(iTree).first->SetBranchAddress("var_bjet_eta_1",&var_bjet_eta_1);
  		float var_bjet_eta_2;   v_trees.at(iTree).first->SetBranchAddress("var_bjet_eta_2",&var_bjet_eta_2);
  		float var_bjet_eta_3;   v_trees.at(iTree).first->SetBranchAddress("var_bjet_eta_3",&var_bjet_eta_3);
  		float var_bjet_eta_4;   v_trees.at(iTree).first->SetBranchAddress("var_bjet_eta_4",&var_bjet_eta_4);
  		float var_bjet_phi_1;   v_trees.at(iTree).first->SetBranchAddress("var_bjet_phi_1",&var_bjet_phi_1);
  		float var_bjet_phi_2;   v_trees.at(iTree).first->SetBranchAddress("var_bjet_phi_2",&var_bjet_phi_2);
  		float var_bjet_phi_3;   v_trees.at(iTree).first->SetBranchAddress("var_bjet_phi_3",&var_bjet_phi_3);
  		float var_bjet_phi_4;   v_trees.at(iTree).first->SetBranchAddress("var_bjet_phi_4",&var_bjet_phi_4);
  		float var_bjet_e_1;     v_trees.at(iTree).first->SetBranchAddress("var_bjet_e_1",&var_bjet_e_1);
  		float var_bjet_e_2;     v_trees.at(iTree).first->SetBranchAddress("var_bjet_e_2",&var_bjet_e_2);
  		float var_bjet_e_3;     v_trees.at(iTree).first->SetBranchAddress("var_bjet_e_3",&var_bjet_e_3);
  		float var_bjet_e_4;     v_trees.at(iTree).first->SetBranchAddress("var_bjet_e_4",&var_bjet_e_4);

  		float var_jet_pt_1;     v_trees.at(iTree).first->SetBranchAddress("var_jet_pt_1",&var_jet_pt_1);
  		float var_jet_pt_2;     v_trees.at(iTree).first->SetBranchAddress("var_jet_pt_2",&var_jet_pt_2);
  		float var_jet_pt_3;     v_trees.at(iTree).first->SetBranchAddress("var_jet_pt_3",&var_jet_pt_3);
  		float var_jet_pt_4;     v_trees.at(iTree).first->SetBranchAddress("var_jet_pt_4",&var_jet_pt_4);
  		float var_jet_eta_1;    v_trees.at(iTree).first->SetBranchAddress("var_jet_eta_1",&var_jet_eta_1);
  		float var_jet_eta_2;    v_trees.at(iTree).first->SetBranchAddress("var_jet_eta_2",&var_jet_eta_2);
  		float var_jet_eta_3;    v_trees.at(iTree).first->SetBranchAddress("var_jet_eta_3",&var_jet_eta_3);
  		float var_jet_eta_4;    v_trees.at(iTree).first->SetBranchAddress("var_jet_eta_4",&var_jet_eta_4);
  		float var_jet_phi_1;    v_trees.at(iTree).first->SetBranchAddress("var_jet_phi_1",&var_jet_phi_1);
  		float var_jet_phi_2;    v_trees.at(iTree).first->SetBranchAddress("var_jet_phi_2",&var_jet_phi_2);
  		float var_jet_phi_3;    v_trees.at(iTree).first->SetBranchAddress("var_jet_phi_3",&var_jet_phi_3);
  		float var_jet_phi_4;    v_trees.at(iTree).first->SetBranchAddress("var_jet_phi_4",&var_jet_phi_4);
  		float var_jet_e_1;      v_trees.at(iTree).first->SetBranchAddress("var_jet_e_1",&var_jet_e_1);
  		float var_jet_e_2; 		v_trees.at(iTree).first->SetBranchAddress("var_jet_e_2",&var_jet_e_2);
  		float var_jet_e_3; 		v_trees.at(iTree).first->SetBranchAddress("var_jet_e_3",&var_jet_e_3);
  		float var_jet_e_4; 		v_trees.at(iTree).first->SetBranchAddress("var_jet_e_4",&var_jet_e_4);

  		int NBaseLeptons;  v_trees.at(iTree).first->SetBranchAddress("NBaseLeptons",&NBaseLeptons);

		int var_jet_n; v_trees.at(iTree).first->SetBranchAddress("NJets",&var_jet_n);
		int var_bjet_n; v_trees.at(iTree).first->SetBranchAddress("NBJets",&var_bjet_n);
		int var_rcjet_n; v_trees.at(iTree).first->SetBranchAddress("NTopJets",&var_rcjet_n);
		
		Bool_t isTRF; v_trees.at(iTree).first->SetBranchAddress("isTRF",&isTRF);

		float temp_weight;

		// Loop over the entries in each tree and do the thing.
		for(unsigned int i=0; i < v_trees.at(iTree).first->GetEntries(); i++)
		{
			v_trees.at(iTree).first->GetEntry(i);

			//if(i>200000) break; // MAX, REMOVE THIS FOR PLOTS

			temp_weight = weight;
			temp_weight *= mc_weight;

			if(i%1000000==true)
			{
				std::cout << "DSID: " << v_trees.at(iTree).second  << "\tEntry " 
										  << (i-1) << " / " << v_trees.at(iTree).first->GetEntries() << std::endl;

			}

			Bool_t fillPlots=false;
			if(reg=="all" && !isTRF) fillPlots=true;
			if(reg=="Preselect_Gbb" && !isTRF && isPreselect_Gbb) fillPlots=true;
			if(reg=="Preselect_Gtt_0l" && !isTRF && isPreselect_Gtt_0l) fillPlots=true;
			if(reg=="Preselect_Gtt_1l" && !isTRF && isPreselect_Gtt_1l) fillPlots=true;

			if(reg=="GbbSRA2" && !isTRF && isGbbSRA2) fillPlots=true;
			if(reg=="GbbSRB2" && !isTRF && isGbbSRB2) fillPlots=true;
			if(reg=="GbbSRC2" && !isTRF && isGbbSRC2) fillPlots=true;
			if(reg=="GbbSRA4" && !isTRF && isGbbSRA4) fillPlots=true;
			if(reg=="GbbSRB4" && !isTRF && isGbbSRB4) fillPlots=true;

			if(reg=="Gtt1LSRA2" && !isTRF && isGtt1LSRA2) fillPlots=true;
			if(reg=="Gtt1LSRB2" && !isTRF && isGtt1LSRB2) fillPlots=true;
			if(reg=="Gtt1LSRC2" && !isTRF && isGtt1LSRC2) fillPlots=true;
			if(reg=="Gtt1LSRA4" && !isTRF && isGtt1LSRA4) fillPlots=true;
			if(reg=="Gtt1LSRB4" && !isTRF && isGtt1LSRB4) fillPlots=true;
			if(reg=="Gtt1LSRC4" && !isTRF && isGtt1LSRC4) fillPlots=true;

			if(reg=="Gtt0LSRA" && !isTRF && isGtt0LSRA) fillPlots=true;
			if(reg=="Gtt0LSRB" && !isTRF && isGtt0LSRB) fillPlots=true;
			if(reg=="Gtt0LSRC" && !isTRF && isGtt0LSRC) fillPlots=true;
			if(reg=="Gtt0LSRD" && !isTRF && isGtt0LSRD) fillPlots=true;

			if(reg=="GbbCRA2" && !isTRF && isGbbCRA2) fillPlots=true;
			if(reg=="GbbCRB2" && !isTRF && isGbbCRB2) fillPlots=true;
			if(reg=="GbbCRC2" && !isTRF && isGbbCRC2) fillPlots=true;
			if(reg=="GbbCRA4" && !isTRF && isGbbCRA4) fillPlots=true;
			if(reg=="GbbCRB4" && !isTRF && isGbbCRB4) fillPlots=true;

			if(reg=="Gtt1LCRA2" && !isTRF && isGtt1LCRA2) fillPlots=true;
			if(reg=="Gtt1LCRB2" && !isTRF && isGtt1LCRB2) fillPlots=true;
			if(reg=="Gtt1LCRC2" && !isTRF && isGtt1LCRC2) fillPlots=true;
			if(reg=="Gtt1LCRA4" && !isTRF && isGtt1LCRA4) fillPlots=true;
			if(reg=="Gtt1LCRB4" && !isTRF && isGtt1LCRB4) fillPlots=true;
			if(reg=="Gtt1LCRC4" && !isTRF && isGtt1LCRC4) fillPlots=true;

			if(reg=="Gtt0LCRA" && !isTRF && isGtt0LCRA) fillPlots=true;
			if(reg=="Gtt0LCRB" && !isTRF && isGtt0LCRB) fillPlots=true;
			if(reg=="Gtt0LCRC" && !isTRF && isGtt0LCRC) fillPlots=true;
			if(reg=="Gtt0LCRD" && !isTRF && isGtt0LCRD) fillPlots=true;

			if(dsid=="407012" || dsid=="407032" || dsid=="407036" || dsid=="407040" || dsid=="407044")
				if(var_Met < 200.0)
					fillPlots = false;

			// Now fill the histos.
			if(fillPlots)
			{
				v_truth_met.at(iTree)->Fill(var_Met,temp_weight);
				v_truth_Meff.at(iTree)->Fill(var_Meff,temp_weight);
				v_truth_Meff_4j.at(iTree)->Fill(var_Meff_4j,temp_weight);
				v_truth_mT.at(iTree)->Fill(var_mT,temp_weight);
				v_truth_mTb.at(iTree)->Fill(var_mTb,temp_weight);
				// v_truth_m1.at(iTree)->Fill(var_rcjet_mass_1,temp_weight);
				// v_truth_m2.at(iTree)->Fill(var_rcjet_mass_2,temp_weight);

				v_mu_pt.at(iTree)->Fill(var_mu_pt, temp_weight);
				v_mu_eta.at(iTree)->Fill(var_mu_eta, temp_weight);
				v_mu_phi.at(iTree)->Fill(var_mu_phi, temp_weight);
				v_mu_e.at(iTree)->Fill(var_mu_e, temp_weight);
				v_el_pt.at(iTree)->Fill(var_el_pt, temp_weight);
				v_el_eta.at(iTree)->Fill(var_el_eta, temp_weight);
				v_el_phi.at(iTree)->Fill(var_el_phi, temp_weight);
				v_el_e.at(iTree)->Fill(var_el_e, temp_weight);
				v_rcjet_pt_1.at(iTree)->Fill(var_rcjet_pt_1, temp_weight);
				v_rcjet_pt_2.at(iTree)->Fill(var_rcjet_pt_2, temp_weight);
				v_rcjet_pt_3.at(iTree)->Fill(var_rcjet_pt_3, temp_weight);
				v_rcjet_pt_4.at(iTree)->Fill(var_rcjet_pt_4, temp_weight);
				v_rcjet_eta_1.at(iTree)->Fill(var_rcjet_eta_1, temp_weight);
				v_rcjet_eta_2.at(iTree)->Fill(var_rcjet_eta_2, temp_weight);
				v_rcjet_eta_3.at(iTree)->Fill(var_rcjet_eta_3, temp_weight);
				v_rcjet_eta_4.at(iTree)->Fill(var_rcjet_eta_4, temp_weight);
				v_rcjet_phi_1.at(iTree)->Fill(var_rcjet_phi_1, temp_weight);
				v_rcjet_phi_2.at(iTree)->Fill(var_rcjet_phi_2, temp_weight);
				v_rcjet_phi_3.at(iTree)->Fill(var_rcjet_phi_3, temp_weight);
				v_rcjet_phi_4.at(iTree)->Fill(var_rcjet_phi_4, temp_weight);
				v_rcjet_mass_1.at(iTree)->Fill(var_rcjet_mass_1, temp_weight);
				v_rcjet_mass_2.at(iTree)->Fill(var_rcjet_mass_2, temp_weight);
				v_rcjet_mass_3.at(iTree)->Fill(var_rcjet_mass_3, temp_weight);
				v_rcjet_mass_4.at(iTree)->Fill(var_rcjet_mass_4, temp_weight);
				v_bjet_pt_1.at(iTree)->Fill(var_bjet_pt_1, temp_weight);
				v_bjet_pt_2.at(iTree)->Fill(var_bjet_pt_2, temp_weight);
				v_bjet_pt_3.at(iTree)->Fill(var_bjet_pt_3, temp_weight);
				v_bjet_pt_4.at(iTree)->Fill(var_bjet_pt_4, temp_weight);
				v_bjet_eta_1.at(iTree)->Fill(var_bjet_eta_1, temp_weight);
				v_bjet_eta_2.at(iTree)->Fill(var_bjet_eta_2, temp_weight);
				v_bjet_eta_3.at(iTree)->Fill(var_bjet_eta_3, temp_weight);
				v_bjet_eta_4.at(iTree)->Fill(var_bjet_eta_4, temp_weight);
				v_bjet_phi_1.at(iTree)->Fill(var_bjet_phi_1, temp_weight);
				v_bjet_phi_2.at(iTree)->Fill(var_bjet_phi_2, temp_weight);
				v_bjet_phi_3.at(iTree)->Fill(var_bjet_phi_3, temp_weight);
				v_bjet_phi_4.at(iTree)->Fill(var_bjet_phi_4, temp_weight);
				v_bjet_e_1.at(iTree)->Fill(var_bjet_e_1, temp_weight);
				v_bjet_e_2.at(iTree)->Fill(var_bjet_e_2, temp_weight);
				v_bjet_e_3.at(iTree)->Fill(var_bjet_e_3, temp_weight);
				v_bjet_e_4.at(iTree)->Fill(var_bjet_e_4, temp_weight);
				v_jet_pt_1.at(iTree)->Fill(var_jet_pt_1, temp_weight);
				v_jet_pt_2.at(iTree)->Fill(var_jet_pt_2, temp_weight);
				v_jet_pt_3.at(iTree)->Fill(var_jet_pt_3, temp_weight);
				v_jet_pt_4.at(iTree)->Fill(var_jet_pt_4, temp_weight);
				v_jet_eta_1.at(iTree)->Fill(var_jet_eta_1, temp_weight);
				v_jet_eta_2.at(iTree)->Fill(var_jet_eta_2, temp_weight);
				v_jet_eta_3.at(iTree)->Fill(var_jet_eta_3, temp_weight);
				v_jet_eta_4.at(iTree)->Fill(var_jet_eta_4, temp_weight);
				v_jet_phi_1.at(iTree)->Fill(var_jet_phi_1, temp_weight);
				v_jet_phi_2.at(iTree)->Fill(var_jet_phi_2, temp_weight);
				v_jet_phi_3.at(iTree)->Fill(var_jet_phi_3, temp_weight);
				v_jet_phi_4.at(iTree)->Fill(var_jet_phi_4, temp_weight);
				v_jet_e_1.at(iTree)->Fill(var_jet_e_1, temp_weight);
				v_jet_e_2.at(iTree)->Fill(var_jet_e_2, temp_weight);
				v_jet_e_3.at(iTree)->Fill(var_jet_e_3, temp_weight);
				v_jet_e_4.at(iTree)->Fill(var_jet_e_4, temp_weight);

				v_baselepton_n.at(iTree)->Fill(NBaseLeptons, temp_weight);
				v_jet_n.at(iTree)->Fill(var_jet_n, temp_weight);
				v_bjet_n.at(iTree)->Fill(var_bjet_n, temp_weight);
				v_rcjet_n.at(iTree)->Fill(var_rcjet_n, temp_weight);
			}
		}
	}

	///////////////////////////////////////

	// Draw the plots, make 'em look nice.

	// Colours from the ATLAS palette:
	std::vector<TString> v_colours;
	v_colours.push_back("#36bdbd"); // teal
	v_colours.push_back("#ffad35"); // orange
	v_colours.push_back("#5dbe5d"); // green
	v_colours.push_back("#0b80c3"); // blue
	v_colours.push_back("#5656d7"); // purple
	v_colours.push_back("#d351ff"); // pink
	v_colours.push_back("#efda4e"); // yellow
	v_colours.push_back("#bcbc93"); // brown
	v_colours.push_back("#9a846d"); // worse brown
	v_colours.push_back("#7c7c7c"); // dark grey

	string extraText; extraText = "SUSY 0L Multi-b/t Search";

	TLegend* leg;
	leg = new TLegend(0.8,0.4,1.2,0.9); // for ratio
	//leg = new TLegend(0.6,0.2,1.0,0.7);
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.04);

	TCanvas* c; c = new TCanvas("canvas");
	c->cd();
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);

	// TPad *pad_histo = 0;
	// TPad *pad_ratio = 0;
	// c->Divide(1, 2, 0.0, 0.5);

	// TPad *c_1 = ((TPad*)(c->GetPad(1)));
	// TPad *c_2 = ((TPad*)(c->GetPad(2)));
	// pad_histo = (TPad *) c->cd(1);
	// pad_ratio = (TPad *) c->cd(2);
	// pad_histo->SetPad(0.05,0.35,0.95,0.95);
	// pad_ratio->SetPad(0.05,0.05,0.95,0.35);
 //    c_2->SetTopMargin(0.02);
 //    c_2->SetBottomMargin(0.02);
 //    c_1->SetLeftMargin(0.10);
 //    c_2->SetLeftMargin(0.10);

	/*
	for(unsigned int iTree=0; iTree<v_trees.size(); iTree++)
	{
		TString dsid;
		dsid.Form("%d", v_trees.at(iTree).second); 

		std::cout << "DSID: " << dsid << "\tPLOTTING" << std::endl;

		std::cout << v_truth_met.at(iTree)->Integral(0,999999) << std::endl;

		Bool_t isFirst=false; isFirst = (iTree==0);
		Bool_t isLast=false; isLast = ((iTree==0 && v_trees.size()==1)||(iTree==v_trees.size()-1 && v_trees.size()>1));

		// missing transverse energy
		v_truth_met.at(iTree)->SetMaximum(v_truth_met.at(iTree)->GetMaximum()*100);
		v_truth_met.at(iTree)->GetXaxis()->SetRangeUser(0,1200);
		v_truth_met.at(iTree)->SetLineColor(TColor::GetColor(v_colours.at(iTree%v_trees.size())));
		v_truth_met.at(iTree)->Rebin(4);
		leg->AddEntry(v_truth_met.at(iTree),dsid,"l");
		v_truth_met.at(iTree)->GetXaxis()->SetTitle("Missing Transverse Energy [GeV]");
		v_truth_met.at(iTree)->GetYaxis()->SetTitle("Events");
		if(isFirst) v_truth_met.at(iTree)->Draw("hist");
		else v_truth_met.at(iTree)->Draw("hist same");
		stampATLAS_ratio("Internal", 0.55, 0.8);
		stampText(extraText,0.55,0.725,0.035);
		leg->Draw();
		c->SetLogy();
		gPad->RedrawAxis();
		c->Update();
		if(isLast) c->SaveAs("plots/"+reg+"/truth_met.eps");
	}

	leg->Clear();
	c->Clear();
*/

	// LIN SCALE PLOTS
	truthPlot(v_trees, v_jet_n, v_colours, leg, c, false,
			 "Akt4 jet multiplicity", "Events", 
			 0, 20.0, 0.11, 1000000.0, 1,
			 "Internal", extraText,
			 reg, "jet_n");
	c->Clear();

	truthPlot(v_trees, v_bjet_n, v_colours, leg, c, false,
			 "b-tagged akt4 jet multiplicity", "Events", 
			 0, 20.0, 0.11, 1000000.0, 1,
			 "Internal", extraText,
			 reg, "bjet_n");
	c->Clear();

	truthPlot(v_trees, v_rcjet_n, v_colours, leg, c, false,
			 "RC akt10 jet multiplicity", "Events", 
			 0, 20.0, 0.11, 1000000.0, 1,
			 "Internal", extraText,
			 reg, "rcjet_n");
	c->Clear();

	truthPlot(v_trees, v_baselepton_n, v_colours, leg, c, false,
			  "Lepton multiplicity", "Events", 
			  0, 10.0, 0.0, 100000.0, 1,
			  "Internal", extraText,
			  reg, "lepton_n");
	c->Clear();


	// LOG SCALE PLOTS
	truthPlot(v_trees, v_truth_met, v_colours, leg, c, true,
			  "Missing transverse energy [GeV]", "Events", 
			  0, 1000.0, 0.11, 500000.0, 2, // x1 x2 y1 y2 rebin
			  "Internal", extraText,
			  reg, "truth_met");
	c->Clear();

	truthPlot(v_trees, v_truth_Meff, v_colours, leg, c, true,
			  "Effective mass [GeV]", "Events", 
			  0, 2000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "truth_meff");
	c->Clear();

	truthPlot(v_trees, v_truth_Meff_4j, v_colours, leg, c, true,
			  "Effective mass 4j [GeV]", "Events", 
			  0, 2000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "truth_meff4j");
	c->Clear();

	truthPlot(v_trees, v_truth_mTb, v_colours, leg, c, true,
			  "mTb min [GeV]", "Events", 
			  0, 2000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "truth_mTb");
	c->Clear();

	truthPlot(v_trees, v_truth_mT, v_colours, leg, c, true,
			  "Transverse mass [GeV]", "Events", 
			  0, 2000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "truth_mT");
	c->Clear();

	// el pt
	truthPlot(v_trees, v_el_pt, v_colours, leg, c, true,
			  "el p_{T} [GeV]", "Events", 
			  0, 1000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "el_pt");
	c->Clear();

	truthPlot(v_trees, v_el_eta, v_colours, leg, c, true,
			  "el #eta", "Events", 
			  -3.0, 3.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "el_eta");
	c->Clear();

	truthPlot(v_trees, v_el_phi, v_colours, leg, c, true,
			  "el #phi", "Events", 
			  -3.2, 3.2, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "el_phi");
	c->Clear();

	truthPlot(v_trees, v_el_e, v_colours, leg, c, true,
			  "el E [GeV]", "Events", 
			  0, 1000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "el_e");
	c->Clear();

	// mu pt
	truthPlot(v_trees, v_mu_pt, v_colours, leg, c, true,
			  "#mu p_{T} [GeV]", "Events", 
			  0, 1000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "mu_pt");
	c->Clear();

	truthPlot(v_trees, v_mu_eta, v_colours, leg, c, true,
			  "#mu #eta", "Events", 
			  -3.0, 3.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "mu_eta");
	c->Clear();

	truthPlot(v_trees, v_mu_phi, v_colours, leg, c, true,
			  "#mu #phi", "Events", 
			  -3.2, 3.2, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "mu_phi");
	c->Clear();

	truthPlot(v_trees, v_mu_e, v_colours, leg, c, true,
			  "#mu E [GeV]", "Events", 
			  0, 1000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "mu_e");
	c->Clear();

	// jet pt
	truthPlot(v_trees, v_jet_pt_1, v_colours, leg, c, true,
			  "Leading akt4 jet p_{T} [GeV]", "Events", 
			  0, 1000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "jet_pt_1");
	c->Clear();

	truthPlot(v_trees, v_jet_pt_2, v_colours, leg, c, true,
			  "Subleading akt4 jet p_{T} [GeV]", "Events", 
			  0, 1000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "jet_pt_2");
	c->Clear();

	truthPlot(v_trees, v_jet_pt_3, v_colours, leg, c, true,
			  "3rd akt4 jet p_{T} [GeV]", "Events", 
			  0, 1000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "jet_pt_3");
	c->Clear();

	truthPlot(v_trees, v_jet_pt_4, v_colours, leg, c, true,
			  "3rd akt4 jet p_{T} [GeV]", "Events", 
			  0, 1000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "jet_pt_4");
	c->Clear();

	// jet eta
	truthPlot(v_trees, v_jet_eta_1, v_colours, leg, c, true,
			  "Leading akt4 jet #eta", "Events", 
			  -3.0, 3.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "jet_eta_1");
	c->Clear();

	truthPlot(v_trees, v_jet_eta_2, v_colours, leg, c, true,
			  "Subleading akt4 jet #eta", "Events", 
			  -3.0, 3.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "jet_eta_2");
	c->Clear();

	truthPlot(v_trees, v_jet_eta_3, v_colours, leg, c, true,
			  "3rd akt4 jet #eta", "Events", 
			  -3.0, 3.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "jet_eta_3");
	c->Clear();

	truthPlot(v_trees, v_jet_eta_4, v_colours, leg, c, true,
			  "3rd akt4 jet #eta", "Events", 
			  -3.0, 3.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "jet_eta_4");
	c->Clear();

	// jet phi
	truthPlot(v_trees, v_jet_phi_1, v_colours, leg, c, true,
			  "Leading akt4 jet #phi", "Events", 
			  -3.2, 3.2, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "jet_phi_1");
	c->Clear();

	truthPlot(v_trees, v_jet_phi_2, v_colours, leg, c, true,
			  "Subleading akt4 jet #phi", "Events", 
			  -3.2, 3.2, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "jet_phi_2");
	c->Clear();

	truthPlot(v_trees, v_jet_phi_3, v_colours, leg, c, true,
			  "3rd akt4 jet #phi", "Events", 
			  -3.2, 3.2, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "jet_phi_3");
	c->Clear();

	truthPlot(v_trees, v_jet_phi_4, v_colours, leg, c, true,
			  "3rd akt4 jet #phi", "Events", 
			  -3.2, 3.2, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "jet_phi_4");
	c->Clear();

	// jet energy
	truthPlot(v_trees, v_jet_e_1, v_colours, leg, c, true,
			  "Leading akt4 jet Energy [GeV]", "Events", 
			  0, 2000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "jet_e_1");
	c->Clear();

	truthPlot(v_trees, v_jet_e_2, v_colours, leg, c, true,
			  "Subleading akt4 jet Energy [GeV]", "Events", 
			  0, 2000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "jet_e_2");
	c->Clear();

	truthPlot(v_trees, v_jet_e_3, v_colours, leg, c, true,
			  "3rd akt4 jet Energy [GeV]", "Events", 
			  0, 2000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "jet_e_3");
	c->Clear();

	truthPlot(v_trees, v_jet_e_4, v_colours, leg, c, true,
			  "3rd akt4 jet Energy [GeV]", "Events", 
			  0, 2000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "jet_e_4");
	c->Clear();

	// bjet pt
	truthPlot(v_trees, v_bjet_pt_1, v_colours, leg, c, true,
			  "Leading b-tagged akt4 jet p_{T} [GeV]", "Events", 
			  0, 1000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "bjet_pt_1");
	c->Clear();

	truthPlot(v_trees, v_bjet_pt_2, v_colours, leg, c, true,
			  "Subleading b-tagged akt4 jet p_{T} [GeV]", "Events", 
			  0, 1000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "bjet_pt_2");
	c->Clear();

	truthPlot(v_trees, v_bjet_pt_3, v_colours, leg, c, true,
			  "3rd b-tagged akt4 jet p_{T} [GeV]", "Events", 
			  0, 1000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "bjet_pt_3");
	c->Clear();

	truthPlot(v_trees, v_bjet_pt_4, v_colours, leg, c, true,
			  "3rd b-tagged akt4 jet p_{T} [GeV]", "Events", 
			  0, 1000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "bjet_pt_4");
	c->Clear();

	// bjet eta
	truthPlot(v_trees, v_bjet_eta_1, v_colours, leg, c, true,
			  "Leading b-tagged akt4 jet #eta", "Events", 
			  -3.0, 3.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "bjet_eta_1");
	c->Clear();

	truthPlot(v_trees, v_bjet_eta_2, v_colours, leg, c, true,
			  "Subleading b-tagged akt4 jet #eta", "Events", 
			  -3.0, 3.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "bjet_eta_2");
	c->Clear();

	truthPlot(v_trees, v_bjet_eta_3, v_colours, leg, c, true,
			  "3rd b-tagged akt4 jet #eta", "Events", 
			  -3.0, 3.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "bjet_eta_3");
	c->Clear();

	truthPlot(v_trees, v_bjet_eta_4, v_colours, leg, c, true,
			  "3rd b-tagged akt4 jet #eta", "Events", 
			  -3.0, 3.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "bjet_eta_4");
	c->Clear();

	// bjet phi
	truthPlot(v_trees, v_bjet_phi_1, v_colours, leg, c, true,
			  "Leading b-tagged akt4 jet #phi", "Events", 
			  -3.2, 3.2, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "bjet_phi_1");
	c->Clear();

	truthPlot(v_trees, v_bjet_phi_2, v_colours, leg, c, true,
			  "Subleading b-tagged akt4 jet #phi", "Events", 
			  -3.2, 3.2, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "bjet_phi_2");
	c->Clear();

	truthPlot(v_trees, v_bjet_phi_3, v_colours, leg, c, true,
			  "3rd b-tagged akt4 jet #phi", "Events", 
			  -3.2, 3.2, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "bjet_phi_3");
	c->Clear();

	truthPlot(v_trees, v_bjet_phi_4, v_colours, leg, c, true,
			  "3rd b-tagged akt4 jet #phi", "Events", 
			  -3.2, 3.2, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "bjet_phi_4");
	c->Clear();

	// bjet energy
	truthPlot(v_trees, v_bjet_e_1, v_colours, leg, c, true,
			  "Leading b-tagged akt4 jet Energy [GeV]", "Events", 
			  0, 2000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "bjet_e_1");
	c->Clear();

	truthPlot(v_trees, v_bjet_e_2, v_colours, leg, c, true,
			  "Subleading b-tagged akt4 jet Energy [GeV]", "Events", 
			  0, 2000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "bjet_e_2");
	c->Clear();

	truthPlot(v_trees, v_bjet_e_3, v_colours, leg, c, true,
			  "3rd b-tagged akt4 jet Energy [GeV]", "Events", 
			  0, 2000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "bjet_e_3");
	c->Clear();

	truthPlot(v_trees, v_bjet_e_4, v_colours, leg, c, true,
			  "3rd b-tagged akt4 jet Energy [GeV]", "Events", 
			  0, 2000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "bjet_e_4");
	c->Clear();

	// rc jet pt
	truthPlot(v_trees, v_rcjet_pt_1, v_colours, leg, c, true,
			  "Leading RC akt10 jet p_{T} [GeV]", "Events", 
			  0, 2000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "rcjet_pt_1");
	c->Clear();

	truthPlot(v_trees, v_rcjet_pt_2, v_colours, leg, c, true,
			  "Subleading RC akt10 jet p_{T} [GeV]", "Events", 
			  0, 2000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "rcjet_pt_2");
	c->Clear();

	truthPlot(v_trees, v_rcjet_pt_3, v_colours, leg, c, true,
			  "3rd RC akt10 jet p_{T} [GeV]", "Events", 
			  0, 2000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "rcjet_pt_3");
	c->Clear();

	truthPlot(v_trees, v_rcjet_pt_4, v_colours, leg, c, true,
			  "4th RC akt10 jet p_{T} [GeV]", "Events", 
			  0, 2000.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "rcjet_pt_4");
	c->Clear();

	// rc jet eta
	truthPlot(v_trees, v_rcjet_eta_1, v_colours, leg, c, true,
			  "Leading RC akt10 jet #eta", "Events", 
			  -3.0, 3.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "rcjet_eta_1");
	c->Clear();

	truthPlot(v_trees, v_rcjet_eta_2, v_colours, leg, c, true,
			  "Subleading RC akt10 jet #eta", "Events", 
			  -3.0, 3.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "rcjet_eta_2");
	c->Clear();

	truthPlot(v_trees, v_rcjet_eta_3, v_colours, leg, c, true,
			  "3rd RC akt10 jet #eta", "Events", 
			  -3.0, 3.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "rcjet_eta_3");
	c->Clear();

	truthPlot(v_trees, v_rcjet_eta_4, v_colours, leg, c, true,
			  "4th RC akt10 jet #eta", "Events", 
			  -3.0, 3.0, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "rcjet_eta_4");
	c->Clear();

	// rc jet phi
	truthPlot(v_trees, v_rcjet_phi_1, v_colours, leg, c, true,
			  "Leading RC akt10 jet #phi", "Events", 
			  -3.2, 3.2, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "rcjet_phi_1");
	c->Clear();

	truthPlot(v_trees, v_rcjet_phi_2, v_colours, leg, c, true,
			  "Subleading RC akt10 jet #phi", "Events", 
			  -3.2, 3.2, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "rcjet_phi_2");
	c->Clear();

	truthPlot(v_trees, v_rcjet_phi_3, v_colours, leg, c, true,
			  "3rd RC akt10 jet #phi", "Events", 
			  -3.2, 3.2, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "rcjet_phi_3");
	c->Clear();

	truthPlot(v_trees, v_rcjet_phi_4, v_colours, leg, c, true,
			  "4th RC akt10 jet #phi", "Events", 
			  -3.2, 3.2, 0.11, 1000000.0, 2,
			  "Internal", extraText,
			  reg, "rcjet_phi_4");
	c->Clear();

	// rcjet mass
	truthPlot(v_trees, v_rcjet_mass_1, v_colours, leg, c, true,
			  "Leading RC akt10 jet mass [GeV]", "Events", 
			  0, 2000.0, 0.11, 100000000.0, 2,
			  "Internal", extraText,
			  reg, "rcjet_m_1");
	c->Clear();

	truthPlot(v_trees, v_rcjet_mass_2, v_colours, leg, c, true,
			  "Subleading RC akt10 jet mass [GeV]", "Events", 
			  0, 2000.0, 0.11, 100000000.0, 2,
			  "Internal", extraText,
			  reg, "rcjet_m_2");
	c->Clear();

	truthPlot(v_trees, v_rcjet_mass_3, v_colours, leg, c, true,
			  "3rd RC akt10 jet mass [GeV]", "Events", 
			  0, 2000.0, 0.11, 100000000.0, 2,
			  "Internal", extraText,
			  reg, "rcjet_m_3");
	c->Clear();

	truthPlot(v_trees, v_rcjet_mass_4, v_colours, leg, c, true,
			  "4th RC akt10 jet mass [GeV]", "Events", 
			  0, 2000.0, 0.11, 100000000.0, 2,
			  "Internal", extraText,
			  reg, "rcjet_m_4");
	c->Clear();

	// Sign out.
	std::cout << "Done with plotting." << std::endl;

	return;
}

void stampATLAS(const std::string &text, float x, float y)
{
  TLatex l;
  l.SetNDC();
  l.SetTextFont(72);
  l.SetTextColor(1);
  l.SetTextSize(0.06);
  l.DrawLatex(x, y, "ATLAS");
  TLatex p;
  p.SetNDC();
  p.SetTextFont(42);
  p.SetTextColor(1);
  p.SetTextSize(0.06);
  p.DrawLatex(x+0.15, y, text.c_str());
}

void stampATLAS_ratio(const std::string &text, float x, float y)
{
  TLatex l;
  l.SetNDC();
  l.SetTextFont(72);
  l.SetTextColor(1);
  l.SetTextSize(0.06);
  l.DrawLatex(x, y, "ATLAS");
  TLatex p;
  p.SetNDC();
  p.SetTextFont(42);
  p.SetTextColor(1);
  p.SetTextSize(0.06);
  p.DrawLatex(x+0.10, y, text.c_str()); // CHANGE TO THIS WHEN RATIO
  //p.DrawLatex(x+0.15, y, text.c_str());
}

void stampLumiText(float lumi, float x, float y, const std::string &text, float size)
{
  std::stringstream ss;
  ss << "#int L dt = " << lumi << " fb^{-1}, " << text;
  TLatex l;
  l.SetNDC();
  l.SetTextFont(42);
  l.SetTextColor(1);
  l.SetTextSize(size);
  l.DrawLatex(x, y, ss.str().c_str());
}

void stampText(const std::string &text, float x, float y, float size) 
{
  TLatex l;
  l.SetNDC();
  l.SetTextFont(42);
  l.SetTextColor(1);
  l.SetTextSize(size);
  l.DrawLatex(x, y, text.c_str());
}

void truthPlot(std::vector<pair<TTree*, Int_t>> treevec,
			   std::vector<TH1F*> histovec,
			   std::vector<TString> colourvec,
			   TLegend*& leg,
			   TCanvas*& c,
			   Bool_t doLog,
			   TString xLabel,
			   TString yLabel,
			   float xmin, 
			   float xmax,
			   float ymin,
			   float ymax,
			   int rebin,
			   const std::string atlasLabel,
			   const std::string extraText,
			   TString reg,
			   TString filename)
{
	c->Divide(1, 2, 0.0, 0.5);
	TPad *c_1 = 0; c_1 = ((TPad*)(c->GetPad(1)));
	TPad *c_2 = 0; c_2 = ((TPad*)(c->GetPad(2)));
	c_1->SetPad(0.05,0.3,0.95,0.95);
	c_2->SetPad(0.05,0.10,0.95,0.3);
    c_2->SetTopMargin(0.02);
    c_2->SetBottomMargin(0.30);
    c_1->SetLeftMargin(0.10);
    c_2->SetLeftMargin(0.10);

  	for(unsigned int iTree=0; iTree<treevec.size(); iTree++)
  	{
	    TString dsid;
	    dsid.Form("%d", treevec.at(iTree).second); 

	    std::cout << "DSID: " << dsid << "\tPLOTTING" << std::endl;

	    Bool_t isFirst=false; isFirst = (iTree==0);
	    Bool_t isLast=false; isLast = ((iTree==0 && treevec.size()==1)||(iTree==treevec.size()-1 && treevec.size()>1));

	    // Main pad
		c_1->cd();
	    histovec.at(iTree)->SetMinimum(ymin);
	    if(doLog) histovec.at(iTree)->SetMaximum(ymax);
	    else histovec.at(iTree)->SetMaximum(histovec.at(iTree)->GetMaximum()*1.33);
	    histovec.at(iTree)->GetXaxis()->SetRangeUser(xmin,xmax);
	    histovec.at(iTree)->SetLineColor(TColor::GetColor(colourvec.at(iTree%treevec.size())));
	    leg->AddEntry(histovec.at(iTree),dsid,"l");
	    histovec.at(iTree)->GetXaxis()->SetTitle(xLabel);
	    histovec.at(iTree)->GetYaxis()->SetTitle(yLabel);
	    // histovec.at(iTree)->GetYaxis()->SetTitleSize(0.12);
	    // histovec.at(iTree)->GetXaxis()->SetTitleSize(0.12);
	    //histovec.at(iTree)->Rebin(rebin);
	 	if(isFirst) histovec.at(iTree)->Draw("hist");
	    else histovec.at(iTree)->Draw("hist same");
	    stampATLAS_ratio(atlasLabel, 0.55, 0.8);
	    stampText(extraText,0.55,0.725,0.035);
	    stampText((std::string)reg,0.55,0.650,0.035);
  	    stampText("Normalised to 3.3 fb^{-1}",0.55,0.575,0.035);
	    leg->Draw();
	    if(doLog) c_1->SetLogy();
	    else c_1->SetLogy(0);

	    // construct the ratio plot ...

	    TH1F* rat = (TH1F*)histovec.at(iTree)->Clone("rat");
	  //  	if(dsid=="410003" || dsid=="407012") 
	  //  		{
	  //  			std::cout << "for dsid " << dsid << ", no entry in ratio pad" << std::endl;
	  //  			continue;
			// }

	   	if(dsid=="410003"  || dsid=="410004") 
	   		{
//	   			std::cout << "for dsid " << dsid << ", we divide by 410003" << std::endl;
	   			rat->Divide(histovec.at(iTree),histovec.front());
			}
	   	else
		   	{
//	   			std::cout << "for dsid " << dsid << ", we divide by 407012" << std::endl;
	   			rat->Divide(histovec.at(iTree),histovec.back());
			}

	     // Ratio pad
	    c_2->cd();
	    rat->SetMinimum(0.1);
	    rat->SetMaximum(1.9);
	    rat->GetXaxis()->SetRangeUser(xmin,xmax);
	    rat->GetXaxis()->SetTitle(xLabel);
	    rat->GetYaxis()->SetTitle("Ratio");
	    rat->GetYaxis()->SetTitleOffset(0.30);
	   	rat->GetXaxis()->SetTitleSize(0.12);
	   	rat->GetYaxis()->SetTitleSize(0.12);
	   	rat->GetYaxis()->SetLabelSize(0.12);
	   	rat->GetXaxis()->SetLabelSize(0.12);
	   	rat->GetYaxis()->SetNdivisions(4, 0, 2);

	   	// line at 1.0
	    TLine* lin; lin = new TLine(rat->GetXaxis()->GetBinLowEdge(1), 1.0, rat->GetXaxis()->GetBinUpEdge(rat->GetNbinsX()+1), 1.0);
   		lin->SetLineColor(kBlack);
   		lin->SetLineWidth(1);
   		lin->SetLineStyle(2);
   		lin->Draw();
   		//gPad->RedrawAxis();

	     // if(!(dsid=="410003" || dsid=="407012"))
   		if(isFirst) rat->Draw("e0");
	    if(!(dsid=="410004" || dsid=="407012")) rat->Draw("e0 same");
	     //else rat->Draw("e1 same");


	    gPad->RedrawAxis();
	    c->Update();
  }
 c->SaveAs("plots/"+reg+"/"+filename+".eps"); 

  leg->Clear();
  c->Clear();

  return;
}
