#include <bqpch.h>
#include <bq/event/event.h>

bq::event::event(bq::event_type t): type(t)
{
	
}

bq::event::event(event_type t, bq::keyboard::keycode k): type(t), keycode(k)
{
}

bq::event::event(event_type t, bq::v2f m): type(t), mouse_clicked_pos(m)
{
}

bq::event::~event()
{
}
