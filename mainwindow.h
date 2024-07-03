#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QPixmap>
#include <QTextEdit>
#include <QMessageBox>
#include <QList>
#include <QStringList>
#include <QVector>

#include <algorithm>

#include <myutility.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    void on_AddAlphabetButton_clicked();

    void on_AddStatesButton_clicked();

    void on_CreateTableButton_clicked();

    void on_tableWidget_cellChanged(int row, int column);

private:
    Ui::MainWindow *ui;

    QStringList alp_;

    int numOfStates_;

    QVector<QVector<QStringList>> table_;
};
#endif // MAINWINDOW_H
