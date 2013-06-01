# src/CMakeLists.txt
# Builds unity-autopilot-wrapper
#
# See LICENSE.md for Copyright information

include_directories (${UAW_EXTERNAL_INCLUDE_DIRS}
                     ${UAW_INTERNAL_SOURCE_DIRECTORY}
                     ${UAW_INTERNAL_INCLUDE_DIRECTORY})

# compiz_autopilot_tests.h is not added to a vera++ target
# as the lines need to go over 100 chars

set (UAW_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/unity_autopilot_wrapper.cpp)

add_executable (${UAW_BINARY}
                ${UAW_SRCS})

target_link_libraries (${UAW_BINARY}
                       ${UAW_EXTERNAL_LIBRARIES})

verapp_profile_check_source_files_conformance (${UAW_VERAPP_OUTPUT_DIRECTORY}
                                               ${CMAKE_CURRENT_SOURCE_DIR}
                                               ${UAW_VERAPP_PROFILE}
                                               ${UAW_BINARY}
                                               ERROR)
