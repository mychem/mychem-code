# - Try to find OpenBabel3
# Once done this will define
#"
#  OPENBABEL3_FOUND - system has OpenBabel
#  OPENBABEL3_INCLUDE_DIR - the OpenBabel3 include directory
#  OPENBABEL3_LIBRARIES - Link these to use OpenBabel3

# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

#
# Search for Open Babel 3 libraries and includes
#
if (OPENBABEL3_INCLUDE_DIR AND OPENBABEL3_LIBRARIES)
  # in cache already
  set(OPENBABEL3_FOUND TRUE)
else (OPENBABEL3_INCLUDE_DIR AND OPENBABEL3_LIBRARIES)

    include(UsePkgConfig)

    pkgconfig(openbabel-3 _obIncDir _obLinkDir _obLinkFlags _obCflags)

    # query pkg-config asking for a openbabel >= 3.0
    exec_program(${PKGCONFIG_EXECUTABLE} ARGS --atleast-version=3.0 openbabel-3 RETURN_VALUE _return_VALUE OUTPUT_VARIABLE _pkgconfigDevNull )
    if(_return_VALUE STREQUAL "0")
        set(OPENBABEL_MINI_FOUND TRUE)
    endif(_return_VALUE STREQUAL "0")
    message(STATUS "OPENBABEL_MINI_FOUND <${OPENBABEL_MINI_FOUND}>")

    exec_program(${PKGCONFIG_EXECUTABLE} ARGS --variable=pkgincludedir openbabel-3 RETURN_VALUE _return_VALUE OUTPUT_VARIABLE _obPkgIncDir )
    if (_obPkgIncDir)
        set(_obIncDir "${_obPkgIncDir}")
    endif (_obPkgIncDir)

    find_path(OPENBABEL3_INCLUDE_DIR openbabel/obconversion.h
        PATHS
        $ENV{OPENBABEL3_INCLUDE_DIR}
        ${_obIncDir}
        /usr/local/include
        /usr/include
    )

    find_library(OPENBABEL3_LIBRARIES NAMES openbabel
        PATHS
        ${_obLinkDir}
        $ENV{OPENBABEL3_LIBRARIES}
        /usr/lib
        /usr/local/lib
    )

    if(OPENBABEL3_INCLUDE_DIR AND OPENBABEL3_LIBRARIES AND OPENBABEL_MINI_FOUND)
        set(OPENBABEL3_FOUND TRUE)
    endif(OPENBABEL3_INCLUDE_DIR AND OPENBABEL3_LIBRARIES AND OPENBABEL_MINI_FOUND)
endif()

if (OPENBABEL3_FOUND)
    message(STATUS "Found OpenBabel3: ${OPENBABEL3_LIBRARIES}")
else (OPENBABEL3_FOUND)
    if (OPENBABEL3_FIND_REQUIRED)
        message(FATAL_ERROR "Could NOT find OpenBabel3")
    endif (OPENBABEL3_FIND_REQUIRED)
endif (OPENBABEL3_FOUND)

mark_as_advanced(OPENBABEL3_INCLUDE_DIR OPENBABEL3_LIBRARIES)
