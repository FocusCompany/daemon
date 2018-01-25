#!/usr/bin/env bash

set -e
cd $HOME/protobuf/

if [ ! -d "$HOME/protobuf/protobuf-3.5.1" ]; then
  echo "Building Protobuf Library"
  wget https://github.com/google/protobuf/releases/download/v3.5.1/protobuf-all-3.5.1.tar.gz -O protobuf.tar.gz
  tar -xzf protobuf.tar.gz
  rm protobuf.tar.gz
  if [[ $1 = "osx" ]]; then
    cd protobuf-3.5.1 && ./autogen.sh && ./configure && make
  else
    cd protobuf-3.5.1 && ./autogen.sh && ./configure --prefix=/usr && make
  fi
else
  echo "Using cached protobuf"
  cd protobuf-3.5.1
fi
echo "Installing Protobuf Library to /usr or /usr/local/ (Linux/Mac)"
sudo make install
echo "Protobuf successfully installed"
