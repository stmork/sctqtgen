/* Copyright (C) 2022 - Steffen A. Mork */

#include "sc_qt_timerservice.h"

using namespace sc::qt;
using namespace sc::timer;
using Qt::TimerType::PreciseTimer;
using Qt::TimerType::CoarseTimer;

SCTimer::SCTimer(QObject * parent, TimedInterface * statemachine, const sc::eventid new_id) :
	QTimer(parent),
	machine(statemachine),
	event_id(new_id)
{
	assert(statemachine != nullptr);

	connect(this, &QTimer::timeout, [this] ()
	{
		machine->raiseTimeEvent(event_id);
	});
}

SCTimerService::SCTimerService(QObject * parent) : QObject(parent)
{
}

void SCTimerService::setTimer(
		TimedInterface * statemachine,
		sc::eventid      event,
		sc::integer      time_ms,
		bool             is_periodic)
{
	SCTimer *  timer          = getTimer(statemachine, event);
	const bool high_precision = (time_ms % 1000) != 0;

	// amor the timer
	timer->setTimerType(high_precision ? PreciseTimer : CoarseTimer);
	timer->setInterval(time_ms);
	timer->setSingleShot(!is_periodic);
	timer->start();
}

void SCTimerService::unsetTimer(
		TimedInterface * statemachine,
		sc::eventid      event)
{
	SCTimer * timer = this->getTimer(statemachine, event);

	if (timer != nullptr)
	{
		timer->stop();
	}
}

SCTimer * SCTimerService::getTimer(
		TimedInterface * statemachine,
		sc::eventid      event)
{
	TimerKey  key(statemachine, event);
	SCTimer * timer;

	if (chart_map.contains(key))
	{
		timer = chart_map[key];
	}
	else
	{
		timer = new SCTimer(this, statemachine, event);

		chart_map.insert(key, timer);
	}
	return timer;
}
