#include "ui/addincome.h"
#include "ui_addincome.h"

AddIncome::AddIncome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddIncome)
{
    ui->setupUi(this);

    InitializeCurrencyComboBox();
    ui->dateEdit->setDate(QDate::currentDate());

    ui->dateEdit->setMaximumDate(QDate::currentDate());
    ui->lineEditMoneyValue->setValidator( new QDoubleValidator(0.0, std::numeric_limits<float>::max(), 2, this));

    date = QDate::currentDate();
    moneyValue = 0;
    currency = CurrConversion::activeCurrency;
    source = QString("");
    comment = QString("");
}

AddIncome::~AddIncome()
{
    delete ui;
}

void AddIncome::InitializeCurrencyComboBox()
{
    ui->comboBoxCurrency->addItem(CurrConversion::activeCurrency);  // to make active curr on top
    for (auto iter = CurrConversion::currencyList.begin(); iter != CurrConversion::currencyList.end(); ++iter)
    {
        if (*iter != CurrConversion::activeCurrency)
            ui->comboBoxCurrency->addItem(*iter);
    }
}

QDate AddIncome::getDate() const
{
    return date;
}

Money AddIncome::getMoney() const
{
    return Money(moneyValue, currency);
}

QString AddIncome::getSource() const
{
    return source;
}

QString AddIncome::getComment() const
{
    return comment;
}

void AddIncome::on_dateEdit_userDateChanged(const QDate &date)
{
    this->date = date;
}

void AddIncome::on_lineEditMoneyValue_textChanged(const QString &arg1)
{
    this->moneyValue = arg1.toFloat();
}

void AddIncome::on_comboBoxCurrency_currentTextChanged(const QString &arg1)
{
    this->currency = arg1;
}

void AddIncome::on_lineEditSource_textChanged(const QString &arg1)
{
    this->source = arg1;
}

void AddIncome::on_lineEditComment_textChanged(const QString &arg1)
{
    this->comment = arg1;
}
