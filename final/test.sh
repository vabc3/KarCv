#!/bin/sh

SIC=~/prog/opencv/final/src/sic
for p in $*;
do
	echo "[$p]";
	$SIC -m -p $p |sed -n "/^1\./p;"	
done;
