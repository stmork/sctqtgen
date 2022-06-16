#pragma once

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

private:
	StateMachine statemachine;

public:
	explicit MainWindow(QWidget * parent = 0);
	~MainWindow();

protected:
	void changeEvent(QEvent * e) override;

private:
	Ui::MainWindow * ui;

private slots:
	void on();
	void off();
};

#endif // MAINWINDOW_H
