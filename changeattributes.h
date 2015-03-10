#ifndef CHANGEATTRIBUTES_H
#define CHANGEATTRIBUTES_H

#include <QtWidgets>

class changeattributes : public QDialog
{
    Q_OBJECT
public:
    explicit changeattributes(QWidget *parent = 0);
    ~changeattributes();

signals:

public slots:

private slots:
    void closeWindow();

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


    QFrame windowFrame;

    QPushButton *exitButton;
};

#endif // CHANGEATTRIBUTES_H
