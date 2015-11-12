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

void postTruth(void)
{
	std::cout << "The truth is out there." << std::endl;

	TString inDir = "/Users/mleblanc/susyGtt/20151101_truth/truthOut/";
	TString inDir2 = "/fetch/data-outTree/";

	// TFile* f_410000; f_410000 = new TFile(inDir+"410000"+inDir2+"410000.merge.root");
	// TFile* f_410001; f_410001 = new TFile(inDir+"410001"+inDir2+"410001.merge.root");
	// TFile* f_410002; f_410002 = new TFile(inDir+"410002"+inDir2+"410002.merge.root");
	// TFile* f_410003; f_410003 = new TFile(inDir+"410003"+inDir2+"410003.merge.root");
	// TFile* f_410004; f_410004 = new TFile(inDir+"410004"+inDir2+"410004.merge.root");
	// TFile* f_410006; f_410006 = new TFile(inDir+"410006"+inDir2+"410006.merge.root");
	TFile* f_407012; f_407012 = new TFile(inDir+"407012"+inDir2+"407012.merge.root");
	TFile* f_407032; f_407032 = new TFile(inDir+"407032"+inDir2+"407032.merge.root");
	TFile* f_407036; f_407036 = new TFile(inDir+"407036"+inDir2+"407036.merge.root");
	TFile* f_407040; f_407040 = new TFile(inDir+"407040"+inDir2+"407040.merge.root");
	TFile* f_407044; f_407044 = new TFile(inDir+"407044"+inDir2+"407044.merge.root");

	// TTree* t_410000; t_410000 = (TTree*)f_410000->Get("out_tree");
	// TTree* t_410001; t_410001 = (TTree*)f_410001->Get("out_tree");
	// TTree* t_410002; t_410002 = (TTree*)f_410002->Get("out_tree");
	// TTree* t_410003; t_410003 = (TTree*)f_410003->Get("out_tree");
	// TTree* t_410004; t_410004 = (TTree*)f_410004->Get("out_tree");
	// TTree* t_410006; t_410006 = (TTree*)f_410006->Get("out_tree");
	TTree* t_407012; t_407012 = (TTree*)f_407012->Get("out_tree");
	TTree* t_407032; t_407032 = (TTree*)f_407032->Get("out_tree");
	TTree* t_407036; t_407036 = (TTree*)f_407036->Get("out_tree");
	TTree* t_407040; t_407040 = (TTree*)f_407040->Get("out_tree");
	TTree* t_407044; t_407044 = (TTree*)f_407044->Get("out_tree");

	std::vector<pair<TTree*, Int_t>> v_trees;
	// v_trees.push_back(std::make_pair(t_410000,410000));
	// v_trees.push_back(std::make_pair(t_410001,410001));
	// v_trees.push_back(std::make_pair(t_410002,410002));
	// v_trees.push_back(std::make_pair(t_410003,410003));
	// v_trees.push_back(std::make_pair(t_410004,410004));
	// v_trees.push_back(std::make_pair(t_410006,410006));
	v_trees.push_back(std::make_pair(t_407012,407012));
	v_trees.push_back(std::make_pair(t_407032,407032));
	v_trees.push_back(std::make_pair(t_407036,407036));
	v_trees.push_back(std::make_pair(t_407040,407040));
	v_trees.push_back(std::make_pair(t_407044,407044));

	TH2D* h_yields; h_yields = new TH2D("yields","yields",5,1,6,36,1,37); // x=DSID, y=SR

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

        // if(reg=="410000") weight /= 20099000.0;
        // if(reg=="410001") weight /= 19995000.0;
        // if(reg=="410002") weight /= 20000000.0;
        // if(reg=="410003") weight /= 4910000.0;
        // if(reg=="410004") weight /= 9820000.0;
        // if(reg=="410006") weight /= 10000000.0;

        if(reg=="407012") weight /= 2.74497;
		if(reg=="407032") weight /= 2.95191;
        if(reg=="407036") weight /= 2.43458;
        if(reg=="407040") weight /= 3.7725e+06; 
        if(reg=="407044") weight /= 2.85515e+09; 

		weight*=1.e3; // pb to fb
		weight*=3.5; // 2015 lumi

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
		
		// Loop over the entries in each tree and do the thing.
		for(unsigned int i=0; i < v_trees.at(iTree).first->GetEntries(); i++)
		{
			v_trees.at(iTree).first->GetEntry(i);
			if(i%1000000==true) std::cout << "DSID: " << v_trees.at(iTree).second  << "\tEntry " 
										  << (i-1) << " / " << v_trees.at(iTree).first->GetEntries() << std::endl;

			Float_t weight_temp=-1.0; weight_temp=weight;
			weight_temp*=mc_weight;
						
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

			}

			if(all) h_yields->Fill(reg, "All", weight_temp);
			if(isPreselect) h_yields->Fill(reg, "Presel", weight_temp);
			if(isPreselect_Gbb) h_yields->Fill(reg, "PreGbb", weight_temp);
			if(isPreselect_Gtt_0l) h_yields->Fill(reg, "PreGtt0l", weight_temp);
			if(isPreselect_Gtt_1l) h_yields->Fill(reg, "PreGtt1l", weight_temp);

			//if(isGbbSRA1) h_yields->Fill(reg, "GbbSRA1", weight_temp);
			//if(isGbbSRB1) h_yields->Fill(reg, "GbbSRB1", weight_temp);
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
		}
	}

	std::cout << "Done processing events." << std::endl;

	TFile* out; out = new TFile("truthYields.root", "RECREATE");
	h_yields->Write();
	out->Close();

	std::cout << "Output written." << std::endl;

	return;
}
