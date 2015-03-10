#include "changeattributes.h"

changeattributes::changeattributes(QWidget *parent) : QDialog(parent)
{
    setFixedSize(250, 200);
    setWindowTitle("Muistikirja - Settings");
    setWindowFlags(Qt::FramelessWindowHint);

    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    setStyleSheet("QWidget { background-color: #ffffff; border:1px solid #000000; }");

    topLayout = new QHBoxLayout;
    topLayout->setAlignment(Qt::AlignTop | Qt::AlignRight);

    exitButton = new QPushButton;
    exitButton->setMaximumSize(15, 15);
    exitButton->setIcon(QIcon("icons/close.png"));
    exitButton->setStyleSheet("border: 0px");

    widthEdit = new QLineEdit;
    widthEdit->setFixedSize(100, 25);

    heightEdit = new QLineEdit;
    heightEdit->setFixedSize(100, 25);

    fontSizeEdit = new QLineEdit;
    fontSizeEdit->setFixedSize(100, 25);

    widthText = new QLabel;
    widthText->setText("Width:");
    widthText->setFixedSize(50, 25);
    widthText->setStyleSheet("border:0px;");

    heightText = new QLabel;
    heightText->setText("Height:");
    heightText->setFixedSize(50, 25);
    heightText->setStyleSheet("border:0px;");

    fontSizeText = new QLabel;
    fontSizeText->setText("Font size:");
    fontSizeText->setFixedSize(50, 25);
    fontSizeText->setStyleSheet("border:0px;");

    saveButton = new QPushButton;
    saveButton->setText("Save");
    saveButton->setFixedSize(50, 30);
    saveButton->setStyleSheet("margin-bottom: 10px;");

    formLayout = new QGridLayout;
    formLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    formLayout->addWidget(widthText, 0, 0);
    formLayout->addWidget(widthEdit, 0, 1);
    formLayout->addWidget(heightText, 1, 0);
    formLayout->addWidget(heightEdit, 1, 1);
    formLayout->addWidget(fontSizeText, 2, 0);
    formLayout->addWidget(fontSizeEdit, 2, 1);
    formLayout->addWidget(saveButton, 3, 1);
    formLayout->setVerticalSpacing(15);

    mainLayout->addLayout(topLayout);
    topLayout->addWidget(exitButton);
    mainLayout->addLayout(formLayout);

    connect(exitButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
}


changeattributes::~changeattributes()
{

}


void changeattributes::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QPen(QColor(227, 227, 227), 15));
    painter.drawLine(QPoint(20, 18), QPoint(size().width()-50, 18));

}

void changeattributes::closeWindow()
{
    close();
}

void changeattributes::mousePressEvent(QMouseEvent *e)
{
    mousePos = e->pos();
}

void changeattributes::mouseReleaseEvent(QMouseEvent *e)
{
    movingWindow = false;
}

void changeattributes::mouseMoveEvent(QMouseEvent *e)
{
    QPoint mouseDiff;
    QPoint newPos;
    if (e->buttons() && Qt::LeftButton)
    {
        if (e->pos().x() > 15 && e->pos().x() < size().width()-50 && e->pos().y() > 10 && e->pos().y() < 30)
        {
            movingWindow = true;

        }
    }

    if (movingWindow)
    {
        mouseDiff = e->pos() - mousePos;
        newPos = this->pos() + mouseDiff;

        this->move(newPos);
    }
}
