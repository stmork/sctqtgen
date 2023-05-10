#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>

#include <src-gen/SynchronizationStatemachine.h>
#include <src-lib/sc_self_pointer.h>

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow :
	public QMainWindow,
	protected SynchronizationStatemachine::OperationCallback,
	protected SelfPointer<SynchronizationStatemachine::OperationCallback>
{
	Q_OBJECT

public:
	MainWindow(QWidget * parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow             *             ui;
	SynchronizationStatemachine              statemachine;
	SelfPointer<SynchronizationStatemachine> sm_ptr;

	void waiting() override;
	void started() override;
	void left() override;
	void right() override;
	void leftClicked() override;
	void rightClicked() override;
	void completed() override;
};
#endif // MAINWINDOW_H
