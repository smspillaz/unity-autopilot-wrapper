# cmake/FindXorgGtest.cmake
#
# Find the xorg-gtest sources to see if they can be built
# locally
#
# See LICENSE.md for Copyright information.

# xorg-gtest
pkg_check_modules (XORG_SERVER
                   xorg-gtest>=0.7.0
                   xorg-server
                   x11
                   xi
                   xext)

if (XORG_SERVER_FOUND)

    execute_process (COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=prefix xorg-gtest OUTPUT_VARIABLE _xorg_gtest_prefix)
    execute_process (COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=includedir xorg-gtest OUTPUT_VARIABLE _xorg_gtest_include_dir)
    execute_process (COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=sourcedir xorg-gtest OUTPUT_VARIABLE _xorg_gtest_source_dir)
    execute_process (COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=CPPflags xorg-gtest OUTPUT_VARIABLE _xorg_gtest_cflags)

    string (STRIP ${_xorg_gtest_prefix} _xorg_gtest_prefix)
    string (STRIP ${_xorg_gtest_include_dir} _xorg_gtest_include_dir)
    string (STRIP ${_xorg_gtest_source_dir} _xorg_gtest_source_dir)
    string (STRIP ${_xorg_gtest_cflags} _xorg_gtest_cflags)

    set (XORG_SERVER_GTEST_INCLUDES ${XORG_SERVER_INCLUDE_DIRS})
    set (XORG_SERVER_GTEST_LIBRARY_DIRS ${XORG_SERVER_LIBRARIES})
    set (XORG_SERVER_GTEST_LIBRARIES} ${XORG_SERVER_LIBRARIES})
    set (XORG_SERVER_INCLUDE_XORG_GTEST ${_xorg_gtest_include_dir} CACHE PATH "Path to Xorg GTest Headers")
    set (XORG_SERVER_GTEST_SRC ${_xorg_gtest_source_dir} CACHE PATH "Path to Xorg GTest Sources")
    set (XORG_SERVER_GTEST_CFLAGS ${_xorg_gtest_cflags})
    set (XORG_SERVER_GTEST_ROOT ${CMAKE_SOURCE_DIR}/tests/xorg-gtest CACHE PATH "Path to Xorg GTest CMake sources")
    set (COMPIZ_XORG_SYSTEM_TEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/tests/xorg-gtest/include CACHE PATH "Path to Compiz Xorg GTest Headers")

    if (NOT XorgGTest_FIND_QUIETLY)
        message (STATUS "Found xorg-gtest sources at " ${XORG_SERVER_GTEST_SRC})
    endif (NOT XorgGTest_FIND_QUIETLY)

    set (XORG_GTEST_FOUND ON)

else (XORG_SERVER_FOUND)

    if (XorgGTest_FIND_REQUIRED)
        message (SEND_ERROR "Could not found xorg-gtest")
    endif (XorgGTest_FIND_REQUIRED)

    set (XORG_GTEST_FOUND OFF)

endif (XORG_SERVER_FOUND)
