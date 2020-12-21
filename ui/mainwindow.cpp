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
    CurrConversion::addCurrency("USD", 1);
    CurrConversion::addCurrency("EUR", 1.22);  // todo import coef from elsewhere
    CurrConversion::addCurrency("RUB", 73.68);  // todo import coef from elsewhere
    CurrConversion::addCurrency("GBP", 1.62);  // todo import coef from elsewhere
    CurrConversion::changeActiveCurrency("RUB");

    InitializeActCurrencyComboBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitializeActCurrencyComboBox()
{
    ui->comboBoxActiveCurrency->addItem(CurrConversion::activeCurrency);  // to make active curr on top
    for (auto iter = CurrConversion::currencyList.begin(); iter != CurrConversion::currencyList.end(); ++iter)
    {
        if (*iter != CurrConversion::activeCurrency)
            ui->comboBoxActiveCurrency->addItem(*iter);
    }
}

void MainWindow::showMngrInTable(const Manager& argMngr)
{
    auto mngrVec = argMngr.getVector();
    ui->tableTransactions->clearContents();
    ui->tableTransactions->setRowCount(mngrVec.size());

    for (auto i = 0; i < mngrVec.size(); ++i)
    {
        QSharedPointer<Transaction> iterTrans = mngrVec.at(i);

        // adding inc/exp
        QTableWidgetItem *twClassType = new QTableWidgetItem
                (iterTrans->getClassType());
        ui->tableTransactions->setItem(i,0,twClassType);

        // adding date
        QTableWidgetItem *twDate = new QTableWidgetItem
                (iterTrans->getDate().toString("dd/MM/yyyy"));
        ui->tableTransactions->setItem(i,1,twDate);

        // adding value
        Money transMoney (iterTrans->getPrice());
        QTableWidgetItem *twMoney = new QTableWidgetItem
                (transMoney.to_str(" "));
        ui->tableTransactions->setItem(i,2,twMoney);

        // adding comment
        QTableWidgetItem *twComment = new QTableWidgetItem
                (iterTrans->getComment());
        ui->tableTransactions->setItem(i,4,twComment);

        if (iterTrans->getClassType() == QString("Income"))
        {
            QSharedPointer<Income> iterInc = qSharedPointerDynamicCast<Income>(iterTrans);

            // adding source
            QTableWidgetItem *twSource = new QTableWidgetItem
                    (iterInc->getSource());
            ui->tableTransactions->setItem(i,3,twSource);
        }
        else if (iterTrans->getClassType() == QString("Expense"))
        {
            QSharedPointer<Expense> iterExp = qSharedPointerDynamicCast<Expense>(iterTrans);

            // adding goods
            QTableWidgetItem *twGoods = new QTableWidgetItem
                    (iterExp->getGoods());
            ui->tableTransactions->setItem(i,3,twGoods);
        }
    }
    qDebug() << argMngr.residual().to_str(" ");
}

void MainWindow::on_buttonAddIncome_clicked()
{
    AddIncome addIncomeDialog;
    if (addIncomeDialog.exec() == QDialog::Accepted)
    {
        QDate newDate = addIncomeDialog.getDate();
        Money newMoney = addIncomeDialog.getMoney();
        QString newSource = addIncomeDialog.getSource();
        QString newComment = addIncomeDialog.getComment();
        QSharedPointer<Income> newInc = QSharedPointer<Income>::create(newDate, newMoney, newComment, newSource);
        QSharedPointer<Transaction> newTrans = qSharedPointerDynamicCast<Transaction>(newInc);
        mainMngr.addEnd(newInc);

        showMngrInTable(mainMngr);
    }
}

void MainWindow::on_buttonAddExpense_clicked()
{
    AddExpense addExpenseDialog;
    if (addExpenseDialog.exec() == QDialog::Accepted)
    {
        QDate newDate = addExpenseDialog.getDate();
        Money newMoney = addExpenseDialog.getMoney();
        QString newGoods = addExpenseDialog.getGoods();
        QString newComment = addExpenseDialog.getComment();
        QSharedPointer<Expense> newInc = QSharedPointer<Expense>::create(newDate, newMoney, newComment, newGoods);
        QSharedPointer<Transaction> newTrans = qSharedPointerDynamicCast<Transaction>(newInc);
        mainMngr.addEnd(newInc);

        showMngrInTable(mainMngr);
    }
}

void MainWindow::on_comboBoxActiveCurrency_currentTextChanged(const QString &arg1)
{
    CurrConversion::changeActiveCurrency(arg1);
}
