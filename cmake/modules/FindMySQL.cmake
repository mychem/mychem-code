# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#.rst:
# FindMySQL
# ---------
#
# This module can be used to find ...detects if MySQL or MariaDB libraries are installed and
# where the include files are. It defines also the path to the
# plugin directory. The most important issue is that is requires mysql_config or mariadb_config.
#
# This module defines:
# 
# ::
#
#   MYSQL_LIBRARIES, full path to the MySQL or MariaDB
#   PLUGIN_DIR    full path to plugin directory
#   MYSQL_INCLUDE_DIR   include dir to be used when using the MySQL or MariaDB
#                     library
#   MYSQL_FOUND         set to true if MySQL or MariaDB was found
#                      successfully
#   MYSQL_FLAVOR        Set to 'mysql' or 'mariadb'
#
#
# Usage of this module as follows:
# Typical usage culd be something like this:
#
# .. code-block:: cmake
#   set(MYSQL_FLAVOR mariadb)
#   find_package(MYSQL)
#   if(MYSQL_FOUND)
#     include_directories(${MYSQL_INCLUDE_DIR})
#     add_executable(foo foo.cc)
#   endif()
#
# Variables used by this module, they can change the default behaviour and
# need to set before calling find_package:
# MYSQL_CONFIG_PATH
# MYSQL_FLAVOR
#

find_program(MARIADB_CONFIG
    NAMES
    mariadb_config
    PATHS
    ${MYSQL_CONFIG_PATH}
    /bin
    /usr/bin
    /usr/local/bin
)

find_program(MYSQL_CONFIG
    NAMES
    mysql_config
    PATHS
    ${MYSQL_CONFIG_PATH}
    /bin
    /usr/bin
    /usr/local/bin
)

# Use mariadb flavor by default
if(NOT MYSQL_FLAVOR)
    if(MARIADB_CONFIG)
        set(MYSQL_FLAVOR "mariadb")
    elseif(MYSQL_CONFIG)
        set(MYSQL_FLAVOR "mysql")
    else()
	message(FATAL_ERROR "MYSQL_FLAVOR is not defined")
    endif()
endif()

if(NOT MYSQL_CONFIG)
    if(MARIADB_CONFIG)
        set(DB_CONFIG ${MARIADB_CONFIG})
    endif()
else()
    set(DB_CONFIG ${MYSQL_CONFIG})
endif()

if(DB_CONFIG)
    message(STATUS "Using db-config: ${DB_CONFIG}")

    # set INCLUDE_DIR
    exec_program(
        ${DB_CONFIG}
        ARGS --include
        OUTPUT_VARIABLE MY_TMP
    )
    string(REGEX REPLACE "-I([^ ]+)( .*)?" "\\1" MY_TMP "${MY_TMP}")
    set(MYSQL_ADD_INCLUDE_DIR ${MY_TMP} CACHE FILEPATH INTERNAL)

    find_path(MYSQL_INCLUDE_DIR mysql.h
        ${MYSQL_ADD_INCLUDE_DIR}
        /usr/include
        /usr/include/${MYSQL_FLAVOR}
        /usr/local/include
        /usr/local/include/${MYSQL_FLAVOR}
    )

    # set LIBRARY_DIR
    exec_program(
        ${DB_CONFIG}
        ARGS --libs
        OUTPUT_VARIABLE MY_TMP
    )
    set(MYSQL_ADD_LIBRARIES "")
    string(REGEX MATCHALL "(^| )-l[^ ]+" MYSQL_LIB_LIST "${MY_TMP}")
    foreach(LIB ${MYSQL_LIB_LIST})
        string(REGEX REPLACE "[ ]*-l([^ ]*)" "\\1" LIB "${LIB}")
        list(APPEND MYSQL_ADD_LIBRARIES "${LIB}")
    endforeach(LIB ${MYSQL_LIBS})

    # Add mysqlclient or mariadbclient library
    set(MYSQL_ADD_LIBRARY_PATH "")
    string(REGEX MATCHALL "-L[^ ]+" MYSQL_LIBDIR_LIST "${MY_TMP}")
    foreach(LIB ${MYSQL_LIBDIR_LIST})
        string(REGEX REPLACE "[ ]*-L([^ ]*)" "\\1" LIB "${LIB}")
        list(APPEND MYSQL_ADD_LIBRARY_PATH "${LIB}")
    endforeach(LIB ${MYSQL_LIBS})


    if(UNIX)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES} ".so.1")
    endif()
    set(TMP_MYSQL_LIBRARIES "")
    foreach(LIB ${MYSQL_ADD_LIBRARIES})
        find_library(
            "MYSQL_LIBRARIES_${LIB}" NAMES ${LIB}
            PATHS
	    ${MYSQL_ADD_LIBRARY_PATH}
            /usr/local/lib64
	    /usr/local/lib64/${MYSQL_FLAVOR}
            /usr/local/lib
            /usr/local/lib/${MYSQL_FLAVOR}
        )
        list(APPEND TMP_MYSQL_LIBRARIES "${MYSQL_LIBRARIES_${LIB}}")
    endforeach(LIB ${MYSQL_ADD_LIBRARIES})
    set(MYSQL_LIBRARIES ${TMP_MYSQL_LIBRARIES} CACHE FILEPATH INTERNAL)

    # Set MYSQL_VERSION
    exec_program(
       ${DB_CONFIG}
        ARGS --version
        OUTPUT_VARIABLE MY_TMP
    )
    set(MYSQL_VERSION ${MY_TMP})

    # Set MySQL plugin dir
    exec_program(
        ${DB_CONFIG}
        ARGS --plugindir
	OUTPUT_VARIABLE TMP_PLUGIN_DIR
    )
    if(NOT PLUGIN_DIR)
        set(PLUGIN_DIR ${TMP_PLUGIN_DIR} CACHE FILEPATH INTERNAL)
    endif()
endif()


if(MYSQL_INCLUDE_DIR AND MYSQL_LIBRARIES)
    set(MYSQL_FOUND TRUE CACHE INTERNAL "MySQL found")
    if(${MYSQL_FLAVOR} MATCHES "mariadb")
        message(STATUS "Found MariaDB ${MYSQL_VERSION}: ${MYSQL_INCLUDE_DIR}, ${MYSQL_LIBRARIES}")
        message(STATUS "Mariadb plugin_dir: ${PLUGIN_DIR}")
    else()
        message(STATUS "Found MySQL ${MYSQL_VERSION}: ${MYSQL_INCLUDE_DIR}, ${MYSQL_LIBRARIES}")
	message(STATUS "MySQL plugin_dir: ${PLUGIN_DIR}")
    endif()
else(MYSQL_INCLUDE_DIR AND MYSQL_LIBRARIES)
    set(MYSQL_FOUND FALSE CACHE INTERNAL "MySQL found")
    message(STATUS "MySQL or MariaDB not found.")
    if(MYSQL_FIND_REQUIRED)
	    message(FATAL_ERROR "Could NOT find MySQL or MariaDB")
    endif(MYSQL_FIND_REQUIRED)
endif(MYSQL_INCLUDE_DIR AND MYSQL_LIBRARIES)

mark_as_advanced(MYSQL_INCLUDE_DIR MYSQL_LIBRARIES)
