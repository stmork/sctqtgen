package de.morknet.sct.qt.generator;

import org.yakindu.sct.generator.core.GeneratorModule;
import org.yakindu.sct.generator.core.IExecutionFlowGenerator;
import org.yakindu.sct.model.sgen.GeneratorEntry;

import com.google.inject.Binder;

public class QtGeneratorModule implements GeneratorModule
{
	public void configure(GeneratorEntry entry, Binder binder)
	{
		binder.bind(IExecutionFlowGenerator.class).to(QtGenerator.class);
	}
}
