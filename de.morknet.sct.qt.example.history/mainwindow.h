/**
 * Copyright (C) GIRA Giersiepen GmbH & Co. KG
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src-gen/HistoryStatemachine.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow :
	public QMainWindow,
	protected HistoryStatemachine::OperationCallback
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget * parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow   *  ui;
	HistoryStatemachine statemachine;

	void label(char * text) override;
};

#endif // MAINWINDOW_H
