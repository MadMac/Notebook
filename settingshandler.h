#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H

#include <QSize>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class settingshandler
{
public:
    settingshandler();
    ~settingshandler();
    QSize getWindowSize();
    void setWindowSize(QSize newSize);
    int getFontSize();
    void setFontSize(int newFontSize);

    QString getNoteBookFile();
    void setNoteBookFile(QString filepath);

    void loadSettings();
    void saveSettings();


private:
    QSize windowSize;
    int fontSize;
    QString notebookFile;

    QFile settingsFile;


};

#endif // SETTINGSHANDLER_H
