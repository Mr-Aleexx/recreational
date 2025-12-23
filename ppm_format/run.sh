#!/bin/bash

if [ $# -eq 0 ]
  then
    echo -e "Error \nUsage : ./run.sh <file_output.ppm>"
    exit 1
fi

if [[ $1 != *.ppm  ]] 
  then
    echo -e "Error \nOutput file must be a ppm format file"
    exit
fi

#Remove extension
no_extension=${1%%.*}
echo $no_extension

# Adding the .png extension
png_ext="${no_extension}.png"

gcc first_time_ppm.c -o first_time_ppm
./first_time_ppm "$1"
convert $1 $png_ext
imgcat $png_ext
