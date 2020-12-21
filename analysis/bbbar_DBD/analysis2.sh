Kt=35
for cuts in 2 0
do
#cuts=2
    root -l test_id_RR.cc\(\"eR\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_rad_${K}_R125_cuts${cuts} &
    root -l test_id_RR.cc\(\"eL\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_rad_${K}_R125_cuts${cuts} &
    
#root -l test_id_RR.cc\(\"eR\",\"277fb_genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_iD_eR_norad_${Kt}_cuts${cuts}
    root -l test_id_RR_IDR.cc\(\"eL\",$cuts,$Kt,0.8,0.8\) > log_iD_eL_IDR500GeV_${Kt}_cuts${cuts} 
    #cuts=0
#root -l test_id_RR_IDR.cc\(\"eL\",$cuts,$Kt,0.8,0.8\) > log_iD_eL_IDR500GeV_${Kt}_cuts${cuts}

done
