cuts=4
root -l analysis.cc\(\"eL\",\"l5_valencia1.4\",$cuts\) > log_eL_l5_valencia1.4 &
root -l analysis.cc\(\"eL\",\"s5_valencia1.4\",$cuts\) > log_eL_s5_valencia1.4
mv log* output/.
mv *root output/.




