//
// dumpYields.C
// ATLAS 2015 SUSY Multi-b/t search truth analysis: calculate systematic values.
// MLB [UVic] <matt.leblanc@cern.ch>
//

// Provided as-is for reference, but will probably require some modifications if you
// want to actually get it running. This scrapes a 2-d histogram produced by postTruth.C in order to
// dump the yields & systematic uncertainties per-region for our analysis.

// I actually run this on my laptop, to where I also download the merged output of running the main
// truth analysis over US Connect's condor system. The output file is about 3 GB, which is managable for me.

// Run as > root -l -b -q dumpYields.C

void dumpYields(void)
{
	TFile* f; f = new TFile("truthYields.root");
	TH2D* h_yields; h_yields = (TH2D*)f->Get("yields");

	std::cout << "Yields obtained. Dumping systematics ..." << std::endl;

	for(unsigned int iReg=0; iReg<h_yields->GetXaxis()->GetNbins(); iReg++)
	{
		std::cout << std::setw(12) << h_yields->GetXaxis()->GetBinLabel(iReg) << " ";
	}
	std::cout << std::endl;

	for(unsigned int iDSID=1; iDSID<h_yields->GetYaxis()->GetNbins(); iDSID++)
	{
		std::cout << std::setw(12) << h_yields->GetYaxis()->GetBinLabel(iDSID);
		for(unsigned int iReg=1; iReg<h_yields->GetXaxis()->GetNbins(); iReg++)
		{
			//std::cout << setiosflags(ios::fixed) << std::setw(13) << setprecision(0) << h_yields->GetBinContent(iReg,iDSID);
			std::cout << std::setw(12) << setprecision(3) << h_yields->GetBinContent(iReg,iDSID) << " ";
		}

		std::cout << std::endl;
	}

	std::cout << "\nSystematics per signal region ...\n" << std::endl;
	std::vector<TString> systs;
	systs.push_back("");
	// systs.push_back("Nominal");	
	// systs.push_back("Rad. Up");
	// systs.push_back("Rad. Down");
	// systs.push_back("Gen.");
	// systs.push_back("Had. / PS");
	// systs.push_back("nom/5");
	systs.push_back("F Nominal");
	systs.push_back("F Rad. Up");
	systs.push_back("F Rad. Down");
	systs.push_back("F Had. / PS");
	systs.push_back("F Tune");
	for(unsigned int iSyst=0; iSyst<systs.size(); iSyst++)
	{
		std::cout << std::setw(12) << systs.at(iSyst) << " ";
	}
	std::cout << std::endl;

	for(unsigned int iDSID=1; iDSID<h_yields->GetYaxis()->GetNbins(); iDSID++)
	{
		std::cout << std::setw(12) << h_yields->GetYaxis()->GetBinLabel(iDSID);
		for(unsigned int iReg=1; iReg<h_yields->GetXaxis()->GetNbins(); iReg++)
		{
			if(iReg<7) continue;
			//std::cout << setiosflags(ios::fixed) << std::setw(13) << setprecision(0) << h_yields->GetBinContent(iReg,iDSID);
			if(iReg < 7) std::cout << std::setw(12) << setprecision(5) << fabs((h_yields->GetBinContent(1,iDSID) - h_yields->GetBinContent(iReg,iDSID)))/(h_yields->GetBinContent(1,iDSID))*100 << " ";
			else if(iReg >= 7) 
				{
					std::cout << std::setw(12) << setprecision(5) << fabs((h_yields->GetBinContent(7,iDSID) - h_yields->GetBinContent(iReg,iDSID)))/(h_yields->GetBinContent(7,iDSID))*100 << " ";
				}

		}

		std::cout << std::endl;
	}

	std::cout << "\nSR/CR ...\n" << std::endl;
	for(unsigned int iSyst=0; iSyst<systs.size(); iSyst++)
	{
		std::cout << std::setw(12) << systs.at(iSyst) << " ";
	}
	std::cout << std::endl;

	for(unsigned int iDSID=6; iDSID<h_yields->GetYaxis()->GetNbins()-17; iDSID++)
	{
		std::cout << std::setw(12) << h_yields->GetYaxis()->GetBinLabel(iDSID);
		for(unsigned int iReg=1; iReg<h_yields->GetXaxis()->GetNbins(); iReg++)
		{
			if(iReg<7) continue;
			//std::cout << setiosflags(ios::fixed) << std::setw(13) << setprecision(0) << h_yields->GetBinContent(iReg,iDSID);
			//if(iReg < 7) std::cout << std::setw(12) << setprecision(5) << fabs((h_yields->GetBinContent(1,iDSID) - h_yields->GetBinContent(iReg,iDSID)))/(h_yields->GetBinContent(1,iDSID)) / fabs((h_yields->GetBinContent(7,iDSID) - h_yields->GetBinContent(iReg,iDSID+15)))/(h_yields->GetBinContent(7,iDSID+15)) << " ";
			else if(iReg >= 7) 
				{
					std::cout << std::setw(12) << setprecision(5) << (fabs((h_yields->GetBinContent(7,iDSID) - h_yields->GetBinContent(iReg,iDSID)))/(h_yields->GetBinContent(7,iDSID))) /  (fabs((h_yields->GetBinContent(7,iDSID+15) - h_yields->GetBinContent(iReg,iDSID+15)))/(h_yields->GetBinContent(7,iDSID+15))) << " ";
				}

		}

		std::cout << std::endl;
	}

		std::cout << std::endl;

	return;
}
