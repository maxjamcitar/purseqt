#include "ui/addincome.h"
#include "ui_addincome.h"

AddIncome::AddIncome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddIncome)
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

AddIncome::~AddIncome()
{
    delete ui;
}

