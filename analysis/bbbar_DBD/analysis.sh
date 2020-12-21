Kt=35
#for cuts in 0 1 2 3 4 5 11 12 13 14 15 16
#do
#    root -l test_id_RR.cc\(\"eR\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_rad_${Kt}_R125_cuts${cuts}  &
#    root -l test_selection_rad.cc\(\"eR\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_rad_${Kt}_R125_cuts${cuts} 
#    root -l test_selection_bkg.cc\(\"eR\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_bkg_${Kt}_R125_cuts${cuts} 
    
#    sleep 20
#    mv *root output_20200427/.
#    mv log* output_20200427/.
#done

for cuts in 0 1 2 3 4 5 11 12 13 14 15 16
do
    root -l test_id_RR.cc\(\"eL\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_rad_${K}_R125_cuts${cuts} &
    root -l test_selection_rad.cc\(\"eL\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_rad_${Kt}_R125_cuts${cuts}
    root -l test_selection_bkg.cc\(\"eL\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_bkg_${Kt}_R125_cuts${cuts}
    
    sleep 20
    mv *root output_20200428/.
    mv log* output_20200428/.
done


for cuts in 0 1 2 3 4 5 11 12 13 14 15 16
do
    root -l test_selection.cc\(\"eR\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_${Kt}_R125_cuts${cuts} &
    root -l test_selection.cc\(\"eL\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_${Kt}_R125_cuts${cuts}
    
    mv *root output_20200428/.
    mv log* output_20200428/.
done


for cuts in {11..12}
do
    
root -l analysis.cc\(\"eR\",\"genkt_restorer\",$cuts,35,0.8,0.8\) > log_bkg_35_analysis_genkt_restorer_eR_cuts${cuts} &
root -l analysis.cc\(\"eL\",\"genkt_restorer\",$cuts\,35,0.8,0.8\)> log_bkg_35_analysis_genkt_restorer_eL_cuts${cuts}

root -l analysis.cc\(\"eR\",\"genkt_restorer\",$cuts,20,0.8,0.8\) > log_bkg_20_analysis_genkt_restorer_eR_cuts${cuts} &
root -l analysis.cc\(\"eL\",\"genkt_restorer\",$cuts,20,0.8,0.8\)> log_bkg_20_analysis_genkt_restorer_eL_cuts${cuts}

root -l analysis.cc\(\"eR\",\"genkt_restorer\",$cuts,50,0.8,0.8\) > log_bkg_50_analysis_genkt_restorer_eR_cuts${cuts} &
root -l analysis.cc\(\"eL\",\"genkt_restorer\",$cuts\,50,0.8,0.8\)> log_bkg_50_analysis_genkt_restorer_eL_cuts${cuts}

mv log* output_20200428/.
mv *root output_20200428/.

done

for cuts in {11..12}
do

    root -l analysis.cc\(\"eR\",\"radret_genkt_R125\",$cuts,35,0.8,0.8\) > log_bkg_35_analysis_radret_genkt_R125_eR_cuts${cuts} &
    root -l analysis.cc\(\"eL\",\"radret_genkt_R125\",$cuts\,35,0.8,0.8\)> log_bkg_35_analysis_radret_genkt_R125_eL_cuts${cuts}

    root -l analysis.cc\(\"eR\",\"radret_genkt_R125\",$cuts,20,0.8,0.8\) > log_bkg_20_analysis_radret_genkt_R125_eR_cuts${cuts} &
    root -l analysis.cc\(\"eL\",\"radret_genkt_R125\",$cuts,20,0.8,0.8\)> log_bkg_20_analysis_radret_genkt_R125_eL_cuts${cuts}

    root -l analysis.cc\(\"eR\",\"radret_genkt_R125\",$cuts,50,0.8,0.8\) > log_bkg_50_analysis_radret_genkt_R125_eR_cuts${cuts} &
    root -l analysis.cc\(\"eL\",\"radret_genkt_R125\",$cuts\,50,0.8,0.8\)> log_bkg_50_analysis_radret_genkt_R125_eL_cuts${cuts}

    mv log* output_20200428/.
    mv *root output_20200428/.

done
