#!/usr/bin/env bash
set -e

FILE_IN="dataset/file.txt"
FILE_OUT_FOLDER="out"
FILE_OUT="$FILE_OUT_FOLDER/out.temp.txt"
RESULTS_FOLDER="results/"

#
# This is the number of samples to collect in order to detect possible outliers.
# It represent how many time you want to run the program.
#
EXEC_N=5

#
# MINIMUM P_DEGREE (=1 by default)
#
MIN_P_DEGREE=1

#
# Maximum P_DEGREE
#
MAX_P_DEGREE=20

#
# Degree step (1 is the best, more granular)
#
P_DEGREE_STEP=1

# The compiled program must be here and must be named spm_project
if [ ! -f "spm_project" ]; then
    echo "Cannot find the executable file"
    exit 1
fi

# Also the file to be compressed must be here!
if [ ! -f $FILE_IN ]; then
  echo "Cannot find the file to be compressed"
  exit 1
fi

rm -rf $FILE_OUT_FOLDER && mkdir -p $FILE_OUT_FOLDER
rm -rf $RESULTS_FOLDER && mkdir -p $RESULTS_FOLDER


echo "Starting SEQ benchmark"
SEQ_TEMP_RESULT_FILE="$RESULTS_FOLDER/seq.temp.txt"
# Start the program
echo "Executing the sequential version"
for ((i=0; i<EXEC_N; i++)); do
  echo -ne "Executing $i/$EXEC_N\r"
  ./spm_project SEQ "$FILE_IN" "$FILE_OUT" 0 -M >> $SEQ_TEMP_RESULT_FILE
done


# parse the file into csv
python b_tools/output_parser.py $SEQ_TEMP_RESULT_FILE "$RESULTS_FOLDER/sequential.csv"
rm $SEQ_TEMP_RESULT_FILE
echo "SEQ benchmark finished"

echo "Starting THR benchmark"
for ((p=MIN_P_DEGREE; p<=MAX_P_DEGREE; p+=P_DEGREE_STEP)); do
  echo "P_DEGREE = $p"
  THR_TEMP_RESULT_FILE="$RESULTS_FOLDER/thr_$p.temp.txt"
  for ((i=0; i<EXEC_N;i++)); do
    echo -ne "Executing $i/$EXEC_N\r"
    ./spm_project THR "$FILE_IN" "$FILE_OUT" "$p" -M >> $THR_TEMP_RESULT_FILE
  done
  ## parse the file into csv
  python b_tools/output_parser.py $THR_TEMP_RESULT_FILE "$RESULTS_FOLDER/thr_$p.csv"
  rm $THR_TEMP_RESULT_FILE
  echo -e "\nDone!"
done
echo "Merging files"
python b_tools/merge_results.py "$RESULTS_FOLDER/thr_" "$MIN_P_DEGREE" "$MAX_P_DEGREE" "$P_DEGREE_STEP" "$RESULTS_FOLDER/thr.csv"
echo "Deleting temp files..."
for ((p=MIN_P_DEGREE; p<=MAX_P_DEGREE; p+=P_DEGREE_STEP)); do
  rm "$RESULTS_FOLDER/thr_$p.csv"
done
echo "SEQ benchmark finished"
