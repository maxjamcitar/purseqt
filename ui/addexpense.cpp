#include "ui/addexpense.h"
#include "ui_addexpense.h"

AddExpense::AddExpense(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddExpense)
{
    ui->setupUi(this);

    ui->comboBoxCurrency->addItem(CurrConversion::activeCurrency);  // to make active curr on top
    for (auto iter = CurrConversion::currencyList.begin(); iter != CurrConversion::currencyList.end(); ++iter)
    {
        if (*iter != CurrConversion::activeCurrency)
            ui->comboBoxCurrency->addItem(*iter);
    }

    ui->dateEdit->setDate(QDate::currentDate());
}

AddExpense::~AddExpense()
{
    delete ui;
}

