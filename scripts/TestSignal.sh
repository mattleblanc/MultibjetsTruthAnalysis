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


# 410004
python MultibjetsTruthAnalysis/scripts/Run.py \
    --submitDir=/home/mleblanc/out/TestSignal/370102/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370102.MGPy8EG_A14N_GG_ttn1_900_5000_400.merge.DAOD_SUSY10.e4049_s2608_r6765_r6282_p2411/" \
    --driver=direct \
    --doRcJets=1 \
    --doAK10Jets=0 \
    --debug=1 \
    --doTRF=0 \
    --process="testMLB00"

exit 0
