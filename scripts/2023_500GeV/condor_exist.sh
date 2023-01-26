#!/bin/bash

path=$PWD

for prod in "eL_pR" "eR_pL"
do
    folder_name="/lustre/ific.uv.es/prj/ific/flc/500-TDR_ws/2f_Z_hadronic/ILD_l5_o1_v02/v02-02-03/"
    cd $folder_name
    echo $folder_name
    
    subfolders=*
	prod2="eR.pL"
    if [[ $prod == "eL_pR" ]]; then
  		prod2="eL.pR"
	fi

    i=0
    for sf in $subfolders
    do

		echo ${folder_name}"/"${sf}"/000/*"${prod2}"*"
		if [ ! -f ${folder_name}/${sf}/000/*${prod2}* ]; then
			echo "Skip "${sf} "because has no "${prod2}
			continue
		fi

		#cd ${folder_name}/${sf}/000/
		cd ${folder_name}/${sf}/000/
		echo " tessssst   -> " $PWD
		filenames=*
		
		for fileN in $filenames
    	do
			echo $fileN
			name="0000"$i
			if [ $i -gt 9 ]; then
				name="000"$i
			fi
			if [ $i -gt 99 ]; then
				name="00"$i
			fi
			if [ $i -gt 999 ]; then
				name="0"$i
			fi
			if [ $i -gt 9999 ]; then
				name=$i
			fi
			if [ -f /lustre/ific.uv.es/prj/ific/flc/ntuples-2021/2f_hadronic_sample/unmerged_${prod}_${name}.root ] || [ -f /lustre/ific.uv.es/prj/ific/flc/ntuples-2021/2f_hadronic/unmerged_${prod}_${name}.root ];	then
				echo "Skip "${name}
			else
				cd ${path}
				cp ${path}/test_default.xml ${path}/test_${prod}_${name}.xml
				sed -i -e 's/LCIOFOLDER/'${sf}'/g' ${path}/test_${prod}_${name}.xml
				sed -i -e 's/LCIOFILE/'${fileN}'/g' ${path}/test_${prod}_${name}.xml
				sed -i -e 's/newFileN/'${name}'/g' ${path}/test_${prod}_${name}.xml
				if [ $i -gt 200 ]; then
					sed -i -e 's/xTYPEANALYSIS/'1'/g' ${path}/test_${prod}_${name}.xml
					sed -i -e 's/xFOLDER/'2f_hadronic_${prod}'/g' ${path}/test_${prod}_${name}.xml
					sed -i -e 's/xPROD/'${prod}'/g' ${path}/test_${prod}_${name}.xml
				else 
					sed -i -e 's/xTYPEANALYSIS/'0'/g' ${path}/test_${prod}_${name}.xml
					sed -i -e 's/xFOLDER/'2f_hadronic_sample_${prod}'/g' ${path}/test_${prod}_${name}.xml
					sed -i -e 's/xPROD/'${prod}'/g' ${path}/test_${prod}_${name}.xml
				fi


				cp ${path}/run_default.sh ${path}/run_${prod}_${name}.sh
				sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${name}.sh
				sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${name}.sh
				cp ${path}/run_default.sub ${path}/run_${prod}_${name}.sub
				sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${name}.sub
				sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${name}.sub
						
				condor_submit run_${prod}_${name}.sub
				#sleep 0.1s 
				cd -
			fi
		
			#rm ${path}/run_${prod}_${name}.sub
			#rm ${path}/run_${prod}_${name}.sh
			i=$((i+1))
		done
	done
done

