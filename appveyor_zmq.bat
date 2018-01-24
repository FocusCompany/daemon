setlocal

IF NOT exist "libzmq-4.2.3" (
   echo Building ZMQ Library
   curl -L -o libzmq.zip https://github.com/zeromq/libzmq/archive/v4.2.3.zip
   7z x libzmq.zip
   del /Q libzmq.zip
   cd libzmq-4.2.3
   mkdir install-zmq
   mkdir build
   cd build
   cmake -G "NMake Makefiles" -DZMQ_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="../install-zmq" -DBUILD_STATIC=OFF ..
   nmake install
) ELSE (
  echo Using cached ZMQ
)
echo Installing ZMQ Library
echo Moving ZMQ Library to C:\...
xcopy "C:\projects\daemon\libzmq-4.2.3\install-zmq" "C:\Program Files\Focus\zmq" /E /I
echo ZMQ successfully installed