# /testsutil/CMakeLists.txt
# Build unity-autopilot-wrapper test util functions
#
# See LICENSE.md for copyright information

set (UAW_TESTS_UTIL_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/tmpenv.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/tmpenv.h)

add_library (${UAW_TESTS_UTIL_LIBRARY} STATIC
             ${UAW_TESTS_UTIL_SRCS})

set (UAW_SIMPLE_EXECUTABLE_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/simple_executable.cpp)

add_executable (${UAW_SIMPLE_EXECUTABLE_BINARY}
                ${UAW_SIMPLE_EXECUTABLE_SRCS})

set (UAW_FAKE_AUTOPILOT_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/fake_autopilot.cpp)

add_executable (${UAW_FAKE_AUTOPILOT_BINARY}
                ${UAW_FAKE_AUTOPILOT_SRCS})

set (UAW_FAKE_COMPIZ_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/fake_compiz.cpp)

add_executable (${UAW_FAKE_COMPIZ_BINARY}
                ${UAW_FAKE_COMPIZ_SRCS})

set (UAW_FAKE_SERVER_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/fake_server.cpp)

add_executable (${UAW_FAKE_XORG_BINARY}
                ${UAW_FAKE_SERVER_SRCS})

# We already have a target called UnityXephyrWrapper, we need
# to change the name of this binary with a different target name
add_executable (${UAW_FAKE_XEPHYR_BINARY}Fake
                ${UAW_FAKE_SERVER_SRCS})

set_target_properties (${UAW_FAKE_XEPHYR_BINARY}Fake
                       PROPERTIES
                       OUTPUT_NAME
                       ${UAW_FAKE_XEPHYR_BINARY})

set (UAW_FAKE_DBUS_LAUNCH_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/fake_dbus_launch.cpp)

add_executable (${UAW_FAKE_DBUS_LAUNCH_BINARY}
                ${UAW_FAKE_DBUS_LAUNCH_SRCS})
