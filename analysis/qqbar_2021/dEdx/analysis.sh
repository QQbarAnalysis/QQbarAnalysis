for file in "15161" "15162_0" "15162_1" "15162_2" "15162_3" "15162_4" "15162_5" "15162_6" "15162_7" "15162_8"
do
    root -l -q analysis.cc\(\"${file}_eLpR.root\",\"${file}\",true,true\) > log_correction_${file} &
    root -l -q analysis.cc\(\"${file}_eLpR.root\",\"${file}\",true,false\) > log_nocorrection_${file}
done




