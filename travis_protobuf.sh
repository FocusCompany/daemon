#!/usr/bin/env bash

set -e

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
cd $HOME/protobuf/

if [ ! -d "$HOME/protobuf/lib" ]; then
  wget https://github.com/google/protobuf/archive/v3.5.0.tar.gz -O proto
  tar -xzf proto
  cd protobuf-3.5.0 && ./autogen.sh && ./configure && make && sudo make install
else
  echo "Using cached directory."
  cd protobuf-3.5.0 && sudo make install
fi