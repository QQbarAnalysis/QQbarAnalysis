
cuts=6
#root -l analysis.cc\(\"eR\",\"genkt_restorer\",$cuts\) > log_analysis_genkt_restorer_eR_cuts$cuts 
root -l analysis.cc\(\"eL\",\"genkt_restorer\",$cuts\) > log_analysis_genkt_restorer_eL_cuts$cuts &
root -l analysis.cc\(\"eL\",\"genkt_norestorer\",$cuts\) > log_analysis_genkt_norestorer_eL_cuts$cuts
mv log* output/.
mv *root output/.

source test_angular.sh
source test_selection.sh
