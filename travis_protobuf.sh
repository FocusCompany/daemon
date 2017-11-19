#!/usr/bin/env bash

set -e

if [ ! -d "$HOME/protobuf/lib" ]; then
  wget https://github.com/google/protobuf/releases/download/v3.5.0/protobuf-cpp-3.5.0.tar.gz -O proto
  tar -xzf proto
  cd protobuf-3.5.0 && ./configure --prefix=$HOME/protobuf && make && sudo make install
else
  echo "Using cached directory."
fi

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/travis/protobuf/lib