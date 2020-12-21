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
    enum ParameterType {DATE = 0, PRICE, CATEGORY};
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

    qsizetype getIndex(QSharedPointer<Transaction> tran);

    void setBegin(QSharedPointer<Transaction> tran);
    void setEnd(QSharedPointer<Transaction> tran);
    void setAt(QSharedPointer<Transaction> tran);

    void readFile(QString fileName);
    void writeFile(QString fileName);

    bool compareTwo(const QSharedPointer<Transaction> left, const QSharedPointer<Transaction> right, ParameterType field) const;
    void sort(ParameterType field, bool isAscending);
    QString show() const;
    Money accounting () const;
    Money accountingExps () const;
    Money accountingIncs () const;
    Money residual () const;

private:
    QVector<QSharedPointer<Transaction>> dqueue;
};

#endif // MANAGER_H
