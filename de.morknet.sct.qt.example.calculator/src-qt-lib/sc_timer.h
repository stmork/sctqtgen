/* Copyright (C) 2021 - Steffen A. Mork */

#ifndef SC_TIMER_H_
#define SC_TIMER_H_

#include "sc_types.h"

namespace sc {
namespace timer {

class TimedInterface;
class TimerServiceInterface;

/*! \file Interface for state machines which use timed event triggers.
*/
class TimedInterface {
	public:
	
		virtual ~TimedInterface() = 0;
		
		/*! Set the timer service for the state machine. It must be set
		    externally on a timed state machine before a run cycle can be executed.
		*/
		virtual void setTimerService(sc::timer::TimerServiceInterface* timerService) = 0;
		
		/*! Returns the currently used timer service.
		*/
		virtual sc::timer::TimerServiceInterface* getTimerService() = 0;
		
		/*! Callback method if a time event occurred.
		*/
		virtual void raiseTimeEvent(sc_eventid event) = 0;
		
		/*! Method to retrieve the number of time events that can be 
			active at once in this state machine.
		*/
		virtual sc_integer getNumberOfParallelTimeEvents() = 0;
};

inline TimedInterface::~TimedInterface() {}


/*! \file Timer service interface.
 */
class TimerServiceInterface
{
	public:
		
		virtual ~TimerServiceInterface() = 0;
	
		/*! Starts the timing for a time event.
		 */ 
		virtual void setTimer(TimedInterface* statemachine, sc_eventid event, sc_integer time_ms, sc_boolean isPeriodic) = 0;
		
		/*! Unsets the given time event.
		 */
		virtual void unsetTimer(TimedInterface* statemachine, sc_eventid event) = 0;
	
		/*! Cancel timer service. Use this to end possible timing threads and free
		 	 memory resources.
		 */
		virtual void cancel() = 0;
};

inline TimerServiceInterface::~TimerServiceInterface() {}

} /* namespace sc::timer */
} /* namespace sc */

#endif /* SC_TIMER_H_ */