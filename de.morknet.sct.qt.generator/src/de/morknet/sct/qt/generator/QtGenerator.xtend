/*
 * Copyright (C) 2020  -  Steffen A. Mork
 */

package de.morknet.sct.qt.generator

import com.google.inject.Inject
import de.morknet.sct.qt.generator.templates.Features
import de.morknet.sct.qt.generator.templates.Header
import de.morknet.sct.qt.generator.templates.Implementation
import de.morknet.sct.qt.generator.templates.Names
import de.morknet.sct.qt.generator.templates.Selector
import org.eclipse.emf.ecore.EObject
import org.eclipse.xtext.generator.IFileSystemAccess
import org.yakindu.base.types.Annotation
import org.yakindu.sct.generator.core.IExecutionFlowGenerator
import org.yakindu.sct.model.sexec.ExecutionFlow
import org.yakindu.sct.model.sexec.ExecutionState
import org.yakindu.sct.model.sexec.TimeEvent
import org.yakindu.sct.model.sgen.FeatureConfiguration
import org.yakindu.sct.model.sgen.FeatureParameterValue
import org.yakindu.sct.model.sgen.GeneratorEntry
import org.yakindu.sct.model.sgraph.Scope
import org.yakindu.sct.model.sgraph.Statechart
import org.yakindu.sct.model.stext.stext.OperationDefinition

class QtGenerator implements IExecutionFlowGenerator
{
	@Inject Header header
	@Inject Implementation impl
	@Inject Selector selector
	@Inject extension Names
	@Inject extension Features

	override generate(ExecutionFlow flow, GeneratorEntry entry, IFileSystemAccess access)
	{
		initFeatures(entry)

		var sc = flow.sourceElement as Statechart

		if (isDebug())
		{
			access.generateFile("Log.txt", info(flow, entry))
			access.generateFile("Elements.txt", elements(sc, entry))
		}
		header.generate(flow, entry, access)
		impl.generate(flow, entry, access)
	}

	def private info(ExecutionFlow flow, GeneratorEntry entry) '''
		«getLicenseText(entry)»
		Has internal events: «selector.hasInternalEvents(flow)»
		Has timers:          «selector.hasTimers(flow)»

		«FOR FeatureConfiguration f : entry.features»
		Feature: «f.type.name»
			«FOR FeatureParameterValue v : f.parameterValues»
				«v.parameter.name» = «v.stringValue » // «v.parameter.comment»
			«ENDFOR»
		«ENDFOR»
		Is event driven: «selector.isEventDriven(flow)»
		«flow.annotations»
		«FOR Annotation anno : flow.annotations»
		Annotation: «anno.toString»
		«ENDFOR»
		«FOR Scope scope : flow.scopes»
		Scope: «name(scope)»
			Has in events:  «selector.hasInEvents(scope)»
			Has out events: «selector.hasOutEvents(scope)»
			«FOR op : scope.eContents.filter(OperationDefinition)»
			Op:    «op.name» : «op.type»
				«FOR param : op.parameters»
					«param.name» : «param.type»
				«ENDFOR»
			«ENDFOR»
			«FOR event : scope.events»
			Event: «event.name» «event.direction» «event.type»
			«ENDFOR»
		«ENDFOR»
		The name of the Statemachine is '«flow.name»'

		The Statemachine has the following states:

		«FOR ExecutionState state : flow.states»
		State: «state.name.replaceFirst(flow.name+'\\.','')»
		«ENDFOR»
	'''

	def private elements(Statechart flow, GeneratorEntry entry) '''
		Statechart:
		«FOR EObject o : flow.eAllContents.toList»
		«o»
		«ENDFOR»

		Timers:
		«FOR TimeEvent t : flow.eAllContents.filter(TimeEvent).toList»
		«t»
		«ENDFOR»

		Generator:
		«FOR EObject o : entry.eAllContents.toList»
		«o»
		«ENDFOR»
	'''
}
