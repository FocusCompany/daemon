#!/usr/bin/env bash

set -e

cd $HOME/protobuf/

if [ ! -d "$HOME/protobuf/lib" ]; then
  wget https://github.com/google/protobuf/releases/download/v3.5.0/protobuf-cpp-3.5.0.tar.gz -O proto
  tar -xzf proto
  cd protobuf-3.5.0 && ./configure && make && sudo make install
else
  echo "Using cached directory."
  cd protobuf-3.5.0 && sudo make install
fi