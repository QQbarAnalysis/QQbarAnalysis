#source test_selection.sh
#cuts=3
#root -l analysis.cc\(\"eL\",\"l5_valencia2.0\",$cuts\) > log_eL_l5_valencia2.0_cuts3 &
#root -l analysis.cc\(\"eL\",\"s5_valencia2.0\",$cuts\) > log_eL_s5_valencia2.0_cuts3

cuts=4
root -l analysis.cc\(\"eL\",\"l5_valencia2.0\",$cuts\) > log_eL_l5_valencia2.0_cuts4 
#root -l analysis.cc\(\"eL\",\"s5_valencia2.0\",$cuts\) > log_eL_s5_valencia2.0_cuts4
mv log* output/.
mv *root output/.
