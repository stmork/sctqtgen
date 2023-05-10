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

private:
	Statemachine              statemachine;
	SelfPointer<Statemachine> sm_ptr;

public:
	explicit MainWindow(QWidget * parent = 0);
	~MainWindow();

protected:
	void changeEvent(QEvent * e) override;

private:
	Ui::MainWindow * ui;

private slots:
	void updateGui();
	void waitState();
	void lanesState();
	void on_quitButton_clicked();
};

#endif // MAINWINDOW_H
