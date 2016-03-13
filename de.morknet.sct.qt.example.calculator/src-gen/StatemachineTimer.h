/*
 * Copyright (C) 2016 - Steffen A. Mork
 *
 * NOTE: This code is automatically generated. So do not
 * change this file! The changes will be lost!
 *
 * $Id$
 * $Author$
 */

#ifndef STATEMACHINETIMER_H
#define STATEMACHINETIMER_H

#include <QMap>
#include <QTimer>

#include "src-gen/sc_types.h"
#include "src-gen/StatemachineInterface.h"

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
	 * param id The unique YAKINDU SCT timer id.
	 */
	StatemachineTimer(sc_eventid id);

public slots:
	/**
	 * This slot converts the occured timeout event into a signal
	 * which informs the statemachine about an timeout event
	 * including the sc_eventid.
	 */
	void in_timeout();

signals:
	/**
	 * This method signal sends the sc_eventId to the statemachine
	 * in case of a timeout event.
	 *
	 * @param evid The sc_eventid which uniquely identifies this timer.
	 */
	void out_timeout(sc_eventid evid);
};

#endif // STATEMACHINETIMER_H
