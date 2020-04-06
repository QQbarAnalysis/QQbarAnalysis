#!/bin/bash
# file name: kt_test.sh

path="/nfs/dust/ilc/user/airqui/bbbar/condor_jobs/IDR_500GeV_small/eL_norestorer/"
source $path/init_ilcsoft.sh
cp -r ${path}/lib $PWD/.
cp ${path}/gear_ILD_s5_o1_v02.xml $PWD/.
cp ${path}/test_kt_xNAMEfile.xml .


export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libVertexRestorer.so"
export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libParticleTagger.so"
export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libQQbarProcessor.so"

echo $PWD
echo "making an ls" $(ls)
Marlin ${PWD}/test_kt_xNAMEfile.xml
