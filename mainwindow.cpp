#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();
    ui->statusBar->addPermanentWidget(new QLabel(QString("Hint: You can drag & drop files!")));     //had to change it to permanent, because menu was hiding it
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
    saveSettings();
    delete ui;
}

void MainWindow::loadSettings()
{

    QSettings settings(QSettings::NativeFormat, QSettings::UserScope,"Gcode_Renamer","Gcode_Renamer");

    if(settings.childGroups().contains("settings"))
    {
        settings.beginGroup("settings");
        ui->timePlaceComboBox->setCurrentIndex(settings.value("timePlace","0").toInt());
        ui->separatorComboBox->setCurrentIndex(settings.value("separator","0").toInt());
        ui->deleteOriginalFileComboBox->setCurrentIndex(settings.value("delete","0").toInt());
        ui->autoSaveCheckBox->setChecked(settings.value("autoSave", "false").toBool());
        ui->silentModeCheckBox->setChecked(settings.value("silentMode", "false").toBool());
        settings.endGroup();
    }

}

void MainWindow::saveSettings()
{
     QSettings settings(QSettings::NativeFormat, QSettings::UserScope,"Gcode_Renamer","Gcode_Renamer");
     settings.beginGroup("settings");
     settings.setValue("timePlace", ui->timePlaceComboBox->currentIndex());
     settings.setValue("separator", ui->separatorComboBox->currentIndex());
     settings.setValue("delete", ui->deleteOriginalFileComboBox->currentIndex());
     settings.setValue("autoSave", ui->autoSaveCheckBox->isChecked());
     settings.setValue("silentMode", ui->silentModeCheckBox->isChecked());
     settings.endGroup();
     settings.sync();

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
         if(pathList.size() > 1)
         {
             if(ui->autoSaveCheckBox->isChecked())
             {
                 for(int i = 0; i< pathList.size(); i++)
                 {
                     openNewGcode(pathList[i]);
                 }
             }
             else
             {
                 openNewGcode(pathList[0]);
             }
         }
         else
         {
             openNewGcode(pathList[0]);
         }



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


    //GcodeFile test(path,this);
    loadedGcodeFile = new GcodeFile(path,this);

    ui->filenameText->setText(loadedGcodeFile->getOriFileName());
    ui->filenameText->show();

    if(!loadedGcodeFile->getNormalTime().isEmpty())
    {

        ui->printTimeText->setText(loadedGcodeFile->getNormalTime());
        ui->printTimeText->show();
        ui->label_normalTime->show();
        ui->pushButton_2->setEnabled(true);

    }
    if(!loadedGcodeFile->getSilentTime().isEmpty())
    {
        ui->printSilentTimeText->setText(loadedGcodeFile->getSilentTime());
        ui->printSilentTimeText->show();
        ui->label_silentTime->show();

    }
    if (loadedGcodeFile->getNormalTime().isEmpty())
    {
        QMessageBox::information(this, tr("No print time info found!"),"No print time info found!");
    }
    else
    {
        ui->newFilenameText->setText(loadedGcodeFile->getNewName(ui->timeFormatComboBox->currentIndex(),ui->timePlaceComboBox->currentIndex(),ui->separatorComboBox->currentIndex(),ui->silentModeCheckBox->isChecked()));
        ui->label_newFilename->show();
        ui->newFilenameText->show();
        if(ui->autoSaveCheckBox->isChecked())
        {
            saveNewGcode();

        }
    }
}

void MainWindow::saveNewGcode()
{
    loadedGcodeFile->saveRenamed(ui->timeFormatComboBox->currentIndex(),ui->deleteOriginalFileComboBox->currentIndex(),ui->timePlaceComboBox->currentIndex(),ui->separatorComboBox->currentIndex(), ui->silentModeCheckBox->isChecked());
}

void MainWindow::openActionTriggerred()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Gcode file"), "", tr("Gcode files (*.gcode)"));
    if(fileName != ""){
        openNewGcode(fileName);
    }
}

void MainWindow::updateNewFilename()
{
    if(loadedGcodeFile)
    {
        if(!(loadedGcodeFile->getNormalTime().isEmpty()))
        {
            ui->newFilenameText->setText(loadedGcodeFile->getNewName(ui->timeFormatComboBox->currentIndex(),ui->timePlaceComboBox->currentIndex(),ui->separatorComboBox->currentIndex(),ui->silentModeCheckBox->isChecked()));
        }
    }
}

void MainWindow::on_openButton_released()
{
    openActionTriggerred();
}

void MainWindow::on_pushButton_2_released()
{
    saveNewGcode();
}

void MainWindow::on_actionOpen_triggered()
{
    openActionTriggerred();
}

void MainWindow::on_silentModeCheckBox_stateChanged(int)
{
    updateNewFilename();
}

void MainWindow::on_separatorComboBox_currentIndexChanged(int )
{
    updateNewFilename();
}

void MainWindow::on_timePlaceComboBox_currentIndexChanged(int )
{
    updateNewFilename();
}

void MainWindow::on_timeFormatComboBox_currentIndexChanged(int )
{
    updateNewFilename();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox;
    msgBox.about(this,"About","<img src=\":/coffee.png\" alt=\"Buy me a Beer!\">");
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox msgBox;
    msgBox.aboutQt(this,"About Qt");
}
