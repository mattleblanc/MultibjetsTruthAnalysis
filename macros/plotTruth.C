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

void stampATLAS(const std::string &text, float x, float y);
void stampATLAS_ratio(const std::string &text, float x, float y);
void stampLumiText(float lumi, float x, float y, const std::string &text, float size);
void stampText(const std::string &text, float x, float y, float size);

void plotTruth(TString reg)
{
	std::cout << "plotTruth.C\tWe can handle this." << std::endl;
	std::cout << "Making plots for region:\t" << reg << std::endl;

	TString inDir = "/Users/mleblanc/susyGtt/20151101_truth/truthOut/";
	//TString inDir = "/Users/mleblanc/susyGtt/20151101_truth/testOut/";
	TString inDir2 = "/fetch/data-outTree/";

	//TFile* f_410000; f_410000 = new TFile(inDir+"mc15_13TeV:mc15_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.DAOD_TRUTH1.e3698_p2375.root");
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
	//v_trees.push_back(std::make_pair(t_410000,410000));
	//v_trees.push_back(std::make_pair(t_410001,410001));
	// v_trees.push_back(std::make_pair(t_410002,410002));
	// v_trees.push_back(std::make_pair(t_410003,410003));
	// v_trees.push_back(std::make_pair(t_410004,410004));
	// v_trees.push_back(std::make_pair(t_410006,410006));
	v_trees.push_back(std::make_pair(t_407012,407012));
	v_trees.push_back(std::make_pair(t_407032,407032));
	v_trees.push_back(std::make_pair(t_407036,407036));
	v_trees.push_back(std::make_pair(t_407040,407040));
	v_trees.push_back(std::make_pair(t_407044,407044));

	// Declare histograms ...
	std::vector<TH1F*> v_truth_met;
	std::vector<TH1F*> v_truth_Meff;
	std::vector<TH1F*> v_truth_Meff_4j;
	std::vector<TH1F*> v_truth_mT;
	std::vector<TH1F*> v_truth_mTb;

	for(unsigned int iHist=0; iHist<v_trees.size(); iHist++)
	{
		TString dsid;
		dsid.Form("%d", v_trees.at(iHist).second); 

		TH1F* tempHistMet; tempHistMet = new TH1F(dsid,dsid,100,0,2000);
		TH1F* tempHistMeff; tempHistMeff = new TH1F(dsid,dsid,100,0,2000);
		TH1F* tempHistMeff4j; tempHistMeff4j = new TH1F(dsid,dsid,100,0,2000);
		TH1F* tempHistMT; tempHistMT = new TH1F(dsid,dsid,200,0,2000);
		TH1F* tempHistMTb; tempHistMTb = new TH1F(dsid,dsid,200,0,2000);

		TH1F* tempHist; tempHist = new TH1F(dsid,dsid,100,0,2000);

		v_truth_met.push_back(tempHistMet);
		v_truth_Meff.push_back(tempHistMeff);		
		v_truth_Meff_4j.push_back(tempHistMeff4j);	
		v_truth_mT.push_back(tempHistMT);		
		v_truth_mTb.push_back(tempHistMTb);

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

        // if(dsid=="410000") weight /= 20099000.0;
        // if(dsid=="410001") weight /= 19995000.0;
        // if(dsid=="410002") weight /= 20000000.0;
        // if(dsid=="410003") weight /= 4910000.0;
        // if(dsid=="410004") weight /= 9820000.0;
        // if(dsid=="410006") weight /= 10000000.0;

        if(dsid=="407012") weight /= 2.74497;
		if(dsid=="407032") weight /= 2.95191;
        if(dsid=="407036") weight /= 2.43458;
        if(dsid=="407040") weight /= 3.7725e6; 
        if(dsid=="407044") weight /= 2.85515e9; 

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

		float temp_weight;

		// Loop over the entries in each tree and do the thing.
		for(unsigned int i=0; i < v_trees.at(iTree).first->GetEntries(); i++)
		{
			v_trees.at(iTree).first->GetEntry(i);

			temp_weight = weight;
			temp_weight *= mc_weight;

			if(i%1000000==true)
			{
				std::cout << "DSID: " << v_trees.at(iTree).second  << "\tEntry " 
										  << (i-1) << " / " << v_trees.at(iTree).first->GetEntries() << std::endl;
			}

			Bool_t fillPlots=false;
			if(reg=="all") fillPlots=true;
			if(reg=="Preselect_Gbb" && isPreselect_Gbb) fillPlots=true;
			if(reg=="Preselect_Gtt_0l" && isPreselect_Gtt_0l) fillPlots=true;
			if(reg=="Preselect_Gtt_1l" && isPreselect_Gtt_1l) fillPlots=true;

			if(reg=="GbbSRA2" && isGbbSRA2) fillPlots=true;
			if(reg=="GbbSRB2" && isGbbSRB2) fillPlots=true;
			if(reg=="GbbSRC2" && isGbbSRC2) fillPlots=true;
			if(reg=="GbbSRA4" && isGbbSRA4) fillPlots=true;
			if(reg=="GbbSRB4" && isGbbSRB4) fillPlots=true;

			if(reg=="Gtt1LSRA2" && isGtt1LSRA2) fillPlots=true;
			if(reg=="Gtt1LSRB2" && isGtt1LSRB2) fillPlots=true;
			if(reg=="Gtt1LSRC2" && isGtt1LSRC2) fillPlots=true;
			if(reg=="Gtt1LSRA4" && isGtt1LSRA4) fillPlots=true;
			if(reg=="Gtt1LSRB4" && isGtt1LSRB4) fillPlots=true;
			if(reg=="Gtt1LSRC4" && isGtt1LSRC4) fillPlots=true;

			if(reg=="Gtt0LSRA" && isGtt0LSRA) fillPlots=true;
			if(reg=="Gtt0LSRB" && isGtt0LSRB) fillPlots=true;
			if(reg=="Gtt0LSRC" && isGtt0LSRC) fillPlots=true;
			if(reg=="Gtt0LSRD" && isGtt0LSRD) fillPlots=true;

			if(reg=="GbbCRA2" && isGbbCRA2) fillPlots=true;
			if(reg=="GbbCRB2" && isGbbCRB2) fillPlots=true;
			if(reg=="GbbCRC2" && isGbbCRC2) fillPlots=true;
			if(reg=="GbbCRA4" && isGbbCRA4) fillPlots=true;
			if(reg=="GbbCRB4" && isGbbCRB4) fillPlots=true;

			if(reg=="Gtt1LCRA2" && isGtt1LCRA2) fillPlots=true;
			if(reg=="Gtt1LCRB2" && isGtt1LCRB2) fillPlots=true;
			if(reg=="Gtt1LCRC2" && isGtt1LCRC2) fillPlots=true;
			if(reg=="Gtt1LCRA4" && isGtt1LCRA4) fillPlots=true;
			if(reg=="Gtt1LCRB4" && isGtt1LCRB4) fillPlots=true;
			if(reg=="Gtt1LCRC4" && isGtt1LCRC4) fillPlots=true;

			if(reg=="Gtt0LCRA" && isGtt0LCRA) fillPlots=true;
			if(reg=="Gtt0LCRB" && isGtt0LCRB) fillPlots=true;
			if(reg=="Gtt0LCRC" && isGtt0LCRC) fillPlots=true;
			if(reg=="Gtt0LCRD" && isGtt0LCRD) fillPlots=true;



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
			}
		}
	}

	///////////////////////////////////////

	// Draw the plots, make 'em look nice.

	// Colours from the ATLAS palette:
	std::vector<TString> v_colours;
	v_colours.push_back("#0b80c3"); // blue
	v_colours.push_back("#36bdbd"); // teal
	v_colours.push_back("#ffad35"); // orange
	v_colours.push_back("#5dbe5d"); // green
	v_colours.push_back("#d351ff"); // pink
	v_colours.push_back("#5656d7"); // purple
	v_colours.push_back("#efda4e"); // yellow
	v_colours.push_back("#bcbc93"); // brown
	v_colours.push_back("#9a846d"); // worse brown
	v_colours.push_back("#7c7c7c"); // dark grey

	string extraText; extraText = "SUSY 0L Multi-b/t Search";

	TLegend* leg;
	leg = new TLegend(0.65,0.4,0.99,0.7);
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.04);

	TCanvas* c; c = new TCanvas("canvas");
	c->cd();
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);

	for(unsigned int iTree=0; iTree<v_trees.size(); iTree++)
	{
		TString dsid;
		dsid.Form("%d", v_trees.at(iTree).second); 

		std::cout << "DSID: " << dsid << "\tPLOTTING" << std::endl;

		Bool_t isFirst=false; isFirst = (iTree==0);
		Bool_t isLast=false; isLast = ((iTree==0 && v_trees.size()==1)||(iTree==v_trees.size()-1 && v_trees.size()>1));

		// missing transverse energy
		v_truth_met.at(iTree)->SetMaximum(v_truth_met.at(iTree)->GetMaximum()*10);
		v_truth_met.at(iTree)->GetXaxis()->SetRangeUser(0,1200);
		v_truth_met.at(iTree)->SetLineColor(TColor::GetColor(v_colours.at(iTree%v_trees.size())));
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
		if(isLast) c->SaveAs("plots/"+reg+"/truth_met.pdf");
	}

	leg->Clear();
	c->Clear();

	for(unsigned int iTree=0; iTree<v_trees.size(); iTree++)
	{
		TString dsid;
		dsid.Form("%d", v_trees.at(iTree).second); 

		std::cout << "DSID: " << dsid << "\tPLOTTING" << std::endl;

		Bool_t isFirst=false; isFirst = (iTree==0);
		Bool_t isLast=false; isLast = ((iTree==0 && v_trees.size()==1)||(iTree==v_trees.size()-1 && v_trees.size()>1));

		//effective mass
		v_truth_Meff.at(iTree)->SetMaximum(v_truth_Meff.at(iTree)->GetMaximum()*20);
		v_truth_Meff.at(iTree)->GetXaxis()->SetRangeUser(0,2000);
		v_truth_Meff.at(iTree)->SetLineColor(TColor::GetColor(v_colours.at(iTree%v_trees.size())));
		leg->AddEntry(v_truth_Meff.at(iTree),dsid,"l");
		v_truth_Meff.at(iTree)->GetXaxis()->SetTitle("Effective Mass [GeV]");
		v_truth_Meff.at(iTree)->GetYaxis()->SetTitle("Events");
		if(isFirst) v_truth_Meff.at(iTree)->Draw("hist");
		else v_truth_Meff.at(iTree)->Draw("hist same");
		stampATLAS_ratio("Internal", 0.55, 0.8);
		stampText(extraText,0.55,0.725,0.035);
		leg->Draw();
		c->SetLogy();
		gPad->RedrawAxis();
		c->Update();
		if(isLast) c->SaveAs("plots/"+reg+"/truth_Meff.pdf");
	}

	leg->Clear();
	c->Clear();

	for(unsigned int iTree=0; iTree<v_trees.size(); iTree++)
	{
		TString dsid;
		dsid.Form("%d", v_trees.at(iTree).second); 

		std::cout << "DSID: " << dsid << "\tPLOTTING" << std::endl;

		Bool_t isFirst=false; isFirst = (iTree==0);
		Bool_t isLast=false; isLast = ((iTree==0 && v_trees.size()==1)||(iTree==v_trees.size()-1 && v_trees.size()>1));

		//effective mass
		v_truth_Meff_4j.at(iTree)->SetMaximum(v_truth_Meff_4j.at(iTree)->GetMaximum()*20);
		v_truth_Meff_4j.at(iTree)->GetXaxis()->SetRangeUser(0,2000);
		v_truth_Meff_4j.at(iTree)->SetLineColor(TColor::GetColor(v_colours.at(iTree%v_trees.size())));
		leg->AddEntry(v_truth_Meff_4j.at(iTree),dsid,"l");
		v_truth_Meff_4j.at(iTree)->GetXaxis()->SetTitle("Effective Mass 4j [GeV]");
		v_truth_Meff_4j.at(iTree)->GetYaxis()->SetTitle("Events");
		if(isFirst) v_truth_Meff_4j.at(iTree)->Draw("hist");
		else v_truth_Meff_4j.at(iTree)->Draw("hist same");
		stampATLAS_ratio("Internal", 0.55, 0.8);
		stampText(extraText,0.55,0.725,0.035);
		leg->Draw();
		c->SetLogy();
		gPad->RedrawAxis();
		c->Update();
		if(isLast) c->SaveAs("plots/"+reg+"/truth_Meff4j.pdf");
	}

	leg->Clear();
	c->Clear();

	for(unsigned int iTree=0; iTree<v_trees.size(); iTree++)
	{
		TString dsid;
		dsid.Form("%d", v_trees.at(iTree).second); 

		std::cout << "DSID: " << dsid << "\tPLOTTING" << std::endl;

		Bool_t isFirst=false; isFirst = (iTree==0);
		Bool_t isLast=false; isLast = ((iTree==0 && v_trees.size()==1)||(iTree==v_trees.size()-1 && v_trees.size()>1));

		//effective mass
		v_truth_mT.at(iTree)->SetMaximum(v_truth_mT.at(iTree)->GetMaximum()*10);
		v_truth_mT.at(iTree)->GetXaxis()->SetRangeUser(0,600);
		v_truth_mT.at(iTree)->SetLineColor(TColor::GetColor(v_colours.at(iTree%v_trees.size())));
		leg->AddEntry(v_truth_mT.at(iTree),dsid,"l");
		v_truth_mT.at(iTree)->GetXaxis()->SetTitle("MT [GeV]");
		v_truth_mT.at(iTree)->GetYaxis()->SetTitle("Events");
		if(isFirst) v_truth_mT.at(iTree)->Draw("hist");
		else v_truth_mT.at(iTree)->Draw("hist same");
		stampATLAS_ratio("Internal", 0.55, 0.8);
		stampText(extraText,0.55,0.725,0.035);
		leg->Draw();
		c->SetLogy();
		gPad->RedrawAxis();
		c->Update();
		if(isLast) c->SaveAs("plots/"+reg+"/truth_mT.pdf");
	}

	leg->Clear();
	c->Clear();

	for(unsigned int iTree=0; iTree<v_trees.size(); iTree++)
	{
		TString dsid;
		dsid.Form("%d", v_trees.at(iTree).second); 

		std::cout << "DSID: " << dsid << "\tPLOTTING" << std::endl;

		Bool_t isFirst=false; isFirst = (iTree==0);
		Bool_t isLast=false; isLast = ((iTree==0 && v_trees.size()==1)||(iTree==v_trees.size()-1 && v_trees.size()>1));

		//effective mass
		v_truth_mTb.at(iTree)->SetMaximum(v_truth_mTb.at(iTree)->GetMaximum()*10);
		v_truth_mTb.at(iTree)->GetXaxis()->SetRangeUser(0,600);
		v_truth_mTb.at(iTree)->SetLineColor(TColor::GetColor(v_colours.at(iTree%v_trees.size())));
		leg->AddEntry(v_truth_mTb.at(iTree),dsid,"l");
		v_truth_mTb.at(iTree)->GetXaxis()->SetTitle("MTb [GeV]");
		v_truth_mTb.at(iTree)->GetYaxis()->SetTitle("Events");
		if(isFirst) v_truth_mTb.at(iTree)->Draw("hist");
		else v_truth_mTb.at(iTree)->Draw("hist same");
		stampATLAS_ratio("Internal", 0.55, 0.8);
		stampText(extraText,0.55,0.725,0.035);
		leg->Draw();
		c->SetLogy();
		gPad->RedrawAxis();
		c->Update();
		if(isLast) c->SaveAs("plots/"+reg+"/truth_mTb.pdf");
	}

	leg->Clear();
	c->Clear();

	// Sign out.
	std::cout << "Done with plotting." << std::endl;

	return;
}

void stampATLAS(const std::string &text, float x, float y) {
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

void stampATLAS_ratio(const std::string &text, float x, float y) {
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
  p.DrawLatex(x+0.14, y, text.c_str());
}

void stampLumiText(float lumi, float x, float y, const std::string &text, float size) {
  std::stringstream ss;
  ss << "#int L dt = " << lumi << " fb^{-1}, " << text;
  TLatex l;
  l.SetNDC();
  l.SetTextFont(42);
  l.SetTextColor(1);
  l.SetTextSize(size);
  l.DrawLatex(x, y, ss.str().c_str());
}

void stampText(const std::string &text, float x, float y, float size) {
  TLatex l;
  l.SetNDC();
  l.SetTextFont(42);
  l.SetTextColor(1);
  l.SetTextSize(size);
  l.DrawLatex(x, y, text.c_str());
}