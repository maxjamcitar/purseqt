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
    Manager();
    Manager(Manager &otherManager);
    ~Manager();

    std::list<Transaction> getList() const;

    bool isEmpty();

    std::size_t getSize();

    void addBegin(const Transaction tran);
    void addEnd(const Transaction tran);

    void delBegin();
    void delEnd();

    Transaction getBegin();
    Transaction getEnd();

    void setBegin(Transaction tran);
    void setEnd(Transaction tran);

    void readFile(QString fileName);
    void writeFile(QString fileName);

    void sort(Transaction::Parameter field, bool switcher);
    std::string show();
    int accounting ();
    int accountingExps ();
    int accountingInc ();
    int residual ();

private:
    std::list<Transaction> dqueue;  // std::list because there is no such Qt container
    unsigned int size;
};

#endif // MANAGER_H
