#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QFile>
#include <QTextStream>
#include <QTextDocument>
#include <QDebug>
#include <iostream>

class filehandler
{
public:
    filehandler();
    ~filehandler();

    QString loadFile();
    void saveFile(QTextDocument *allText);


private:
    QFile file;

};

#endif // FILEHANDLER_H
