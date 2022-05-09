#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "statemachine.h"


namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	StateMachine csm;

public:
	explicit MainWindow(QWidget * parent = 0);
	~MainWindow();

public slots:
	void ShowAccu(sc::integer accu);
	void Exit();

private:
	Ui::MainWindow * ui;
};

#endif // MAINWINDOW_H
