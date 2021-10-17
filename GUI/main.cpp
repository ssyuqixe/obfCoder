#include "GUI.h"
#include <QtWidgets/QApplication>

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "Parser.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUI w;
    w.show();

    return a.exec();
}
