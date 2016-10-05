/*
 * Copyright (C) 2016  -  Steffen A. Mork
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.generator.templates

import java.io.File
import org.yakindu.sct.model.sgen.FeatureConfiguration
import org.yakindu.sct.model.sgen.FeatureParameterValue
import org.yakindu.sct.model.sgen.GeneratorEntry
import de.morknet.sct.qt.generator.IFeatureConstants

class Features
{
	def baseClassName(GeneratorEntry it)
	{
		for (FeatureConfiguration f : features.filter[f|f.type.name == IFeatureConstants.QT_FEATURE])
		{
			val param = f.getParameterValue(IFeatureConstants.QT_BASECLASSNAME)

			if (param != null)
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
	
			if (param != null)
			{
				return param.stringValue
			}
		}
		throw new IllegalStateException("Class name not configured!");
	}

	def isCpp11(GeneratorEntry it)
	{
		for (FeatureConfiguration f : features.filter[f|f.type.name == IFeatureConstants.QT_FEATURE])
		{
			val param = f.getParameterValue(IFeatureConstants.QT_CPP11)

			if (param != null)
			{
				return param.booleanValue
			}
		}
		return IFeatureConstants.QT_CPP11_DEFAULT
	}

	def generateTimer(GeneratorEntry it)
	{
		for (FeatureConfiguration f : features.filter[f|f.type.name == IFeatureConstants.QT_FEATURE])
		{
			val param = f.getParameterValue(IFeatureConstants.QT_GENERATETIMER)

			if (param != null)
			{
				return param.booleanValue
			}
		}
		return IFeatureConstants.QT_GENERATETIMER_DEFAULT
	}

	def isThreadSafe(GeneratorEntry it)
	{
		var boolean cpp11      = IFeatureConstants.QT_CPP11_DEFAULT
		var boolean threadSafe = IFeatureConstants.QT_THREADSAFE_DEFAULT;

		for (FeatureConfiguration f : features.filter[f|f.type.name == IFeatureConstants.QT_FEATURE])
		{
			var FeatureParameterValue param

			param = f.getParameterValue(IFeatureConstants.QT_THREADSAFE)
			if (param != null)
			{
				threadSafe = param.booleanValue
			}

			param = f.getParameterValue(IFeatureConstants.QT_CPP11)
			if (param != null)
			{
				cpp11 = param.booleanValue
			}
		}
		return cpp11 && threadSafe
	}

	def getLicenseText(GeneratorEntry it)
	{
		var text = "";

		for (FeatureConfiguration f : features.filter[f|f.type.name == "LicenseHeader"])
		{
			val param = f.getParameterValue("licenseText")

			if (param != null)
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

	def getSrcGen(GeneratorEntry it)
	{
		for (FeatureConfiguration f : features.filter[f|f.type.name == "Outlet"])
		{
			val param = f.getParameterValue("targetFolder")

			if (param != null)
			{
				return param.stringValue + File.separator
			}
		}
		return ""
	}
}
