/*
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.standalone.extension;

import org.eclipse.emf.common.util.URI;
import org.yakindu.sct.generator.core.extensions.ILibraryDescriptor;
import org.yakindu.sct.generator.core.library.IDefaultFeatureValueProvider;

import com.google.inject.Injector;
	
public class LibraryDescriptor implements ILibraryDescriptor {

	private IDefaultFeatureValueProvider defaultFeatureValueProvider;
	private String id;
	private URI uri;

	public LibraryDescriptor(String id, URI uri, IDefaultFeatureValueProvider defaultFeatureValueProvider) {
		this.id = id;
		this.uri = uri;
		this.defaultFeatureValueProvider = defaultFeatureValueProvider;
	}

	@Override
	public URI getURI() {
		return uri;
	}

	@Override
	public String getLibraryId() {
		return id;
	}

	@Override
	public IDefaultFeatureValueProvider createFeatureValueProvider() {
		return defaultFeatureValueProvider;
	}

	@Override
	public IDefaultFeatureValueProvider createFeatureValueProvider(Injector arg0)
	{
		return null;
	}
}