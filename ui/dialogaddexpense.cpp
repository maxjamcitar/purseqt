#include "ui/dialogaddexpense.h"
#include "ui_dialogaddexpense.h"

DialogAddExpense::DialogAddExpense(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddExpense)
{
    ui->setupUi(this);

    // make window not resizable
    setFixedSize( QSize(this->geometry().size()) );

    InitializeCurrencyComboBox();
    ui->dateEdit->setDate(QDate::currentDate());

    ui->dateEdit->setMaximumDate(QDate::currentDate());
    ui->lineEditMoneyValue->setValidator( new QDoubleValidator(0.0, std::numeric_limits<double>::max(), 2, this));

    date = QDate::currentDate();
    moneyValue = 0;
    currency = CurrConversion::activeCurrency;
    goods = QString("");
    comment = QString("");
}

DialogAddExpense::~DialogAddExpense()
{
    delete ui;
}

void DialogAddExpense::InitializeCurrencyComboBox()
{
    ui->comboBoxCurrency->addItem(CurrConversion::activeCurrency);  // to make active curr on top
    for (auto iter = CurrConversion::currencyList.begin(); iter != CurrConversion::currencyList.end(); ++iter)
    {
        if (*iter != CurrConversion::activeCurrency)
            ui->comboBoxCurrency->addItem(*iter);
    }
}

QDate DialogAddExpense::getDate() const
{
    return date;
}

Money DialogAddExpense::getMoney() const
{
    return Money(moneyValue, currency);
}

QString DialogAddExpense::getGoods() const
{
    return goods;
}

QString DialogAddExpense::getComment() const
{
    return comment;
}

void DialogAddExpense::on_dateEdit_userDateChanged(const QDate &date)
{
    this->date = date;
}

void DialogAddExpense::on_lineEditMoneyValue_textChanged(const QString &arg1)
{
    this->moneyValue = arg1.toDouble();
}

void DialogAddExpense::on_comboBoxCurrency_currentTextChanged(const QString &arg1)
{
    this->currency = arg1;
}

void DialogAddExpense::on_lineEditGoods_textChanged(const QString &arg1)
{
    this->goods = arg1;
}

void DialogAddExpense::on_lineEditComment_textChanged(const QString &arg1)
{
    this->comment = arg1;
}
