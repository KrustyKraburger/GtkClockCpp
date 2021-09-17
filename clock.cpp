
#include <iostream>
#include <ctime>
#include <cmath>
#include <cairomm/context.h>
#include <glibmm/main.h>

#include "clock.h"

namespace Clock
{
    static double getClockRadius(ClockStyle& style);
    static void ctx_set_source_rgba(const Cairo::RefPtr<Cairo::Context>& ctx, Gdk::RGBA& rgba);
    static void setAreaTransform(const Cairo::RefPtr<Cairo::Context>& ctx, Gdk::Rectangle& drawingArea);
    static void drawClockCircle(const Cairo::RefPtr<Cairo::Context>& ctx, ClockStyle& style);
    static void drawClockTicks(const Cairo::RefPtr<Cairo::Context>& ctx, ClockStyle& style);
    static void drawClockArrows(const Cairo::RefPtr<Cairo::Context>& ctx, ClockStyle& style);

    ClockWidget::ClockWidget()
    {
        set_vexpand(true);
        set_hexpand(true);
        
        _timerSlot = Glib::signal_timeout()
            .connect(sigc::mem_fun(*this, &ClockWidget::on_timeout), 1000);
    }

    ClockWidget::ClockWidget(const ClockStyle& style) : ClockWidget()
    {
        _style = style;
    }

    ClockWidget::~ClockWidget()
    {
        if (_timerSlot.connected())
            _timerSlot.disconnect();
    }

    bool ClockWidget::on_timeout()
    {
        if (get_parent() != nullptr)
            queue_draw();
            
        return true;
    }

    bool ClockWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& ctx)
    {
        auto widgetRect = get_allocation();
        setAreaTransform(ctx, widgetRect);
        drawClockCircle(ctx, _style);
        drawClockTicks(ctx, _style);
        drawClockArrows(ctx, _style);

        return true;
    }

    static void setAreaTransform(const Cairo::RefPtr<Cairo::Context>& ctx, 
        Gdk::Rectangle& drawingArea)
    {
        auto width = drawingArea.get_width();
        auto height = drawingArea.get_height();
        auto scaleFactor = std::min(width, height);
        ctx->scale(scaleFactor, scaleFactor);
        ctx->translate(0.5 * width / scaleFactor, 0.5 * height / scaleFactor);
    }

    static void ctx_set_source_rgba(const Cairo::RefPtr<Cairo::Context>& ctx, 
        Gdk::RGBA& rgba)
    {
        ctx->set_source_rgba(
            rgba.get_red(), 
            rgba.get_green(), 
            rgba.get_blue(), 
            rgba.get_alpha());
    }

    static double getClockRadius(ClockStyle& style)
    {
        return 0.5 - style.LineWidth / 2.0;
    }

    static void drawClockCircle(const Cairo::RefPtr<Cairo::Context>& ctx, 
        ClockStyle& style)
    {
        ctx->save();
        ctx->set_line_width(style.LineWidth);
        ctx->arc(0.0, 0.0, getClockRadius(style), 0.0, 2.0 * M_PI);
        ctx_set_source_rgba(ctx, style.Background);
        ctx->fill_preserve();
        ctx_set_source_rgba(ctx, style.Border);
        ctx->stroke_preserve();
        ctx->restore();
    }

    static void drawClockTicks(const Cairo::RefPtr<Cairo::Context>& ctx, 
        ClockStyle& style)
    {
        ctx->set_line_width(style.LineWidth);
        ctx->set_source_rgba(0.0, 0.0, 0.0, 1.0);
        ctx->set_line_cap(Cairo::LINE_CAP_ROUND);

        auto radius = getClockRadius(style);
        for (int i = 0; i < 12; i++)
        {
            ctx->save();

            auto currentTickSize = style.TickSize;
            if (i % 3 != 0)
            {
                currentTickSize *= 0.5;
                ctx->set_line_width(style.LineWidth / 3.0);
            }

            ctx->move_to(
                (radius - currentTickSize) * cos(i * M_PI / 6),
                (radius - currentTickSize) * sin(i * M_PI / 6));
            ctx->line_to(
                radius * cos(i * M_PI / 6),
                radius * sin(i * M_PI / 6));

            ctx->stroke();
            ctx->restore();
        }
    }

    static int convertHours(int utcHours, int utcOffset)
    {
        auto time = utcHours + utcOffset;
        if (time < 0)
            time += 24;
        else if (time >= 24)
            time -= 24;

        return time;
    }

    static void drawClockArrows(const Cairo::RefPtr<Cairo::Context>& ctx, 
        ClockStyle& style)
    {
        time_t epocheSeconds = time(NULL);
        struct tm* pTimeInfo = gmtime(&epocheSeconds);
        
        // Seconds
        auto angle = pTimeInfo->tm_sec * M_PI / 30.0;
        auto maxArrowSize = getClockRadius(style) - style.TickSize;
        auto arrowSize = 0.95 * maxArrowSize;
        ctx->save();
        ctx->set_line_width(style.LineWidth / 3.0);
        ctx_set_source_rgba(ctx, style.Seconds);
        ctx->move_to(0.0, 0.0);
        ctx->line_to(arrowSize * sin(angle), - arrowSize * cos(angle));
        ctx->stroke();
        ctx->restore();

        // Minutes
        angle = pTimeInfo->tm_min * M_PI / 30.0 + angle / 60.0;
        arrowSize = 0.8 * maxArrowSize;
        ctx_set_source_rgba(ctx, style.Minutes);
        ctx->move_to(0.0, 0.0);
        ctx->line_to(arrowSize * sin(angle), - arrowSize * cos(angle));
        ctx->stroke();

        // Hours
        auto hourse = convertHours(pTimeInfo->tm_hour, style.UtcOffset);
        angle = hourse * M_PI / 6.0 + angle / 12.0;
        arrowSize = 0.6 * maxArrowSize;
        ctx_set_source_rgba(ctx, style.Hours);
        ctx->move_to(0.0, 0.0);
        ctx->line_to(arrowSize * sin(angle), - arrowSize * cos(angle));
        ctx->stroke();

        ctx->set_source_rgba(0.0, 0.0, 0.0, 1.0);
        ctx->arc(0.0, 0.0, 0.5 * style.LineWidth, 0.0, 2.0 * M_PI);
        ctx->fill();
    }
}
