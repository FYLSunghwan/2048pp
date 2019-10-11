#!/usr/bin/env bash

set -e

if [ $# -eq 0 ]
  then
    docker build -t FYLSunghwan/2048pp .
else
    docker build -f $1 -t FYLSunghwan/2048pp:$2 .
fi

docker run FYLSunghwan/2048pp