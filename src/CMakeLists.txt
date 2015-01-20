include_directories(
    ${MySQL_INCLUDE_DIR} 
    ${OPENBABEL2_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}/include
    ${CMAKE_SOURCE_DIR}/include
)

if (BUILD_SHARED)
    message(STATUS "Defining dlhandler source files")
    if (WIN32)
        set(dlhandler_SRCS
            ${CMAKE_SOURCE_DIR}/src/dlhandler_win32.cpp
        )
    else (WIN32)
        set(dlhandler_SRCS
            ${CMAKE_SOURCE_DIR}/src/dlhandler_unix.cpp
        )
    endif (WIN32)
endif (BUILD_SHARED)

set(serialization_SRCS
	${CMAKE_SOURCE_DIR}/src/serialization.cpp
)

if (NOT WIN32)
    set(MYCHEM_LIBRARIES
        dl
    )
endif (NOT WIN32)

add_definitions( -DHAVE_DLOPEN )

set( libmychem_SRCS
     conversion.c
     conversion_wrapper.cpp
     helper.c
     helper_wrapper.cpp
     modification.c
     modification_wrapper.cpp
     molmatch.c
     molmatch_wrapper.cpp
     property.c
     property_wrapper.cpp
     serialization.cpp
     mychem.def
     ${dlhandler_SRCS}
)

add_library( mychem-lib SHARED ${libmychem_SRCS} )
set_target_properties( mychem-lib PROPERTIES OUTPUT_NAME mychem )
set_target_properties( mychem-lib PROPERTIES VERSION ${MYCHEM_VERSION} SOVERSION ${MYCHEM_VERSION_MAJOR} )

target_link_libraries( mychem-lib
    ${OPENBABEL2_LIBRARIES}
    ${MySQL_LIBRARIES}
    ${MYCHEM_LIBRARIES}
)

#### install files ####
install(TARGETS mychem-lib DESTINATION ${LIB_INSTALL_DIR})
