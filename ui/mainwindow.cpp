#include "ui/mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/addincome.h"
#include "ui/addexpense.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // currency initialization
    CurrConversion::addCurrency("RUB", 73.68);  // todo import coef from elsewhere
    CurrConversion::addCurrency("EUR", 1.22);  // todo import coef from elsewhere
    CurrConversion::addCurrency("GBP", 1.62);  // todo import coef from elsewhere
    CurrConversion::changeActiveCurrency("RUB");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonAddIncome_clicked()
{
    AddIncome addIncomeDialog;
    if (addIncomeDialog.exec() == QDialog::Accepted)
    {
        qDebug() << QString("inc todo getters from dialog");
    }
}

void MainWindow::on_buttonAddExpense_clicked()
{
    AddExpense addExpenseDialog;
    if (addExpenseDialog.exec() == QDialog::Accepted)
    {
        qDebug() << QString("exp todo getters from dialog");
    }
}
