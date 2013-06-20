/*
 * resizescreen.cpp
 *
 * Utility functions to change the screen size for testing purposes
 *
 * See LICENSE.md for Copyright information
 */
#include <vector>
#include <limits>

#include <cmath>

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#include "resizescreen.h"
#include "x11_connection.h"

namespace uaw = unity::autopilot_wrapper;

bool uaw::ScaleToPreferredMinimum (Display             *display,
                                   X11Connection const &connection)
{
    auto              deleter = uaw::XRRScreenConfigDeleter ();
    uaw::ScreenConfig config (connection.GetConfig (display),
                              deleter);
    uaw::ScreenSizeArray sizes =
        connection.GetScreenSizes (config);

    int bestScoringPositive = -1;
    int bestScoringNegative = -1;
    unsigned int bestScoringWidth =
        std::numeric_limits <unsigned int>::max ();
    unsigned int bestScoringHeight =
        std::numeric_limits <unsigned int>::max ();

    if (sizes.num > 1)
    {
        for (int i = 0; i < static_cast <int> (sizes.num); ++i)
        {
            unsigned int width = sizes.array[i].width;
            unsigned int height = sizes.array[i].height;

            /* Short circuit */
            if (width == uaw::PreferredMinimumWidth &&
                height == uaw::PreferredMinimumHeight)
            {
                connection.ChangeSizeIndex (display, config, i);
                return true;
            }

            int widthDifference =
                uaw::PreferredMinimumWidth - width;
            int heightDifference =
                uaw::PreferredMinimumHeight - height;

            unsigned int absoluteWidthDifference =
                std::abs (widthDifference);
            unsigned int absoluteHeightDifference =
                std::abs (heightDifference);

            bool negative = false;

            if (widthDifference < 0 ||
                heightDifference < 0)
                negative = true;

            const bool widthBestScore =
                absoluteWidthDifference > bestScoringWidth;
            const bool heightBestScore =
                absoluteHeightDifference > bestScoringHeight;

            const bool bothDimentionsBestScore =
                widthBestScore && heightBestScore;

            if (bothDimentionsBestScore ||
                (absoluteWidthDifference < bestScoringWidth))
            {
                if (negative)
                    bestScoringNegative = i;
                else
                    bestScoringPositive = i;

                bestScoringWidth = absoluteWidthDifference;
                bestScoringHeight = absoluteHeightDifference;
            }
        }

        /* Prefer any positive score over a negative score all else equal */
        unsigned int widthPositive = 0;
        unsigned int heightPositive = 0;
        unsigned int widthNegative = 0;
        unsigned int heightNegative = 0;

        if (static_cast <int> (bestScoringNegative) != -1)
        {
            widthNegative = std::abs (sizes.array[bestScoringNegative].width);
            heightNegative = std::abs (sizes.array[bestScoringNegative].height);
        }

        if (static_cast <int> (bestScoringPositive) != -1)
        {
            widthPositive = sizes.array[bestScoringPositive].width;
            heightPositive = sizes.array[bestScoringPositive].height;
        }

        bool widthEqual = widthPositive == widthNegative;
        bool heightEqual = heightPositive == heightNegative;

        int index = -1;

        if (widthEqual && heightEqual)
            index = bestScoringPositive;
        else if (widthPositive > widthNegative)
            index = bestScoringPositive;
        else if (widthNegative && heightNegative)
            index = bestScoringNegative;

        if (index != -1)
        {
            connection.ChangeSizeIndex (display,
                                        config,
                                        static_cast <unsigned int> (index));
            return true;
        }
    }

    return false;
}
