#ifndef CHANGEATTRIBUTES_H
#define CHANGEATTRIBUTES_H

#include <QtWidgets>
#include "filehandler.h"
#include "settingshandler.h"


class MainWindow;

class changeattributes : public QDialog
{
    Q_OBJECT
public:
    explicit changeattributes(QWidget *parent = 0);
    ~changeattributes();

    void init(MainWindow *pWindow, settingshandler *handler);

signals:

public slots:

private slots:
    void closeWindow();
    void saveSettings();

private:

    bool movingWindow;
    QPoint mousePos;

    void paintEvent(QPaintEvent *);

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    QVBoxLayout *mainLayout;
    QHBoxLayout *topLayout;
    QGridLayout *formLayout;

    QLineEdit *widthEdit;
    QLineEdit *heightEdit;
    QLineEdit *fontSizeEdit;

    QPushButton *saveButton;

    QLabel *widthText;
    QLabel *heightText;
    QLabel *fontSizeText;

    QPushButton *exitButton;

    settingshandler *SettingsHandler;

    MainWindow *parentWindow;



};

#endif // CHANGEATTRIBUTES_H
