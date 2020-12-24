#ifndef MANAGER_H
#define MANAGER_H
#include "transaction.h"
#include "income.h"
#include "expense.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QVector>

class Manager
{
public:
    enum ParameterType {CLASSTR, DATE, MONEY, CATEGORY};
    static ParameterType Parameter; // allows to use static enum
    Manager();
    Manager(Manager &otherManager);
    ~Manager();

    QVector<QSharedPointer<Transaction>> getVector() const;

    bool isEmpty();

    qsizetype getSize();

    void addBegin(QSharedPointer<Transaction> tran);
    void addEnd(QSharedPointer<Transaction> tran);
    void addAfter(QSharedPointer<Transaction> tran, const int i);

    void delBegin();
    void delEnd();
    void delAt(const int i);

    QSharedPointer<Transaction> getBegin();
    QSharedPointer<Transaction> getEnd();
    QSharedPointer<Transaction> getAt(const int i);

    QDate getMinDate() const;
    QDate getMaxDate() const;

    qsizetype getIndex(QSharedPointer<Transaction> tran);

    void setBegin(QSharedPointer<Transaction> tran);
    void setEnd(QSharedPointer<Transaction> tran);
    void setAt(const int i, QSharedPointer<Transaction> tran);

    bool readFile(QString fileName);
    bool writeFile(QString fileName);

    bool compareTwo(const QSharedPointer<Transaction> left, const QSharedPointer<Transaction> right, ParameterType field, bool isAscending) const;
    void sort(ParameterType field, bool isAscending);
    QString show() const;
    Money accounting () const;
    Money residualDates(const QDate& date1, const QDate& date2) const;
    Money accountingExps () const;
    Money accountingIncs () const;
    Money residual () const;

private:
    QVector<QSharedPointer<Transaction>> dqueue;
};

#endif // MANAGER_H
