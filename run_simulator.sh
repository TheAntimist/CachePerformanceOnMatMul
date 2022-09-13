#!/bin/sh
# Run Simulator on input traces 

input_file=${1:-'traces/'}   #Pass absolute path
#input_config=${2:-'../config/config_arch1.yaml'}
if [[ -z "${SIM_CONFIG}" ]]; then
input_config=${2:-'../config/config_simple_multilevel'}
else
input_config="${SIM_CONFIG}"
fi
echo "Using Input Config ${input_config}"
cd Simulator/src/

for entry in $input_file/*.out
do
  f=$(echo "${entry##*/}");
  tracename=$(echo $f| cut  -d'.' -f 1);
  echo $tracename	
  filename="${tracename}_stats.out"
  echo "Running $tracename on simulator"
  time ./cache_simulator.py -pdc ${input_config} -t $entry | tee stats.txt
  mv cache_simulator.log $filename  
done
mv *_stats.out $input_file/
cd -
mv -v traces/* /content/drive/MyDrive/final_traces
