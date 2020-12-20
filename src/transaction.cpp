#include "transaction.h"

Transaction::Transaction()
{
    Transaction::setClassType("Transaction");
    this->date = QDate(0000, 00, 00);
    Transaction::setCategory("OTHER");
    this->price = Money(0.0, CurrConversion::activeCurrency);
    Transaction::setComment(QString(""));
}

Transaction::Transaction(const QDate &date, const QString &category, const Money &price, const QString comment)
{
    Transaction::setClassType("Transaction");
    this->date = date;
    Transaction::setCategory(category);
    this->setPrice(price);
    this->comment = comment;
}

Transaction::Transaction(const Transaction &otherTr)
{
    Transaction::setClassType("Transaction");
    this->date = otherTr.date;
    Transaction::setCategory(otherTr.category);
    this->price = otherTr.price;
    this->comment = otherTr.comment;
}

Transaction::~Transaction()
{
    //cout << "The destructor is called"<< endl;
}

void Transaction::setCategory(const QString &otherCategory)
{
    this->category = otherCategory;
    categoryList.insert(otherCategory);
}

QString Transaction::getCategory() const
{
    return category;
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
    return QStringLiteral("Date: %1 | Category: %2 | Price: %3 | Comment: %4")
            .arg(strDate).arg(this->getCategory()).arg(this->price.to_str()).arg(this->comment);
}

QDataStream& Transaction::toStreamRaw(QDataStream &out) const
{
    out << this->classType
           << this->date
           << this->category
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
