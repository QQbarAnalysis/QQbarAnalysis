for cuts in {11..12}
do
#cuts=5
    root -l analysis_rad.cc\(\"eR\",\"radret\",$cuts,5000,0.8,0.8\) > log_bkg_5000_analysis_radret_eR_cuts${cuts} &
    root -l analysis_rad.cc\(\"eL\",\"radret\",$cuts\,5000,0.8,0.8\)> log_bkg_5000_analysis_radret_eL_cuts${cuts}
    
    root -l analysis_rad.cc\(\"eR\",\"radret\",$cuts,10,0.8,0.8\) > log_bkg_10_analysis_radret_eR_cuts${cuts} &
    root -l analysis_rad.cc\(\"eL\",\"radret\",$cuts\,10,0.8,0.8\)> log_bkg_10_analysis_radret_eL_cuts${cuts}

    root -l analysis_rad.cc\(\"eR\",\"radret\",$cuts,20,0.8,0.8\) > log_bkg_20_analysis_radret_eR_cuts${cuts} &
    root -l analysis_rad.cc\(\"eL\",\"radret\",$cuts\,20,0.8,0.8\)> log_bkg_20_analysis_radret_eL_cuts${cuts}

    root -l analysis_rad.cc\(\"eR\",\"radret\",$cuts,30,0.8,0.8\) > log_bkg_30_analysis_radret_eR_cuts${cuts} &
    root -l analysis_rad.cc\(\"eL\",\"radret\",$cuts\,30,0.8,0.8\)> log_bkg_30_analysis_radret_eL_cuts${cuts}

    root -l analysis_rad.cc\(\"eR\",\"radret\",$cuts,35,0.8,0.8\) > log_bkg_35_analysis_radret_eR_cuts${cuts} &
    root -l analysis_rad.cc\(\"eL\",\"radret\",$cuts\,35,0.8,0.8\)> log_bkg_35_analysis_radret_eL_cuts${cuts}

    root -l analysis_rad.cc\(\"eR\",\"radret\",$cuts,40,0.8,0.8\) > log_bkg_40_analysis_radret_eR_cuts${cuts} &
    root -l analysis_rad.cc\(\"eL\",\"radret\",$cuts\,40,0.8,0.8\)> log_bkg_40_analysis_radret_eL_cuts${cuts}  
done


mv log* output/.
mv *root output/.
