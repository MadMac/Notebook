#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Notebook");
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

    mainLayout = new QVBoxLayout;
    topLayout = new QHBoxLayout;
    bottomLayout = new QHBoxLayout;

    setFixedSize(500,600);

    mainEdit = new QTextEdit;
    mainEdit->setFixedSize(480, 475);


    mainEdit->setStyleSheet("background-color: #ffffff; border:0px;");
    mainEdit->setFrameStyle(0);
    mainEdit->setTextInteractionFlags(Qt::TextEditorInteraction);
    mainEdit->setFont(*normalFont);
    mainEdit->verticalScrollBar()->setMaximumWidth(5);
    mainEdit->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { background-color: #ffffff; }"
                                                 "QScrollBar::handle:vertical { border: 0px; background-color: #F5F5F5; border-radius: 2px; }");

    header  = new QLabel;
    header->setText("Notebook");
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
    lockWindow->setToolTip("Locks window movement");

    folderButton = new QPushButton;
    folderButton->setMinimumSize(18, 13);
    folderButton->setMaximumSize(18, 13);
    folderButton->setIcon(QIcon("icons/folder.png"));
    folderButton->setStyleSheet("border: 0px");
    folderButton->setToolTip("Open file");

    toSystemtray = new QPushButton;
    toSystemtray->setIcon(QIcon("icons/tosystemtray.png"));
    toSystemtray->setStyleSheet("border: 0px");
    toSystemtray->setMaximumSize(20, 20);
    toSystemtray->setToolTip("Hides to tray");

    attributesButton = new QPushButton;
    attributesButton->setIcon(QIcon("icons/attributes.png"));
    attributesButton->setStyleSheet("border: 0px");
    attributesButton->setMaximumSize(13, 13);
    attributesButton->setToolTip("Open window attributes");

    topLayout->addWidget(exitButton);
    topLayout->setAlignment(Qt::AlignRight);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(header);
    mainLayout->addWidget(mainEdit);

    bottomLayout->addWidget(lockWindow);
    bottomLayout->addWidget(toSystemtray);
    bottomLayout->addWidget(folderButton);
    bottomLayout->addWidget(attributesButton);
    mainLayout->addLayout(bottomLayout);

    ui->centralWidget->setLayout(mainLayout);
    ui->centralWidget->setStyleSheet("Border:1px solid rgb(0, 0, 0)");

    connect(mainEdit, SIGNAL(textChanged()), this, SLOT(saveTrigger()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitTrigger()));
    connect(lockWindow, SIGNAL(clicked()), this, SLOT(lockWindowButton()));
    connect(toSystemtray, SIGNAL(clicked()), this, SLOT(hideWindow()));
    connect(folderButton, SIGNAL(clicked()), this, SLOT(openFileDialog()));
    connect(attributesButton, SIGNAL(clicked()), this, SLOT(openAttributesWindow()));

    connect(trayicon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    movingWindow = false;
    moveLocked = false;

    SettingsHandler.loadSettings();
    FileHandler.changeFilePath(SettingsHandler.getNoteBookFile());
    updateWindow();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCursor()));
    timer->start(1);


    ChangeAttributesWindow = new changeattributes();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete ChangeAttributesWindow;
}

void MainWindow::hideWindow()
{
    trayicon->show();
    setVisible(false);
}

void MainWindow::openAttributesWindow()
{

    if (ChangeAttributesWindow->isHidden())
    {

        ChangeAttributesWindow->init(this, &SettingsHandler);

        ChangeAttributesWindow->show();
    } else {

        ChangeAttributesWindow->raise();
    }
}

void MainWindow::openFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open notes"), "", tr("Text files (*.txt)"));
    if (filePath != "")
    {
        SettingsHandler.setNoteBookFile(filePath);
        updateWindow();
        FileHandler.changeFilePath(SettingsHandler.getNoteBookFile());
        mainEdit->setText(FileHandler.loadFile());
        mainEdit->setFocus();
    }
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick)
    {
        setVisible(true);
        trayicon->hide();
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
    if (!moveLocked)
    {
        QPainter painter(this);

        painter.setPen(QPen(QColor(227, 227, 227), 15));
        painter.drawLine(QPoint(20, 16), QPoint(size().width()-50, 16));
    }
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
        repaint();
    } else {
        lockWindow->setIcon(QIcon("icons/lock_open.png"));
        moveLocked = false;
        repaint();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
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

    if (movingWindow && !moveLocked)
    {
        mouseDiff = e->pos() - mousePos;
        newPos = this->pos() + mouseDiff;

        this->move(newPos);
    }

    //qDebug() << mouseDiff;
}

void MainWindow::updateWindow()
{
    SettingsHandler.saveSettings();
    setFixedSize(SettingsHandler.getWindowSize());
    mainEdit->setFixedSize(size().width()-15, size().height()-135);
    normalFont->setPixelSize(SettingsHandler.getFontSize());
    mainEdit->setFont(*normalFont);
    mainEdit->setText(FileHandler.loadFile());

    repaint();
}

void MainWindow::saveTrigger()
{
    FileHandler.saveFile(mainEdit->document());
}

void MainWindow::exitTrigger()
{
    QApplication::quit();
}
