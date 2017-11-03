#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "delayedstatemachine.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	DelayedStateMachine dsm;

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	void changeEvent(QEvent *e);

private:
	Ui::MainWindow *ui;

private slots:
	void stateA();
	void doSomething();
	void exit();
};

#endif // MAINWINDOW_H
