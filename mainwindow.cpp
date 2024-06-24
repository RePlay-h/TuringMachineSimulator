#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix{":img/img/pointer.png"};
    pix = pix.scaled(50, 50, Qt::KeepAspectRatio);
    ui->pointer->setPixmap(pix);
}

void MainWindow::start() {

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize)
{

}

