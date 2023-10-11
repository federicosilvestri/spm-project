#!/usr/bin/env bash
set -e

OUTPUT_FILE="out.temp.txt"
EXEC_N=20


# The compiled program must be here and must be named spm_project
if [ ! -f "spm_project" ]; then
    echo "Cannot find the executable file"
    exit 1
fi

# Also the file to be compressed must be here!
if [ ! -f "file.txt" ]; then
  echo "Cannot find the file to be compressed"
  exit 1
fi

# Start the program
echo "Executing the sequential version"
for ((i=0; i<EXEC_N; i++)); do
  echo "Executing $i/$EXEC_N"
  ./spm_project SEQ file.txt $OUTPUT_FILE 0 -M >> temp_results.txt
done
