#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// Wire statemachine into main window
	connect(&csm, &CalculatorStateMachine::gui_ShowAccu, this, &MainWindow::ShowAccu);
	connect(&csm, &CalculatorStateMachine::gui_Exit,     this, &MainWindow::Exit);

	// Now start the statemachine
	csm.enter();

	// Wire GUi elements into statemachine
	connect(ui->button0, &QPushButton::clicked, &csm, &CalculatorStateMachine::gui_Button0);
	connect(ui->button1, &QPushButton::clicked, &csm, &CalculatorStateMachine::gui_Button1);
	connect(ui->button2, &QPushButton::clicked, &csm, &CalculatorStateMachine::gui_Button2);
	connect(ui->button3, &QPushButton::clicked, &csm, &CalculatorStateMachine::gui_Button3);
	connect(ui->button4, &QPushButton::clicked, &csm, &CalculatorStateMachine::gui_Button4);
	connect(ui->button5, &QPushButton::clicked, &csm, &CalculatorStateMachine::gui_Button5);
	connect(ui->button6, &QPushButton::clicked, &csm, &CalculatorStateMachine::gui_Button6);
	connect(ui->button7, &QPushButton::clicked, &csm, &CalculatorStateMachine::gui_Button7);
	connect(ui->button8, &QPushButton::clicked, &csm, &CalculatorStateMachine::gui_Button8);
	connect(ui->button9, &QPushButton::clicked, &csm, &CalculatorStateMachine::gui_Button9);

	connect(ui->buttonAdd,    &QPushButton::clicked, &csm, &CalculatorStateMachine::gui_ButtonAdd);
	connect(ui->buttonSub,    &QPushButton::clicked, &csm, &CalculatorStateMachine::gui_ButtonSub);
	connect(ui->buttonMult,   &QPushButton::clicked, &csm, &CalculatorStateMachine::gui_ButtonMult);
	connect(ui->buttonDiv,    &QPushButton::clicked, &csm, &CalculatorStateMachine::gui_ButtonDiv);
	connect(ui->buttonClear,  &QPushButton::clicked, &csm, &CalculatorStateMachine::gui_ButtonClear);
	connect(ui->buttonEquals, &QPushButton::clicked, &csm, &CalculatorStateMachine::gui_ButtonEquals);
}

MainWindow::~MainWindow()
{
	// Don't forget to stop the statemachine!
	csm.exit();

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
