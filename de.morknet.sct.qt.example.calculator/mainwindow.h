#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>

#include "statemachine.h"
#include "src-qt-lib/sc_self_pointer.h"

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	StateMachine              csm;
	SelfPointer<StateMachine> csm_ptr;

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
