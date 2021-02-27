#!/bin/bash

inputxml=qqbar250_steer.xml

# chiral
chiral=eLpR

# model
model=l5

# Process ID
#processID=15161
processID=15162

dirin=/group/ilc/grid/storm/prod/ilc/mc-2020/ild/dst-merged/250-SetA/2f_hadronic_eL_pR/ILD_l5_o1_v02/v02-02/000${processID}/000/

#nfile=10
#nfile=-1
nfile=50
#nfile=12
#nfile=1
#nperjob=50

nperjob=3
./submit2 $dirin $processID 1 $nfile $nperjob $inputxml $model $chiral
