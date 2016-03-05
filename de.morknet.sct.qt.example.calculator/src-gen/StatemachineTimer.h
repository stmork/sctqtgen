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

class StatemachineTimer :  public QTimer
{
	Q_OBJECT

	sc_eventid event_id;

public:
	StatemachineTimer(sc_eventid id);

public slots:
	void in_timeout();

signals:
	void out_timeout(sc_eventid evid);
};

#endif // STATEMACHINETIMER_H
