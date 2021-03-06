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

set (UAW_INTEGRATION_TESTS_BINARY
     uaw_integration_tests)

set (UAW_INTEGRATION_TESTS_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/concrete_x11.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/fdbackup.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/locatebinary.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/pipe.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/readfd.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/redirectedfd.cpp)

add_executable (${UAW_INTEGRATION_TESTS_BINARY}
                ${UAW_INTEGRATION_TESTS_SRCS})

verapp_profile_check_source_files_conformance (${UAW_VERAPP_OUTPUT_DIRECTORY}
                                               ${CMAKE_CURRENT_SOURCE_DIR}
                                               ${UAW_VERAPP_PROFILE}
                                               ${UAW_INTEGRATION_TESTS_BINARY}
                                               ERROR)

target_link_libraries (${UAW_INTEGRATION_TESTS_BINARY}
                       ${UAW_LIBRARY}
                       ${UAW_TESTS_UTIL_LIBRARY}
                       ${UAW_MOCKS_LIBRARY}
                       ${UAW_MATCHERS_LIBRARY}
                       ${GTEST_LIBRARY}
                       ${GMOCK_LIBRARY}
                       ${XORG_GTEST_MAIN_LIBRARY})
