root -l analysis_rho.cc\(\"both\",\"genkt_restorer\",40,5,0,0.8,0.8\)> log_rho_both_bb_b_40_charge_08_08 
#root -l analysis_rho.cc\(\"eL\",\"genkt_restorer\",40,5,0,0.8,0.8\)> log_rho_eL_bb_b_40_charge_08_08

mv *root output/.
mv log* output/.

root -l analysis_rho.cc\(\"both\",\"genkt_restorer\",40,4,0,0.8,0.8\)> log_rho_both_bb_c_40_charge_08_08 
#root -l analysis_rho.cc\(\"eL\",\"genkt_restorer\",40,4,0,0.8,0.8\)> log_rho_eL_bb_c_40_charge_08_08 

mv *root output/.
mv log* output/.


root -l analysis_rho.cc\(\"both\",\"genkt_restorer\",40,3,0,0.8,0.8\)> log_rho_both_bb_uds_40_charge_08_08 
#root -l analysis_rho.cc\(\"eL\",\"genkt_restorer\",40,3,0,0.8,0.8\)> log_rho_eL_bb_uds_40_charge_08_08

mv *root output/.
mv log* output/.

