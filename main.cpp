#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("TheRealMazur");                //Had to add it to have write permissions in Win 10 -.-'
    a.setOrganizationDomain("https://github.com/TheRealMazur/Gcode_renamer");
    a.setApplicationName("Gcode_Renamer");
    MainWindow w;
    w.show();

    return a.exec();
}
