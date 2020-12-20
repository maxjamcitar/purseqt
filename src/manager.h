#ifndef MANAGER_H
#define MANAGER_H
#include "transaction.h"
#include "income.h"
#include "expense.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <list>

//static const char* const fileName = "test.bin";

class Manager
{
public:
    enum ParameterType {DATE = 0, PRICE, CATEGORY};
    static ParameterType Parameter; // allows to use static enum
    Manager();
    Manager(Manager &otherManager);
    ~Manager();

    std::list<QSharedPointer<Transaction>> getList() const;

    bool isEmpty();

    std::size_t getSize();

    void addBegin(QSharedPointer<Transaction> tran);
    void addEnd(QSharedPointer<Transaction> tran);

    void delBegin();
    void delEnd();

    QSharedPointer<Transaction> getBegin();
    QSharedPointer<Transaction> getEnd();

    void setBegin(QSharedPointer<Transaction> tran);
    void setEnd(QSharedPointer<Transaction> tran);

    void readFile(QString fileName);
    void writeFile(QString fileName);

    bool compareTwo(const QSharedPointer<Transaction> left, const QSharedPointer<Transaction> right, ParameterType field) const;
    void sort(ParameterType field, bool isAscending);
    QString show() const;
    Money accounting ();
    Money accountingExps ();
    Money accountingIncs ();
    Money residual ();

private:
    std::list<QSharedPointer<Transaction>> dqueue;  // std::list because there is no such Qt container
};

#endif // MANAGER_H
