#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect (ui->pushButton1, &QPushButton::clicked, &dsm, &AbstractDelayDispatcher::button1);
	connect (ui->pushButton2, &QPushButton::clicked, &dsm, &AbstractDelayDispatcher::button2);
	connect (ui->exitButton,  &QPushButton::clicked, this, &MainWindow::exit);

	connect (&dsm, &AbstractDelayDispatcher::stateA,      this, &MainWindow::stateA);
	connect (&dsm, &AbstractDelayDispatcher::doSomething, this, &MainWindow::doSomething);

	dsm.start();
}

MainWindow::~MainWindow()
{
	dsm.stop();
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

void MainWindow::stateA()
{
	ui->label->setText(tr("State A"));
}

void MainWindow::doSomething()
{
	ui->label->setText(tr("Do something!"));
}

void MainWindow::exit()
{
	QApplication::exit();
}
