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
	@Inject extension Features
	@Inject extension Selector

	def generate(ExecutionFlow flow, GeneratorEntry entry, IFileSystemAccess access)
	{
		access.generateFile(headerFileName(flow, entry), signalDispatcher(flow, entry))
		if (generateTimer(entry))
		{
			access.generateFile("StatemachineTimer.h", timer(entry))
		}
	}

	def private signalDispatcher(ExecutionFlow it, GeneratorEntry entry)
	'''
	«fileHeader(entry)»

	#ifndef «classDefineGuard(entry)»
	#define «classDefineGuard(entry)»

	#include <QObject>
	#include <QHash>
	#include "«getSrcGen(entry)»«baseClassName(entry)».h"
	#include "«getSrcGen(entry)»TimerInterface.h"
	#include "«getSrcGen(entry)»StatemachineTimer.h"
	«IF isThreadSafe(entry)»
	
	#include <mutex>
	
	typedef std::recursive_mutex      sc_mutex;
	typedef std::lock_guard<sc_mutex> sc_lock;
	«ENDIF»
	
	/**
	 * This class provides a link layer which wires the in and out events
	 * to the signal and slots of a Qt application.
	 */
	class «className(entry)» :
		public    QObject,
		public    «baseClassName(entry)»,
		«FOR scope : getOcbScopes()»
		protected «baseClassName(entry)»::«ocbName(scope)»,
		«ENDFOR»
		protected TimerInterface
	{
		Q_OBJECT

		QHash<sc_eventid, StatemachineTimer *> timerMap;

	«IF isThreadSafe(entry)»
	protected:
		/** This mutex is used to provide thread safety. */
		sc_mutex                               mutex;

	«ENDIF»
	public:
		/**
		 * The constructor initializes the Qt event layer and the YAKINDU
		 * statemachine. This layer implements all OCBs and signal/slot
		 * management.
		 */
		«className(entry)»();

		/**
		 * The destructor frees all resources allocated from this
		 * Qt/SCT layer.
		 */
		virtual ~«className(entry)»();

		/**
		 * This method initializes the statemachine an runs
		 * the first cycle. The virtual method initializeValues()
		 * is for initializing some statemachine values. After
		 * entering the statemachine the method react() is run
		 * to evaluate possible raised out events.
		 */
		void start();

		/**
		 * This method stopps the statemachine an runs
		 * the last cycle. After leaving the statemachine
		 * the method react() is run to evaluate possible
		 * raised out events.
		 */
		void stop();

	public slots:
		/* Triggered from QTimer */
		void timeout(sc_eventid event);
		«FOR scope : getInterfaceScopes()»
			«IF hasInEvents(scope)»
				«commentScope(scope)»
				«FOR event : getInEvents(scope)»

					/**
					 * This callback acts as a slot for
					 * the in event «event.name».
					 */
					virtual void «Emit(event)»(«type(event)»);
				«ENDFOR»
			«ENDIF»
		«ENDFOR»
	
	signals:
		«FOR scope : getInterfaceScopes()»
			«IF hasOutEvents(scope)»
				«commentScope(scope)»
				«FOR event : getOutEvents(scope)»

					/**
					 * This out event emits signal «event.name».
					 */
					void «Emit(event)»(«type(event)»);
				«ENDFOR»
			«ENDIF»
		«ENDFOR»

	protected:
		/**
		 * This method is intended to initialize possible ressources of
		 * this Qt/SCT layer.
		 */
		virtual void initializeValues() = 0;

		/**
		 * This runs a single statemachine cycle. See
		 * documentation of YAKINDU statechart tools for
		 * more information. After running the cycle the
		 * method react() is run to evaluate possible
		 * raised out events.
		 */
		virtual void runCycle() Q_DECL_OVERRIDE;
	
		/**
		 * This method converts raised out events into
		 * Qt signals. Events from internal scope are
		 * not converted into Qt signals. Instead a 
		 * further runCycle() is done.
		 */
		virtual void react();
	
		virtual void setTimer(TimedStatemachineInterface* statemachine,
			sc_eventid event, sc_integer time, sc_boolean isPeriodic) Q_DECL_OVERRIDE;
		virtual void unsetTimer(TimedStatemachineInterface* statemachine,
			sc_eventid event) Q_DECL_OVERRIDE;
		virtual void cancel() Q_DECL_OVERRIDE;
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

	/**
	 * This class represents a single timer instance for the YAKINDU
	 * SCT. The implementation uses the QTimer class of Qt.
	 */
	class StatemachineTimer :  public QTimer
	{
		Q_OBJECT
	
		/** This is the unique identifier from YAKINDU SCT. */
		sc_eventid event_id;
	
	public:
		/**
		 * The constructor initializes the timer identified by
		 * the unique sc_eventid.
		 *
		 * param id The unique YAKINDU SCT timer id.
		 */
		StatemachineTimer(sc_eventid id);
	
	public slots:
		/**
		 * This slot converts the occured timeout event into a signal
		 * which informs the statemachine about an timeout event
		 * including the sc_eventid.
		 */
		void in_timeout();
	
	signals:
		/**
		 * This method signal sends the sc_eventId to the statemachine
		 * in case of a timeout event.
		 *
		 * @param evid The sc_eventid which uniquely identifies this timer.
		 */
		void out_timeout(sc_eventid evid);
	};
	
	#endif // STATEMACHINETIMER_H
	'''
}
