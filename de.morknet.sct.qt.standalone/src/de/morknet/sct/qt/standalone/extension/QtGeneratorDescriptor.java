/*
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.standalone.extension;

import java.net.URL;
import java.util.List;

import org.yakindu.sct.generator.core.execution.IGeneratorEntryExecutor;
import org.yakindu.sct.generator.core.extensions.IGeneratorDescriptor;
import org.yakindu.sct.model.sgen.GeneratorEntry;

import com.google.common.collect.Lists;
import com.google.inject.Module;

public class QtGeneratorDescriptor implements IGeneratorDescriptor {
	@Override
	public String getName() {
		return "MORKNet SCT Qt Code Generator";
	}

	@Override
	public List<String> getLibraryIDs() {
		return Lists.newArrayList(
				"org.yakindu.generator.core.features",
				"org.yakindu.generator.core.features.sctbase",
				"org.yakindu.sct.generator.feature.cpp",
				"de.morknet.sct.qt.generator.FeatureTypeLibrary");
	}

	@Override
	public String getId() {
		return "de::morknet::sct::qt::generator";
	}

	@Override
	public String getElementRefType() {
		return "org.yakindu.sct.model.sgraph.Statechart";
	}

	@Override
	public String getDescription() {
		return "MORKNet SCT Qt Code Generator";
	}

	@Override
	public String getContentType() {
		return "statechart";
	}

	@Override
	public IGeneratorEntryExecutor createExecutor()
	{
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Module getBindings(GeneratorEntry entry)
	{
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public URL getImagePath()
	{
		return null;
	}
}