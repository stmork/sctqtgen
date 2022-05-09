/* Copyright (C) 2022 - Steffen A. Mork */

#ifndef CALCULATORSTATEMACHINE_H_
#define CALCULATORSTATEMACHINE_H_

/*!
Forward declaration for the CalculatorStatemachine state machine.
*/
class CalculatorStatemachine;


#include <deque>
#include "../src-qt-lib/sc_types.h"
#include "../src-qt-lib/sc_statemachine.h"
#include "../src-qt-lib/sc_timer.h"
#include <QObject>

/*! \file
Header of the state machine 'CalculatorStatemachine'.
*/


class CalculatorStatemachine : public QObject, public sc::timer::TimedInterface, public sc::StatemachineInterface
{
	Q_OBJECT
	
	public:
		CalculatorStatemachine(QObject *parent);
		
		virtual ~CalculatorStatemachine();
		
		
		
		/*! Enumeration of all states. */
		enum class State
		{
			NO_STATE,
			main_region_active,
			main_region__final_
		};
		
		/*! The number of states. */
		static const sc::integer numStates = 2;
		static const sc::integer scvi_main_region_active = 0;
		static const sc::integer scvi_main_region__final_ = 0;
		
		/*! Enumeration of all events which are consumed. */
		enum class Event
		{
			NO_EVENT,
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
			_te0_main_region_active_
		};
		
		class EventInstance
		{
			public:
				explicit EventInstance(Event id) : eventId(id){}
				virtual ~EventInstance() = default;
				const Event eventId;
		};
		
		/*! Can be used by the client code to trigger a run to completion step without raising an event. */
		void triggerWithoutEvent();
		
		//! Inner class for gui interface scope.
		class Gui
		{
			public:
				Gui(CalculatorStatemachine* parent);
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
			protected:
				friend class CalculatorStatemachine;
				
				/*! Indicates event 'Button0' of interface scope 'gui' is active. */
				bool Button0_raised;
				/*! Indicates event 'Button1' of interface scope 'gui' is active. */
				bool Button1_raised;
				/*! Indicates event 'Button2' of interface scope 'gui' is active. */
				bool Button2_raised;
				/*! Indicates event 'Button3' of interface scope 'gui' is active. */
				bool Button3_raised;
				/*! Indicates event 'Button4' of interface scope 'gui' is active. */
				bool Button4_raised;
				/*! Indicates event 'Button5' of interface scope 'gui' is active. */
				bool Button5_raised;
				/*! Indicates event 'Button6' of interface scope 'gui' is active. */
				bool Button6_raised;
				/*! Indicates event 'Button7' of interface scope 'gui' is active. */
				bool Button7_raised;
				/*! Indicates event 'Button8' of interface scope 'gui' is active. */
				bool Button8_raised;
				/*! Indicates event 'Button9' of interface scope 'gui' is active. */
				bool Button9_raised;
				/*! Indicates event 'ButtonAdd' of interface scope 'gui' is active. */
				bool ButtonAdd_raised;
				/*! Indicates event 'ButtonSub' of interface scope 'gui' is active. */
				bool ButtonSub_raised;
				/*! Indicates event 'ButtonMult' of interface scope 'gui' is active. */
				bool ButtonMult_raised;
				/*! Indicates event 'ButtonDiv' of interface scope 'gui' is active. */
				bool ButtonDiv_raised;
				/*! Indicates event 'ButtonEquals' of interface scope 'gui' is active. */
				bool ButtonEquals_raised;
				/*! Indicates event 'ButtonClear' of interface scope 'gui' is active. */
				bool ButtonClear_raised;
				/*! Value of event 'ShowAccu' of interface scope 'gui'. */
				sc::integer ShowAccu_value;
				
				
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
				
				virtual void Digit(sc::integer digit) = 0;
				
				
		};
		
		/*! Set the working instance of the operation callback interface 'InternalOperationCallback'. */
		void setInternalOperationCallback(InternalOperationCallback* operationCallback);
		
		/*
		 * Functions inherited from StatemachineInterface
		 */
		void enter() override;
		
		void exit() override;
		
		/*!
		 * Checks if the state machine is active (until 2.4.1 this method was used for states).
		 * A state machine is active if it has been entered. It is inactive if it has not been entered at all or if it has been exited.
		 */
		bool isActive() const override;
		
		
		/*!
		* Checks if all active states are final. 
		* If there are no active states then the state machine is considered being inactive. In this case this method returns false.
		*/
		bool isFinal() const override;
		
