/*
 * Copyright (C) 2019  -  Steffen A. Mork
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.generator.templates

import com.google.inject.Inject
import com.yakindu.sct.model.sexec.ExecutionFlow
import com.yakindu.sct.model.sgen.GeneratorEntry
import org.eclipse.xtext.generator.IFileSystemAccess

class Implementation
{
	@Inject extension Comments
	@Inject extension Names
	@Inject extension Features
	@Inject extension Selector

	/**
	 * Entry point for code generation.
	 * @param flow The statecharts execution flow.
	 * @param entry The generator configuration entry.
	 * @param access The file system starting point for file access
	 */
	def generate(ExecutionFlow flow, GeneratorEntry entry, IFileSystemAccess access)
	{
		access.generateFile(implFileName(flow, entry), signalDispatcher(flow, entry))
		if (generateTimer())
		{
			access.generateFile("StatemachineTimer.cpp", timer(entry))
		}
	}

	/**
	 * The template method creates the abstract signal dispatcher class.
	 * It is put between the generated abstract statemachine class
	 * generated from the YAKINDU SCT and the implementation class. 
	 */
	def private signalDispatcher(ExecutionFlow it, GeneratorEntry entry)
	'''
	«fileHeader(entry)»

	#include "«getSrcGen(entry) + headerFileName(entry)»"
	«IF isDebug()»
	#include <QtDebug>
	«IF hasTimers»
	#include <inttypes.h>
	«ENDIF»
	«ENDIF»
	
	/**
	 * The callback instances are setup inside this constructor.
	 * It's easy to say that the callback instances are implemented
	 * by our class instance itself.
	 */
	«className(entry)»::«className(entry)»(«qtBaseClass(entry)» * parent) :
		«qtBaseClass(entry)»(parent)
	{
		«IF hasTimers»
		«baseClassName(entry)»::setTimer(this);
		«ENDIF»
		«FOR scope : ocbScopes»
			«ocbNameSetter(scope)»(this);
		«ENDFOR»
		«baseClassName(entry)»::init();
	}

	/**
	 * The destructor calls the statemachine's exit() method,
	 * calls the react() method for processing outgoing signals
	 * and frees all known timer.
	 */
	«className(entry)»::~«className(entry)»()
	{
		«IF hasTimers»
		«IF isThreadSafe()»
		sc_lock lock(mutex);

		«ENDIF»
		«IF isCpp11()»
			for(StatemachineTimer *timer : timerMap.values())
			{
		«ELSE»
			QHash<sc_eventid, StatemachineTimer *>::iterator i;

			for(i = timerMap.begin();i != timerMap.end(); ++i)
			{
				StatemachineTimer *timer = *i;

		«ENDIF»
			timer->disconnect(
				timer, &StatemachineTimer::out_timeout,
				this, &«className(entry)»::sct_timeout);
			timer->stop();

			delete timer;
		}
		«ENDIF»
	}

	void «className(entry)»::start(void)
	{
		«IF isThreadSafe()»
		sc_lock lock(mutex);

		«ENDIF»
		// Do some custom initialization.
		initializeValues();

		«baseClassName(entry)»::clearOutEvents();
		«baseClassName(entry)»::enter();
		react();
	}

	void «className(entry)»::stop(void)
	{
		«IF isThreadSafe()»
		sc_lock lock(mutex);

		«ENDIF»
		«baseClassName(entry)»::clearOutEvents();
		«baseClassName(entry)»::exit();
		react();
	}

	void «className(entry)»::runCycle()
	{
		«baseClassName(entry)»::runCycle();
		react();
	}

	void «className(entry)»::react(void)
	{
		«IF hasInternalEvents»
			bool internalEventOccured = false;
		«ENDIF»
		«FOR scope : getInterfaceScopes()»
			«IF hasOutEvents(scope)»

				«commentScope(scope)»
				«FOR event : getOutEvents(scope)»
					if («instanceName(scope)».«asRaised(event)»())
					{
						«IF isDebug()»
						sctQtDebug("emit «Emit(event)»()...");
						«ENDIF»
						emit «Emit(event)»(«typeGetter(event, scope)»);
					}
				«ENDFOR»
			«ENDIF»
		«ENDFOR»
		«IF hasInternalEvents»
			«FOR scope : getInternalScopes»

				«commentScope(scope)»
				«FOR event : getEvents(scope)»
					internalEventOccured |= «instanceName(scope)».«asRaised(event)»();
				«ENDFOR»
			«ENDFOR»
			«IF !isEventDriven»

			// Check for internal events
			if (internalEventOccured)
			{
				runCycle();
			}
			«ENDIF»
		«ENDIF»
	}

	void «className(entry)»::sctQtDebug(const QString & message) const
	{
		«IF isDebug()»
			qDebug() << message;
		«ELSE»
			Q_UNUSED(message)
		«ENDIF»
	}

	«FOR scope : getInterfaceScopes()»
		«IF hasInEvents(scope)»

			«commentScope(scope)»
			«FOR event : getInEvents(scope)»

	void «className(entry)»::«Emit(event)»(«type(event)» «parameter(event)»)
	{
		«IF isThreadSafe()»
		sc_lock lock(mutex);

		«ENDIF»
		«IF isDebug()»
		sctQtDebug("«Emit(event)»()...");
		«ENDIF»
		«instanceName(scope)».«asRaise(event)»(«parameter(event)»);
		«IF !isEventDriven»
		runCycle();
		«ENDIF»
	}
			«ENDFOR»
		«ENDIF»
	«ENDFOR»
	«IF hasTimers»

	/**
	 * This method implements the canceling of the statemachine.
	 * It intentionally does nothing.
	 */
	void «className(entry)»::cancel(void)
	{
		«IF isDebug()»
		sctQtDebug("Cancel.");
		«ENDIF»
	}

	/*********************************************************************/
	/*                                                                   */
	/*     Timer callbacks                                               */
	/*                                                                   */
	/*********************************************************************/

	/**
	 * This method implements the TimerInterface class provided by
	 * the YAKINDU SCT. It intends to initialize and start a timer
	 * In this Qt implementation the timer is mapped from a
	 * sc_eventid. A timer is only created on first request. The
	 * timer is initialized per cycle time and periodicity and
	 * connected via a Qt signal into this class for statemachine
	 * callback. Note that a timer may be reinitialized!
	 *
	 * @see sct_timeout()
	 */
	void «className(entry)»::setTimer(
			TimedStatemachineInterface *statemachine,
			const sc_eventid event,
			const sc_integer time,
			const sc_boolean isPeriodic)
	{
		Q_UNUSED(statemachine);
		StatemachineTimer *timer = timerMap[event];
		const bool high_precision = (time % 1000) != 0;

		if (timer == «IF isCpp11()»nullptr«ELSE»NULL«ENDIF»)
		{
			timer = new StatemachineTimer(this, event);
			timerMap.insert(event, timer);
		}
		timer->setTimerType(high_precision ? Qt::TimerType::PreciseTimer : Qt::TimerType::CoarseTimer);
		timer->setInterval(time);
		timer->setSingleShot(!isPeriodic);
		timer->connect(
			timer, &StatemachineTimer::out_timeout,
			this, &«className(entry)»::sct_timeout);
		timer->start();
		«IF isDebug()»

		if (high_precision)
		{
			sctQtDebug(QString::asprintf("Activated timer %" PRIxPTR " with timeout %dms.", event, time));
		}
		else
		{
			sctQtDebug(QString::asprintf("Activated timer %" PRIxPTR " with timeout %ds.", event, time / 1000));
		}
		«ENDIF»
	}

	/**
	 * This method deinitialize a timer belonging to a sc_eventid. The timer
	 * is not deleted but disconnected from Qt signal/slot.
	 */
	void «className(entry)»::unsetTimer(
		TimedStatemachineInterface *statemachine,
		const sc_eventid event)
	{
		Q_UNUSED(statemachine);
		StatemachineTimer *timer = timerMap[event];

		if (timer != «IF isCpp11()»nullptr«ELSE»NULL«ENDIF»)
		{
			timer->disconnect(
				timer, &StatemachineTimer::out_timeout,
				this, &«className(entry)»::sct_timeout);
			timer->stop();
			«IF isDebug()»
			sctQtDebug(QString::asprintf("Disabled timer %" PRIxPTR ".", event));
			«ENDIF»
		}
	}

	/**
	 * This Qt slot is signalled by a timer belonging to the given
	 * sc_eventid.
	 */
	void «className(entry)»::sct_timeout(const sc_eventid event)
	{
		«IF isThreadSafe()»
		sc_lock lock(mutex);

		«ENDIF»
		«IF isDebug()»
		sctQtDebug(QString::asprintf("Time event occured with id %" PRIxPTR ".", event));
		«ENDIF»
		raiseTimeEvent(event);
		runCycle();
	}
	«ENDIF»
	'''

	def private timer(GeneratorEntry it)
	'''
	«fileHeader()»

	#include "«getSrcGen()»StatemachineTimer.h"

	StatemachineTimer::StatemachineTimer(
		QObject * parent,
		const sc_eventid id) : QTimer(parent), event_id(id)
	{
		connect(this, &StatemachineTimer::timeout, this, &StatemachineTimer::in_timeout);
	}
	
	void StatemachineTimer::in_timeout()
	{
		emit out_timeout(event_id);
	}
	'''
}
