/* Copyright (C) 2023 - Steffen A. Mork */

#pragma once

#ifndef SC_QT_TIMERSERVICE_H_
#define SC_QT_TIMERSERVICE_H_

#include <memory>

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
			QObject          *          parent,
			sc::timer::TimedInterface * statemachine,
			const sc::eventid           id);
		SCTimer() = delete;

	private:
		sc::timer::TimedInterface * machine;
		sc::eventid                 event_id;
	};

	class SCTimerService : public QObject, public sc::timer::TimerServiceInterface
	{
		Q_OBJECT

	public:
		explicit SCTimerService(QObject * parent = nullptr);

		virtual void setTimer(
			std::shared_ptr<sc::timer::TimedInterface> statemachine,
			sc::eventid                                event,
			sc::integer                                time_ms,
			bool                                       is_periodic) override;
		virtual void unsetTimer(
			std::shared_ptr<sc::timer::TimedInterface> statemachine,
			sc::eventid                                event) override;

	private:
		SCTimer * getTimer(sc::timer::TimedInterface * machine, sc::eventid event);

		typedef std::pair<sc::timer::TimedInterface *, sc::eventid> TimerKey;

		typedef QMap<TimerKey, SCTimer *>                           TimerMap;

		TimerMap chart_map;
	};
}

#endif // SC_QT_TIMERSERVICE_H_


