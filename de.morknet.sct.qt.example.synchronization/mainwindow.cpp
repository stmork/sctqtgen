#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) :
	QMainWindow(parent),
	SelfPointer<SynchronizationStatemachine::OperationCallback>(this),
	ui(new Ui::MainWindow),
	statemachine(nullptr),
	sm_ptr(&statemachine)
{
	ui->setupUi(this);

	connect(
		ui->startButton, &QPushButton::clicked,
		&statemachine, &SynchronizationStatemachine::start);
	connect(
		ui->leftButton, &QPushButton::clicked,
		&statemachine, &SynchronizationStatemachine::triggerLeft);
	connect(
		ui->rightButton, &QPushButton::clicked,
		&statemachine, &SynchronizationStatemachine::triggerRight);

	statemachine.setOperationCallback(*this);
	statemachine.enter();
}

MainWindow::~MainWindow()
{
	statemachine.exit();
	delete ui;
}

void MainWindow::waiting()
{
	ui->label->setText("Waiting");
	ui->left->setText("-");
	ui->right->setText("-");
}

void MainWindow::started()
{
	ui->label->setText("Started");
}

void MainWindow::left()
{
	ui->left->setText("Left");
}

void MainWindow::right()
{
	ui->right->setText("Right");
}

void MainWindow::leftClicked()
{
	ui->left->setText("Left clicked");
}

void MainWindow::rightClicked()
{
	ui->right->setText("Right clicked");
}

void MainWindow::completed()
{
	ui->label->setText("Completed");
	ui->left->setText("-");
	ui->right->setText("-");
}
