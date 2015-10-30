import ROOT
import logging
import shutil
import os

logging.basicConfig(level=logging.INFO)
from optparse import OptionParser

parser = OptionParser()

# job configuration
parser.add_option("--submitDir", help="dir to store the output", default="submit_dir")
parser.add_option("--inputDS", help="input DS from DQ2", default="none")
parser.add_option("--driver", help="select where to run", choices=("direct", "condor", "prooflite", "proof", "grid"), default="direct")
parser.add_option("--nevents", type=int, help="number of events to process for all the datasets")
parser.add_option("--skip-events", type=int, help="skip the first n events")
parser.add_option("-w", "--overwrite", action='store_true', default=True, help="overwrite previous submitDir")

parser.add_option("--doxAOD", help="Make xAOD output [0/1]", type="int", default=1) 
parser.add_option("--doRcJets", help="DoRcJets flag [0/1]", type="int", default=0)
parser.add_option("--doAK10Jets", help="DoAK10Jets flag [0/1]", type="int", default=1)
parser.add_option("--debug", help="Debug mode: print extra stuff [0/1]", type="int", default=0)
parser.add_option("--doTRF", help="TRF flag [0/1]", type="int", default=1)
parser.add_option("--process", help="name of the process added to the output grid jobs", default="")

(options, args) = parser.parse_args()

import atexit
@atexit.register
def quite_exit():
    ROOT.gSystem.Exit(0)

logging.info("loading packages")
ROOT.gROOT.SetBatch(True)
ROOT.gROOT.Macro("$ROOTCOREDIR/scripts/load_packages.C")

if options.overwrite:
    import shutil
    shutil.rmtree(options.submitDir, True)

#Set up the job for xAOD access:
ROOT.xAOD.Init().ignore();

# create a new sample handler to describe the data files we use
logging.info("creating new sample handler")
sh_all = ROOT.SH.SampleHandler()

if options.inputDS != "none":
    ROOT.SH.scanDQ2 (sh_all, options.inputDS);
else :
    search_directories = []
    #search_directories = ["/afs/cern.ch/user/c/crizzi/IFAE/storage/SUSY10/"]
    #search_directories = ["/share/t3data3/kratsg/xAODs/test/"]
    #    search_directories = ["/afs/cern.ch/work/l/lvalery/public/mc15_dSUSY1/test/"]
    #search_directories = ("/afs/cern.ch/atlas/project/PAT/xAODs/r5787/",)
    #search_directories = ["/u/at/swiatlow/nfs/test/rel20/ttbarSUSY1/"]
    search_directories = ["/share/t3data2/swiatlow/truth_test/"]
    #search_directories = ["/afs/cern.ch/work/a/amarzin/susy_13TeV/samples/ttbar/"]
    #search_directories = ["/afs/cern.ch/work/a/amarzin/susy_13TeV/samples/Z/"]
    #search_directories = ["/afs/cern.ch/work/l/lvalery/public/mc15_dSUSY1/test/"]
    # scan for datasets in the given directories
    for directory in search_directories:
        ROOT.SH.scanDir(sh_all, directory)

# print out the samples we found
logging.info("%d different datasets found scanning all directories", len(sh_all))

# set the name of the tree in our files
sh_all.setMetaString("nc_tree", "CollectionTree")

# this is the basic description of our job
logging.info("creating new job")
job = ROOT.EL.Job()
job.sampleHandler(sh_all)

#Set the xAOD access mode of the job:
job.options().setString( ROOT.EL.Job.optXaodAccessMode,ROOT.EL.Job.optXaodAccessMode_branch );

if options.nevents:
    logging.info("processing only %d events", options.nevents)
    job.options().setDouble(ROOT.EL.Job.optMaxEvents, options.nevents)

if options.skip_events:
    logging.info("skipping first %d events", options.skip_events)
    job.options().setDouble(ROOT.EL.Job.optSkipEvents, options.skip_events)

# add our algorithm to the job
logging.info("creating algorithms")
alg = ROOT.TruthAnalysis()

logging.info("adding algorithms")
job.algsAdd(alg)

# make the driver we want to use:
# this one works by running the algorithm directly
logging.info("creating driver")
driver = None
if (options.driver == "direct"):
    logging.info("running on direct")
    driver = ROOT.EL.DirectDriver()
    logging.info("submit job")
    driver.submit(job, options.submitDir)
elif (options.driver == "condor" ):
    driver = ROOT.EL.CondorDriver()
    driver.options().setBool(ROOT.EL.Job.optBatchSharedFileSystem, False)
    driver.options().setString(ROOT.EL.Job.optCondorConf, "stream_output = true")
    driver.submitOnly(job, options.submitDir)
elif (options.driver == "prooflite"):
    logging.info("running on prooflite")
    driver = ROOT.EL.ProofDriver()
    logging.info("submit job")
    driver.submit(job, options.submitDir)
elif (options.driver == "proof"):
    logging.info("running on proof")
    driver = ROOT.EL.ProofDriver()
    driver.proofMaster = "swiatlow@atlint03.slac.stanford.edu:21001";
    driver.makeParOptions = "--nobuild";
    driver.proofParm.setString ("PROOF_LookupOpt", "none");
    driver.proofParm.setString ("PROOF_INTWAIT", "30000")
    driver.proofParm.setString ("PROOF_INITCMD",  ROOT.gSystem.GetFromPipe("source $ROOTCOREBIN/../rcSetup.sh -P").Data())
    driver.submit (job, options.submitDir);
elif (options.driver == "grid"):
    logging.info("running on Grid")
    driver = ROOT.EL.PrunDriver()
    #driver.options().setString("nc_outputSampleName", "user.%nickname%.%in:name[2]%.%in:name[3]%.%in:name[5]%_25")
    #driver.options().setString("nc_outputSampleName", "user.%nickname%.%in:name[2]%."+options.process+".%in:name[5]%.%in:name[6]%_test_01_03")
    driver.options().setString("nc_outputSampleName", "user.%nickname%.%in:name[2]%."+options.process+".%in:name[5]%.%in:name[6]%_tag_08_v1")
    driver.options().setDouble("nc_nGBPerJob", 2)
    #driver.options().setDouble("nc_disableAutoRetry", 1)
    #driver.options().setString("nc_cmtConfig", "x86_64-slc6-gcc48-opt")
    #driver.options().setString("EL::Job::optGridMergeOutput", "0")
    #driver.options().setString("nc_excludedSite", "TRIUMF-LCG2_DATADISK")
    #driver.options().setString("nc_EventLoop_SubmitFlags", "--allowTaskDuplication");
    # driver.options().setString("EL::Job::optGridDestSE","CERN-PROD_LOCALGROUPDISK")
    #driver.options().setString("nc_optGridDestSE","CERN-PROD_LOCALGROUPDISK")
    logging.info("submit job")
    driver.submitOnly(job, options.submitDir)
