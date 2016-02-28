#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// Wire statemachine into main window
	connect(&csm, SIGNAL(ShowAccu(sc_integer)), this, SLOT(ShowAccu(sc_integer)));
	connect(&csm, SIGNAL(Exit()), this, SLOT(Exit()));

	// Now start the statemachine
	csm.start();

	// Wire GUi elements into statemachine
	connect(ui->button0, SIGNAL(clicked()), &csm, SLOT(Button0()));
	connect(ui->button1, SIGNAL(clicked()), &csm, SLOT(Button1()));
	connect(ui->button2, SIGNAL(clicked()), &csm, SLOT(Button2()));
	connect(ui->button3, SIGNAL(clicked()), &csm, SLOT(Button3()));
	connect(ui->button4, SIGNAL(clicked()), &csm, SLOT(Button4()));
	connect(ui->button5, SIGNAL(clicked()), &csm, SLOT(Button5()));
	connect(ui->button6, SIGNAL(clicked()), &csm, SLOT(Button6()));
	connect(ui->button7, SIGNAL(clicked()), &csm, SLOT(Button7()));
	connect(ui->button8, SIGNAL(clicked()), &csm, SLOT(Button8()));
	connect(ui->button9, SIGNAL(clicked()), &csm, SLOT(Button9()));

	connect(ui->buttonAdd, SIGNAL(clicked()), &csm, SLOT(ButtonAdd()));
	connect(ui->buttonSub, SIGNAL(clicked()), &csm, SLOT(ButtonSub()));
	connect(ui->buttonMult, SIGNAL(clicked()), &csm, SLOT(ButtonMult()));
	connect(ui->buttonDiv, SIGNAL(clicked()), &csm, SLOT(ButtonDiv()));
	connect(ui->buttonClear, SIGNAL(clicked()), &csm, SLOT(ButtonClear()));
	connect(ui->buttonEquals, SIGNAL(clicked()), &csm, SLOT(ButtonEquals()));
}

MainWindow::~MainWindow()
{
	// Don't forget to stop the statemachine!
	csm.stop();

	delete ui;
}

void MainWindow::Exit()
{
	QApplication::exit();
}

void MainWindow::ShowAccu(sc_integer accu)
{
	QString label = QString::number(accu);

	ui->label->setText(label);
}
