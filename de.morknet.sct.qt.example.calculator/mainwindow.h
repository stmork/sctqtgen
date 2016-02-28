#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "calculatorstatemachine.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	CalculatorStateMachine csm;

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void ShowAccu(sc_integer accu);
	void Exit();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
