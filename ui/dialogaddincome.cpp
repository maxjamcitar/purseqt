#include "ui/dialogaddincome.h"
#include "ui_dialogaddincome.h"

DialogAddIncome::DialogAddIncome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddIncome)
{
    ui->setupUi(this);

    // make window not resizable
    setFixedSize( QSize(this->geometry().size()) );

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

DialogAddIncome::~DialogAddIncome()
{
    delete ui;
}

void DialogAddIncome::InitializeCurrencyComboBox()
{
    ui->comboBoxCurrency->addItem(CurrConversion::activeCurrency);  // to make active curr on top
    for (auto iter = CurrConversion::currencyList.begin(); iter != CurrConversion::currencyList.end(); ++iter)
    {
        if (*iter != CurrConversion::activeCurrency)
            ui->comboBoxCurrency->addItem(*iter);
    }
}

QDate DialogAddIncome::getDate() const
{
    return date;
}

Money DialogAddIncome::getMoney() const
{
    return Money(moneyValue, currency);
}

QString DialogAddIncome::getSource() const
{
    return source;
}

QString DialogAddIncome::getComment() const
{
    return comment;
}

void DialogAddIncome::on_dateEdit_userDateChanged(const QDate &date)
{
    this->date = date;
}

void DialogAddIncome::on_lineEditMoneyValue_textChanged(const QString &arg1)
{
    this->moneyValue = arg1.toFloat();
}

void DialogAddIncome::on_comboBoxCurrency_currentTextChanged(const QString &arg1)
{
    this->currency = arg1;
}

void DialogAddIncome::on_lineEditSource_textChanged(const QString &arg1)
{
    this->source = arg1;
}

void DialogAddIncome::on_lineEditComment_textChanged(const QString &arg1)
{
    this->comment = arg1;
}
