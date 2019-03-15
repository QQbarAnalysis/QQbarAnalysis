#!/bin/bash
# file name: kt_xNAMEfile.sh


#path="/nfs/dust/ilc/user/airqui/bbbar/condor_jobs/DBD_eekt/250GeV_eR_test/"
#source $path/init_ilcsoft.sh
#cp -r ${path}/data $PWD/.
#cp -r ${path}/lib $PWD/.
#cp -r ${path}/lcfiweights $PWD/.
#cp ${path}/GearOutput.xml $PWD/.
#cp ${path}/test_kt_xNAMEfile.xml .

#export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libQQbarProcessor.so"
#export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libVertexRestorer.so"
#export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libmyFastJetProcessor.so"
#export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libTrashRecoProcessor.so"
#export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libTruthVertexFinder.so"

echo $PWD
echo "making an ls" $(ls)
/cvmfs/ilc.desy.de/sw/x86_64_gcc44_sl6/v01-17-06/Marlin/v01-05/bin/Marlin ${PWD}/test_kt_0.xml