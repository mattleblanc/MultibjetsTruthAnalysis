#!/bin/bash

#login:susyGtt mleblanc$ python MultibjetsTruthAnalysis/scripts/Run.py -h
#Usage: Run.py [options]

#Options:
#  -h, --help            show this help message and exit
#  --submitDir=SUBMITDIR
#                        dir to store the output
#  --inputDS=INPUTDS     input DS from DQ2
#  --driver=DRIVER       select where to run
#  --nevents=NEVENTS     number of events to process for all the datasets
#  --skip-events=SKIP_EVENTS
#                        skip the first n events
#  -w, --overwrite       overwrite previous submitDir
#  --doxAOD=DOXAOD       Make xAOD output [0/1]
#  --doRcJets=DORCJETS   DoRcJets flag [0/1]
#  --doAK10Jets=DOAK10JETS
#                        DoAK10Jets flag [0/1]
#  --debug=DEBUG         Debug mode: print extra stuff [0/1]
#  --doTRF=DOTRF         TRF flag [0/1]
#  --process=PROCESS     name of the process added to the output grid jobs


# nominal
python MultibjetsTruthAnalysis/scripts/Run.py \
    --submitDir=/home/mleblanc/out/cutflow/410000/ \
    --inputDS="mc15_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.DAOD_TRUTH1.e3698_p2375/" \
    --driver=condor \
    --doRcJets=1 \
    --doAK10Jets=0 \
    --debug=1 \
    --doTRF=0 \
    --nevents=5000 \
    --process="testMLB00"

#410003
python MultibjetsTruthAnalysis/scripts/Run.py \
    --submitDir=/home/mleblanc/out/cutflow/410003/ \
    --inputDS="mc15_13TeV:mc15_13TeV.410003.aMcAtNloHerwigppEvtGen_ttbar_nonallhad.merge.DAOD_TRUTH1.e3964_p2425/" \
    --driver=condor \
    --doRcJets=1 \
    --doAK10Jets=0 \
    --debug=1 \
    --doTRF=0 \
    --nevents=5000 \
    --process="testMLB00"

#410004
python MultibjetsTruthAnalysis/scripts/Run.py \
    --submitDir=/home/mleblanc/out/cutflow/410004/ \
    --inputDS="mc15_13TeV:mc15_13TeV.410004.aMcAtNloHerwigppEvtGen_ttbar_nonallhad.merge.DAOD_TRUTH1.e3964_p2425/" \
    --driver=condor \
    --doRcJets=1 \
    --doAK10Jets=0 \
    --debug=1 \
    --doTRF=0 \
    --nevents=5000 \
    --process="testMLB00"

exit 0
