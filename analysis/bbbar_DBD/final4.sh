#for Kt in 35 20 50
#do
#Kt=35
#cuts=4
    #for cuts in {0..5}
    #do
    #root -l test_selection_bkg.cc\(\"eR\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_bkg_${Kt}_R125_cuts${cuts} &
    #root -l test_selection_rad.cc\(\"eR\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_rad_${Kt}_R125_cuts${cuts} 

    #root -l test_selection_bkg.cc\(\"eL\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_bkg_${Kt}_R125_cuts${cuts} &
    #root -l test_selection_rad.cc\(\"eL\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_rad_${Kt}_R125_cuts${cuts} 
    #mv *root output_final2/.
    #mv log* output_final2/.
    
#    root -l test_selection.cc\(\"eR\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_${Kt}_R125_cuts${cuts} 
#    root -l test_selection.cc\(\"eL\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_${Kt}_R125_cuts${cuts}
#    mv *root output_final2/.
#    mv log* output_final2/.
	
#done

Kt=35
cuts=14

root -l test_selection_bkg.cc\(\"eR\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_bkg_${Kt}_R125_cuts${cuts} &
root -l test_selection_rad.cc\(\"eR\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_rad_${Kt}_R125_cuts${cuts}

mv *root output_final2/.
mv log* output_final2/.

