#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QMessageBox>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),currentAction(NoAction),isEmpty(true)
{
    setWindowIcon(QIcon(":/image/ico.png"));
    setIconSize(QSize(100,40));
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    connect(ui->ButtonAc,SIGNAL(clicked(bool)),this,SLOT(clear()));
    connect(ui->Buttonflag,SIGNAL(clicked(bool)),this,SLOT(negationClicked()));
    connect(ui->ButtonMod,SIGNAL(clicked(bool)),this,SLOT(percentageClicked()));
    connect(ui->ButtonPt,SIGNAL(clicked(bool)),this,SLOT(decimalPointClicked()));
    connect(ui->ButtonEq,SIGNAL(clicked(bool)),this,SLOT(evaluactionClicked()));

    connect(ui->ButtonAdd,SIGNAL(clicked(bool)),this,SLOT(actionChanged()));
    connect(ui->ButtonSub,SIGNAL(clicked(bool)),this,SLOT(actionChanged()));
    connect(ui->ButtonMul,SIGNAL(clicked(bool)),this,SLOT(actionChanged()));
    connect(ui->ButtonDiv,SIGNAL(clicked(bool)),this,SLOT(actionChanged()));

    connect(ui->Num0,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->Num1,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->Num2,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->Num3,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->Num4,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->Num5,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->Num6,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->Num7,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->Num8,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->Num9,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));

    connect(ui->actionAbout_Qt,SIGNAL(triggered(bool)),qApp,SLOT(aboutQt()));
    connect(ui->actionAbout,SIGNAL(triggered(bool)),this,SLOT(aboutApp()));
}

/*清除输入*/
void MainWindow::clear()
{
    currentAction = NoAction;
    currentNumber.clear();
    lastNumber.clear();
    isEmpty = true;
    displayNumber();
}

/*输入操作符*/
void MainWindow::actionChanged()
{
    if(currentNumber.size() == 0) {
        statusBar()->showMessage(tr("操作符之前必须有操作数"),3000);
        return ;
    }else {
        lastNumber = currentNumber;
        currentNumber = "0";
    }

    QPushButton *currentButton = qobject_cast<QPushButton*>(this->sender());
    if(currentButton) {
        isEmpty = false;
        if(currentButton == ui->ButtonAdd) {
            currentAction = AdditionFlag;
            statusBar()->showMessage(tr("输入了加号"),3000);
        }else if(currentButton == ui->ButtonSub) {
            currentAction = SubtractionFlag;
            statusBar()->showMessage(tr("输入了减号"),3000);
        }else if(currentButton == ui->ButtonMul) {
            currentAction = MultiplicationFlag;
            statusBar()->showMessage(tr("输入了乘号"),3000);
        }else if(currentButton == ui->ButtonDiv) {
            currentAction = DivisionFlag;
            statusBar()->showMessage(tr("输入了除号"),3000);
        }else{
            currentAction = NoAction;
        }
    }
}

/*输入数字,如果上次计算的结果还存在先清除掉*/
void MainWindow::inputNumber()
{
    if(lastNumber.size() == 0 && isEmpty == false) {
        this->clear();
    }
    QPushButton * currentButton = qobject_cast<QPushButton*>(this->sender());
    if(currentButton) {
        if(currentNumber == "0") {
            currentNumber.clear();
        }
        if(currentButton == ui->Num0)
        {
            currentNumber.append("0");
            statusBar()->showMessage(tr("输入了0"),3000);
        }else if(currentButton == ui->Num1)
        {
            currentNumber.append("1");
            statusBar()->showMessage(tr("输入了1"),3000);
        }
        else if(currentButton == ui->Num2)
        {
            currentNumber.append("2");
            statusBar()->showMessage(tr("输入了2"),3000);
        }
        else if(currentButton == ui->Num3)
        {
            currentNumber.append("3");
            statusBar()->showMessage(tr("输入了3"),3000);
        }
        else if(currentButton == ui->Num4)
        {
            currentNumber.append("4");
            statusBar()->showMessage(tr("输入了4"),3000);
        }
        else if(currentButton == ui->Num5)
        {
            currentNumber.append("5");
            statusBar()->showMessage(tr("输入了5"),3000);
        }
        else if(currentButton == ui->Num6)
        {
            currentNumber.append("6");
            statusBar()->showMessage(tr("输入了6"),3000);
        }
        else if(currentButton == ui->Num7)
        {
            currentNumber.append("7");
            statusBar()->showMessage(tr("输入了7"),3000);
        }
        else if(currentButton == ui->Num8)
        {
            currentNumber.append("8");
            statusBar()->showMessage(tr("输入了8"),3000);
        }
        else if(currentButton == ui->Num9)
        {
            currentNumber.append("9");
            statusBar()->showMessage(tr("输入了9"),3000);
        }
    }
    displayNumber();
}

/*在屏幕上显示数字*/
void MainWindow::displayNumber()
{
    ui->Ans->setText(currentNumber);
}

/*改变数字正负*/
void MainWindow::negationClicked()
{
    if(currentNumber.size() == 0 || currentNumber == "0") {
        currentNumber = "0";
    }else {
        if(currentNumber.at(0) == '-') {
            currentNumber.remove(0,1);
        }else{
            currentNumber.push_front("-");
        }
    }
    displayNumber();
    statusBar()->showMessage(tr("符号转换"));
}

/*百分比*/
void MainWindow::percentageClicked()
{
    if(currentNumber.size() == 0 || currentNumber == "0") {
        currentNumber = "0";
    }else {
        double number = currentNumber.toDouble() / 100;
        currentNumber = QString::number(number);
    }
    displayNumber();
    statusBar()->showMessage(tr("计算百分比"),3000);
}

/*加入小数点*/
void MainWindow::decimalPointClicked()
{
    if(currentNumber.size() == 0) {
        currentNumber = "0.";
    }else if(currentNumber.indexOf(".")==-1) {
        currentNumber.append(".");
    }
    displayNumber();
    statusBar()->showMessage(tr("输入了小数点"),3000);
}

/*计算结果*/
void MainWindow::evaluactionClicked()
{
    switch (currentAction) {
    case NoAction:
    {
        statusBar()->showMessage(tr("请选择一个运算操作"),3000);
        return;
        break;
    }
    case AdditionFlag:
    {
        currentNumber = QString::number(lastNumber.toDouble()+currentNumber.toDouble());
        break;
    }
    case SubtractionFlag:
    {
        currentNumber = QString::number(lastNumber.toDouble()-currentNumber.toDouble());
        break;
    }
    case MultiplicationFlag:
    {
        currentNumber = QString::number(lastNumber.toDouble()*currentNumber.toDouble());
        break;
    }
    case DivisionFlag:
    {
        currentNumber = QString::number(lastNumber.toDouble()/currentNumber.toDouble());
        break;
    }
    }
    lastNumber.clear();
    currentAction = NoAction;
    displayNumber();
    statusBar()->showMessage(tr("计算成功"),3000);
}
void MainWindow::aboutApp()
{
    QMessageBox::about(menuBar(),tr("About calculator"),\
                       tr("Author: akxxsb(Qsc)"
               "\nEmail: acvcla@gmail.com"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
