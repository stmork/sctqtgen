#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->pushButton, &QPushButton::clicked, &statemachine, &StateMachine::Clicked);
	connect(&statemachine, &StateMachine::On,  this, &MainWindow::on);
	connect(&statemachine, &StateMachine::Off, this, &MainWindow::off);
	statemachine.start();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void MainWindow::on()
{
	ui->label->setText("On");
}

void MainWindow::off()
{
	ui->label->setText("Off");
}
