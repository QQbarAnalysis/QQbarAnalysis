#!/bin/bash
# file name: kt_xNAMEfile.sh

path="/lhome/ific/a/airqui/QQbar/QQbarAnalysisExample/scripts/2021_LCFIandQQbar_dEdxCorrection"
source $path/init_ilcsoft.sh
cp -r ${path}/data $PWD/.
cp -r ${path}/lib $PWD/.
cp -r ${path}/lcfiweights $PWD/.
cp ${path}/GearOutput.xml $PWD/.
cp ${path}/test_xPROD_xNAMEfile.xml .

export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libQQbarProcessor.so"
echo $PWD
Marlin ${PWD}/test_xPROD_xNAMEfile.xml
