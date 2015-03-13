#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "filehandler.h"
#include "changeattributes.h"
#include "settingshandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateWindow();


private slots:
    void saveTrigger();
    void exitTrigger();
    void lockWindowButton();
    void updateCursor();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void hideWindow();

    void openFileDialog();

    void openAttributesWindow();



private:
    Ui::MainWindow *ui;

    bool movingWindow;
    bool moveLocked;

    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void update();

    QVBoxLayout *mainLayout;
    QHBoxLayout *topLayout;
    QHBoxLayout *bottomLayout;
    QLabel *header;
    QFont *headerFont;
    QFont *normalFont;
    QTextEdit *mainEdit;
    QPushButton *exitButton;
    QPushButton *lockWindow;
    QPushButton *toSystemtray;
    QPushButton *folderButton;
    QPushButton *attributesButton;
    QFontDatabase *fontDatabase;

    QSystemTrayIcon *trayicon;

    QTimer *timer;

    filehandler FileHandler;

    QPoint mousePos;

    changeattributes *ChangeAttributesWindow;
    settingshandler SettingsHandler;




};

#endif // MAINWINDOW_H
