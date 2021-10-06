#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src-gen/OrthogonalStatemachine.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow :
	public QMainWindow,
	protected OrthogonalStatemachine::OperationCallback
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget * parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow    *    ui;
	OrthogonalStatemachine statemachine;

	enum Selection
	{
		NOTHING,
		LEFT,
		RIGHT,
		BOTH
	} selection = BOTH;

	bool isLeft() override;
	bool isRight() override;
	void label() override;
};
#endif // MAINWINDOW_H
