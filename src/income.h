#ifndef INCOME_H
#define INCOME_H

#include "transaction.h"
#include <QDateTime>

class Income : public Transaction
{
public:
    Income(const QDate &date, const Money &price, const QString &comment, const QString &source);
    Income(Income &otherInc);
    Income();
    ~Income();
    void setSource(const QString &otherSource);
    QString getSource() const;
    virtual QString toString() const override;
    virtual QDataStream& toStreamRaw(QDataStream &out) const override;
    Income fromStreamRaw(QDataStream &out);
private:
    QString source;
};

#endif // INCOME_H
