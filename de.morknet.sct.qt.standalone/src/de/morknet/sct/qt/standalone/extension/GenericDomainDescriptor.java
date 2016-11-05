/*
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.standalone.extension;

import java.nio.charset.Charset;

import org.eclipse.swt.graphics.Image;

import com.google.inject.Module;
import com.google.inject.util.Modules;

import de.morknet.sct.qt.standalone.generator.Log4jGeneratorLog;
import de.morknet.sct.qt.standalone.generator.StandaloneFileSystemAccess;
import de.morknet.sct.qt.standalone.generator.StandaloneGeneratorModule;

public class GenericDomainDescriptor implements IDomainDescriptor
{
	private String genRootDir;
	private Charset encoding;

	public GenericDomainDescriptor(String genRootDir, Charset encoding) {
		this.genRootDir = genRootDir;
		this.encoding = encoding;
	}

	@Override
	public String getDomainID() {
		return "org.yakindu.domain.default";
	}

	@Override
	public String getName() {
		return "Default";
	}

	@Override
	public String getDescription() {
		return "The default domain for YAKINDU Statechart Tools.";
	}

	@Override
	public IDomainInjectorProvider getDomainInjectorProvider() {
		return new GenericDomainInjectorProvider() {
			@Override
			public Module getGeneratorModule(String generatorId) {
				Module generatorModule = super.getGeneratorModule(generatorId);
				return Modules.override(generatorModule).with(new StandaloneGeneratorModule(genRootDir, encoding,
						StandaloneFileSystemAccess.class, Log4jGeneratorLog.class));
			}

			protected Module getResourceModule() {
				return Modules.override(getLanguageRuntimeModule()).with(getTypeSystemModule());
			};
		};
	}

	@Override
	public Image getImage() {
		return null;
	}
}