#include <iostream>

#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	SDL_Init(SDL_INIT_VIDEO); // Basics of SDL, init what you need to use
	qDebug() << "Initalize SDL successfully!";

	MainWindow MainWinExample;	// Creating an using a QMainWindow with central SDL widget
	qDebug() << "init sdl window";
	MainWinExample.show();
	qDebug() << "show window";

	MainWinExample.render();

	int RetVal = a.exec();	// Most examples have this on the return, we
							// need to have it return to a variable cause:
	SDL_Quit();	// We can't put this statement before the exec, or after

	qDebug() << "Quite SDL!";
	
	return RetVal;
}
