package de.morknet.sct.qt.generator;

import com.google.inject.Binder;
import com.yakindu.sct.generator.core.IExecutionFlowGenerator;
import com.yakindu.sct.generator.core.IGeneratorModule;
import com.yakindu.sct.model.sgen.GeneratorEntry;

public class QtGeneratorModule implements IGeneratorModule
{
	public void configure(GeneratorEntry entry, Binder binder)
	{
		binder.bind(IExecutionFlowGenerator.class).to(QtGenerator.class);
	}
}
