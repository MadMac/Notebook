#include "filehandler.h"

filehandler::filehandler()
{
    settingsFile.setFileName("asetukset.txt");

    settingsFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream settingsIn(&settingsFile);
    QString filePath;

    while(!settingsIn.atEnd()) {
        filePath = settingsIn.readLine();
    }

    settingsFile.close();

    filePath.trimmed();
    file.setFileName(filePath);
    qDebug() << filePath;

}

filehandler::~filehandler()
{
    file.close();
    settingsFile.close();
}

void filehandler::changeFilePath(QString path)
{
    file.setFileName(path);

    settingsFile.open(QIODevice::WriteOnly | QIODevice::Text);
    settingsFile.resize(0);
    QTextStream out(&settingsFile);
    out << path;
    settingsFile.close();
}

QString filehandler::loadFile()
{
    QString line;

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString allText;


    while (!in.atEnd()) {
        line = in.readLine();
        allText.append(line);
        allText.append("\n");

    }

    file.close();
    allText = allText.trimmed();
    return allText;
}

void filehandler::saveFile(QTextDocument *allText)
{
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.resize(0);
    qDebug() << QString(allText->toPlainText());
    QTextStream out(&file);
    out << allText->toPlainText();
    file.close();
}
