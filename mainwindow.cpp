#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , alp_{}
    , numOfStates_{0}
{
    ui->setupUi(this);
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
    // get text of items
    QString alp_str = ui->alphabet->text();
    if (alp_str.size() == 0) {
        QMessageBox::warning(nullptr, "Ooops...", "You must enter at least one character");
    }
    else {
        // get list of items
        alp_  = alp_str.split(" ");
        // remove all empty elements
        alp_.removeIf([](QString ch) {return ch == "";});

        // check all elements for repetition
        for(auto& item : alp_) {
            if(alp_.count(item) > 1) {
                alp_.clear();
                QMessageBox::warning(nullptr, "Ooops...", "Elements must not be repeated!");
                break;
            }
        }

        qDebug() << "Alphabet: " << alp_; //TODO
    }
}


void MainWindow::on_AddStatesButton_clicked()
{
    bool ok;
    numOfStates_ = ui->numOfStates->text().toInt(&ok);

    if(ok) {
        qDebug() << "NumOfStates: " << numOfStates_; //TODO
    }
    else {
        QMessageBox::warning(nullptr, "Ooops...", "Enter a valid numeric value");
    }
}


void MainWindow::on_CreateTableButton_clicked()
{
    if(numOfStates_ == 0 || alp_.empty()) {
        QMessageBox::warning(nullptr, "Ooops...", "Please enter alphabet or number of states");
    }
    else {
        ui->tableWidget->setColumnCount(numOfStates_);
        ui->tableWidget->setRowCount(alp_.size());

        QStringList strStates;

        for(int i = 0; i < numOfStates_; ++i) {
            strStates.append("q" + QString::number(i));
        }

        ui->tableWidget->setVerticalHeaderLabels(alp_);
        ui->tableWidget->setHorizontalHeaderLabels(strStates);
        ui->tableWidget->show();
        qDebug() << "TABLE CREATE"; // TODO
    }
}

