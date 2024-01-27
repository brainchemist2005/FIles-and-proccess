#!/bin/sh -x
# Script généré automatiquement à partir de test_autorestart.sh.in

BASE=/home/zack/Desktop/INF3173/FIles-and-proccess/cmake-build-debug/bin
export PATH="$BASE:$PATH"

autorestart montecarlo | tee log.txt

grep -i "Success" log.txt
