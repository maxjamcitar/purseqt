#include "expense.h"

Expense::Expense()
{
    Transaction::setClassType("Expense");
    this->date = QDate(0000, 00, 00);
    this->category = QString("OTHER");
    categoryList.insert("OTHER");
    this->price = Money(0.0, Money::activeCurrency);
    this->goods = QString("");
}

Expense::Expense(const QDate &date, const QString &category, const Money &price, const QString &comment, const QString &goods)
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

QDataStream& Expense::toStringRaw(QDataStream &out) const
{
    out << this->classType
           << this->date
           << this->category
           << this->price.to_str(QString(""))
           << this->goods
           << this->comment;
    return out;
}
