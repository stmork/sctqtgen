#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "statemachine.h"

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	Statemachine statemachine;

public:
	explicit MainWindow(QWidget * parent = 0);
	~MainWindow();

protected:
	void changeEvent(QEvent * e) override;

private:
	Ui::MainWindow * ui;

private slots:
	void updateGui();
	void waitState();
	void lanesState();
	void on_quitButton_clicked();
};

#endif // MAINWINDOW_H
