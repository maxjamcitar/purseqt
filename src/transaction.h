#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "money.h"
#include <QString>
#include <QDate>
#include <QDataStream>
#include <QSet>

class Transaction
{
public:
    //enum Parameter {DATE, PRICE, COMMENT};

    virtual ~Transaction();
    virtual QString getClassType () const;  // expense, income or elsewhat
    void setDate (const QDate &otherDate);
    QDate getDate () const;
    void setPrice (const Money &otherPrice);
    Money getPrice () const;
    void setComment(const QString &otherComment);
    QString getComment() const;

    virtual QString toString() const;
    virtual QDataStream& toStreamRaw(QDataStream &out) const;
    //virtual Transaction fromStreamRaw(QDataStream &out) const;

    //static QSet<QString> categoryList;  // todo save category list

    friend class Manager;   // so Manager can store abstract Transactions instead of Expenses or Incomes
protected:
    Transaction(const QDate &date, const Money &price, const QString comment);
    Transaction(const Transaction &otherTr);
    Transaction();
    void setClassType (const QString &otherClassType);
protected:
    QDate date;
    QString classType;
    Money price;
    QString comment;
};

#endif // TRANSACTION_H
