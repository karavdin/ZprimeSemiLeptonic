#! /bin/sh
module use -a /afs/desy.de/group/cms/modulefiles/  
module load root/5.34

for sG in 0.001 0.01 0.1 0.2 0.4 0.6 0.8 1 10 100
do
    for sC in  0.01 0.1 1 1 5 10 50 100 500 1000 
    do
	#echo "start for sG=${sG} and sC=${sC}"
	root -b -q ./Zprime_vs_QCD_TMVAClassification_SVMoptimisation.C\(\"SVM\",\"${sG}\",\"${sC}\"\) &> LOG_SVMopt_2/sG_${sG}_sC_${sC}
	echo "done for sG=${sG} and sC=${sC}"
    done
done
