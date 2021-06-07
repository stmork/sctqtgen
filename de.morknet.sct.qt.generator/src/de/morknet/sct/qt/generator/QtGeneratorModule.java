/*
 * Copyright (C) 2021  -  Steffen A. Mork
 */

package de.morknet.sct.qt.generator;

import com.google.inject.Binder;
import com.yakindu.sct.generator.core.IGeneratorModule;
import com.yakindu.sct.generator.core.ISGraphGenerator;
import com.yakindu.sct.model.sgen.GeneratorEntry;

public class QtGeneratorModule implements IGeneratorModule
{
	public void configure(GeneratorEntry entry, Binder binder)
	{
		binder.bind(ISGraphGenerator.class).to(QtGenerator.class);
	}
}
