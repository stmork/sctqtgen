/* Copyright (C) 2022 - Steffen A. Mork */

#ifndef HISTORYSTATEMACHINE_H_
#define HISTORYSTATEMACHINE_H_

/*!
Forward declaration for the HistoryStatemachine state machine.
*/
class HistoryStatemachine;


#include <deque>
#include "../src-lib/sc_types.h"
#include "../src-lib/sc_statemachine.h"
#include <QObject>

/*! \file
Header of the state machine 'History'.
*/


class HistoryStatemachine : public QObject, public sc::StatemachineInterface
{
	Q_OBJECT
	
	public:
		HistoryStatemachine(QObject *parent);
		
		virtual ~HistoryStatemachine();
		
		
		
		/*! Enumeration of all states. */
		enum class State
		{
			NO_STATE,
			main_region_Start,
			main_region_Start_main_StateA,
			main_region_Start_main_StateA_Inner_Left_Red,
			main_region_Start_main_StateA_Inner_Left_Blue,
			main_region_Start_main_StateA_Inner_Left_Green,
			main_region_Start_main_StateB,
			main_region_Start_main_StateB_Inner_Right_Magenta,
			main_region_Start_main_StateB_Inner_Right_Cyan,
			main_region_Outside
		};
		
		/*! The number of states. */
		static const sc::integer numStates = 9;
		static const sc::integer scvi_main_region_Start = 0;
		static const sc::integer scvi_main_region_Start_main_StateA = 0;
		static const sc::integer scvi_main_region_Start_main_StateA_Inner_Left_Red = 0;
		static const sc::integer scvi_main_region_Start_main_StateA_Inner_Left_Blue = 0;
		static const sc::integer scvi_main_region_Start_main_StateA_Inner_Left_Green = 0;
		static const sc::integer scvi_main_region_Start_main_StateB = 0;
		static const sc::integer scvi_main_region_Start_main_StateB_Inner_Right_Magenta = 0;
		static const sc::integer scvi_main_region_Start_main_StateB_Inner_Right_Cyan = 0;
		static const sc::integer scvi_main_region_Outside = 0;
		
		/*! Enumeration of all events which are consumed. */
		enum class Event
		{
			NO_EVENT,
			proceed,
			toggle,
			outside
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
		
		//! Inner class for default interface scope operation callbacks.
		class OperationCallback
		{
			public:
				virtual ~OperationCallback() = 0;
				
				virtual void label(std::string text) = 0;
				
				
		};
		
		/*! Set the working instance of the operation callback interface 'OperationCallback'. */
		void setOperationCallback(OperationCallback* operationCallback);
		
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
		/*! Slot for the in event 'proceed' that is defined in the default interface scope. */
		void proceed();
		
		/*! Slot for the in event 'toggle' that is defined in the default interface scope. */
		void toggle();
		
		/*! Slot for the in event 'outside' that is defined in the default interface scope. */
		void outside();
		
		
	protected:
		
		
		std::deque<EventInstance*> incomingEventQueue;
		
		EventInstance* getNextEvent();
		
		void dispatchEvent(EventInstance* event);
		
		
		
	private:
		HistoryStatemachine(const HistoryStatemachine &rhs);
		HistoryStatemachine& operator=(const HistoryStatemachine&);
		
		
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc::ushort maxOrthogonalStates = 1;
			//! dimension of the state configuration vector for history states
		static const sc::ushort maxHistoryStates = 3;
		
		
		
		State stateConfVector[maxOrthogonalStates];
		
		State historyVector[maxHistoryStates];
		
		OperationCallback* ifaceOperationCallback;
		
		
		bool isExecuting;
		
		
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
		sc::integer react(const sc::integer transitioned_before);
		sc::integer main_region_Start_react(const sc::integer transitioned_before);
		sc::integer main_region_Start_main_StateA_react(const sc::integer transitioned_before);
		sc::integer main_region_Start_main_StateA_Inner_Left_Red_react(const sc::integer transitioned_before);
		sc::integer main_region_Start_main_StateA_Inner_Left_Blue_react(const sc::integer transitioned_before);
		sc::integer main_region_Start_main_StateA_Inner_Left_Green_react(const sc::integer transitioned_before);
		sc::integer main_region_Start_main_StateB_react(const sc::integer transitioned_before);
		sc::integer main_region_Start_main_StateB_Inner_Right_Magenta_react(const sc::integer transitioned_before);
		sc::integer main_region_Start_main_StateB_Inner_Right_Cyan_react(const sc::integer transitioned_before);
		sc::integer main_region_Outside_react(const sc::integer transitioned_before);
		void clearInEvents();
		void microStep();
		void runCycle();
		
		
		
		
		/*! Indicates event 'proceed' of default interface scope is active. */
		bool proceed_raised;
		
		/*! Indicates event 'toggle' of default interface scope is active. */
		bool toggle_raised;
		
		/*! Indicates event 'outside' of default interface scope is active. */
		bool outside_raised;
		
		
		
};


inline HistoryStatemachine::OperationCallback::~OperationCallback() {}


#endif /* HISTORYSTATEMACHINE_H_ */
