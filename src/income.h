#ifndef INCOME_H
#define INCOME_H

#include "transaction.h"

class Income : public Transaction
{
public:
    Income(const QDate &date, const QString &category, const Money &price, const QString &comment, const QString &source);
    Income(Income &otherInc);
    Income();
    ~Income();
    void setSource(const QString &otherSource);
    QString getSource() const;
    QString toString() const override;
    QDataStream& toStreamRaw(QDataStream &out) const override;
    Income fromStreamRaw(QDataStream &out) const override;
private:
    QString source;
};

#endif // INCOME_H
