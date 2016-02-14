/*
 * Copyright (C) 2016  -  Steffen A. Mork
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.generator;

import static de.morknet.sct.qt.generator.IFeatureConstants.LIBRARY_NAME;
import static de.morknet.sct.qt.generator.IFeatureConstants.MY_PARAMETER;

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
			FeatureParameterValue parameterValue, EObject context)
	{
		String parameterName = parameterValue.getParameter().getName();
		if (MY_PARAMETER.equals(parameterName)) {
			parameterValue.setValue("default value");
		}
	}

	public IStatus validateParameterValue(FeatureParameterValue parameterValue)
	{
		String parameterName = parameterValue.getParameter().getName();
		// TODO implement validation
		// return error("Illegal parameter value");
		return Status.OK_STATUS;
	}
}
