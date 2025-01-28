project(mychem)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

cmake_minimum_required(VERSION 3.10.0)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

# this is adapted from KDE's FindKDE4Internal.cmake : default the build type to
# "release with debug info".
#
# We will define two other build types: Debug and Release.
# These names are case-insensitive i.e. you can do -DCMAKE_BUILD_TYPE=debug
if (NOT CMAKE_BUILD_TYPE)
   message( "Build Type not set, defaulting to Debug..." )
   set(CMAKE_BUILD_TYPE Debug)
endif (NOT CMAKE_BUILD_TYPE)

message(STATUS "The build type is ${CMAKE_BUILD_TYPE}")

include (CheckCXXCompilerFlag)

# Mychem version number.
set(MYCHEM_VERSION_MAJOR 2)
set(MYCHEM_VERSION_MINOR 0)
set(MYCHEM_VERSION_RELEASE 0)
set(MYCHEM_VERSION "${MYCHEM_VERSION_MAJOR}.${MYCHEM_VERSION_MINOR}.${MYCHEM_VERSION_RELEASE}")

#-----------------------------------------------------------------------------
# Define test environment
#-----------------------------------------------------------------------------

if (NOT MY_DB)
  set (MY_DB "mysql")
endif (NOT MY_DB)

if (MY_HOST AND MY_USER AND MY_PASSWD)
  set(MY_ARGS -h ${MY_HOST} -u ${MY_USER} -p ${MY_PASSWD} -b ${MY_DB})
  enable_testing()
  message( STATUS "Test module enabled" )
else (MY_HOST AND MY_USER AND MY_PASSWD)
  if (MY_HOST AND MY_USER)
    set(MY_ARGS -h ${MY_HOST} -u ${MY_USER} -b ${MY_DB})
    enable_testing()
    message( STATUS "Test module enabled" )
  else (MY_HOST AND MY_USER)
    message( STATUS "Test module disabled" )
  endif (MY_HOST AND MY_USER)
endif (MY_HOST AND MY_USER AND MY_PASSWD)

option(BUILD_SHARED "enable static build support" ON)


#-----------------------------------------------------------------------------
# Software dependency
#-----------------------------------------------------------------------------

include( FindPkgConfig )

# Open Babel dependency
find_package( OpenBabel REQUIRED )

# MySQL
find_package( MySQL REQUIRED )


#-----------------------------------------------------------------------------
# Installation directory
#-----------------------------------------------------------------------------

message(STATUS "Mychem installation directory: ${PLUGIN_DIR}")

#-----------------------------------------------------------------------------
# Set platform specific stuff
#-----------------------------------------------------------------------------

include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckSymbolExists)
include(CheckTypeSize)
include(CheckCSourceCompiles)

check_include_file(stdlib.h   HAVE_STLID_H)
check_include_file(stdio.h       HAVE_STDIO_H)
check_include_file(string.h   HAVE_STRING_H)
check_include_file_cxx(sstream  HAVE_SSTREAM)

if (UNIX)
  if (APPLE)
    set(CMAKE_INSTALL_NAME_DIR ${LIB_INSTALL_DIR})
  endif (APPLE)
endif (UNIX)

if (APPLE)
  set (CMAKE_SHARED_LINKER_FLAGS "-single_module -multiply_defined suppress ${CMAKE_SHARED_LINKER_FLAGS}")
  set (CMAKE_MODULE_LINKER_FLAGS "-multiply_defined suppress ${CMAKE_MODULE_LINKER_FLAGS}")
  set (CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -fno-common")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-common")
endif (APPLE)

if (CMAKE_SYSTEM_NAME MATCHES Linux)
  # Fix a bug with dynamic plugin
  add_definitions( -D__CYGWIN__)

  if (CMAKE_COMPILER_IS_GNUCXX)
    set (CMAKE_SHARED_LINKER_FLAGS "-Wl,--fatal-warnings -Wl,--no-undefined -lc ${CMAKE_SHARED_LINKER_FLAGS}")
    set (CMAKE_MODULE_LINKER_FLAGS "-Wl,--fatal-warnings -Wl,--no-undefined -lc ${CMAKE_MODULE_LINKER_FLAGS}")

    set (CMAKE_SHARED_LINKER_FLAGS "-Wl,--enable-new-dtags ${CMAKE_SHARED_LINKER_FLAGS}")
    set (CMAKE_MODULE_LINKER_FLAGS "-Wl,--enable-new-dtags ${CMAKE_MODULE_LINKER_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "-Wl,--enable-new-dtags ${CMAKE_EXE_LINKER_FLAGS}")
  endif (CMAKE_COMPILER_IS_GNUCXX)

  if (CMAKE_C_COMPILER MATCHES "icc")
    set ( CMAKE_SHARED_LINKER_FLAGS "-Wl,--fatal-warnings -Wl,--no-undefined -lc ${CMAKE_SHARED_LINKER_FLAGS}")
    set ( CMAKE_MODULE_LINKER_FLAGS "-Wl,--fatal-warnings -Wl,--no-undefined -lc ${CMAKE_MODULE_LINKER_FLAGS}")
  endif (CMAKE_C_COMPILER MATCHES "icc")

endif (CMAKE_SYSTEM_NAME MATCHES Linux)


#-----------------------------------------------------------------------------
# Compiler specific settings
#-----------------------------------------------------------------------------

if (CMAKE_SYSTEM_NAME MATCHES Linux)
  set( CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wno-long-long -Wundef -Wcast-align -Werror-implicit-function-declaration -Wchar-subscripts -Wall -W -Wpointer-arith -Wwrite-strings -Wformat-security -Wmissing-format-attribute -fno-common")
  set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wnon-virtual-dtor -Wno-long-long -ansi -Wundef -Wcast-align -Wchar-subscripts -Wall -W -Wpointer-arith -Wformat-security -fno-check-new -fno-common")
endif (CMAKE_SYSTEM_NAME MATCHES Linux)

# The compilation has only been tested with GCC.
if (CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS_RELEASE        "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g")
  set(CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG -g3 -fno-inline -fno-reorder-blocks -fno-schedule-insns")
  set(CMAKE_C_FLAGS_RELEASE          "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")
  set(CMAKE_C_FLAGS_RELWITHDEBINFO   "${CMAKE_C_FLAGS_RELWITHDEBINFO} -O2 -g")
  set(CMAKE_C_FLAGS_DEBUG            "${CMAKE_C_FLAGS_DEBUG} -g -O2 -fno-reorder-blocks -fno-schedule-insns -fno-inline")


  # get the gcc version
  exec_program(${CMAKE_C_COMPILER} ARGS --version OUTPUT_VARIABLE _gcc_version_info)

  string (REGEX MATCH "[345]\\.[0-9]\\.[0-9]" _gcc_version "${_gcc_version_info}")
   # gcc on mac just reports: "gcc (GCC) 3.3 20030304 ..." without the patch level, handle this here:
  if (NOT _gcc_version)
      string (REGEX REPLACE ".*\\(GCC\\).* ([34]\\.[0-9]) .*" "\\1.0" _gcc_version "${_gcc_version_info}")
   endif (NOT _gcc_version)

endif (CMAKE_COMPILER_IS_GNUCXX)


#-----------------------------------------------------------------------------
# Subdirectories
#-----------------------------------------------------------------------------

add_subdirectory( include )
add_subdirectory( src )
add_subdirectory( tests )
