# - Try to find OpenBabel
# Once done this will define
#"
#  OPENBABEL_FOUND - system has OpenBabel
#  OPENBABEL_INCLUDE_DIR - the OpenBabel include directory
#  OPENBABEL_LIBRARIES - Link these to use OpenBabel

# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

#
# Search for Open Babel libraries and includes
#
if (OPENBABEL_INCLUDE_DIR AND OPENBABEL_LIBRARIES)
  # in cache already
  set(OPENBABEL_FOUND TRUE)
else (OPENBABEL_INCLUDE_DIR AND OPENBABEL_LIBRARIES)

    include(FindPkgConfig)

    # query pkg-config asking for a openbabel-3
    exec_program(${PKG_CONFIG_EXECUTABLE} ARGS openbabel-3 RETURN_VALUE _return_VALUE OUTPUT_VARIABLE _pkgconfigDevNull )
    if(_return_VALUE STREQUAL "0")
        set(OPENBABEL_MINI_FOUND TRUE)
    endif(_return_VALUE STREQUAL "0")
    message(STATUS "OPENBABEL_MINI_FOUND <${OPENBABEL_MINI_FOUND}>")

    exec_program(${PKG_CONFIG_EXECUTABLE} ARGS --variable=pkgincludedir openbabel-3 RETURN_VALUE _return_VALUE OUTPUT_VARIABLE _obPkgIncDir )
    if (_obPkgIncDir)
        set(_obIncDir "${_obPkgIncDir}")
    endif (_obPkgIncDir)

    find_path(OPENBABEL_INCLUDE_DIR openbabel/obconversion.h
        PATHS
        $ENV{OPENBABEL_INCLUDE_DIR}
        ${_obIncDir}
        /usr/local/include/openbabel-3
        /usr/include/openbabel-3
    )

    find_library(OPENBABEL_LIBRARIES NAMES openbabel
        PATHS
        ${_obLinkDir}
        $ENV{OPENBABEL_LIBRARIES}
        /usr/lib
        /usr/local/lib
    )

    if(OPENBABEL_INCLUDE_DIR AND OPENBABEL_LIBRARIES AND OPENBABEL_MINI_FOUND)
        set(OPENBABEL_FOUND TRUE)
    endif(OPENBABEL_INCLUDE_DIR AND OPENBABEL_LIBRARIES AND OPENBABEL_MINI_FOUND)
endif()

if (OPENBABEL_FOUND)
    message(STATUS "Found OpenBabel: ${OPENBABEL_LIBRARIES}")
else (OPENBABEL_FOUND)
    if (OPENBABEL_FIND_REQUIRED)
        message(FATAL_ERROR "Could NOT find OpenBabel")
    endif (OPENBABEL_FIND_REQUIRED)
endif (OPENBABEL_FOUND)
mark_as_advanced(OPENBABEL_INCLUDE_DIR OPENBABEL_LIBRARIES)
