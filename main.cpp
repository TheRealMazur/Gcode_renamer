#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("My Company");                //Had to add it to have write permissions in Win 10 -.-'
    a.setOrganizationDomain("https://github.com/krzmazur1/Gcode_renamer");
    a.setApplicationName("Gcode_Renamer");
    MainWindow w;
    w.show();

    return a.exec();
}
