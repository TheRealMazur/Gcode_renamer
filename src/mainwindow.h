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
#include <QSettings>
#include <QStandardPaths>
#include <QApplication>

#include <QPixmap>
#include <QDir>

#include "gcodefile.h"



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


    void on_actionOpen_triggered();

    void on_silentModeCheckBox_stateChanged(int arg1);

    void on_separatorComboBox_currentIndexChanged(int index);

    void on_timePlaceComboBox_currentIndexChanged(int index);

    void on_timeFormatComboBox_currentIndexChanged(int index);

    void on_actionAbout_triggered();

    void on_actionAbout_Qt_triggered();

private:
    Ui::MainWindow *ui;
    GcodeFile *loadedGcodeFile = nullptr; // the G-Code file that has been loaded into the program
    void saveNewGcode();
    void loadSettings();
    void saveSettings();
    void openActionTriggerred();    //added to avoid code duplication, used whenever user wants to open the file opening dialog
    void updateNewFilename();

};

#endif // MAINWINDOW_H
