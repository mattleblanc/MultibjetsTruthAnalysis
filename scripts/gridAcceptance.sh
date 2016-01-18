#!/bin/bash

prun --exec "python MultibjetsTruthAnalysis/scripts/acceptance.py %IN" \
    --useRootCore \
    --inDsTxt MultibjetsTruthAnalysis/scripts/signal_samples.txt \
    --outDS "user.mleblanc.370102.acceptance.out.v02/" \
    --maxNFilesPerJob 1
    
exit 0