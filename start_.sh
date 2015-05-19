#!/bin/bash

#LD_LIBRARY_PATH="/usr/local/cuda-4.0/cuda/lib64;./;./libs;./lib64" ./haartraining -numPos 5 -numNeg 5 -data classifier -vec test.vec -bg negatives.dat -h 400 -w 400 -precalcValBufSize 1024 -precalcIdxBufSize 1024 -numStages 2

LD_LIBRARY_PATH="/usr/local/cuda-4.0/cuda/lib64;./;./libs;./lib64" ./haartraining -data nstages14_minhitrate0.9_maxfalsealarm0.4_npos800_nneg2600 -vec logo_positives.vec -bg negative_date_file.dat -nstages 14 -minhitrate 0.9 -maxfalsealarm 0.4 -npos 800  -nneg 2600 -w 40 -h 20 -mode ALL -precalcValBufSize 1024 -precalcIdxBufSize 1024
