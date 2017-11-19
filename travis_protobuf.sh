#!/usr/bin/env bash

set -e

if [ ! -d "$HOME/protobuf/lib" ]; then
  wget https://github.com/google/protobuf/releases/download/v3.5.0/protobuf-cpp-3.5.0.tar.gz
  tar -xzvf protobuf-cpp-3.5.0.tar.gz
  cd protobuf-cpp-3.5.0 && ./configure --prefix=$HOME/protobuf && make && make install
else
  echo "Using cached directory."
fi