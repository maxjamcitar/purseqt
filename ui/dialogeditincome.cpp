#include "dialogeditincome.h"
#include "ui_dialogeditincome.h"

DialogEditIncome::DialogEditIncome(QWidget *parent, QSharedPointer<Income>* otherIncInst) :
    QDialog(parent),
    ui(new Ui::EditIncome)
{
    ui->setupUi(this);

    // make window not resizable
    setFixedSize( QSize(this->geometry().size()) );

    ui->dateEdit->setMaximumDate(QDate::currentDate());
    ui->lineEditMoneyValue->setValidator( new QDoubleValidator(0.0, std::numeric_limits<double>::max(), 2, this));

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

DialogEditIncome::~DialogEditIncome()
{
    delete ui;
}

void DialogEditIncome::InitializeCurrencyComboBox()
{
    ui->comboBoxCurrency->addItem(incInst->getMoney().getCurrency());  // to make active curr on top
    for (auto iter = CurrConversion::currencyList.begin(); iter != CurrConversion::currencyList.end(); ++iter)
    {
        if (*iter != incInst->getMoney().getCurrency())
            ui->comboBoxCurrency->addItem(*iter);
    }
}

QDate DialogEditIncome::getDate() const
{
    return incInst->getDate();
}

Money DialogEditIncome::getMoney() const
{
    return incInst->getMoney();
}

QString DialogEditIncome::getSource() const
{
    return incInst->getSource();
}

QString DialogEditIncome::getComment() const
{
    return incInst->getComment();
}

QSharedPointer<Income> DialogEditIncome::getIncome() const
{
    return incInst;
}

void DialogEditIncome::on_dateEdit_userDateChanged(const QDate &date)
{
    incInst->setDate(date);
}

void DialogEditIncome::on_lineEditMoneyValue_textChanged(const QString &arg1)
{
    Money thisMoney = incInst->getMoney();
    thisMoney.setValue(arg1.toDouble());
    incInst->setMoney(thisMoney);
}

void DialogEditIncome::on_comboBoxCurrency_currentTextChanged(const QString &arg1)
{
    Money thisMoney = incInst->getMoney();
    thisMoney.setCurrency(arg1);
    incInst->setMoney(thisMoney);
}

void DialogEditIncome::on_lineEditSource_textChanged(const QString &arg1)
{
    incInst->setSource(arg1);
}

void DialogEditIncome::on_lineEditComment_textChanged(const QString &arg1)
{
    incInst->setComment(arg1);
}
