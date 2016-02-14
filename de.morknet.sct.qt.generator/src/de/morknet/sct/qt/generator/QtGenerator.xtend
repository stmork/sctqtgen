/*
 * Copyright (C) 2016  -  Steffen A. Mork
 * $Id: AbstractDcsHomeStationStateMachineDispatcher.h 42086 2016-02-08 15:19:28Z steffen.mork $
 * $Author: steffen.mork $
 */

package de.morknet.sct.qt.generator

import javax.inject.Inject
import org.eclipse.xtext.generator.IFileSystemAccess
import org.yakindu.sct.generator.core.AbstractWorkspaceGenerator
import org.yakindu.sct.generator.core.impl.IExecutionFlowGenerator
import org.yakindu.sct.model.sexec.ExecutionFlow
import org.yakindu.sct.model.sexec.ExecutionState
import org.yakindu.sct.model.sgen.FeatureConfiguration
import org.yakindu.sct.model.sgen.FeatureParameterValue
import org.yakindu.sct.model.sgen.GeneratorEntry
import org.yakindu.sct.model.sgraph.Scope
import org.yakindu.sct.model.stext.stext.OperationDefinition

class QtGenerator extends AbstractWorkspaceGenerator implements IExecutionFlowGenerator
{
	@Inject Header header
	@Inject Implementation impl
	@Inject extension Names
	@Inject extension Selector

	override generate(ExecutionFlow flow, GeneratorEntry entry, IFileSystemAccess access) {
		access.generateFile("Log.txt", info(flow, entry))
		header.generate(flow, entry, access)
		impl.generate(flow, entry, access)
	}

	def private info(ExecutionFlow flow, GeneratorEntry entry) '''
		«getLicenseText(entry)»
		«FOR FeatureConfiguration f : entry.features»
		Feature: «f.type.name»
			«FOR FeatureParameterValue v : f.parameterValues»
				«v.parameter.name» = «v.stringValue » // «v.parameter.comment»
			«ENDFOR»
		«ENDFOR»
		«FOR Scope scope : flow.scopes»
		Scope: «name(scope)»
			«FOR op : scope.eContents.filter(OperationDefinition)»
			Op:    «op.name»
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
}
