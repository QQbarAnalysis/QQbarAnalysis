#source test_angular.sh 
for cuts in {3..4}
do
    root -l test_selection.cc\(\"eL\",\"l5_valencia2.0\",$cuts\) &
    sleep 5s
    root -l test_selection.cc\(\"eL\",\"s5_valencia2.0\",$cuts\) 
done

mv *root output/.
