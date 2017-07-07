This project provides a generator for conneting the [YAKINDU
Statecharttools](http://statecharts.org) with a Qt application. Since the
concept of incoming and outgoing events is similar to the Qt signal and slot
concept it is logical to link both together. Note that the generated code is
an Addon onto the already generated C++-Code from SCT. So you need two
sgen-files. One to generate the C++ statemachine and one to generate the
link layer between the statemachine and your Qt application.

## Installation
You can decide between a snapshot or a release build. In your YAKINDU SCT Eclipse environment you only need to add the update site you want:
1. Snapshot: https://sourceforge.net/projects/sctqtgen/files/repositories/snapshot/
2. Release https://sourceforge.net/projects/sctqtgen/files/repositories/release/

If there are any updates you get informed if you select the menu item "Help -> Check for Updates..."

## Usage
To create a Qt-layer you have to create a new SCT-sgen-file.
1. Select "File -> New -> Other..."
2. In the wizard you search for "Code Generator".
3. Select "YAKINDU SCT -> Code Generator Model"
4. Choose an appropriate name and click "Next >"
5. Select "Qt-Generator for SCT" from the combobox, choose your statemachine for your Qt layer and click "Finish"

You now have a preconfigured sgen file for your Qt layer. There are two
features: *Outlet* and *QtSettings*. It is useful to configure the *Outlet*
in the same way as your C++ sgen file. With the *QtSettings* you can
configure the Qt generator.

### QtSettings
There are five preconfigured feature parameters to control the Qt generator.

#### baseClassName (String, required)
Look at your generated header file of your C++ generated statemachine. The
base class name ist equal to the class name of this statemachine. It is
equal to the *moduleName* you configured for your C++ sgen file in the
*IdentifierSettings* feature.

#### className (String, required)
This is the class name of the Qt link layer class. Choose something unique.

#### cpp11 (boolean, optional)
You can choose C++11 for generating some additional keywords like *override*. If you use C++11 don't forget to add the following line to your Qt's .pro-file:
~~~
CONFIG   += c++11
~~~

#### generateTimer (boolean, optional)
For the use of the SCT timer interface it is possible to generate a Qt timer
implementation. If you need more than one Qt link layer only one
implementation of the timer interface is necessary. So set this one to
*true* only in one sgen file.

#### threadSafe (boolean, optional)
The generated SCT statemachine is not thread safe as is. If you need to have
a thread safe environment you have to set this value to *true*. Note that Qt
mostly makes use of threads so you should set this to true just in case you
make use of timers.

**Note:** You have also set the cpp11 parameter to *true* because the generator makes use of the C++11 mutexes!

#### debug (boolean, optional, since V1.1.2)
Until version 1.1.1 the generator places some qDebug() calls into the
generated code to make debugging easier. Now this is done using the 
~~~
    virtual void sctQtDebug(const QString &message) const;
~~~
callback. So you can overload this method for some appropriate logging.

Additionally the you can turn off generating the log calls for release
builds. The default logging method is generated anyway so there is no need
to adjust your overloaded code.

The header contains the
~~~
#define QT_SCT_DEBUG 1
~~~
definition in the case if this debug flag is true.

#### camelCase (boolean, optional, since V1.1.2)
If this flags is true the signal and slot names are camel case which is the
default. Otherwise the names are generates as lower camel case like Qt is
using.

## Generated code
The generated code implements the following methods of the statemachines base class:
1. Initialisation of all SCT operation callbacks (so called OCB).
2. A pure virtual method *initializeValues()* for custom value initialisation.
2. In events as Qt slots
2. Out events as Qt signals
3. Respects internal events with an extra *runCycle()* call.
3. Implementation of the TimerInterface
4. Implementation of all SCT operations

### Setup project
To setup a new Qt-Project with YAKINDU SCT you should first create a Qt
project with qtcreator. After setting up the GUI etc. you can start
modelling the statechart using the YAKINDU statechart tools. It's no problem
to use qtcreator and YANKINDU SCT on the same project directory at the same
time. After that, you have to setup the sgen file for C++ and the
Qt-Generator. The C++ feature *IdentifierSettings* parameter *moduleName*
should have the same name as the Qt feature *QtSettings* parameter
*baseClassName*.

**NOTE!** In the default configuration of the C++ generator the operations
and variables of the internal scope are not visible. IMO it is a [bug and
I filed it up](https://github.com/Yakindu/statecharts/issues/271). The
SCT developers stated out that this bahaviour is by design. If you want
to use the internal scope inside your Qt layer you can work aound this by
setting the feature *GeneratorOptions* parameter
*innerFunctionVisibility* to *protected* as mentioned in the
[bug](https://github.com/Yakindu/statecharts/issues/271).

After setting up the statechart and the sgen files, the YAKINDU SCT and the
Qt-Generator plugins have generated the source files.

**NOTE!** You should add the generated source files to your SCM, since there is no
known way to generate them without starting the Eclipse IDE. Watch out for
the SCT bugs https://github.com/Yakindu/statecharts/issues/273 and
https://github.com/Yakindu/statecharts/issues/162.

After that you should add the generated files into your Qt project. Select
the project's context menu and select "*Add existing Files...*".

### Derive the Qt layer base class
Add a new C++ class which derive the abstract class generated from the Qt
generator. Implement this by deriving the base class with public visibility
otherwise you cannot connect the Qt's signals and slots to the statemachine.
Since the generated class does not implement any operation you have to do
this inside this class. Implement also the *initializeValues()* method since
it is defined pure virtual.

### Modify MainWindow class
First add a member variable of your statemachine's class to the *MainWindow* class. After that you should expand the constructor:
1. Wire all out events as signal from the statemachine to where ever you want.
2. Call the statemachine's *start()* method. Inside this method it calls the SCT *init()* method to initialize all values from the SCT statemachine. After that the Qt layers *initializeValues() *method is called. Finally the statemachine enters the processing by calling the SCT *enter()* method. Since the *enter()* method may raise out events, the *react()* method of the Qt layer is called.
3. Wire all signals from outside to slots of the statemachine which represents the in events.
Wiring the signals and slots in this order ensures no loss of events.

Finally you should add a call to the statemachines *stop()* method to the
destructor. Inside the *stop()* method the SCT's *exit()* method is called
and final out events are processed via the *react()* method of the Qt layer.

Now basically everything is done to integrate the Qt layer of the SCT statemachine to your Qt application.

### Implementation Notes
First you have to be familiar using the [YAKINDU SCT](https://www.itemis.com/en/yakindu/statechart-tools/documentation/)'s
C++ generator and [their implementation notes](https://www.itemis.com/en/yakindu/statechart-tools/documentation/#CGeneratorFeatures).

#### Running one cycle and out events
To process one cycle of the SCT's statemachine you have to call it's
*runCycle()* method. The Qt layer overrides this method to additionally call
the method *react()*. This method process all raised out events. Every
raised out event will emit a Qt signal. You are free to override the
*react()* method for additional custom processing, but don't forget to call
the base classes *react()* method otherwise you may loose events.

#### In events
The SCT's in events are implemented as Qt slots inside the Qt layer. In the
generated class the slot methods runs the SCT's *runCycle()* method. Since
this method may raise out events the *react()* method is called internally.

#### Custom event callbacks
The SCT only supports some very basic native datatypes such as *integer* and
*boolean*. If you need more typed datatypes like *unsigned* or slots with
more than one parameter you have to apply a custom handler.

For every in event you have to implement the Qt slot. Inside this method
call the SCT's *raiseXXX()* method to inform the statechart. After that you
have to call *runCycle()*.

For custom out event processing you have to override the *react()* method.
Emit signals everytime a *isRaisedXXX()* method returns true.

**NOTE!** Don't forget to call the base classes *react()* method otherwise you
will loose events.

#### Thread safety
Under normal cirmumstances you don't bother about thread safety. Simply
modify the feature *QtSettings* parameter *threadSafe* to your needs and
everything is done. If you need to implement custom processing for events
and thread safety you have to add the following line to every custom event
handler:
~~~
    sc_lock lock(mutex);
~~~

**Stay tuned for some example projects.**
