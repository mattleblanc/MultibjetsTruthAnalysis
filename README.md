
<img src="http://i.imgur.com/cQ90uWb.jpg" width="250" align="right" alt="truth" />

# MultibjetsTruthAnalysis

Truth-level analysis for ATLAS Run-II SUSY multi-b/t search.

The truth is out there.

tl;dr: Process `TRUTH1` DxAODs using `Run.py`, and post-process this output using the macros `postTruth.C`, `dumpYields.C` and `plotTruth.C`.

Reminder: optimise for discovery.

# How-To

First, make sure you're able to run. Check out the packages you'll need, and set up your environment. `MultibjetsTruthAnalysis` is dependent on @kratsg's `xAODJetReclustering` package, in order to make the reclustered large-R jets which are used for top-tagging. You'll also need to set up the `BtaggingTRFandRW` package, which is included as a tarball in the `data/` directory of this one -- a setup script for that is included, just run it as shown below.

```
setupATLAS
lsetup fax
mkdir myWorkDir && cd $_
rcSetup Base,2.3.31
git clone git@github.com:mattleblanc/MultibjetsTruthAnalysis.git
git clone https://github.com/kratsg/xAODJetReclustering
./MultibjetsTruthAnalysis/scripts/setup-BtaggingTRFandRW.sh
```
Be sure to set up FAX before RootCore. Be sure to initialise your proxy before trying to run: 

```
voms-proxy-init -voms atlas
```

To compile, always run `rc build`, which is equivalent to `rc find_packages && rc compile && rc make_par`.

To check that things are working, you can run a quick test job on 20k events using the `direct` driver by running:

```
./MultibjetsTruthAnalysis/scripts/TestTruth.sh
```

... though you may want to redirect the output to somewhere more appropriate, by first modifying the `submitDir` in this script.

# Links

[CERN](http://home.cern)

[The ATLAS Collaboration](http://atlas.ch/)

[University of Victoria](https://www.uvic.ca/science/physics/)

[University of Chicago](http://physics.uchicago.edu/)

[SLAC](https://www6.slac.stanford.edu/)
