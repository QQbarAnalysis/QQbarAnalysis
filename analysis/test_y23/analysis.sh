#root -l -q analysis.cc\(\"/home/irles/WorkArea/BBbar/ntuples/bbbar_250GeV_DBD_eL_genkt_durham_cambridge.root\"\)
root -l -q analysis.cc\(\"/home/irles/WorkArea/BBbar/ntuples/bbbar_250GeV_DBD_eR_genkt_durham_cambridge.root\"\)
root -l -q analysis.cc\(\"/home/irles/WorkArea/BBbar/ntuples/bbbar_250GeV_DBD_eL_genkt_durham_cambridge.root\"\)


#> output_analysis_signal_inclusive.log 
#root -l -q analysis.cc\(\"/home/irles/WorkArea/BBbar/ntuples/bbbar_250GeV_DBD_eL_genkt_durham_cambridge.root\",0.8,0.8\) > output_analysis_signal_exclusive.log
#root -l -q analysis.cc\(\"/home/irles/WorkArea/BBbar/ntuples/bbbar_250GeV_DBD_eL_genkt_durham_cambridge_inc35.root\",0.8,0.8\) > output_analysis_signal_inclusive_35.log 
#root -l -q analysis.cc\(\"/home/irles/WorkArea/BBbar/ntuples/bbbar_250GeV_DBD_eL_genkt_durham_cambridge_inc35.root\",0.8,0.8,false\) > output_analysis_signal_exclusive_35.log 

#bbbar_250GeV_DBD_eL_radret_genkt_durham_cambridge.root\",0.8,0.8\) > output_analysis.log & 
#root -l -q analysis.cc\(\"bbbar_250GeV_DBD_eL_radret_genkt_durham_cambridge.root\",0.8,0.8,false\)
