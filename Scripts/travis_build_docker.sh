#!/usr/bin/env bash

set -e

if [ $# -eq 0 ]
  then
    docker build -t sunghwan19/2048pp .
else
    docker build -f $1 -t sunghwan19/2048pp:$2 .
fi

docker run sunghwan19/2048pp