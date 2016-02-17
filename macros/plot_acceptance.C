//
// plot_acceptance.C
// Produce HEPData acceptance plots based on ATLAS Run-II Multi-b/t Search Truth Analysis outputs.
//
// Matt LeBlnac
// matt.leblanc@cern.ch
//

void setInputFile(Int_t dsid, TFile*& inFile);
void getSusyMasses(Int_t dsid, Float_t &Mg, Float_t &Mn);

void plot_acceptance(void)
{
  std::cout << "plot_acceptance.C\t'Happiness can only exist in acceptance.'\n\t\t\t\t--George Orwell" << std::endl;

  // Fill vectors of DSIDs and signal regions
  std::vector<int> dsids;
  std::vector<TString> regions;

  for(int iDSID=370100; iDSID<=370187; iDSID++) 
    {
      if(iDSID==370111 || iDSID==370112) continue;
      dsids.push_back(iDSID);
    }

  for(int iDSID=370250; iDSID<=370351; iDSID++)
    {
      dsids.push_back(iDSID);
    }

  TH2F* h2_acc_GbbSRC2; h2_acc_GbbSRC2 = new TH2F("GbbSRC2Acceptance","GbbSRC2Acceptance",12,850,2050,34,0,1700.0);
  TH2F* h2_acc_GbbSRA4; h2_acc_GbbSRA4 = new TH2F("GbbSRA4Acceptance","GbbSRA4Acceptance",12,850,2050,34,0,1700.0);
  TH2F* h2_acc_GbbSRB4; h2_acc_GbbSRB4 = new TH2F("GbbSRB4Acceptance","GbbSRB4Acceptance",12,850,2050,34,0,1700.0);
  TH2F* h2_acc_Gtt1LSRA2; h2_acc_Gtt1LSRA2 = new TH2F("Gtt1LSRA2Acceptance","Gtt1LSRA2Acceptance",12,850,2050,34,0,1700.0);
  TH2F* h2_acc_Gtt1LSRB2; h2_acc_Gtt1LSRB2 = new TH2F("Gtt1LSRB2Acceptance","Gtt1LSRB2Acceptance",12,850,2050,34,0,1700.0);
  TH2F* h2_acc_Gtt0LSRA; h2_acc_Gtt0LSRA = new TH2F("Gtt0LSRAAcceptance","Gtt0LSRAAcceptance",12,850,2050,34,0,1700.0);
  TH2F* h2_acc_Gtt0LSRB; h2_acc_Gtt0LSRB = new TH2F("Gtt0LSRBAcceptance","Gtt0LSRBAcceptance",12,850,2050,34,0,1700.0);
  TH2F* h2_acc_Gtt0LSRC; h2_acc_Gtt0LSRC = new TH2F("Gtt0LSRCAcceptance","Gtt0LSRCAcceptance",12,850,2050,34,0,1700.0);

  TFile* outFile; outFile = new TFile("multib.acceptances.root","recreate");

  for(int iDSID=0; iDSID<dsids.size(); iDSID++)
    {
      // Open the right input file.
      TFile* inFile;
      setInputFile(dsids.at(iDSID),inFile);

      TTree* inTree; inTree = (TTree*)inFile->Get("out_tree");

      Float_t mc_weight; inTree->SetBranchAddress("mc_weight",&mc_weight);

      Int_t isGbbSRC2; inTree->SetBranchAddress("isGbbSRC2",&isGbbSRC2);
      Int_t isGbbSRA4; inTree->SetBranchAddress("isGbbSRA4",&isGbbSRA4);
      Int_t isGbbSRB4; inTree->SetBranchAddress("isGbbSRB4",&isGbbSRB4);
      Int_t isGtt1LSRA2; inTree->SetBranchAddress("isGtt1LSRA2",&isGtt1LSRA2);
      Int_t isGtt1LSRB2; inTree->SetBranchAddress("isGtt1LSRB2",&isGtt1LSRB2);
      Int_t isGtt0LSRA; inTree->SetBranchAddress("isGtt0LSRA",&isGtt0LSRA);
      Int_t isGtt0LSRB; inTree->SetBranchAddress("isGtt0LSRB",&isGtt0LSRB);
      Int_t isGtt0LSRC; inTree->SetBranchAddress("isGtt0LSRC",&isGtt0LSRC);

      //Bool_t isTRF; inTree->SetBranchAddress("isTRF",&isTRF);
      //Bool_t isTRF_incl; inTree->SetBranchAddress("isTRF_incl",&isTRF_incl);
      //Double_t TRF_wgt; inTree->SetBranchAddress("TRF_wgt",&TRF_wgt);
      //Int_t NBJets_TRF;  inTree->SetBranchAddress("NBJets_TRF",&NBJets_TRF);
      
      //TH1F* h370100; h370100 = new TH1F("370100","370100",50,0,50);
      TH1F* hDSID; hDSID = new TH1F("1dh","1dh",10,0,9);
      
      //std::cout << "There are " << inTree->GetEntries() << " entries in the input ttree." << std::endl;
      
      Float_t weight = 1.0;
      
      for(int iEvent=0; iEvent<inTree->GetEntries(); iEvent++)
	      {
          weight=1.0;
	        inTree->GetEntry(iEvent);
      	  //if(isTRF) continue;

          //weight*=TRF_wgt;
          weight*=mc_weight;
      	  
      	  hDSID->Fill("All",weight);
          if(dsids.at(iDSID)>=370250)
          {
            if(isGbbSRC2) hDSID->Fill("SRGbbSRC2",weight);
            if(isGbbSRA4) hDSID->Fill("SRGbbSRA4",weight);
        	  if(isGbbSRB4) hDSID->Fill("SRGbbSRB4",weight);
          }
          else if(dsids.at(iDSID)<=370187)
          {
        	  if(isGtt1LSRA2) hDSID->Fill("SRGtt1LSRA2",weight);
        	  if(isGtt1LSRB2) hDSID->Fill("SRGtt1LSRB2",weight);
        	  if(isGtt0LSRA) hDSID->Fill("SRGtt0LSRA",weight);
        	  if(isGtt0LSRB) hDSID->Fill("SRGtt0LSRB",weight);
        	  if(isGtt0LSRC) hDSID->Fill("SRGtt0LSRC",weight);
          }
	      }

      Float_t massGluino;
      Float_t massNeutralino;

      getSusyMasses(dsids.at(iDSID), massGluino, massNeutralino);

          if(dsids.at(iDSID)>=370250)
          {
            std::cout << std::fixed << dsids.at(iDSID) << "\tSR-Gbb-A\t" << std::setprecision(6) << 100.0*hDSID->GetBinContent(2)/hDSID->GetBinContent(1)
		            << "\t"; std::cout.unsetf(ios_base::fixed); std::cout << massGluino << "\t" << massNeutralino << std::endl;
            std::cout << std::fixed << dsids.at(iDSID) << "\tSR-Gbb-B\t"  << std::setprecision(6) << 100.0*hDSID->GetBinContent(3)/hDSID->GetBinContent(1)
		            << "\t"; std::cout.unsetf(ios_base::fixed); std::cout << massGluino << "\t" << massNeutralino << std::endl;
            std::cout << std::fixed << dsids.at(iDSID) << "\tSR-Gbb-C\t"  << std::setprecision(6) << 100.0*hDSID->GetBinContent(4)/hDSID->GetBinContent(1)
		            << "\t"; std::cout.unsetf(ios_base::fixed); std::cout << massGluino << "\t" << massNeutralino << std::endl;
          }
          else if(dsids.at(iDSID)<=370187)
          {
            std::cout << std::fixed << dsids.at(iDSID) << "\tSR-Gtt-1L-A\t"  << std::setprecision(6) << 100.0*hDSID->GetBinContent(2)/hDSID->GetBinContent(1)
		            << "\t"; std::cout.unsetf(ios_base::fixed); std::cout << massGluino << "\t" << massNeutralino << std::endl;
            std::cout << std::fixed << dsids.at(iDSID) << "\tSR-Gtt-1L-B\t" << std::setprecision(6) << 100.0*hDSID->GetBinContent(3)/hDSID->GetBinContent(1)
                << "\t"; std::cout.unsetf(ios_base::fixed); std::cout << massGluino << "\t" << massNeutralino << std::endl;
            std::cout << std::fixed << dsids.at(iDSID) << "\tSR-Gtt-0L-A\t" << std::setprecision(6) << 100.0*hDSID->GetBinContent(4)/hDSID->GetBinContent(1)
                << "\t"; std::cout.unsetf(ios_base::fixed); std::cout << massGluino << "\t" << massNeutralino << std::endl;
            std::cout << std::fixed << dsids.at(iDSID) << "\tSR-Gtt-0L-B\t" << std::setprecision(6) << 100.0*hDSID->GetBinContent(5)/hDSID->GetBinContent(1)
		            << "\t"; std::cout.unsetf(ios_base::fixed); std::cout << massGluino << "\t" << massNeutralino << std::endl;
            std::cout << std::fixed << dsids.at(iDSID) << "\tSR-Gtt-0L-C\t" << std::setprecision(6) << 100.0*hDSID->GetBinContent(6)/hDSID->GetBinContent(1)
		            << "\t"; std::cout.unsetf(ios_base::fixed); std::cout << massGluino << "\t" << massNeutralino << std::endl;
          }

          hDSID->Print();
          std::cout << "n bins " << hDSID->GetNbinsX() << std::endl;
          for(int ibin=0; ibin<hDSID->GetNbinsX(); ibin++)
          {
            std::cout << "bin " << ibin << " content " << hDSID->GetBinContent(ibin) << std::endl;
          }

      outFile->cd();

      if(dsids.at(iDSID)>=370250)
      {
        h2_acc_GbbSRC2->Fill(massGluino,massNeutralino,100.0*hDSID->GetBinContent(2)/hDSID->GetBinContent(1));
        h2_acc_GbbSRA4->Fill(massGluino,massNeutralino,100.0*hDSID->GetBinContent(3)/hDSID->GetBinContent(1));
        h2_acc_GbbSRB4->Fill(massGluino,massNeutralino,100.0*hDSID->GetBinContent(4)/hDSID->GetBinContent(1));
      }
       else if(dsids.at(iDSID)<=370187)
      {
        h2_acc_Gtt1LSRA2->Fill(massGluino,massNeutralino,100.0*hDSID->GetBinContent(2)/hDSID->GetBinContent(1));
        h2_acc_Gtt1LSRB2->Fill(massGluino,massNeutralino,100.0*hDSID->GetBinContent(3)/hDSID->GetBinContent(1));
        h2_acc_Gtt0LSRA->Fill(massGluino,massNeutralino,100.0*hDSID->GetBinContent(4)/hDSID->GetBinContent(1));
        h2_acc_Gtt0LSRB->Fill(massGluino,massNeutralino,100.0*hDSID->GetBinContent(5)/hDSID->GetBinContent(1));
        h2_acc_Gtt0LSRC->Fill(massGluino,massNeutralino,100.0*hDSID->GetBinContent(6)/hDSID->GetBinContent(1));
      }
      delete hDSID;
      delete inFile;
    }
  
      h2_acc_GbbSRC2->Write();
      h2_acc_GbbSRA4->Write();
      h2_acc_GbbSRB4->Write();
      h2_acc_Gtt1LSRA2->Write();
      h2_acc_Gtt1LSRB2->Write();
      h2_acc_Gtt0LSRA->Write();
      h2_acc_Gtt0LSRB->Write();
      h2_acc_Gtt0LSRC->Write();

  return;
}

