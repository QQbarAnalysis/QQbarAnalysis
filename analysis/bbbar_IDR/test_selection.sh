#source test_angular.sh 
for cuts in {0..4}
do
    root -l test_selection.cc\(\"eL\",\"l5_valencia1.4\",$cuts\) &
    sleep 5s
    root -l test_selection.cc\(\"eL\",\"s5_valencia1.4\",$cuts\) 
done

mv *root output/.
