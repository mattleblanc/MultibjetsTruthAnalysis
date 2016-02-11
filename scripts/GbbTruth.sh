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

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370263/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370263.MGPy8EG_A14N_GG_bbn1_1100_5000_200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370340/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370340.MGPy8EG_A14N_GG_bbn1_1900_5000_1880.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370278/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370278.MGPy8EG_A14N_GG_bbn1_1300_5000_400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370280/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370280.MGPy8EG_A14N_GG_bbn1_1300_5000_800.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370312/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370312.MGPy8EG_A14N_GG_bbn1_1700_5000_400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370343/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370343.MGPy8EG_A14N_GG_bbn1_2000_5000_400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370282/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370282.MGPy8EG_A14N_GG_bbn1_1300_5000_1200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370301/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370301.MGPy8EG_A14N_GG_bbn1_1600_5000_1.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370341/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370341.MGPy8EG_A14N_GG_bbn1_2000_5000_1.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370299/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370299.MGPy8EG_A14N_GG_bbn1_1500_5000_1400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370262/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370262.MGPy8EG_A14N_GG_bbn1_1100_5000_1.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370300/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370300.MGPy8EG_A14N_GG_bbn1_1500_5000_1480.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370265/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370265.MGPy8EG_A14N_GG_bbn1_1100_5000_600.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370296/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370296.MGPy8EG_A14N_GG_bbn1_1500_5000_800.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370319/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370319.MGPy8EG_A14N_GG_bbn1_1700_5000_1680.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370314/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370314.MGPy8EG_A14N_GG_bbn1_1700_5000_800.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370258/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370258.MGPy8EG_A14N_GG_bbn1_1000_5000_400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370257/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370257.MGPy8EG_A14N_GG_bbn1_1000_5000_200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370310/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370310.MGPy8EG_A14N_GG_bbn1_1700_5000_1.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370252/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370252.MGPy8EG_A14N_GG_bbn1_900_5000_400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370337/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370337.MGPy8EG_A14N_GG_bbn1_1900_5000_1400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370287/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370287.MGPy8EG_A14N_GG_bbn1_1400_5000_600.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370290/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370290.MGPy8EG_A14N_GG_bbn1_1400_5000_1200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370294/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370294.MGPy8EG_A14N_GG_bbn1_1500_5000_400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370285/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370285.MGPy8EG_A14N_GG_bbn1_1400_5000_200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370345/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370345.MGPy8EG_A14N_GG_bbn1_2000_5000_800.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370273/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370273.MGPy8EG_A14N_GG_bbn1_1200_5000_800.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370268/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370268.MGPy8EG_A14N_GG_bbn1_1100_5000_1080.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370254/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370254.MGPy8EG_A14N_GG_bbn1_900_5000_800.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370277/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370277.MGPy8EG_A14N_GG_bbn1_1300_5000_200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370275/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370275.MGPy8EG_A14N_GG_bbn1_1200_5000_1180.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370320/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370320.MGPy8EG_A14N_GG_bbn1_1800_5000_1.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370293/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370293.MGPy8EG_A14N_GG_bbn1_1500_5000_200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370253/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370253.MGPy8EG_A14N_GG_bbn1_900_5000_600.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370324/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370324.MGPy8EG_A14N_GG_bbn1_1800_5000_800.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370342/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370342.MGPy8EG_A14N_GG_bbn1_2000_5000_200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370271/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370271.MGPy8EG_A14N_GG_bbn1_1200_5000_400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370260/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370260.MGPy8EG_A14N_GG_bbn1_1000_5000_800.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370321/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370321.MGPy8EG_A14N_GG_bbn1_1800_5000_200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370284/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370284.MGPy8EG_A14N_GG_bbn1_1400_5000_1.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370315/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370315.MGPy8EG_A14N_GG_bbn1_1700_5000_1000.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370286/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370286.MGPy8EG_A14N_GG_bbn1_1400_5000_400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370348/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370348.MGPy8EG_A14N_GG_bbn1_2000_5000_1400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370292/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370292.MGPy8EG_A14N_GG_bbn1_1500_5000_1.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370332/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370332.MGPy8EG_A14N_GG_bbn1_1900_5000_400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370279/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370279.MGPy8EG_A14N_GG_bbn1_1300_5000_600.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370329/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370329.MGPy8EG_A14N_GG_bbn1_1800_5000_1780.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370316/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370316.MGPy8EG_A14N_GG_bbn1_1700_5000_1200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370308/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370308.MGPy8EG_A14N_GG_bbn1_1600_5000_1400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370256/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370256.MGPy8EG_A14N_GG_bbn1_1000_5000_1.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370325/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370325.MGPy8EG_A14N_GG_bbn1_1800_5000_1000.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370317/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370317.MGPy8EG_A14N_GG_bbn1_1700_5000_1400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370336/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370336.MGPy8EG_A14N_GG_bbn1_1900_5000_1200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370291/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370291.MGPy8EG_A14N_GG_bbn1_1400_5000_1380.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370335/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370335.MGPy8EG_A14N_GG_bbn1_1900_5000_1000.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370338/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370338.MGPy8EG_A14N_GG_bbn1_1900_5000_1600.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370255/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370255.MGPy8EG_A14N_GG_bbn1_900_5000_880.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370346/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370346.MGPy8EG_A14N_GG_bbn1_2000_5000_1000.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370297/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370297.MGPy8EG_A14N_GG_bbn1_1500_5000_1000.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370266/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370266.MGPy8EG_A14N_GG_bbn1_1100_5000_800.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370261/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370261.MGPy8EG_A14N_GG_bbn1_1000_5000_980.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370274/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370274.MGPy8EG_A14N_GG_bbn1_1200_5000_1000.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370326/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370326.MGPy8EG_A14N_GG_bbn1_1800_5000_1200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370350/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370350.MGPy8EG_A14N_GG_bbn1_2000_5000_1800.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370327/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370327.MGPy8EG_A14N_GG_bbn1_1800_5000_1400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370323/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370323.MGPy8EG_A14N_GG_bbn1_1800_5000_600.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370288/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370288.MGPy8EG_A14N_GG_bbn1_1400_5000_800.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370333/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370333.MGPy8EG_A14N_GG_bbn1_1900_5000_600.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370328/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370328.MGPy8EG_A14N_GG_bbn1_1800_5000_1600.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370251/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370251.MGPy8EG_A14N_GG_bbn1_900_5000_200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370303/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370303.MGPy8EG_A14N_GG_bbn1_1600_5000_400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370331/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370331.MGPy8EG_A14N_GG_bbn1_1900_5000_200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370259/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370259.MGPy8EG_A14N_GG_bbn1_1000_5000_600.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370322/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370322.MGPy8EG_A14N_GG_bbn1_1800_5000_400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370269/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370269.MGPy8EG_A14N_GG_bbn1_1200_5000_1.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370334/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370334.MGPy8EG_A14N_GG_bbn1_1900_5000_800.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370339/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370339.MGPy8EG_A14N_GG_bbn1_1900_5000_1800.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370267/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370267.MGPy8EG_A14N_GG_bbn1_1100_5000_1000.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370305/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370305.MGPy8EG_A14N_GG_bbn1_1600_5000_800.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370264/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370264.MGPy8EG_A14N_GG_bbn1_1100_5000_400.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370298/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370298.MGPy8EG_A14N_GG_bbn1_1500_5000_1200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370330/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370330.MGPy8EG_A14N_GG_bbn1_1900_5000_1.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370306/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370306.MGPy8EG_A14N_GG_bbn1_1600_5000_1000.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370318/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370318.MGPy8EG_A14N_GG_bbn1_1700_5000_1600.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370272/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370272.MGPy8EG_A14N_GG_bbn1_1200_5000_600.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370351/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370351.MGPy8EG_A14N_GG_bbn1_2000_5000_1980.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370307/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370307.MGPy8EG_A14N_GG_bbn1_1600_5000_1200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370270/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370270.MGPy8EG_A14N_GG_bbn1_1200_5000_200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370347/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370347.MGPy8EG_A14N_GG_bbn1_2000_5000_1200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370344/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370344.MGPy8EG_A14N_GG_bbn1_2000_5000_600.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370304/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370304.MGPy8EG_A14N_GG_bbn1_1600_5000_600.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370313/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370313.MGPy8EG_A14N_GG_bbn1_1700_5000_600.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370281/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370281.MGPy8EG_A14N_GG_bbn1_1300_5000_1000.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370276/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370276.MGPy8EG_A14N_GG_bbn1_1300_5000_1.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370302/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370302.MGPy8EG_A14N_GG_bbn1_1600_5000_200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370349/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370349.MGPy8EG_A14N_GG_bbn1_2000_5000_1600.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370309/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370309.MGPy8EG_A14N_GG_bbn1_1600_5000_1580.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370295/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370295.MGPy8EG_A14N_GG_bbn1_1500_5000_600.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370283/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370283.MGPy8EG_A14N_GG_bbn1_1300_5000_1280.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370250/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370250.MGPy8EG_A14N_GG_bbn1_900_5000_1.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370289/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370289.MGPy8EG_A14N_GG_bbn1_1400_5000_1000.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370311/ \
    --inputDS="mc15_13TeV:mc15_13TeV.370311.MGPy8EG_A14N_GG_bbn1_1700_5000_200.merge.DAOD_TRUTH1.e4050_p2482" \
	--driver=condor \
    --debug=1

exit 0
