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
    MainWindow::setAcceptDrops(true);
    ui->openButton->setAcceptDrops(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dropEvent( QDropEvent *event )
{
    const QMimeData* mimeData = event->mimeData();

       if (mimeData->hasUrls())
       {
         QStringList pathList;
         QList<QUrl> urlList = mimeData->urls();

         for (int i = 0; i < urlList.size() && i < 32;++i)
         {
             foreach(QString str, QStringList(QString("GCODE,GCO,G,NGC").split(','))){
                 if(str.compare(QFileInfo(urlList.at(i).toLocalFile()).suffix().toUpper(), Qt::CaseSensitive) == 0)
                 {
                     pathList.append(urlList.at(i).toLocalFile());
                 }

             }

         }

         //qDebug() << pathList;
         openNewGcode(pathList[0]);

       }
}

void MainWindow::dragEnterEvent( QDragEnterEvent *event )
{
foreach(QUrl url, event->mimeData()->urls())
if (QFileInfo(url.toLocalFile()).suffix().toUpper()=="GCODE")
{
event->acceptProposedAction();
return;
}
}

void MainWindow::openNewGcode()
{
    ui->pushButton_2->setEnabled(false);
    ui->printTimeText->hide();
    ui->printSilentTimeText->hide();
    ui->newFilenameText->hide();
    ui->label_newFilename->hide();
    ui->label_normalTime->hide();
    ui->label_silentTime->hide();
    ui->filenameText->hide();

    GcodeFile test(this);
    ui->filenameText->setText(test.getOriFileName());
    //qDebug() << test.getOriFileName();
    ui->filenameText->show();



    if(!test.getNormalTime().isEmpty())
    {

        ui->printTimeText->setText(test.getNormalTime());
        ui->printTimeText->show();
        ui->label_normalTime->show();
        ui->pushButton_2->setEnabled(true);

    }
    if(!test.getSilentTime().isEmpty())
    {
        ui->printSilentTimeText->setText(test.getSilentTime());
        ui->printSilentTimeText->show();
        ui->label_silentTime->show();

    }
    if (test.getNormalTime().isEmpty())
    {
        QMessageBox::information(this, tr("No print time info found!"),"No print time info found!");
    }
    else if(ui->autoSaveCheckBox->isChecked())
    {
        test.saveRenamed(ui->deleteOriginalFileCheckBox->currentIndex());

    }

}

void MainWindow::openNewGcode(QString path)
{
    ui->pushButton_2->setEnabled(false);
    ui->printTimeText->hide();
    ui->printSilentTimeText->hide();
    ui->newFilenameText->hide();
    ui->label_newFilename->hide();
    ui->label_normalTime->hide();
    ui->label_silentTime->hide();
    ui->filenameText->hide();

    GcodeFile test(path,this);

    ui->filenameText->setText(test.getOriFileName());
    ui->filenameText->show();
    //qDebug() << test.getOriFileName();

    if(!test.getNormalTime().isEmpty())
    {

        ui->printTimeText->setText(test.getNormalTime());
        ui->printTimeText->show();
        ui->label_normalTime->show();
        ui->pushButton_2->setEnabled(true);

    }
    if(!test.getSilentTime().isEmpty())
    {
        ui->printSilentTimeText->setText(test.getSilentTime());
        ui->printSilentTimeText->show();
        ui->label_silentTime->show();

    }
    if (test.getNormalTime().isEmpty())
    {
        QMessageBox::information(this, tr("No print time info found!"),"No print time info found!");
    }
    else if(ui->autoSaveCheckBox->isChecked())
    {
        test.saveRenamed(ui->deleteOriginalFileCheckBox->currentIndex());

    }
}

void MainWindow::on_openButton_released()
{
    //if(file2Open.isOpen())file2Open.close();
    openNewGcode();

}

void MainWindow::on_pushButton_2_released()
{

    //file2Open.fileName().chop(file2Open.fileName().lastIndexOf('.'));
    //file2Open.copy("C:/Users/Kris/Desktop/aaaTEST/qt.gcode");


}
