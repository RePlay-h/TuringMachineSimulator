#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(int displaySizeX, int displaySizeY, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , displaySizeX_(displaySizeX)
    , displaySizeY_(displaySizeY)
{
    ui->setupUi(this);
    qDebug() << displaySizeX_ << ' ' <<displaySizeY_;
    QPixmap pix{":img/img/pointer.png"}; // set arrow image
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



void MainWindow::on_AddAlphabetButton_clicked()
{
    QTextEdit *alphabet = new QTextEdit(nullptr);
    alphabet->resize(500, 500);
    alphabet->move((displaySizeX_ - 500)/2, (displaySizeY_ - 500)/2);


    QMessageBox *msg = new QMessageBox(alphabet);
    msg->setText("Please enter all characters separated by a space. When finished, press Enter");

    msg->show();
    alphabet->show();
}

