set( MYCHEM_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data/" )

#
# Helper Module CMakeLists.txt File
#
include_directories(
  ${MYSQL_INCLUDE_DIR}
  ${OPENBABEL_INCLUDE_DIR}
  ${CMAKE_BINARY_DIR}/include
  ${CMAKE_SOURCE_DIR}/include
)

add_definitions( -DHAVE_DLOPEN )

#
# Conversion Test
#
set(
  CONVERSION_TEST_SRCS
  conversion_test.cpp
  mysql_handler.cpp
  test_functions.cpp
)
add_executable(conversion_test ${CONVERSION_TEST_SRCS})
target_link_libraries(
  conversion_test
  ${MYSQL_LIBRARIES}
)
add_test(
  ConversionTest
  ${CMAKE_CURRENT_BINARY_DIR}/conversion_test ${MY_ARGS} -d ${MYCHEM_DATA_DIR}
)

#
# Helper Test
#
set(
  HELPER_TEST_SRCS
  helper_test.cpp
  mysql_handler.cpp
  test_functions.cpp
)
add_executable( helper_test ${HELPER_TEST_SRCS} )
target_link_libraries(
  helper_test
  ${MYSQL_LIBRARIES}
)
add_test(
  HelperTest
  ${CMAKE_CURRENT_BINARY_DIR}/helper_test ${MY_ARGS} -d ${MYCHEM_DATA_DIR}
)

#
# Modification Test
#
set(
  MODIFICATION_TEST_SRCS
  modification_test.cpp
  mysql_handler.cpp
  test_functions.cpp
)
add_executable(modification_test ${MODIFICATION_TEST_SRCS})
target_link_libraries(
  modification_test
  ${MYSQL_LIBRARIES}
)
add_test(
  ModificationTest
  ${CMAKE_CURRENT_BINARY_DIR}/modification_test ${MY_ARGS} -d ${MYCHEM_DATA_DIR}
)

#
# Molmatch Test
#
set(
  MOLMATCH_TEST_SRCS
  molmatch_test.cpp
  mysql_handler.cpp
  test_functions.cpp
)
add_executable(molmatch_test ${MOLMATCH_TEST_SRCS})
target_link_libraries(
  molmatch_test
  ${MYSQL_LIBRARIES}
)
add_test(
  MolmatchTest
  ${CMAKE_CURRENT_BINARY_DIR}/molmatch_test ${MY_ARGS} -d ${MYCHEM_DATA_DIR}
)

#
# Property Test
#
set(
  PROPERTY_TEST_SRCS
  property_test.cpp
  mysql_handler.cpp
  test_functions.cpp
)
add_executable( property_test ${PROPERTY_TEST_SRCS} )
target_link_libraries(
  property_test
  ${MYSQL_LIBRARIES}
)
add_test(
  PropertyTest
  ${CMAKE_CURRENT_BINARY_DIR}/property_test ${MY_ARGS} -d ${MYCHEM_DATA_DIR}
)

