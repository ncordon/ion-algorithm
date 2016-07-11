#!/bin/bash

files="solidstate normalization condsolid localsearch"

for f in $files
do
    source-highlight -f latexcolor -i ${f}.rb -o ${f}.tex
done
