# /CMakeLists.txt
# Main CMake file for the unity-autopilot-wrapper project. Finds Google Test
# and determines if we can build unity-autopilot-wrapper
#
# See LICENCE.md for Copyright information

project (UnityAutopilotWrapper)

cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

include (FindPkgConfig)

function (check_python_module MODULE)
    message (STATUS "Checking for python module " ${MODULE})
    execute_process (COMMAND ${PYTHON_EXECUTABLE} -c "import ${MODULE}"
                     RESULT_VARIABLE _import_result
                     OUTPUT_QUIET
                     ERROR_QUIET)

    if (${_import_result} EQUAL 1)
        message (WARNING "${MODULE} is required to run "
                          "unity-autopilot-wrapper")
    endif (${_import_result} EQUAL 1)
endfunction ()

function (find_autopilot)
    find_program (PYTHON_EXECUTABLE python) 
    mark_as_advanced (PYTHON_EXECUTABLE)

    if (${PYTHON_EXECUTABLE} STREQUAL "PYTHON_EXECUTABLE-NOTFOUND")
        message (SEND_ERROR "Python is required to build "
                             "unity-autopilot-wrapper")
    else (${PYTHON_EXECUTABLE} STREQUAL "PYTHON_EXECUTABLE-NOTFOUND")
        check_python_module (autopilot)
        check_python_module (unity)
    endif (${PYTHON_EXECUTABLE} STREQUAL "PYTHON_EXECUTABLE-NOTFOUND")
endfunction (find_autopilot)

# Search the following directories as well as
# the global cmake directories for new modules
set (UAW_CMAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set (UAW_VERAPP_CMAKE_DIRECTORY ${UAW_CMAKE_DIRECTORY}/Vera++)
set (CMAKE_MODULE_PATH
     ${UAW_VERAPP_CMAKE_DIRECTORY} ${UAW_CMAKE_DIRECTORY} ${CMAKE_MODULE_PATH})

set (Boost_USE_STATIC_LIBS ON)

find_package (Boost 1.46 COMPONENTS program_options)
find_package (GoogleTest REQUIRED)
find_package (XorgGTest REQUIRED)
find_package (VeraPP 1.2 REQUIRED)

# Check for autopilot
find_autopilot ()

# Check compiz, unity
pkg_check_modules (COMPIZ compiz)
pkg_check_modules (UNITY unity)

# Check for xephyr
find_program (XEPHYR Xephyr)
mark_as_advanced (XEPHYR)

if (${XEPHYR} STREQUAL "XEPHYR-NOTFOUND")
    message (WARNING "Xephyr not found, you will not be able to run "
                     "unity-autopilot-wrapper in xephyr")
endif (${XEPHYR} STREQUAL "XEPHYR-NOTFOUND")

# Check for unity-autopilot-wrapper pkgconfig dependencies
pkg_check_modules (UAW_EXTERNAL_DEPS xorg-gtest x11 xrandr)

if (NOT COMPIZ_FOUND)
    message (WARNING "Compiz not found, you will not be able to run "
                     "unity-autopilot-wrapper")
endif (NOT COMPIZ_FOUND)

if (NOT UNITY_FOUND)
    message (WARNING "Unity not found, you will not be able to run "
                     "unity-autopilot-wrapper")
endif (NOT UNITY_FOUND)

# Set up Vera++
set (UAW_VERAPP_OUTPUT_DIRECTORY
     ${CMAKE_CURRENT_BINARY_DIR}/vera++)
set (UAW_VERAPP_SCRIPTS_OUTPUT_DIRECTORY
     ${UAW_VERAPP_OUTPUT_DIRECTORY}/scripts)
set (UAW_VERAPP_RULES_OUTPUT_DIRECTORY
     ${UAW_VERAPP_SCRIPTS_OUTPUT_DIRECTORY}/rules)
set (UAW_VERAPP_PROFILES_OUTPUT_DIRECTORY
     ${UAW_VERAPP_OUTPUT_DIRECTORY}/profiles)
set (UAW_VERAPP_SOURCE_DIRECTORY
     ${CMAKE_CURRENT_SOURCE_DIR}/tools/vera++)
set (UAW_VERAPP_SCRIPTS_SOURCE_DIRECTORY
    ${UAW_VERAPP_SOURCE_DIRECTORY}/scripts)
set (UAW_VERAPP_RULES_SOURCE_DIRECTORY
    ${UAW_VERAPP_SCRIPTS_SOURCE_DIRECTORY}/rules/)
set (UAW_VERAPP_PROFILES_SOURCE_DIRECTORY
    ${UAW_VERAPP_SOURCE_DIRECTORY}/profiles/)

set (UAW_VERAPP_PROFILE uaw)

set (UAW_VERAPP_IMPORT_RULES uaw_verapp_import_rules)

include (${UAW_CMAKE_DIRECTORY}/VeraPPTargets.cmake)

# Build xorg-gtest
include (${UAW_CMAKE_DIRECTORY}/XorgGTestTargets.cmake)

# -fPIC, -Wall and -Werror are mandatory
set (COMPILER_FLAGS "-fPIC -Wall -Werror")
set (CXX_CXX11_FLAGS "-std=c++0x")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILER_FLAGS} ${CXX_CXX11_FLAGS}")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMPILER_FLAGS}")

