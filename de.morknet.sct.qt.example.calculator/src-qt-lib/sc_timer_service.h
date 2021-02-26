/* Copyright (C) 2021 - Steffen A. Mork */

#ifndef SC_TIMER_SERVICE_H_
#define SC_TIMER_SERVICE_H_

#include "sc_timer.h"

namespace sc {
namespace timer {

class TimerTask {

private:

	sc_integer time_ms;
	sc_boolean periodic;
	sc_eventid pt_evid;
	sc_integer elapsed_time_ms;
	TimedInterface *handle;

public:

	TimerTask() : //
			time_ms(0), //
			periodic(false), //
			pt_evid(0), //
			elapsed_time_ms(0), //
			handle(sc_null) //
	{
	}

	TimerTask(TimedInterface *statemachine, sc_eventid event, sc_integer time,
			sc_boolean isPeriodic) : //
			time_ms(time), //
			periodic(isPeriodic), //
			pt_evid(event), //
			elapsed_time_ms(0), //
			handle(statemachine) //
	{
	}

	~TimerTask() {
	}

	sc_integer getTimeMs() const {
		return time_ms;
	}

	void setTimeMs(sc_integer timeMs) {
		time_ms = timeMs;
	}

	sc_integer getElapsedTimeMs() const {
		return elapsed_time_ms;
	}

	void updateElapsedTimeMs(sc_integer elapsedTimeMs = 0) {
		elapsed_time_ms += elapsedTimeMs;
	}

	void setElapsedTimeMs(sc_integer elapsedTimeMs = 0) {
		elapsed_time_ms = elapsedTimeMs;
	}

	sc_eventid getPtEvid() const {
		return pt_evid;
	}

	void setPtEvid(sc_eventid ptEvid) {
		pt_evid = ptEvid;
	}

	sc_boolean isPeriodic() const {
		return periodic;
	}

	void setPeriodic(sc_boolean periodic) {
		this->periodic = periodic;
	}

	TimedInterface* getHandle() {
		return handle;
	}

	void setHandle(TimedInterface *handle) {
		this->handle = handle;
	}

};

class TimerService: public TimerServiceInterface {
private:
	sc_integer length;
	TimerTask *tasks;
public:

	TimerService(TimerTask *tasks, sc_integer length) {
		this->length = length;
		this->tasks = tasks;
	}

	virtual ~TimerService() {
		cancel();
	}

	/*! Starts the timing for a time event.
	 */
	virtual void setTimer(TimedInterface *statemachine, sc_eventid event,
			sc_integer time_ms, sc_boolean isPeriodic);

	/*! Unsets the given time event.
	 */
	virtual void unsetTimer(TimedInterface *statemachine, sc_eventid event);

	/*!
	 * This function must be called by the user. The elapsed time must be calculated every time,
	 * the function gets called.
	 */
	void proceed(sc_integer elapsed_ms);

	/*! Cancel timer service. Use this to end possible timing threads and free
	 memory resources.
	 */
	virtual void cancel();
};

} /* namespace sc::timer */
} /* namespace sc */

#endif /* SC_TIMER_SERVICE_H_ */

