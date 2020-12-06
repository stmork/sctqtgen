/*
 * Copyright (C) 2020  -  Steffen A. Mork
 */

package de.morknet.sct.qt.generator;

public interface IFeatureConstants
{
	public static final String LIBRARY_NAME     = "Qt-Generator for SCT";
	public static final String QT_FEATURE       = "QtSettings";

	public static final String QT_BASECLASSNAME = "baseClassName";
	public static final String QT_CLASSNAME     = "className";
	public static final String QT_CPP11         = "cpp11";
	public static final String QT_GENERATETIMER = "generateTimer";
	public static final String QT_THREADSAFE    = "threadSafe";
	public static final String QT_DEBUG         = "debug";
	public static final String QT_CAMEL_CASE    = "camelCase";
	public static final String QT_BASE_CLASS    = "qtBaseClass";

	public static final String  QT_BASECLASSNAME_DEFAULT = "AbstractStateMachine";
	public static final String  QT_CLASSNAME_DEFAULT     = QT_BASECLASSNAME_DEFAULT + "Adaptor";
	public static final boolean QT_CPP11_DEFAULT         = true;
	public static final boolean QT_GENERATETIMER_DEFAULT = true;
	public static final boolean QT_THREADSAFE_DEFAULT    = false;
	public static final boolean QT_DEBUG_DEFAULT         = true;
	public static final boolean QT_CAMEL_CASE_DEFAULT    = true;
	public static final String  QT_BASE_CLASS_DEFAULT    = "QObject";
}
