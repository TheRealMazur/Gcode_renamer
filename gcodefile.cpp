#include "gcodefile.h"

GcodeFile::GcodeFile(QString fileName, QWidget* parent): QMainWindow(parent)
{
    //filePath = fileName;
    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());

        //GcodeFile::~GcodeFile();
        return;
    }else
    {
        filePath = fileName;
        QFileInfo fileInfo(file);
        oriFileName = fileInfo.fileName();
        normalTime="";
        silentTime="";
        extractTime();
    }


}

QString GcodeFile::getOriFileName()
{
    return oriFileName;
}

QString GcodeFile::getNormalTime()
{
    return normalTime;
}

QString GcodeFile::getSilentTime()
{
    return silentTime;
}

GcodeFile::GcodeFile( QWidget* parent): QMainWindow(parent)
{
    QFileDialog dialog(this);
    filePath = dialog.getOpenFileName(this,
                                      tr("Open Gcode"), QDir::homePath()+="/Desktop", tr("Gcode Files (*.gcode *.gco *.g *.ngc)"));
    file.setFileName(filePath);
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());

        //GcodeFile::~GcodeFile();
        return;
    }
    QFileInfo fileInfo(file);
    oriFileName = fileInfo.fileName();
    normalTime="";
    silentTime="";
    extractTime();
}

GcodeFile::~GcodeFile()
{
    if(file.isOpen())
    {
        file.close();
    }
}

void GcodeFile::extractTime()
{
    QTextStream in (&file);
    QString searchString("time");
    QString slic3rString("estimated");
    QString line;
    do {
        line = in.readLine();
        if(line[0]==';')
        //if(line.startsWith(';', Qt::CaseSensitive))
        {
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
        }
    } while (!line.isNull());

}

void GcodeFile::saveRenamed(bool deleteOriginal)
{
    if(deleteOriginal)
    {
        file.rename(filePath.left(filePath.lastIndexOf("/",-1,Qt::CaseSensitive)+1)+"renamed.gcode");
        //qDebug() << filePath.left(filePath.lastIndexOf("/",-1,Qt::CaseSensitive)+1)+"renamed.gcode";
        file.close();
    }
    else
    {
        file.copy(filePath.left(filePath.lastIndexOf("/",-1,Qt::CaseSensitive)+1)+"copied.gcode");
        //qDebug() << filePath.left(filePath.lastIndexOf("/",-1,Qt::CaseSensitive)+1)+"copied.gcode";
        file.close();
    }

    //file.rename()

}
