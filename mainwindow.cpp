#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_released()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Gcode"), QDir::homePath()+="/Desktop", tr("Gcode Files (*.gcode)"));
    std::string  x = fileName.toStdString();
    std::printf("%s", x.c_str());
}
