# /CMakeLists.txt
# Main CMake file for the unity-autopilot-wrapper project. Finds Google Test
# and determines if we can build unity-autopilot-wrapper
#
# See LICENCE.md for Copyright information

project (UnityAutopilotWrapper)

cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

function (check_python_module MODULE)
    message (STATUS "Checking for python module " ${MODULE})
    execute_process (COMMAND ${PYTHON_EXECUTABLE} -c "import ${MODULE}"
                     RESULT_VARIABLE _import_result
                     OUTPUT_QUIET
                     ERROR_QUIET)

    if (${_import_result} EQUAL 1)
        message (SEND_ERROR "${MODULE} is required to build "
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
     ${UAW_VERAPP_CMAKE_DIRECTORY} ${CMAKE_MODULE_PATH})

set (Boost_USE_STATIC_LIBS ON)

find_package (Boost 1.46 COMPONENTS program_options)
find_package (GTest QUIET)
find_package (VeraPP 1.2 REQUIRED)

# Check for autopilot
find_autopilot ()

if (NOT GTEST_FOUND)

    # Find the the Google Test include directory
    # by searching the system-wide include directory
    # paths
    find_path (GTEST_INCLUDE_DIR
               gtest/gtest.h)

    if (GTEST_INCLUDE_DIR)
        set (GTEST_INCLUDE_BASE "include/")
        string (LENGTH ${GTEST_INCLUDE_BASE} GTEST_INCLUDE_BASE_LENGTH)
        string (LENGTH ${GTEST_INCLUDE_DIR} GTEST_INCLUDE_DIR_LENGTH)

        math (EXPR
              GTEST_INCLUDE_PREFIX_LENGTH
              "${GTEST_INCLUDE_DIR_LENGTH} - ${GTEST_INCLUDE_BASE_LENGTH}")
        string (SUBSTRING
                ${GTEST_INCLUDE_DIR}
                0
                ${GTEST_INCLUDE_PREFIX_LENGTH}
                GTEST_INCLUDE_PREFIX)

        set (GTEST_SRC_DIR ${GTEST_INCLUDE_PREFIX}/src/gtest)

        add_subdirectory (${GTEST_SRC_DIR}
                          ${CMAKE_CURRENT_BINARY_DIR}/src/gtest)

        set (GTEST_LIBRARY gtest)
        set (GTEST_MAIN_LIBRARY gtest_main)
        set (GTEST_BOTH_LIBRARIES
             ${GTEST_LIBRARY}
             ${GTEST_MAIN_LIBRARY})

        set (GTEST_FOUND TRUE)
    endif (GTEST_INCLUDE_DIR)

endif (NOT GTEST_FOUND)

find_library (GMOCK_LIBRARY gmock)
find_library (GMOCK_MAIN_LIBRARY gmock_main)

if (NOT GTEST_FOUND OR NOT GMOCK_LIBRARY OR NOT GMOCK_MAIN_LIBRARY)
    message (SEND_ERROR "Google Test is required to build "
                        "unity-autopilot-wrapper")
endif (NOT GTEST_FOUND OR NOT GMOCK_LIBRARY OR NOT GMOCK_MAIN_LIBRARY)

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

# -fPIC, -Wall and -Werror are mandatory
set (COMPILER_FLAGS "-fPIC -Wall -Werror")
set (CXX_CXX11_FLAGS "-std=c++0x")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILER_FLAGS} ${CXX_CXX11_FLAGS}")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMPILER_FLAGS}")

set (UAW_EXTERNAL_INCLUDE_DIRS
     ${Boost_INCLUDE_DIRS})
set (UAW_EXTERNAL_LIBRARY_DIRS
     ${Boost_LIBRARY_DIRS})
set (UAW_EXTERNAL_LIBRARIES
     ${Boost_LIBRARIES}
     ${GTEST_MAIN_LIBRARY})
set (UAW_INTERNAL_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (UAW_INTERNAL_SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (UAW_TESTS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set (UAW_MOCKS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mocks)
set (UAW_MATCHERS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/matchers)
set (UAW_TESTS_UTIL_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testsutil)

set (UAW_MOCKS_LIBRARY uaw_mocks)
set (UAW_MATCHERS_LIBRARY uaw_matchers)
set (UAW_TESTS_UTIL_LIBRARY uaw_tests_util)

set (UAW_MAIN_LIBRARY unity_autopilot_wrapper_main)
set (UAW_BINARY unity_autopilot_wrapper)

add_subdirectory (${UAW_INTERNAL_SOURCE_DIRECTORY})
add_subdirectory (${UAW_TESTS_DIRECTORY})
add_subdirectory (${UAW_MOCKS_DIRECTORY})
add_subdirectory (${UAW_MATCHERS_DIRECTORY})
add_subdirectory (${UAW_TESTS_UTIL_DIRECTORY})
