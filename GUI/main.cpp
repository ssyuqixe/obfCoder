#include "GUI.h"
#include <QtWidgets/QApplication>

#include "stdafx.h"

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "Parser.h"

bool UseSimulator = true;

_CrtMemState MemState;

int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    GUI w;
    w.show();

    return a.exec();
}
