for cuts in {0..17}
do   
    root -l test_selection.cc\(\"eR\",\"genkt_restorer\",$cuts\) > log_sel_eR_genkt_restorer_cuts$cuts &
    root -l test_selection.cc\(\"eL\",\"genkt_restorer\",$cuts\) > log_sel_eL_genkt_restorer_cuts$cuts 
done

sleep 120
mv log_sel* output/.
mv selection*root output/.

