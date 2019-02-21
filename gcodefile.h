#ifndef GCODEFILE_H
#define GCODEFILE_H

#include <QMainWindow>
#include <QString>
#include <QIODevice>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
//#include <QWidget>
#include <QTextStream>
#include <QApplication>

#include <QDebug>


class GcodeFile : public QMainWindow
{
    Q_OBJECT
    QFile file;
    QString filePath, oriFileName, normalTime, silentTime;
    QString getSlic3rTime(QString line);
    QString translateTimeFormat(QString in, int timeFormat);
    char separators[3]={'_','-','.'};
public:
    explicit GcodeFile(QString fileName, QWidget * parent = nullptr);
    explicit GcodeFile(QWidget * parent = nullptr);
    ~GcodeFile();
    void extractTime();
    QString getOriFileName();
    QString getNormalTime();
    QString getSilentTime();
    QString getNewName(int timeFormat, bool addAtEnd, int separator, bool silentMode = false);
    void saveRenamed(int timeFormat, bool deleteOriginal, bool addAtEnd, int separator, bool silentMode = false);

signals:

public slots:
};

#endif // GCODEFILE_H
