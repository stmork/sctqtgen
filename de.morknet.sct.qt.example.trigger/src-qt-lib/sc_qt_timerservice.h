/* Copyright (C) 2022 - Steffen A. Mork */

#pragma once

#ifndef SC_QT_TIMERSERVICE_H_
#define SC_QT_TIMERSERVICE_H_

#include <QObject>
#include <QTimer>
#include <QMap>

#include "sc_timer.h"

namespace sc::qt
{
	class SCTimer : public QTimer
	{
		Q_OBJECT

	public:
		explicit SCTimer(
				QObject *                   parent,
				sc::timer::TimedInterface * statemachine,
				const sc_eventid            id);
		SCTimer() = delete;

	private slots:
		void trigger();

	private:
		sc::timer::TimedInterface * machine;
		sc_eventid                  event_id;
	};

	class SCTimerService : public QObject, public sc::timer::TimerServiceInterface
	{
		Q_OBJECT

	public:
		explicit SCTimerService(QObject * parent = nullptr);

		virtual void setTimer(
				sc::timer::TimedInterface * statemachine,
				sc_eventid                  event,
				sc_integer                  time_ms,
				sc_boolean                  is_periodic) override;
		virtual void unsetTimer(
				sc::timer::TimedInterface * statemachine,
				sc_eventid                  event) override;
		virtual void cancel() override;

	private:
		SCTimer * getTimer(sc::timer::TimedInterface * machine, sc_eventid event);

		typedef std::pair<sc::timer::TimedInterface *, sc_eventid> TimerKey;

		typedef QMap<TimerKey, SCTimer *>                          TimerMap;

		TimerMap chart_map;
	};
}

#endif // SC_QT_TIMERSERVICE_H_


