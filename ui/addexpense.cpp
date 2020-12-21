#include "ui/addexpense.h"
#include "ui_addexpense.h"

AddExpense::AddExpense(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddExpense)
{
    ui->setupUi(this);

    InitializeCurrencyComboBox();
    ui->dateEdit->setDate(QDate::currentDate());

    ui->lineEditMoneyValue->setValidator( new QDoubleValidator(0.0, std::numeric_limits<float>::max(), 2, this));

    date = QDate::currentDate();
    moneyValue = 0;
    currency = CurrConversion::activeCurrency;
    goods = QString("");
    comment = QString("");
}

AddExpense::~AddExpense()
{
    delete ui;
}

void AddExpense::InitializeCurrencyComboBox()
{
    ui->comboBoxCurrency->addItem(CurrConversion::activeCurrency);  // to make active curr on top
    for (auto iter = CurrConversion::currencyList.begin(); iter != CurrConversion::currencyList.end(); ++iter)
    {
        if (*iter != CurrConversion::activeCurrency)
            ui->comboBoxCurrency->addItem(*iter);
    }
}

QDate AddExpense::getDate() const
{
    return date;
}

Money AddExpense::getMoney() const
{
    return Money(moneyValue, currency);
}

QString AddExpense::getGoods() const
{
    return goods;
}

QString AddExpense::getComment() const
{
    return comment;
}

void AddExpense::on_dateEdit_userDateChanged(const QDate &date)
{
    this->date = date;
}

void AddExpense::on_lineEditMoneyValue_textChanged(const QString &arg1)
{
    this->moneyValue = arg1.toFloat();
}

void AddExpense::on_comboBoxCurrency_currentTextChanged(const QString &arg1)
{
    this->currency = arg1;
}

void AddExpense::on_lineEditGoods_textChanged(const QString &arg1)
{
    this->goods = arg1;
}

void AddExpense::on_lineEditComment_textChanged(const QString &arg1)
{
    this->comment = arg1;
}
