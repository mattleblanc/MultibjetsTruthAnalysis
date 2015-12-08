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

#python MultibjetsTruthAnalysis/scripts/Run.py \
#    --submitDir=/home/mleblanc/out/truthOut/410000/ \
#    --inputDS="mc15_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.DAOD_TRUTH1.e3698_p2375/" \
#    --driver=condor \
#    --doRcJets=1 \
#    --doAK10Jets=0 \
#    --debug=1 \
#    --doTRF=0 \
#    --process="testMLB00"

#python MultibjetsTruthAnalysis/scripts/Run.py \
#    --submitDir=/home/mleblanc/out/truthOut/410001/ \
#    --inputDS="mc15_13TeV:mc15_13TeV.410001.PowhegPythiaEvtGen_P2012radHi_ttbar_hdamp345_down_nonallhad.merge.DAOD_TRUTH1.e3783_p2425/" \
#    --driver=condor \
#    --doRcJets=1 \
#    --doAK10Jets=0 \
#    --debug=1 \
#    --doTRF=0 \
#    --process="testMLB00"

#python MultibjetsTruthAnalysis/scripts/Run.py \
#    --submitDir=/home/mleblanc/out/truthOut/410002/ \
#    --inputDS="mc15_13TeV:mc15_13TeV.410002.PowhegPythiaEvtGen_P2012radLo_ttbar_hdamp172_up_nonallhad.merge.DAOD_TRUTH1.e3783_p2425/" \
#    --driver=condor \
#    --doRcJets=1 \
#    --doAK10Jets=0 \
#    --debug=1 \
#    --doTRF=0 \
#    --process="testMLB00"

#python MultibjetsTruthAnalysis/scripts/Run.py \
#    --submitDir=/home/mleblanc/out/truthOut/410003/ \
#    --inputDS="mc15_13TeV:mc15_13TeV.410003.aMcAtNloHerwigppEvtGen_ttbar_nonallhad.merge.DAOD_TRUTH1.e3964_p2425/" \
#    --driver=condor \
#    --doRcJets=1 \
#    --doAK10Jets=0 \
#    --debug=1 \
#    --doTRF=0 \
#    --process="testMLB00"

#python MultibjetsTruthAnalysis/scripts/Run.py \
#    --submitDir=/home/mleblanc/out/truthOut/410004/ \
#    --inputDS="mc15_13TeV:mc15_13TeV.410004.PowhegHerwigppEvtGen_UEEE5_ttbar_hdamp172p5_nonallhad.merge.DAOD_TRUTH1.e3836_p2425/" \
#    --driver=condor \
#    --doRcJets=1 \
#    --doAK10Jets=0 \
#    --debug=1 \
#    --doTRF=0 \
#    --process="testMLB00"

#python MultibjetsTruthAnalysis/scripts/Run.py \
#    --submitDir=/home/mleblanc/out/truthOut/410006/ \
#    --inputDS="mc15_13TeV:mc15_13TeV.410006.PowhegPythia8EvtGen_A14_ttbar_hdamp172p5_nonallhad.merge.DAOD_TRUTH1.e3836_p2425/" \
#    --driver=condor \
#    --doRcJets=1 \
#    --doAK10Jets=0 \
#    --debug=1 \
#    --doTRF=0 \
#    --process="testMLB00"

#407032
python MultibjetsTruthAnalysis/scripts/Run.py \
    --submitDir=/home/mleblanc/out/trf/407032/ \
    --inputDS="mc15_13TeV:mc15_13TeV.407032.PhPyEG_CT10_P2012radHiC6L1_ttbarMET200_hdamp345_down_nonAH.merge.DAOD_TRUTH1.e4505_p2436/" \
    --driver=condor \
    --doRcJets=1 \
    --doAK10Jets=0 \
    --debug=1 \
    --doTRF=0 \
    --process="testMLB00"

#407036    
python MultibjetsTruthAnalysis/scripts/Run.py \
    --submitDir=/home/mleblanc/out/trf/407036/ \
    --inputDS="mc15_13TeV:mc15_13TeV.407036.PhPyEG_CT10_P2012radLoC6L1_ttbarMET200_hdamp172_up_nonAH.merge.DAOD_TRUTH1.e4505_p2436/" \
    --driver=condor \
    --doRcJets=1 \
    --doAK10Jets=0 \
    --debug=1 \
    --doTRF=0 \
    --process="testMLB00"

#407012
python MultibjetsTruthAnalysis/scripts/Run.py \
    --submitDir=/home/mleblanc/out/trf/407012/ \
    --inputDS="mc15_13TeV:mc15_13TeV.407012.PowhegPythiaEvtGen_P2012CT10_ttbarMET200_hdamp172p5_nonAH.merge.DAOD_TRUTH1.e4023_p2436/" \
    --driver=condor \
    --doRcJets=1 \
    --doAK10Jets=0 \
    --debug=1 \
    --doTRF=0 \
    --process="testMLB00"

#407040
python MultibjetsTruthAnalysis/scripts/Run.py \
    --submitDir=/home/mleblanc/out/trf/407040/ \
    --inputDS="mc15_13TeV:mc15_13TeV.407040.PhHppEG_CT10_UE5C6L1_ttbarMET200_hdamp172p5_nonAH.merge.DAOD_TRUTH1.e4497_p2436/" \
    --driver=condor \
    --doRcJets=1 \
    --doAK10Jets=0 \
    --debug=1 \
    --doTRF=0 \
    --process="testMLB00"

#407044
python MultibjetsTruthAnalysis/scripts/Run.py \
    --submitDir=/home/mleblanc/out/trf/407044/ \
    --inputDS="mc15_13TeV:mc15_13TeV.407044.PhPy8EG_CT10_A14N23LO_ttbarMET200_hdamp172p5_nonAH.merge.DAOD_TRUTH1.e4497_p2436/" \
    --driver=condor \
    --doRcJets=1 \
    --doAK10Jets=0 \
    --debug=1 \
    --doTRF=0 \
    --process="testMLB00"

exit 0
