/* Copyright (C) 2022 - Steffen A. Mork */

#ifndef DELAYEDSTATEMACHINE_H_
#define DELAYEDSTATEMACHINE_H_

/*!
 * Forward declaration for the DelayedStatemachine state machine.
 */
 class DelayedStatemachine;


#include <deque>
#include "../src-qt-lib/sc_types.h"
#include "../src-qt-lib/sc_rxcpp.h"
#include "../src-qt-lib/sc_statemachine.h"
#include <QObject>

/*! \file Header of the state machine 'DelayedExit'.
*/


#ifndef SCT_EVENTS_DELAYEDEXIT_H
#define SCT_EVENTS_DELAYEDEXIT_H
#ifndef SC_INVALID_EVENT_VALUE
#define SC_INVALID_EVENT_VALUE 0
#endif

namespace delayedexit_events
{
typedef enum  {
	invalid_event = SC_INVALID_EVENT_VALUE,
	Gui_button1,
	Gui_button2,
	Gui_complete
} DelayedStatemachineEventName;

class SctEvent
{
	public:
		SctEvent(DelayedStatemachineEventName name) : name(name){}
		virtual ~SctEvent(){}
		const DelayedStatemachineEventName name;
		
};
		
template <typename T>
class TypedSctEvent : public SctEvent
{
	public:
		TypedSctEvent(DelayedStatemachineEventName name, T value) :
			SctEvent(name),
			value(value)
			{}
		virtual ~TypedSctEvent(){}
		const T value;
};

class SctEvent_Gui_button1 : public SctEvent
{
	public:
		SctEvent_Gui_button1(DelayedStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_button2 : public SctEvent
{
	public:
		SctEvent_Gui_button2(DelayedStatemachineEventName name) : SctEvent(name){};
};
class SctEvent_Gui_complete : public SctEvent
{
	public:
		SctEvent_Gui_complete(DelayedStatemachineEventName name) : SctEvent(name){};
};

}
#endif /* SCT_EVENTS_DELAYEDEXIT_H */


/*! Define indices of states in the StateConfVector */
#define SCVI_MAIN_REGION_STATEA 0
#define SCVI_MAIN_REGION_DO_SOMETHING 0
#define SCVI_MAIN_REGION_WAIT_BUTTON_1 0
#define SCVI_MAIN_REGION_WAIT_BUTTON_2 0


class DelayedStatemachine : public QObject, public sc::StatemachineInterface
{
	Q_OBJECT
	
	public:
		DelayedStatemachine(QObject *parent);
		
		~DelayedStatemachine();
		
		/*! Enumeration of all states */ 
		typedef enum
		{
			Delayedexit_last_state,
			main_region_StateA,
			main_region_Do_Something,
			main_region_Wait_Button_1,
			main_region_Wait_Button_2
		} DelayedexitStates;
					
		static const sc_integer numStates = 4;
		
		//! Inner class for gui interface scope.
		class Gui
		{
			public:
				Gui(DelayedStatemachine* parent);
				
				
				
				
				
				
				
				
				
				
				
			protected:
				friend class DelayedStatemachine;
				
				/*! Raises the in event 'button1' that is defined in the interface scope 'gui'. */
				void internal_gui_button1();
				sc_boolean button1_raised;
				/*! Raises the in event 'button2' that is defined in the interface scope 'gui'. */
				void internal_gui_button2();
				sc_boolean button2_raised;
				/*! Raises the in event 'complete' that is defined in the interface scope 'gui'. */
				void internal_gui_complete();
				sc_boolean complete_raised;
				void dispatch_event(delayedexit_events::SctEvent * event);
				
				
			private:
				DelayedStatemachine* parent;
				
				
				
				
				
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
		sc_boolean isStateActive(DelayedexitStates state) const;
		
		
		
	public slots:
		/*! slot for the in event 'button1' that is defined in the interface scope 'gui'. */
		void gui_button1();
		
		/*! slot for the in event 'button2' that is defined in the interface scope 'gui'. */
		void gui_button2();
		
		/*! slot for the in event 'complete' that is defined in the interface scope 'gui'. */
		void gui_complete();
		
		
	signals:
		/*! Signal representing the out event 'stateA' that is defined in the interface scope 'gui'. */
		void gui_stateA();
		
		/*! Signal representing the out event 'doSomething' that is defined in the interface scope 'gui'. */
		void gui_doSomething();
		
		/*! Signal representing the out event 'stopping' that is defined in the interface scope 'gui'. */
		void gui_stopping(sc_boolean value);
		
		/*! Signal representing the out event 'triggerStop' that is defined in the interface scope 'gui'. */
		void gui_triggerStop();
		
		/*! Signal representing the out event 'stopped' that is defined in the interface scope 'gui'. */
		void gui_stopped();
		
	
	protected:
		
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc_ushort maxOrthogonalStates = 1;
		
		
		
		DelayedexitStates stateConfVector[maxOrthogonalStates];
		
		
		Gui ifaceGui;
		
		
		sc_boolean isExecuting;
		
		
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
		sc_integer react(const sc_integer transitioned_before);
		sc_integer main_region_StateA_react(const sc_integer transitioned_before);
		sc_integer main_region_Do_Something_react(const sc_integer transitioned_before);
		sc_integer main_region_Wait_Button_1_react(const sc_integer transitioned_before);
		sc_integer main_region_Wait_Button_2_react(const sc_integer transitioned_before);
		void clearInEvents();
		void microStep();
		void runCycle();
		
		
		
		
	private:
		delayedexit_events::SctEvent* getNextEvent();
		void dispatch_event(delayedexit_events::SctEvent * event);
		std::deque<delayedexit_events::SctEvent*> inEventQueue;
		
		
};




#endif /* DELAYEDSTATEMACHINE_H_ */
