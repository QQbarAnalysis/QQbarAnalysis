#!/bin/bash
# file name: kt_xNAMEfile.sh

path="/lhome/ific/a/airqui/QQbar/QQbarAnalysis-500GeV/scripts/2023_500GeV"
source $path/init_ilcsoft.sh
cp -r ${path}/data $PWD/.
cp -r ${path}/lib $PWD/.
cp -r ${path}/lcfiweights $PWD/.
cp ${path}/GearOutput.xml $PWD/.
cp ${path}/test_xPROD_xNAMEfile.xml .

export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libQQbarProcessor.so"
echo $PWD
Marlin ${PWD}/test_xPROD_xNAMEfile.xml
#if [ -f ${path}/2f_hadronic_xPROD_xNAMEfile.root ];	then
#    mv ${path}/2f_hadronic_xPROD_xNAMEfile.root /lustre/ific.uv.es/prj/ific/flc/ntuples-2021/500GeV_2023_signal/.
#fi
#if [ -f ${path}/2f_hadronic_sample_xPROD_xNAMEfile.root ];	then
#    mv ${path}/2f_hadronic_sample_xPROD_xNAMEfile.root /lustre/ific.uv.es/prj/ific/flc/ntuples-2021/500GeV_2023_signal/.
#fi
#rm ${path}/*xPROD_xNAMEfile*log
#rm ${path}/*xPROD_xNAMEfile*sub
#rm ${path}/*xPROD_xNAMEfile*txt
#rm ${path}/*xPROD_xNAMEfile*sh
#rm ${path}/*xPROD_xNAMEfile*txt