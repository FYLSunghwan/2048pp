#!/usr/bin/env bash

set -e

if [ $# -eq 0 ]
  then
    docker build -t fylsunghwan/2048pp .
else
    docker build -f $1 -t fylsunghwan/2048pp:$2 .
fi

docker run fylunghwan/2048pp