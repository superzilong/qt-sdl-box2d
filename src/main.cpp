#include <iostream>

#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "Core/Log.h"

int main(int argc, char *argv[])
{
	Log::Init();

    QApplication a(argc, argv);

	SDL_Init(SDL_INIT_VIDEO); // Basics of SDL, init what you need to use
	LOG_TRACE("Initalize SDL successfully!{}");

	MainWindow MainWinExample;	// Creating an using a QMainWindow with central SDL widget
	LOG_TRACE("init sdl window");
	
	MainWinExample.show();
	LOG_TRACE("show window");

	MainWinExample.render();

	int RetVal = a.exec();	// Most examples have this on the return, we
							// need to have it return to a variable cause:
	SDL_Quit();	// We can't put this statement before the exec, or after

	LOG_TRACE("Quite SDL!");
	
	return RetVal;
}
