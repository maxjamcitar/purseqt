#include "editexpense.h"
#include "ui_editexpense.h"

EditExpense::EditExpense(QWidget *parent, QSharedPointer<Expense>* otherExpInst) :
    QDialog(parent),
    ui(new Ui::EditExpense)
{
    ui->setupUi(this);

    // make window not resizable
    setFixedSize( QSize(this->geometry().size()) );

    ui->dateEdit->setMaximumDate(QDate::currentDate());
    ui->lineEditMoneyValue->setValidator( new QDoubleValidator(0.0, std::numeric_limits<float>::max(), 2, this));

    if (otherExpInst)
    {
        expInst = *otherExpInst;
        ui->dateEdit->setDate(expInst->getDate());
        ui->lineEditMoneyValue->setText(QString::number((expInst->getMoney()).getValue()));
        ui->lineEditComment->setText(expInst->getComment());
        ui->lineEditGoods->setText(expInst->getGoods());
    }
    else
    {
        qDebug() << "Nullptr " << expInst << " while editing expense";
    }

    InitializeCurrencyComboBox();
    ui->dateEdit->setDate(expInst->getDate());
}

EditExpense::~EditExpense()
{
    delete ui;
}

void EditExpense::InitializeCurrencyComboBox()
{
    ui->comboBoxCurrency->addItem(expInst->getMoney().getCurrency());  // to make active curr on top
    for (auto iter = CurrConversion::currencyList.begin(); iter != CurrConversion::currencyList.end(); ++iter)
    {
        if (*iter != expInst->getMoney().getCurrency())
            ui->comboBoxCurrency->addItem(*iter);
    }
}

QDate EditExpense::getDate() const
{
    return expInst->getDate();
}

Money EditExpense::getMoney() const
{
    return expInst->getMoney();
}

QString EditExpense::getGoods() const
{
    return expInst->getGoods();
}

QString EditExpense::getComment() const
{
    return expInst->getComment();
}

QSharedPointer<Expense> EditExpense::getExpense() const
{
    return expInst;
}

void EditExpense::on_dateEdit_userDateChanged(const QDate &date)
{
    expInst->setDate(date);
}

void EditExpense::on_lineEditMoneyValue_textChanged(const QString &arg1)
{
    Money thisMoney = expInst->getMoney();
    thisMoney.setValue(arg1.toFloat());
    expInst->setMoney(thisMoney);
}

void EditExpense::on_comboBoxCurrency_currentTextChanged(const QString &arg1)
{
    Money thisMoney = expInst->getMoney();
    thisMoney.setCurrency(arg1);
    expInst->setMoney(thisMoney);
}

void EditExpense::on_lineEditGoods_textChanged(const QString &arg1)
{
    expInst->setGoods(arg1);
}

void EditExpense::on_lineEditComment_textChanged(const QString &arg1)
{
    expInst->setComment(arg1);
}
