#!/usr/bin/env bash

set -e
cd $HOME/jwt-cpp/

if [ ! -d "$HOME/jwt-cpp/release" ]; then
  echo "Building JWT Library"
  mkdir release
  git clone https://github.com/pokowaka/jwt-cpp.git
  cd release
  cmake -DCMAKE_BUILD_TYPE=Release ../jwt-cpp/
  fi
else
  echo "Using cached JWT"
  cd release
fi
echo "Installing JWT Library"
sudo make install
echo "JWT successfully installed"
