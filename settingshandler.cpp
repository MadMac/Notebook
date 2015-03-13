#include "settingshandler.h"

settingshandler::settingshandler()
{
    windowSize.setWidth(400);
    windowSize.setHeight(500);
    fontSize = 12;
    settingsFile.setFileName("settings.txt");
}

settingshandler::~settingshandler()
{

}

QSize settingshandler::getWindowSize()
{
    return windowSize;
}

void settingshandler::setWindowSize(QSize newSize)
{
    windowSize = newSize;
}

int settingshandler::getFontSize()
{
    return fontSize;
}

void settingshandler::setFontSize(int newFontSize)
{
    fontSize = newFontSize;
}

QString settingshandler::getNoteBookFile()
{
    return notebookFile;
}

void settingshandler::setNoteBookFile(QString filepath)
{
    notebookFile = filepath;
}

void settingshandler::saveSettings()
{
    settingsFile.open(QIODevice::WriteOnly | QIODevice::Text);
    settingsFile.resize(0);
    QTextStream out(&settingsFile);
    out << notebookFile + "\n";
    out << QString::number(windowSize.width()) + "\n";
    out << QString::number(windowSize.height()) + "\n";
    out << QString::number(getFontSize());
    settingsFile.close();
}

void settingshandler::loadSettings()
{
    QString line;
    qDebug() << settingsFile.fileName();
    if (QFile::exists(settingsFile.fileName()))
    {
        settingsFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream settingsIn(&settingsFile);

        notebookFile = settingsIn.readLine();
        windowSize.setWidth(settingsIn.readLine().toInt());
        windowSize.setHeight(settingsIn.readLine().toInt());
        fontSize = settingsIn.readLine().toInt();
        settingsFile.close();

    } else {
        qDebug() << "Settings file not found.";
    }



}
