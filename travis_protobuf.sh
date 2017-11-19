#!/usr/bin/env bash

set -e
cd $HOME/protobuf/

if [ ! -d "$HOME/protobuf/lib" ]; then
  wget https://github.com/google/protobuf/archive/v3.5.0.tar.gz -O proto
  tar -xzf proto
  if [[ $1 = "osx" ]]; then
    cd protobuf-3.5.0 && ./autogen.sh && ./configure && make && sudo make install
  else
    cd protobuf-3.5.0 && ./autogen.sh && ./configure --prefix=/usr && make && sudo make install
  fi
else
  echo "Using cached directory."
  cd protobuf-3.5.0 && sudo make install
fi

cd $HOME/build/FocusCompany/daemon/Shared/Proto/
chmod +x generate.sh
./generate.sh