set (UAW_EXTERNAL_INCLUDE_DIRS
     ${UAW_EXTERNAL_DEPS_INCLUDE_DIRS}
     ${Boost_INCLUDE_DIRS})
set (UAW_EXTERNAL_LIBRARY_DIRS
     ${UAW_EXTERNAL_DEPS_LIBRARY_DIRS}
     ${Boost_LIBRARY_DIRS})
set (UAW_EXTERNAL_LIBRARIES
     ${UAW_EXTERNAL_DEPS_LIBRARIES}
     ${Boost_LIBRARIES}
     ${XORG_SERVER_GTEST_LIBRARIES}
     ${XORG_SERVER_LIBRARIES}
     xorg_gtest_all
     ${GTEST_MAIN_LIBRARY})
set (UAW_INTERNAL_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (UAW_INTERNAL_SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (UAW_TESTS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set (UAW_MOCKS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mocks)
set (UAW_MATCHERS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/matchers)
set (UAW_TESTS_UTIL_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testsutil)
set (UAW_TESTS_UTIL_BINARY_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testsutil)

set (UAW_MOCKS_LIBRARY uaw_mocks)
set (UAW_MATCHERS_LIBRARY uaw_matchers)
set (UAW_TESTS_UTIL_LIBRARY uaw_tests_util)

set (UAW_MAIN_LIBRARY unity_autopilot_wrapper_main)
set (UAW_LIBRARY uaw_static)
set (UAW_BINARY unity_autopilot_wrapper)
set (UAW_XEPHYR_WRAPPER_BINARY UnityXephyrWrapper)

# tests configuration
set (UAW_CONFIG_BINARY_DIR
     ${CMAKE_CURRENT_BINARY_DIR})

set (UAW_SIMPLE_EXECUTABLE_DIRECTORY
     ${UAW_TESTS_UTIL_BINARY_DIRECTORY})

set (UAW_SIMPLE_EXECUTABLE_BINARY
     simple_executable)

set (UAW_FAKE_AUTOPILOT_BINARY
     autopilot)

set (UAW_FAKE_COMPIZ_BINARY
     compiz)

set (UAW_FAKE_XORG_BINARY
     Xorg)

set (UAW_FAKE_XEPHYR_BINARY
     UnityXephyrWrapper)

set (UAW_FAKE_DBUS_LAUNCH_BINARY
     dbus-launch)

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/uaw_acceptance_tests_config.h.in
                ${UAW_CONFIG_BINARY_DIR}/uaw_acceptance_tests_config.h)

add_subdirectory (${UAW_INTERNAL_SOURCE_DIRECTORY})
add_subdirectory (${UAW_TESTS_DIRECTORY})
add_subdirectory (${UAW_MOCKS_DIRECTORY})
add_subdirectory (${UAW_MATCHERS_DIRECTORY})
add_subdirectory (${UAW_TESTS_UTIL_DIRECTORY})
