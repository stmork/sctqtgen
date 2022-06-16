#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "statemachine.h"

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	StateMachine dsm;
	QTimer              timer;

public:
	explicit MainWindow(QWidget * parent = 0);
	~MainWindow();

protected:
	void changeEvent(QEvent * e) override;

private:
	Ui::MainWindow * ui;

private slots:
	void stateA();
	void doSomething();
	void stopping(bool waiting);
	void triggerStop();
	void exit();
};

#endif // MAINWINDOW_H
