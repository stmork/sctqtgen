/* Copyright (C) 2022 - Steffen A. Mork */

#ifndef TIMERLESSSTATEMACHINE_H_
#define TIMERLESSSTATEMACHINE_H_

/*!
Forward declaration for the TimerlessStatemachine state machine.
*/
class TimerlessStatemachine;


#include <deque>
#include "../src-qt-lib/sc_types.h"
#include "../src-qt-lib/sc_statemachine.h"
#include <QObject>

/*! \file
Header of the state machine 'TimerlessStatemachine'.
*/


class TimerlessStatemachine : public QObject, public sc::StatemachineInterface
{
	Q_OBJECT
	
	public:
		TimerlessStatemachine(QObject *parent);
		
		virtual ~TimerlessStatemachine();
		
		
		
		/*! Enumeration of all states. */
		enum class State
		{
			NO_STATE,
			main_region_State_Off,
			main_region_State_On
		};
		
		/*! The number of states. */
		static const sc::integer numStates = 2;
		static const sc::integer scvi_main_region_State_Off = 0;
		static const sc::integer scvi_main_region_State_On = 0;
		
		/*! Enumeration of all events which are consumed. */
		enum class Event
		{
			NO_EVENT,
			Gui_clicked
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
				Gui(TimerlessStatemachine* parent);
				
				
				
				
				
				
				
			protected:
				friend class TimerlessStatemachine;
				
				/*! Indicates event 'clicked' of interface scope 'gui' is active. */
				bool clicked_raised;
				
				
			private:
				TimerlessStatemachine* parent;
				
				
				
				
				
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
		/*! Slot for the in event 'clicked' that is defined in the interface scope 'gui'. */
		void gui_clicked();
		
		
	signals:
		/*! Signal representing the out event 'on' that is defined in the interface scope 'gui'. */
		void gui_on();
		
		/*! Signal representing the out event 'off' that is defined in the interface scope 'gui'. */
		void gui_off();
		
	
	protected:
		
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc::ushort maxOrthogonalStates = 1;
		
		
		
		State stateConfVector[maxOrthogonalStates];
		
		
		Gui ifaceGui;
		
		
		bool isExecuting;
		
		
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
		sc::integer react(const sc::integer transitioned_before);
		sc::integer main_region_State_Off_react(const sc::integer transitioned_before);
		sc::integer main_region_State_On_react(const sc::integer transitioned_before);
		void clearInEvents();
		void microStep();
		void runCycle();
		
		
		
		
		std::deque<EventInstance*> incomingEventQueue;
		
		EventInstance* getNextEvent();
		
		void dispatchEvent(EventInstance* event);
		
		
		
	private:
		
		
		
		
};




#endif /* TIMERLESSSTATEMACHINE_H_ */
