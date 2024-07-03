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

MainWindow::~MainWindow()
{
    delete ui;
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
        numOfStates_++;
        alp_.push_front(" ");

        // set table size

        ui->tableWidget->setColumnCount(alp_.size());
        ui->tableWidget->setRowCount(numOfStates_);

        // create a special QStringList in which the states will be stored: q0, q1, q2, ...
        QStringList strStates;

        for(int i = 0; i < numOfStates_; ++i) {
            strStates.append("q" + QString::number(i));
        }

        // set header labels
        ui->tableWidget->setVerticalHeaderLabels(strStates);
        ui->tableWidget->setHorizontalHeaderLabels(alp_);
        ui->tableWidget->show();

        table_.resize(numOfStates_);

        for(int i = 0; i < numOfStates_; ++i) {
            table_[i].resize(alp_.size());
        }

        qDebug() << "TABLE CREATE"; // TODO
    }
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    QStringList cell = ui->tableWidget->item(row, column)->text().split("/");

    if(!alp_.contains(cell[0]) || cell.size() > 3 || cell.size() < 3 || cell[2].toInt() > numOfStates_ || cell[2].toInt() < 0) {
        QMessageBox::warning(nullptr, "Ooops...", "Enter the string correctly");
        ui->tableWidget->removeCellWidget(row, column);
    }
    else {
        table_[row][column] = std::move(cell);
        qDebug() << "TABLE IS UPDATED";
    }
}

