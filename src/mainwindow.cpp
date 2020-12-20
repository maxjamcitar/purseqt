#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addincome.h"
#include "addexpense.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonAddIncome_clicked()
{
    AddIncome* addIncomeDialog = new AddIncome();
    addIncomeDialog->exec();
}

void MainWindow::on_buttonAddExpense_clicked()
{
    AddExpense* addExpenseDialog = new AddExpense();
    addExpenseDialog->exec();
}
