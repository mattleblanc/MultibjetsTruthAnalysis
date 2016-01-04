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

#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom.h"

void dumpYields(void)
{
	TFile* f; f = new TFile("truthYields.root");
	TH2D* h_yields; h_yields = (TH2D*)f->Get("yields");

	std::cout << "Yields obtained. Dumping systematics ..." << std::endl;

	for(int iDSID=0; iDSID<h_yields->GetXaxis()->GetNbins()+1; iDSID++)
	{
		std::cout << std::setw(12) << h_yields->GetXaxis()->GetBinLabel(iDSID) << " ";
	}
	std::cout << std::endl;

	for(int iVar=0; iVar<h_yields->GetYaxis()->GetNbins(); iVar++)
	{
		std::cout << std::setw(12) << h_yields->GetYaxis()->GetBinLabel(iVar);
		for(int iDSID=1; iDSID<h_yields->GetXaxis()->GetNbins()+1; iDSID++)
		{
			//std::cout << std::setw(12) << setprecision(3) << h_yields->GetBinError(iDSID,iVar)/h_yields->GetBinContent(iDSID,iVar) << " ";
			std::cout << std::setw(12) << setprecision(3) << h_yields->GetBinContent(iDSID,iVar) << " ";
		}

		std::cout << std::endl;
	}

	std::cout << "\nSystematics per signal region ...\n" << std::endl;
	std::vector<TString> systs;
	systs.push_back("");
	//systs.push_back("Nominal");	
	// systs.push_back("Rad. Up");
	// systs.push_back("Rad. Down");
	systs.push_back("Nom.");
	systs.push_back("Gen.");
	// systs.push_back("nom/5");
	systs.push_back("Nominal");
	systs.push_back("Rad. Up");
	systs.push_back("Rad. Down");
	systs.push_back("Had. / PS");
	//systs.push_back("Tune");

	// Print out variation names ...
	for(unsigned long iSyst=0; iSyst<systs.size(); iSyst++)
	{
		std::cout << std::setw(12) << systs.at(iSyst) << " ";
	}
	std::cout << std::endl;

	// Get the systematics.
	for(int iVar=6; iVar<h_yields->GetYaxis()->GetNbins(); iVar++)
	{
		// Which region?
		std::cout << std::setw(12) << h_yields->GetYaxis()->GetBinLabel(iVar);

		// Then, loop over the variation samples.
		for(int iDSID=1; iDSID<h_yields->GetXaxis()->GetNbins()+1; iDSID++)
		{
					if(iDSID<3) std::cout << std::setw(12) << setprecision(5) << fabs((h_yields->GetBinContent(1,iVar) - h_yields->GetBinContent(iDSID,iVar)))/(h_yields->GetBinContent(1,iVar))*100 << " ";
					else std::cout << std::setw(12) << setprecision(5) << fabs((h_yields->GetBinContent(3,iVar) - h_yields->GetBinContent(iDSID,iVar)))/(h_yields->GetBinContent(3,iVar))*100 << " ";
		}

		std::cout << std::endl;
	}

	std::cout << "\nSR/CR ...\n" << std::endl;
	for(unsigned long iSyst=0; iSyst<systs.size(); iSyst++)
	{
		std::cout << std::setw(12) << systs.at(iSyst) << " ";
	}
	std::cout << std::endl;

	for(int iVar=6; iVar<h_yields->GetYaxis()->GetNbins()-15; iVar++) // We just want to loop over the signal regions here.
	{
		std::cout << std::setw(12) << h_yields->GetYaxis()->GetBinLabel(iVar);
		for(int iDSID=1; iDSID<h_yields->GetXaxis()->GetNbins()+1; iDSID++)
		{
					if(iDSID<3) std::cout << std::setw(12) << setprecision(5) << (fabs((h_yields->GetBinContent(1,iVar) - h_yields->GetBinContent(iDSID,iVar)))/(h_yields->GetBinContent(1,iVar))) /  (fabs((h_yields->GetBinContent(1,iVar+15) - h_yields->GetBinContent(iDSID,iVar+15)))/(h_yields->GetBinContent(1,iVar+15))) << " ";
					else std::cout << std::setw(12) << setprecision(5) << (fabs((h_yields->GetBinContent(3,iVar) - h_yields->GetBinContent(iDSID,iVar)))/(h_yields->GetBinContent(1,iVar))) /  (fabs((h_yields->GetBinContent(3,iVar+15) - h_yields->GetBinContent(iDSID,iVar+15)))/(h_yields->GetBinContent(3,iVar+15))) << " ";
		}

		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\nTransfer factor uncertainty ...\n" << std::endl;
	for(unsigned long iSyst=0; iSyst<systs.size(); iSyst++)
	{
		std::cout << std::setw(12) << systs.at(iSyst) << " ";
	}
	std::cout << std::endl;

	for(int iVar=6; iVar<h_yields->GetYaxis()->GetNbins(); iVar++) // We just want to loop over the signal regions here.
	{
		vector<float> uncerts;

		std::cout << std::setw(12) << h_yields->GetYaxis()->GetBinLabel(iVar);

		for(int iDSID=1; iDSID<h_yields->GetXaxis()->GetNbins(); iDSID++)
		{
			float tf_nom, tf_syst;
			if(iDSID<3)
			{
				if(iVar<21)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,iVar+15);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,iVar+15);
				}

				// Gbb validation regions
				if(iVar==36)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,21);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,21);
				}
				if(iVar==37)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,22);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,22);
				}
				if(iVar==38)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,23);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,23);
				}
				if(iVar==39)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,24);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,24);
				}
				if(iVar==40)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,25);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,25);
				}

				// Gtt 0L validation regions
				if(iVar==41)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,32);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,32);
				}
				if(iVar==42)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,33);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,33);
				}
				if(iVar==43)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,34);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,34);
				}
				if(iVar==44)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,35);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,35);
				}
				if(iVar==45)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,32);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,32);
				}
				if(iVar==46)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,33);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,33);
				}
				if(iVar==47)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,34);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,34);
				}
				if(iVar==48)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,35);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,35);
				}

				// Gtt 1L validation regions
				if(iVar==49)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,26);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,26);
				}
				if(iVar==50)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,27);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,27);
				}
				if(iVar==51)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,29);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,29);
				}
				if(iVar==52)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,30);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,30);
				}
				if(iVar==53)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,26);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,26);
				}
				if(iVar==54)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,27);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,27);
				}
				if(iVar==55)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,29);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,29);
				}
				if(iVar==56)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,30);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,30);
				}
				if(iVar==57)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,26);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,26);
				}
				if(iVar==58)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,27);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,27);
				}
				if(iVar==59)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,29);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,29);
				}
				if(iVar==60)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,30);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,30);
				}
				if(iVar==61)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,26);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,26);
				}
				if(iVar==62)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,27);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,27);
				}
				if(iVar==63)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,29);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,29);
				}
				if(iVar==64)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,30);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,30);
				}
				if(iVar==65)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,26);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,26);
				}
				if(iVar==66)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,27);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,27);
				}
				if(iVar==67)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,28);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,28);
				}
				if(iVar==68)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,31);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,31);
				}
				if(iVar==69)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,28);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,28);
				}
				if(iVar==70)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,31);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,31);
				}
				if(iVar==71)
				{
					tf_nom = h_yields->GetBinContent(1,iVar)/h_yields->GetBinContent(1,28);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,28);
				}

			}
			else
			{
				if(iVar<21)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,iVar+15);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,iVar+15);
				}

				// Gbb validation regions
				if(iVar==36)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,21);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,21);
				}
				if(iVar==37)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,22);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,22);
				}
				if(iVar==38)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,23);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,23);
				}
				if(iVar==39)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,24);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,24);
				}
				if(iVar==40)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,25);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,25);
				}

				// Gtt 0L validation regions
				if(iVar==41)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,32);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,32);
				}
				if(iVar==42)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,33);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,33);
				}
				if(iVar==43)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,34);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,34);
				}
				if(iVar==44)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,35);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,35);
				}
				if(iVar==45)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,32);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,32);
				}
				if(iVar==46)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,33);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,33);
				}
				if(iVar==47)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,34);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,34);
				}
				if(iVar==48)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,35);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,35);
				}

				// Gtt 1L validation regions
				if(iVar==49)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,26);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,26);
				}
				if(iVar==50)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,27);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,27);
				}
				if(iVar==51)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,29);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,29);
				}
				if(iVar==52)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,30);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,30);
				}
				if(iVar==53)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,26);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,26);
				}
				if(iVar==54)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,27);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,27);
				}
				if(iVar==55)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,29);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,29);
				}
				if(iVar==56)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,30);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,30);
				}
				if(iVar==57)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,26);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,26);
				}
				if(iVar==58)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,27);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,27);
				}
				if(iVar==59)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,29);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,29);
				}
				if(iVar==60)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,30);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,30);
				}
				if(iVar==61)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,26);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,26);
				}
				if(iVar==62)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,27);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,27);
				}
				if(iVar==63)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,29);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,29);
				}
				if(iVar==64)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,30);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,30);
				}
				if(iVar==65)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,26);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,26);
				}
				if(iVar==66)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,27);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,27);
				}
				if(iVar==67)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,28);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,28);
				}
				if(iVar==68)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,31);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,31);
				}
				if(iVar==69)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,28);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,28);
				}
				if(iVar==70)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,31);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,31);
				}
				if(iVar==71)
				{
					tf_nom = h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,28);
					tf_syst = h_yields->GetBinContent(iDSID,iVar)/h_yields->GetBinContent(iDSID,28);
				}
			}

			//std::cout << "nom is " << h_yields->GetBinContent(3,iVar)/h_yields->GetBinContent(3,iVar+15) << " right?" << std::endl;

			float pdiff = fabs(tf_nom-tf_syst)/tf_nom*100.0;

			std::cout << std::setw(12) << setprecision(5) << pdiff << " &";

			uncerts.push_back(pdiff);
		}

		std::cout << "\t+" << sqrt(pow(uncerts.at(3),2)+pow(uncerts.at(5),2)+pow(uncerts.at(1),2)) << "/-" << sqrt(pow(uncerts.at(4),2)+pow(uncerts.at(5),2)+pow(uncerts.at(1),2)) << std::endl;
	}

	std::cout << std::endl;

	return;
}
