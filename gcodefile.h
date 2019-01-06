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
    char separators[3]={'_','-','.'};
public:
    explicit GcodeFile(QString fileName, QWidget * parent = nullptr);
    explicit GcodeFile(QWidget * parent = nullptr);
    ~GcodeFile();
    void extractTime();
    QString getOriFileName();
    QString getNormalTime();
    QString getSilentTime();
    void saveRenamed(bool deleteOriginal, bool addAtEnd, char separator, bool silentMode = false);

signals:

public slots:
};

#endif // GCODEFILE_H
