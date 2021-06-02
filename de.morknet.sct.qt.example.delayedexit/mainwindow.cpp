#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	timer.setInterval(1000);
	timer.setSingleShot(true);

	connect (ui->pushButton1, &QPushButton::clicked, &dsm, &DelayedStateMachine::gui_button1);
	connect (ui->pushButton2, &QPushButton::clicked, &dsm, &DelayedStateMachine::gui_button2);
	connect (ui->exitButton,  &QPushButton::clicked, this, &MainWindow::exit);

	connect (&timer, &QTimer::timeout, &dsm, &AbstractDelay::gui_complete);
	connect (&dsm, &DelayedStateMachine::gui_stateA,      this, &MainWindow::stateA);
	connect (&dsm, &DelayedStateMachine::gui_doSomething, this, &MainWindow::doSomething);
	connect (&dsm, &DelayedStateMachine::gui_triggerStop, this, &MainWindow::triggerStop);
	connect (&dsm, &DelayedStateMachine::gui_stopping,    this, &MainWindow::stopping);

	dsm.enter();
}

MainWindow::~MainWindow()
{
	dsm.exit();
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

void MainWindow::stateA()
{
	ui->label->setText(tr("State A"));
}

void MainWindow::doSomething()
{
	ui->label->setText(tr("Do something!"));
}

void MainWindow::stopping(bool waiting)
{
	ui->waiting->setText(tr(waiting ? "Waiting..." : ""));
}

void MainWindow::triggerStop()
{
	timer.start();
}

void MainWindow::exit()
{
	QApplication::exit();
}
