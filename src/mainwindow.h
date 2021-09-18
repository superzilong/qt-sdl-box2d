#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
private:
    Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void render();

private:

	Ui::MainWindow *ui;
	int idx = 0;

private slots:
	void slot_PrintMousePos(const QPoint& pos);
};
#endif // MAINWINDOW_H
