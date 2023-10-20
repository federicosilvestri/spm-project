#!/usr/bin/env bash


IN_FILE="/data1/spm/100MB.txt"
OUT_FILE="/tmp/spm.txt"

TIME_SEQ=$(./spm_project SEQ "$IN_FILE"  "$OUT_FILE" 0 -M | grep "TOTAL=" | sed "s/TOTAL=//g" | sed "s/ns//g")
TIME_PAR=$(./spm_project THR "$IN_FILE"  "$OUT_FILE" 10 -M | grep "TOTAL=" | sed "s/TOTAL=//g" | sed "s/ns//g")

bc -l <<< "$TIME_SEQ/$TIME_PAR"

