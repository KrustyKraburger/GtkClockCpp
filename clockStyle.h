
#pragma once

#include <gdkmm/rgba.h>

namespace Clock
{
    class ClockStyle
    {
        public:
            ClockStyle();
            ~ClockStyle();

            int UtcOffset;
            double LineWidth;
            double TickSize;
            Gdk::RGBA Background;
            Gdk::RGBA Border;
            Gdk::RGBA Seconds;
            Gdk::RGBA Minutes;
            Gdk::RGBA Hours;
    };
}