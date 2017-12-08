# Daemon
[![Build Status](https://travis-ci.org/FocusCompany/daemon.svg?branch=master)](https://travis-ci.org/FocusCompany/daemon)
[![Build status](https://ci.appveyor.com/api/projects/status/u00q9kpab61t2ql3?svg=true)](https://ci.appveyor.com/project/EtiennePasteur/daemon)

## Installation
First take a look at the dependencies bellow, you should install all the dependencies to successfully compile the Focus Daemon. Once done just run the following commands in the root directory of the repository
```bash
mkdir build
cd build
cmake ..

make                                                                        //For Linux/Mac users
msbuild daemon.sln /property:Configuration=Debug /property:Platform=Win32   //For Windows users
```
Then simply run the generated executable depending on the platform where you have build the daemon.
### Dependencies
#### Protobuf
##### On windows :
```bash
mkdir tmp
cd tmp
mkdir install
curl -L -o protobuf.zip https://github.com/google/protobuf/releases/download/v3.5.0/protobuf-all-3.5.0.zip
7z x protobuf.zip
del /Q protobuf.zip
cd protobuf-3.5.0/cmake
mkdir build
cd build
mkdir solution
cd solution
cmake -G "Visual Studio 15 2017" -DCMAKE_INSTALL_PREFIX=../../../../install -Dprotobuf_BUILD_TESTS=OFF ../..
msbuild protobuf.sln
msbuild INSTALL.vcxproj
move "C:\....\tmp\install" "C:\Program Files\protobuf"
```
##### On Linux/Mac:
```bash
wget https://github.com/google/protobuf/releases/download/v3.5.0/protobuf-all-3.5.0.tar.gz -O protobuf.tar.gz
tar -xzf protobuf.tar.gz
rm protobuf.tar.gz
cd protobuf-3.5.0 && ./autogen.sh && ./configure && make                //For Mac users
cd protobuf-3.5.0 && ./autogen.sh && ./configure --prefix=/usr && make  //For Linux Users
sudo make install
```
## Class Diagram
![placeholder](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/FocusCompany/Daemon/master/daemon.puml)