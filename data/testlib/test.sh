#!/bin/sh

SIC=~/prog/opencv/final/src/sic
DIR=`pwd`

for p in $*;
do
	echo "[$p]";
	mkdir $p.d
	$SIC -m -p $p -f $p.d |sed -n "/^1\./p;"
	sed s/_/\\\\_/g $p.d/index.tex >> index.tex
done;
