#include "src/manager.h"
#include <QErrorMessage>

Manager::Manager()
{
    dqueue = QVector<QSharedPointer<Transaction>>();
}

Manager::Manager(Manager &otherManager)
{
    if (this != &otherManager)
    {
        dqueue = otherManager.getVector();
    }
}

Manager::~Manager()
{
    dqueue.clear();
}

QVector<QSharedPointer<Transaction>> Manager::getVector() const
{
    return dqueue;
}

bool Manager::isEmpty()
{
    return !(Manager::getSize());
}

qsizetype Manager::getSize()
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

void Manager::addAfter(QSharedPointer<Transaction> tran, const int i)
{
    dqueue.insert(i+1, tran);
}

void Manager::delBegin()
{
    if (dqueue.size() != 0)
    {
        dqueue.pop_front();
    }
    else
        qDebug() << "Failed to remove first element of vector " << &(this->dqueue) << "as it is already empty.";
}

void Manager::delEnd()
{
    if (dqueue.size() != 0)
    {
        dqueue.pop_back();
    }
    else
        qDebug() << "Failed to remove last element of vector " << &(this->dqueue) << "as it is already empty.";
}

void Manager::delAt(const int i)
{
    dqueue.remove(i);
}

QSharedPointer<Transaction> Manager::getBegin(){
    return dqueue.front();
}

QSharedPointer<Transaction> Manager::getEnd(){
    return dqueue.back();
}

QSharedPointer<Transaction> Manager::getAt(const int i)
{
    return dqueue.at(i);
}

qsizetype Manager::getIndex(QSharedPointer<Transaction> tran)
{
    return dqueue.indexOf(tran);
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

void Manager::setAt(const int i, QSharedPointer<Transaction> tran)
{
    this->dqueue.replace(i, tran);
}

bool Manager::readFile(QString fileName){
    QFile file(fileName);
    if (file.exists())
    {
        QDataStream stream(&file);
        if (file.open(QIODevice::ReadOnly))
        {
            dqueue.clear();
            QString classType;
            while(!file.atEnd())
            {
                stream >> classType;
                if (classType == QString("Income"))
                {
                    QSharedPointer<Income> incPtr = QSharedPointer<Income>(new Income);
                    incPtr->fromStreamRaw(stream);
                    QSharedPointer<Transaction> transInst = qSharedPointerDynamicCast<Transaction>(incPtr);
                    addEnd(transInst);
                }
                else if (classType == QString("Expense"))
                {
                    QSharedPointer<Expense> expPtr = QSharedPointer<Expense>(new Expense);
                    expPtr->fromStreamRaw(stream);
                    QSharedPointer<Transaction> transInst = qSharedPointerDynamicCast<Transaction>(expPtr);
                    addEnd(transInst);
                }
                else
                {
                    qDebug() << "Failed to parse a transaction (corrupted or unknown type " + classType + ")";
                }
            }
            file.close();
            return true;
        }
        else
        {
            QMessageBox::critical(nullptr, "Can't open file", "File " + fileName + " cannot be opened for read.");
            return false;
        }
    }
    else
    {
        QMessageBox::critical(nullptr, "File does not exist", "File " + fileName + " does not exist.");
        return false;
    }
}

bool Manager::writeFile(QString fileName)
{
    QFile file(fileName);
    QDataStream stream(&file);
    if (file.open(QIODevice::WriteOnly))
    {
        for (auto iter = dqueue.begin(); iter != dqueue.end(); ++iter)
        {
            (*iter)->toStreamRaw(stream);
        }
        file.close();
        return true;
    }
    else
    {
        QMessageBox::critical(nullptr, "Can't open file", "File " + fileName + "cannot be opened for write.");
        return false;
    }

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

bool Manager::compareTwo(const QSharedPointer<Transaction> left, const QSharedPointer<Transaction> right, ParameterType field) const
{
    bool result;
    QString leftCateg, rightCateg;
    switch (field)
    {
    case ParameterType::DATE:
        result = (left->getDate() > right->getDate()) ? true : false;
        break;

    case ParameterType::PRICE:
        result = (left->getMoney() > right->getMoney()) ? true : false;
        break;

    case ParameterType::CATEGORY:
        if (left->getClassType() == QString("Income"))
        {
            QSharedPointer<Income> leftInc = qSharedPointerDynamicCast<Income>(left);
            leftCateg = leftInc->getSource();
        }
        else if (left->getClassType() == QString("Expense"))
        {
            QSharedPointer<Expense> leftExp = qSharedPointerDynamicCast<Expense>(left);
            leftCateg = leftExp->getGoods();
        }
        else
            leftCateg = QString("NaN");

        if (right->getClassType() == QString("Income"))
        {
            QSharedPointer<Income> rightInc = qSharedPointerDynamicCast<Income>(right);
            rightCateg = rightInc->getSource();
        }
        else if (right->getClassType() == QString("Expense"))
        {
            QSharedPointer<Expense> rightExp = qSharedPointerDynamicCast<Expense>(right);
            rightCateg = rightExp->getGoods();
        }
        else
            rightCateg = QString("NaN");

        result = (leftCateg > rightCateg) ? true : false;
        break;

    default:
        QMessageBox::critical(nullptr, "Sorting failed", "Unknown sorting parameter. Sorting cancelled");
    }
    return result;
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
                if (compareTwo(*mainItemIter, *nextItemIter, field))
                {
                    std::swap(mainItemIter, nextItemIter);
                }
            }
            else
                if (!compareTwo(*mainItemIter, *nextItemIter, field))
                {
                    std::swap(mainItemIter, nextItemIter);
                }
            nextItemIter = std::next(nextItemIter);
        }
        mainItemIter = std::next(mainItemIter);
    }
}


Money Manager::accounting() const
{
    Money res;
    if(dqueue.size())
    {
        for (auto iter = dqueue.begin(); iter != dqueue.end(); ++iter)
        {
            res += (*iter)->getMoney();
        }
    }
    else
        res.setValue(-1);
    return res;
}

Money Manager::accountingExps() const
{
    Money res;
    if(dqueue.size())
    {
        for (auto iter = dqueue.begin(); iter != dqueue.end(); ++iter)
        {
            if ((*iter)->getClassType() == QString("Expense"))
            {
                res += (*iter)->getMoney();
            }
        }
    }
    else
        res.setValue(-1);
    return res;
}

Money Manager::accountingIncs() const
{
    Money res;
    if(dqueue.size())
    {
        for (auto iter = dqueue.begin(); iter != dqueue.end(); ++iter)
        {
            if ((*iter)->getClassType() == QString("Income"))
            {
                res += (*iter)->getMoney();
            }
        }
    }
    else
        res.setValue(-1);
    return res;
}

Money Manager::residual() const
{
    Money res;
    if(dqueue.size())
    {
        for (auto iter = dqueue.begin(); iter != dqueue.end(); ++iter)
        {
            if ((*iter)->getClassType() == QString("Income"))
            {
                res += (*iter)->getMoney();
            }
            else if ((*iter)->getClassType() == QString("Expense"))
            {
                res -= (*iter)->getMoney();
            }
            else
                qDebug() << "Transaction with unidentified class type in dqueue";
        }
    }
    else
        res.setValue(0);
    return res;
}
