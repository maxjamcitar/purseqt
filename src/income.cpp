#include "income.h"

Income::Income()
    : Transaction()
{
    Transaction::setClassType("Income");
    this->date = QDate(0000, 00, 00);
    this->category = QString("OTHER");
    categoryList.insert("OTHER");
    this->price = Money(0.0, CurrConversion::activeCurrency);
    this->source = QString("");
}

Income::Income(const QDate &date, const QString &category, const Money &price, const QString &comment, const QString &source)
    : Transaction(date, category, price, comment)
{
    Transaction::setClassType("Income");
    this->date = date;
    this->category = category;
    this->setPrice(price);
    this->comment = comment;
    this->source = source;
}

Income::Income(Income &otherInc)
    : Transaction(otherInc)
{
    Transaction::setClassType("Income");
    this->date = otherInc.date;
    this->category = otherInc.category;
    this->price = otherInc.price;
    this->source = otherInc.source;
}

Income::~Income()
{

}

void Income::setSource(const QString &otherSource)
{
    this->source = otherSource;
}

QString Income::getSource() const
{
    return source;
}


QString Income::toString() const
{
    int year, month, day;
    this->date.getDate(&year, &month, &day);
    QString strDate = QStringLiteral("%1.%2.%3").arg(year).arg(month).arg(day);
    return QStringLiteral("Date: %1 | Category: %2 | Price: %3 | Source: %4 | Comment: %5")
            .arg(strDate).arg(this->getCategory()).arg(this->price.to_str()).arg(this->source).arg(this->comment);
}

QDataStream& Income::toStreamRaw(QDataStream &out) const
{
    out << this->classType
           << this->date
           << this->category
           << this->price.getValue() << this->price.getCurrency()
           << this->source
           << this->comment;
    return out;
}

Income Income::fromStreamRaw(QDataStream &out) const
{
    Income ret;
    float priceValue;
    QString priceStr;
    out
           //>> ret.classType
           >> ret.date
           >> ret.category
           >> priceValue >> priceStr
           >> ret.source
           >> ret.comment;
    ret.price.setValue(priceValue);
    ret.price.convertTo(priceStr);
    return ret;
}