void setInputFile(Int_t dsid, TFile*& inFile)
{
      // Gtt grid

      if(dsid==370100) inFile = new TFile("/home/mleblanc/out/acceptance/370100/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370100.MGPy8EG_A14N_GG_ttn1_900_5000_1.merge.DAOD_TRUTH1.e4049_p2482-0.root","open"); 
      if(dsid==370101) inFile = new TFile("/home/mleblanc/out/acceptance/370101/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370101.MGPy8EG_A14N_GG_ttn1_900_5000_200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370102) inFile = new TFile("/home/mleblanc/out/acceptance/370102/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370102.MGPy8EG_A14N_GG_ttn1_900_5000_400.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370103) inFile = new TFile("/home/mleblanc/out/acceptance/370103/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370103.MGPy8EG_A14N_GG_ttn1_900_5000_545.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370104) inFile = new TFile("/home/mleblanc/out/acceptance/370104/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370104.MGPy8EG_A14N_GG_ttn1_1000_5000_1.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370105) inFile = new TFile("/home/mleblanc/out/acceptance/370105/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370105.MGPy8EG_A14N_GG_ttn1_1000_5000_200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370106) inFile = new TFile("/home/mleblanc/out/acceptance/370106/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370106.MGPy8EG_A14N_GG_ttn1_1000_5000_400.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370107) inFile = new TFile("/home/mleblanc/out/acceptance/370107/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370107.MGPy8EG_A14N_GG_ttn1_1000_5000_600.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370108) inFile = new TFile("/home/mleblanc/out/acceptance/370108/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370108.MGPy8EG_A14N_GG_ttn1_1000_5000_645.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370109) inFile = new TFile("/home/mleblanc/out/acceptance/370109/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370109.MGPy8EG_A14N_GG_ttn1_1100_5000_1.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370110) inFile = new TFile("/home/mleblanc/out/acceptance/370110/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370110.MGPy8EG_A14N_GG_ttn1_1100_5000_200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370111) inFile = new TFile("/home/mleblanc/out/acceptance/370111/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370111.MGPy8EG_A14N_GG_ttn1_1100_5000_400.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370112) inFile = new TFile("/home/mleblanc/out/acceptance/370112/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370112.MGPy8EG_A14N_GG_ttn1_1100_5000_600.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370113) inFile = new TFile("/home/mleblanc/out/acceptance/370113/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370113.MGPy8EG_A14N_GG_ttn1_1100_5000_745.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370114) inFile = new TFile("/home/mleblanc/out/acceptance/370114/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370114.MGPy8EG_A14N_GG_ttn1_1200_5000_1.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370115) inFile = new TFile("/home/mleblanc/out/acceptance/370115/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370115.MGPy8EG_A14N_GG_ttn1_1200_5000_100.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370116) inFile = new TFile("/home/mleblanc/out/acceptance/370116/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370116.MGPy8EG_A14N_GG_ttn1_1200_5000_200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370117) inFile = new TFile("/home/mleblanc/out/acceptance/370117/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370117.MGPy8EG_A14N_GG_ttn1_1200_5000_400.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370118) inFile = new TFile("/home/mleblanc/out/acceptance/370118/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370118.MGPy8EG_A14N_GG_ttn1_1200_5000_600.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370119) inFile = new TFile("/home/mleblanc/out/acceptance/370119/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370119.MGPy8EG_A14N_GG_ttn1_1200_5000_700.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370120) inFile = new TFile("/home/mleblanc/out/acceptance/370120/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370120.MGPy8EG_A14N_GG_ttn1_1200_5000_800.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370121) inFile = new TFile("/home/mleblanc/out/acceptance/370121/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370121.MGPy8EG_A14N_GG_ttn1_1200_5000_845.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370122) inFile = new TFile("/home/mleblanc/out/acceptance/370122/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370122.MGPy8EG_A14N_GG_ttn1_1200_5000_855.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370123) inFile = new TFile("/home/mleblanc/out/acceptance/370123/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370123.MGPy8EG_A14N_GG_ttn1_1300_5000_1.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370124) inFile = new TFile("/home/mleblanc/out/acceptance/370124/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370124.MGPy8EG_A14N_GG_ttn1_1300_5000_200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370125) inFile = new TFile("/home/mleblanc/out/acceptance/370125/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370125.MGPy8EG_A14N_GG_ttn1_1300_5000_400.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370126) inFile = new TFile("/home/mleblanc/out/acceptance/370126/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370126.MGPy8EG_A14N_GG_ttn1_1300_5000_600.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370127) inFile = new TFile("/home/mleblanc/out/acceptance/370127/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370127.MGPy8EG_A14N_GG_ttn1_1300_5000_800.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370128) inFile = new TFile("/home/mleblanc/out/acceptance/370128/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370128.MGPy8EG_A14N_GG_ttn1_1300_5000_945.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370129) inFile = new TFile("/home/mleblanc/out/acceptance/370129/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370129.MGPy8EG_A14N_GG_ttn1_1400_5000_1.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370130) inFile = new TFile("/home/mleblanc/out/acceptance/370130/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370130.MGPy8EG_A14N_GG_ttn1_1400_5000_100.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370131) inFile = new TFile("/home/mleblanc/out/acceptance/370131/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370131.MGPy8EG_A14N_GG_ttn1_1400_5000_200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370132) inFile = new TFile("/home/mleblanc/out/acceptance/370132/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370132.MGPy8EG_A14N_GG_ttn1_1400_5000_400.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370133) inFile = new TFile("/home/mleblanc/out/acceptance/370133/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370133.MGPy8EG_A14N_GG_ttn1_1400_5000_600.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370134) inFile = new TFile("/home/mleblanc/out/acceptance/370134/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370134.MGPy8EG_A14N_GG_ttn1_1400_5000_800.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370135) inFile = new TFile("/home/mleblanc/out/acceptance/370135/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370135.MGPy8EG_A14N_GG_ttn1_1400_5000_1000.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370136) inFile = new TFile("/home/mleblanc/out/acceptance/370136/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370136.MGPy8EG_A14N_GG_ttn1_1400_5000_1045.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370137) inFile = new TFile("/home/mleblanc/out/acceptance/370137/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370137.MGPy8EG_A14N_GG_ttn1_1500_5000_1.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370138) inFile = new TFile("/home/mleblanc/out/acceptance/370138/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370138.MGPy8EG_A14N_GG_ttn1_1500_5000_200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370139) inFile = new TFile("/home/mleblanc/out/acceptance/370139/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370139.MGPy8EG_A14N_GG_ttn1_1500_5000_400.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370140) inFile = new TFile("/home/mleblanc/out/acceptance/370140/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370140.MGPy8EG_A14N_GG_ttn1_1500_5000_600.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370141) inFile = new TFile("/home/mleblanc/out/acceptance/370141/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370141.MGPy8EG_A14N_GG_ttn1_1500_5000_800.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370142) inFile = new TFile("/home/mleblanc/out/acceptance/370142/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370142.MGPy8EG_A14N_GG_ttn1_1500_5000_1000.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370143) inFile = new TFile("/home/mleblanc/out/acceptance/370143/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370143.MGPy8EG_A14N_GG_ttn1_1500_5000_1145.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370144) inFile = new TFile("/home/mleblanc/out/acceptance/370144/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370144.MGPy8EG_A14N_GG_ttn1_1600_5000_1.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370145) inFile = new TFile("/home/mleblanc/out/acceptance/370145/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370145.MGPy8EG_A14N_GG_ttn1_1600_5000_200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370146) inFile = new TFile("/home/mleblanc/out/acceptance/370146/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370146.MGPy8EG_A14N_GG_ttn1_1600_5000_400.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370147) inFile = new TFile("/home/mleblanc/out/acceptance/370147/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370147.MGPy8EG_A14N_GG_ttn1_1600_5000_600.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370148) inFile = new TFile("/home/mleblanc/out/acceptance/370148/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370148.MGPy8EG_A14N_GG_ttn1_1600_5000_800.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370149) inFile = new TFile("/home/mleblanc/out/acceptance/370149/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370149.MGPy8EG_A14N_GG_ttn1_1600_5000_1000.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370150) inFile = new TFile("/home/mleblanc/out/acceptance/370150/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370150.MGPy8EG_A14N_GG_ttn1_1600_5000_1200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370151) inFile = new TFile("/home/mleblanc/out/acceptance/370151/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370151.MGPy8EG_A14N_GG_ttn1_1600_5000_1245.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370152) inFile = new TFile("/home/mleblanc/out/acceptance/370152/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370152.MGPy8EG_A14N_GG_ttn1_1700_5000_1.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370153) inFile = new TFile("/home/mleblanc/out/acceptance/370153/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370153.MGPy8EG_A14N_GG_ttn1_1700_5000_200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370154) inFile = new TFile("/home/mleblanc/out/acceptance/370154/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370154.MGPy8EG_A14N_GG_ttn1_1700_5000_400.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");      
      if(dsid==370155) inFile = new TFile("/home/mleblanc/out/acceptance/370155/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370155.MGPy8EG_A14N_GG_ttn1_1700_5000_600.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370156) inFile = new TFile("/home/mleblanc/out/acceptance/370156/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370156.MGPy8EG_A14N_GG_ttn1_1700_5000_800.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370157) inFile = new TFile("/home/mleblanc/out/acceptance/370157/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370157.MGPy8EG_A14N_GG_ttn1_1700_5000_1000.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370158) inFile = new TFile("/home/mleblanc/out/acceptance/370158/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370158.MGPy8EG_A14N_GG_ttn1_1700_5000_1200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370159) inFile = new TFile("/home/mleblanc/out/acceptance/370159/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370159.MGPy8EG_A14N_GG_ttn1_1700_5000_1345.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370160) inFile = new TFile("/home/mleblanc/out/acceptance/370160/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370160.MGPy8EG_A14N_GG_ttn1_1800_5000_1.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370161) inFile = new TFile("/home/mleblanc/out/acceptance/370161/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370161.MGPy8EG_A14N_GG_ttn1_1800_5000_200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370162) inFile = new TFile("/home/mleblanc/out/acceptance/370162/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370162.MGPy8EG_A14N_GG_ttn1_1800_5000_400.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370163) inFile = new TFile("/home/mleblanc/out/acceptance/370163/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370163.MGPy8EG_A14N_GG_ttn1_1800_5000_600.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370164) inFile = new TFile("/home/mleblanc/out/acceptance/370164/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370164.MGPy8EG_A14N_GG_ttn1_1800_5000_800.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370165) inFile = new TFile("/home/mleblanc/out/acceptance/370165/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370165.MGPy8EG_A14N_GG_ttn1_1800_5000_1000.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370166) inFile = new TFile("/home/mleblanc/out/acceptance/370166/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370166.MGPy8EG_A14N_GG_ttn1_1800_5000_1200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370167) inFile = new TFile("/home/mleblanc/out/acceptance/370167/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370167.MGPy8EG_A14N_GG_ttn1_1800_5000_1400.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370168) inFile = new TFile("/home/mleblanc/out/acceptance/370168/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370168.MGPy8EG_A14N_GG_ttn1_1800_5000_1445.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370169) inFile = new TFile("/home/mleblanc/out/acceptance/370169/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370169.MGPy8EG_A14N_GG_ttn1_1900_5000_1.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370170) inFile = new TFile("/home/mleblanc/out/acceptance/370170/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370170.MGPy8EG_A14N_GG_ttn1_1900_5000_200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370171) inFile = new TFile("/home/mleblanc/out/acceptance/370171/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370171.MGPy8EG_A14N_GG_ttn1_1900_5000_400.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370172) inFile = new TFile("/home/mleblanc/out/acceptance/370172/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370172.MGPy8EG_A14N_GG_ttn1_1900_5000_600.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370173) inFile = new TFile("/home/mleblanc/out/acceptance/370173/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370173.MGPy8EG_A14N_GG_ttn1_1900_5000_800.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370174) inFile = new TFile("/home/mleblanc/out/acceptance/370174/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370174.MGPy8EG_A14N_GG_ttn1_1900_5000_1000.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370175) inFile = new TFile("/home/mleblanc/out/acceptance/370175/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370175.MGPy8EG_A14N_GG_ttn1_1900_5000_1200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370176) inFile = new TFile("/home/mleblanc/out/acceptance/370176/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370176.MGPy8EG_A14N_GG_ttn1_1900_5000_1400.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");      
      if(dsid==370177) inFile = new TFile("/home/mleblanc/out/acceptance/370177/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370177.MGPy8EG_A14N_GG_ttn1_1900_5000_1545.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370178) inFile = new TFile("/home/mleblanc/out/acceptance/370178/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370178.MGPy8EG_A14N_GG_ttn1_2000_5000_1.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370179) inFile = new TFile("/home/mleblanc/out/acceptance/370179/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370179.MGPy8EG_A14N_GG_ttn1_2000_5000_200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370180) inFile = new TFile("/home/mleblanc/out/acceptance/370180/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370180.MGPy8EG_A14N_GG_ttn1_2000_5000_400.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370181) inFile = new TFile("/home/mleblanc/out/acceptance/370181/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370181.MGPy8EG_A14N_GG_ttn1_2000_5000_600.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370182) inFile = new TFile("/home/mleblanc/out/acceptance/370182/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370182.MGPy8EG_A14N_GG_ttn1_2000_5000_800.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370183) inFile = new TFile("/home/mleblanc/out/acceptance/370183/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370183.MGPy8EG_A14N_GG_ttn1_2000_5000_1000.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370184) inFile = new TFile("/home/mleblanc/out/acceptance/370184/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370184.MGPy8EG_A14N_GG_ttn1_2000_5000_1200.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370185) inFile = new TFile("/home/mleblanc/out/acceptance/370185/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370185.MGPy8EG_A14N_GG_ttn1_2000_5000_1400.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370186) inFile = new TFile("/home/mleblanc/out/acceptance/370186/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370186.MGPy8EG_A14N_GG_ttn1_2000_5000_1600.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");
      if(dsid==370187) inFile = new TFile("/home/mleblanc/out/acceptance/370187/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370187.MGPy8EG_A14N_GG_ttn1_2000_5000_1645.merge.DAOD_TRUTH1.e4049_p2482-0.root","open");

      // Gbb grid
      if(dsid==370250) inFile = new TFile("/home/mleblanc/out/acceptance/370250/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370250.MGPy8EG_A14N_GG_bbn1_900_5000_1.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370251) inFile = new TFile("/home/mleblanc//out/acceptance/370251/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370251.MGPy8EG_A14N_GG_bbn1_900_5000_200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370252) inFile = new TFile("/home/mleblanc/out/acceptance/370252/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370252.MGPy8EG_A14N_GG_bbn1_900_5000_400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370253) inFile = new TFile("/home/mleblanc/out/acceptance/370253/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370253.MGPy8EG_A14N_GG_bbn1_900_5000_600.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370254) inFile = new TFile("/home/mleblanc/out/acceptance/370254/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370254.MGPy8EG_A14N_GG_bbn1_900_5000_800.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370255) inFile = new TFile("/home/mleblanc/out/acceptance/370255/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370255.MGPy8EG_A14N_GG_bbn1_900_5000_880.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370256) inFile = new TFile("/home/mleblanc/out/acceptance/370256/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370256.MGPy8EG_A14N_GG_bbn1_1000_5000_1.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370257) inFile = new TFile("/home/mleblanc/out/acceptance/370257/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370257.MGPy8EG_A14N_GG_bbn1_1000_5000_200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370258) inFile = new TFile("/home/mleblanc/out/acceptance/370258/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370258.MGPy8EG_A14N_GG_bbn1_1000_5000_400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370259) inFile = new TFile("/home/mleblanc/out/acceptance/370259/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370259.MGPy8EG_A14N_GG_bbn1_1000_5000_600.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370260) inFile = new TFile("/home/mleblanc/out/acceptance/370260/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370260.MGPy8EG_A14N_GG_bbn1_1000_5000_800.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370261) inFile = new TFile("/home/mleblanc/out/acceptance/370261/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370261.MGPy8EG_A14N_GG_bbn1_1000_5000_980.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370262) inFile = new TFile("/home/mleblanc/out/acceptance/370262/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370262.MGPy8EG_A14N_GG_bbn1_1100_5000_1.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370263) inFile = new TFile("/home/mleblanc/out/acceptance/370263/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370263.MGPy8EG_A14N_GG_bbn1_1100_5000_200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370264) inFile = new TFile("/home/mleblanc/out/acceptance/370264/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370264.MGPy8EG_A14N_GG_bbn1_1100_5000_400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370265) inFile = new TFile("/home/mleblanc/out/acceptance/370265/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370265.MGPy8EG_A14N_GG_bbn1_1100_5000_600.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370266) inFile = new TFile("/home/mleblanc/out/acceptance/370266/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370266.MGPy8EG_A14N_GG_bbn1_1100_5000_800.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370267) inFile = new TFile("/home/mleblanc/out/acceptance/370267/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370267.MGPy8EG_A14N_GG_bbn1_1100_5000_1000.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370268) inFile = new TFile("/home/mleblanc/out/acceptance/370268/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370268.MGPy8EG_A14N_GG_bbn1_1100_5000_1080.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370269) inFile = new TFile("/home/mleblanc/out/acceptance/370269/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370269.MGPy8EG_A14N_GG_bbn1_1200_5000_1.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370270) inFile = new TFile("/home/mleblanc/out/acceptance/370270/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370270.MGPy8EG_A14N_GG_bbn1_1200_5000_200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370271) inFile = new TFile("/home/mleblanc/out/acceptance/370271/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370271.MGPy8EG_A14N_GG_bbn1_1200_5000_400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370272) inFile = new TFile("/home/mleblanc/out/acceptance/370272/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370272.MGPy8EG_A14N_GG_bbn1_1200_5000_600.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370273) inFile = new TFile("/home/mleblanc/out/acceptance/370273/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370273.MGPy8EG_A14N_GG_bbn1_1200_5000_800.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370274) inFile = new TFile("/home/mleblanc/out/acceptance/370274/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370274.MGPy8EG_A14N_GG_bbn1_1200_5000_1000.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370275) inFile = new TFile("/home/mleblanc/out/acceptance/370275/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370275.MGPy8EG_A14N_GG_bbn1_1200_5000_1180.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370276) inFile = new TFile("/home/mleblanc/out/acceptance/370276/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370276.MGPy8EG_A14N_GG_bbn1_1300_5000_1.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370277) inFile = new TFile("/home/mleblanc/out/acceptance/370277/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370277.MGPy8EG_A14N_GG_bbn1_1300_5000_200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370278) inFile = new TFile("/home/mleblanc/out/acceptance/370278/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370278.MGPy8EG_A14N_GG_bbn1_1300_5000_400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370279) inFile = new TFile("/home/mleblanc/out/acceptance/370279/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370279.MGPy8EG_A14N_GG_bbn1_1300_5000_600.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370280) inFile = new TFile("/home/mleblanc/out/acceptance/370280/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370280.MGPy8EG_A14N_GG_bbn1_1300_5000_800.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370281) inFile = new TFile("/home/mleblanc/out/acceptance/370281/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370281.MGPy8EG_A14N_GG_bbn1_1300_5000_1000.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370282) inFile = new TFile("/home/mleblanc/out/acceptance/370282/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370282.MGPy8EG_A14N_GG_bbn1_1300_5000_1200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370283) inFile = new TFile("/home/mleblanc/out/acceptance/370283/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370283.MGPy8EG_A14N_GG_bbn1_1300_5000_1280.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370284) inFile = new TFile("/home/mleblanc/out/acceptance/370284/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370284.MGPy8EG_A14N_GG_bbn1_1400_5000_1.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370285) inFile = new TFile("/home/mleblanc/out/acceptance/370285/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370285.MGPy8EG_A14N_GG_bbn1_1400_5000_200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370286) inFile = new TFile("/home/mleblanc/out/acceptance/370286/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370286.MGPy8EG_A14N_GG_bbn1_1400_5000_400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370287) inFile = new TFile("/home/mleblanc/out/acceptance/370287/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370287.MGPy8EG_A14N_GG_bbn1_1400_5000_600.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370288) inFile = new TFile("/home/mleblanc/out/acceptance/370288/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370288.MGPy8EG_A14N_GG_bbn1_1400_5000_800.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370289) inFile = new TFile("/home/mleblanc/out/acceptance/370289/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370289.MGPy8EG_A14N_GG_bbn1_1400_5000_1000.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370290) inFile = new TFile("/home/mleblanc/out/acceptance/370290/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370290.MGPy8EG_A14N_GG_bbn1_1400_5000_1200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370291) inFile = new TFile("/home/mleblanc/out/acceptance/370291/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370291.MGPy8EG_A14N_GG_bbn1_1400_5000_1380.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370292) inFile = new TFile("/home/mleblanc/out/acceptance/370292/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370292.MGPy8EG_A14N_GG_bbn1_1500_5000_1.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370293) inFile = new TFile("/home/mleblanc/out/acceptance/370293/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370293.MGPy8EG_A14N_GG_bbn1_1500_5000_200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370294) inFile = new TFile("/home/mleblanc/out/acceptance/370294/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370294.MGPy8EG_A14N_GG_bbn1_1500_5000_400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370295) inFile = new TFile("/home/mleblanc/out/acceptance/370295/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370295.MGPy8EG_A14N_GG_bbn1_1500_5000_600.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370296) inFile = new TFile("/home/mleblanc/out/acceptance/370296/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370296.MGPy8EG_A14N_GG_bbn1_1500_5000_800.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370297) inFile = new TFile("/home/mleblanc/out/acceptance/370297/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370297.MGPy8EG_A14N_GG_bbn1_1500_5000_1000.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370298) inFile = new TFile("/home/mleblanc/out/acceptance/370298/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370298.MGPy8EG_A14N_GG_bbn1_1500_5000_1200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370299) inFile = new TFile("/home/mleblanc/out/acceptance/370299/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370299.MGPy8EG_A14N_GG_bbn1_1500_5000_1400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370300) inFile = new TFile("/home/mleblanc/out/acceptance/370300/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370300.MGPy8EG_A14N_GG_bbn1_1500_5000_1480.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370301) inFile = new TFile("/home/mleblanc/out/acceptance/370301/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370301.MGPy8EG_A14N_GG_bbn1_1600_5000_1.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370302) inFile = new TFile("/home/mleblanc/out/acceptance/370302/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370302.MGPy8EG_A14N_GG_bbn1_1600_5000_200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370303) inFile = new TFile("/home/mleblanc/out/acceptance/370303/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370303.MGPy8EG_A14N_GG_bbn1_1600_5000_400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370304) inFile = new TFile("/home/mleblanc/out/acceptance/370304/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370304.MGPy8EG_A14N_GG_bbn1_1600_5000_600.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370305) inFile = new TFile("/home/mleblanc/out/acceptance/370305/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370305.MGPy8EG_A14N_GG_bbn1_1600_5000_800.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370306) inFile = new TFile("/home/mleblanc/out/acceptance/370306/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370306.MGPy8EG_A14N_GG_bbn1_1600_5000_1000.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370307) inFile = new TFile("/home/mleblanc/out/acceptance/370307/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370307.MGPy8EG_A14N_GG_bbn1_1600_5000_1200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370308) inFile = new TFile("/home/mleblanc/out/acceptance/370308/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370308.MGPy8EG_A14N_GG_bbn1_1600_5000_1400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370309) inFile = new TFile("/home/mleblanc/out/acceptance/370309/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370309.MGPy8EG_A14N_GG_bbn1_1600_5000_1580.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370310) inFile = new TFile("/home/mleblanc/out/acceptance/370310/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370310.MGPy8EG_A14N_GG_bbn1_1700_5000_1.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370311) inFile = new TFile("/home/mleblanc/out/acceptance/370311/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370311.MGPy8EG_A14N_GG_bbn1_1700_5000_200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370312) inFile = new TFile("/home/mleblanc/out/acceptance/370312/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370312.MGPy8EG_A14N_GG_bbn1_1700_5000_400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370313) inFile = new TFile("/home/mleblanc/out/acceptance/370313/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370313.MGPy8EG_A14N_GG_bbn1_1700_5000_600.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370314) inFile = new TFile("/home/mleblanc/out/acceptance/370314/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370314.MGPy8EG_A14N_GG_bbn1_1700_5000_800.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370315) inFile = new TFile("/home/mleblanc/out/acceptance/370315/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370315.MGPy8EG_A14N_GG_bbn1_1700_5000_1000.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370316) inFile = new TFile("/home/mleblanc/out/acceptance/370316/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370316.MGPy8EG_A14N_GG_bbn1_1700_5000_1200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370317) inFile = new TFile("/home/mleblanc/out/acceptance/370317/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370317.MGPy8EG_A14N_GG_bbn1_1700_5000_1400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370318) inFile = new TFile("/home/mleblanc/out/acceptance/370318/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370318.MGPy8EG_A14N_GG_bbn1_1700_5000_1600.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370319) inFile = new TFile("/home/mleblanc/out/acceptance/370319/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370319.MGPy8EG_A14N_GG_bbn1_1700_5000_1680.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370320) inFile = new TFile("/home/mleblanc/out/acceptance/370320/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370320.MGPy8EG_A14N_GG_bbn1_1800_5000_1.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370321) inFile = new TFile("/home/mleblanc/out/acceptance/370321/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370321.MGPy8EG_A14N_GG_bbn1_1800_5000_200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370322) inFile = new TFile("/home/mleblanc/out/acceptance/370322/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370322.MGPy8EG_A14N_GG_bbn1_1800_5000_400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370323) inFile = new TFile("/home/mleblanc/out/acceptance/370323/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370323.MGPy8EG_A14N_GG_bbn1_1800_5000_600.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370324) inFile = new TFile("/home/mleblanc/out/acceptance/370324/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370324.MGPy8EG_A14N_GG_bbn1_1800_5000_800.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370325) inFile = new TFile("/home/mleblanc/out/acceptance/370325/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370325.MGPy8EG_A14N_GG_bbn1_1800_5000_1000.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370326) inFile = new TFile("/home/mleblanc/out/acceptance/370326/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370326.MGPy8EG_A14N_GG_bbn1_1800_5000_1200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370327) inFile = new TFile("/home/mleblanc/out/acceptance/370327/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370327.MGPy8EG_A14N_GG_bbn1_1800_5000_1400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370328) inFile = new TFile("/home/mleblanc/out/acceptance/370328/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370328.MGPy8EG_A14N_GG_bbn1_1800_5000_1600.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370329) inFile = new TFile("/home/mleblanc/out/acceptance/370329/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370329.MGPy8EG_A14N_GG_bbn1_1800_5000_1780.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370330) inFile = new TFile("/home/mleblanc/out/acceptance/370330/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370330.MGPy8EG_A14N_GG_bbn1_1900_5000_1.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370331) inFile = new TFile("/home/mleblanc/out/acceptance/370331/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370331.MGPy8EG_A14N_GG_bbn1_1900_5000_200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370332) inFile = new TFile("/home/mleblanc/out/acceptance/370332/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370332.MGPy8EG_A14N_GG_bbn1_1900_5000_400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370333) inFile = new TFile("/home/mleblanc/out/acceptance/370333/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370333.MGPy8EG_A14N_GG_bbn1_1900_5000_600.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370334) inFile = new TFile("/home/mleblanc/out/acceptance/370334/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370334.MGPy8EG_A14N_GG_bbn1_1900_5000_800.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370335) inFile = new TFile("/home/mleblanc/out/acceptance/370335/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370335.MGPy8EG_A14N_GG_bbn1_1900_5000_1000.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370336) inFile = new TFile("/home/mleblanc/out/acceptance/370336/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370336.MGPy8EG_A14N_GG_bbn1_1900_5000_1200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370337) inFile = new TFile("/home/mleblanc/out/acceptance/370337/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370337.MGPy8EG_A14N_GG_bbn1_1900_5000_1400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370338) inFile = new TFile("/home/mleblanc/out/acceptance/370338/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370338.MGPy8EG_A14N_GG_bbn1_1900_5000_1600.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370339) inFile = new TFile("/home/mleblanc/out/acceptance/370339/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370339.MGPy8EG_A14N_GG_bbn1_1900_5000_1800.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370340) inFile = new TFile("/home/mleblanc/out/acceptance/370340/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370340.MGPy8EG_A14N_GG_bbn1_1900_5000_1880.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370341) inFile = new TFile("/home/mleblanc/out/acceptance/370341/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370341.MGPy8EG_A14N_GG_bbn1_2000_5000_1.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370342) inFile = new TFile("/home/mleblanc/out/acceptance/370342/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370342.MGPy8EG_A14N_GG_bbn1_2000_5000_200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370343) inFile = new TFile("/home/mleblanc/out/acceptance/370343/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370343.MGPy8EG_A14N_GG_bbn1_2000_5000_400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370344) inFile = new TFile("/home/mleblanc/out/acceptance/370344/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370344.MGPy8EG_A14N_GG_bbn1_2000_5000_600.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370345) inFile = new TFile("/home/mleblanc/out/acceptance/370345/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370345.MGPy8EG_A14N_GG_bbn1_2000_5000_800.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370346) inFile = new TFile("/home/mleblanc/out/acceptance/370346/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370346.MGPy8EG_A14N_GG_bbn1_2000_5000_1000.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370347) inFile = new TFile("/home/mleblanc/out/acceptance/370347/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370347.MGPy8EG_A14N_GG_bbn1_2000_5000_1200.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370348) inFile = new TFile("/home/mleblanc/out/acceptance/370348/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370348.MGPy8EG_A14N_GG_bbn1_2000_5000_1400.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370349) inFile = new TFile("/home/mleblanc/out/acceptance/370349/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370349.MGPy8EG_A14N_GG_bbn1_2000_5000_1600.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370350) inFile = new TFile("/home/mleblanc/out/acceptance/370350/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370350.MGPy8EG_A14N_GG_bbn1_2000_5000_1800.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");
      if(dsid==370351) inFile = new TFile("/home/mleblanc/out/acceptance/370351/fetch/data-outTree/mc15_13TeV:mc15_13TeV.370351.MGPy8EG_A14N_GG_bbn1_2000_5000_1980.merge.DAOD_TRUTH1.e4050_p2482-0.root","open");

  return;
}

void getSusyMasses(Int_t dsid, Float_t &Mg, Float_t &Mn)
{
      // Gtt Grid

      if(dsid==370100){
        Mg=900.0;
        Mn=1.0;
      }
      if(dsid==370101){
        Mg=900.0;
        Mn=200.0;
      }
      if(dsid==370102){
        Mg=900.0;
        Mn=400.0;
      }
      if(dsid==370103){
        Mg=900.0;
        Mn=545.0;
      }
      if(dsid==370104){
        Mg=1000.0;
        Mn=1.0;
      }
      if(dsid==370105){
        Mg=1000.0;
        Mn=200.0;
      }
      if(dsid==370106){
        Mg=1000.0;
        Mn=400.0;
      }
      if(dsid==370107){
        Mg=1000.0;
        Mn=600.0;
      }
      if(dsid==370108){
        Mg=1000.0;
        Mn=645.0;
      }
      if(dsid==370109){
        Mg=1100.0;
        Mn=1.0;
      }
      if(dsid==370110){
        Mg=1100.0;
        Mn=200.0;
      }
     if(dsid==370111){
        Mg=1100.0;
        Mn=400.0;
      }
      if(dsid==370112){
        Mg=1100.0;
        Mn=600.0;
      }
      if(dsid==370113){
        Mg=1100.0;
        Mn=745.0;
      }
      if(dsid==370114){
        Mg=1200.0;
        Mn=1.0;
      }
      if(dsid==370115){
        Mg=1200.0;
        Mn=100.0;
      }
      if(dsid==370116){
        Mg=1200.0;
        Mn=200.0;
      }
      if(dsid==370117){
        Mg=1200.0;
        Mn=400.0;
      }
      if(dsid==370118){
        Mg=1200.0;
        Mn=600.0;
      }
      if(dsid==370119){
        Mg=1200.0;
        Mn=700.0;
      }
      if(dsid==370120){
        Mg=1200.0;
        Mn=800.0;
      }
      if(dsid==370121){
        Mg=1200.0;
        Mn=845.0;
      }
      if(dsid==370122){
        Mg=1200.0;
        Mn=855.0;
      }
      if(dsid==370123){
        Mg=1300.0;
        Mn=1.0;
      }
      if(dsid==370124){
        Mg=1300.0;
        Mn=200.0;
      }
      if(dsid==370125){
        Mg=1300.0;
        Mn=400.0;
      }
      if(dsid==370126){
        Mg=1300.0;
        Mn=600.0;
      }
      if(dsid==370127){
        Mg=1300.0;
        Mn=800.0;
      }
      if(dsid==370128){
        Mg=1300.0;
        Mn=945.0;
      }
      if(dsid==370129){
        Mg=1400.0;
        Mn=1.0;
      }
      if(dsid==370130){
        Mg=1400.0;
        Mn=100.0;
      }
      if(dsid==370131){
        Mg=1400.0;
        Mn=200.0;
      }
      if(dsid==370132){
        Mg=1400.0;
        Mn=400.0;
      }
      if(dsid==370133){
        Mg=1400.0;
        Mn=600.0;
      }
      if(dsid==370134){
        Mg=1400.0;
        Mn=800.0;
      }
      if(dsid==370135){
        Mg=1400.0;
        Mn=1000.0;
      }
      if(dsid==370136){
        Mg=1400.0;
        Mn=1045.0;
      }
      if(dsid==370137){
        Mg=1500.0;
        Mn=1.0;
      }
      if(dsid==370138){
        Mg=1500.0;
        Mn=200.0;
      }
      if(dsid==370139){
        Mg=1500.0;
        Mn=400.0;
      }
      if(dsid==370140){
        Mg=1500.0;
        Mn=600.0;
      }
      if(dsid==370141){
        Mg=1500.0;
        Mn=800.0;
      }
      if(dsid==370142){
        Mg=1500.0;
        Mn=1000.0;
      }
      if(dsid==370143){
        Mg=1500.0;
        Mn=1145.0;
      }
      if(dsid==370137){
        Mg=1500.0;
        Mn=1.0;
      }
      if(dsid==370138){
        Mg=1500.0;
        Mn=200.0;
      }
      if(dsid==370139){
        Mg=1500.0;
        Mn=400.0;
      }
      if(dsid==370140){
        Mg=1500.0;
        Mn=600.0;
      }
      if(dsid==370141){
        Mg=1500.0;
        Mn=800.0;
      }
      if(dsid==370142){
        Mg=1500.0;
        Mn=1000.0;
      }
      if(dsid==370143){
        Mg=1500.0;
        Mn=1145.0;
      }
      if(dsid==370144){
        Mg=1600.0;
        Mn=1.0;
      }
      if(dsid==370145){
        Mg=1600.0;
        Mn=200.0;
      }
      if(dsid==370146){
        Mg=1600.0;
        Mn=400.0;
      }
      if(dsid==370147){
        Mg=1600.0;
        Mn=600.0;
      }
      if(dsid==370148){
        Mg=1600.0;
        Mn=800.0;
      }
      if(dsid==370149){
        Mg=1600.0;
        Mn=1000.0;
      }
      if(dsid==370150){
        Mg=1600.0;
        Mn=1200.0;
      }
      if(dsid==370151){
        Mg=1600.0;
        Mn=1245.0;
      }
      if(dsid==370152){
        Mg=1700.0;
        Mn=1.0;
      }
      if(dsid==370153){
        Mg=1700.0;
        Mn=200.0;
      }
      if(dsid==370154){
        Mg=1700.0;
        Mn=400.0;
      }
      if(dsid==370155){
        Mg=1700.0;
        Mn=600.0;
      }
      if(dsid==370156){
        Mg=1700.0;
        Mn=800.0;
      }
      if(dsid==370157){
        Mg=1700.0;
        Mn=1000.0;
      }
      if(dsid==370158){
        Mg=1700.0;
        Mn=1200.0;
      }
      if(dsid==370159){
        Mg=1700.0;
        Mn=1345.0;
      }
      if(dsid==370160){
        Mg=1800.0;
        Mn=1.0;
      }
      if(dsid==370161){
        Mg=1800.0;
        Mn=200.0;
      }
      if(dsid==370162){
        Mg=1800.0;
        Mn=400.0;
      }
      if(dsid==370163){
        Mg=1800.0;
        Mn=600.0;
      }
      if(dsid==370164){
        Mg=1800.0;
        Mn=800.0;
      }
      if(dsid==370165){
        Mg=1800.0;
        Mn=1000.0;
      }
      if(dsid==370166){
        Mg=1800.0;
        Mn=1200.0;
      }
      if(dsid==370167){
        Mg=1800.0;
        Mn=1400.0;
      }
      if(dsid==370168){
        Mg=1800.0;
        Mn=1445.0;
      }
      if(dsid==370169){
        Mg=1900.0;
        Mn=1.0;
      }
      if(dsid==370170){
        Mg=1900.0;
        Mn=200.0;
      }
      if(dsid==370171){
        Mg=1900.0;
        Mn=400.0;
      }
      if(dsid==370172){
        Mg=1900.0;
        Mn=600.0;
      }
      if(dsid==370173){
        Mg=1900.0;
        Mn=800.0;
      }
      if(dsid==370174){
        Mg=1900.0;
        Mn=1000.0;
      }
      if(dsid==370175){
        Mg=1900.0;
        Mn=1200.0;
      }
      if(dsid==370176){
        Mg=1900.0;
        Mn=1400.0;
      }
      if(dsid==370177){
        Mg=1900.0;
        Mn=1545.0;
      }
      if(dsid==370178){
        Mg=2000.0;
        Mn=1.0;
      }
      if(dsid==370179){
        Mg=2000.0;
        Mn=200.0;
      }
      if(dsid==370180){
        Mg=2000.0;
        Mn=400.0;
      }
      if(dsid==370181){
        Mg=2000.0;
        Mn=600.0;
      }
      if(dsid==370182){
        Mg=2000.0;
        Mn=800.0;
      }
      if(dsid==370183){
        Mg=2000.0;
        Mn=1000.0;
      }
      if(dsid==370184){
        Mg=2000.0;
        Mn=1200.0;
      }
      if(dsid==370185){
        Mg=2000.0;
        Mn=1400.0;
      }
      if(dsid==370186){
        Mg=2000.0;
        Mn=1600.0;
      }
      if(dsid==370187){
        Mg=2000.0;
        Mn=1645.0;
      }

      // Gbb Grid
      if(dsid==370250){
        Mg=900.0;
        Mn=1.0;
      }
      if(dsid==370251){
        Mg=900.0;
        Mn=200.0;
      }
      if(dsid==370252){
        Mg=900.0;
        Mn=400.0;
      }
      if(dsid==370253){
        Mg=900.0;
        Mn=600.0;
      }
      if(dsid==370254){
        Mg=900.0;
        Mn=800.0;
      }
      if(dsid==370255){
        Mg=900.0;
        Mn=880.0;
      }
      if(dsid==370256){
        Mg=1000.0;
        Mn=1.0;
      }
      if(dsid==370257){
        Mg=1000.0;
        Mn=200.0;
      }
      if(dsid==370258){
        Mg=1000.0;
        Mn=400.0;
      }
      if(dsid==370259){
        Mg=1000.0;
        Mn=600.0;
      }
      if(dsid==370260){
        Mg=1000.0;
        Mn=800.0;
      }
      if(dsid==370261){
        Mg=1000.0;
        Mn=980.0;
      }
      if(dsid==370262){
        Mg=1100.0;
        Mn=1.0;
      }
      if(dsid==370263){
        Mg=1100.0;
        Mn=200.0;
      }
      if(dsid==370264){
        Mg=1100.0;
        Mn=400.0;
      }
      if(dsid==370265){
        Mg=1100.0;
        Mn=600.0;
      }
      if(dsid==370266){
        Mg=1100.0;
        Mn=800.0;
      }
      if(dsid==370267){
        Mg=1100.0;
        Mn=1000.0;
      }
      if(dsid==370268){
        Mg=1100.0;
        Mn=1080.0;
      }
      if(dsid==370269){
        Mg=1200.0;
        Mn=1.0;
      }
      if(dsid==370270){
        Mg=1200.0;
        Mn=200.0;
      }
      if(dsid==370271){
        Mg=1200.0;
        Mn=400.0;
      }
      if(dsid==370272){
        Mg=1200.0;
        Mn=600.0;
      }
      if(dsid==370273){
        Mg=1200.0;
        Mn=800.0;
      }
      if(dsid==370274){
        Mg=1200.0;
        Mn=1000.0;
      }
      if(dsid==370275){
        Mg=1200.0;
        Mn=1180.0;
      }
      if(dsid==370276){
        Mg=1300.0;
        Mn=1.0;
      }
      if(dsid==370277){
        Mg=1300.0;
        Mn=200.0;
      }
      if(dsid==370278){
        Mg=1300.0;
        Mn=400.0;
      }
      if(dsid==370279){
        Mg=1300.0;
        Mn=600.0;
      }
      if(dsid==370280){
        Mg=1300.0;
        Mn=800.0;
      }
      if(dsid==370281){
        Mg=1300.0;
        Mn=1000.0;
      }
      if(dsid==370282){
        Mg=1300.0;
        Mn=1200.0;
      }
      if(dsid==370283){
        Mg=1300.0;
        Mn=1280.0;
      }
      if(dsid==370284){
        Mg=1400.0;
        Mn=1.0;
      }
      if(dsid==370285){
        Mg=1400.0;
        Mn=200.0;
      }
      if(dsid==370286){
        Mg=1400.0;
        Mn=400.0;
      }
      if(dsid==370287){
        Mg=1400.0;
        Mn=600.0;
      }
      if(dsid==370288){
        Mg=1400.0;
        Mn=800.0;
      }
      if(dsid==370289){
        Mg=1400.0;
        Mn=1000.0;
      }
      if(dsid==370290){
        Mg=1400.0;
        Mn=1200.0;
      }
      if(dsid==370291){
        Mg=1400.0;
        Mn=1380.0;
      }
      if(dsid==370292){
        Mg=1500.0;
        Mn=1.0;
      }
      if(dsid==370293){
        Mg=1500.0;
        Mn=200.0;
      }
      if(dsid==370294){
        Mg=1500.0;
        Mn=400.0;
      }
      if(dsid==370295){
        Mg=1500.0;
        Mn=600.0;
      }
      if(dsid==370296){
        Mg=1500.0;
        Mn=800.0;
      }
      if(dsid==370297){
        Mg=1500.0;
        Mn=1000.0;
      }
      if(dsid==370298){
        Mg=1500.0;
        Mn=1200.0;
      }
      if(dsid==370299){
        Mg=1500.0;
        Mn=1400.0;
      }
      if(dsid==370300){
        Mg=1500.0;
        Mn=1480.0;
      }
      if(dsid==370301){
        Mg=1600.0;
        Mn=1.0;
      }
      if(dsid==370302){
        Mg=1600.0;
        Mn=200.0;
      }
      if(dsid==370303){
        Mg=1600.0;
        Mn=400.0;
      }
      if(dsid==370304){
        Mg=1600.0;
        Mn=600.0;
      }
      if(dsid==370305){
        Mg=1600.0;
        Mn=800.0;
      }
      if(dsid==370306){
        Mg=1600.0;
        Mn=1000.0;
      }
      if(dsid==370307){
        Mg=1600.0;
        Mn=1200.0;
      }
      if(dsid==370308){
        Mg=1600.0;
        Mn=1400.0;
      }
      if(dsid==370309){
        Mg=1600.0;
        Mn=1580.0;
      }
      if(dsid==370310){
        Mg=1700.0;
        Mn=1.0;
      }
      if(dsid==370311){
        Mg=1700.0;
        Mn=200.0;
      }
      if(dsid==370312){
        Mg=1700.0;
        Mn=400.0;
      }
      if(dsid==370313){
        Mg=1700.0;
        Mn=600.0;
      }
      if(dsid==370314){
        Mg=1700.0;
        Mn=800.0;
      }
      if(dsid==370315){
        Mg=1700.0;
        Mn=1000.0;
      }
      if(dsid==370316){
        Mg=1700.0;
        Mn=1200.0;
      }
      if(dsid==370317){
        Mg=1700.0;
        Mn=1400.0;
      }
      if(dsid==370318){
        Mg=1700.0;
        Mn=1600.0;
      }
      if(dsid==370319){
        Mg=1700.0;
        Mn=1680.0;
      }
      if(dsid==370320){
        Mg=1800.0;
        Mn=1.0;
      }
      if(dsid==370321){
        Mg=1800.0;
        Mn=200.0;
      }
      if(dsid==370322){
        Mg=1800.0;
        Mn=400.0;
      }
      if(dsid==370323){
        Mg=1800.0;
        Mn=600.0;
      }
      if(dsid==370324){
        Mg=1800.0;
        Mn=800.0;
      }
      if(dsid==370325){
        Mg=1800.0;
        Mn=1000.0;
      }
      if(dsid==370326){
        Mg=1800.0;
        Mn=1200.0;
      }
      if(dsid==370327){
        Mg=1800.0;
        Mn=1400.0;
      }
      if(dsid==370328){
        Mg=1800.0;
        Mn=1600.0;
      }
      if(dsid==370329){
        Mg=1800.0;
        Mn=1780.0;
      }
      if(dsid==370330){
        Mg=1900.0;
        Mn=1.0;
      }
      if(dsid==370331){
        Mg=1900.0;
        Mn=200.0;
      }
      if(dsid==370332){
        Mg=1900.0;
        Mn=400.0;
      }
      if(dsid==370333){
        Mg=1900.0;
        Mn=600.0;
      }
      if(dsid==370334){
        Mg=1900.0;
        Mn=800.0;
      }
      if(dsid==370335){
        Mg=1900.0;
        Mn=1000.0;
      }
      if(dsid==370336){
        Mg=1900.0;
        Mn=1200.0;
      }
      if(dsid==370337){
        Mg=1900.0;
        Mn=1400.0;
      }
      if(dsid==370338){
        Mg=1900.0;
        Mn=1600.0;
      }
      if(dsid==370339){
        Mg=1900.0;
        Mn=1800.0;
      }
      if(dsid==370340){
        Mg=1900.0;
        Mn=1880.0;
      }
      if(dsid==370341){
        Mg=2000.0;
        Mn=1.0;
      }
      if(dsid==370342){
        Mg=2000.0;
        Mn=200.0;
      }
      if(dsid==370343){
        Mg=2000.0;
        Mn=400.0;
      }
      if(dsid==370344){
        Mg=2000.0;
        Mn=600.0;
      }
      if(dsid==370345){
        Mg=2000.0;
        Mn=800.0;
      }
      if(dsid==370346){
        Mg=2000.0;
        Mn=1000.0;
      }
      if(dsid==370347){
        Mg=2000.0;
        Mn=1200.0;
      }
      if(dsid==370348){
        Mg=2000.0;
        Mn=1400.0;
      }
      if(dsid==370349){
        Mg=2000.0;
        Mn=1600.0;
      }
      if(dsid==370350){
        Mg=2000.0;
        Mn=1800.0;
      }
      if(dsid==370351){
        Mg=2000.0;
        Mn=1980.0;
      }

  return;
}
