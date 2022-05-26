/* Copyright (C) 2022 - Steffen A. Mork */

#ifndef ORTHOGONALSTATEMACHINE_H_
#define ORTHOGONALSTATEMACHINE_H_

/*!
 * Forward declaration for the OrthogonalStatemachine state machine.
 */
 class OrthogonalStatemachine;


#include <deque>
#include "../src-lib/sc_types.h"
#include "../src-lib/sc_statemachine.h"
#include <QObject>

/*! \file Header of the state machine 'Orthogonal'.
*/


#ifndef SCT_EVENTS_ORTHOGONAL_H
#define SCT_EVENTS_ORTHOGONAL_H
#ifndef SC_INVALID_EVENT_VALUE
#define SC_INVALID_EVENT_VALUE 0
#endif

namespace orthogonal_events
{
typedef enum  {
	invalid_event = SC_INVALID_EVENT_VALUE,
	trigger
} OrthogonalStatemachineEventName;

class SctEvent
{
	public:
		SctEvent(OrthogonalStatemachineEventName name) : name(name){}
		virtual ~SctEvent(){}
		const OrthogonalStatemachineEventName name;
		
};
		
template <typename T>
class TypedSctEvent : public SctEvent
{
	public:
		TypedSctEvent(OrthogonalStatemachineEventName name, T value) :
			SctEvent(name),
			value(value)
			{}
		virtual ~TypedSctEvent(){}
		const T value;
};

class SctEvent__trigger : public SctEvent
{
	public:
		SctEvent__trigger(OrthogonalStatemachineEventName name) : SctEvent(name){};
};

}
#endif /* SCT_EVENTS_ORTHOGONAL_H */


/*! Define indices of states in the StateConfVector */
#define SCVI_LEFT_STATE 0
#define SCVI_RIGHT_STATE 1


class OrthogonalStatemachine : public QObject, public sc::StatemachineInterface
{
	Q_OBJECT
	
	public:
		OrthogonalStatemachine(QObject *parent);
		
		~OrthogonalStatemachine();
		
		/*! Enumeration of all states */ 
		typedef enum
		{
			Orthogonal_last_state,
			Left_State,
			Right_State
		} OrthogonalStates;
					
		static const sc_integer numStates = 2;
		
		/*! Gets the value of the variable 'left' that is defined in the default interface scope. */
		sc_integer getLeft() const;
		
		/*! Sets the value of the variable 'left' that is defined in the default interface scope. */
		void setLeft(sc_integer value);
		
		/*! Gets the value of the variable 'right' that is defined in the default interface scope. */
		sc_integer getRight() const;
		
		/*! Sets the value of the variable 'right' that is defined in the default interface scope. */
		void setRight(sc_integer value);
		
		//! Inner class for default interface scope operation callbacks.
		class OperationCallback
		{
			public:
				virtual ~OperationCallback() = 0;
				
				virtual sc_boolean isLeft() = 0;
				
				virtual sc_boolean isRight() = 0;
				
				virtual void label() = 0;
				
				
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
		sc_boolean isStateActive(OrthogonalStates state) const;
		
		
		
	public slots:
		/*! slot for the in event 'trigger' that is defined in the default interface scope. */
		void trigger();
		
		
	protected:
		
		
	private:
		OrthogonalStatemachine(const OrthogonalStatemachine &rhs);
		OrthogonalStatemachine& operator=(const OrthogonalStatemachine&);
		
		sc_integer left;
		sc_integer right;
		/*! Raises the in event 'trigger' that is defined in the default interface scope. */
		void internal_trigger();
		sc_boolean trigger_raised;
		void iface_dispatch_event(orthogonal_events::SctEvent * event);
		
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc_ushort maxOrthogonalStates = 2;
		
		
		
		OrthogonalStates stateConfVector[maxOrthogonalStates];
		
		
		OperationCallback* ifaceOperationCallback;
		
		
		sc_boolean isExecuting;
		sc_integer stateConfVectorPosition;
		
		
		// prototypes of all internal functions
		
		void enseq_Left_State_default();
		void enseq_Right_State_default();
		void enseq_Left_default();
		void enseq_Right_default();
		void exseq_Left_State();
		void exseq_Right_State();
		void exseq_Left();
		void exseq_Right();
		void react_Left__entry_Default();
		void react_Right__entry_Default();
		sc_integer react(const sc_integer transitioned_before);
		sc_integer Left_State_react(const sc_integer transitioned_before);
		sc_integer Right_State_react(const sc_integer transitioned_before);
		void clearInEvents();
		void microStep();
		void runCycle();
		
		
		orthogonal_events::SctEvent* getNextEvent();
		void dispatch_event(orthogonal_events::SctEvent * event);
		std::deque<orthogonal_events::SctEvent*> inEventQueue;
		
		
};


inline OrthogonalStatemachine::OperationCallback::~OperationCallback() {}


#endif /* ORTHOGONALSTATEMACHINE_H_ */
