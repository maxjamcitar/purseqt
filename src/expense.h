#ifndef EXPENSE_H
#define EXPENSE_H

#include "transaction.h"

class Expense : public Transaction
{
public:
    Expense(const QDate &date, const Money &price, const QString &comment, const QString &goods);
    Expense(Expense &otherExp);
    Expense();
    ~Expense();
    void setGoods(const QString &otherGoods);
    QString getGoods() const;
    virtual QString toString() const override;
    virtual QDataStream& toStreamRaw(QDataStream &out) const override;
    Expense fromStreamRaw(QDataStream &out) const;
private:
    QString goods;
};

#endif // EXPENSE_H
