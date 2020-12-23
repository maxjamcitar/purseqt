#include "src/expense.h"

Expense::Expense()
    : Transaction()
{
    this->setClassType("Expense");
    this->date = QDate(0000, 00, 00);
    this->money = Money(0.0, CurrConversion::activeCurrency);
    this->goods = QString("");
}

Expense::Expense(const QDate &date, const Money &price, const QString &comment, const QString &goods)
    : Transaction(date, price, comment)
{
    this->setClassType("Expense");
    this->date = date;
    this->setMoney(price);
    this->comment = comment;
    this->goods = goods;
}

Expense::Expense(Expense &otherExp)
    : Transaction(otherExp)
{
    if (this != &otherExp)
    {
        this->setClassType("Expense");
        this->date = otherExp.date;
        this->money = otherExp.money;
        this->goods = otherExp.goods;
    }
}

Expense::~Expense()
{

}

void Expense::setGoods(const QString &otherGoods)
{
    this->goods = otherGoods;
}

QString Expense::getGoods() const
{
    return goods;
}


QString Expense::toString() const
{
    int year, month, day;
    this->date.getDate(&year, &month, &day);
    QString strDate = QStringLiteral("%1.%2.%3").arg(year).arg(month).arg(day);
    return QStringLiteral("Date: %1 | Price: %2 | Goods: %3 | Comment: %4")
            .arg(strDate).arg(this->money.to_str()).arg(this->goods).arg(this->comment);
}

QDataStream& Expense::toStreamRaw(QDataStream &out) const
{
    out << this->classType
           << this->date
           << this->money.getValue() << this->money.getCurrency()
           << this->goods
           << this->comment;
    return out;
}

Expense Expense::fromStreamRaw(QDataStream &out)
{
    Expense ret;
    float priceValue;
    QString priceStr;
    out
           //>> ret.classType
           >> ret.date
           >> priceValue >> priceStr
           >> ret.goods
           >> ret.comment;
    ret.money.setValue(priceValue);
    ret.money.setCurrency(priceStr);

    (*this) = ret;

    return ret;
}
