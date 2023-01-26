#!/bin/bash

path=$PWD

for prod in "eL_pR" "eR_pL"
do
    folder_name="/lustre/ific.uv.es/prj/ific/flc/mc-opt-3/"${prod}"/"
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
	if [ -f ${path}/${prod}_${name}.root ];
        then
            echo "Skip "${name}
        else
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

