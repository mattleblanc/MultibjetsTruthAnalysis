import os
import glob
from sys import argv

import ROOT

ROOT.gROOT.Macro('$ROOTCOREDIR/scripts/load_packages.C')
ROOT.xAOD.Init().ignore()

#files = [
#    'root://fax.mwt2.org:1094//atlas/rucio/mc15_13TeV:DAOD_SUSY10.07108541._000001.pool.root.1',
#    'root://fax.mwt2.org:1094//atlas/rucio/mc15_13TeV:DAOD_SUSY10.07108541._000002.pool.root.1']

#inlist = argv
#files = inlist.split(',')

files = argv[1].split(',')

chain = ROOT.TChain('CollectionTree')
for f in files:
    print "Adding file",f," to chain ..."
    chain.Add(f)

tree = ROOT.xAOD.MakeTransientTree(chain, ROOT.xAOD.TEvent.kBranchAccess)
print tree

nevents = 0
for event in tree:

    electrons = tree.Electrons
    muons = tree.Muons
    
    selected_electrons = filter(lambda el: el.pt() > 10000.0 and abs(el.eta()) < 4.0, electrons)
    selected_muons = filter(lambda mu: mu.pt() > 10000.0 and abs(mu.eta()) < 4.0, muons)
    
    #if len(selected_muons)+len(selected_electrons) < 1:
    if len(selected_muons) + len(selected_electrons) < 1:
        continue
    nevents += 1

    if nevents % 1000 == 0:
        print nevents

print "Total number of events passing: "
print nevents

print "Acceptance is: "
print nevents/float(tree.GetEntries())

