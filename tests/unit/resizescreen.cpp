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
using ::testing::Return;
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
    EXPECT_CALL (connection, ChangeSizeIndex (_, _)).Times (AtLeast (0));
}

void
ResizeScreen::IgnoreGetScreenSizes ()
{
    EXPECT_CALL (connection, GetScreenSizes (_)).Times (AtLeast (0));
}

TEST_F (ResizeScreen, AlwaysCheckAvailableScreenSizes)
{
    IgnoreChangeSizeIndex ();

    EXPECT_CALL (connection, GetScreenSizes (&display))
        .WillOnce (Return (uaw::ScreenSizeArray ()));

    uaw::ScaleToPreferredMinimum (&display, connection);
}

TEST_F (ResizeScreen, NoScreenSizesNoCallToScale)
{
    IgnoreGetScreenSizes ();

    ON_CALL (connection, GetScreenSizes (_))
        .WillByDefault (Return (uaw::ScreenSizeArray ()));

    EXPECT_CALL (connection, ChangeSizeIndex (_, _))
        .Times (0);

    uaw::ScaleToPreferredMinimum (&display, connection);
}

TEST_F (ResizeScreen, OneScreenSizeNoCallToScale)
{
    IgnoreGetScreenSizes ();

    uaw::ScreenSizeArray array;

    array.array.reset (new XRRScreenSize[1]);
    array.num = 1;

    ON_CALL (connection, GetScreenSizes (_))
        .WillByDefault (Return (array));

    EXPECT_CALL (connection, ChangeSizeIndex (_, _))
        .Times (0);

    uaw::ScaleToPreferredMinimum (&display, connection);
}

TEST_F (ResizeScreen, PickExact)
{
    IgnoreGetScreenSizes ();

    uaw::ScreenSizeArray array;

    array.array.reset (new XRRScreenSize[2]);
    array.num = 2;

    array.array[0].width = uaw::PreferredMinimumWidth / 2;
    array.array[0].height = uaw::PreferredMinimumHeight / 2;
    array.array[1].width = uaw::PreferredMinimumWidth;
    array.array[1].height = uaw::PreferredMinimumHeight;

    ON_CALL (connection, GetScreenSizes (_))
        .WillByDefault (Return (array));

    EXPECT_CALL (connection, ChangeSizeIndex (&display, 1));

    uaw::ScaleToPreferredMinimum (&display, connection);
}

TEST_F (ResizeScreen, PickBestLower)
{
    IgnoreGetScreenSizes ();

    uaw::ScreenSizeArray array;

    array.array.reset (new XRRScreenSize[3]);
    array.num = 3;

    array.array[0].width = uaw::PreferredMinimumWidth / 2;
    array.array[0].height = uaw::PreferredMinimumHeight / 2;
    array.array[1].width = uaw::PreferredMinimumWidth / 1.5;
    array.array[1].height = uaw::PreferredMinimumHeight / 1.5;
    array.array[2].width = uaw::PreferredMinimumWidth / 1.2;
    array.array[2].height = uaw::PreferredMinimumHeight / 1.2;

    ON_CALL (connection, GetScreenSizes (_))
        .WillByDefault (Return (array));

    EXPECT_CALL (connection, ChangeSizeIndex (&display, 2));

    uaw::ScaleToPreferredMinimum (&display, connection);
}


TEST_F (ResizeScreen, PickBestUpper)
{
    IgnoreGetScreenSizes ();

    uaw::ScreenSizeArray array;

    array.array.reset (new XRRScreenSize[3]);
    array.num = 3;

    array.array[0].width = uaw::PreferredMinimumWidth / 2;
    array.array[0].height = uaw::PreferredMinimumHeight / 2;
    array.array[1].width = uaw::PreferredMinimumWidth / 1.5;
    array.array[1].height = uaw::PreferredMinimumHeight / 1.5;
    array.array[2].width = uaw::PreferredMinimumWidth * 1.2;
    array.array[2].height = uaw::PreferredMinimumHeight * 1.2;

    ON_CALL (connection, GetScreenSizes (_))
        .WillByDefault (Return (array));

    EXPECT_CALL (connection, ChangeSizeIndex (&display, 2));

    uaw::ScaleToPreferredMinimum (&display, connection);
}

TEST_F (ResizeScreen, PreferHigherAllElseEqual)
{
    IgnoreGetScreenSizes ();

    uaw::ScreenSizeArray array;

    array.array.reset (new XRRScreenSize[3]);
    array.num = 3;

    array.array[0].width = uaw::PreferredMinimumWidth / 2;
    array.array[0].height = uaw::PreferredMinimumHeight / 2;
    array.array[1].width = uaw::PreferredMinimumWidth / 1.5;
    array.array[1].height = uaw::PreferredMinimumHeight / 1.5;
    array.array[2].width = uaw::PreferredMinimumWidth * 1.5;
    array.array[2].height = uaw::PreferredMinimumHeight * 1.5;

    ON_CALL (connection, GetScreenSizes (_))
        .WillByDefault (Return (array));

    EXPECT_CALL (connection, ChangeSizeIndex (&display, 2));

    uaw::ScaleToPreferredMinimum (&display, connection);
}

TEST_F (ResizeScreen, PreferCloserWidthThanHeight)
{
    IgnoreGetScreenSizes ();

    uaw::ScreenSizeArray array;

    array.array.reset (new XRRScreenSize[2]);
    array.num = 2;

    array.array[0].width = uaw::PreferredMinimumWidth / 1.2;
    array.array[0].height = uaw::PreferredMinimumHeight / 1.5;
    array.array[1].width = uaw::PreferredMinimumWidth / 1.5;
    array.array[1].height = uaw::PreferredMinimumHeight / 1.2;

    ON_CALL (connection, GetScreenSizes (_))
        .WillByDefault (Return (array));

    EXPECT_CALL (connection, ChangeSizeIndex (&display, 0));

    uaw::ScaleToPreferredMinimum (&display, connection);
}
