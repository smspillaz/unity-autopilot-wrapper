/*
 * concrete_x11.cpp
 *
 * Integration tests for the X11 connection functionality
 * using xorg-gtest
 *
 * See LICENSE.md for Copyright information
 */
#include <stdexcept>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <boost/bind.hpp>

#include <xorg/gtest/xorg-gtest.h>

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#include <concrete_x11_connection.h>

using ::testing::ExitedWithCode;
using ::testing::NotNull;

namespace uaw = unity::autopilot_wrapper;

class ConcreteXRandR :
    public xorg::testing::Test
{
    public:

        virtual void SetUp ();

    protected:

        uaw::ConcreteX11Connection conn;
        int                        eventBase;
        int                        errorBase;
        ::Display                  *display;

};

void
ConcreteXRandR::SetUp ()
{
    xorg::testing::Test::SetUp ();
    display = Display ();

    if (!XRRQueryExtension (display,
                            &eventBase,
                            &errorBase))
        throw std::runtime_error ("XRRQueryExtension failed");

    int           n;
    XRRScreenSize *sizes = XRRSizes (display,
                                     DefaultScreen (display),
                                     &n);

    ASSERT_GE (n, 1);
    ASSERT_THAT (sizes, NotNull ());
}

TEST_F (ConcreteXRandR, Setup)
{
}

TEST_F (ConcreteXRandR, ConfigNonNull)
{
    auto deleter = uaw::ConcreteX11Connection::ConfigDeleter ();
    uaw::ScreenConfig config (conn.GetConfig (display),
                              deleter);
    EXPECT_THAT (config.get (), NotNull ());
}

TEST_F (ConcreteXRandR, ManageConfig)
{
    EXPECT_EXIT ({
        auto deleter = uaw::ConcreteX11Connection::ConfigDeleter ();
        uaw::ScreenConfig config (conn.GetConfig (display),
                                  deleter);
        /* Since the connection gets closed automatically on _exit ()
         * as all fd's are closed, we need to to properly tear down here */
        xorg::testing::Test::TearDown ();
        _exit (0);
    }, ExitedWithCode (0), "");

    /* As the connection will be closed, we need to re-setup the test */
    xorg::testing::Test::SetUp ();
}

TEST_F (ConcreteXRandR, GetScreenSizes)
{
    auto deleter = uaw::ConcreteX11Connection::ConfigDeleter ();
    uaw::ScreenConfig config (conn.GetConfig (display),
                              deleter);

    uaw::ScreenSizeArray array = conn.GetScreenSizes (config);
    EXPECT_GE (array.num, 1);
}

TEST_F (ConcreteXRandR, ChangeToNonCurrentResolutionChangesRootSize)
{
    auto deleter = uaw::ConcreteX11Connection::ConfigDeleter ();
    uaw::ScreenConfig config (conn.GetConfig (display),
                              deleter);

    XWindowAttributes rootAttributes;
    XGetWindowAttributes (display,
                          DefaultRootWindow (display),
                          &rootAttributes);
    XSelectInput (display,
                  DefaultRootWindow (display),
                  StructureNotifyMask);

    uaw::ScreenSizeArray array = conn.GetScreenSizes (config);

    /* Find the first nonmatching resolution and change to it */
    for (int i = 0; i < array.num; ++i)
    {
        if (array.array[i].width != rootAttributes.width ||
            array.array[i].height != rootAttributes.height)
        {
            conn.ChangeSizeIndex (display, config, i);
        }
    }

    /* Expect a ConfigureNotify */
    EXPECT_TRUE (xorg::testing::XServer::WaitForEventOfType (display,
                                                             ConfigureNotify,
                                                             -1,
                                                             -1,
                                                             0));
}
