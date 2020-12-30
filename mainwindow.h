#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QVector>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int MatNum;
    int i=1;
    int *row=new int[MatNum];
    int *col=new int[MatNum];
    int n=1;
    int j=1;
    int inputStates=0;
    int *input=new int[n];
    void keyPressEvent(QKeyEvent *ev);
};

#endif // MAINWINDOW_H
