/* Copyright (C) 2021 - Steffen A. Mork */

#ifndef SC_QT_TIMERSERVICE_H_
#define SC_QT_TIMERSERVICE_H_


#include <QObject>
#include <QTimer>
#include <QMap>
#include <QPair>

#include "sc_timer.h"


namespace sc
{

namespace qt
{

    class SCTimer : public QTimer
    {
        Q_OBJECT

    public:
        explicit SCTimer(QObject * parent, sc::timer::TimedInterface* machine, const sc_eventid id);

    signals:
        void fireTimeEvent(sc::timer::TimedInterface *machine, sc_eventid event);

    public slots:
        void triggerTimeEvent();

    protected:
        sc::timer::TimedInterface *machine;
        sc_eventid eventId;
    };



    class SCTimerService : public QObject, public sc::timer::TimerServiceInterface
    {
        Q_OBJECT

    public:
        explicit SCTimerService(QObject *parent);

        virtual void setTimer(sc::timer::TimedInterface* statemachine, sc_eventid event, sc_integer time_ms, sc_boolean isPeriodic);
        virtual void unsetTimer(sc::timer::TimedInterface* statemachine, sc_eventid event);
        virtual void cancel();

    signals:

    public slots:
        void raiseTimeEvent(sc::timer::TimedInterface *machine, sc_eventid event);

    protected:
        QMap<sc::timer::TimedInterface*,QMap<sc_eventid, SCTimer*>*> machineTimerMapMap;
        SCTimer* getTimer(sc::timer::TimedInterface *machine, sc_eventid event);

    };

} // namespace qt

} // namespace sc

#endif // SC_QT_TIMERSERVICE_H_

