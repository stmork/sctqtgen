#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <src-gen/SynchronizationStatemachine.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow :
		public QMainWindow,
		protected SynchronizationStatemachine::OperationCallback
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	SynchronizationStatemachine statemachine;

	void waiting() override;
	void started() override;
	void left() override;
	void right() override;
	void leftClicked() override;
	void rightClicked() override;
	void completed() override;
};
#endif // MAINWINDOW_H
