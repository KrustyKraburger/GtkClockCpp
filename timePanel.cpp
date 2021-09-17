
#include <gtkmm.h>
#include "timePanel.h"
#include "clock.h"

class CityClock : public Gtk::Grid
{
    public:
        CityClock(std::string cityName, const Clock::ClockStyle& style)
        {
            set_row_spacing(3);
            set_hexpand(true);
            set_vexpand(true);

            auto clock = Gtk::make_managed<Clock::ClockWidget>(style);
            attach_next_to(*clock, Gtk::PositionType::POS_TOP, 1, 1);

            auto label = Gtk::make_managed<Gtk::Label>();
            label->set_markup("<big>" + cityName + "</big>");
            label->set_justify(Gtk::Justification::JUSTIFY_CENTER);
            label->set_alignment(Gtk::Align::ALIGN_CENTER, Gtk::Align::ALIGN_END);
            attach_next_to(*label, *clock, Gtk::PositionType::POS_BOTTOM, 1, 1);

            show_all_children();
        }

    virtual ~CityClock()
    {
    }
};

TimePanel::TimePanel()
{
    set_column_homogeneous(true);
    set_row_homogeneous(true);
    set_row_spacing(3);
    set_hexpand(true);
    set_vexpand(true);

    auto style1 = std::make_unique<Clock::ClockStyle>();
    style1->UtcOffset = 3;
    auto clock1 = Gtk::make_managed<CityClock>("Moscow", *style1);
    attach_next_to(*clock1, Gtk::PositionType::POS_TOP, 1, 1);

    auto style2 = std::make_unique<Clock::ClockStyle>();
    style2->UtcOffset = 11;
    style2->Background.set_rgba(1.0, 1.0, 1.0, 1.0);
    style2->Seconds.set_rgba(255.0 / 255.0, 244.0 / 255.0, 38.0 / 255.0, 1.0);
    style2->Minutes.set_rgba(255.0 / 255.0, 182.0 / 255.0, 38.0 / 255.0, 1.0);
    style2->Hours.set_rgba(0.0, 0.0, 0.0, 1.0);
    auto clock2 = Gtk::make_managed<CityClock>("Magadan", *style2);
    attach_next_to(*clock2, *clock1, Gtk::PositionType::POS_BOTTOM, 1, 1);

    auto style3 = std::make_unique<Clock::ClockStyle>();
    style3->UtcOffset = 1;
    style3->Background.set_rgba(255.0 / 255.0, 160.0 / 255.0, 242.0 / 255.0, 1.0);
    style3->Seconds.set_rgba(110.0 / 255.0, 73.0 / 255.0, 255.0 / 255.0, 1.0);
    style3->Minutes.set_rgba(235.0 / 255.0, 91.0 / 255.0, 255.0 / 255.0, 1.0);
    style3->Hours.set_rgba(147.0 / 255.0, 255.0 / 255.0, 25.0 / 255.0, 1.0);
    auto clock3 = Gtk::make_managed<CityClock>("Paris", *style3);
    attach_next_to(*clock3, *clock1, Gtk::PositionType::POS_RIGHT, 1, 1);

    auto style4 = std::make_unique<Clock::ClockStyle>();
    style4->UtcOffset = -5;
    style4->Background.set_rgba(107.0 / 255.0, 185.0 / 255.0, 255.0 / 255.0, 1.0);
    style4->Seconds.set_rgba(55.0 / 255.0, 147.0 / 255.0, 158.0 / 255.0, 1.0);
    style4->Minutes.set_rgba(15.0 / 255.0, 77.0 / 255.0, 158.0 / 255.0, 1.0);
    style4->Hours.set_rgba(158.0 / 255.0, 28.0 / 255.0, 0.0 / 255.0, 1.0);
    auto clock4 = Gtk::make_managed<CityClock>("New York", *style4);
    attach_next_to(*clock4, *clock3, Gtk::PositionType::POS_BOTTOM, 1, 1);

    show_all_children();
}

TimePanel::~TimePanel()
{
}
