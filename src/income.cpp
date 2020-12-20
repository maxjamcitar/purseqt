#include "src/income.h"

Income::Income()
    : Transaction()
{
    this->setClassType("Income");
    this->date = QDate(0000, 00, 00);
    this->price = Money(0.0, CurrConversion::activeCurrency);
    this->source = QString("");
}

Income::Income(const QDate &date, const Money &price, const QString &comment, const QString &source)
    : Transaction(date, price, comment)
{
    this->setClassType("Income");
    this->date = date;
    this->setPrice(price);
    this->comment = comment;
    this->source = source;
}

Income::Income(Income &otherInc)
    : Transaction(otherInc)
{
    this->setClassType("Income");
    this->date = otherInc.date;
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
    return QStringLiteral("Date: %1 | Price: %2 | Source: %3 | Comment: %4")
            .arg(strDate).arg(this->price.to_str()).arg(this->source).arg(this->comment);
}

QDataStream& Income::toStreamRaw(QDataStream &out) const
{
    out << this->classType
           << this->date
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
           >> priceValue >> priceStr
           >> ret.source
           >> ret.comment;
    ret.price.setValue(priceValue);
    ret.price.convertTo(priceStr);
    return ret;
}
