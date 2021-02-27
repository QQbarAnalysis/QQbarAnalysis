#!/bin/bash


model=l5
chiral=eLpR
#id=15161
id=15162

# dir=/group/ilc/users/yokugawa/QQbar250/${model}/${chiral}/${id}/000
dir=/group/ilc/users/yokugawa/QQbar250/${model}/${chiral}/${id}/proc_2021

if [ ! -d "$dir" ]; then
	echo "The directory does not exist."
	exit 1
else
	echo ${dir}
	hadd -f ${dir}/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.MERGE50.root ${dir}/QQbarProcessor_out/*.root
fi

