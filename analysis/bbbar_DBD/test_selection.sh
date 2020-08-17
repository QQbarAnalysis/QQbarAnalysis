#source analysis.sh
source test_selection_rad.sh

for cuts in {0..6}
do
    #cuts=5
    echo $cuts
    root -l test_selection.cc\(\"eL\",\"genkt_restorer\",$cuts,5000,0.8,0.8\) > log_sel_bkg_5000_eL_genkt_restorer_cuts${cuts} &
    root -l test_selection.cc\(\"eL\",\"genkt_restorer\",$cuts,10,0.8,0.8\) > log_sel_bkg_10_eL_genkt_restorer_cuts${cuts} &
    root -l test_selection.cc\(\"eL\",\"genkt_restorer\",$cuts,20,0.8,0.8\) > log_sel_bkg_20_eL_genkt_restorer_cuts${cuts} 
    root -l test_selection.cc\(\"eL\",\"genkt_restorer\",$cuts,30,0.8,0.8\) > log_sel_bkg_30_eL_genkt_restorer_cuts${cuts} &
    root -l test_selection.cc\(\"eL\",\"genkt_restorer\",$cuts,35,0.8,0.8\) > log_sel_bkg_35_eL_genkt_restorer_cuts${cuts} &
    root -l test_selection.cc\(\"eL\",\"genkt_restorer\",$cuts,40,0.8,0.8\) > log_sel_bkg_40_eL_genkt_restorer_cuts${cuts}


    root -l test_selection.cc\(\"eR\",\"genkt_restorer\",$cuts,5000,0.8,0.8\) > log_sel_bkg_5000_eR_genkt_restorer_cuts${cuts} &
    root -l test_selection.cc\(\"eR\",\"genkt_restorer\",$cuts,10,0.8,0.8\) > log_sel_bkg_10_eR_genkt_restorer_cuts${cuts} &
    root -l test_selection.cc\(\"eR\",\"genkt_restorer\",$cuts,20,0.8,0.8\) > log_sel_bkg_20_eR_genkt_restorer_cuts${cuts} 
    root -l test_selection.cc\(\"eR\",\"genkt_restorer\",$cuts,30,0.8,0.8\) > log_sel_bkg_30_eR_genkt_restorer_cuts${cuts} &
    root -l test_selection.cc\(\"eR\",\"genkt_restorer\",$cuts,35,0.8,0.8\) > log_sel_bkg_35_eR_genkt_restorer_cuts${cuts} &
    root -l test_selection.cc\(\"eR\",\"genkt_restorer\",$cuts,40,0.8,0.8\) > log_sel_bkg_40_eR_genkt_restorer_cuts${cuts}
    
    sleep 10
    mv log_sel* output/.
    mv selection*root output/.
done

for cuts in {11..18}
do
    #cuts=5
    echo $cuts
    root -l test_selection.cc\(\"eL\",\"genkt_restorer\",$cuts,5000,0.8,0.8\) > log_sel_5000_eL_genkt_restorer_cuts${cuts} &
    root -l test_selection.cc\(\"eL\",\"genkt_restorer\",$cuts,10,0.8,0.8\) > log_sel_10_eL_genkt_restorer_cuts${cuts} &
    root -l test_selection.cc\(\"eL\",\"genkt_restorer\",$cuts,20,0.8,0.8\) > log_sel_20_eL_genkt_restorer_cuts${cuts} 
    root -l test_selection.cc\(\"eL\",\"genkt_restorer\",$cuts,30,0.8,0.8\) > log_sel_30_eL_genkt_restorer_cuts${cuts} &
    root -l test_selection.cc\(\"eL\",\"genkt_restorer\",$cuts,35,0.8,0.8\) > log_sel_35_eL_genkt_restorer_cuts${cuts} &
    root -l test_selection.cc\(\"eL\",\"genkt_restorer\",$cuts,40,0.8,0.8\) > log_sel_40_eL_genkt_restorer_cuts${cuts}

    root -l test_selection.cc\(\"eR\",\"genkt_restorer\",$cuts,5000,0.8,0.8\) > log_sel_5000_eR_genkt_restorer_cuts${cuts} &
    root -l test_selection.cc\(\"eR\",\"genkt_restorer\",$cuts,10,0.8,0.8\) > log_sel_10_eR_genkt_restorer_cuts${cuts} &
    root -l test_selection.cc\(\"eR\",\"genkt_restorer\",$cuts,20,0.8,0.8\) > log_sel_20_eR_genkt_restorer_cuts${cuts} 
    root -l test_selection.cc\(\"eR\",\"genkt_restorer\",$cuts,30,0.8,0.8\) > log_sel_30_eR_genkt_restorer_cuts${cuts} &
    root -l test_selection.cc\(\"eR\",\"genkt_restorer\",$cuts,35,0.8,0.8\) > log_sel_35_eR_genkt_restorer_cuts${cuts} &
    root -l test_selection.cc\(\"eR\",\"genkt_restorer\",$cuts,40,0.8,0.8\) > log_sel_40_eR_genkt_restorer_cuts${cuts}
   
    #sleep 10
    mv log_sel* output/.
    mv selection*root output/.
done

source analysis.sh
