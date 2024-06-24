#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void start();

    ~MainWindow();

private slots:
    void on_MainWindow_iconSizeChanged(const QSize &iconSize);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
