#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) :
	QMainWindow(parent),
	statemachine(nullptr),
	sm_ptr(&statemachine),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->pushButton, &QPushButton::clicked, &statemachine, &Statemachine::gui_pressed);
	connect(&statemachine, &Statemachine::gui_update, this, &MainWindow::updateGui);
	connect(&statemachine, &Statemachine::gui_wait,   this, &MainWindow::waitState);
	connect(&statemachine, &Statemachine::gui_lanes,  this, &MainWindow::lanesState);

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

void MainWindow::updateGui()
{
	ui->counterLabel->setText(QString::asprintf("Counter: %d", statemachine.gui().getCounter()));
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
