# - Try to find OpenBabel2
# Once done this will define
#"
#  OPENBABEL2_FOUND - system has OpenBabel
#  OPENBABEL2_INCLUDE_DIR - the OpenBabel3 include directory
#  OPENBABEL2_LIBRARIES - Link these to use OpenBabel3

# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

#
# Search for Open Babel 2 libraries and includes
#
if (OPENBABEL2_INCLUDE_DIR AND OPENBABEL2_LIBRARIES)
  # in cache already
  set(OPENBABEL2_FOUND TRUE)
else (OPENBABEL2_INCLUDE_DIR AND OPENBABEL2_LIBRARIES)

    include(FindPkgConfig)

    # query pkg-config asking for a openbabel-2.0
    exec_program(${PKG_CONFIG_EXECUTABLE} ARGS openbabel-2.0 RETURN_VALUE _return_VALUE OUTPUT_VARIABLE _pkgconfigDevNull )
    if(_return_VALUE STREQUAL "0")
        set(OPENBABEL_MINI_FOUND TRUE)
    endif(_return_VALUE STREQUAL "0")
    message(STATUS "OPENBABEL_MINI_FOUND <${OPENBABEL_MINI_FOUND}>")

    exec_program(${PKG_CONFIG_EXECUTABLE} ARGS --variable=pkgincludedir openbabel-2.0 RETURN_VALUE _return_VALUE OUTPUT_VARIABLE _obPkgIncDir )
    if (_obPkgIncDir)
        set(_obIncDir "${_obPkgIncDir}")
    endif (_obPkgIncDir)

    find_path(OPENBABEL2_INCLUDE_DIR openbabel/obconversion.h
        PATHS
        $ENV{OPENBABEL2_INCLUDE_DIR}
        ${_obIncDir}
        /usr/local/include
        /usr/include
    )

    find_library(OPENBABEL2_LIBRARIES NAMES openbabel
        PATHS
        ${_obLinkDir}
        $ENV{OPENBABEL2_LIBRARIES}
        /usr/lib
        /usr/local/lib
    )

    if(OPENBABEL2_INCLUDE_DIR AND OPENBABEL2_LIBRARIES AND OPENBABEL_MINI_FOUND)
        set(OPENBABEL2_FOUND TRUE)
    endif(OPENBABEL2_INCLUDE_DIR AND OPENBABEL2_LIBRARIES AND OPENBABEL_MINI_FOUND)
endif()

if (OPENBABEL2_FOUND)
    message(STATUS "Found OpenBabel2: ${OPENBABEL2_LIBRARIES}")
else (OPENBABEL2_FOUND)
    if (OPENBABEL2_FIND_REQUIRED)
        message(FATAL_ERROR "Could NOT find OpenBabel3")
    endif (OPENBABEL2_FIND_REQUIRED)
endif (OPENBABEL2_FOUND)

mark_as_advanced(OPENBABEL2_INCLUDE_DIR OPENBABEL2_LIBRARIES)
