setlocal

mkdir install
IF NOT exist "protobuf-3.5.0" (
   echo Building Protobuf Library
   curl -L -o protobuf.zip https://github.com/google/protobuf/releases/download/v3.5.0/protobuf-all-3.5.0.zip
   7z x protobuf.zip
   del /Q protobuf.zip
   cd protobuf-3.5.0/cmake
   mkdir build
   cd build
   mkdir solution
   cd solution
   cmake -G "Visual Studio 15 2017" -DCMAKE_INSTALL_PREFIX=../../../../install -Dprotobuf_BUILD_TESTS=OFF ../..
   msbuild protobuf.sln || goto error
) ELSE (
  echo Using cached protobuf
  cd protobuf-3.5.0/cmake/build/solution
)
echo Installing Protobuf Library 
msbuild INSTALL.vcxproj || goto error
echo Moving Protobuf Library to C:\... 
move "C:\projects\daemon\install" "C:\Program Files\protobuf"
echo Protobuf successfully installed
goto :EOF

:error
echo Failed!
EXIT /b %ERRORLEVEL%
