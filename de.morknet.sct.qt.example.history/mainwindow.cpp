/**
 * Copyright (C) GIRA Giersiepen GmbH & Co. KG
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) :
	QMainWindow(parent), ui(new Ui::MainWindow),
	statemachine(this)
{
	ui->setupUi(this);

	connect(ui->proceedButton, &QPushButton::clicked, &statemachine, &HistoryStatemachine::proceed);
	connect(ui->toggleButton,  &QPushButton::clicked, &statemachine, &HistoryStatemachine::toggle);
	connect(ui->outsideButton, &QPushButton::clicked, &statemachine, &HistoryStatemachine::outside);

	connect(ui->exitButton, &QPushButton::clicked, []
	{
		QApplication::quit();
	} );

	statemachine.setOperationCallback(this);
	statemachine.enter();
}

MainWindow::~MainWindow()
{
	statemachine.exit();
	delete ui;
}

void MainWindow::label(std::string text)
{
	ui->label->setText(QString(text.c_str()));
}
