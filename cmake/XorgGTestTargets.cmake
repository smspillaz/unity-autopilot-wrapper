# cmake/XorgGTestTargets.cmake
#
# Add a build rule to build xorg-gtest
# locally
#
# See LICENSE.md for Copyright information

include_directories (${XORG_SERVER_GTEST_INCLUDES}
                     ${XORG_SERVER_GTEST_SRC}
                     ${XORG_SERVER_INCLUDE_XORG_GTEST})

link_directories (${XORG_SERVER_LIBRARY_DIRS})

add_definitions (${XORG_SERVER_GTEST_CFLAGS})

set (_xorg_gtest_all_srcs
     ${XORG_SERVER_GTEST_SRC}/src/xorg-gtest-all.cpp)

set (XORG_GTEST_LIBRARY xorg_gtest_all)

add_library (${XORG_GTEST_LIBRARY} STATIC
	         ${_xorg_gtest_all_srcs})

target_link_libraries (${XORG_GTEST_LIBRARY}
                       ${XORG_SERVER_LIBRARIES})
