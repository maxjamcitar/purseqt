#include "src/transaction.h"

Transaction::Transaction()
{
    this->setClassType("Transaction");
    this->date = QDate(0000, 00, 00);
    this->money = Money(0.0, CurrConversion::activeCurrency);
    Transaction::setComment(QString(""));
}

Transaction::Transaction(const QDate &otherDate, const Money &otherMoney, const QString otherComment)
{
    this->setClassType("Transaction");
    this->date = otherDate;
    this->money = otherMoney;
    this->comment = otherComment;
}

Transaction::Transaction(const Transaction &otherTr)
{
    if (this != &otherTr)
    {
        this->setClassType("Transaction");
        this->date = otherTr.date;
        this->money = otherTr.money;
        this->comment = otherTr.comment;
    }
}

Transaction::~Transaction()
{
    //cout << "The destructor is called"<< endl;
}

QString Transaction::getClassType () const
{
    return classType;
}

void Transaction::setDate (const QDate &otherDate)
{
    this->date = otherDate;
}

QDate Transaction::getDate () const
{
    return this->date;
}

void Transaction::setMoney (const Money &otherMoney)
{
    this->money = otherMoney;
}


Money Transaction::getMoney () const
{
    return this->money;
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
            .arg(strDate).arg(this->money.to_str()).arg(this->comment);
}

QDataStream& Transaction::toStreamRaw(QDataStream &out) const
{
    out << this->classType
           << this->date
           << this->money.getValue() << this->money.getCurrency()
           << this->comment;
    return out;
}

/*

Transaction Transaction::fromStreamRaw(QDataStream &out) const
{
    Transaction ret;
    double priceValue;
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
