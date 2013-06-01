#/tests/CMakeLists.txt
# Build unity-autopilot-wrapper tests
#
# See LICENSE.md for Copyright information

set (UAW_UNIT_TESTS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/unit)
set (UAW_INTEGRATION_TESTS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/integration)
set (UAW_ACCEPTANCE_TESTS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/acceptance)

add_subdirectory (${UAW_UNIT_TESTS_DIRECTORY})
add_subdirectory (${UAW_INTEGRATION_TESTS_DIRECTORY})
add_subdirectory (${UAW_ACCEPTANCE_TESTS_DIRECTORY})
