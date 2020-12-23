#include "src/income.h"

Income::Income()
    : Transaction()
{
    this->setClassType("Income");
    this->date = QDate(0000, 00, 00);
    this->money = Money(0.0, CurrConversion::activeCurrency);
    this->source = QString("");
}

Income::Income(const QDate &otherDate, const Money &otherPrice, const QString &otherComment, const QString &otherSource)
    : Transaction(otherDate, otherPrice, otherComment)
{
    this->setClassType("Income");
    this->date = otherDate;
    this->money = otherPrice;
    this->comment = otherComment;
    this->source = otherSource;
}

Income::Income(Income &otherInc)
    : Transaction(otherInc)
{
    if (this != &otherInc)
    {
        this->setClassType("Income");
        this->date = otherInc.date;
        this->money = otherInc.money;
        this->source = otherInc.source;
    }
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
            .arg(strDate).arg(this->money.to_str()).arg(this->source).arg(this->comment);
}

QDataStream& Income::toStreamRaw(QDataStream &out) const
{
    out << this->classType
           << this->date
           << this->money.getValue() << this->money.getCurrency()
           << this->source
           << this->comment;
    return out;
}

Income Income::fromStreamRaw(QDataStream &out)
{
    Income ret;
    float priceValue;
    QString priceStr;
    out
           //>> ret.classType   // commented because it's taken in class check
           >> ret.date
           >> priceValue >> priceStr
           >> ret.source
           >> ret.comment;
    ret.money.setValue(priceValue);
    ret.money.setCurrency(priceStr);

    (*this) = ret;

    return ret;
}
