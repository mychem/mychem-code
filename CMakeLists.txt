project(mychem)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

cmake_minimum_required(VERSION 2.6.0)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

# this is adapted from KDE's FindKDE4Internal.cmake : default the build type to
# "release with debug info".
#
# We will define two other build types: Debug and Release.
# These names are case-insensitive i.e. you can do -DCMAKE_BUILD_TYPE=debug
if (NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif (NOT CMAKE_BUILD_TYPE)

message(STATUS "The build type is ${CMAKE_BUILD_TYPE}")

include (CheckCXXCompilerFlag)
include (MacroEnsureVersion)

# Mychem version number.
set(MYCHEM_VERSION_MAJOR 0)
set(MYCHEM_VERSION_MINOR 9)
set(MYCHEM_VERSION_RELEASE 3)
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
find_package( OpenBabel2 REQUIRED )

# MySQL
find_package( MySQL REQUIRED )


#-----------------------------------------------------------------------------
# Installation directory
# Set the install path. Check the difference between 32bits and  64 bits
#-----------------------------------------------------------------------------

if (NOT LIB_INSTALL_DIR)
  if ("${MySQL_PLUGIN_DIR}" STREQUAL "")
    set( LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" )
  else ("${MySQL_PLUGIN_DIR}" STREQUAL "")
    set( LIB_INSTALL_DIR "${MySQL_PLUGIN_DIR}" )
  endif ("${MySQL_PLUGIN_DIR}" STREQUAL "")
endif (NOT LIB_INSTALL_DIR)
message(STATUS "Mychem installation directory: ${LIB_INSTALL_DIR}")


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

if (WIN32)
  # Set some generic values
  add_definitions( -DWIN32 -D__WIN__ )
  # add definitions for OB in WIN32
  add_definitions( -DUSING_OBDLL -DUSING_DYNAMIC_LIBS)

  if (CYGWIN)
    add_definitions( -D__CYGWIN__)
  endif (CYGWIN)

  if (MSVC)
    # check if it's better to use set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS or
    # add_definitions
    # 'class1' : inherits 'class2::member' via dominance
    add_definitions(-wd4250)
    # 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
    add_definitions(-wd4251)
    # non  DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
    add_definitions(-wd4275)
    # 'conversion' : truncation of constant value
    add_definitions(-wd4309)
    # 'identifier' : 'function' the inline specifier cannot be used when a friend declaration refers to a specialization of a function template
    add_definitions(-wd4396)
    # decorated name length exceeded
    add_definitions(-wd4503)
    # identifier was truncated to '255' characters in the debug information
    add_definitions(-wd4786)

    if (MINGW)
    add_definitions(-D__MINGW32__)
    endif (MINGW)

    if (CMAKE_COMPILER_2005)
        # Disable deprecation warnings for standard C and STL functions in
        # VS2005 and later
        add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE)
        add_definitions(-D_SCL_SECURE_NO_DEPRECATE)
        # 'identifier' : no suitable definition provided for explicit template instantiation request
        add_definitions(-wd4661)
    endif (CMAKE_COMPILER_2005)
  endif (MSVC)
endif (WIN32)

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

if (MSVC)
endif (MSVC)

if (CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
  set(CMAKE_CXX_FLAGS_RELEASE        "-O2 -DNDEBUG -DQT_NO_DEBUG")
  set(CMAKE_CXX_FLAGS_DEBUG          "-g -O2 -fno-reorder-blocks -fno-schedule-insns -fno-inline")
  set(CMAKE_CXX_FLAGS_DEBUGFULL      "-g3 -fno-inline")
  set(CMAKE_CXX_FLAGS_PROFILE        "-g3 -fno-inline -ftest-coverage -fprofile-arcs")
  set(CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 -g -std=gnu89")
  set(CMAKE_C_FLAGS_RELEASE          "-O2 -DNDEBUG -DQT_NO_DEBUG")
  set(CMAKE_C_FLAGS_DEBUG            "-g -O2 -fno-reorder-blocks -fno-schedule-insns -fno-inline")
  set(CMAKE_C_FLAGS_DEBUGFULL        "-g3 -fno-inline")
  set(CMAKE_C_FLAGS_PROFILE          "-g3 -fno-inline -ftest-coverage -fprofile-arcs")

  if (CMAKE_SYSTEM_NAME MATCHES Linux)
    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-long-long -std=iso9899:1990 -Wundef -Wcast-align -Werror-implicit-function-declaration -Wchar-subscripts -Wall -W -Wpointer-arith -Wwrite-strings -Wformat-security -Wmissing-format-attribute -fno-common")
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnon-virtual-dtor -Wno-long-long -ansi -Wundef -Wcast-align -Wchar-subscripts -Wall -W -Wpointer-arith -Wformat-security -fno-check-new -fno-common")
  endif (CMAKE_SYSTEM_NAME MATCHES Linux)

  # gcc under windows
  if (MINGW)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--export-all-symbols -Wl,--disable-auto-import")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,--export-all-symbols -Wl,--disable-auto-import")
  endif (MINGW)

  # get the gcc version
  exec_program(${CMAKE_C_COMPILER} ARGS --version OUTPUT_VARIABLE _gcc_version_info)

  string (REGEX MATCH "[345]\\.[0-9]\\.[0-9]" _gcc_version "${_gcc_version_info}")
   # gcc on mac just reports: "gcc (GCC) 3.3 20030304 ..." without the patch level, handle this here:
  if (NOT _gcc_version)
      string (REGEX REPLACE ".*\\(GCC\\).* ([34]\\.[0-9]) .*" "\\1.0" _gcc_version "${_gcc_version_info}")
   endif (NOT _gcc_version)

   macro_ensure_version("4.1.0" "${_gcc_version}" GCC_IS_NEWER_THAN_4_1)
   macro_ensure_version("4.2.0" "${_gcc_version}" GCC_IS_NEWER_THAN_4_2)
   macro_ensure_version("4.3.0" "${_gcc_version}" GCC_IS_NEWER_THAN_4_3)

   # save a little by making local statics not threadsafe
   # ### do not enable it for older compilers, see
   # ### http://gcc.gnu.org/bugzilla/show_bug.cgi?id=31806
   if (GCC_IS_NEWER_THAN_4_3)
       set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-threadsafe-statics")
   endif (GCC_IS_NEWER_THAN_4_3)

   set(_GCC_COMPILED_WITH_BAD_ALLOCATOR FALSE)
   if (GCC_IS_NEWER_THAN_4_1)
      exec_program(${CMAKE_C_COMPILER} ARGS -v OUTPUT_VARIABLE _gcc_alloc_info)
      string(REGEX MATCH "(--enable-libstdcxx-allocator=mt)" _GCC_COMPILED_WITH_BAD_ALLOCATOR "${_gcc_alloc_info}")
   endif (GCC_IS_NEWER_THAN_4_1)

endif (CMAKE_COMPILER_IS_GNUCXX)

if (CMAKE_C_COMPILER MATCHES "icc")

   # Select flags.
   set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
   set(CMAKE_CXX_FLAGS_RELEASE        "-O2 -DNDEBUG -DQT_NO_DEBUG")
   set(CMAKE_CXX_FLAGS_DEBUG          "-O2 -g -fno-inline -noalign")
   set(CMAKE_CXX_FLAGS_DEBUGFULL      "-g -fno-inline -noalign")
   set(CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 -g")
   set(CMAKE_C_FLAGS_RELEASE          "-O2 -DNDEBUG -DQT_NO_DEBUG")
   set(CMAKE_C_FLAGS_DEBUG            "-O2 -g -fno-inline -noalign")
   set(CMAKE_C_FLAGS_DEBUGFULL        "-g -fno-inline -noalign")

   set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -ansi -Wall -w1 -Wpointer-arith -fno-common")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi -Wall -w1 -Wpointer-arith -fno-exceptions -fno-common")
endif (CMAKE_C_COMPILER MATCHES "icc")


#-----------------------------------------------------------------------------
# Subdirectories
#-----------------------------------------------------------------------------

add_subdirectory( include )
add_subdirectory( src )
add_subdirectory( tests )
