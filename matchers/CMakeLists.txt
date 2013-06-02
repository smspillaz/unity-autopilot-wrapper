# /matchers/CMakeLists.txt
# Build unity-autopilot-wrapper matchers
#
# See LICENSE.md for Copyright Information

include_directories (${UAW_INTERNAL_INCLUDE_DIRECTORY}
                     ${UAW_INTERNAL_SOURCE_DIRECTORY}
                     ${UAW_MOCKS_DIRECTORY}
                     ${UAW_MATCHERS_DIRECTORY}
                     ${UAW_TESTS_UTIL_DIRECTORY}
                     ${UAW_EXTERNAL_INCLUDE_DIRS})

set (UAW_MATCHERS_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/is_display_number_matcher.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/is_display_number_matcher.h)

add_library (${UAW_MATCHERS_LIBRARY} STATIC
             ${UAW_MATCHERS_SRCS})

verapp_profile_check_source_files_conformance (${UAW_VERAPP_OUTPUT_DIRECTORY}
                                               ${CMAKE_CURRENT_SOURCE_DIR}
                                               ${UAW_VERAPP_PROFILE}
                                               ${UAW_MATCHERS_LIBRARY}
                                               ERROR)

target_link_libraries (${UAW_MATCHERS_LIBRARY}
                       ${UAW_LIBRARY}
                       ${UAW_EXTERNAL_LIBRARIES})
