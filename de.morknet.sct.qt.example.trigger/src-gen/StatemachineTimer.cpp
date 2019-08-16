/*
 * Copyright (C) 2019 - Steffen A. Mork
 *
 * NOTE: This code is automatically generated. So do not
 * change this file! The changes will be lost!
 *
 * $Id$
 * $Author$
 */

#include "src-gen/StatemachineTimer.h"

StatemachineTimer::StatemachineTimer(
	QObject * parent,
	const sc_eventid id) : QTimer(parent), event_id(id)
{
	connect(this, &StatemachineTimer::timeout, this, &StatemachineTimer::in_timeout);
}

void StatemachineTimer::in_timeout()
{
	emit out_timeout(event_id);
}
