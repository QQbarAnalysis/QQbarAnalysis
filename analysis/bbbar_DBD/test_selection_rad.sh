#for Kt in 5 60 80 100 120
#do
#    cuts=0
#    #Kt=10
#    root -l test_selection_rad.cc\(\"eR\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_${Kt}_radret_R125_cuts${cuts} &
#    root -l test_selection_rad.cc\(\"eL\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_${Kt}_radret_R125_cuts${cuts}

#    mv selection*root output_Cuts/.
#    mv log_selection* output_Cuts/.
#done


#for cuts in {2..4}
#do
#    for Kt in 20 30 35 40 50
#    do
#	root -l test_selection_bkg.cc\(\"eR\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_bkg_${Kt}_radret_R125_cuts${cuts} &
#	root -l test_selection_bkg.cc\(\"eL\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_bkg_${Kt}_radret_R125_cuts${cuts}
#
#	mv selection*root output_Cuts/.
#	mv log_selection* output_Cuts/.
#    done
#done


#for cuts in {0..4}
#do
#for Kt in 5 60 80 100 120
#do
#    cuts=0
#    root -l test_selection_bkg.cc\(\"eR\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_bkg_${Kt}_radret_R125_cuts${cuts} &
#    cuts=1
#    root -l test_selection_bkg.cc\(\"eR\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_bkg_${Kt}_radret_R125_cuts${cuts} 
#    cuts=2
#    root -l test_selection_bkg.cc\(\"eR\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_bkg_${Kt}_radret_R125_cuts${cuts} &
#    cuts=3
#    root -l test_selection_bkg.cc\(\"eR\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_bkg_${Kt}_radret_R125_cuts${cuts} 
#    cuts=4
#    root -l test_selection_bkg.cc\(\"eR\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_bkg_${Kt}_radret_R125_cuts${cuts} 
#    mv selection*root output_Cuts/.
#    mv log_selection* output_Cuts/.
#    #done
#done

#for Kt in 5 60 80 100 120
#do
#    cuts=0
#    root -l test_selection_bkg.cc\(\"eL\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_bkg_${Kt}_radret_R125_cuts${cuts} &
#    cuts=1
#    root -l test_selection_bkg.cc\(\"eL\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_bkg_${Kt}_radret_R125_cuts${cuts} &
#    cuts=2
#    root -l test_selection_bkg.cc\(\"eL\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_bkg_${Kt}_radret_R125_cuts${cuts} 
#    #cuts=3
#    #root -l test_selection_bkg.cc\(\"eL\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_bkg_${Kt}_radret_R125_cuts${cuts}
#    #cuts=4
#    #root -l test_selection_bkg.cc\(\"eL\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_bkg_${Kt}_radret_R125_cuts${cuts}
#    mv selection*root output_Cuts/.
#    mv log_selection* output_Cuts/.
#    #done
#done

cuts=5
Kt=35

root -l test_selection_bkg.cc\(\"eR\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_bkg_${Kt}_radret_R125_cuts${cuts} &
root -l test_selection_rad.cc\(\"eR\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_rad_${Kt}_radret_R125_cuts${cuts}
mv selection*root output_Cuts/.
mv log_selection* output_Cuts/.

root -l test_selection_bkg.cc\(\"eL\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_bkg_${Kt}_radret_R125_cuts${cuts} &
root -l test_selection_rad.cc\(\"eL\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_rad_${Kt}_radret_R125_cuts${cuts}

mv selection*root output_Cuts/.
mv log_selection* output_Cuts/.


for Kt in 20 50
do
    cuts=5
    #Kt=35
    
    root -l test_selection_bkg.cc\(\"eR\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_bkg_${Kt}_radret_R125_cuts${cuts} &
    root -l test_selection_rad.cc\(\"eR\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eR_rad_${Kt}_radret_R125_cuts${cuts} 
    mv selection*root output_Cuts/.
    mv log_selection* output_Cuts/.
    
    root -l test_selection_bkg.cc\(\"eL\",\"genkt_restorer\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_bkg_${Kt}_radret_R125_cuts${cuts} &
    root -l test_selection_rad.cc\(\"eL\",\"radret_genkt_R125\",$cuts,$Kt,0.8,0.8\) > log_selection_eL_rad_${Kt}_radret_R125_cuts${cuts}
    
    mv selection*root output_Cuts/.
    mv log_selection* output_Cuts/.
done



#for cuts in {0..3}
#do
#    #cuts=0
#    echo $cuts
#    root -l test_selection_rad.cc\(\"eR\",\"radret_genkt_R050\",$cuts,30,0.8,0.8\) > log_test_selection_rad_eR_30_radret_R050_cuts${cuts} &
#    root -l test_selection_rad.cc\(\"eR\",\"radret_genkt_R200\",$cuts,30,0.8,0.8\) > log_test_selection_rad_eR_30_radret_R200_cuts${cuts}
#    mv selection*root output_kstudy/.
#    mv log_test_selection_rad* output_kstudy/.
#done

#source kstudy.sh

#cuts=0
#root -l test_selection_rad.cc\(\"eR\",\"radret_genkt_R100\",$cuts,35,0.8,0.8\) > log_test_selection_rad_eR_35_radret_R100_cuts${cuts} &
#root -l test_selection_rad.cc\(\"eR\",\"radret_genkt_R150\",$cuts,35,0.8,0.8\) > log_test_selection_rad_eR_35_radret_R150_cuts${cuts} 
#root -l test_selection_rad.cc\(\"eR\",\"radret_genkt_R130\",$cuts,35,0.8,0.8\) > log_test_selection_rad_eR_35_radret_R130_cuts${cuts}&
#root -l test_selection_rad.cc\(\"eR\",\"radret_genkt_R140\",$cuts,35,0.8,0.8\) > log_test_selection_rad_eR_35_radret_R140_cuts${cuts}

#cuts=6
#root -l test_selection_rad.cc\(\"eR\",\"radret_genkt_R125\",$cuts,35,0.8,0.8\) > log_test_selection_rad_eR_35_radret_R125_cuts${cuts} &
