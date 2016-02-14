/*
 * Copyright (C) 2016  -  Steffen A. Mork
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.generator

import com.google.inject.Inject
import java.io.File
import java.util.List
import org.yakindu.base.types.Direction
import org.yakindu.sct.model.sexec.ExecutionFlow
import org.yakindu.sct.model.sgen.FeatureConfiguration
import org.yakindu.sct.model.sgen.GeneratorEntry
import org.yakindu.sct.model.sgraph.Scope
import org.yakindu.sct.model.stext.stext.InterfaceScope
import org.yakindu.sct.model.stext.stext.InternalScope
import org.yakindu.sct.model.stext.stext.OperationDefinition

class Selector
{
	@Inject extension Names

	def getOutEvents(Scope it)
	{
		events.filter[e|e.direction == Direction.OUT].sortBy[e|e.name]
	}

	def getEvents(InternalScope it)
	{
		events
	}

	def getLicenseText(GeneratorEntry it)
	{
		var text = "";

		for (FeatureConfiguration f : features.filter[f|f.type.name == "LicenseHeader"])
		{
			text += f.getParameterValue("licenseText").stringValue
			text += "\n"
		}
		if (text.length <= 0)
		{
			return "Copyright Steffen A. Mork"
		}
		else
		{
			return text
		}
	}

	def baseClassName(GeneratorEntry it)
	{
		for (FeatureConfiguration f : features.filter[f|f.type.name == "QtGenerator"])
		{
			return f.getParameterValue("baseClassName").stringValue
		}
		return null
	}

	def className(GeneratorEntry it)
	{
		for (FeatureConfiguration f : features.filter[f|f.type.name == "QtGenerator"])
		{
			return f.getParameterValue("className").stringValue
		}
		return null
	}

	def getSrcGen(GeneratorEntry it)
	{
		for (FeatureConfiguration f : features.filter[f|f.type.name == "Outlet"])
		{
			return f.getParameterValue("targetFolder").stringValue + File.separator
		}
		return ""
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
}
