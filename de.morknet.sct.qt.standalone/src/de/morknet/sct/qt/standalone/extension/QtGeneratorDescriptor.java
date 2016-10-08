/*
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.standalone.extension;

import java.util.List;

import org.eclipse.swt.graphics.Image;
import org.yakindu.sct.generator.core.ISCTGenerator;
import org.yakindu.sct.generator.core.extensions.IGeneratorDescriptor;

import com.google.common.collect.Lists;

import de.morknet.sct.qt.generator.QtCodeGenerator;

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
	public Image getImage() {
		return null;
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
	public ISCTGenerator createGenerator() {
		return new QtCodeGenerator();
	}
}