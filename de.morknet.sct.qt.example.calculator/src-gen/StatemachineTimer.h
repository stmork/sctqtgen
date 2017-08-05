/*
 * Copyright (C) 2017 - Steffen A. Mork
 *
 * NOTE: This code is automatically generated. So do not
 * change this file! The changes will be lost!
 *
 * $Id$
 * $Author$
 */

#ifndef STATEMACHINETIMER_H
#define STATEMACHINETIMER_H

#include <QTimer>

#include "src/sc_types.h"
#include "src/StatemachineInterface.h"

/**
 * This class represents a single timer instance for the YAKINDU
 * SCT. The implementation uses the QTimer class of Qt.
 */
class StatemachineTimer :  public QTimer
{
	Q_OBJECT

	/** This is the unique identifier from YAKINDU SCT. */
	sc_eventid event_id;

public:
	/**
	 * The constructor initializes the timer identified by
	 * the unique sc_eventid.
	 *
	 * @param id The unique YAKINDU SCT timer id.
	 */
	explicit StatemachineTimer(sc_eventid id);

	/**
	 * Remove default constructor since we definitely need the timer event id!.
	 */
	StatemachineTimer() = delete;

	/**
	 * Remove copy constructor since we definitely need the timer event id!.
	 */
	StatemachineTimer(const StatemachineTimer &timer) = delete;

	/**
	 * Remove move constructor since we definitely need the timer event id!.
	 */
	StatemachineTimer(StatemachineTimer && timer) = delete;

public slots:
	/**
	 * This slot converts the occured timeout event into a signal
	 * which informs the statemachine about an timeout event
	 * including the sc_eventid.
	 */
	void in_timeout();

signals:
	/**
	 * This method signal emits the sc_eventid to the statemachine
	 * in case of a timeout event.
	 *
	 * @param id The sc_eventid which uniquely identifies this timer.
	 */
	void out_timeout(sc_eventid id);
};

#endif // STATEMACHINETIMER_H
