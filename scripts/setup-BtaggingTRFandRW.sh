#!/bin/bash

# Did you set up RootCore ?

PREVDIR=`pwd`
echo ${PREVDIR}

cp ${ROOTCOREBIN}/../MultibjetsTruthAnalysis/data/BtaggingTRFandRW.tar ${ROOTCOREBIN}/../
cd ${ROOTCOREBIN}/../
tar -zxvf  ${ROOTCOREBIN}/../BtaggingTRFandRW.tar
rm ${ROOTCOREBIN}/../BtaggingTRFandRW.tar
cd ${PREVDIR}

exit 0
