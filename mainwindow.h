#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//public slots:
//    void onAction();
private:
    Ui::MainWindow *ui;

public slots:
    void onPageChange(bool isNext);
};

#endif // MAINWINDOW_H
