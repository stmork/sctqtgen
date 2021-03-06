/*
 * Copyright (C) 2020  -  Steffen A. Mork
 */

package de.morknet.sct.qt.generator.templates

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
		if (generateTimer())
		{
			access.generateFile("StatemachineTimer.h", timer(entry))
		}
	}

	def private signalDispatcher(ExecutionFlow it, GeneratorEntry entry)
	'''
	«fileHeader(entry)»

	#pragma once

	#ifndef «classDefineGuard(entry)»
	#define «classDefineGuard(entry)»

	#include <«qtBaseClass(entry)»>
	«IF hasTimers()»
	#include <QHash>
	«ENDIF»
	#include "«getSrcGen(entry)»«baseClassName(entry)».h"
	«IF hasTimers()»
	#include "«getSrc(entry)»TimerInterface.h"
	#include "«getSrcGen(entry)»StatemachineTimer.h"
	«ENDIF»
	«IF isThreadSafe()»

	#include <mutex>

	typedef std::recursive_mutex      sc_mutex;
	typedef std::lock_guard<sc_mutex> sc_lock;
	«ENDIF»
	«IF isDebug()»

	#define QT_SCT_DEBUG 1
	«ENDIF»

	/**
	 * This class provides a link layer which wires the in and out events
	 * to the signal and slots of a Qt application.
	 */
	class «className(entry)» :
		public    «qtBaseClass(entry)»,
		public    «baseClassName(entry)»«FOR scope : getOcbScopes()»,
		protected «baseClassName(entry)»::«ocbName(scope)»«ENDFOR»«IF hasTimers()»,
		protected TimerInterface«ENDIF»
	{
		Q_OBJECT

	«IF hasTimers()»
	private:
		/**
		 * The QMap which maps von sc_eventid to a real
		 * StatemachineTimer instance.
		 */
		QHash<sc_eventid, StatemachineTimer *> timerMap;

	«ENDIF»
	«IF isThreadSafe()»
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
		explicit «className(entry)»(«qtBaseClass(entry)» * parent = «IF isCpp11()»nullptr«ELSE»Q_NULLPTR«ENDIF»);

		/**
		 * The destructor frees all resources allocated from this
		 * Qt/SCT layer.
		 */
		virtual ~«className(entry)»();

	private slots:
		«IF hasTimers»
		/**
		 * This slot is triggered from QTimer.
		 *
		 * @param event The timer event id which uniquely identifies the timer.
		 */
		void sct_timeout(const sc_eventid event);

		«ENDIF»
	public slots:
		/**
		 * This method initializes the statemachine and runs
		 * the first cycle. The virtual method initializeValues()
		 * is for initializing some statemachine values. After
		 * entering the statemachine the method react() is run
		 * to evaluate possible raised out events.
		 */
		void start(void);

		/**
		 * This method stops the statemachine and runs
		 * the last cycle. After leaving the statemachine
		 * the method react() is run to evaluate possible
		 * raised out events.
		 */
		void stop(void);

		«FOR scope : getInterfaceScopes()»
			«IF hasInEvents(scope)»
				«commentScope(scope)»
				«FOR event : getInEvents(scope)»
					/**
					 * This callback acts as a slot for
					 * the in event «event.name».
					 «IF event.type !== null»
					 *
					 * @param «parameter(event)» The «parameter(event)» event parameter.
					 «ENDIF»
					 */
					virtual void «Emit(event)»(«type(event)» «parameter(event)»);

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
					 «IF event.type !== null»
					 *
					 * @param «parameter(event)» The «parameter(event)» event parameter.
					 «ENDIF»
					 */
					void «Emit(event)»(«type(event)» «parameter(event)»);

				«ENDFOR»
			«ENDIF»
		«ENDFOR»

	protected:
		/**
		 * This method is intended to initialize possible ressources of
		 * this Qt/SCT layer.
		 */
		virtual void initializeValues(void) = 0;

		/**
		 * This runs a single statemachine cycle. See
		 * documentation of YAKINDU statechart tools for
		 * more information. After running the cycle the
		 * method react() is run to evaluate possible
		 * raised out events.
		 */
		virtual void runCycle(void)«IF isCpp11()» override«ENDIF»;

		/**
		 * This method converts raised out events into
		 * Qt signals. Events from internal scope are
		 * not converted into Qt signals. Instead a 
		 * further runCycle() is done.
		 */
		virtual void react(void);

		/**
		 * This method prints debug messages and may be
		 * overloaded to customize debug logging.
		 *
		 * @param message The message to log.
		 */
		virtual void sctQtDebug(const QString & message) const;
	«IF hasTimers()»
	
		virtual void setTimer(TimedStatemachineInterface* statemachine,
			const sc_eventid event,
			const sc_integer time,
			const sc_boolean isPeriodic)«IF isCpp11()» override«ENDIF»;
		virtual void unsetTimer(TimedStatemachineInterface* statemachine,
			const sc_eventid event)«IF isCpp11()» override«ENDIF»;
		virtual void cancel(void)«IF isCpp11()» override«ENDIF»;
	«ENDIF»
	};
	
	#endif // «classDefineGuard(entry)»
	'''

	def private timer(GeneratorEntry it)
	'''
	«fileHeader()»

	#pragma once

	#ifndef STATEMACHINETIMER_H
	#define STATEMACHINETIMER_H

	#include <QTimer>

	#include "«getSrc()»sc_types.h"

	/**
	 * This class represents a single timer instance for the YAKINDU
	 * SCT. The implementation uses the QTimer class of Qt.
	 */
	class StatemachineTimer :  public QTimer
	{
		Q_OBJECT
	
		/** This is the unique identifier from YAKINDU SCT. */
		const sc_eventid event_id;
	
	public:
		/**
		 * The constructor initializes the timer identified by
		 * the unique sc_eventid.
		 *
		 * @param parent The parent QObject to insert this timer object in.
		 * @param id The unique YAKINDU SCT timer id.
		 */
		explicit StatemachineTimer(QObject * parent, const sc_eventid id);

		«IF isCpp11»
			/**
			 * Remove default constructor since we definitely don't need the timer event id!.
			 */
			StatemachineTimer() = delete;

			/**
			 * Remove copy constructor since we definitely don't need more than one timer
			 * with the same event id!.
			 */
			StatemachineTimer(const StatemachineTimer &timer) = delete;

			/**
			 * Remove move constructor since we definitely don't need timer move around!.
			 */
			StatemachineTimer(StatemachineTimer && timer) = delete;
		«ENDIF»

	private slots:
		/**
		 * This slot converts the occured timeout event into a signal
		 * which informs the statemachine about an timeout event
		 * including the sc_eventid.
		 */
		void in_timeout();
	
	signals:
		/**
		 * This method signal emits the sc_eventid to the statemachine
		 * in case of a timeout event.
		 *
		 * @param id The sc_eventid which uniquely identifies this timer.
		 */
		void out_timeout(sc_eventid id);
	};
	
	#endif // STATEMACHINETIMER_H
	'''
}
