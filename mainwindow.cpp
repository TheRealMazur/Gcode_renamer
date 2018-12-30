#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->filenameText->setVisible(0);
    ui->printTimeText->setVisible(0);
    ui->printSilentTimeText->setVisible(0);
    ui->newFilenameText->setVisible(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_released()
{
//    QFileDialog::FileMode mode = QFileDialog::ExistingFile;
//    QFileDialog::setFileMode(mode);
//    QString fileName = QFileDialog::getOpenFileName(this,
//        tr("Open Gcode"), QDir::homePath()+="/Desktop", tr("Gcode Files (*.gcode)"));
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    QString fileName = dialog.getOpenFileName(this,
        tr("Open Gcode"), QDir::homePath()+="/Desktop", tr("Gcode Files (*.gcode)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }
    QFileInfo fileInfo(file.fileName());
    QString filename(fileInfo.fileName());
    ui->filenameText->setText(filename);
    ui->filenameText->setVisible(1);
    QTextStream in (&file);
    QString searchString("estimated printing time");
    QString line;
    bool found = false;
    do {
        line = in.readLine();
        if (line.contains(searchString, Qt::CaseSensitive)) {
            qDebug() << line.remove(0, line.lastIndexOf('=')+2);

            found=true;
        }
    } while (!line.isNull());

    if (!found)
    {
        QMessageBox::information(this, tr("No print time info found!"),"No print time info found!");
    }

}
