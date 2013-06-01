# /tests/unit/CMakeLists.txt
#
# Build unity-autopilot-wrapper unit tests
#
# See LICENSE.md for Copyright information.

include_directories (${UAW_INTERNAL_INCLUDE_DIRECTORY}
                     ${UAW_INTERNAL_SOURCE_DIRECTORY}
                     ${CMAKE_CURRENT_BINARY_DIR}
                     ${UAW_MOCKS_DIRECTORY}
                     ${UAW_MATCHERS_DIRECTORY}
                     ${UAW_TESTS_UTIL_DIRECTORY}
                     ${UAW_EXTERNAL_INCLUDE_DIRS})

set (UAW_SIMPLE_EXECUTABLE_DIRECTORY
     ${CMAKE_CURRENT_BINARY_DIR})

set (UAW_SIMPLE_EXECUTABLE_BINARY
     simple_executable)

set (UAW_SIMPLE_EXECUTABLE_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/simple_executable.cpp)

add_executable (${UAW_SIMPLE_EXECUTABLE_BINARY}
                ${UAW_SIMPLE_EXECUTABLE_SRCS})

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/uaw_acceptance_tests_config.h.in
                ${CMAKE_CURRENT_BINARY_DIR}/uaw_acceptance_tests_config.h)

set (UAW_ACCEPTANCE_TESTS_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/launch.cpp
     ${CMAKE_CURRENT_BINARY_DIR}/uaw_acceptance_tests_config.h)

set (UAW_ACCEPTANCE_TESTS_BINARY
     uaw_acceptance_tests)

add_executable (${UAW_ACCEPTANCE_TESTS_BINARY}
                ${UAW_ACCEPTANCE_TESTS_SRCS})

verapp_profile_check_source_files_conformance (${UAW_VERAPP_OUTPUT_DIRECTORY}
                                               ${CMAKE_CURRENT_SOURCE_DIR}
                                               ${UAW_VERAPP_PROFILE}
                                               ${UAW_ACCEPTANCE_TESTS_BINARY}
                                               ERROR)

target_link_libraries (${UAW_ACCEPTANCE_TESTS_BINARY}
                       ${UAW_LIBRARY}
                       ${GTEST_LIBRARY}
                       ${GMOCK_LIBRARY}
                       ${GMOCK_MAIN_LIBRARY})
