setlocal

mkdir install-protobuf
IF NOT exist "protobuf-3.5.1" (
   echo Building Protobuf Library
   curl -L -o protobuf.zip https://github.com/google/protobuf/releases/download/v3.5.1/protobuf-all-3.5.1.zip
   7z x protobuf.zip
   del /Q protobuf.zip
   cd protobuf-3.5.1
   mkdir tmp
   cd tmp
   cmake -G "NMake Makefiles" -Dprotobuf_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="../../install-protobuf" ../cmake
   nmake
) ELSE (
  echo Using cached protobuf
  cd protobuf-3.5.1/tmp
)
echo Installing Protobuf Library 
nmake install
echo Moving Protobuf Library to C:\... 
move "C:\projects\daemon\install-protobuf" "C:\Program Files\Focus\protobuf"
echo Protobuf successfully installed