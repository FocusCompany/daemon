setlocal

echo Building Protobuf Library 
mkdir install
dir
cd protobuf-3.5.0
mkdir build_protobuf
cd build_protobuf
mkdir solution
cd solution
cmake -G "Visual Studio 15 2017" -DCMAKE_INSTALL_PREFIX=../../../../install -Dprotobuf_BUILD_TESTS=OFF ../..
msbuild protobuf.sln || goto error
goto :EOF

:error
echo Failed!
EXIT /b %ERRORLEVEL%
