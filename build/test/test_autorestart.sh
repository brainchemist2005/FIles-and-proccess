#!/bin/sh -x
# Script généré automatiquement à partir de test_autorestart.sh.in

BASE=/home/rabahlemaici/Bureau/FIles-and-proccess/build/bin
export PATH="$BASE:$PATH"

autorestart montecarlo | tee log.txt

grep -i "Success" log.txt
