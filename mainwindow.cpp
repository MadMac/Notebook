#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Poistaa ikkunan reunat
    //setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    mainLayout = new QVBoxLayout;

    mainEdit = new QTextEdit;
    mainEdit->setMinimumSize(100, 100);

    headerFont = new QFont;
    headerFont->setPixelSize(18);

    header  = new QLabel;
    header->setText("Muistikirja");
    header->setFont(*headerFont);
    header->setAlignment(Qt::AlignRight);

    mainLayout->addWidget(header);
    mainLayout->addWidget(mainEdit);

    ui->centralWidget->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
