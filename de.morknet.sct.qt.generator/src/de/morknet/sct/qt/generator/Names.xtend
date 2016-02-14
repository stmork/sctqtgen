/*
 * Copyright (C) 2016  -  Steffen A. Mork
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.generator

import org.yakindu.base.types.Event
import org.yakindu.sct.model.sexec.ExecutionFlow
import org.yakindu.sct.model.sgraph.Scope
import org.yakindu.sct.model.stext.stext.InterfaceScope
import org.yakindu.sct.model.stext.stext.InternalScope
import com.google.inject.Inject
import org.yakindu.sct.model.sgen.GeneratorEntry

class Names
{
	@Inject extension Selector

	def headerFileName(ExecutionFlow it, GeneratorEntry entry)
	{
		className(entry) + ".h"
	}

	def implFileName(ExecutionFlow it, GeneratorEntry entry)
	{
		className(entry) + ".cpp"
	}

	def baseClassName(GeneratorEntry it)
	{
		"Abstract" + getModuleName()
	}

	def className(ExecutionFlow it, GeneratorEntry entry)
	{
		baseClassName(entry) + "Dispatcher"
	}

	def classDefineGuard(ExecutionFlow it, GeneratorEntry entry)
	{
		className(entry).toUpperCase + "_H"
	}

	def dispatch name(Scope it)
	{
		"Abstract Scope"
	}

	def dispatch name(InterfaceScope it)
	{
		name.toFirstUpper
	}

	def dispatch name(InternalScope it)
	{
		"Internal"
	}

	def dispatch instanceName(Scope it)
	{
		"// <<< " + it + ">>>"
	}

	def dispatch instanceName(InterfaceScope it)
	{
		"iface" + name.toFirstUpper()
	}
	
	def dispatch instanceName(InternalScope it)
	{
		"ifaceInternalSCI"
	}

	def dispatch ocbName(Scope it)
	{
	}

	def dispatch ocbName(InterfaceScope it)
	{
		"SCI_" + name.toFirstUpper() + "_OCB"
	}
	
	def dispatch ocbName(InternalScope it)
	{
		"InternalSCI_OCB"
	}

	def ocbNameSetter(Scope it)
	{
		"set" + ocbName()
	}

	def Emit(Event it)
	{
		name.toFirstUpper();
	}

	def asRaised(Event it)
	{
		"isRaised_" + name.toFirstLower()
	}

	def type(Event it)
	{
		if (type != null)
		{
			"sc_" + type.name
		}
	}

	def typeGetter(Event it, Scope scope)
	{
		if (it.type != null)
		{
			instanceName(scope) + ".get_" + name.toFirstLower + "_value()" 
		}
	}
}
