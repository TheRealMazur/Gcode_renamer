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
    ui->filenameText->show();
    ui->filenameText->setToolTip(filename);
    QTextStream in (&file);
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
                    //normalTime = QStringLiteral("%1h %2min %3s").arg(time2convert/3600,(time2convert/60)%60,time2convert%60);
                    qDebug() << timeString;
                }
            }



        }
    } while (!line.isNull());



    if(!normalTime.isEmpty())
    {
        ui->printTimeText->setText(normalTime);
        ui->printTimeText->show();
        ui->label_normalTime->show();

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
