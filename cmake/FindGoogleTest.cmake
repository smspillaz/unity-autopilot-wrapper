# cmake/FindGoogleTest.cmake
#
# Try and find the systemwide google-test first
# otherwise, build it locally
#
# See LICENSE.md for Copyright information

find_package (GTest QUIET)

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
    if (GoogleTest_FIND_REQUIRED)
        message (SEND_ERROR "Google Test is required to build "
                            "unity-autopilot-wrapper")
    endif (GoogleTest_FIND_REQUIRED)
endif (NOT GTEST_FOUND OR NOT GMOCK_LIBRARY OR NOT GMOCK_MAIN_LIBRARY)
