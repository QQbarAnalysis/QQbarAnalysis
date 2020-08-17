for cuts in {0..1}
do
    #cuts=1
#    echo $cuts
#root -l kstudy.cc\(\"eR\",\"radret_genkt_R050\",$cuts,5000,0.8,0.8\) > log_kstudy_eR_5000_radret_R050_cuts${cuts} &
#root -l kstudy.cc\(\"eR\",\"radret_genkt_R075\",$cuts,5000,0.8,0.8\) > log_kstudy_eR_5000_radret_R075_cuts${cuts} 
#root -l kstudy.cc\(\"eR\",\"radret_genkt_R100\",$cuts,5000,0.8,0.8\) > log_kstudy_eR_5000_radret_R100_cuts${cuts} &
    root -l kstudy.cc\(\"eR\",\"radret_genkt_R125\",$cuts,35,0.8,0.8\) > log_kstudy_eR_35_radret_R125_cuts${cuts} &
    root -l kstudy.cc\(\"eR\",\"radret_genkt_R125\",$cuts,5000,0.8,0.8\) > log_kstudy_eR_5000_radret_R125_cuts${cuts} 
#    root -l kstudy.cc\(\"eR\",\"radret_genkt_R130\",$cuts,5000,0.8,0.8\) > log_kstudy_eR_5000_radret_R130_cuts${cuts} &
#    root -l kstudy.cc\(\"eR\",\"radret_genkt_R135\",$cuts,5000,0.8,0.8\) > log_kstudy_eR_5000_radret_R135_cuts${cuts} &
#    root -l kstudy.cc\(\"eR\",\"radret_genkt_R140\",$cuts,5000,0.8,0.8\) > log_kstudy_eR_5000_radret_R140_cuts${cuts}
#    root -l kstudy.cc\(\"eR\",\"radret_genkt_R145\",$cuts,5000,0.8,0.8\) > log_kstudy_eR_5000_radret_R145_cuts${cuts} &
#root -l kstudy.cc\(\"eR\",\"radret_genkt_R150\",$cuts,5000,0.8,0.8\) > log_kstudy_eR_5000_radret_R150_cuts${cuts} 
#root -l kstudy.cc\(\"eR\",\"radret_genkt_R175\",$cuts,5000,0.8,0.8\) > log_kstudy_eR_5000_radret_R175_cuts${cuts} &
#root -l kstudy.cc\(\"eR\",\"radret_genkt_R200\",$cuts,30,0.8,0.8\) > log_kstudy_eR_5000_radret_R200_cuts${cuts}

mv kstudy*root output_Rparam_cleanISR/.
mv log_kstudy* output_Rparam_cleanISR/.
done

#source test_selection_rad.sh

#for cuts in {0..3}
#do
#cuts=1
#    echo $cuts
#    root -l kstudy.cc\(\"eL\",\"radret_genkt_R050\",$cuts,30,0.8,0.8\) > log_kstudy_eL_30_radret_R050_cuts${cuts} &
#    root -l kstudy.cc\(\"eL\",\"radret_genkt_R075\",$cuts,30,0.8,0.8\) > log_kstudy_eL_30_radret_R075_cuts${cuts} 
#    root -l kstudy.cc\(\"eL\",\"radret_genkt_R100\",$cuts,30,0.8,0.8\) > log_kstudy_eL_30_radret_R100_cuts${cuts} &
#    root -l kstudy.cc\(\"eL\",\"radret_genkt_R125\",$cuts,30,0.8,0.8\) > log_kstudy_eL_30_radret_R125_cuts${cuts}
#    root -l kstudy.cc\(\"eL\",\"radret_genkt_R150\",$cuts,30,0.8,0.8\) > log_kstudy_eL_30_radret_R150_cuts${cuts} &
#    root -l kstudy.cc\(\"eL\",\"radret_genkt_R175\",$cuts,30,0.8,0.8\) > log_kstudy_eL_30_radret_R175_cuts${cuts} &
#    root -l kstudy.cc\(\"eL\",\"radret_genkt_R200\",$cuts,30,0.8,0.8\) > log_kstudy_eL_30_radret_R200_cuts${cuts} #
#
#    mv kstudy*root output_kstudy/.
#    mv log_kstudy* output_kstudy/.
#done

