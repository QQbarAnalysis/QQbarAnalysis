#!/bin/bash

path=$PWD

for prod in "15161"
do
#"15269" "15271" "15273"
#do
    folder_name="/lustre/ific.uv.es/prj/ific/flc/mc-2020/250-SetA/2f_hadronic_eL_pR/ILD_l5_o1_v02/v02-02/000"${prod}"/000/"
    cd $folder_name
    echo $folder_name
    
    FILES=*
    
    i=0
    for f in $FILES
    do
	name="00"$i
	if [ $i -gt 9 ]; then
            name="0"$i
	fi
	
	if [ $i -gt 99 ]; then
            name=$i
	fi
	cp ${path}/test_default.xml ${path}/test_${prod}_${name}.xml
        sed -i -e 's/xPROD/'${prod}'/g' ${path}/test_${prod}_${name}.xml
	sed -i -e 's/NFile/'${f}'/g' ${path}/test_${prod}_${name}.xml
	sed -i -e 's/newFileN/'${name}'/g' ${path}/test_${prod}_${name}.xml
	
	cp ${path}/run_default.sh ${path}/run_${prod}_${name}.sh
	sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${name}.sh
	sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${name}.sh
	cp ${path}/run_default.sub ${path}/run_${prod}_${name}.sub
        sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${name}.sub
	sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${name}.sub
	
	if [ -f ${path}/${prod}_${name}.root ]; 
	then  
	    echo "Skip "${name} 
        else 
	    echo "Submit --- > " ${name}   
	    cd -
	    condor_submit run_${prod}_${name}.sub
	    #sleep 0.1s 
	    cd -
	fi    
	#rm ${path}/run_${prod}_${name}.sub
	#rm ${path}/run_${prod}_${name}.sh
	i=$((i+1))
    done
    cd -
done

