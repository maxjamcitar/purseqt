#include "dialogeditexpense.h"
#include "ui_dialogeditexpense.h"

DialogEditExpense::DialogEditExpense(QWidget *parent, QSharedPointer<Expense>* otherExpInst) :
    QDialog(parent),
    ui(new Ui::EditExpense)
{
    ui->setupUi(this);

    // make window not resizable
    setFixedSize( QSize(this->geometry().size()) );

    ui->dateEdit->setMaximumDate(QDate::currentDate());
    ui->lineEditMoneyValue->setValidator( new QDoubleValidator(0.0, std::numeric_limits<double>::max(), 2, this));

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

DialogEditExpense::~DialogEditExpense()
{
    delete ui;
}

void DialogEditExpense::InitializeCurrencyComboBox()
{
    ui->comboBoxCurrency->addItem(expInst->getMoney().getCurrency());  // to make active curr on top
    for (auto iter = CurrConversion::currencyList.begin(); iter != CurrConversion::currencyList.end(); ++iter)
    {
        if (*iter != expInst->getMoney().getCurrency())
            ui->comboBoxCurrency->addItem(*iter);
    }
}

QDate DialogEditExpense::getDate() const
{
    return expInst->getDate();
}

Money DialogEditExpense::getMoney() const
{
    return expInst->getMoney();
}

QString DialogEditExpense::getGoods() const
{
    return expInst->getGoods();
}

QString DialogEditExpense::getComment() const
{
    return expInst->getComment();
}

QSharedPointer<Expense> DialogEditExpense::getExpense() const
{
    return expInst;
}

void DialogEditExpense::on_dateEdit_userDateChanged(const QDate &date)
{
    expInst->setDate(date);
}

void DialogEditExpense::on_lineEditMoneyValue_textChanged(const QString &arg1)
{
    Money thisMoney = expInst->getMoney();
    thisMoney.setValue(arg1.toDouble());
    expInst->setMoney(thisMoney);
}

void DialogEditExpense::on_comboBoxCurrency_currentTextChanged(const QString &arg1)
{
    Money thisMoney = expInst->getMoney();
    thisMoney.setCurrency(arg1);
    expInst->setMoney(thisMoney);
}

void DialogEditExpense::on_lineEditGoods_textChanged(const QString &arg1)
{
    expInst->setGoods(arg1);
}

void DialogEditExpense::on_lineEditComment_textChanged(const QString &arg1)
{
    expInst->setComment(arg1);
}
