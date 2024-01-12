#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) :
	QMainWindow(parent),
	SelfPointer<OrthogonalStatemachine::OperationCallback>(this),
	ui(new Ui::MainWindow),
	statemachine(nullptr),
	sm_ptr(&statemachine)
{
	ui->setupUi(this);
	ui->bothRadioButton->setChecked(true);

	connect(ui->triggerButton, &QPushButton::clicked, &statemachine, &OrthogonalStatemachine::trigger);
	connect(ui->nothingRadioButton, &QRadioButton::clicked, [&]
	{
		selection = NOTHING;
	});
	connect(ui->leftRadioButton, &QRadioButton::clicked, [&]
	{
		selection = LEFT;
	});
	connect(ui->rightRadioButton, &QRadioButton::clicked, [&]
	{
		selection = RIGHT;
	});
	connect(ui->bothRadioButton, &QRadioButton::clicked, [&]
	{
		selection = BOTH;
	});
	connect(ui->exitButton, &QPushButton::clicked, []
	{
		QApplication::quit();
	});

	statemachine.setOperationCallback(*this);
	statemachine.enter();
}

MainWindow::~MainWindow()
{
	statemachine.exit();
	delete ui;
}

bool MainWindow::isLeft()
{
	return selection & LEFT;
}

bool MainWindow::isRight()
{
	return selection & RIGHT;
}

void MainWindow::label()
{
	ui->leftLabel->setText( QString::asprintf("Links: %d",  statemachine.getLeft()));
	ui->rightLabel->setText(QString::asprintf("Rechts: %d", statemachine.getRight()));
}
