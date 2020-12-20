#include "src/expense.h"

Expense::Expense()
    : Transaction()
{
    this->setClassType("Expense");
    this->date = QDate(0000, 00, 00);
    this->price = Money(0.0, CurrConversion::activeCurrency);
    this->goods = QString("");
}

Expense::Expense(const QDate &date, const Money &price, const QString &comment, const QString &goods)
    : Transaction(date, price, comment)
{
    this->setClassType("Expense");
    this->date = date;
    this->setPrice(price);
    this->comment = comment;
    this->goods = goods;
}

Expense::Expense(Expense &otherTr)
    : Transaction(otherTr)
{
    this->setClassType("Expense");
    this->date = otherTr.date;
    this->price = otherTr.price;
    this->goods = otherTr.goods;
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
            .arg(strDate).arg(this->price.to_str()).arg(this->goods).arg(this->comment);
}


QDataStream& Expense::toStreamRaw(QDataStream &out) const
{
    out << this->classType
           << this->date
           << this->price.getValue() << this->price.getCurrency()
           << this->goods
           << this->comment;
    return out;
}

Expense Expense::fromStreamRaw(QDataStream &out) const
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
    ret.price.setValue(priceValue);
    ret.price.convertTo(priceStr);
    return ret;
}

