#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->pushButton, &QPushButton::clicked, &statemachine, &StateMachine::gui_clicked);
	connect(&statemachine, &StateMachine::gui_on,  this, &MainWindow::on);
	connect(&statemachine, &StateMachine::gui_off, this, &MainWindow::off);
	statemachine.enter();
}

MainWindow::~MainWindow()
{
	statemachine.exit();
	delete ui;
}

void MainWindow::changeEvent(QEvent * e)
{
	QMainWindow::changeEvent(e);
	switch (e->type())
	{
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
