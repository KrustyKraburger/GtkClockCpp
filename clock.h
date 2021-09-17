
#pragma once

#include <sigc++/connection.h>
#include <gtkmm/drawingarea.h>
#include <gdkmm/rgba.h>
#include "clockStyle.h"

namespace Clock
{
    class ClockWidget : public Gtk::DrawingArea
    {
        public:
            ClockWidget();
            ClockWidget(const ClockStyle& style);
            virtual ~ClockWidget();

        private:
            sigc::connection _timerSlot;
            ClockStyle _style;
            bool on_timeout();
            bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx) override;
    };
}
