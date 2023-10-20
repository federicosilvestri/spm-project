#!/usr/bin/env bash
set -e

DATASET_FOLDER="dataset/"
FILE_OUT_FOLDER="out/"
RESULTS_FOLDER="results/"

#
# This is the number of samples to collect in order to detect possible outliers.
# It represent how many time you want to run the program.
#
EXEC_N=1

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

#
# Minimum file size (in millions of characters)
#
MIN_FILE_SIZE=50

#
# Maximum file size (in millions of characters)
#
MAX_FILE_SIZE=50

#
# File size step
#
FILE_SIZE_STEP=50


# Output file
FILE_OUT="$FILE_OUT_FOLDER/out.txt";
FILE_OUT="$FILE_OUT_FOLDER/out.txt";

# The compiled program must be here and must be named spm_project
if [ ! -f "spm_project" ]; then
    echo "Cannot find the executable file"
    exit 1
fi

# Dataset generation
if [ ! -d "$DATASET_FOLDER" ]; then
  mkdir -p "$DATASET_FOLDER"

  # Generate the dataset
  for ((s=MIN_FILE_SIZE; s<=MAX_FILE_SIZE; s+=FILE_SIZE_STEP)); do
    echo -ne "Generating dataset with size=$s/$MAX_FILE_SIZE\r"
    python b_tools/ds_generator.py -M -o "$DATASET_FOLDER/file_$s.txt" -U "$s" > /dev/null
  done
  echo -e "\nDone!"
else
  echo "Dataset already exist!"
fi

rm -rf $FILE_OUT_FOLDER && mkdir -p $FILE_OUT_FOLDER
rm -rf $RESULTS_FOLDER && mkdir -p $RESULTS_FOLDER


#
# Iterating for file size
#
for ((s=MIN_FILE_SIZE; s<=MAX_FILE_SIZE; s+=FILE_SIZE_STEP)); do
  FILE_IN="$DATASET_FOLDER/file_$s.txt"


  #
  # Sequential benchmarking
  #
  echo "Starting SEQ benchmark"
  SEQ_TEMP_RESULT_FILE="$RESULTS_FOLDER/seq.temp.txt"
  echo "Executing the sequential version"
  for ((i=0; i<EXEC_N; i++)); do
    echo -ne "Executing $((i+1))/$EXEC_N\r"
    ./spm_project SEQ "$FILE_IN" "$FILE_OUT" 0 -M >> $SEQ_TEMP_RESULT_FILE
  done
  # parse the file into csv
  python b_tools/output_parser.py $SEQ_TEMP_RESULT_FILE "$RESULTS_FOLDER/sequential_$s.csv"
#  rm $SEQ_TEMP_RESULT_FILE
  echo "SEQ benchmark finished"


  #
  # Parallel benchmarking (THR)
  #
  echo "Starting THR benchmark"
  for ((p=MIN_P_DEGREE; p<=MAX_P_DEGREE; p+=P_DEGREE_STEP)); do
    echo "P_DEGREE = $p"
    THR_TEMP_RESULT_FILE="$RESULTS_FOLDER/thr_$p.temp.txt"
    for ((i=0; i<EXEC_N;i++)); do
      echo -ne "Executing $((i+1))/$EXEC_N\r"
      ./spm_project THR "$FILE_IN" "$FILE_OUT" "$p" -M >> $THR_TEMP_RESULT_FILE
    done
    ## parse the file into csv
    python b_tools/output_parser.py $THR_TEMP_RESULT_FILE "$RESULTS_FOLDER/thr_temp_$p.csv"
    rm $THR_TEMP_RESULT_FILE
    echo -e "\nDone!"
  done
  echo "Merging files"
  python b_tools/merge_results.py "$RESULTS_FOLDER/thr_temp_" "$MIN_P_DEGREE" "$MAX_P_DEGREE" "$P_DEGREE_STEP" "$RESULTS_FOLDER/thr_$s.csv"
#  echo "Deleting temp files..."
#  for ((p=MIN_P_DEGREE; p<=MAX_P_DEGREE; p+=P_DEGREE_STEP)); do
#    rm "$RESULTS_FOLDER/thr_temp_$p.csv"
#  done
  echo "THR benchmark finished"


  #
  # Parallel benchmarking (FF)
  #

  # @TODO
done

echo "Done"
