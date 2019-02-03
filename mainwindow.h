#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
#include <QMimeData>
#include <QDropEvent>
#include "gcodefile.h"

#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);


private slots:
    void on_openButton_released();

    void on_pushButton_2_released();
    void openNewGcode(QString path);


private:
    Ui::MainWindow *ui;
    GcodeFile *loadedGcodeFile; // the G-Code file that has been loaded into the program
    void safeNewGcode();
    //QFile file2Open, file2Save;

};

#endif // MAINWINDOW_H
