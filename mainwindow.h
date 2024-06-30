#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QTextEdit>
#include <QMessageBox>

#include <memory>

#include <myutility.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int displaySizeX, int displaySizeY, QWidget *parent = nullptr);

    void start();

    ~MainWindow();

private slots:
    void on_MainWindow_iconSizeChanged(const QSize &iconSize);


    void on_AddAlphabetButton_clicked();

private:
    Ui::MainWindow *ui;
    int displaySizeX_;
    int displaySizeY_;
};
#endif // MAINWINDOW_H
