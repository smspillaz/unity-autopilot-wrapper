/*
 * resizescreen.cpp
 *
 * Unit tests for changing the screen size
 *
 * See LICENSE.md for Copyright information
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <mock_x11_connection.h>
#include <resizescreen.h>
#include <x11_connection.h>

using ::testing::_;
using ::testing::AtLeast;
using ::testing::IsNull;
using ::testing::Return;
using ::testing::ReturnNull;
using ::testing::Test;

namespace uaw = unity::autopilot_wrapper;
namespace uawm = unity::autopilot_wrapper::mocks;

struct _XDisplay
{
};

class ResizeScreen :
    public Test
{
    public:

        void IgnoreGetScreenSizes ();
        void IgnoreChangeSizeIndex ();

        Display                 display;
        uawm::MockX11Connection connection;
};

void
ResizeScreen::IgnoreChangeSizeIndex ()
{
    EXPECT_CALL (connection, ChangeSizeIndex (_, _, _)).Times (AtLeast (0));
}

void
ResizeScreen::IgnoreGetScreenSizes ()
{
    EXPECT_CALL (connection, GetConfig (_)).Times (AtLeast (0));
    EXPECT_CALL (connection, GetScreenSizes (_)).Times (AtLeast (0));
}

TEST_F (ResizeScreen, AlwaysCheckAvailableScreenSizes)
{
    IgnoreChangeSizeIndex ();

    EXPECT_CALL (connection, GetConfig (&display))
        .WillOnce (ReturnNull ());
    EXPECT_CALL (connection, GetScreenSizes (IsNull ()))
        .WillOnce (Return (uaw::ScreenSizeArray ()));

    uaw::ScaleToPreferredMinimum (&display, connection);
}

TEST_F (ResizeScreen, NoScreenSizesNoCallToScale)
{
    IgnoreGetScreenSizes ();

    ON_CALL (connection, GetScreenSizes (_))
        .WillByDefault (Return (uaw::ScreenSizeArray ()));

    EXPECT_CALL (connection, ChangeSizeIndex (_, _, _))
        .Times (0);

    uaw::ScaleToPreferredMinimum (&display, connection);
}

TEST_F (ResizeScreen, OneScreenSizeNoCallToScale)
{
    IgnoreGetScreenSizes ();

    XRRScreenSize sizes[1] =
    {
        {
            0,
            0,
            0,
            0
        }
    };

    uaw::ScreenSizeArray array;

    array.array = sizes;
    array.num = 1;

    ON_CALL (connection, GetScreenSizes (_))
        .WillByDefault (Return (array));

    EXPECT_CALL (connection, ChangeSizeIndex (_, _, _))
        .Times (0);

    uaw::ScaleToPreferredMinimum (&display, connection);
}

TEST_F (ResizeScreen, PickExact)
{
    IgnoreGetScreenSizes ();

    XRRScreenSize sizes[2] =
    {
        {
            static_cast <int> (uaw::PreferredMinimumWidth / 2),
            static_cast <int> (uaw::PreferredMinimumHeight / 2),
            0,
            0
        },
        {
            static_cast <int> (uaw::PreferredMinimumWidth),
            static_cast <int> (uaw::PreferredMinimumHeight),
            0,
            0
        }
    };

    uaw::ScreenSizeArray array;

    array.array = sizes;
    array.num = 2;

    ON_CALL (connection, GetScreenSizes (_))
        .WillByDefault (Return (array));

    EXPECT_CALL (connection, ChangeSizeIndex (&display, _, 1));

    uaw::ScaleToPreferredMinimum (&display, connection);
}

TEST_F (ResizeScreen, PickBestLower)
{
    IgnoreGetScreenSizes ();

    XRRScreenSize sizes[3] =
    {
        {
            static_cast <int> (uaw::PreferredMinimumWidth / 2),
            static_cast <int> (uaw::PreferredMinimumHeight / 2),
            0,
            0
        },
        {
            static_cast <int> (uaw::PreferredMinimumWidth / 1.5),
            static_cast <int> (uaw::PreferredMinimumHeight / 1.5),
            0,
            0
        },
        {
            static_cast <int> (uaw::PreferredMinimumWidth / 1.2),
            static_cast <int> (uaw::PreferredMinimumHeight / 1.2),
            0,
            0
        }
    };

    uaw::ScreenSizeArray array;

    array.array = sizes;
    array.num = 3;

    ON_CALL (connection, GetScreenSizes (_))
        .WillByDefault (Return (array));

    EXPECT_CALL (connection, ChangeSizeIndex (&display, _, 2));

    uaw::ScaleToPreferredMinimum (&display, connection);
}


TEST_F (ResizeScreen, PickBestUpper)
{
    IgnoreGetScreenSizes ();

    XRRScreenSize sizes[3] =
    {
        {
            static_cast <int> (uaw::PreferredMinimumWidth / 2),
            static_cast <int> (uaw::PreferredMinimumHeight / 2),
            0,
            0
        },
        {
            static_cast <int> (uaw::PreferredMinimumWidth / 1.5),
            static_cast <int> (uaw::PreferredMinimumHeight / 1.5),
            0,
            0
        },
        {
            static_cast <int> (uaw::PreferredMinimumWidth * 1.2),
            static_cast <int> (uaw::PreferredMinimumHeight * 1.2),
            0,
            0
        }
    };

    uaw::ScreenSizeArray array;

    array.array = sizes;
    array.num = 3;

    ON_CALL (connection, GetScreenSizes (_))
        .WillByDefault (Return (array));

    EXPECT_CALL (connection, ChangeSizeIndex (&display, _, 2));

    uaw::ScaleToPreferredMinimum (&display, connection);
}

TEST_F (ResizeScreen, PreferHigherAllElseEqual)
{
    IgnoreGetScreenSizes ();

    XRRScreenSize sizes[3] =
    {
        {
            static_cast <int> (uaw::PreferredMinimumWidth / 2),
            static_cast <int> (uaw::PreferredMinimumHeight / 2),
            0,
            0
        },
        {
            static_cast <int> (uaw::PreferredMinimumWidth / 1.5),
            static_cast <int> (uaw::PreferredMinimumHeight / 1.5),
            0,
            0
        },
        {
            static_cast <int> (uaw::PreferredMinimumWidth * 1.5),
            static_cast <int> (uaw::PreferredMinimumHeight * 1.5),
            0,
            0
        }
    };

    uaw::ScreenSizeArray array;

    array.array = sizes;
    array.num = 3;

    ON_CALL (connection, GetScreenSizes (_))
        .WillByDefault (Return (array));

    EXPECT_CALL (connection, ChangeSizeIndex (&display, _, 2));

    uaw::ScaleToPreferredMinimum (&display, connection);
}

TEST_F (ResizeScreen, PreferCloserWidthThanHeight)
{
    IgnoreGetScreenSizes ();

    XRRScreenSize sizes[2] =
    {
        {
            static_cast <int> (uaw::PreferredMinimumWidth / 1.2),
            static_cast <int> (uaw::PreferredMinimumHeight / 1.5),
            0,
            0
        },
        {
            static_cast <int> (uaw::PreferredMinimumWidth / 1.5),
            static_cast <int> (uaw::PreferredMinimumHeight / 1.2),
            0,
            0
        }
    };

    uaw::ScreenSizeArray array;

    array.array = sizes;
    array.num = 2;

    ON_CALL (connection, GetScreenSizes (_))
        .WillByDefault (Return (array));

    EXPECT_CALL (connection, ChangeSizeIndex (&display, _, 0));

    uaw::ScaleToPreferredMinimum (&display, connection);
}
