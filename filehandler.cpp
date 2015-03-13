#include "filehandler.h"

filehandler::filehandler()
{

}

filehandler::~filehandler()
{
    file.close();
}

void filehandler::changeFilePath(QString path)
{
    file.setFileName(path);
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
