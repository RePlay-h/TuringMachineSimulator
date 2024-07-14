#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , alp_{}
    , numOfStates_{0}
    , mch_{}
    , table_{}
{
    ui->setupUi(this);


    QPixmap pix{":img/img/pointer.png"}; // set arrow image
    pix = pix.scaled(50, 50, Qt::KeepAspectRatio);
    ui->pointer->setPixmap(pix);

    //  Customize the Ribbon
    for(int i = -LENOFCOMMANDLINE; i < LENOFCOMMANDLINE+1; ++i) {
        ui->CommandLine->addItem("  "); // add item number
        ui->CommandLine->item(i+LENOFCOMMANDLINE)->setSizeHint({50, 50});
    }
    ui->CommandLine->scrollToItem(ui->CommandLine->item(LENOFCOMMANDLINE-8)); // move on to the central element of the Ribbon
    ui->CommandLine->setCurrentItem(ui->CommandLine->item(LENOFCOMMANDLINE));
    ui->CommandLine->show();


    ui->EnterWordLine->setReadOnly(true);
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
            table_[i] = QVector<Сonfiguration>(alp_.size(), Сonfiguration(0,0,' '));
        }
        ui->CreateTableButton->setEnabled(false);
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

        // save table data
        table_[row][column].state = cell[2].toInt();

        if (cell[1] == "L") {
            table_[row][column].mv = -1;
        }
        if (cell[1] == "N") {
            table_[row][column].mv = 0;
        }
        if (cell[1] == "R") {
            table_[row][column].mv = 1;
        }

        table_[row][column].word = cell[0][0];



        qDebug() << "TABLE IS UPDATED"; //TODO
    }
}


// go to element number 0
void MainWindow::on_ToCenterButton_clicked()
{
    ui->CommandLine->scrollToItem(ui->CommandLine->item(0));
    ui->CommandLine->scrollToItem(ui->CommandLine->item(LENOFCOMMANDLINE+7));
}


//
void MainWindow::on_CommandLine_itemDoubleClicked(QListWidgetItem *item)
{
    //make the line below the ribbon possible for text entry
    ui->EnterWordLine->setReadOnly(false);
    // activate the line under the ribbon
    ui->EnterWordLine->setFocus();
}


void MainWindow::on_EnterWordLine_returnPressed()
{
    // get word from line
    QString word = ui->EnterWordLine->text();

    if(!alp_.contains(word)) {
        QMessageBox::warning(nullptr, "Ooops...", "Enter a word that is in the alphabet");
    }
    else {
        ui->CommandLine->currentItem()->setText(" " + word);
    }
    ui->EnterWordLine->clear();
    ui->EnterWordLine->setReadOnly(true);

}
// A slot that calls Machine when you need to move to another cell
void MainWindow::MoveTo(int step) {
    QListWidgetItem *item = ui->CommandLine->currentItem();

    int st = ui->CommandLine->currentIndex().row() + step; // calculate a new cell
    qDebug() << "STEP IS: " << st;
    ui->CommandLine->setCurrentItem(ui->CommandLine->item(st));
    ui->CommandLine->scrollToItem(ui->CommandLine->item(st));

    ui->CommandLine->show();
}

// A slot that places a new word in the current cell
void MainWindow::ChangeItem(QChar word) {
    qDebug() << "SET TEXT" << word;
    ui->CommandLine->currentItem()->setText(" " + QString(word));
}

// Initial settings of the main window
void MainWindow::on_RunButton_clicked()
{
    qDebug() << "RunButton clicked";

    // disable all buttons on the main window while the program is running
    ui->tableWidget->setEnabled(false);
    ui->RunButton->setEnabled(false);
    ui->alphabet->setEnabled(false);
    ui->numOfStates->setEnabled(false);
    ui->AddAlphabetButton->setEnabled(false);
    ui->AddStatesButton->setEnabled(false);
    ui->CreateTableButton->setEnabled(false);
    ui->ToCenterButton->setEnabled(false);
    ui->EnterWordLine->setEnabled(false);


    connect(&mch_, &Machine::MoveTo, this, &MainWindow::MoveTo);
    connect(&mch_, &Machine::ChangeItem, this, &MainWindow::ChangeItem);
    connect(this, &MainWindow::GetWord, &mch_, &Machine::GetWord);
    connect(&mch_, &Machine::StopCircle, this, &MainWindow::StopCircle);

    ui->CommandLine->setCurrentItem(ui->CommandLine->item(1000));
    on_ToCenterButton_clicked();
    ui->CommandLine->show();

    mch_.ResetMachine(); // Reset word and machine status
    mch_.Init(&table_, &alp_);

    StartCircle();
}

void MainWindow::StartCircle() {
    while(!isStopCircle) {
        qDebug() << "TEXT SIZE: " << ui->CommandLine->currentItem()->text().size();
        mch_.GetWord(ui->CommandLine->currentItem()->text()[1]);
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
    isStopCircle = false;
}

// A slot that stops the machine
void MainWindow::StopCircle() {
    ui->tableWidget->setEnabled(true);
    ui->RunButton->setEnabled(true);
    ui->alphabet->setEnabled(true);
    ui->numOfStates->setEnabled(true);
    ui->AddAlphabetButton->setEnabled(true);
    ui->AddStatesButton->setEnabled(true);
    ui->CreateTableButton->setEnabled(true);
    ui->ToCenterButton->setEnabled(true);
    ui->EnterWordLine->setEnabled(true);

    ui->CommandLine->setCurrentItem(ui->CommandLine->item(1000));
    on_ToCenterButton_clicked();
    ui->CommandLine->show();

    disconnect(&mch_, &Machine::MoveTo, this, &MainWindow::MoveTo);
    disconnect(&mch_, &Machine::ChangeItem, this, &MainWindow::ChangeItem);
    disconnect(this, &MainWindow::GetWord, &mch_, &Machine::GetWord);
    disconnect(&mch_, &Machine::StopCircle, this, &MainWindow::StopCircle);

    isStopCircle = true;
}
