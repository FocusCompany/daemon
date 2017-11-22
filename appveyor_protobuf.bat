setlocal

echo Building Protobuf Library 
mkdir install
cd protobuf-3.5.0/cmake
mkdir build
cd build
mkdir solution
cd solution
cmake -G "Visual Studio 15 2017" -DCMAKE_INSTALL_PREFIX=../../../../install -Dprotobuf_BUILD_TESTS=OFF ../..
msbuild protobuf.sln /target:INSTALL || goto error
goto :EOF

:error
echo Failed!
EXIT /b %ERRORLEVEL%
