/* Copyright (C) 2021 - Steffen A. Mork */

#ifndef ABSTRACTTIMERLESS_H_
#define ABSTRACTTIMERLESS_H_

/*!
 * Forward declaration for the AbstractTimerLess state machine.
 */
 class AbstractTimerLess;


#include <deque>
#include "../src-qt-lib/sc_types.h"
#include "../src-qt-lib/sc_rxcpp.h"
#include "../src-qt-lib/sc_statemachine.h"
#include <QObject>

/*! \file Header of the state machine 'Timerless'.
*/


#ifndef SCT_EVENTS_TIMERLESS_H
#define SCT_EVENTS_TIMERLESS_H
#ifndef SC_INVALID_EVENT_VALUE
#define SC_INVALID_EVENT_VALUE 0
#endif

namespace timerless_events
{
typedef enum  {
	invalid_event = SC_INVALID_EVENT_VALUE,
	Gui_clicked
} AbstractTimerLessEventName;

class SctEvent
{
	public:
		SctEvent(AbstractTimerLessEventName name) : name(name){}
		virtual ~SctEvent(){}
		const AbstractTimerLessEventName name;
		
};
		
template <typename T>
class TypedSctEvent : public SctEvent
{
	public:
		TypedSctEvent(AbstractTimerLessEventName name, T value) :
			SctEvent(name),
			value(value)
			{}
		virtual ~TypedSctEvent(){}
		const T value;
};

class SctEvent_Gui_clicked : public SctEvent
{
	public:
		SctEvent_Gui_clicked(AbstractTimerLessEventName name) : SctEvent(name){};
};

}
#endif /* SCT_EVENTS_TIMERLESS_H */


/*! Define indices of states in the StateConfVector */
#define SCVI_MAIN_REGION_STATE_OFF 0
#define SCVI_MAIN_REGION_STATE_ON 0


class AbstractTimerLess : public QObject, public sc::StatemachineInterface
{
	Q_OBJECT
	
	public:
		AbstractTimerLess(QObject *parent);
		
		~AbstractTimerLess();
		
		/*! Enumeration of all states */ 
		typedef enum
		{
			Timerless_last_state,
			main_region_State_Off,
			main_region_State_On
		} TimerlessStates;
					
		static const sc_integer numStates = 2;
		
		//! Inner class for gui interface scope.
		class Gui
		{
			public:
				Gui(AbstractTimerLess* parent);
				
				
				
				
				
				
			protected:
				friend class AbstractTimerLess;
				
				/*! Raises the in event 'clicked' that is defined in the interface scope 'gui'. */
				void internal_gui_clicked();
				sc_boolean clicked_raised;
				void dispatch_event(timerless_events::SctEvent * event);
				
				
			private:
				AbstractTimerLess* parent;
				
				
				
				
				
		};
		
		/*! Returns an instance of the interface class 'Gui'. */
		Gui* gui();
		
		
		/*
		 * Functions inherited from StatemachineInterface
		 */
		virtual void enter();
		
		virtual void exit();
		
		/*!
		 * Checks if the state machine is active (until 2.4.1 this method was used for states).
		 * A state machine is active if it has been entered. It is inactive if it has not been entered at all or if it has been exited.
		 */
		virtual sc_boolean isActive() const;
		
		
		/*!
		* Checks if all active states are final. 
		* If there are no active states then the state machine is considered being inactive. In this case this method returns false.
		*/
		virtual sc_boolean isFinal() const;
		
		/*! 
		 * Checks if member of the state machine must be set. For example an operation callback.
		 */
		sc_boolean check();
		
		
		/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
		sc_boolean isStateActive(TimerlessStates state) const;
		
		
		
	public slots:
		/*! slot for the in event 'clicked' that is defined in the interface scope 'gui'. */
		void gui_clicked();
		
		
	signals:
		/*! Signal representing the out event 'on' that is defined in the interface scope 'gui'. */
		void gui_on();
		
		/*! Signal representing the out event 'off' that is defined in the interface scope 'gui'. */
		void gui_off();
		
	
	protected:
		
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc_ushort maxOrthogonalStates = 1;
		
		
		
		TimerlessStates stateConfVector[maxOrthogonalStates];
		
		
		Gui ifaceGui;
		
		
		sc_boolean isExecuting;
		
		
		// prototypes of all internal functions
		
		void enact_main_region_State_On();
		void exact_main_region_State_On();
		void enseq_main_region_State_Off_default();
		void enseq_main_region_State_On_default();
		void enseq_main_region_default();
		void exseq_main_region_State_Off();
		void exseq_main_region_State_On();
		void exseq_main_region();
		void react_main_region__entry_Default();
		sc_integer react(const sc_integer transitioned_before);
		sc_integer main_region_State_Off_react(const sc_integer transitioned_before);
		sc_integer main_region_State_On_react(const sc_integer transitioned_before);
		void clearInEvents();
		void microStep();
		void runCycle();
		
		
		
		
	private:
		timerless_events::SctEvent* getNextEvent();
		void dispatch_event(timerless_events::SctEvent * event);
		std::deque<timerless_events::SctEvent*> inEventQueue;
		
		
};




#endif /* ABSTRACTTIMERLESS_H_ */
