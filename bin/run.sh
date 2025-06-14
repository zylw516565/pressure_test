#!/bin/sh
# usage:
#    ./run.sh <压测总时长,单位s>

# set -x

[ $# -ne 1 ] && echo "usage $0 <TotalRunTime>" && exit 1
echo "TotalRunTime:$1s"

SOURCE_DIR=`pwd`
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SOURCE_DIR

./PressureTest $1
