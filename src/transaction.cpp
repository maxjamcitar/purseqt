#include "transaction.h"

Transaction::Transaction()
{
    this->setClassType("Transaction");
    this->date = QDate(0000, 00, 00);
    this->price = Money(0.0, CurrConversion::activeCurrency);
    Transaction::setComment(QString(""));
}

Transaction::Transaction(const QDate &date, const Money &price, const QString comment)
{
    this->setClassType("Transaction");
    this->date = date;
    this->setPrice(price);
    this->comment = comment;
}

Transaction::Transaction(const Transaction &otherTr)
{
    this->setClassType("Transaction");
    this->date = otherTr.date;
    this->price = otherTr.price;
    this->comment = otherTr.comment;
}

Transaction::~Transaction()
{
    //cout << "The destructor is called"<< endl;
}

QString Transaction::getClassType () const
{
    return classType;
}


void Transaction::setPrice (const Money &otherPrice)
{
    this->price = otherPrice;
}


Money Transaction::getPrice () const
{
    return this->price;
}

void Transaction::setComment(const QString &otherComment)
{
    this->comment = otherComment;
}

QString Transaction::getComment() const
{
    return comment;
}

QString Transaction::toString() const
{
    int year, month, day;
    this->date.getDate(&year, &month, &day);
    QString strDate = QStringLiteral("%1.%2.%3").arg(year).arg(month).arg(day);
    return QStringLiteral("Date: %1 | Price: %2 | Comment: %3")
            .arg(strDate).arg(this->price.to_str()).arg(this->comment);
}

QDataStream& Transaction::toStreamRaw(QDataStream &out) const
{
    out << this->classType
           << this->date
           << this->price.getValue() << this->price.getCurrency()
           << this->comment;
    return out;
}

/*

Transaction Transaction::fromStreamRaw(QDataStream &out) const
{
    Transaction ret;
    float priceValue;
    QString priceStr;
    out
           //>> ret.classType
           >> ret.date
           >> ret.category
           >> priceValue >> priceStr
           >> ret.comment;
    ret.price.setValue(priceValue);
    ret.price.convertTo(priceStr);
    return ret;
}

*/

void Transaction::setClassType (const QString &otherClassType)
{
    classType = otherClassType;
}
