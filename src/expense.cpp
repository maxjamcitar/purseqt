#include "expense.h"

Expense::Expense()
    : Transaction()
{
    Transaction::setClassType("Expense");
    this->date = QDate(0000, 00, 00);
    this->category = QString("OTHER");
    categoryList.insert("OTHER");
    this->price = Money(0.0, CurrConversion::activeCurrency);
    this->goods = QString("");
}

Expense::Expense(const QDate &date, const QString &category, const Money &price, const QString &comment, const QString &goods)
    : Transaction(date, category, price, comment)
{
    Transaction::setClassType("Expense");
    this->date = date;
    this->category = category;
    this->setPrice(price);
    this->comment = comment;
    this->goods = goods;
}

Expense::Expense(Expense &otherTr)
    : Transaction(otherTr)
{
    Transaction::setClassType("Expense");
    this->date = otherTr.date;
    this->category = otherTr.category;
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
    return QStringLiteral("Date: %1 | Category: %2 | Price: %3 | Goods: %4 | Comment: %5")
            .arg(strDate).arg(this->getCategory()).arg(this->price.to_str()).arg(this->goods).arg(this->comment);
}


QDataStream& Expense::toStreamRaw(QDataStream &out) const
{
    out << this->classType
           << this->date
           << this->category
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
           >> ret.category
           >> priceValue >> priceStr
           >> ret.goods
           >> ret.comment;
    ret.price.setValue(priceValue);
    ret.price.convertTo(priceStr);
    return ret;
}

