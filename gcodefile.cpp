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

QString GcodeFile::getSlic3rTime(QString line)
{
    QString processedTime;
    QString time = line.remove(0, line.lastIndexOf('=')+2);
    processedTime = time;
    QString s=time;
    s =s.remove(0, s.lastIndexOf('m')+2);
    s=s.left(s.lastIndexOf('s'));
    int secondsInt = s.toInt();
    int hrsInt;
    int minsInt;
    QString h = time;
    if(h.contains('h'))
    {
        h =h.left(h.lastIndexOf('h'));
        hrsInt = h.toInt();
    }
    else
    {
        hrsInt = 0;
    }


    if(secondsInt>=30)
    {

        QStringList splitList = time.split(' ');
        int indexOfMins;
        if(hrsInt!=0)
        {
            indexOfMins = 1;
        }
        else
        {
            indexOfMins = 0;

        }
        QString m = time.split(' ')[indexOfMins];
        m=m.left(m.lastIndexOf('m'));
        minsInt = m.toInt();
        if(minsInt==59)
        {
            minsInt=0;
        }
        else
        {
            minsInt++;
        }



        processedTime=QString::number(hrsInt)+"h "+QString::number(minsInt)+"min";
    }
    else
    {
        processedTime=time.left(time.lastIndexOf('m')+1)+"in";
    }
    return processedTime;
}


void GcodeFile::extractTime()
{
    QTextStream in (&file);
    QString searchString("time");
    QString slic3rString("estimated");
    QMessageBox info(this->parentWidget());

    info.setStandardButtons(QMessageBox::StandardButton::NoButton);
    info.setText("Reading file(s) please wait.");
    info.setWindowModality(Qt::WindowModality::NonModal);

    info.setWindowFlag(Qt::WindowType::FramelessWindowHint);


    info.show();
    QCoreApplication::processEvents();
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
                        silentTime = getSlic3rTime(line);

                    }
                    else
                    {
                        normalTime = getSlic3rTime(line);
                    }
                }

                else
                {
                    if(line.contains("TIME:",Qt::CaseSensitive))
                    {
                        QString timeString = line.remove(0,line.lastIndexOf(':')+1);
                        int time2convert=timeString.toInt();
                        int h = time2convert/3600;
                        int m = (time2convert/60)%60;
                        int s = time2convert%60;
                        if (s>=30)
                        {
                            if(m==59)
                            {
                                m=0;
                                h++;
                            }
                            else
                            {
                                m++;
                            }

                        }
                        normalTime="";
                        if(h>0)normalTime+=QString::number(h)+"h ";
                        normalTime+=QString::number(m)+"min";
                        //normalTime = h + "h " + m +"m";


                    }
                    else if(line.contains("Build time:",Qt::CaseSensitive))
                    {
                        QString timeString = line.remove(0,line.lastIndexOf(':')+2);
                        QStringList list = timeString.split(' ');
                        //normalTime = list[0] + "h " + list[2] +"m";
                        int h=list[0].toInt();
                        int m = list[2].toInt();
                        normalTime = "";
                        if(h>0)normalTime+=QString::number(h)+"h ";
                        normalTime+=QString::number(m)+"min";
                    }
                }



            }
        }
    } while (!line.isNull());
    info.close();
    info.deleteLater();

}

void GcodeFile::saveRenamed(bool deleteOriginal, bool addAtEnd, char separator, bool silentMode)
{
    QString newFile=filePath.left(filePath.lastIndexOf("/",-1,Qt::CaseSensitive)+1);
    QString time2paste;
    if(silentMode && !silentTime.isEmpty())
    {
        time2paste=silentTime.replace(" ", "");
    }
    else
    {
        time2paste+=normalTime.replace(" ", "");
    }
    if(!addAtEnd)
    {
        newFile+=time2paste;
        if(separator<3)newFile+=separators[separator];
        newFile+=oriFileName;
    }
    else
    {
        newFile+=oriFileName.left(oriFileName.lastIndexOf('.'));
        if(separator<3)newFile+=separators[separator];
        newFile+=time2paste;
        newFile+=oriFileName.remove(0,oriFileName.lastIndexOf('.'));

    }

    if(deleteOriginal)
    {
        file.rename(newFile);
    }
    else
    {
        file.copy(newFile);
    }

    file.close();
}