		/*! 
		 * Checks if member of the state machine must be set. For example an operation callback.
		 */
		bool check() const;
		
		/*
		 * Functions inherited from TimedStatemachineInterface
		 */
		void setTimerService(sc::timer::TimerServiceInterface* timerService) override;
		
		sc::timer::TimerServiceInterface* getTimerService() override;
		
		void raiseTimeEvent(sc::eventid event) override;
		
		sc::integer getNumberOfParallelTimeEvents() override;
		
		
		
		/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
		bool isStateActive(State state) const;
		
		//! number of time events used by the state machine.
		static const sc::integer timeEventsCount = 1;
		
		//! number of time events that can be active at once.
		static const sc::integer parallelTimeEventsCount = 1;
		
		
	public slots:
		/*! Slot for the in event 'Button0' that is defined in the interface scope 'gui'. */
		void gui_Button0();
		
		/*! Slot for the in event 'Button1' that is defined in the interface scope 'gui'. */
		void gui_Button1();
		
		/*! Slot for the in event 'Button2' that is defined in the interface scope 'gui'. */
		void gui_Button2();
		
		/*! Slot for the in event 'Button3' that is defined in the interface scope 'gui'. */
		void gui_Button3();
		
		/*! Slot for the in event 'Button4' that is defined in the interface scope 'gui'. */
		void gui_Button4();
		
		/*! Slot for the in event 'Button5' that is defined in the interface scope 'gui'. */
		void gui_Button5();
		
		/*! Slot for the in event 'Button6' that is defined in the interface scope 'gui'. */
		void gui_Button6();
		
		/*! Slot for the in event 'Button7' that is defined in the interface scope 'gui'. */
		void gui_Button7();
		
		/*! Slot for the in event 'Button8' that is defined in the interface scope 'gui'. */
		void gui_Button8();
		
		/*! Slot for the in event 'Button9' that is defined in the interface scope 'gui'. */
		void gui_Button9();
		
		/*! Slot for the in event 'ButtonAdd' that is defined in the interface scope 'gui'. */
		void gui_ButtonAdd();
		
		/*! Slot for the in event 'ButtonSub' that is defined in the interface scope 'gui'. */
		void gui_ButtonSub();
		
		/*! Slot for the in event 'ButtonMult' that is defined in the interface scope 'gui'. */
		void gui_ButtonMult();
		
		/*! Slot for the in event 'ButtonDiv' that is defined in the interface scope 'gui'. */
		void gui_ButtonDiv();
		
		/*! Slot for the in event 'ButtonEquals' that is defined in the interface scope 'gui'. */
		void gui_ButtonEquals();
		
		/*! Slot for the in event 'ButtonClear' that is defined in the interface scope 'gui'. */
		void gui_ButtonClear();
		
		
	signals:
		/*! Signal representing the out event 'Exit' that is defined in the interface scope 'gui'. */
		void gui_Exit();
		
		/*! Signal representing the out event 'ShowAccu' that is defined in the interface scope 'gui'. */
		void gui_ShowAccu(sc::integer value);
		
	
	protected:
		CalculatorStatemachine(const CalculatorStatemachine &rhs);
		CalculatorStatemachine& operator=(const CalculatorStatemachine&);
		
		sc::integer operand;
		sc::integer accu;
		
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc::ushort maxOrthogonalStates = 1;
		
		sc::timer::TimerServiceInterface* timerService;
		bool timeEvents[timeEventsCount];
		
		
		State stateConfVector[maxOrthogonalStates];
		
		
		Gui ifaceGui;
		InternalOperationCallback* ifaceInternalOperationCallback;
		
		
		bool isExecuting;
		
		
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
		sc::integer react(const sc::integer transitioned_before);
		sc::integer main_region_active_react(const sc::integer transitioned_before);
		sc::integer main_region__final__react(const sc::integer transitioned_before);
		void clearInEvents();
		void microStep();
		void runCycle();
		
		
		
		
		std::deque<EventInstance*> incomingEventQueue;
		
		EventInstance* getNextEvent();
		
		void dispatchEvent(EventInstance* event);
		
		
		
	private:
		
		
		
		
};


inline CalculatorStatemachine::InternalOperationCallback::~InternalOperationCallback() {}


#endif /* CALCULATORSTATEMACHINE_H_ */
