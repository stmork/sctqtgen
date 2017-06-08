/*
 * Copyright Steffen A. Mork
 *
 * NOTE: This code is automatically generated. So do not
 * change this file! The changes will be lost!
 *
 * $Id$
 * $Author$
 */

#ifndef ABSTRACTSTATEMACHINEDISPATCHER_H
#define ABSTRACTSTATEMACHINEDISPATCHER_H

#include <QObject>
#include "src-gen/AbstractStateMachine.h"

/**
 * This class provides a link layer which wires the in and out events
 * to the signal and slots of a Qt application.
 */
class AbstractStateMachineDispatcher :
	public    QObject,
	public    AbstractStateMachine
{
	Q_OBJECT

public:
	/**
	 * The constructor initializes the Qt event layer and the YAKINDU
	 * statemachine. This layer implements all OCBs and signal/slot
	 * management.
	 */
	AbstractStateMachineDispatcher();

	/**
	 * The destructor frees all resources allocated from this
	 * Qt/SCT layer.
	 */
	virtual ~AbstractStateMachineDispatcher();

	/**
	 * This method initializes the statemachine an runs
	 * the first cycle. The virtual method initializeValues()
	 * is for initializing some statemachine values. After
	 * entering the statemachine the method react() is run
	 * to evaluate possible raised out events.
	 */
	void start();

	/**
	 * This method stopps the statemachine an runs
	 * the last cycle. After leaving the statemachine
	 * the method react() is run to evaluate possible
	 * raised out events.
	 */
	void stop();

public slots:
	/**********************************
	 * Gui scope
	 *********************************/
	
	/**
	 * This callback acts as a slot for
	 * the in event clicked.
	 */
	virtual void Clicked( );


signals:
	/**********************************
	 * Gui scope
	 *********************************/
	
	/**
	 * This out event emits signal off.
	 */
	void Off( );

	/**
	 * This out event emits signal on.
	 */
	void On( );


protected:
	/**
	 * This method is intended to initialize possible ressources of
	 * this Qt/SCT layer.
	 */
	virtual void initializeValues() = 0;

	/**
	 * This runs a single statemachine cycle. See
	 * documentation of YAKINDU statechart tools for
	 * more information. After running the cycle the
	 * method react() is run to evaluate possible
	 * raised out events.
	 */
	virtual void runCycle() override;

	/**
	 * This method converts raised out events into
	 * Qt signals. Events from internal scope are
	 * not converted into Qt signals. Instead a 
	 * further runCycle() is done.
	 */
	virtual void react();
};

#endif // ABSTRACTSTATEMACHINEDISPATCHER_H
