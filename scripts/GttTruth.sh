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
	--submitDir=/home/mleblanc/out/acceptance/370147/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370147.MGPy8EG_A14N_GG_ttn1_1600_5000_600.merge.DAOD_TRUTH1.e4049_p2482/" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370154/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370154.MGPy8EG_A14N_GG_ttn1_1700_5000_400.merge.DAOD_TRUTH1.e4049_p2482/" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370128/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370128.MGPy8EG_A14N_GG_ttn1_1300_5000_945.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370122/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370122.MGPy8EG_A14N_GG_ttn1_1200_5000_855.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370157/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370157.MGPy8EG_A14N_GG_ttn1_1700_5000_1000.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370129/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370129.MGPy8EG_A14N_GG_ttn1_1400_5000_1.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370103/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370103.MGPy8EG_A14N_GG_ttn1_900_5000_545.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370119/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370119.MGPy8EG_A14N_GG_ttn1_1200_5000_700.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370180/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370180.MGPy8EG_A14N_GG_ttn1_2000_5000_400.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370155/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370155.MGPy8EG_A14N_GG_ttn1_1700_5000_600.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370149/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370149.MGPy8EG_A14N_GG_ttn1_1600_5000_1000.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370145/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370145.MGPy8EG_A14N_GG_ttn1_1600_5000_200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370164/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370164.MGPy8EG_A14N_GG_ttn1_1800_5000_800.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370162/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370162.MGPy8EG_A14N_GG_ttn1_1800_5000_400.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370165/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370165.MGPy8EG_A14N_GG_ttn1_1800_5000_1000.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370166/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370166.MGPy8EG_A14N_GG_ttn1_1800_5000_1200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370150/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370150.MGPy8EG_A14N_GG_ttn1_1600_5000_1200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370125/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370125.MGPy8EG_A14N_GG_ttn1_1300_5000_400.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370113/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370113.MGPy8EG_A14N_GG_ttn1_1100_5000_745.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370186/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370186.MGPy8EG_A14N_GG_ttn1_2000_5000_1600.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370178/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370178.MGPy8EG_A14N_GG_ttn1_2000_5000_1.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370126/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370126.MGPy8EG_A14N_GG_ttn1_1300_5000_600.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370132/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370132.MGPy8EG_A14N_GG_ttn1_1400_5000_400.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370100/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370100.MGPy8EG_A14N_GG_ttn1_900_5000_1.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370107/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370107.MGPy8EG_A14N_GG_ttn1_1000_5000_600.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370106/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370106.MGPy8EG_A14N_GG_ttn1_1000_5000_400.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370174/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370174.MGPy8EG_A14N_GG_ttn1_1900_5000_1000.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370153/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370153.MGPy8EG_A14N_GG_ttn1_1700_5000_200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370117/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370117.MGPy8EG_A14N_GG_ttn1_1200_5000_400.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370109/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370109.MGPy8EG_A14N_GG_ttn1_1100_5000_1.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370124/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370124.MGPy8EG_A14N_GG_ttn1_1300_5000_200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370171/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370171.MGPy8EG_A14N_GG_ttn1_1900_5000_400.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370152/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370152.MGPy8EG_A14N_GG_ttn1_1700_5000_1.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370176/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370176.MGPy8EG_A14N_GG_ttn1_1900_5000_1400.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370182/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370182.MGPy8EG_A14N_GG_ttn1_2000_5000_800.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370170/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370170.MGPy8EG_A14N_GG_ttn1_1900_5000_200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370163/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370163.MGPy8EG_A14N_GG_ttn1_1800_5000_600.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370187/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370187.MGPy8EG_A14N_GG_ttn1_2000_5000_1645.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370102/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370102.MGPy8EG_A14N_GG_ttn1_900_5000_400.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370133/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370133.MGPy8EG_A14N_GG_ttn1_1400_5000_600.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370130/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370130.MGPy8EG_A14N_GG_ttn1_1400_5000_100.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370161/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370161.MGPy8EG_A14N_GG_ttn1_1800_5000_200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370151/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370151.MGPy8EG_A14N_GG_ttn1_1600_5000_1245.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370111/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370111.MGPy8EG_A14N_GG_ttn1_1100_5000_400.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370159/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370159.MGPy8EG_A14N_GG_ttn1_1700_5000_1345.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370108/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370108.MGPy8EG_A14N_GG_ttn1_1000_5000_645.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370110/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370110.MGPy8EG_A14N_GG_ttn1_1100_5000_200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370144/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370144.MGPy8EG_A14N_GG_ttn1_1600_5000_1.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370177/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370177.MGPy8EG_A14N_GG_ttn1_1900_5000_1545.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370173/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370173.MGPy8EG_A14N_GG_ttn1_1900_5000_800.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370142/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370142.MGPy8EG_A14N_GG_ttn1_1500_5000_1000.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370116/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370116.MGPy8EG_A14N_GG_ttn1_1200_5000_200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370139/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370139.MGPy8EG_A14N_GG_ttn1_1500_5000_400.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370120/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370120.MGPy8EG_A14N_GG_ttn1_1200_5000_800.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370172/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370172.MGPy8EG_A14N_GG_ttn1_1900_5000_600.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370101/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370101.MGPy8EG_A14N_GG_ttn1_900_5000_200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370105/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370105.MGPy8EG_A14N_GG_ttn1_1000_5000_200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370156/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370156.MGPy8EG_A14N_GG_ttn1_1700_5000_800.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370118/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370118.MGPy8EG_A14N_GG_ttn1_1200_5000_600.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370175/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370175.MGPy8EG_A14N_GG_ttn1_1900_5000_1200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370168/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370168.MGPy8EG_A14N_GG_ttn1_1800_5000_1445.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370158/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370158.MGPy8EG_A14N_GG_ttn1_1700_5000_1200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370114/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370114.MGPy8EG_A14N_GG_ttn1_1200_5000_1.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370121/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370121.MGPy8EG_A14N_GG_ttn1_1200_5000_845.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370146/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370146.MGPy8EG_A14N_GG_ttn1_1600_5000_400.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370183/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370183.MGPy8EG_A14N_GG_ttn1_2000_5000_1000.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370134/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370134.MGPy8EG_A14N_GG_ttn1_1400_5000_800.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370123/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370123.MGPy8EG_A14N_GG_ttn1_1300_5000_1.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370160/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370160.MGPy8EG_A14N_GG_ttn1_1800_5000_1.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370138/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370138.MGPy8EG_A14N_GG_ttn1_1500_5000_200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370167/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370167.MGPy8EG_A14N_GG_ttn1_1800_5000_1400.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370179/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370179.MGPy8EG_A14N_GG_ttn1_2000_5000_200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370137/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370137.MGPy8EG_A14N_GG_ttn1_1500_5000_1.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370184/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370184.MGPy8EG_A14N_GG_ttn1_2000_5000_1200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370169/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370169.MGPy8EG_A14N_GG_ttn1_1900_5000_1.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370127/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370127.MGPy8EG_A14N_GG_ttn1_1300_5000_800.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370140/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370140.MGPy8EG_A14N_GG_ttn1_1500_5000_600.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370104/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370104.MGPy8EG_A14N_GG_ttn1_1000_5000_1.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370185/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370185.MGPy8EG_A14N_GG_ttn1_2000_5000_1400.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370136/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370136.MGPy8EG_A14N_GG_ttn1_1400_5000_1045.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370181/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370181.MGPy8EG_A14N_GG_ttn1_2000_5000_600.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370143/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370143.MGPy8EG_A14N_GG_ttn1_1500_5000_1145.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370141/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370141.MGPy8EG_A14N_GG_ttn1_1500_5000_800.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370115/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370115.MGPy8EG_A14N_GG_ttn1_1200_5000_100.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370112/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370112.MGPy8EG_A14N_GG_ttn1_1100_5000_600.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370131/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370131.MGPy8EG_A14N_GG_ttn1_1400_5000_200.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370135/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370135.MGPy8EG_A14N_GG_ttn1_1400_5000_1000.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
python MultibjetsTruthAnalysis/scripts/Run.py \
	--submitDir=/home/mleblanc/out/acceptance/370148/ \
	--inputDS="mc15_13TeV:mc15_13TeV.370148.MGPy8EG_A14N_GG_ttn1_1600_5000_800.merge.DAOD_TRUTH1.e4049_p2482" \
	--driver=condor \
	--debug=1
	
exit 0
