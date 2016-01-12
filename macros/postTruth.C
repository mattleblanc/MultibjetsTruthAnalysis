//
// postTruth.C
// ATLAS 2015 SUSY Multi-b/t search truth analysis post-processing.
// MLB [UVic] <matt.leblanc@cern.ch>
//

// Provided as-is for reference, but will probably require some modifications if you
// want to actually get it running. This produces a file with a 2-d histogram in it
// whose contents are used to actually dump the systematic uncertainties using 
// dumpYields.C

// I actually run this on my laptop, to where I also download the merged output of running the main
// truth analysis over US Connect's condor system. The output file is about 3 GB, which is managable for me.

// Run as > root -l -b -q postTruth.C

#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom.h"

void theTruth(void);

void postTruth(void)
{
	//std::cout << "The truth is out there." << std::endl;

	theTruth();

	//TString inDir = "/Users/mleblanc/susyGtt/20151101_truth/trfOut/";
	TString inDir = "";
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

	// TTree* t_410000; t_410000 = (TTree*)f_410000->Get("out_tree");
	// TTree* t_410001; t_410001 = (TTree*)f_410001->Get("out_tree");
	// TTree* t_410002; t_410002 = (TTree*)f_410002->Get("out_tree");
	TTree* t_410003; t_410003 = (TTree*)f_410003->Get("out_tree");
	TTree* t_410004; t_410004 = (TTree*)f_410004->Get("out_tree");
	// TTree* t_410006; t_410006 = (TTree*)f_410006->Get("out_tree");
	TTree* t_407012; t_407012 = (TTree*)f_407012->Get("out_tree");
	TTree* t_407032; t_407032 = (TTree*)f_407032->Get("out_tree");
	TTree* t_407036; t_407036 = (TTree*)f_407036->Get("out_tree");
	TTree* t_407040; t_407040 = (TTree*)f_407040->Get("out_tree");
	//TTree* t_407044; t_407044 = (TTree*)f_407044->Get("out_tree");

	std::vector<pair<TTree*, Int_t>> v_trees;
	//// v_trees.push_back(std::make_pair(t_410000,410000));
	//// v_trees.push_back(std::make_pair(t_410001,410001));
	//// v_trees.push_back(std::make_pair(t_410002,410002));
	v_trees.push_back(std::make_pair(t_410003,410003));
	v_trees.push_back(std::make_pair(t_410004,410004));
	//// v_trees.push_back(std::make_pair(t_410006,410006));
	v_trees.push_back(std::make_pair(t_407012,407012));
	v_trees.push_back(std::make_pair(t_407032,407032));
	v_trees.push_back(std::make_pair(t_407036,407036));
	v_trees.push_back(std::make_pair(t_407040,407040));
	//v_trees.push_back(std::make_pair(t_407044,407044));

	TH2D* h_yields; h_yields = new TH2D("yields","yields",7,1,8,72,1,73); // x=DSID, y=SR
	TH2D* h_yields_trf; h_yields_trf = new TH2D("yields_trf","yields_trf",7,1,8,72,1,73); // x=DSID, y=SR


	for(unsigned int iTree=0; iTree<v_trees.size(); iTree++)
	{
		TString reg;
		reg.Form("%d", v_trees.at(iTree).second); 

		std::cout << "DSID: " << reg << "\t" << v_trees.at(iTree).first->GetEntries() 
				  << " entries." << std::endl;

		// for each tree, load the branches.
        Float_t weight = 1.0;

        // Always use nominal XS, k-factor.
        // Get these from SUSYTools:
        // https://svnweb.cern.ch/trac/atlasoff/browser/PhysicsAnalysis/SUSYPhys/SUSYTools/trunk/data/susy_crosssections_13TeV.txt
      	if(reg=="410000" || reg=="410001" || reg=="410002" || reg=="410003" || reg=="410004" || reg=="410006")
      		weight *= 831.76*1.*0.543*1.;

      	if(reg=="407012" || reg=="407032" || reg=="407036" || reg=="407040" || reg=="407044")
      		weight *=  831.76*1.*0.0092194758*1.;

      	/*
      		Make sure to use the proper sum-of-weights per-sample, though.
      		Get these by opening up the merged files and running e.g.
      			root > TH1F* histo_temp = new TH1F("blah", "blah", boundaries)
				root > myTree->Draw("1>>blah", "(1)*mc_weight")
				root > std::cout << histo_temp->Integral() << std::endl
		*/

        //if(reg=="410000") weight /= 1.67772e+07;//20099000.0;
        // if(reg=="410001") weight /= 19995000.0;
        // if(reg=="410002") weight /= 20000000.0;
        if(reg=="410003") weight /= 2.85815e+06;//4910000.0;
        if(reg=="410004") weight /= 9.82e+06; //9820000.0;
        // if(reg=="410006") weight /= 10000000.0;

        if(reg=="407012") weight /= 2.74497;
		if(reg=="407032") weight /= 2.95191;
        if(reg=="407036") weight /= 2.43458;
        if(reg=="407040") weight /= 3.7725e+06; 
        //if(reg=="407044") weight /= 2.85515e+09;

		weight*=1.e3; // pb to fb
		weight*=3.3; // 2015 lumi

		// for each tree, load the branches.
		Float_t mc_weight; v_trees.at(iTree).first->SetBranchAddress("mc_weight",&mc_weight);

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
		
		Int_t isGbbVRI2; v_trees.at(iTree).first->SetBranchAddress("isGbbVRI2",&isGbbVRI2);
		Int_t isGbbVRII2; v_trees.at(iTree).first->SetBranchAddress("isGbbVRII2",&isGbbVRII2);
		Int_t isGbbVRIII2; v_trees.at(iTree).first->SetBranchAddress("isGbbVRIII2",&isGbbVRIII2);
		Int_t isGbbVRI4; v_trees.at(iTree).first->SetBranchAddress("isGbbVRI4",&isGbbVRI4);
		Int_t isGbbVRII4; v_trees.at(iTree).first->SetBranchAddress("isGbbVRII4",&isGbbVRII4);

		Int_t isVR1LGtt0LI; v_trees.at(iTree).first->SetBranchAddress("isVR1LGtt0LI",&isVR1LGtt0LI);
		Int_t isVR1LGtt0LII; v_trees.at(iTree).first->SetBranchAddress("isVR1LGtt0LII",&isVR1LGtt0LII);
		Int_t isVR1LGtt0LIII; v_trees.at(iTree).first->SetBranchAddress("isVR1LGtt0LIII",&isVR1LGtt0LIII);
		Int_t isVR1LGtt0LIV; v_trees.at(iTree).first->SetBranchAddress("isVR1LGtt0LIV",&isVR1LGtt0LIV);
		Int_t isVR0LGtt0LI; v_trees.at(iTree).first->SetBranchAddress("isVR0LGtt0LI",&isVR0LGtt0LI);
		Int_t isVR0LGtt0LII; v_trees.at(iTree).first->SetBranchAddress("isVR0LGtt0LII",&isVR0LGtt0LII);
		Int_t isVR0LGtt0LIII; v_trees.at(iTree).first->SetBranchAddress("isVR0LGtt0LIII",&isVR0LGtt0LIII);
		Int_t isVR0LGtt0LIV; v_trees.at(iTree).first->SetBranchAddress("isVR0LGtt0LIV",&isVR0LGtt0LIV);

		Int_t isVRGtt1LI2mT2b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LI2mT2b",&isVRGtt1LI2mT2b);
		Int_t isVRGtt1LII2mT2b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LII2mT2b",&isVRGtt1LII2mT2b);
		Int_t isVRGtt1LI4mT2b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LI4mT2b",&isVRGtt1LI4mT2b);
		Int_t isVRGtt1LII4mT2b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LII4mT2b",&isVRGtt1LII4mT2b);
		Int_t isVRGtt1LI2mT3b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LI2mT3b",&isVRGtt1LI2mT3b);
		Int_t isVRGtt1LII2mT3b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LII2mT3b",&isVRGtt1LII2mT3b);
		Int_t isVRGtt1LI4mT3b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LI4mT3b",&isVRGtt1LI4mT3b); 
		Int_t isVRGtt1LII4mT3b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LII4mT3b",&isVRGtt1LII4mT3b);
		Int_t isVRGtt1LI2mTb2b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LI2mTb2b",&isVRGtt1LI2mTb2b);
		Int_t isVRGtt1LII2mTb2b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LII2mTb2b",&isVRGtt1LII2mTb2b);
		Int_t isVRGtt1LI4mTb2b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LI4mTb2b",&isVRGtt1LI4mTb2b);
		Int_t isVRGtt1LII4mTb2b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LII4mTb2b",&isVRGtt1LII4mTb2b);
		Int_t isVRGtt1LI2mTb3b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LI2mTb3b",&isVRGtt1LI2mTb3b);
		Int_t isVRGtt1LII2mTb3b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LII2mTb3b",&isVRGtt1LII2mTb3b);
		Int_t isVRGtt1LI4mTb3b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LI4mTb3b",&isVRGtt1LI4mTb3b);
		Int_t isVRGtt1LII4mTb3b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LII4mTb3b",&isVRGtt1LII4mTb3b);
		Int_t isVRGtt1LI2mT4b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LI2mT4b",&isVRGtt1LI2mT4b);
		Int_t isVRGtt1LII2mT4b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LII2mT4b",&isVRGtt1LII2mT4b);
		Int_t isVRGtt1LIII22b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LIII22b",&isVRGtt1LIII22b);
		Int_t isVRGtt1LIII42b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LIII42b",&isVRGtt1LIII42b);
		Int_t isVRGtt1LIII23b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LIII23b",&isVRGtt1LIII23b);
		Int_t isVRGtt1LIII43b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LIII43b",&isVRGtt1LIII43b);
		Int_t isVRGtt1LIII24b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LIII24b",&isVRGtt1LIII24b);
		Int_t isVRGtt1LIII44b; v_trees.at(iTree).first->SetBranchAddress("isVRGtt1LIII44b",&isVRGtt1LIII44b);

		Int_t NSignalLeptons;  v_trees.at(iTree).first->SetBranchAddress("NSignalLeptons",&NSignalLeptons);
		Int_t NJets;  v_trees.at(iTree).first->SetBranchAddress("NJets",&NJets);
		Int_t NBJets;  v_trees.at(iTree).first->SetBranchAddress("NBJets",&NBJets);
		Int_t NTopJets;  v_trees.at(iTree).first->SetBranchAddress("NTopJets",&NTopJets);

		Float_t var_Met;  v_trees.at(iTree).first->SetBranchAddress("var_Met",&var_Met);
		Float_t var_Meff;  v_trees.at(iTree).first->SetBranchAddress("var_Meff",&var_Meff);
		Float_t var_mT;  v_trees.at(iTree).first->SetBranchAddress("var_mT",&var_mT);
		Float_t var_mTb;  v_trees.at(iTree).first->SetBranchAddress("var_mTb",&var_mTb);

		Bool_t isTRF; v_trees.at(iTree).first->SetBranchAddress("isTRF",&isTRF);
		Bool_t isTRF_incl; v_trees.at(iTree).first->SetBranchAddress("isTRF_incl",&isTRF_incl);
		Double_t TRF_wgt; v_trees.at(iTree).first->SetBranchAddress("TRF_wgt",&TRF_wgt);
		Int_t NBJets_TRF;  v_trees.at(iTree).first->SetBranchAddress("NBJets_TRF",&NBJets_TRF);

		// Loop over the entries in each tree and do the thing.
		for(unsigned int i=0; i < v_trees.at(iTree).first->GetEntries(); i++)
		{
			v_trees.at(iTree).first->GetEntry(i);
			if(i%1000000==true) std::cout << "DSID: " << v_trees.at(iTree).second  << "\tEntry " 
										  << (i-1) << " / " << v_trees.at(iTree).first->GetEntries() << std::endl;

			Float_t weight_temp=-1.0; weight_temp=weight;
			weight_temp*=mc_weight;
						
		   //    std::cout << "var_Meff is " << var_Meff << std::endl;
		   //    std::cout << "var_mT is " << var_mT << std::endl;
		   //    std::cout << "var_mTb is " << var_mTb << std::endl;
		   //    std::cout << "var_Met is " << var_Met << std::endl;
		   //    std::cout << "NJets is " << NJets << std::endl;
		   //    std::cout << "NBJets is " << NBJets << std::endl;
		   //    std::cout << "NTopJets is " << NTopJets << std::endl;

			if(i==0)
			{
				h_yields->Fill(reg, "All", 0.0);
				h_yields->Fill(reg, "Presel", 0.0);
				h_yields->Fill(reg, "PreGbb", 0.0);
				h_yields->Fill(reg, "PreGtt0l", 0.0);
				h_yields->Fill(reg, "PreGtt1l", 0.0);

				//h_yields->Fill(reg, "GbbSRA1", 0.0);
				//h_yields->Fill(reg, "GbbSRB1", 0.0);
				h_yields->Fill(reg, "GbbSRA2", 0.0);
				h_yields->Fill(reg, "GbbSRB2", 0.0);
				h_yields->Fill(reg, "GbbSRC2", 0.0);
				h_yields->Fill(reg, "GbbSRA4", 0.0);
				h_yields->Fill(reg, "GbbSRB4", 0.0);

				h_yields->Fill(reg, "Gtt1LSRA2", 0.0);
				h_yields->Fill(reg, "Gtt1LSRB2", 0.0);
				h_yields->Fill(reg, "Gtt1LSRC2", 0.0);
				h_yields->Fill(reg, "Gtt1LSRA4", 0.0);
				h_yields->Fill(reg, "Gtt1LSRB4", 0.0);
				h_yields->Fill(reg, "Gtt1LSRC4", 0.0);

				h_yields->Fill(reg, "Gtt0LSRA", 0.0);
				h_yields->Fill(reg, "Gtt0LSRB", 0.0);
				h_yields->Fill(reg, "Gtt0LSRC", 0.0);
				h_yields->Fill(reg, "Gtt0LSRD", 0.0);

				h_yields->Fill(reg, "GbbCRA2", 0.0);
				h_yields->Fill(reg, "GbbCRB2", 0.0);
				h_yields->Fill(reg, "GbbCRC2", 0.0);
				h_yields->Fill(reg, "GbbCRA4", 0.0);
				h_yields->Fill(reg, "GbbCRB4", 0.0);

				h_yields->Fill(reg, "Gtt1LCRA2", 0.0);
				h_yields->Fill(reg, "Gtt1LCRB2", 0.0);
				h_yields->Fill(reg, "Gtt1LCRC2", 0.0);
				h_yields->Fill(reg, "Gtt1LCRA4", 0.0);
				h_yields->Fill(reg, "Gtt1LCRB4", 0.0);
				h_yields->Fill(reg, "Gtt1LCRC4", 0.0);

				h_yields->Fill(reg, "Gtt0LCRA", 0.0);
				h_yields->Fill(reg, "Gtt0LCRB", 0.0);
				h_yields->Fill(reg, "Gtt0LCRC", 0.0);
				h_yields->Fill(reg, "Gtt0LCRD", 0.0);

				h_yields->Fill(reg, "GbbVRI2", 0.0);
				h_yields->Fill(reg, "GbbVRII2", 0.0);
				h_yields->Fill(reg, "GbbVRIII2", 0.0);
				h_yields->Fill(reg, "GbbVRI4", 0.0);
				h_yields->Fill(reg, "GbbVRII4", 0.0);
				h_yields->Fill(reg, "VR1LGtt0LI", 0.0);
				h_yields->Fill(reg, "VR1LGtt0LII", 0.0);
				h_yields->Fill(reg, "VR1LGtt0LIII", 0.0);
				h_yields->Fill(reg, "VR1LGtt0LIV", 0.0);
				h_yields->Fill(reg, "VR0LGtt0LI", 0.0);
				h_yields->Fill(reg, "VR0LGtt0LII", 0.0);
				h_yields->Fill(reg, "VR0LGtt0LIII", 0.0);
				h_yields->Fill(reg, "VR0LGtt0LIV", 0.0);
				h_yields->Fill(reg, "VRGtt1LI2mT2b", 0.0);
				h_yields->Fill(reg, "VRGtt1LII2mT2b", 0.0);
				h_yields->Fill(reg, "VRGtt1LI4mT2b", 0.0);
				h_yields->Fill(reg, "VRGtt1LII4mT2b", 0.0);
				h_yields->Fill(reg, "VRGtt1LI2mT3b", 0.0);
				h_yields->Fill(reg, "VRGtt1LII2mT3b", 0.0);
				h_yields->Fill(reg, "VRGtt1LI4mT3b", 0.0); 
				h_yields->Fill(reg, "VRGtt1LII4mT3b", 0.0);
				h_yields->Fill(reg, "VRGtt1LI2mTb2b", 0.0);
				h_yields->Fill(reg, "VRGtt1LII2mTb2b", 0.0);
				h_yields->Fill(reg, "VRGtt1LI4mTb2b", 0.0);
				h_yields->Fill(reg, "VRGtt1LII4mTb2b", 0.0);
				h_yields->Fill(reg, "VRGtt1LI2mTb3b", 0.0);
				h_yields->Fill(reg, "VRGtt1LII2mTb3b", 0.0);
				h_yields->Fill(reg, "VRGtt1LI4mTb3b", 0.0);
				h_yields->Fill(reg, "VRGtt1LII4mTb3b", 0.0);
				h_yields->Fill(reg, "VRGtt1LI2mT4b", 0.0);
				h_yields->Fill(reg, "VRGtt1LII2mT4b", 0.0);
				h_yields->Fill(reg, "VRGtt1LIII22b", 0.0);
				h_yields->Fill(reg, "VRGtt1LIII42b", 0.0);
				h_yields->Fill(reg, "VRGtt1LIII23b", 0.0);
				h_yields->Fill(reg, "VRGtt1LIII43b", 0.0);
				h_yields->Fill(reg, "VRGtt1LIII24b", 0.0);
				h_yields->Fill(reg, "VRGtt1LIII44b", 0.0);

				h_yields_trf->Fill(reg, "All", 0.0);
				h_yields_trf->Fill(reg, "Presel", 0.0);
				h_yields_trf->Fill(reg, "PreGbb", 0.0);
				h_yields_trf->Fill(reg, "PreGtt0l", 0.0);
				h_yields_trf->Fill(reg, "PreGtt1l", 0.0);

				//h_yields_trf->Fill(reg, "GbbSRA1", 0.0);
				//h_yields_trf->Fill(reg, "GbbSRB1", 0.0);
				h_yields_trf->Fill(reg, "GbbSRA2", 0.0);
				h_yields_trf->Fill(reg, "GbbSRB2", 0.0);
				h_yields_trf->Fill(reg, "GbbSRC2", 0.0);
				h_yields_trf->Fill(reg, "GbbSRA4", 0.0);
				h_yields_trf->Fill(reg, "GbbSRB4", 0.0);

				h_yields_trf->Fill(reg, "Gtt1LSRA2", 0.0);
				h_yields_trf->Fill(reg, "Gtt1LSRB2", 0.0);
				h_yields_trf->Fill(reg, "Gtt1LSRC2", 0.0);
				h_yields_trf->Fill(reg, "Gtt1LSRA4", 0.0);
				h_yields_trf->Fill(reg, "Gtt1LSRB4", 0.0);
				h_yields_trf->Fill(reg, "Gtt1LSRC4", 0.0);

				h_yields_trf->Fill(reg, "Gtt0LSRA", 0.0);
				h_yields_trf->Fill(reg, "Gtt0LSRB", 0.0);
				h_yields_trf->Fill(reg, "Gtt0LSRC", 0.0);
				h_yields_trf->Fill(reg, "Gtt0LSRD", 0.0);

				h_yields_trf->Fill(reg, "GbbCRA2", 0.0);
				h_yields_trf->Fill(reg, "GbbCRB2", 0.0);
				h_yields_trf->Fill(reg, "GbbCRC2", 0.0);
				h_yields_trf->Fill(reg, "GbbCRA4", 0.0);
				h_yields_trf->Fill(reg, "GbbCRB4", 0.0);

				h_yields_trf->Fill(reg, "Gtt1LCRA2", 0.0);
				h_yields_trf->Fill(reg, "Gtt1LCRB2", 0.0);
				h_yields_trf->Fill(reg, "Gtt1LCRC2", 0.0);
				h_yields_trf->Fill(reg, "Gtt1LCRA4", 0.0);
				h_yields_trf->Fill(reg, "Gtt1LCRB4", 0.0);
				h_yields_trf->Fill(reg, "Gtt1LCRC4", 0.0);

				h_yields_trf->Fill(reg, "Gtt0LCRA", 0.0);
				h_yields_trf->Fill(reg, "Gtt0LCRB", 0.0);
				h_yields_trf->Fill(reg, "Gtt0LCRC", 0.0);
				h_yields_trf->Fill(reg, "Gtt0LCRD", 0.0);

				h_yields_trf->Fill(reg, "GbbVRI2", 0.0);
				h_yields_trf->Fill(reg, "GbbVRII2", 0.0);
				h_yields_trf->Fill(reg, "GbbVRIII2", 0.0);
				h_yields_trf->Fill(reg, "GbbVRI4", 0.0);
				h_yields_trf->Fill(reg, "GbbVRII4", 0.0);
				h_yields_trf->Fill(reg, "VR1LGtt0LI", 0.0);
				h_yields_trf->Fill(reg, "VR1LGtt0LII", 0.0);
				h_yields_trf->Fill(reg, "VR1LGtt0LIII", 0.0);
				h_yields_trf->Fill(reg, "VR1LGtt0LIV", 0.0);
				h_yields_trf->Fill(reg, "VR0LGtt0LI", 0.0);
				h_yields_trf->Fill(reg, "VR0LGtt0LII", 0.0);
				h_yields_trf->Fill(reg, "VR0LGtt0LIII", 0.0);
				h_yields_trf->Fill(reg, "VR0LGtt0LIV", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LI2mT2b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LII2mT2b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LI4mT2b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LII4mT2b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LI2mT3b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LII2mT3b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LI4mT3b", 0.0); 
				h_yields_trf->Fill(reg, "VRGtt1LII4mT3b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LI2mTb2b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LII2mTb2b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LI4mTb2b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LII4mTb2b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LI2mTb3b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LII2mTb3b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LI4mTb3b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LII4mTb3b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LI2mT4b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LII2mT4b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LIII22b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LIII42b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LIII23b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LIII43b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LIII24b", 0.0);
				h_yields_trf->Fill(reg, "VRGtt1LIII44b", 0.0);
			}

			if(!isTRF)
			{
				//std::cout << "not TRF" << std::endl;

				if(all) h_yields->Fill(reg, "All", weight_temp);
				if(isPreselect) h_yields->Fill(reg, "Presel", weight_temp);
				if(isPreselect_Gbb) h_yields->Fill(reg, "PreGbb", weight_temp);
				if(isPreselect_Gtt_0l) h_yields->Fill(reg, "PreGtt0l", weight_temp);
				if(isPreselect_Gtt_1l) h_yields->Fill(reg, "PreGtt1l", weight_temp);

				if(isGbbSRA2) h_yields->Fill(reg, "GbbSRA2", weight_temp);
				if(isGbbSRB2) h_yields->Fill(reg, "GbbSRB2", weight_temp);
				if(isGbbSRC2) h_yields->Fill(reg, "GbbSRC2", weight_temp);
				if(isGbbSRA4) h_yields->Fill(reg, "GbbSRA4", weight_temp);
				if(isGbbSRB4) h_yields->Fill(reg, "GbbSRB4", weight_temp);

				if(isGtt1LSRA2) h_yields->Fill(reg, "Gtt1LSRA2", weight_temp);
				if(isGtt1LSRB2) h_yields->Fill(reg, "Gtt1LSRB2", weight_temp);
				if(isGtt1LSRC2) h_yields->Fill(reg, "Gtt1LSRC2", weight_temp);
				if(isGtt1LSRA4) h_yields->Fill(reg, "Gtt1LSRA4", weight_temp);
				if(isGtt1LSRB4) h_yields->Fill(reg, "Gtt1LSRB4", weight_temp);
				if(isGtt1LSRC4) h_yields->Fill(reg, "Gtt1LSRC4", weight_temp);

				if(isGtt0LSRA) h_yields->Fill(reg, "Gtt0LSRA", weight_temp);
				if(isGtt0LSRB) h_yields->Fill(reg, "Gtt0LSRB", weight_temp);
				if(isGtt0LSRC) h_yields->Fill(reg, "Gtt0LSRC", weight_temp);
				if(isGtt0LSRD) h_yields->Fill(reg, "Gtt0LSRD", weight_temp);

				if(isGbbCRA2) h_yields->Fill(reg, "GbbCRA2", weight_temp);
				if(isGbbCRB2) h_yields->Fill(reg, "GbbCRB2", weight_temp);
				if(isGbbCRC2) h_yields->Fill(reg, "GbbCRC2", weight_temp);
				if(isGbbCRA4) h_yields->Fill(reg, "GbbCRA4", weight_temp);
				if(isGbbCRB4) h_yields->Fill(reg, "GbbCRB4", weight_temp);

				if(isGtt1LCRA2) h_yields->Fill(reg, "Gtt1LCRA2", weight_temp);
				if(isGtt1LCRB2) h_yields->Fill(reg, "Gtt1LCRB2", weight_temp);
				if(isGtt1LCRC2) h_yields->Fill(reg, "Gtt1LCRC2", weight_temp);
				if(isGtt1LCRA4) h_yields->Fill(reg, "Gtt1LCRA4", weight_temp);
				if(isGtt1LCRB4) h_yields->Fill(reg, "Gtt1LCRB4", weight_temp);
				if(isGtt1LCRC4) h_yields->Fill(reg, "Gtt1LCRC4", weight_temp);

				if(isGtt0LCRA) h_yields->Fill(reg, "Gtt0LCRA", weight_temp);
				if(isGtt0LCRB) h_yields->Fill(reg, "Gtt0LCRB", weight_temp);
				if(isGtt0LCRC) h_yields->Fill(reg, "Gtt0LCRC", weight_temp);
				if(isGtt0LCRD) h_yields->Fill(reg, "Gtt0LCRD", weight_temp);

				if(isGbbVRI2) h_yields->Fill(reg, "GbbVRI2", weight_temp);
				if(isGbbVRII2) h_yields->Fill(reg, "GbbVRII2", weight_temp);
				if(isGbbVRIII2) h_yields->Fill(reg, "GbbVRIII2", weight_temp);
				if(isGbbVRI4) h_yields->Fill(reg, "GbbVRI4", weight_temp);
				if(isGbbVRII4) h_yields->Fill(reg, "GbbVRII4", weight_temp);
				if(isVR1LGtt0LI) h_yields->Fill(reg, "VR1LGtt0LI", weight_temp);
				if(isVR1LGtt0LII) h_yields->Fill(reg, "VR1LGtt0LII", weight_temp);
				if(isVR1LGtt0LIII) h_yields->Fill(reg, "VR1LGtt0LIII", weight_temp);
				if(isVR1LGtt0LIV) h_yields->Fill(reg, "VR1LGtt0LIV", weight_temp);
				if(isVR0LGtt0LI) h_yields->Fill(reg, "VR0LGtt0LI", weight_temp);
				if(isVR0LGtt0LII) h_yields->Fill(reg, "VR0LGtt0LII", weight_temp);
				if(isVR0LGtt0LIII) h_yields->Fill(reg, "VR0LGtt0LIII", weight_temp);
				if(isVR0LGtt0LIV) h_yields->Fill(reg, "VR0LGtt0LIV", weight_temp);
				if(isVRGtt1LI2mT2b) h_yields->Fill(reg, "VRGtt1LI2mT2b", weight_temp);
				if(isVRGtt1LII2mT2b) h_yields->Fill(reg, "VRGtt1LII2mT2b", weight_temp);
				if(isVRGtt1LI4mT2b) h_yields->Fill(reg, "VRGtt1LI4mT2b", weight_temp);
				if(isVRGtt1LII4mT2b) h_yields->Fill(reg, "VRGtt1LII4mT2b", weight_temp);
				if(isVRGtt1LI2mT3b) h_yields->Fill(reg, "VRGtt1LI2mT3b", weight_temp);
				if(isVRGtt1LII2mT3b) h_yields->Fill(reg, "VRGtt1LII2mT3b", weight_temp);
				if(isVRGtt1LI4mT3b) h_yields->Fill(reg, "VRGtt1LI4mT3b", weight_temp); 
				if(isVRGtt1LII4mT3b) h_yields->Fill(reg, "VRGtt1LII4mT3b", weight_temp);
				if(isVRGtt1LI2mTb2b) h_yields->Fill(reg, "VRGtt1LI2mTb2b", weight_temp);
				if(isVRGtt1LII2mTb2b) h_yields->Fill(reg, "VRGtt1LII2mTb2b", weight_temp);
				if(isVRGtt1LI4mTb2b) h_yields->Fill(reg, "VRGtt1LI4mTb2b", weight_temp);
				if(isVRGtt1LII4mTb2b) h_yields->Fill(reg, "VRGtt1LII4mTb2b", weight_temp);
				if(isVRGtt1LI2mTb3b) h_yields->Fill(reg, "VRGtt1LI2mTb3b", weight_temp);
				if(isVRGtt1LII2mTb3b) h_yields->Fill(reg, "VRGtt1LII2mTb3b", weight_temp);
				if(isVRGtt1LI4mTb3b) h_yields->Fill(reg, "VRGtt1LI4mTb3b", weight_temp);
				if(isVRGtt1LII4mTb3b) h_yields->Fill(reg, "VRGtt1LII4mTb3b", weight_temp);
				if(isVRGtt1LI2mT4b) h_yields->Fill(reg, "VRGtt1LI2mT4b", weight_temp);
				if(isVRGtt1LII2mT4b) h_yields->Fill(reg, "VRGtt1LII2mT4b", weight_temp);
				if(isVRGtt1LIII22b) h_yields->Fill(reg, "VRGtt1LIII22b", weight_temp);
				if(isVRGtt1LIII42b) h_yields->Fill(reg, "VRGtt1LIII42b", weight_temp);
				if(isVRGtt1LIII23b) h_yields->Fill(reg, "VRGtt1LIII23b", weight_temp);
				if(isVRGtt1LIII43b) h_yields->Fill(reg, "VRGtt1LIII43b", weight_temp);
				if(isVRGtt1LIII24b) h_yields->Fill(reg, "VRGtt1LIII24b", weight_temp);
				if(isVRGtt1LIII44b) h_yields->Fill(reg, "VRGtt1LIII44b", weight_temp);
			}
			else if(isTRF)
			{
				//std::cout << "is TRF\tTRF_wgt is " << TRF_wgt << std::endl;
				weight_temp*=TRF_wgt;

				if(all) h_yields_trf->Fill(reg, "All", weight_temp);
				if(isPreselect) h_yields_trf->Fill(reg, "Presel", weight_temp);
				if(isPreselect_Gbb) h_yields_trf->Fill(reg, "PreGbb", weight_temp);
				if(isPreselect_Gtt_0l) h_yields_trf->Fill(reg, "PreGtt0l", weight_temp);
				if(isPreselect_Gtt_1l) h_yields_trf->Fill(reg, "PreGtt1l", weight_temp);

				if(isGbbSRA2) h_yields_trf->Fill(reg, "GbbSRA2", weight_temp);
				if(isGbbSRB2) h_yields_trf->Fill(reg, "GbbSRB2", weight_temp);
				if(isGbbSRC2) h_yields_trf->Fill(reg, "GbbSRC2", weight_temp);
				if(isGbbSRA4) h_yields_trf->Fill(reg, "GbbSRA4", weight_temp);
				if(isGbbSRB4) h_yields_trf->Fill(reg, "GbbSRB4", weight_temp);

				if(isGtt1LSRA2) h_yields_trf->Fill(reg, "Gtt1LSRA2", weight_temp);
				if(isGtt1LSRB2) h_yields_trf->Fill(reg, "Gtt1LSRB2", weight_temp);
				if(isGtt1LSRC2) h_yields_trf->Fill(reg, "Gtt1LSRC2", weight_temp);
				if(isGtt1LSRA4) h_yields_trf->Fill(reg, "Gtt1LSRA4", weight_temp);
				if(isGtt1LSRB4) h_yields_trf->Fill(reg, "Gtt1LSRB4", weight_temp);
				if(isGtt1LSRC4) h_yields_trf->Fill(reg, "Gtt1LSRC4", weight_temp);
				if(isGtt0LSRA) h_yields_trf->Fill(reg, "Gtt0LSRA", weight_temp);
				if(isGtt0LSRB) h_yields_trf->Fill(reg, "Gtt0LSRB", weight_temp);
				if(isGtt0LSRC) h_yields_trf->Fill(reg, "Gtt0LSRC", weight_temp);
				if(isGtt0LSRD) h_yields_trf->Fill(reg, "Gtt0LSRD", weight_temp);

				if(isGbbCRA2) h_yields_trf->Fill(reg, "GbbCRA2", weight_temp);
				if(isGbbCRB2) h_yields_trf->Fill(reg, "GbbCRB2", weight_temp);
				if(isGbbCRC2) h_yields_trf->Fill(reg, "GbbCRC2", weight_temp);
				if(isGbbCRA4) h_yields_trf->Fill(reg, "GbbCRA4", weight_temp);
				if(isGbbCRB4) h_yields_trf->Fill(reg, "GbbCRB4", weight_temp);

				if(isGtt1LCRA2) h_yields_trf->Fill(reg, "Gtt1LCRA2", weight_temp);
				if(isGtt1LCRB2) h_yields_trf->Fill(reg, "Gtt1LCRB2", weight_temp);
				if(isGtt1LCRC2) h_yields_trf->Fill(reg, "Gtt1LCRC2", weight_temp);
				if(isGtt1LCRA4) h_yields_trf->Fill(reg, "Gtt1LCRA4", weight_temp);
				if(isGtt1LCRB4) h_yields_trf->Fill(reg, "Gtt1LCRB4", weight_temp);
				if(isGtt1LCRC4) h_yields_trf->Fill(reg, "Gtt1LCRC4", weight_temp);

				if(isGtt0LCRA) h_yields_trf->Fill(reg, "Gtt0LCRA", weight_temp);
				if(isGtt0LCRB) h_yields_trf->Fill(reg, "Gtt0LCRB", weight_temp);
				if(isGtt0LCRC) h_yields_trf->Fill(reg, "Gtt0LCRC", weight_temp);
				if(isGtt0LCRD) h_yields_trf->Fill(reg, "Gtt0LCRD", weight_temp);

				if(isGbbVRI2) h_yields_trf->Fill(reg, "GbbVRI2", weight_temp);
				if(isGbbVRII2) h_yields_trf->Fill(reg, "GbbVRII2", weight_temp);
				if(isGbbVRIII2) h_yields_trf->Fill(reg, "GbbVRIII2", weight_temp);
				if(isGbbVRI4) h_yields_trf->Fill(reg, "GbbVRI4", weight_temp);
				if(isGbbVRII4) h_yields_trf->Fill(reg, "GbbVRII4", weight_temp);
				if(isVR1LGtt0LI) h_yields_trf->Fill(reg, "VR1LGtt0LI", weight_temp);
				if(isVR1LGtt0LII) h_yields_trf->Fill(reg, "VR1LGtt0LII", weight_temp);
				if(isVR1LGtt0LIII) h_yields_trf->Fill(reg, "VR1LGtt0LIII", weight_temp);
				if(isVR1LGtt0LIV) h_yields_trf->Fill(reg, "VR1LGtt0LIV", weight_temp);
				if(isVR0LGtt0LI) h_yields_trf->Fill(reg, "VR0LGtt0LI", weight_temp);
				if(isVR0LGtt0LII) h_yields_trf->Fill(reg, "VR0LGtt0LII", weight_temp);
				if(isVR0LGtt0LIII) h_yields_trf->Fill(reg, "VR0LGtt0LIII", weight_temp);
				if(isVR0LGtt0LIV) h_yields_trf->Fill(reg, "VR0LGtt0LIV", weight_temp);
				if(isVRGtt1LI2mT2b) h_yields_trf->Fill(reg, "VRGtt1LI2mT2b", weight_temp);
				if(isVRGtt1LII2mT2b) h_yields_trf->Fill(reg, "VRGtt1LII2mT2b", weight_temp);
				if(isVRGtt1LI4mT2b) h_yields_trf->Fill(reg, "VRGtt1LI4mT2b", weight_temp);
				if(isVRGtt1LII4mT2b) h_yields_trf->Fill(reg, "VRGtt1LII4mT2b", weight_temp);
				if(isVRGtt1LI2mT3b) h_yields_trf->Fill(reg, "VRGtt1LI2mT3b", weight_temp);
				if(isVRGtt1LII2mT3b) h_yields_trf->Fill(reg, "VRGtt1LII2mT3b", weight_temp);
				if(isVRGtt1LI4mT3b) h_yields_trf->Fill(reg, "VRGtt1LI4mT3b", weight_temp); 
				if(isVRGtt1LII4mT3b) h_yields_trf->Fill(reg, "VRGtt1LII4mT3b", weight_temp);
				if(isVRGtt1LI2mTb2b) h_yields_trf->Fill(reg, "VRGtt1LI2mTb2b", weight_temp);
				if(isVRGtt1LII2mTb2b) h_yields_trf->Fill(reg, "VRGtt1LII2mTb2b", weight_temp);
				if(isVRGtt1LI4mTb2b) h_yields_trf->Fill(reg, "VRGtt1LI4mTb2b", weight_temp);
				if(isVRGtt1LII4mTb2b) h_yields_trf->Fill(reg, "VRGtt1LII4mTb2b", weight_temp);
				if(isVRGtt1LI2mTb3b) h_yields_trf->Fill(reg, "VRGtt1LI2mTb3b", weight_temp);
				if(isVRGtt1LII2mTb3b) h_yields_trf->Fill(reg, "VRGtt1LII2mTb3b", weight_temp);
				if(isVRGtt1LI4mTb3b) h_yields_trf->Fill(reg, "VRGtt1LI4mTb3b", weight_temp);
				if(isVRGtt1LII4mTb3b) h_yields_trf->Fill(reg, "VRGtt1LII4mTb3b", weight_temp);
				if(isVRGtt1LI2mT4b) h_yields_trf->Fill(reg, "VRGtt1LI2mT4b", weight_temp);
				if(isVRGtt1LII2mT4b) h_yields_trf->Fill(reg, "VRGtt1LII2mT4b", weight_temp);
				if(isVRGtt1LIII22b) h_yields_trf->Fill(reg, "VRGtt1LIII22b", weight_temp);
				if(isVRGtt1LIII42b) h_yields_trf->Fill(reg, "VRGtt1LIII42b", weight_temp);
				if(isVRGtt1LIII23b) h_yields_trf->Fill(reg, "VRGtt1LIII23b", weight_temp);
				if(isVRGtt1LIII43b) h_yields_trf->Fill(reg, "VRGtt1LIII43b", weight_temp);
				if(isVRGtt1LIII24b) h_yields_trf->Fill(reg, "VRGtt1LIII24b", weight_temp);
				if(isVRGtt1LIII44b) h_yields_trf->Fill(reg, "VRGtt1LIII44b", weight_temp);
			}

			// if(!isTRF)
			// {
			// 	//std::cout << "not TRF" << std::endl;

			// 	if(all) h_yields->Fill(reg, "All", 1.0);
			// 	if(isPreselect) h_yields->Fill(reg, "Presel", 1.0);
			// 	if(isPreselect_Gbb) h_yields->Fill(reg, "PreGbb", 1.0);
			// 	if(isPreselect_Gtt_0l) h_yields->Fill(reg, "PreGtt0l", 1.0);
			// 	if(isPreselect_Gtt_1l) h_yields->Fill(reg, "PreGtt1l", 1.0);

			// 	if(isGbbSRA2) h_yields->Fill(reg, "GbbSRA2", 1.0);
			// 	if(isGbbSRB2) h_yields->Fill(reg, "GbbSRB2", 1.0);
			// 	if(isGbbSRC2) h_yields->Fill(reg, "GbbSRC2", 1.0);
			// 	if(isGbbSRA4) h_yields->Fill(reg, "GbbSRA4", 1.0);
			// 	if(isGbbSRB4) h_yields->Fill(reg, "GbbSRB4", 1.0);

			// 	if(isGtt1LSRA2) h_yields->Fill(reg, "Gtt1LSRA2", 1.0);
			// 	if(isGtt1LSRB2) h_yields->Fill(reg, "Gtt1LSRB2", 1.0);
			// 	if(isGtt1LSRC2) h_yields->Fill(reg, "Gtt1LSRC2", 1.0);
			// 	if(isGtt1LSRA4) h_yields->Fill(reg, "Gtt1LSRA4", 1.0);
			// 	if(isGtt1LSRB4) h_yields->Fill(reg, "Gtt1LSRB4", 1.0);
			// 	if(isGtt1LSRC4) h_yields->Fill(reg, "Gtt1LSRC4", 1.0);

			// 	if(isGtt0LSRA) h_yields->Fill(reg, "Gtt0LSRA", 1.0);
			// 	if(isGtt0LSRB) h_yields->Fill(reg, "Gtt0LSRB", 1.0);
			// 	if(isGtt0LSRC) h_yields->Fill(reg, "Gtt0LSRC", 1.0);
			// 	if(isGtt0LSRD) h_yields->Fill(reg, "Gtt0LSRD", 1.0);

			// 	if(isGbbCRA2) h_yields->Fill(reg, "GbbCRA2", 1.0);
			// 	if(isGbbCRB2) h_yields->Fill(reg, "GbbCRB2", 1.0);
			// 	if(isGbbCRC2) h_yields->Fill(reg, "GbbCRC2", 1.0);
			// 	if(isGbbCRA4) h_yields->Fill(reg, "GbbCRA4", 1.0);
			// 	if(isGbbCRB4) h_yields->Fill(reg, "GbbCRB4", 1.0);

			// 	if(isGtt1LCRA2) h_yields->Fill(reg, "Gtt1LCRA2", 1.0);
			// 	if(isGtt1LCRB2) h_yields->Fill(reg, "Gtt1LCRB2", 1.0);
			// 	if(isGtt1LCRC2) h_yields->Fill(reg, "Gtt1LCRC2", 1.0);
			// 	if(isGtt1LCRA4) h_yields->Fill(reg, "Gtt1LCRA4", 1.0);
			// 	if(isGtt1LCRB4) h_yields->Fill(reg, "Gtt1LCRB4", 1.0);
			// 	if(isGtt1LCRC4) h_yields->Fill(reg, "Gtt1LCRC4", 1.0);

			// 	if(isGtt0LCRA) h_yields->Fill(reg, "Gtt0LCRA", 1.0);
			// 	if(isGtt0LCRB) h_yields->Fill(reg, "Gtt0LCRB", 1.0);
			// 	if(isGtt0LCRC) h_yields->Fill(reg, "Gtt0LCRC", 1.0);
			// 	if(isGtt0LCRD) h_yields->Fill(reg, "Gtt0LCRD", 1.0);

			// 	if(isGbbVRI2) h_yields->Fill(reg, "GbbVRI2", 1.0);
			// 	if(isGbbVRII2) h_yields->Fill(reg, "GbbVRII2", 1.0);
			// 	if(isGbbVRIII2) h_yields->Fill(reg, "GbbVRIII2", 1.0);
			// 	if(isGbbVRI4) h_yields->Fill(reg, "GbbVRI4", 1.0);
			// 	if(isGbbVRII4) h_yields->Fill(reg, "GbbVRII4", 1.0);
			// 	if(isVR1LGtt0LI) h_yields->Fill(reg, "VR1LGtt0LI", 1.0);
			// 	if(isVR1LGtt0LII) h_yields->Fill(reg, "VR1LGtt0LII", 1.0);
			// 	if(isVR1LGtt0LIII) h_yields->Fill(reg, "VR1LGtt0LIII", 1.0);
			// 	if(isVR1LGtt0LIV) h_yields->Fill(reg, "VR1LGtt0LIV", 1.0);
			// 	if(isVR0LGtt0LI) h_yields->Fill(reg, "VR0LGtt0LI", 1.0);
			// 	if(isVR0LGtt0LII) h_yields->Fill(reg, "VR0LGtt0LII", 1.0);
			// 	if(isVR0LGtt0LIII) h_yields->Fill(reg, "VR0LGtt0LIII", 1.0);
			// 	if(isVR0LGtt0LIV) h_yields->Fill(reg, "VR0LGtt0LIV", 1.0);
			// 	if(isVRGtt1LI2mT2b) h_yields->Fill(reg, "VRGtt1LI2mT2b", 1.0);
			// 	if(isVRGtt1LII2mT2b) h_yields->Fill(reg, "VRGtt1LII2mT2b", 1.0);
			// 	if(isVRGtt1LI4mT2b) h_yields->Fill(reg, "VRGtt1LI4mT2b", 1.0);
			// 	if(isVRGtt1LII4mT2b) h_yields->Fill(reg, "VRGtt1LII4mT2b", 1.0);
			// 	if(isVRGtt1LI2mT3b) h_yields->Fill(reg, "VRGtt1LI2mT3b", 1.0);
			// 	if(isVRGtt1LII2mT3b) h_yields->Fill(reg, "VRGtt1LII2mT3b", 1.0);
			// 	if(isVRGtt1LI4mT3b) h_yields->Fill(reg, "VRGtt1LI4mT3b", 1.0); 
			// 	if(isVRGtt1LII4mT3b) h_yields->Fill(reg, "VRGtt1LII4mT3b", 1.0);
			// 	if(isVRGtt1LI2mTb2b) h_yields->Fill(reg, "VRGtt1LI2mTb2b", 1.0);
			// 	if(isVRGtt1LII2mTb2b) h_yields->Fill(reg, "VRGtt1LII2mTb2b", 1.0);
			// 	if(isVRGtt1LI4mTb2b) h_yields->Fill(reg, "VRGtt1LI4mTb2b", 1.0);
			// 	if(isVRGtt1LII4mTb2b) h_yields->Fill(reg, "VRGtt1LII4mTb2b", 1.0);
			// 	if(isVRGtt1LI2mTb3b) h_yields->Fill(reg, "VRGtt1LI2mTb3b", 1.0);
			// 	if(isVRGtt1LII2mTb3b) h_yields->Fill(reg, "VRGtt1LII2mTb3b", 1.0);
			// 	if(isVRGtt1LI4mTb3b) h_yields->Fill(reg, "VRGtt1LI4mTb3b", 1.0);
			// 	if(isVRGtt1LII4mTb3b) h_yields->Fill(reg, "VRGtt1LII4mTb3b", 1.0);
			// 	if(isVRGtt1LI2mT4b) h_yields->Fill(reg, "VRGtt1LI2mT4b", 1.0);
			// 	if(isVRGtt1LII2mT4b) h_yields->Fill(reg, "VRGtt1LII2mT4b", 1.0);
			// 	if(isVRGtt1LIII22b) h_yields->Fill(reg, "VRGtt1LIII22b", 1.0);
			// 	if(isVRGtt1LIII42b) h_yields->Fill(reg, "VRGtt1LIII42b", 1.0);
			// 	if(isVRGtt1LIII23b) h_yields->Fill(reg, "VRGtt1LIII23b", 1.0);
			// 	if(isVRGtt1LIII43b) h_yields->Fill(reg, "VRGtt1LIII43b", 1.0);
			// 	if(isVRGtt1LIII24b) h_yields->Fill(reg, "VRGtt1LIII24b", 1.0);
			// 	if(isVRGtt1LIII44b) h_yields->Fill(reg, "VRGtt1LIII44b", 1.0);
			// }
			// else if(isTRF)
			// {
			// 	//std::cout << "is TRF\tTRF_wgt is " << TRF_wgt << std::endl;
			// 	weight_temp*=TRF_wgt;

			// 	if(all) h_yields_trf->Fill(reg, "All", 1.0/*TRF_wgt*/);
			// 	if(isPreselect) h_yields_trf->Fill(reg, "Presel", 1.0/*TRF_wgt*/);
			// 	if(isPreselect_Gbb) h_yields_trf->Fill(reg, "PreGbb", 1.0/*TRF_wgt*/);
			// 	if(isPreselect_Gtt_0l) h_yields_trf->Fill(reg, "PreGtt0l", 1.0/*TRF_wgt*/);
			// 	if(isPreselect_Gtt_1l) h_yields_trf->Fill(reg, "PreGtt1l", 1.0/*TRF_wgt*/);

			// 	if(isGbbSRA2) h_yields_trf->Fill(reg, "GbbSRA2", 1.0/*TRF_wgt*/);
			// 	if(isGbbSRB2) h_yields_trf->Fill(reg, "GbbSRB2", 1.0/*TRF_wgt*/);
			// 	if(isGbbSRC2) h_yields_trf->Fill(reg, "GbbSRC2", 1.0/*TRF_wgt*/);
			// 	if(isGbbSRA4) h_yields_trf->Fill(reg, "GbbSRA4", 1.0/*TRF_wgt*/);
			// 	if(isGbbSRB4) h_yields_trf->Fill(reg, "GbbSRB4", 1.0/*TRF_wgt*/);

			// 	if(isGtt1LSRA2) h_yields_trf->Fill(reg, "Gtt1LSRA2", 1.0/*TRF_wgt*/);
			// 	if(isGtt1LSRB2) h_yields_trf->Fill(reg, "Gtt1LSRB2", 1.0/*TRF_wgt*/);
			// 	if(isGtt1LSRC2) h_yields_trf->Fill(reg, "Gtt1LSRC2", 1.0/*TRF_wgt*/);
			// 	if(isGtt1LSRA4) h_yields_trf->Fill(reg, "Gtt1LSRA4", 1.0/*TRF_wgt*/);
			// 	if(isGtt1LSRB4) h_yields_trf->Fill(reg, "Gtt1LSRB4", 1.0/*TRF_wgt*/);
			// 	if(isGtt1LSRC4) h_yields_trf->Fill(reg, "Gtt1LSRC4", 1.0/*TRF_wgt*/);

			// 	if(isGtt0LSRA) h_yields_trf->Fill(reg, "Gtt0LSRA", 1.0/*TRF_wgt*/);
			// 	if(isGtt0LSRB) h_yields_trf->Fill(reg, "Gtt0LSRB", 1.0/*TRF_wgt*/);
			// 	if(isGtt0LSRC) h_yields_trf->Fill(reg, "Gtt0LSRC", 1.0/*TRF_wgt*/);
			// 	if(isGtt0LSRD) h_yields_trf->Fill(reg, "Gtt0LSRD", 1.0/*TRF_wgt*/);

			// 	if(isGbbCRA2) h_yields_trf->Fill(reg, "GbbCRA2", 1.0/*TRF_wgt*/);
			// 	if(isGbbCRB2) h_yields_trf->Fill(reg, "GbbCRB2", 1.0/*TRF_wgt*/);
			// 	if(isGbbCRC2) h_yields_trf->Fill(reg, "GbbCRC2", 1.0/*TRF_wgt*/);
			// 	if(isGbbCRA4) h_yields_trf->Fill(reg, "GbbCRA4", 1.0/*TRF_wgt*/);
			// 	if(isGbbCRB4) h_yields_trf->Fill(reg, "GbbCRB4", 1.0/*TRF_wgt*/);

			// 	if(isGtt1LCRA2) h_yields_trf->Fill(reg, "Gtt1LCRA2", 1.0/*TRF_wgt*/);
			// 	if(isGtt1LCRB2) h_yields_trf->Fill(reg, "Gtt1LCRB2", 1.0/*TRF_wgt*/);
			// 	if(isGtt1LCRC2) h_yields_trf->Fill(reg, "Gtt1LCRC2", 1.0/*TRF_wgt*/);
			// 	if(isGtt1LCRA4) h_yields_trf->Fill(reg, "Gtt1LCRA4", 1.0/*TRF_wgt*/);
			// 	if(isGtt1LCRB4) h_yields_trf->Fill(reg, "Gtt1LCRB4", 1.0/*TRF_wgt*/);
			// 	if(isGtt1LCRC4) h_yields_trf->Fill(reg, "Gtt1LCRC4", 1.0/*TRF_wgt*/);

			// 	if(isGtt0LCRA) h_yields_trf->Fill(reg, "Gtt0LCRA", 1.0/*TRF_wgt*/);
			// 	if(isGtt0LCRB) h_yields_trf->Fill(reg, "Gtt0LCRB", 1.0/*TRF_wgt*/);
			// 	if(isGtt0LCRC) h_yields_trf->Fill(reg, "Gtt0LCRC", 1.0/*TRF_wgt*/);
			// 	if(isGtt0LCRD) h_yields_trf->Fill(reg, "Gtt0LCRD", 1.0/*TRF_wgt*/);

			// 	if(isGbbVRI2) h_yields_trf->Fill(reg, "GbbVRI2", 1.0/*TRF_wgt*/);
			// 	if(isGbbVRII2) h_yields_trf->Fill(reg, "GbbVRII2", 1.0/*TRF_wgt*/);
			// 	if(isGbbVRIII2) h_yields_trf->Fill(reg, "GbbVRIII2", 1.0/*TRF_wgt*/);
			// 	if(isGbbVRI4) h_yields_trf->Fill(reg, "GbbVRI4", 1.0/*TRF_wgt*/);
			// 	if(isGbbVRII4) h_yields_trf->Fill(reg, "GbbVRII4", 1.0/*TRF_wgt*/);
			// 	if(isVR1LGtt0LI) h_yields_trf->Fill(reg, "VR1LGtt0LI", 1.0/*TRF_wgt*/);
			// 	if(isVR1LGtt0LII) h_yields_trf->Fill(reg, "VR1LGtt0LII", 1.0/*TRF_wgt*/);
			// 	if(isVR1LGtt0LIII) h_yields_trf->Fill(reg, "VR1LGtt0LIII", 1.0/*TRF_wgt*/);
			// 	if(isVR1LGtt0LIV) h_yields_trf->Fill(reg, "VR1LGtt0LIV", 1.0/*TRF_wgt*/);
			// 	if(isVR0LGtt0LI) h_yields_trf->Fill(reg, "VR0LGtt0LI", 1.0/*TRF_wgt*/);
			// 	if(isVR0LGtt0LII) h_yields_trf->Fill(reg, "VR0LGtt0LII", 1.0/*TRF_wgt*/);
			// 	if(isVR0LGtt0LIII) h_yields_trf->Fill(reg, "VR0LGtt0LIII", 1.0/*TRF_wgt*/);
			// 	if(isVR0LGtt0LIV) h_yields_trf->Fill(reg, "VR0LGtt0LIV", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LI2mT2b) h_yields_trf->Fill(reg, "VRGtt1LI2mT2b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LII2mT2b) h_yields_trf->Fill(reg, "VRGtt1LII2mT2b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LI4mT2b) h_yields_trf->Fill(reg, "VRGtt1LI4mT2b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LII4mT2b) h_yields_trf->Fill(reg, "VRGtt1LII4mT2b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LI2mT3b) h_yields_trf->Fill(reg, "VRGtt1LI2mT3b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LII2mT3b) h_yields_trf->Fill(reg, "VRGtt1LII2mT3b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LI4mT3b) h_yields_trf->Fill(reg, "VRGtt1LI4mT3b", 1.0/*TRF_wgt*/); 
			// 	if(isVRGtt1LII4mT3b) h_yields_trf->Fill(reg, "VRGtt1LII4mT3b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LI2mTb2b) h_yields_trf->Fill(reg, "VRGtt1LI2mTb2b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LII2mTb2b) h_yields_trf->Fill(reg, "VRGtt1LII2mTb2b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LI4mTb2b) h_yields_trf->Fill(reg, "VRGtt1LI4mTb2b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LII4mTb2b) h_yields_trf->Fill(reg, "VRGtt1LII4mTb2b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LI2mTb3b) h_yields_trf->Fill(reg, "VRGtt1LI2mTb3b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LII2mTb3b) h_yields_trf->Fill(reg, "VRGtt1LII2mTb3b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LI4mTb3b) h_yields_trf->Fill(reg, "VRGtt1LI4mTb3b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LII4mTb3b) h_yields_trf->Fill(reg, "VRGtt1LII4mTb3b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LI2mT4b) h_yields_trf->Fill(reg, "VRGtt1LI2mT4b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LII2mT4b) h_yields_trf->Fill(reg, "VRGtt1LII2mT4b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LIII22b) h_yields_trf->Fill(reg, "VRGtt1LIII22b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LIII42b) h_yields_trf->Fill(reg, "VRGtt1LIII42b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LIII23b) h_yields_trf->Fill(reg, "VRGtt1LIII23b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LIII43b) h_yields_trf->Fill(reg, "VRGtt1LIII43b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LIII24b) h_yields_trf->Fill(reg, "VRGtt1LIII24b", 1.0/*TRF_wgt*/);
			// 	if(isVRGtt1LIII44b) h_yields_trf->Fill(reg, "VRGtt1LIII44b", 1.0/*TRF_wgt*/);
			// }		

		}
	}

	std::cout << "Done processing events." << std::endl;

	TFile* out; out = new TFile("truthYields.root", "RECREATE");
	h_yields->Write();
	h_yields_trf->Write();
	out->Close();

	std::cout << "Output written." << std::endl;

	return;
}

void theTruth(void)
{
	std::vector<TString> truth;

	truth.push_back("You can't handle the truth.");
	truth.push_back("The truth is out there.");
	truth.push_back("The truth will set you free.");
	truth.push_back("All truths are easy to understand once they are discovered; the point is to discover them.");
	truth.push_back("Rather than love, than money, than fame, give me truth.");
	truth.push_back("If you tell the truth, you don't have to remember anything.");
	truth.push_back("Truth will ultimately prevail where there is pains to bring it to light.");
	truth.push_back("Perhaps the truth depends on a walk around the lake.");
	truth.push_back("Whatever satisfies the soul is truth.");
	truth.push_back("The truth is rarely pure and never simple.");
	truth.push_back("Once you eliminate the impossible, whatever remains, no matter how improbable, must be the truth.");
	truth.push_back("If you are out to describe the truth, leave elegance to the tailor.");
	truth.push_back("If you do not tell the truth about yourself you cannot tell it about other people.");
	truth.push_back("Truth is a tendency.");
	truth.push_back("Truth is so rare that it is delightful to tell it.");
	truth.push_back("Not being known doesn't stop the truth from being true.");
	truth.push_back("Everything you add to the truth subtracts from the truth.");
	truth.push_back("Truth is immortal; error is mortal.");
	truth.push_back("Time discovers truth.");
	truth.push_back("You never monkey with the truth.");

	TRandom* tr = new TRandom();
	int rand = tr->Integer(truth.size());

	std::cout << truth.at(rand) << std::endl;

	return;
}