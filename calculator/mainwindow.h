#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QString>

namespace Ui {
class MainWindow;
}

enum ActionFlag{
    NoAction,
    AdditionFlag,
    SubtractionFlag,
    MultiplicationFlag,
    DivisionFlag
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ActionFlag currentAction;
    QString lastNumber;
    QString currentNumber;
    bool isEmpty;

public slots:
    void clear();                         /*清除输入*/
    void actionChanged();                 /*输入操作符*/
    void inputNumber();                   /*输入数字,如果上次计算的结果还存在先清除掉*/
    void displayNumber();                 /*在屏幕上显示数字*/
    void negationClicked();               /*改变数字正负*/
    void percentageClicked();             /*百分比*/
    void decimalPointClicked();           /*加入小数点*/
    void evaluactionClicked();            /*计算结果*/
    void aboutApp();
};

#endif // MAINWINDOW_H
