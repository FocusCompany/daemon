cmake_minimum_required(VERSION 2.8.12)

# - Try to find JWTCPP
# Once done this will define
# JWTCPP_FOUND - System has JWTCPP
# JWTCPP_INCLUDE_DIRS - The JWTCPP include directories
# JWTCPP_LIBRARIES - The libraries needed to use JWTCPP
# JWTCPP_DEFINITIONS - Compiler switches required for using JWTCPP

find_path ( JWTCPP_INCLUDE_DIR jwt/jwt.h )
find_library ( JWTCPP_LIBRARY NAMES jwt )

set ( JWTCPP_LIBRARIES ${JWTCPP_LIBRARY} )
set ( JWTCPP_INCLUDE_DIRS ${JWTCPP_INCLUDE_DIR} )

include ( FindPackageHandleStandardArgs )
# handle the QUIETLY and REQUIRED arguments and set JWTCPP_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args ( JWTCPP DEFAULT_MSG JWTCPP_LIBRARY JWTCPP_INCLUDE_DIR )