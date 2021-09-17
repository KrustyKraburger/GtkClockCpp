
#include "clockStyle.h"

namespace Clock
{
    ClockStyle::ClockStyle() : LineWidth(0.03), TickSize(0.08), UtcOffset(3)
    {
        Background.set_rgba(0.44, 0.44, 1.0, 0.4);
        Border.set_rgba(0.0, 0.0, 0.0, 1.0);
        Seconds.set_rgba(20.0 / 255.0, 68.0 / 255.0, 1.0, 1.0);
        Minutes.set_rgba(1.0, 104.0 / 255.0, 147.0 / 255.0, 1.0);
        Hours.set_rgba(1.0, 88.0 / 255.0, 17.0 / 255.0, 1.0);
    }

    ClockStyle::~ClockStyle()
    {
    }
}
