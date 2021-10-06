/* Copyright (C) GIRA Giersiepen GmbH & Co. KG */

#ifndef HISTORYSTATEMACHINE_H_
#define HISTORYSTATEMACHINE_H_

/*!
 * Forward declaration for the HistoryStatemachine state machine.
 */
 class HistoryStatemachine;


#include <deque>
#include "../src-lib/sc_types.h"
#include "../src-lib/sc_statemachine.h"
#include <QObject>

/*! \file Header of the state machine 'History'.
*/


#ifndef SCT_EVENTS_HISTORY_H
#define SCT_EVENTS_HISTORY_H
#ifndef SC_INVALID_EVENT_VALUE
#define SC_INVALID_EVENT_VALUE 0
#endif

namespace history_events
{
typedef enum  {
	invalid_event = SC_INVALID_EVENT_VALUE,
	proceed,
	toggle,
	outside
} HistoryStatemachineEventName;

class SctEvent
{
	public:
		SctEvent(HistoryStatemachineEventName name) : name(name){}
		virtual ~SctEvent(){}
		const HistoryStatemachineEventName name;
		
};
		
template <typename T>
class TypedSctEvent : public SctEvent
{
	public:
		TypedSctEvent(HistoryStatemachineEventName name, T value) :
			SctEvent(name),
			value(value)
			{}
		virtual ~TypedSctEvent(){}
		const T value;
};

class SctEvent__proceed : public SctEvent
{
	public:
		SctEvent__proceed(HistoryStatemachineEventName name) : SctEvent(name){};
};
class SctEvent__toggle : public SctEvent
{
	public:
		SctEvent__toggle(HistoryStatemachineEventName name) : SctEvent(name){};
};
class SctEvent__outside : public SctEvent
{
	public:
		SctEvent__outside(HistoryStatemachineEventName name) : SctEvent(name){};
};

}
#endif /* SCT_EVENTS_HISTORY_H */


/*! Define indices of states in the StateConfVector */
#define SCVI_MAIN_REGION_START 0
#define SCVI_MAIN_REGION_START_MAIN_STATEA 0
#define SCVI_MAIN_REGION_START_MAIN_STATEA_INNER_LEFT_RED 0
#define SCVI_MAIN_REGION_START_MAIN_STATEA_INNER_LEFT_BLUE 0
#define SCVI_MAIN_REGION_START_MAIN_STATEA_INNER_LEFT_GREEN 0
#define SCVI_MAIN_REGION_START_MAIN_STATEB 0
#define SCVI_MAIN_REGION_START_MAIN_STATEB_INNER_RIGHT_MAGENTA 0
#define SCVI_MAIN_REGION_START_MAIN_STATEB_INNER_RIGHT_CYAN 0
#define SCVI_MAIN_REGION_OUTSIDE 0


class HistoryStatemachine : public QObject, public sc::StatemachineInterface
{
	Q_OBJECT
	
	public:
		HistoryStatemachine(QObject *parent);
		
		~HistoryStatemachine();
		
		/*! Enumeration of all states */ 
		typedef enum
		{
			History_last_state,
			main_region_Start,
			main_region_Start_main_StateA,
			main_region_Start_main_StateA_Inner_Left_Red,
			main_region_Start_main_StateA_Inner_Left_Blue,
			main_region_Start_main_StateA_Inner_Left_Green,
			main_region_Start_main_StateB,
			main_region_Start_main_StateB_Inner_Right_Magenta,
			main_region_Start_main_StateB_Inner_Right_Cyan,
			main_region_Outside
		} HistoryStates;
					
		static const sc_integer numStates = 9;
		
		//! Inner class for default interface scope operation callbacks.
		class OperationCallback
		{
			public:
				virtual ~OperationCallback() = 0;
				
				virtual void label(sc_string text) = 0;
				
				
		};
		
		/*! Set the working instance of the operation callback interface 'OperationCallback'. */
		void setOperationCallback(OperationCallback* operationCallback);
		
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
		sc_boolean isStateActive(HistoryStates state) const;
		
		
		
	public slots:
		/*! slot for the in event 'proceed' that is defined in the default interface scope. */
		void proceed();
		
		/*! slot for the in event 'toggle' that is defined in the default interface scope. */
		void toggle();
		
		/*! slot for the in event 'outside' that is defined in the default interface scope. */
		void outside();
		
		
	protected:
		
		
	private:
		HistoryStatemachine(const HistoryStatemachine &rhs);
		HistoryStatemachine& operator=(const HistoryStatemachine&);
		
