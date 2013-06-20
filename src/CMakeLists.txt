# src/CMakeLists.txt
# Builds unity-autopilot-wrapper
#
# See LICENSE.md for Copyright information

include_directories (${UAW_EXTERNAL_INCLUDE_DIRS}
                     ${UAW_INTERNAL_SOURCE_DIRECTORY}
                     ${UAW_INTERNAL_INCLUDE_DIRECTORY})

# compiz_autopilot_tests.h is not added to a vera++ target
# as the lines need to go over 100 chars

set (UAW_LIBRARY_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/concrete_x11_connection.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/concrete_x11_connection.h
     ${CMAKE_CURRENT_SOURCE_DIR}/displaydiscovery.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/displaydiscovery.h
     ${CMAKE_CURRENT_SOURCE_DIR}/fdbackup.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/fdbackup.h
     ${CMAKE_CURRENT_SOURCE_DIR}/environment.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/environment.h
     ${CMAKE_CURRENT_SOURCE_DIR}/exports.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/exports.h
     ${CMAKE_CURRENT_SOURCE_DIR}/launch.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/launch.h
     ${CMAKE_CURRENT_SOURCE_DIR}/listtests.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/listtests.h
     ${CMAKE_CURRENT_SOURCE_DIR}/locatebinary.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/locatebinary.h
     ${CMAKE_CURRENT_SOURCE_DIR}/pipe.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/pipe.h
     ${CMAKE_CURRENT_SOURCE_DIR}/servertype.h
     ${CMAKE_CURRENT_SOURCE_DIR}/serversetup.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/serversetup.h
     ${CMAKE_CURRENT_SOURCE_DIR}/readfd.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/readfd.h
     ${CMAKE_CURRENT_SOURCE_DIR}/redirectedfd.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/redirectedfd.h
     ${CMAKE_CURRENT_SOURCE_DIR}/resizescreen.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/resizescreen.h
     ${CMAKE_CURRENT_SOURCE_DIR}/x11_connection.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/x11_connection.h)

add_library (${UAW_LIBRARY} STATIC
             ${UAW_LIBRARY_SRCS})

target_link_libraries (${UAW_LIBRARY}
                       ${UAW_EXTERNAL_LIBRARIES})

verapp_profile_check_source_files_conformance (${UAW_VERAPP_OUTPUT_DIRECTORY}
                                               ${CMAKE_CURRENT_SOURCE_DIR}
                                               ${UAW_VERAPP_PROFILE}
                                               ${UAW_LIBRARY}
                                               ERROR)

set (UAW_MAIN_LIBRARY_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/unity_autopilot_main.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/unity_autopilot_test.h)

add_library (${UAW_MAIN_LIBRARY} STATIC
             ${UAW_MAIN_LIBRARY_SRCS})

target_link_libraries (${UAW_MAIN_LIBRARY}
                       ${UAW_LIBRARY}
                       ${UAW_EXTERNAL_LIBRARIES})

verapp_profile_check_source_files_conformance (${UAW_VERAPP_OUTPUT_DIRECTORY}
                                               ${CMAKE_CURRENT_SOURCE_DIR}
                                               ${UAW_VERAPP_PROFILE}
                                               ${UAW_MAIN_LIBRARY}
                                               ERROR)

# Not added to vera++ checks
set (UAW_BINARY_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/unity_all_autopilot.cpp)

add_executable (${UAW_BINARY}
                ${UAW_BINARY_SRCS})

target_link_libraries (${UAW_BINARY}
                       ${UAW_LIBRARY}
                       ${UAW_MAIN_LIBRARY})

add_executable (${UAW_XEPHYR_WRAPPER_BINARY}
                ${CMAKE_CURRENT_SOURCE_DIR}/xephyr_wrapper.cpp)

target_link_libraries (${UAW_XEPHYR_WRAPPER_BINARY}
                       ${UAW_LIBRARY})


verapp_profile_check_source_files_conformance (${UAW_VERAPP_OUTPUT_DIRECTORY}
                                               ${CMAKE_CURRENT_SOURCE_DIR}
                                               ${UAW_VERAPP_PROFILE}
                                               ${UAW_XEPHYR_WRAPPER_BINARY}
                                               ERROR)


install (TARGETS
         ${UAW_XEPHYR_WRAPPER_BINARY}
         ${UAW_BINARY}
         RUNTIME DESTINATION bin)

