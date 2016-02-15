/*
 * Copyright (C) 2016  -  Steffen A. Mork
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.generator

import com.google.inject.Inject
import org.eclipse.xtext.generator.IFileSystemAccess
import org.yakindu.sct.model.sexec.ExecutionFlow
import org.yakindu.sct.model.sgen.GeneratorEntry

class Header
{
	@Inject extension Comments
	@Inject extension Names
	@Inject extension Selector

	def generate(ExecutionFlow flow, GeneratorEntry entry, IFileSystemAccess access)
	{
		access.generateFile(headerFileName(flow, entry), signalDispatcher(flow, entry))
		access.generateFile("StatemachineTimer.h", timer(entry))
	}

	def private signalDispatcher(ExecutionFlow it, GeneratorEntry entry)
	'''
	«fileHeader(entry)»

	#ifndef «classDefineGuard(entry)»
	#define «classDefineGuard(entry)»

	#include <QObject>
	#include <QMap>
	#include "«getSrcGen(entry)»«baseClassName(entry)».h"
	#include "«getSrcGen(entry)»TimerInterface.h"
	#include "«getSrcGen(entry)»StatemachineTimer.h"
	
	#include <mutex>
	
	class «className(entry)» :
		public    QObject,
		public    «baseClassName(entry)»,
		«FOR scope : getOcbScopes()»
		protected «baseClassName(entry)»::«ocbName(scope)»,
		«ENDFOR»
		protected TimerInterface
	{
		Q_OBJECT

		QMap<sc_eventid, StatemachineTimer *> timerMap;
		std::recursive_mutex                  mutex;

	public:
		«className(entry)»();
		virtual ~«className(entry)»();

		void start();

	public slots:
		/* Triggered from QTimer */
		void timeout(sc_eventid event);
		«FOR scope : getInterfaceScopes()»
			«IF hasInEvents(scope)»

				«commentScope(scope)»
				«FOR event : getInEvents(scope)»
					virtual void «Emit(event)»(«type(event)»);
				«ENDFOR»
			«ENDIF»
		«ENDFOR»
	
	signals:
		«FOR scope : getInterfaceScopes()»
			«IF hasOutEvents(scope)»
				«commentScope(scope)»
				«FOR event : getOutEvents(scope)»
					void «Emit(event)»(«type(event)»);
				«ENDFOR»

			«ENDIF»
		«ENDFOR»

	protected:
		virtual void initializeValues() = 0;
		virtual void runCycle();
		virtual void react();
		virtual void cancel();
	
		void setTimer(TimedStatemachineInterface* statemachine, sc_eventid event, sc_integer time, sc_boolean isPeriodic);
		void unsetTimer(TimedStatemachineInterface* statemachine, sc_eventid event);
	};
	
	#endif // «classDefineGuard(entry)»
	'''

	def private timer(GeneratorEntry it)
	'''
	«fileHeader()»

	#ifndef STATEMACHINETIMER_H
	#define STATEMACHINETIMER_H
	
	#include <QMap>
	#include <QTimer>
	
	#include "«getSrcGen()»sc_types.h"
	#include "«getSrcGen()»StatemachineInterface.h"

	class StatemachineTimer :  public QTimer
	{
		Q_OBJECT
	
		sc_eventid event_id;
	
	public:
		StatemachineTimer(sc_eventid id);
	
	public slots:
		void in_timeout();
	
	signals:
		void out_timeout(sc_eventid evid);
	};
	
	#endif // STATEMACHINETIMER_H
	'''
}
