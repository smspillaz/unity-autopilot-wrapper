# /mocks/CMakeLists.txt
# Build unity-autopilot-wrapper mocks
#
# See LICENSE.md for Copyright Information

include_directories (${UAW_INTERNAL_INCLUDE_DIRECTORY}
                     ${UAW_INTERNAL_SOURCE_DIRECTORY}
                     ${UAW_MOCKS_DIRECTORY}
                     ${UAW_MATCHERS_DIRECTORY}
                     ${UAW_TESTS_UTIL_DIRECTORY}
                     ${UAW_EXTERNAL_INCLUDE_DIRS})

set (UAW_MOCKS_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/mock_x11_connection.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/mock_x11_connection.h)

add_library (${UAW_MOCKS_LIBRARY} STATIC
             ${UAW_MOCKS_SRCS})

verapp_profile_check_source_files_conformance (${UAW_VERAPP_OUTPUT_DIRECTORY}
                                               ${CMAKE_CURRENT_SOURCE_DIR}
                                               ${UAW_VERAPP_PROFILE}
                                               ${UAW_MOCKS_LIBRARY}
                                               ERROR)

target_link_libraries (${UAW_MOCKS_LIBRARY}
                       ${UAW_LIBRARY}
                       ${UAW_EXTERNAL_LIBRARIES})
