/* Copyright (C) 2022 - Steffen A. Mork */

#ifndef DELAYEDSTATEMACHINE_H_
#define DELAYEDSTATEMACHINE_H_

/*!
Forward declaration for the DelayedStatemachine state machine.
*/
class DelayedStatemachine;


#include <deque>
#include "../src-qt-lib/sc_types.h"
#include "../src-qt-lib/sc_statemachine.h"
#include <QObject>

/*! \file
Header of the state machine 'DelayedStatemachine'.
*/


class DelayedStatemachine : public QObject, public sc::StatemachineInterface
{
	Q_OBJECT
	
	public:
		DelayedStatemachine(QObject *parent);
		
		virtual ~DelayedStatemachine();
		
		
		
		/*! Enumeration of all states. */
		enum class State
		{
			NO_STATE,
			main_region_StateA,
			main_region_Do_Something,
			main_region_Wait_Button_1,
			main_region_Wait_Button_2
		};
		
		/*! The number of states. */
		static const sc::integer numStates = 4;
		static const sc::integer scvi_main_region_StateA = 0;
		static const sc::integer scvi_main_region_Do_Something = 0;
		static const sc::integer scvi_main_region_Wait_Button_1 = 0;
		static const sc::integer scvi_main_region_Wait_Button_2 = 0;
		
		/*! Enumeration of all events which are consumed. */
		enum class Event
		{
			NO_EVENT,
			Gui_button1,
			Gui_button2,
			Gui_complete
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
				Gui(DelayedStatemachine* parent);
				
				
				
				
				
				
				
				
				
				
				
				
			protected:
				friend class DelayedStatemachine;
				
				/*! Indicates event 'button1' of interface scope 'gui' is active. */
				bool button1_raised;
				/*! Indicates event 'button2' of interface scope 'gui' is active. */
				bool button2_raised;
				/*! Indicates event 'complete' of interface scope 'gui' is active. */
				bool complete_raised;
				/*! Value of event 'stopping' of interface scope 'gui'. */
				bool stopping_value;
				
				
			private:
				DelayedStatemachine* parent;
				
				
				
				
				
		};
		
		/*! Returns an instance of the interface class 'Gui'. */
		Gui* gui();
		
		
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
		
		
		/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
		bool isStateActive(State state) const;
		
		
		
	public slots:
		/*! Slot for the in event 'button1' that is defined in the interface scope 'gui'. */
		void gui_button1();
		
		/*! Slot for the in event 'button2' that is defined in the interface scope 'gui'. */
		void gui_button2();
		
		/*! Slot for the in event 'complete' that is defined in the interface scope 'gui'. */
		void gui_complete();
		
		
	signals:
		/*! Signal representing the out event 'stateA' that is defined in the interface scope 'gui'. */
		void gui_stateA();
		
		/*! Signal representing the out event 'doSomething' that is defined in the interface scope 'gui'. */
		void gui_doSomething();
		
		/*! Signal representing the out event 'stopping' that is defined in the interface scope 'gui'. */
		void gui_stopping(bool value);
		
		/*! Signal representing the out event 'triggerStop' that is defined in the interface scope 'gui'. */
		void gui_triggerStop();
		
		/*! Signal representing the out event 'stopped' that is defined in the interface scope 'gui'. */
		void gui_stopped();
		
	
	protected:
		
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc::ushort maxOrthogonalStates = 1;
		
		
		
		State stateConfVector[maxOrthogonalStates];
		
		
		Gui ifaceGui;
		
		
		bool isExecuting;
		
		
		// prototypes of all internal functions
		
		void enact_main_region_StateA();
		void enact_main_region_Do_Something();
		void enact_main_region_Wait_Button_1();
		void enact_main_region_Wait_Button_2();
		void exact_main_region_Do_Something();
		void exact_main_region_Wait_Button_1();
		void exact_main_region_Wait_Button_2();
		void enseq_main_region_StateA_default();
		void enseq_main_region_Do_Something_default();
		void enseq_main_region_Wait_Button_1_default();
		void enseq_main_region_Wait_Button_2_default();
		void enseq_main_region_default();
		void exseq_main_region_StateA();
		void exseq_main_region_Do_Something();
		void exseq_main_region_Wait_Button_1();
		void exseq_main_region_Wait_Button_2();
		void exseq_main_region();
		void react_main_region__entry_Default();
		sc::integer react(const sc::integer transitioned_before);
		sc::integer main_region_StateA_react(const sc::integer transitioned_before);
		sc::integer main_region_Do_Something_react(const sc::integer transitioned_before);
		sc::integer main_region_Wait_Button_1_react(const sc::integer transitioned_before);
		sc::integer main_region_Wait_Button_2_react(const sc::integer transitioned_before);
		void clearInEvents();
		void microStep();
		void runCycle();
		
		
		
		
		std::deque<EventInstance*> incomingEventQueue;
		
		EventInstance* getNextEvent();
		
		void dispatchEvent(EventInstance* event);
		
		
		
	private:
		
		
		
		
};




#endif /* DELAYEDSTATEMACHINE_H_ */
