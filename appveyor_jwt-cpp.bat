setlocal

mkdir install-jwt
IF NOT exist "jwt-cpp" (
   echo Building jwt-cpp library
   git clone https://github.com/pokowaka/jwt-cpp.git
   cd jwt-cpp
   mkdir build
   cd build
   cmake -G "Visual Studio 15 2017" -DCMAKE_INSTALL_PREFIX="../../install-jwt" -DOPENSSL_INCLUDE_DIRS=C:\OpenSSL-Win32\include -DOPENSSL_LIBRARY_DIRS=C:\OpenSSL-Win32\lib ..
   cmake --build . --clean-first
) ELSE (
  echo Using cached jwt-cpp
  cd jwt-cpp/build
)
echo Installing jwt-cpp library
cmake --build . --target install
echo Moving jwt-cpp ibrary to C:\...
move "C:\projects\daemon\install-jwt" "C:\Program Files\jwt-cpp"
echo Jwt-cpp successfully installed
