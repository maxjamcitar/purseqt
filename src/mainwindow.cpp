#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addincome.h"

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
