#!/bin/bash                                                                                                                          
for i in {1..9}
do  
    name="7638_0000"$i
    cp test_kt_0.xml test_kt_$name.xml
    sed -i -e 's/xNAMEfile/'$name'/g' test_kt_$name.xml
    cp kt_0.sh kt_$name.sh
    sed -i -e 's/xNAMEfile/'$name'/g' kt_$name.sh
    cp kt_0.sub kt_$name.sub   
    sed -i -e 's/xNAMEfile/'$name'/g' kt_$name.sub
    if [ -f $name.root ]; then
	echo "Skip "$name
    else
	echo "Submit --- > " $name
	condor_submit kt_$name.sub
	sleep 0.1s
    fi
done

for i in {10..99}
do  
    name="7638_000"$i
    cp test_kt_0.xml test_kt_$name.xml
    sed -i -e 's/xNAMEfile/'$name'/g' test_kt_$name.xml
    cp kt_0.sh kt_$name.sh
    sed -i -e 's/xNAMEfile/'$name'/g' kt_$name.sh
    cp kt_0.sub kt_$name.sub   
    sed -i -e 's/xNAMEfile/'$name'/g' kt_$name.sub
    if [ -f $name.root ]; then
	echo "Skip "$name
    else                                                                                  
        echo "Submit --- > " $name
	condor_submit kt_$name.sub
	sleep 0.1s
    fi
done

for i in {100..177}
do  
    name="7638_00"$i
    cp test_kt_0.xml test_kt_$name.xml
    sed -i -e 's/xNAMEfile/'$name'/g' test_kt_$name.xml
    cp kt_0.sh kt_$name.sh
    sed -i -e 's/xNAMEfile/'$name'/g' kt_$name.sh
    cp kt_0.sub kt_$name.sub   
    sed -i -e 's/xNAMEfile/'$name'/g' kt_$name.sub
    if [ -f $name.root ]; then
	echo "Skip "$name                                         
    else       
	echo "Submit --- > " $name
	condor_submit kt_$name.sub
	sleep 0.1s
    fi
done
