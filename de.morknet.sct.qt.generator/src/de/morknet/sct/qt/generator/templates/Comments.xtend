/*
 * Copyright (C) 2021  -  Steffen A. Mork
 */

package de.morknet.sct.qt.generator.templates

import com.google.inject.Inject
import com.yakindu.sct.model.sgen.GeneratorEntry
import com.yakindu.sct.model.stext.stext.InterfaceScope
import com.yakindu.sct.model.stext.stext.InternalScope

class Comments
{
	@Inject extension Names
	@Inject extension Features

	def fileHeader(GeneratorEntry it)
	'''
	/*
	 * «getLicenseText()»
	 *
	 * NOTE: This code is automatically generated. So do not
	 * change this file! The changes will be lost!
	 *
	 * $«"Id"»$
	 * $«"Author"»$
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
