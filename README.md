# Daemon
[![Build Status](https://travis-ci.org/FocusCompany/daemon.svg?branch=master)](https://travis-ci.org/FocusCompany/daemon)
[![Build status](https://ci.appveyor.com/api/projects/status/u00q9kpab61t2ql3/branch/master?svg=true)](https://ci.appveyor.com/project/EtiennePasteur/daemon/branch/master)

## Installation
First take a look at the dependencies bellow, you should install all the dependencies to successfully compile the Focus Daemon. Once done just run the following commands in the root directory of the repository
```bash
mkdir build
cd build

cmake .. (Linux)  /or/  cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Debug .. (Windows)
make     (Linux)  /or/  nmake                                                  (Windows)
```
Then simply run the generated executable depending on the platform where you have build the daemon.
### Dependencies
#### All Platform
    - Protobuf 3 (https://github.com/google/protobuf)
    - OpenSSL
    - ZeroMQ (https://github.com/zeromq/libzmq)
    - Jwt-cpp (https://github.com/pokowaka/jwt-cpp)
#### Linux
    - libx11-dev
    - libxmu-dev
    - libxss-dev
    - libwebkit2gtk-4.0-dev
#### MacOs
    - Carbon    
## Class Diagram
![placeholder](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/FocusCompany/Daemon/master/docs/daemon.puml)
## Protobuf Envelope
![placeholder](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/FocusCompany/protobuf_envelope/master/docs/protobuf_envelope.puml)
