/*
 * Copyright (C) 2017  -  Steffen A. Mork
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.generator.templates

import de.morknet.sct.qt.generator.IFeatureConstants
import java.io.File
import org.yakindu.sct.model.sgen.FeatureConfiguration
import org.yakindu.sct.model.sgen.GeneratorEntry

class Features
{
	private static boolean debug      = IFeatureConstants.QT_DEBUG_DEFAULT;
	private static boolean cpp11      = IFeatureConstants.QT_CPP11_DEFAULT;
	private static boolean genTimer   = IFeatureConstants.QT_GENERATETIMER_DEFAULT;
	private static boolean threadSafe = IFeatureConstants.QT_THREADSAFE_DEFAULT;
	private static boolean camelCase  = IFeatureConstants.QT_CAMEL_CALSE_DEFAULT;

	def initFeatures(GeneratorEntry it)
	{
		for (FeatureConfiguration f : features.filter[f|f.type.name == IFeatureConstants.QT_FEATURE])
		{
			var param = f.getParameterValue(IFeatureConstants.QT_DEBUG)
			if (param !== null)
			{
				debug = param.booleanValue
			}

			param = f.getParameterValue(IFeatureConstants.QT_CPP11)
			if (param !== null)
			{
				cpp11 = param.booleanValue
			}

			param = f.getParameterValue(IFeatureConstants.QT_GENERATETIMER)
			if (param !== null)
			{
				genTimer = param.booleanValue
			}

			param = f.getParameterValue(IFeatureConstants.QT_THREADSAFE)
			if (param !== null)
			{
				threadSafe = param.booleanValue
			}

			param = f.getParameterValue(IFeatureConstants.QT_CAMEL_CALSE)
			if (param !== null)
			{
				threadSafe = param.booleanValue
			}
		}
	}

	def baseClassName(GeneratorEntry it)
	{
		for (FeatureConfiguration f : features.filter[f|f.type.name == IFeatureConstants.QT_FEATURE])
		{
			val param = f.getParameterValue(IFeatureConstants.QT_BASECLASSNAME)

			if (param !== null)
			{
				return param.stringValue
			}
		}
		throw new IllegalStateException("Base class name not configured!");
	}

	def className(GeneratorEntry it)
	{
		for (FeatureConfiguration f : features.filter[f|f.type.name == IFeatureConstants.QT_FEATURE])
		{
			val param = f.getParameterValue(IFeatureConstants.QT_CLASSNAME)
	
			if (param !== null)
			{
				return param.stringValue
			}
		}
		throw new IllegalStateException("Class name not configured!");
	}

	def isDebug()
	{
		return debug
	}

	def isCpp11()
	{
		return cpp11
	}

	def generateTimer()
	{
		return genTimer
	}

	def isThreadSafe()
	{
		return cpp11 && threadSafe
	}

	def isCamelCase()
	{
		return camelCase
	}

	def getLicenseText(GeneratorEntry it)
	{
		var text = "";

		for (FeatureConfiguration f : features.filter[f|f.type.name == "LicenseHeader"])
		{
			val param = f.getParameterValue("licenseText")

			if (param !== null)
			{
				text += f.getParameterValue("licenseText").stringValue
				text += "\n"
			}
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

	def getSrc(GeneratorEntry it)
	{
		for (FeatureConfiguration f : features.filter[f|f.type.name == "Outlet"])
		{
			val param = f.getParameterValue("libraryTargetFolder")

			if (param !== null)
			{
				return param.stringValue + File.separator
			}
		}
		return ""
	}

	def getSrcGen(GeneratorEntry it)
	{
		for (FeatureConfiguration f : features.filter[f|f.type.name == "Outlet"])
		{
			val param = f.getParameterValue("targetFolder")

			if (param !== null)
			{
				return param.stringValue + File.separator
			}
		}
		return ""
	}
}
