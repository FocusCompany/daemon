setlocal

mkdir install-jwt
IF NOT exist "jwt-cpp" (
   echo Building jwt-cpp library
   git clone https://github.com/pokowaka/jwt-cpp.git
   cd jwt-cpp
   mkdir build
   cd build
   cmake -G "NMake Makefiles" -DOPENSSL_INCLUDE_DIRS=C:\OpenSSL-Win32\include -DOPENSSL_LIBRARY_DIRS=C:\OpenSSL-Win32\lib -DCMAKE_INSTALL_PREFIX="../../install-jwt" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS_DEBUG="/MTd" -DENABLE_DOC=OFF -DENABLE_TESTS=OFF ..
   nmake
) ELSE (
  echo Using cached jwt-cpp
  cd jwt-cpp/build
)
echo Installing jwt-cpp library
nmake install
echo Moving jwt-cpp ibrary to C:\...
move "C:\projects\daemon\install-jwt" "C:\Program Files\Focus\jwt-cpp"
echo Jwt-cpp successfully installed