		/*! Raises the in event 'proceed' that is defined in the default interface scope. */
		void internal_proceed();
		sc_boolean proceed_raised;
		/*! Raises the in event 'toggle' that is defined in the default interface scope. */
		void internal_toggle();
		sc_boolean toggle_raised;
		/*! Raises the in event 'outside' that is defined in the default interface scope. */
		void internal_outside();
		sc_boolean outside_raised;
		void iface_dispatch_event(history_events::SctEvent * event);
		
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc_ushort maxOrthogonalStates = 1;
			//! dimension of the state configuration vector for history states
		static const sc_ushort maxHistoryStates = 3;
		
		
		
		HistoryStates stateConfVector[maxOrthogonalStates];
		
		HistoryStates historyVector[maxHistoryStates];
		
		OperationCallback* ifaceOperationCallback;
		
		
		sc_boolean isExecuting;
		
		
		// prototypes of all internal functions
		
		void enact_main_region_Start_main_StateA_Inner_Left_Red();
		void enact_main_region_Start_main_StateA_Inner_Left_Blue();
		void enact_main_region_Start_main_StateA_Inner_Left_Green();
		void enact_main_region_Start_main_StateB_Inner_Right_Magenta();
		void enact_main_region_Start_main_StateB_Inner_Right_Cyan();
		void enact_main_region_Outside();
		void enseq_main_region_Start_default();
		void enseq_main_region_Start_main_StateA_default();
		void enseq_main_region_Start_main_StateA_Inner_Left_Red_default();
		void enseq_main_region_Start_main_StateA_Inner_Left_Blue_default();
		void enseq_main_region_Start_main_StateA_Inner_Left_Green_default();
		void enseq_main_region_Start_main_StateB_default();
		void enseq_main_region_Start_main_StateB_Inner_Right_Magenta_default();
		void enseq_main_region_Start_main_StateB_Inner_Right_Cyan_default();
		void enseq_main_region_Outside_default();
		void enseq_main_region_default();
		void enseq_main_region_Start_main_default();
		void dhenseq_main_region_Start_main();
		void enseq_main_region_Start_main_StateA_Inner_Left_default();
		void dhenseq_main_region_Start_main_StateA_Inner_Left();
		void enseq_main_region_Start_main_StateB_Inner_Right_default();
		void dhenseq_main_region_Start_main_StateB_Inner_Right();
		void exseq_main_region_Start();
		void exseq_main_region_Start_main_StateA();
		void exseq_main_region_Start_main_StateA_Inner_Left_Red();
		void exseq_main_region_Start_main_StateA_Inner_Left_Blue();
		void exseq_main_region_Start_main_StateA_Inner_Left_Green();
		void exseq_main_region_Start_main_StateB();
		void exseq_main_region_Start_main_StateB_Inner_Right_Magenta();
		void exseq_main_region_Start_main_StateB_Inner_Right_Cyan();
		void exseq_main_region_Outside();
		void exseq_main_region();
		void exseq_main_region_Start_main();
		void exseq_main_region_Start_main_StateA_Inner_Left();
		void exseq_main_region_Start_main_StateB_Inner_Right();
		void react_main_region__entry_Default();
		void react_main_region_Start_main_StateA_Inner_Left__entry_Default();
		void react_main_region_Start_main_StateB_Inner_Right__entry_Default();
		void react_main_region_Start_main__entry_Default();
		void react_main_region_Start_main_ReturnoftheGYRAknights();
		sc_integer react(const sc_integer transitioned_before);
		sc_integer main_region_Start_react(const sc_integer transitioned_before);
		sc_integer main_region_Start_main_StateA_react(const sc_integer transitioned_before);
		sc_integer main_region_Start_main_StateA_Inner_Left_Red_react(const sc_integer transitioned_before);
		sc_integer main_region_Start_main_StateA_Inner_Left_Blue_react(const sc_integer transitioned_before);
		sc_integer main_region_Start_main_StateA_Inner_Left_Green_react(const sc_integer transitioned_before);
		sc_integer main_region_Start_main_StateB_react(const sc_integer transitioned_before);
		sc_integer main_region_Start_main_StateB_Inner_Right_Magenta_react(const sc_integer transitioned_before);
		sc_integer main_region_Start_main_StateB_Inner_Right_Cyan_react(const sc_integer transitioned_before);
		sc_integer main_region_Outside_react(const sc_integer transitioned_before);
		void clearInEvents();
		void microStep();
		void runCycle();
		
		
		history_events::SctEvent* getNextEvent();
		void dispatch_event(history_events::SctEvent * event);
		std::deque<history_events::SctEvent*> inEventQueue;
		
		
};


inline HistoryStatemachine::OperationCallback::~OperationCallback() {}


#endif /* HISTORYSTATEMACHINE_H_ */
