#include "manager.h"
#include <string>
#include <sstream>
#include <iostream>
#include <QErrorMessage>

Manager::Manager()
{
    dqueue = std::list<QSharedPointer<Transaction>>();
}

Manager::Manager(Manager &otherManager)
{
    dqueue = otherManager.getList();
}

Manager::~Manager()
{
    dqueue.clear();
}

std::list<QSharedPointer<Transaction>> Manager::getList() const
{
    return dqueue;
}

bool Manager::isEmpty()
{
    return !(Manager::getSize());
}

std::size_t Manager::getSize()
{
    return dqueue.size();
}

void Manager::addBegin(QSharedPointer<Transaction> tran)
{
   dqueue.push_front(tran);
}

void Manager::addEnd(QSharedPointer<Transaction> tran)
{
    dqueue.push_back(tran);
}

void Manager::delBegin(){
    if (dqueue.size() != 0)
    {
        dqueue.pop_front();
    }
    else
        qDebug() << "Failed to remove first element of std::list " << &(this->dqueue) << "as it is already empty.";
}

void Manager::delEnd(){
    if (dqueue.size() != 0)
    {
        dqueue.pop_back();
    }
    else
        qDebug() << "Failed to remove last element of std::list " << &(this->dqueue) << "as it is already empty.";
}

QSharedPointer<Transaction> Manager::getBegin(){
    return dqueue.front();
}

QSharedPointer<Transaction> Manager::getEnd(){
    return dqueue.back();
}

void Manager::setBegin(QSharedPointer<Transaction> tran)
{
    if (dqueue.size() != 0)
    {
        dqueue.front() = tran;
    }
}

void Manager::setEnd(QSharedPointer<Transaction> tran){
    if (dqueue.size() != 0)
    {
        dqueue.back() = tran;
    }
}

void Manager::readFile(QString fileName){
    QFile file(fileName);
    if (file.exists())
    {
        QDataStream stream(&file);
        file.open(QIODevice::ReadOnly);
        dqueue.clear();
        QString classType;
        while(!file.atEnd())
        {
            stream >> classType;
            if (classType == QString("Income"))
            {
                Income incInst;
                incInst.fromStreamRaw(stream);
                QSharedPointer<Transaction> transInst = QSharedPointer<Transaction>(new Transaction, incInst);
                addEnd(transInst);
            }
            else if (classType == QString("Expense"))
            {
                Expense expInst;
                expInst.fromStreamRaw(stream);
                QSharedPointer<Transaction> transInst = QSharedPointer<Transaction>(new Transaction, expInst);
                addEnd(transInst);
            }
            else
            {
                QErrorMessage err;
                err.showMessage(QString("Failed to parse a transaction (corrupted or unknown type " + classType + ")"));
            }
        }
        file.close();
    }
    else
    {
        QErrorMessage err;
        err.showMessage(QString("File " + fileName + "cannot be opened."));
    }
}

void Manager::writeFile(QString fileName)
{
    QFile file(fileName);
    QDataStream stream(&file);
    file.open(QIODevice::WriteOnly);
    for (auto iter = dqueue.begin(); iter != dqueue.end(); ++iter)
    {
        (*iter)->toStreamRaw(stream);
    }
    file.close();
}

QString Manager::show() const
{
    QDataStream strStream;
    QString result;
    if (dqueue.size() == 0)
        return QString ("Deque is empty");
    for (auto iter = dqueue.begin(); iter != dqueue.end(); ++iter)
    {
        strStream << (*iter)->toString() << QString("\n");
    }
    strStream >> result;
    return result;
}

bool Manager::compareTwo(const Transaction& left, const Transaction& right, ParameterType field) const
{
    switch (field)
    {

    case ParameterType::PRICE:
        return (left.getPrice() > right.getPrice()) ? true : false;
        break;

    case ParameterType::CATEGORY:
        return (left.getCategory() > right.getCategory()) ? true : false;
        break;

    default:
        qDebug() << QString("Unknown parameter. Sorting by date");

    case ParameterType::DATE:
        return (left.getDate() > right.getDate()) ? true : false;
        break;
    }
}

void Manager::sort(ParameterType field, bool isAscending)
{
    if (dqueue.size() == 0)
        qDebug() << QString("No need to sort manager dqueue as it's empty");
    else if (dqueue.size() == 0)
        qDebug() << QString("No need to sort manager dqueue as it contains only 1 item");
    auto mainItemIter = dqueue.begin();
    // this is basically bubble sort
    while(mainItemIter != dqueue.end())
    {
        auto nextItemIter = std::next(mainItemIter);
        while (nextItemIter != dqueue.end())
        {
            if (isAscending)
            {
                if (compareTwo(*(*mainItemIter), *(*mainItemIter), field))
                {
                    std::swap(mainItemIter, nextItemIter);
                }
            }
            else
                if (!compareTwo(*(*mainItemIter), *(*mainItemIter), field))
                {
                    std::swap(mainItemIter, nextItemIter);
                }
            nextItemIter = std::next(nextItemIter);
        }
        mainItemIter = std::next(mainItemIter);
    }
}

Money Manager::accounting()
{
    Money res;
    if(dqueue.size())
    {
        for (auto iter = dqueue.begin(); iter != dqueue.end(); ++iter)
        {
            res += (*iter)->getPrice();
        }
    }
    else
        res.setValue(-1);
    return res;
}

Money Manager::accountingExps()
{
    Money res;
    if(dqueue.size())
    {
        for (auto iter = dqueue.begin(); iter != dqueue.end(); ++iter)
        {
            if ((*iter)->getClassType() == QString("Expense"))
            {
                res += (*iter)->getPrice();
            }
        }
    }
    else
        res.setValue(-1);
    return res;
}

Money Manager::accountingIncs()
{
    Money res;
    if(dqueue.size())
    {
        for (auto iter = dqueue.begin(); iter != dqueue.end(); ++iter)
        {
            if ((*iter)->getClassType() == QString("Income"))
            {
                res += (*iter)->getPrice();
            }
        }
    }
    else
        res.setValue(-1);
    return res;
}

Money Manager::residual()
{
    Money res;
    if(dqueue.size())
    {
        for (auto iter = dqueue.begin(); iter != dqueue.end(); ++iter)
        {
            if ((*iter)->getClassType() == QString("Income"))
            {
                res += (*iter)->getPrice();
            }
            else if ((*iter)->getClassType() == QString("Expense"))
            {
                res -= (*iter)->getPrice();
            }
            else
                qDebug() << "Transaction with unidentified class type in dqueue";
        }
    }
    else
        res.setValue(0);
    return res;
}
