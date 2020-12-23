/*
 * Copyright (C) 2017  -  Steffen A. Mork
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.generator;

import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Status;
import org.eclipse.emf.ecore.EObject;

import com.yakindu.sct.generator.core.library.AbstractDefaultFeatureValueProvider;
import com.yakindu.sct.model.sgen.FeatureParameterValue;
import com.yakindu.sct.model.sgen.FeatureType;
import com.yakindu.sct.model.sgen.FeatureTypeLibrary;
	
/**
 * Default value provider for Qt-Generator for SCT feature library
 */
public class QtGeneratorDefaultValueProvider extends AbstractDefaultFeatureValueProvider
{
	public boolean isProviderFor(FeatureTypeLibrary library)
	{
		return library.getName().equals(IFeatureConstants.LIBRARY_NAME);
	}

	public void setDefaultValue(
			FeatureType type,
			FeatureParameterValue parameterValue,
			EObject context)
	{
		String parameterName = parameterValue.getParameter().getName();

		if (IFeatureConstants.QT_BASECLASSNAME.equals(parameterName))
		{
			parameterValue.setValue(IFeatureConstants.QT_BASECLASSNAME_DEFAULT);
		}
		if (IFeatureConstants.QT_CLASSNAME.equals(parameterName))
		{
			parameterValue.setValue(IFeatureConstants.QT_CLASSNAME_DEFAULT);
		}
		if (IFeatureConstants.QT_CPP11.equals(parameterName))
		{
			parameterValue.setValue(IFeatureConstants.QT_CPP11_DEFAULT);
		}
		if (IFeatureConstants.QT_GENERATETIMER.equals(parameterName))
		{
			parameterValue.setValue(IFeatureConstants.QT_GENERATETIMER_DEFAULT);
		}
		if (IFeatureConstants.QT_THREADSAFE.equals(parameterName))
		{
			parameterValue.setValue(IFeatureConstants.QT_THREADSAFE_DEFAULT);
		}
		if (IFeatureConstants.QT_DEBUG.equals(parameterName))
		{
			parameterValue.setValue(IFeatureConstants.QT_DEBUG_DEFAULT);
		}
		if (IFeatureConstants.QT_CAMEL_CASE.equals(parameterName))
		{
			parameterValue.setValue(IFeatureConstants.QT_CAMEL_CASE_DEFAULT);
		}
		if (IFeatureConstants.QT_BASE_CLASS.equals(parameterName))
		{
			parameterValue.setValue(IFeatureConstants.QT_BASE_CLASS_DEFAULT);
		}
	}

	public IStatus validateParameterValue(FeatureParameterValue parameterValue)
	{
		return Status.OK_STATUS;
	}
}
