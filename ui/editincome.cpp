#include "editincome.h"
#include "ui_editincome.h"

EditIncome::EditIncome(QWidget *parent, QSharedPointer<Income>* otherIncInst) :
    QDialog(parent),
    ui(new Ui::EditIncome)
{
    ui->setupUi(this);

    // make window not resizable
    setFixedSize( QSize(this->geometry().size()) );

    ui->dateEdit->setMaximumDate(QDate::currentDate());
    ui->lineEditMoneyValue->setValidator( new QDoubleValidator(0.0, std::numeric_limits<float>::max(), 2, this));

    if (otherIncInst)
    {
        incInst = *otherIncInst;
        ui->dateEdit->setDate(incInst->getDate());
        ui->lineEditMoneyValue->setText(QString::number((incInst->getMoney()).getValue()));
        ui->lineEditComment->setText(incInst->getComment());
        ui->lineEditSource->setText(incInst->getSource());
    }
    else
    {
        qDebug() << "Nullptr " << otherIncInst << " while editing income";
    }

    InitializeCurrencyComboBox();
    ui->dateEdit->setDate(incInst->getDate());
}

EditIncome::~EditIncome()
{
    delete ui;
}

void EditIncome::InitializeCurrencyComboBox()
{
    ui->comboBoxCurrency->addItem(incInst->getMoney().getCurrency());  // to make active curr on top
    for (auto iter = CurrConversion::currencyList.begin(); iter != CurrConversion::currencyList.end(); ++iter)
    {
        if (*iter != incInst->getMoney().getCurrency())
            ui->comboBoxCurrency->addItem(*iter);
    }
}

QDate EditIncome::getDate() const
{
    return incInst->getDate();
}

Money EditIncome::getMoney() const
{
    return incInst->getMoney();
}

QString EditIncome::getSource() const
{
    return incInst->getSource();
}

QString EditIncome::getComment() const
{
    return incInst->getComment();
}

QSharedPointer<Income> EditIncome::getIncome() const
{
    return incInst;
}

void EditIncome::on_dateEdit_userDateChanged(const QDate &date)
{
    incInst->setDate(date);
}

void EditIncome::on_lineEditMoneyValue_textChanged(const QString &arg1)
{
    Money thisMoney = incInst->getMoney();
    thisMoney.setValue(arg1.toFloat());
    incInst->setMoney(thisMoney);
}

void EditIncome::on_comboBoxCurrency_currentTextChanged(const QString &arg1)
{
    Money thisMoney = incInst->getMoney();
    thisMoney.setCurrency(arg1);
    incInst->setMoney(thisMoney);
}

void EditIncome::on_lineEditSource_textChanged(const QString &arg1)
{
    incInst->setSource(arg1);
}

void EditIncome::on_lineEditComment_textChanged(const QString &arg1)
{
    incInst->setComment(arg1);
}
