#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->filenameText->hide();
    ui->printTimeText->hide();
    ui->printSilentTimeText->hide();
    ui->newFilenameText->hide();
    ui->label_newFilename->hide();
    ui->label_normalTime->hide();
    ui->label_silentTime->hide();
    ui->pushButton_2->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
    if(file2Open.isOpen())file2Open.close();
}

void MainWindow::on_openButton_released()
{
    if(file2Open.isOpen())file2Open.close();
    ui->pushButton_2->setEnabled(false);
    ui->printTimeText->hide();
    ui->printSilentTimeText->hide();
    ui->newFilenameText->hide();
    ui->label_newFilename->hide();
    ui->label_normalTime->hide();
    ui->label_silentTime->hide();
    ui->filenameText->hide();
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    QString fileName = dialog.getOpenFileName(this,
        tr("Open Gcode"), QDir::homePath()+="/Desktop", tr("Gcode Files (*.gcode)"));
    file2Open.setFileName(fileName);
    if (!file2Open.open(QIODevice::ReadOnly|QIODevice::Text)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file2Open.errorString());
                return;
            }
    QFileInfo fileInfo(file2Open.fileName());
    QString filename(fileInfo.fileName());
    ui->filenameText->setText(filename);
    ui->filenameText->show();
    ui->filenameText->setToolTip(filename);
    QTextStream in (&file2Open);
    QString searchString("time");
    QString slic3rString("estimated");
    QString normalTime = "", silentTime = "";
    QString line;

    do {
        line = in.readLine();
        if (line.contains(searchString, Qt::CaseInsensitive)) {
            if(line.contains(slic3rString,Qt::CaseSensitive))
            {
                if(line.contains("silent mode",Qt::CaseSensitive))
                {
                    silentTime = line.remove(0, line.lastIndexOf('=')+2);
                }
                else
                {
                    normalTime = line.remove(0, line.lastIndexOf('=')+2);
                }
            }

            else
            {
                if(line.contains("TIME:",Qt::CaseSensitive))
                {
                    QString timeString = line.remove(0,line.lastIndexOf(':')+1);
                    int time2convert=timeString.toInt();
                    QString h = QVariant(time2convert/3600).toString();
                    QString m = QVariant((time2convert/60)%60).toString();
                    QString s = QVariant(time2convert%60).toString();
                    normalTime = h + "h " + m +"min " + s+"s";

                }
            }



        }
    } while (!line.isNull());



    if(!normalTime.isEmpty())
    {
        qDebug() << normalTime;
        ui->printTimeText->setText(normalTime);
        ui->printTimeText->show();
        ui->label_normalTime->show();
        ui->pushButton_2->setEnabled(true);

    }
    if(!silentTime.isEmpty())
    {
        ui->printSilentTimeText->setText(silentTime);
        ui->printSilentTimeText->show();
        ui->label_silentTime->show();

    }
    if (normalTime.isEmpty())
    {
        QMessageBox::information(this, tr("No print time info found!"),"No print time info found!");
    }

}

void MainWindow::on_pushButton_2_released()
{

    //file2Open.fileName().chop(file2Open.fileName().lastIndexOf('.'));
    file2Open.copy("C:/Users/Kris/Desktop/aaaTEST/qt.gcode");


}
