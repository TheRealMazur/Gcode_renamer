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

#include <QDebug>


class GcodeFile : public QMainWindow
{
    Q_OBJECT
    QFile file;
    QString filePath, oriFileName, normalTime, silentTime;
public:
    explicit GcodeFile(QString fileName, QWidget * parent = nullptr);
    explicit GcodeFile(QWidget * parent = nullptr);
    ~GcodeFile();
    void extractTime();
    QString getOriFileName();
    QString getNormalTime();
    QString getSilentTime();
    void saveRenamed(bool deleteOriginal);

signals:

public slots:
};

#endif // GCODEFILE_H
