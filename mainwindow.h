#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define LENOFCOMMANDLINE 1000


#include <QMainWindow>
#include <QPixmap>
#include <QTextEdit>
#include <QMessageBox>
#include <QList>
#include <QListWidget>
#include <QTime>

#include <algorithm>
#include <chrono>
#include <thread>


#include "machine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void StartCircle();

signals:
    void GetWord(QChar word);


private slots:

    void on_AddAlphabetButton_clicked();

    void on_AddStatesButton_clicked();

    void on_CreateTableButton_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    void on_ToCenterButton_clicked();

    void on_CommandLine_itemDoubleClicked(QListWidgetItem *item);

    void on_EnterWordLine_returnPressed();

    void on_RunButton_clicked();

    void MoveTo(int step);

    void ChangeItem(QChar word);

    void StopCircle();
private:
    Ui::MainWindow *ui;

    QStringList alp_;

    int numOfStates_;

    Machine mch_;

    QVector<QVector<Сonfiguration>> table_;

    bool isStopCircle;
};
#endif // MAINWINDOW_H
