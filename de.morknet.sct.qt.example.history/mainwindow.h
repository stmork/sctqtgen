#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>

#include "src-gen/HistoryStatemachine.h"
#include "src-lib/sc_self_pointer.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow :
	public QMainWindow,
	protected HistoryStatemachine::OperationCallback,
	protected SelfPointer<HistoryStatemachine::OperationCallback>
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget * parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow         *         ui;
	HistoryStatemachine              statemachine;
	SelfPointer<HistoryStatemachine> sm_ptr;

	void label(std::string text) override;
};

#endif // MAINWINDOW_H
