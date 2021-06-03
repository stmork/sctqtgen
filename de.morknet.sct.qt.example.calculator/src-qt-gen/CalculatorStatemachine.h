/* Copyright (C) 2021 - Steffen A. Mork */

#ifndef CALCULATORSTATEMACHINE_H_
#define CALCULATORSTATEMACHINE_H_

/*!
 * Forward declaration for the CalculatorStatemachine state machine.
 */
 class CalculatorStatemachine;


#include <deque>
#include "../src-qt-lib/sc_types.h"
#include "../src-qt-lib/sc_rxcpp.h"
#include "../src-qt-lib/sc_statemachine.h"
#include "../src-qt-lib/sc_timer.h"
#include <QObject>

/*! \file Header of the state machine 'Calculator'.
*/


#ifndef SCT_EVENTS_CALCULATOR_H
#define SCT_EVENTS_CALCULATOR_H
#ifndef SC_INVALID_EVENT_VALUE
#define SC_INVALID_EVENT_VALUE 0
#endif

namespace calculator_events
{
typedef enum  {
	invalid_event = SC_INVALID_EVENT_VALUE,
	Gui_Button0,
	Gui_Button1,
	Gui_Button2,
	Gui_Button3,
	Gui_Button4,
	Gui_Button5,
	Gui_Button6,
	Gui_Button7,
	Gui_Button8,
	Gui_Button9,
	Gui_ButtonAdd,
	Gui_ButtonSub,
	Gui_ButtonMult,
	Gui_ButtonDiv,
	Gui_ButtonEquals,
	Gui_ButtonClear,
	Calculator_main_region_active_time_event_0
} CalculatorStatemachineEventName;

class SctEvent
{
	public:
		SctEvent(CalculatorStatemachineEventName name) : name(name){}
		virtual ~SctEvent(){}
		const CalculatorStatemachineEventName name;
		
};
		
template <typename T>
class TypedSctEvent : public SctEvent
{
	public:
		TypedSctEvent(CalculatorStatemachineEventName name, T value) :
			SctEvent(name),
			value(value)
			{}
		virtual ~TypedSctEvent(){}
		const T value;
};

class SctEvent_Gui_Button0 : public SctEvent
{
	public:
		SctEvent_Gui_Button0(CalculatorStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_Button1 : public SctEvent
{
	public:
		SctEvent_Gui_Button1(CalculatorStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_Button2 : public SctEvent
{
	public:
		SctEvent_Gui_Button2(CalculatorStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_Button3 : public SctEvent
{
	public:
		SctEvent_Gui_Button3(CalculatorStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_Button4 : public SctEvent
{
	public:
		SctEvent_Gui_Button4(CalculatorStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_Button5 : public SctEvent
{
	public:
		SctEvent_Gui_Button5(CalculatorStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_Button6 : public SctEvent
{
	public:
		SctEvent_Gui_Button6(CalculatorStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_Button7 : public SctEvent
{
	public:
		SctEvent_Gui_Button7(CalculatorStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_Button8 : public SctEvent
{
	public:
		SctEvent_Gui_Button8(CalculatorStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_Button9 : public SctEvent
{
	public:
		SctEvent_Gui_Button9(CalculatorStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_ButtonAdd : public SctEvent
{
	public:
		SctEvent_Gui_ButtonAdd(CalculatorStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_ButtonSub : public SctEvent
{
	public:
		SctEvent_Gui_ButtonSub(CalculatorStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_ButtonMult : public SctEvent
{
	public:
		SctEvent_Gui_ButtonMult(CalculatorStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_ButtonDiv : public SctEvent
{
	public:
		SctEvent_Gui_ButtonDiv(CalculatorStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_ButtonEquals : public SctEvent
{
	public:
		SctEvent_Gui_ButtonEquals(CalculatorStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_ButtonClear : public SctEvent
{
	public:
		SctEvent_Gui_ButtonClear(CalculatorStatemachineEventName name) : SctEvent(name){};
};
class TimedSctEvent : public SctEvent
{
	public:
		TimedSctEvent(CalculatorStatemachineEventName name) : SctEvent(name){};
};

}
#endif /* SCT_EVENTS_CALCULATOR_H */


/*! Define indices of states in the StateConfVector */
#define SCVI_MAIN_REGION_ACTIVE 0
#define SCVI_MAIN_REGION__FINAL_ 0


class CalculatorStatemachine : public QObject, public sc::timer::TimedInterface, public sc::StatemachineInterface
{
	Q_OBJECT
	
	public:
		CalculatorStatemachine(QObject *parent);
		
		~CalculatorStatemachine();
		
		/*! Enumeration of all states */ 
		typedef enum
		{
			Calculator_last_state,
			main_region_active,
			main_region__final_
		} CalculatorStates;
					
		static const sc_integer numStates = 2;
		
		//! Inner class for gui interface scope.
		class Gui
		{
			public:
				Gui(CalculatorStatemachine* parent);
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
			protected:
				friend class CalculatorStatemachine;
				
				/*! Raises the in event 'Button0' that is defined in the interface scope 'gui'. */
				void internal_gui_Button0();
				sc_boolean Button0_raised;
				/*! Raises the in event 'Button1' that is defined in the interface scope 'gui'. */
				void internal_gui_Button1();
				sc_boolean Button1_raised;
				/*! Raises the in event 'Button2' that is defined in the interface scope 'gui'. */
				void internal_gui_Button2();
				sc_boolean Button2_raised;
				/*! Raises the in event 'Button3' that is defined in the interface scope 'gui'. */
				void internal_gui_Button3();
				sc_boolean Button3_raised;
				/*! Raises the in event 'Button4' that is defined in the interface scope 'gui'. */
				void internal_gui_Button4();
				sc_boolean Button4_raised;
				/*! Raises the in event 'Button5' that is defined in the interface scope 'gui'. */
				void internal_gui_Button5();
				sc_boolean Button5_raised;
				/*! Raises the in event 'Button6' that is defined in the interface scope 'gui'. */
				void internal_gui_Button6();
				sc_boolean Button6_raised;
				/*! Raises the in event 'Button7' that is defined in the interface scope 'gui'. */
				void internal_gui_Button7();
				sc_boolean Button7_raised;
				/*! Raises the in event 'Button8' that is defined in the interface scope 'gui'. */
				void internal_gui_Button8();
				sc_boolean Button8_raised;
				/*! Raises the in event 'Button9' that is defined in the interface scope 'gui'. */
				void internal_gui_Button9();
				sc_boolean Button9_raised;
				/*! Raises the in event 'ButtonAdd' that is defined in the interface scope 'gui'. */
				void internal_gui_ButtonAdd();
				sc_boolean ButtonAdd_raised;
				/*! Raises the in event 'ButtonSub' that is defined in the interface scope 'gui'. */
				void internal_gui_ButtonSub();
				sc_boolean ButtonSub_raised;
				/*! Raises the in event 'ButtonMult' that is defined in the interface scope 'gui'. */
				void internal_gui_ButtonMult();
				sc_boolean ButtonMult_raised;
				/*! Raises the in event 'ButtonDiv' that is defined in the interface scope 'gui'. */
				void internal_gui_ButtonDiv();
				sc_boolean ButtonDiv_raised;
				/*! Raises the in event 'ButtonEquals' that is defined in the interface scope 'gui'. */
				void internal_gui_ButtonEquals();
				sc_boolean ButtonEquals_raised;
				/*! Raises the in event 'ButtonClear' that is defined in the interface scope 'gui'. */
				void internal_gui_ButtonClear();
				sc_boolean ButtonClear_raised;
				void dispatch_event(calculator_events::SctEvent * event);
				
				
			private:
				CalculatorStatemachine* parent;
				
				
				
				
				
		};
		
		/*! Returns an instance of the interface class 'Gui'. */
		Gui* gui();
		
		//! Inner class for internal interface scope operation callbacks.
		class InternalOperationCallback
		{
			public:
				virtual ~InternalOperationCallback() = 0;
				
				virtual void Add() = 0;
				
				virtual void Sub() = 0;
				
				virtual void Mult() = 0;
				
				virtual void Div() = 0;
				
				virtual void Equals() = 0;
				
				virtual void Clear() = 0;
				
				virtual void Digit(sc_integer digit) = 0;
				
				
		};
		
		/*! Set the working instance of the operation callback interface 'InternalOperationCallback'. */
		void setInternalOperationCallback(InternalOperationCallback* operationCallback);
		
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
		
		/*
		 * Functions inherited from TimedStatemachineInterface
		 */
		virtual void setTimerService(sc::timer::TimerServiceInterface* timerService);
		
		virtual sc::timer::TimerServiceInterface* getTimerService();
		
		virtual void raiseTimeEvent(sc_eventid event);
		
		virtual sc_integer getNumberOfParallelTimeEvents();
		
		
		
		/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
		sc_boolean isStateActive(CalculatorStates state) const;
		
		//! number of time events used by the state machine.
		static const sc_integer timeEventsCount = 1;
		
		//! number of time events that can be active at once.
		static const sc_integer parallelTimeEventsCount = 1;
		
		
	public slots:
		/*! slot for the in event 'Button0' that is defined in the interface scope 'gui'. */
		void gui_Button0();
		
		/*! slot for the in event 'Button1' that is defined in the interface scope 'gui'. */
		void gui_Button1();
		
		/*! slot for the in event 'Button2' that is defined in the interface scope 'gui'. */
		void gui_Button2();
		
		/*! slot for the in event 'Button3' that is defined in the interface scope 'gui'. */
		void gui_Button3();
		
		/*! slot for the in event 'Button4' that is defined in the interface scope 'gui'. */
		void gui_Button4();
		
		/*! slot for the in event 'Button5' that is defined in the interface scope 'gui'. */
		void gui_Button5();
		
		/*! slot for the in event 'Button6' that is defined in the interface scope 'gui'. */
		void gui_Button6();
		
		/*! slot for the in event 'Button7' that is defined in the interface scope 'gui'. */
		void gui_Button7();
		
		/*! slot for the in event 'Button8' that is defined in the interface scope 'gui'. */
		void gui_Button8();
		
		/*! slot for the in event 'Button9' that is defined in the interface scope 'gui'. */
		void gui_Button9();
		
		/*! slot for the in event 'ButtonAdd' that is defined in the interface scope 'gui'. */
		void gui_ButtonAdd();
		
		/*! slot for the in event 'ButtonSub' that is defined in the interface scope 'gui'. */
		void gui_ButtonSub();
		
		/*! slot for the in event 'ButtonMult' that is defined in the interface scope 'gui'. */
		void gui_ButtonMult();
		
		/*! slot for the in event 'ButtonDiv' that is defined in the interface scope 'gui'. */
		void gui_ButtonDiv();
		
		/*! slot for the in event 'ButtonEquals' that is defined in the interface scope 'gui'. */
		void gui_ButtonEquals();
		
		/*! slot for the in event 'ButtonClear' that is defined in the interface scope 'gui'. */
		void gui_ButtonClear();
		
		
	signals:
		/*! Signal representing the out event 'Exit' that is defined in the interface scope 'gui'. */
		void gui_Exit();
		
		/*! Signal representing the out event 'ShowAccu' that is defined in the interface scope 'gui'. */
		void gui_ShowAccu(sc_integer value);
		
	
	protected:
		CalculatorStatemachine(const CalculatorStatemachine &rhs);
		CalculatorStatemachine& operator=(const CalculatorStatemachine&);
		
		sc_integer operand;
		sc_integer accu;
		void internal_dispatch_event(calculator_events::SctEvent * event);
		
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc_ushort maxOrthogonalStates = 1;
		
		sc::timer::TimerServiceInterface* timerService;
		sc_boolean timeEvents[timeEventsCount];
		
		
		CalculatorStates stateConfVector[maxOrthogonalStates];
		
		
		Gui ifaceGui;
		InternalOperationCallback* ifaceInternalOperationCallback;
		
		
		sc_boolean isExecuting;
		
		/*! Gets the value of the variable 'operand' that is defined in the internal scope. */
		sc_integer getOperand() const;
		
		/*! Sets the value of the variable 'operand' that is defined in the internal scope. */
		void setOperand(sc_integer value);
		
		/*! Gets the value of the variable 'accu' that is defined in the internal scope. */
		sc_integer getAccu() const;
		
		/*! Sets the value of the variable 'accu' that is defined in the internal scope. */
		void setAccu(sc_integer value);
		
		
		// prototypes of all internal functions
		
		void enact_main_region_active();
		void exact_main_region_active();
		void enseq_main_region_active_default();
		void enseq_main_region__final__default();
		void enseq_main_region_default();
		void exseq_main_region_active();
		void exseq_main_region__final_();
		void exseq_main_region();
		void react_main_region__entry_Default();
		sc_integer react(const sc_integer transitioned_before);
		sc_integer main_region_active_react(const sc_integer transitioned_before);
		sc_integer main_region__final__react(const sc_integer transitioned_before);
		void clearInEvents();
		void microStep();
		void runCycle();
		
		
		
		
	private:
		calculator_events::SctEvent* getNextEvent();
		void dispatch_event(calculator_events::SctEvent * event);
		calculator_events::CalculatorStatemachineEventName getTimedEventName(sc_eventid evid);
		std::deque<calculator_events::SctEvent*> inEventQueue;
		
		
};


inline CalculatorStatemachine::InternalOperationCallback::~InternalOperationCallback() {}


#endif /* CALCULATORSTATEMACHINE_H_ */
