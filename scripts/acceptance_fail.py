# Script to quickly calculate acceptances from SUSY signal files
# Matt LeBlanc & Quentin Buat
# <matt.leblanc@cern.ch>
# 7 Jan 2015

import os
import logging
import glob

import ROOT
ROOT.gROOT.Macro('$ROOTCOREDIR/scripts/load_packages.C')
ROOT.xAOD.Init().ignore()

logging.info("creating new sample handler")
sh_all = ROOT.SH.SampleHandler()
#ROOT.SH.scanDQ2 (sh_all, "mc15_13TeV.370102.MGPy8EG_A14N_GG_ttn1_900_5000_400.merge.DAOD_SUSY10.e4049_s2608_r6765_r6282_p2452/");

#ROOT.SH.scanDQ2(sh_all, "root://fax.mwt2.org:1094//atlas/rucio/mc15_13TeV:DAOD_SUSY10.07108541._000002.pool.root.1")


#ROOT.SH.scanDir(sh_all, "/home/mleblanc/input/");
#ROOT.SH.scanDQ2(sh_all,"root://fax.mwt2.org:1094//atlas/rucio/mc15_13TeV:DAOD_SUSY10.07108541._000001.pool.root.1");
#ROOT.SH.scanDQ2(sh_all,"root://fax.mwt2.org:1094//atlas/rucio/mc15_13TeV:DAOD_SUSY10.07108541._000002.pool.root.1");

ROOT.SH.addGrid(sh_all,"mc15_13TeV:mc15_13TeV.370102.MGPy8EG_A14N_GG_ttn1_900_5000_400.merge.DAOD_SUSY10.e4049_s2608_r6765_r6282_p2452")

sh_all.printContent()

for sample in sh_all:
    #chain = sample.makeTChain()

#    tree = ROOT.xAOD.MakeTransientTree(chain, ROOT.xAOD.TEvent.kBranchAccess)

    nevents = 0
#    for ifile in xrange(sample.numFiles()):

    print sample.fileName()
    f = ROOT.TFile.Open( sample.fileName(), "READ" );
    tree = ROOT.xAOD.MakeTransientTree(f)
    print tree
    tree.Show()
        
        
    nevents = 0
    for iev in xrange(tree.GetEntries()):
        tree.GetEntry(iev)
        
        electrons = tree.TruthElectrons
        muons = tree.TruthMuons

        selected_electrons = filter(lambda el: el.pt() > 10000.0 and abs(el.eta()) < 4.0, electrons)
        selected_muons = filter(lambda mu: mu.pt() > 10000.0 and abs(mu.eta()) < 4.0, muons)

        if len(selected_muons)+len(selected_electrons) < 1:
            continue
        nevents += 1

        if nevents % 1000 == 0:
            print nevents
            
        if nevents>10000:
            break

    print "Total number of events passing: " 
    print nevents

    print "Acceptance is: "
    print nevents/float(tree.GetEntries())
