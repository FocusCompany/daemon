setlocal

echo Building Protobuf Library 
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
move install C:\Program Files\protobuf\
goto :EOF

:error
echo Failed!
EXIT /b %ERRORLEVEL%
