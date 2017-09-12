/*
 * Copyright (C) 2017 - Steffen A. Mork
 *
 * NOTE: This code is automatically generated. So do not
 * change this file! The changes will be lost!
 *
 * $Id$
 * $Author$
 */

#include "src-gen/StatemachineTimer.h"

StatemachineTimer::StatemachineTimer(const sc_eventid id) : event_id(id)
{
	connect(this, &StatemachineTimer::timeout, this, &StatemachineTimer::in_timeout);
}

void StatemachineTimer::in_timeout()
{
	emit out_timeout(event_id);
}
