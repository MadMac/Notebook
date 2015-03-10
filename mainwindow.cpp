#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Muistikirja");
    setWindowFlags(Qt::FramelessWindowHint);

    fontDatabase->addApplicationFont("fonts/Roboto-Regular.ttf");

    headerFont = new QFont;
    headerFont->setPixelSize(24);
    headerFont->setFamily("Roboto");
    headerFont->setLetterSpacing(QFont::AbsoluteSpacing, 2);

    normalFont = new QFont;
    normalFont->setPixelSize(12);
    normalFont->setFamily("Roboto");
    normalFont->setLetterSpacing(QFont::AbsoluteSpacing, 1);

    trayicon = new QSystemTrayIcon;
    setWindowIcon(QIcon("icons/systemtray.png"));
    trayicon->setIcon(QIcon("icons/systemtray.png"));
    trayicon->show();

    mainLayout = new QVBoxLayout;
    topLayout = new QHBoxLayout;
    bottomLayout = new QHBoxLayout;

    mainEdit = new QTextEdit;
    mainEdit->setMinimumSize(300, 500);
    mainEdit->setText(FileHandler.loadFile());
    mainEdit->setStyleSheet("background-color: #ffffff; border:0px;");
    mainEdit->setFrameStyle(0);
    mainEdit->setTextInteractionFlags(Qt::TextEditorInteraction);
    mainEdit->setFont(*normalFont);

    header  = new QLabel;
    header->setText("Muistikirja");
    header->setFont(*headerFont);
    header->setAlignment(Qt::AlignRight);
    header->setStyleSheet("margin-right: 20px; margin-top: 15px; margin-bottom:15px; border: 0px;");

    exitButton = new QPushButton;
    exitButton->setMaximumSize(15, 15);
    exitButton->setIcon(QIcon("icons/close.png"));
    exitButton->setStyleSheet("border: 0px");

    lockWindow = new QPushButton;
    lockWindow->setIcon(QIcon("icons/lock_open.png"));
    lockWindow->setCheckable(true);
    lockWindow->setStyleSheet("border: 0px");
    lockWindow->setMaximumSize(20, 20);

    folderButton = new QPushButton;
    folderButton->setMinimumSize(18, 13);
    folderButton->setMaximumSize(18, 13);
    folderButton->setIcon(QIcon("icons/folder.png"));
    folderButton->setStyleSheet("border: 0px");

    toSystemtray = new QPushButton;
    toSystemtray->setIcon(QIcon("icons/tosystemtray.png"));
    toSystemtray->setStyleSheet("border: 0px");
    toSystemtray->setMaximumSize(20, 20);

    topLayout->addWidget(exitButton);
    topLayout->setAlignment(Qt::AlignRight);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(header);
    mainLayout->addWidget(mainEdit);

    bottomLayout->addWidget(lockWindow);
    bottomLayout->addWidget(toSystemtray);
    bottomLayout->addWidget(folderButton);
    mainLayout->addLayout(bottomLayout);

    qDebug() << "FileHandler initialized";

    ui->centralWidget->setLayout(mainLayout);
    ui->centralWidget->setStyleSheet("Border:1px solid rgb(0, 0, 0)");

    connect(mainEdit, SIGNAL(textChanged()), this, SLOT(saveTrigger()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitTrigger()));
    connect(lockWindow, SIGNAL(clicked()), this, SLOT(lockWindowButton()));
    connect(toSystemtray, SIGNAL(clicked()), this, SLOT(hideWindow()));
    connect(folderButton, SIGNAL(clicked()), this, SLOT(openFileDialog()));

    connect(trayicon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    movingWindow = false;
    moveLocked = false;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCursor()));
    timer->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hideWindow()
{
    setVisible(false);
}

void MainWindow::openFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Avaa muistiinpanot"), "", tr("Text files (*.txt)"));
    if (filePath != "")
    {
        FileHandler.changeFilePath(filePath);
        mainEdit->setText(FileHandler.loadFile());
        mainEdit->setFocus();
    }
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick)
    {
        qDebug() << "Test";
        setVisible(true);
        raise();
        QApplication::setActiveWindow(this);
    }
}

void MainWindow::updateCursor()
{
    if (movingWindow && !moveLocked)
    {
        setCursor(Qt::ClosedHandCursor);

    } else {
        setCursor(Qt::ArrowCursor);
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QPen(QColor(227, 227, 227), 15));
    painter.drawLine(QPoint(20, 16), QPoint(270, 16));
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    mousePos = e->pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    movingWindow = false;
}

void MainWindow::lockWindowButton()
{
    if (lockWindow->isChecked())
    {
        lockWindow->setIcon(QIcon("icons/lock_closed.png"));
        moveLocked = true;

    } else {
        lockWindow->setIcon(QIcon("icons/lock_open.png"));
        moveLocked = false;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    QPoint mouseDiff;
    QPoint newPos;
    if (e->buttons() && Qt::LeftButton)
    {
        if (e->pos().x() > 15 && e->pos().x() < 280 && e->pos().y() > 10 && e->pos().y() < 30)
        {
            movingWindow = true;

        }
    }

    if (movingWindow && !moveLocked)
    {
        mouseDiff = e->pos() - mousePos;
        newPos = this->pos() + mouseDiff;

        this->move(newPos);
    }

    qDebug() << mouseDiff;
}

void MainWindow::saveTrigger()
{
    FileHandler.saveFile(mainEdit->document());
}

void MainWindow::exitTrigger()
{
    QApplication::quit();
}
