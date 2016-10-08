/*
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.standalone;

import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.List;

import org.apache.log4j.Logger;
import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.gmf.runtime.notation.NotationPackage;
import org.eclipse.xtext.resource.IResourceServiceProvider;
import org.eclipse.xtext.scoping.IGlobalScopeProvider;
import org.eclipse.xtext.scoping.impl.ResourceSetGlobalScopeProvider;
import org.yakindu.sct.domain.extension.DomainRegistry;
import org.yakindu.sct.domain.extension.IDomainDescriptor;
import org.yakindu.sct.generator.core.GeneratorExecutor;
import org.yakindu.sct.generator.core.extensions.GeneratorExtensions;
import org.yakindu.sct.generator.core.extensions.LibraryExtensions;
import org.yakindu.sct.generator.core.features.IDefaultFeatureValueProvider;
import org.yakindu.sct.generator.core.features.impl.CoreLibraryDefaultFeatureValueProvider;
import org.yakindu.sct.generator.core.features.impl.GenericJavaLibraryDefaultValueProvider;
import org.yakindu.sct.generator.core.features.impl.SCTBaseLibaryDefaultFeatureValueProvider;
import org.yakindu.sct.generator.genmodel.SGenRuntimeModule;
import org.yakindu.sct.generator.genmodel.SGenStandaloneSetup;
import org.yakindu.sct.model.resource.SCTResourceFactory;
import org.yakindu.sct.model.sgen.GeneratorModel;
import org.yakindu.sct.model.sgen.SGenPackage;
import org.yakindu.sct.model.stext.STextRuntimeModule;
import org.yakindu.sct.model.stext.STextStandaloneSetup;

import com.google.common.collect.Lists;
import com.google.inject.Binder;
import com.google.inject.Guice;
import com.google.inject.Injector;
import com.google.inject.Module;
import com.google.inject.util.Modules;

import de.morknet.sct.qt.generator.QtGeneratorDefaultValueProvider;
import de.morknet.sct.qt.standalone.extension.CppGeneratorDescriptor;
import de.morknet.sct.qt.standalone.extension.GenericDomainDesciptor;
import de.morknet.sct.qt.standalone.extension.JavaGeneratorDescriptor;
import de.morknet.sct.qt.standalone.extension.LibraryDescriptor;
import de.morknet.sct.qt.standalone.extension.QtGeneratorDescriptor;

public class StatemachineGenerator {

	private final static Logger log = Logger.getLogger(StatemachineGenerator.class);

	private static final String SCT_FILE_EXTENSION = "sct";
	private ResourceSet resourceSet;
	private static final Charset encoding = StandardCharsets.UTF_8;

	private String absoluteCppLibrariesDir = System.getProperty("user.dir") + "/libraries";
	private String absoluteQtLibrariesDir = System.getProperty("user.home") + 
			"/workspace/sctqtgen/de.morknet.sct.qt.generator/library";
	private String absoluteWorkspaceDir = System.getProperty("user.dir") + "/..";

	public void doIt(final String [] args)
	{
		log.info("Starting build...");
		initLanguages();
		initResourceSet();

		initSCTDomain();
		initSCTGenerator();
		initSgenLibraries();

		loadSCTModels(args);

		generateAll();
	}

	protected void loadSCTModels(final String [] args)
	{
		for (String arg : args)
		{
			load(arg);
		}
	}

	protected void generateAll()
	{
		final EList<Resource> resources = resourceSet.getResources();
		final List<GeneratorModel> genModels = Lists.newArrayList();

		for (Resource resource : resources)
		{
			EObject content = resource.getContents().get(0);
			if (content instanceof GeneratorModel)
				genModels.add((GeneratorModel) content);
		}
		for (GeneratorModel generatorModel : genModels) {
			new GeneratorExecutor().executeGenerator(generatorModel);
		}
	}

	protected static void initSCTGenerator()
	{
		GeneratorExtensions.getGeneratorDescriptors().add(new JavaGeneratorDescriptor());
		GeneratorExtensions.getGeneratorDescriptors().add(new CppGeneratorDescriptor());
		GeneratorExtensions.getGeneratorDescriptors().add(new QtGeneratorDescriptor());
	}

	private static void addLibraryDescriptor(
			final String libraryId,
			final String filename,
			final IDefaultFeatureValueProvider provider)
	{
		LibraryExtensions.getLibraryDescriptors().add(
				new LibraryDescriptor(libraryId, URI.createFileURI(filename), provider));
	}

	protected void initSgenLibraries()
	{
		addLibraryDescriptor(
				"org.yakindu.generator.core.features",
				absoluteCppLibrariesDir + "/CoreFeatureTypeLibrary.xmi",
				new CoreLibraryDefaultFeatureValueProvider());
		addLibraryDescriptor(
				"org.yakindu.generator.core.features",
				absoluteCppLibrariesDir + "/CoreFeatureTypeLibrary.xmi",
				new CoreLibraryDefaultFeatureValueProvider());
		addLibraryDescriptor(
				"org.yakindu.sct.generator.feature.java",
				absoluteCppLibrariesDir + "/GenericJavaFeatureTypeLibrary.xmi",
				new GenericJavaLibraryDefaultValueProvider());
		addLibraryDescriptor(
				"org.yakindu.sct.generator.feature.cpp",
				absoluteCppLibrariesDir + "/CppFeatureTypeLibrary.xmi",
				new GenericJavaLibraryDefaultValueProvider());

		/*
			URI uri = URI.createPlatformPluginURI("/org.yakindu.sct.generator.cpp/library/FeatureTypeLibrary.xmi", false);

			System.out.println(uri);
			LibraryExtensions.getLibraryDescriptors().add(new LibraryDescriptor(
					"org.yakindu.sct.generator.feature.cpp",
					uri,
					new CDefaultFeatureValueProvider()));
		 */

		addLibraryDescriptor(
				"org.yakindu.generator.core.features.sctbase",
				absoluteCppLibrariesDir + "/SCTBaseFeatureLibrary.xmi",
				new SCTBaseLibaryDefaultFeatureValueProvider());
		addLibraryDescriptor(
				"de.morknet.sct.qt.generator.FeatureTypeLibrary",
				absoluteQtLibrariesDir + "/FeatureTypeLibrary.xmi",
				new QtGeneratorDefaultValueProvider());
	}

	protected Resource load(String string)
	{
		return resourceSet.getResource(URI.createFileURI(string), true);
	}

	protected void initSCTDomain() {
		IDomainDescriptor domainDescriptor = new GenericDomainDesciptor(absoluteWorkspaceDir, encoding);
		DomainRegistry.getDomainDescriptors().add(domainDescriptor);
	}

	protected void initResourceSet() {
		resourceSet = new ResourceSetImpl();
		resourceSet.getResourceFactoryRegistry().getExtensionToFactoryMap().put(SCT_FILE_EXTENSION,
				new SCTResourceFactory());
	}

	protected static void initLanguages()
	{
		doSgenSetup();
		doSTextSetup();
	}

	protected static void doSgenSetup()
	{
		SGenPackage.eINSTANCE.eClass();
		new SGenStandaloneSetup() {
			@Override
			public Injector createInjector() {
				return Guice.createInjector(Modules.override(new SGenRuntimeModule()).with(new Module()
				{
					@Override
					public void configure(Binder binder) {
						binder.bind(IGlobalScopeProvider.class).to(ResourceSetGlobalScopeProvider.class);
					}
				}));
			}
		}.createInjectorAndDoEMFRegistration();
	}

	protected static void doSTextSetup()
	{
		NotationPackage.eINSTANCE.eClass();

		Injector stextInjector = new STextStandaloneSetup()
		{
			@Override
			public Injector createInjector() {
				return Guice.createInjector(Modules.override(new STextRuntimeModule()).with(new Module()
				{
					@Override
					public void configure(Binder binder) {
						binder.bind(IGlobalScopeProvider.class).to(ResourceSetGlobalScopeProvider.class);
					}
				}));
			}
		}.createInjectorAndDoEMFRegistration();
		IResourceServiceProvider.Registry.INSTANCE.getExtensionToFactoryMap().put(SCT_FILE_EXTENSION,
				stextInjector.getInstance(IResourceServiceProvider.class));
	}
}
