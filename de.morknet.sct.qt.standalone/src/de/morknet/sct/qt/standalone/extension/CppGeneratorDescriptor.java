/*
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.standalone.extension;

import java.util.List;

import org.eclipse.swt.graphics.Image;
import org.yakindu.sct.generator.core.ISCTGenerator;
import org.yakindu.sct.generator.core.extensions.IGeneratorDescriptor;
import org.yakindu.sct.generator.cpp.CppCodeGenerator;

import com.google.common.collect.Lists;

public class CppGeneratorDescriptor implements IGeneratorDescriptor {
	@Override
	public String getName() {
		return "YAKINDU SCT C++ Code Generator";
	}

	@Override
	public List<String> getLibraryIDs() {
		return Lists.newArrayList(
				"org.yakindu.generator.core.features",
				"org.yakindu.generator.core.features.sctbase",
				"org.yakindu.sct.generator.feature.cpp");
	}

	@Override
	public Image getImage() {
		return null;
	}

	@Override
	public String getId() {
		return "yakindu::cpp";
	}

	@Override
	public String getElementRefType() {
		return "org.yakindu.sct.model.sgraph.Statechart";
	}

	@Override
	public String getDescription() {
		return "YAKINDU SCT C++ Code Generator";
	}

	@Override
	public String getContentType() {
		return "statechart";
	}

	@Override
	public ISCTGenerator createGenerator() {
		return new CppCodeGenerator();
	}
}