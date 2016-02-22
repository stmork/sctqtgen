/*
 * Copyright (C) 2016  -  Steffen A. Mork
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.generator;

import static de.morknet.sct.qt.generator.IFeatureConstants.LIBRARY_NAME;
import static de.morknet.sct.qt.generator.IFeatureConstants.QT_BASECLASSNAME;
import static de.morknet.sct.qt.generator.IFeatureConstants.QT_CLASSNAME;
import static de.morknet.sct.qt.generator.IFeatureConstants.QT_CPP11;
import static de.morknet.sct.qt.generator.IFeatureConstants.QT_GENERATETIMER;

import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Status;
import org.eclipse.emf.ecore.EObject;
import org.yakindu.sct.generator.core.features.AbstractDefaultFeatureValueProvider;
import org.yakindu.sct.model.sgen.FeatureParameterValue;
import org.yakindu.sct.model.sgen.FeatureTypeLibrary;
	
/**
 * Default value provider for Qt-Generator for SCT feature library
 */
public class QtGeneratorDefaultValueProvider extends AbstractDefaultFeatureValueProvider
{
	public boolean isProviderFor(FeatureTypeLibrary library)
	{
		return library.getName().equals(LIBRARY_NAME);
	}

	@Override
	protected void setDefaultValue(
			FeatureParameterValue parameterValue,
			EObject context)
	{
		String parameterName = parameterValue.getParameter().getName();

		if (QT_BASECLASSNAME.equals(parameterName))
		{
			parameterValue.setValue("AbstractStateMachine");
		}
		if (QT_CLASSNAME.equals(parameterName))
		{
			parameterValue.setValue("AbstractStateMachineDispatcher");
		}
		if (QT_CPP11.equals(parameterName))
		{
			parameterValue.setValue("true");
		}
		if (QT_GENERATETIMER.equals(parameterName))
		{
			parameterValue.setValue("true");
		}
	}

	public IStatus validateParameterValue(FeatureParameterValue parameterValue)
	{
		return Status.OK_STATUS;
	}
}
