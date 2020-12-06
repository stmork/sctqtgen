/*
 * Copyright (C) 2019  -  Steffen A. Mork
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.generator.templates

import com.google.inject.Inject
import com.yakindu.base.types.Direction
import com.yakindu.sct.model.sexec.ExecutionFlow
import com.yakindu.sct.model.sexec.TimeEvent
import com.yakindu.sct.model.sgraph.Scope
import com.yakindu.sct.model.sgraph.Statechart
import com.yakindu.sct.model.stext.stext.InterfaceScope
import com.yakindu.sct.model.stext.stext.InternalScope
import com.yakindu.sct.model.stext.stext.OperationDefinition
import java.util.List

class Selector
{
	@Inject extension Names

	def hasInEvents(Scope it)
	{
		events.filter[e|e.direction == Direction.IN].size > 0;
	}

	def getInEvents(Scope it)
	{
		events.filter[e|e.direction == Direction.IN].sortBy[e|e.name]
	}

	def hasOutEvents(Scope it)
	{
		events.filter[e|e.direction == Direction.OUT].size > 0;
	}

	def getOutEvents(Scope it)
	{
		events.filter[e|e.direction == Direction.OUT].sortBy[e|e.name]
	}

	def getEvents(InternalScope it)
	{
		events
	}

	def private hasOperations(Scope it)
	{
		eContents.filter(OperationDefinition).size > 0
	}

	def getOcbScopes(ExecutionFlow it)
	{
		return scopes.filter[s|hasOperations(s)]
	}

	def List<InterfaceScope> getInterfaceScopes(ExecutionFlow it)
	{
		return scopes.filter(typeof(InterfaceScope)).sortBy[s|name(s)];
	}

	def Iterable<InternalScope> getInternalScopes(ExecutionFlow it)
	{
		return scopes.filter(typeof(InternalScope));
	}

	def int countInternalEvents(ExecutionFlow it)
	{
		var count = 0;

		for (InternalScope scope : internalScopes)
		{
			count += getEvents(scope).size();
		}
		return count;
	}

	def boolean isEventDriven(ExecutionFlow it)
	{
		var sc = sourceElement as Statechart

		sc.annotations.exists[a|a.type.name == "EventDriven"]
	}

	def boolean hasInternalEvents(ExecutionFlow it)
	{
		return countInternalEvents > 0
	}

	def boolean hasTimers(ExecutionFlow it)
	{
		eAllContents.filter(TimeEvent).size > 0
	}
}
