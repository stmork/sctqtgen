/* Copyright (C) 2021 - Steffen A. Mork */

#include "sc_timer_service.h"

using namespace sc::timer;

/*! Starts the timing for a time event.
 */
void TimerService::setTimer(TimedInterface *statemachine, sc_eventid event,
		sc_integer time_ms, sc_boolean isPeriodic) {

	/* create new task and go through all timers ... */
//	TimerTask *task = new TimerTask(statemachine, event, time_ms, isPeriodic);
	for (int i = 0; i < this->length; i++) {

		/* ... and find an unused one. */
		if (this->tasks[i].getPtEvid() == 0) {

			/* set timer properties */

			this->tasks[i].setPtEvid(event);
			this->tasks[i].setTimeMs(time_ms);
			this->tasks[i].setPeriodic(isPeriodic);
			this->tasks[i].setHandle(statemachine);

			// reset the elapsed time ...
			this->tasks[i].setElapsedTimeMs(0);

			break;
		}
	}
}

/*! Unsets the given time event.
 */
void TimerService::unsetTimer(TimedInterface *statemachine, sc_eventid event) {
	(void) statemachine;
	/* go through all timers ... */
	for (int i = 0; i < this->length; i++) {
		if (this->tasks[i].getPtEvid() == event) {
			this->tasks[i].setPtEvid(0);
			this->tasks[i].setHandle(sc_null);
		}
	}
}

/*!
 * This function must be called by the user. The elapsed time must be calculated every time,
 * the function gets called.
 */
void TimerService::proceed(sc_integer elapsed_ms) {

	/* go through all timers ... */
	for (int i = 0; i < this->length; i++) {

		/* ... and process all used */
		if (this->tasks[i].getPtEvid() != 0) {

			this->tasks[i].updateElapsedTimeMs(elapsed_ms);

			/* raise Time Event if the timer has proceed */
			if (this->tasks[i].getElapsedTimeMs()
					>= this->tasks[i].getTimeMs()) {

				/* raise time event */
				this->tasks[i].getHandle()->raiseTimeEvent(
						this->tasks[i].getPtEvid());

				/* update periodic timer */
				if (this->tasks[i].isPeriodic()) {
					this->tasks[i].setElapsedTimeMs(
							this->tasks[i].getElapsedTimeMs()
									- this->tasks[i].getTimeMs());
				}
			}
		}
	}
}

/*! Cancel timer service. Use this to end possible timing threads and free
 memory resources.
 */
void TimerService::cancel() {

	/* delete all timers */
	for (int i = 0; i < this->length; i++) {
		this->tasks[i].setPtEvid(0);
	}
}

