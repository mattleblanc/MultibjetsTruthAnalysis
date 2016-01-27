import os
import glob
from sys import argv

#import rootpy
import ROOT
#from ROOT import TTree, TFile, TH1, AddressOf, gROOT

ROOT.gROOT.Macro('$ROOTCOREDIR/scripts/load_packages.C')
ROOT.xAOD.Init().ignore()

files = argv[1].split(',')

chain = ROOT.TChain('CollectionTree')
for f in files:
    print "Adding file",f," to chain ..."
    chain.Add(f)

tree = ROOT.xAOD.MakeTransientTree(chain, ROOT.xAOD.TEvent.kBranchAccess)
print tree

# output
f = ROOT.TFile("gttgbb2k15_acc_out.root","recreate")

#with root_open('acc_out.root') as output:

h_acceptance = ROOT.TH1F("acceptance","",1, 0, 1)
h_dsid=ROOT.TH1F("dsid","",1,0,1);

nevents = 0

for ievt in xrange(tree.GetEntries()):
    tree.GetEntry(ievt)

    dsid = tree.EventInfo.mcChannelNumber()

    electrons = tree.TruthElectrons
    muons = tree.TruthMuons
    
    selected_electrons = filter(lambda el: el.pt() > 20000.0, electrons)
    selected_muons = filter(lambda mu: mu.pt() > 20000.0, muons)
    
    if len(selected_muons) + len(selected_electrons) < 1:
        continue
    nevents += 1
    
    if nevents % 1000 == 0:
        print nevents
        
print "Total number of events passing: "
print nevents
    
print "Acceptance is: "
acceptance = nevents/float(tree.GetEntries())
print acceptance

h_acceptance.SetBinContent(1,acceptance)
h_dsid.SetBinContent(1,dsid)

f.Write()
