#!/bin/bash                                                                                                                          
for i in {0..148}
do  
    name=$[10000+$i]
    
    cp test_kt_test.xml test_kt_$name.xml
    sed -i -e 's/xNAMEfile/'$name'/g' test_kt_$name.xml
    cp kt_test.sh kt_$name.sh
    sed -i -e 's/xNAMEfile/'$name'/g' kt_$name.sh
    cp kt_test.sub kt_$name.sub   
    sed -i -e 's/xNAMEfile/'$name'/g' kt_$name.sub
    if [ -f $name.root ]; then
	echo "Skip "$name
    else
	echo "Submit --- > " $name
	condor_submit kt_$name.sub
	sleep 0.1s
    fi
done

