#!/bin/bash

binaries_dirs=$(find ./initial-utilities -maxdepth 1)

for directory in $binaries_dirs
do
  rm -fv $directory/*{.out,.o}
done