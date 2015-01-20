set( MYCHEM_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data/" )

#
# Helper Module CMakeLists.txt File
#
include_directories(
    ${MySQL_INCLUDE_DIR} 
    ${OPENBABEL2_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}/include 
    ${CMAKE_SOURCE_DIR}/include 
)

add_definitions( -DHAVE_DLOPEN )

#
# Conversion Test
#
set( conversion_test_SRCS
    conversion_test.cpp
    mysql_handler.cpp
    test_functions.cpp
)
add_executable( conversion_test ${conversion_test_SRCS} )
target_link_libraries( conversion_test
    ${MySQL_LIBRARIES}
)
add_test( ConversionTest ${CMAKE_CURRENT_BINARY_DIR}/conversion_test
          ${MY_ARGS} -d ${MYCHEM_DATA_DIR}
)

#
# Helper Test
#
set( helper_test_SRCS
    helper_test.cpp
    mysql_handler.cpp
    test_functions.cpp
)
add_executable( helper_test ${helper_test_SRCS} )
target_link_libraries( helper_test
    ${MySQL_LIBRARIES}
)
add_test( HelperTest ${CMAKE_CURRENT_BINARY_DIR}/helper_test
          ${MY_ARGS} -d ${MYCHEM_DATA_DIR}
)

#
# Modification Test
#
set( modification_test_SRCS
     modification_test.cpp
     mysql_handler.cpp
     test_functions.cpp
)
add_executable( modification_test ${modification_test_SRCS} )
target_link_libraries( modification_test
    ${MySQL_LIBRARIES}
)
add_test( ModificationTest ${CMAKE_CURRENT_BINARY_DIR}/modification_test
          ${MY_ARGS} -d ${MYCHEM_DATA_DIR}
)

#
# Molmatch Test
#
set( molmatch_test_SRCS
     molmatch_test.cpp
     mysql_handler.cpp
     test_functions.cpp
)
add_executable( molmatch_test ${molmatch_test_SRCS} )
target_link_libraries( molmatch_test
    ${MySQL_LIBRARIES}
)
add_test( MolmatchTest ${CMAKE_CURRENT_BINARY_DIR}/molmatch_test
          ${MY_ARGS} -d ${MYCHEM_DATA_DIR}
)

#
# Property Test
#
set( property_test_SRCS
     property_test.cpp
     mysql_handler.cpp
     test_functions.cpp
)
add_executable( property_test ${property_test_SRCS} )
target_link_libraries( property_test
    ${MySQL_LIBRARIES}
)
add_test( PropertyTest ${CMAKE_CURRENT_BINARY_DIR}/property_test
          ${MY_ARGS} -d ${MYCHEM_DATA_DIR}
)

