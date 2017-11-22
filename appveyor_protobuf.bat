setlocal

echo Building Protobuf Library 
curl -L -o protobuf.zip https://github.com/google/protobuf/releases/download/v3.5.0/protobuf-all-3.5.0.zip
7z x protobuf.zip
del /Q protobuf.zip
mkdir install
cd protobuf-3.5.0/cmake
mkdir build
cd build
mkdir solution
cd solution
cmake -G "Visual Studio 15 2017" -DCMAKE_INSTALL_PREFIX=../../../../install -Dprotobuf_BUILD_TESTS=OFF ../..
msbuild protobuf.sln || goto error
echo Installing Protobuf Library 
msbuild INSTALL.vcxproj || goto error
cd ../../../../
echo Moving Protobuf Library to C:\... 
move "install\" "C:\Program Files\protobuf\"
echo Protobuf successfully installed
goto :EOF

:error
echo Failed!
EXIT /b %ERRORLEVEL%
