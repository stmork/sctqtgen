/*
 * Copyright (C) 2016  -  Steffen A. Mork
 * $Id: AbstractDcsHomeStationStateMachineDispatcher.h 42086 2016-02-08 15:19:28Z steffen.mork $
 * $Author: steffen.mork $
 */

package de.morknet.sct.qt.generator

import org.yakindu.sct.model.stext.stext.InterfaceScope
import com.google.inject.Inject
import org.yakindu.sct.model.sgen.GeneratorEntry
import org.yakindu.sct.model.stext.stext.InternalScope

class Comments
{
	@Inject extension Names
	@Inject extension Selector

	def fileHeader(GeneratorEntry it)
	'''
	/*
	 * «getLicenseText()»
	 *
	 * NOTE: This code is automatically generated. So do not
	 * change this file. The changes will be lost!
	 *
	 * $Id$
	 * $Author$
	 */
	'''

	def dispatch commentScope(InterfaceScope it)
	'''
		/**********************************
		 * «name(it)» scope
		 *********************************/

	'''

	def dispatch commentScope(InternalScope it)
	'''
		/**********************************
		 * «name(it)» scope
		 *********************************/

	'''
}