package de.morknet.sct.qt.generator;

import org.yakindu.sct.generator.core.impl.GenericJavaBasedGenerator;
import org.yakindu.sct.model.sexec.ExecutionFlow;
import org.yakindu.sct.model.sgen.GeneratorEntry;
import org.yakindu.sct.model.sgraph.Statechart;

public class QtCodeGenerator extends GenericJavaBasedGenerator
{
	@Override
	public void runGenerator(Statechart statechart, GeneratorEntry entry)
	{
		QtGenerator delegate = getInjector(entry).getInstance(QtGenerator.class);
		ExecutionFlow flow = createExecutionFlow(statechart, entry);

		delegate.generate(flow, entry, getFileSystemAccess(entry));
	}
}
