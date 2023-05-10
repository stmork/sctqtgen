#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>

#include "src-gen/OrthogonalStatemachine.h"
#include "src-lib/sc_self_pointer.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow :
	public QMainWindow,
	protected OrthogonalStatemachine::OperationCallback,
	protected SelfPointer<OrthogonalStatemachine::OperationCallback>
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget * parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow           *          ui;
	OrthogonalStatemachine              statemachine;
	SelfPointer<OrthogonalStatemachine> sm_ptr;

	enum Selection
	{
		NOTHING,
		LEFT,
		RIGHT,
		BOTH
	} selection = BOTH;

	bool isLeft() override;
	bool isRight() override;
	void label() override;
};

#endif // MAINWINDOW_H
