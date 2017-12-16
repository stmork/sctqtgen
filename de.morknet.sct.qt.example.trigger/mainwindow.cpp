#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->pushButton, &QPushButton::clicked, &statemachine, &Statemachine::pressed);
	connect(&statemachine, &Statemachine::update, this, &MainWindow::updateGui);
	connect(&statemachine, &Statemachine::wait,   this, &MainWindow::waitState);
	connect(&statemachine, &Statemachine::lanes,  this, &MainWindow::lanesState);

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

void MainWindow::updateGui()
{
	ui->counterLabel->setText(QString::asprintf("Zähler: %d", statemachine.getSCI_Gui()->get_counter()));
}

void MainWindow::waitState()
{
	ui->stateLabel->setText("Wait");
}

void MainWindow::lanesState()
{
	ui->stateLabel->setText("Lanes");
}

void MainWindow::on_quitButton_clicked()
{
	QApplication::quit();
}
