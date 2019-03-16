#!/bin/bash
# file name: kt_test.sh

path="/nfs/dust/ilc/user/airqui/bbbar/condor_jobs/DBD_eekt_testrestorer/500GeV_idr_eL_before/"
source $path/init_ilcsoft.sh
cp -r ${path}/data $PWD/.
cp -r ${path}/lib $PWD/.
cp -r ${path}/lcfiweights $PWD/.
cp ${path}/gear_ILD_l5_o1_v02.xml $PWD/.
cp ${path}/test_kt_0.xml .


export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libVertexRestorer.so"
export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libTrashRecoProcessor.so"
export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libTruthVertexFinder.so"
echo $PWD
echo "making an ls" $(ls)
Marlin ${PWD}/test_kt_0.xml
#Marlin test_kt_0.xml