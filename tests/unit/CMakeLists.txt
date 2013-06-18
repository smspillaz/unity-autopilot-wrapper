# /tests/unit/CMakeLists.txt
#
# Build unity-autopilot-wrapper unit tests
#
# See LICENSE.md for Copyright information.

include_directories (${UAW_INTERNAL_INCLUDE_DIRECTORY}
                     ${UAW_INTERNAL_SOURCE_DIRECTORY}
                     ${UAW_CONFIG_BINARY_DIR}
                     ${UAW_MOCKS_DIRECTORY}
                     ${UAW_MATCHERS_DIRECTORY}
                     ${UAW_TESTS_UTIL_DIRECTORY}
                     ${UAW_EXTERNAL_INCLUDE_DIRS})

set (UAW_UNIT_TESTS_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/displaydiscovery.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/resizescreen.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/serversetup.cpp
     ${UAW_CONFIG_BINARY_DIR}/uaw_acceptance_tests_config.h)

set (UAW_UNIT_TESTS_BINARY
     uaw_unit_tests)

add_executable (${UAW_UNIT_TESTS_BINARY}
                ${UAW_UNIT_TESTS_SRCS})

verapp_profile_check_source_files_conformance (${UAW_VERAPP_OUTPUT_DIRECTORY}
                                               ${CMAKE_CURRENT_SOURCE_DIR}
                                               ${UAW_VERAPP_PROFILE}
                                               ${UAW_UNIT_TESTS_BINARY}
                                               ERROR)

target_link_libraries (${UAW_UNIT_TESTS_BINARY}
                       ${UAW_LIBRARY}
                       ${UAW_TESTS_UTIL_LIBRARY}
                       ${UAW_MOCKS_LIBRARY}
                       ${UAW_MATCHERS_LIBRARY}
                       ${GTEST_LIBRARY}
                       ${GMOCK_LIBRARY}
                       ${GMOCK_MAIN_LIBRARY})
