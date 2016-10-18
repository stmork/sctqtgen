/*
 * Copyright (C) 2016  -  Steffen A. Mork
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.generator;

import org.yakindu.sct.generator.core.impl.GenericJavaBasedGenerator;
import org.yakindu.sct.model.sexec.ExecutionFlow;
import org.yakindu.sct.model.sgen.GeneratorEntry;
import org.yakindu.sct.model.sgraph.Statechart;

import com.google.inject.Inject;

public class QtCodeGenerator extends GenericJavaBasedGenerator
{
	@Inject
	private QtGenerator delegate;

	@Override
	public void runGenerator(Statechart statechart, GeneratorEntry entry)
	{
		final ExecutionFlow flow = createExecutionFlow(statechart, entry);

		if (debugFeatureHelper.isDumpSexec(entry))
		{
			dumpSexec(entry, flow);
		}
		delegate.generate(flow, entry, sctFsa.getIFileSystemAccess());
	}
}
