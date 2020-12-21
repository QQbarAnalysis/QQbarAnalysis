Kt=35

for cuts in 0 -1 -2 1 2
do
    root -l test_id_RR.cc\(\"both\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_both_rad_${K}_R125_cuts${cuts} &
    root -l test_id_RR.cc\(\"eL\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_rad_${K}_R125_cuts${cuts}
    
    sleep 30
    root -l test_id_RR.cc\(\"eR\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_rad_${K}_R125_cuts${cuts}
    
    mv *root output_20200427/.
    mv log* output_20200427/. 
done

source analysis2.sh
