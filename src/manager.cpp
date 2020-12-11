#include "manager.h"
#include <string>
#include <sstream>
#include <iostream>

Manager::Manager()
{
    dqueue = std::list<Transaction>();
}

Manager::Manager(Manager &otherManager)
{
    dqueue = otherManager.getList();
}

Manager::~Manager()
{
    dqueue.clear();
}

std::list<Transaction> Manager::getList() const
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

void Manager::addBegin(const Transaction tran)
{
   dqueue.push_front(tran);
}

void Manager::addEnd(const Transaction tran)
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

Transaction Manager::getBegin(){
    return dqueue.front();
}

Transaction Manager::getEnd(){
    return dqueue.back();
}

void Manager::setBegin(Transaction tran)
{
    if (dqueue.size() != 0)
    {
        dqueue.front() = tran;
    }
}

void Manager::setEnd(Transaction tran){
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
        file.open( QIODevice::ReadOnly);
        dqueue.clear();
        QString tip;
        QString date;
        QString need;
        QString category;
        QString comment;
        int price;
        node *tmp=new node;
        while(!file.atEnd())
        {
            stream >> tip;
            if (tip=="Inc")
            {
                Income *original = new Income();
                stream >> date >> comment >> price;
                original->setDate(date.toStdString());
                original->setComment(comment.toStdString());
                original->setPrice(price);
                tmp->info=original;
                addEnd(tmp->info);
            }
            if (tip=="Exps")
            {
                Expenses *original = new Expenses();
                stream >> date >> category >> need >> price;
                original->setDate(date.toStdString());
                original->setCategory(category.toStdString());
                original->setNeed(need.toStdString());
                original->setPrice(price);
                tmp->info=original;
                addEnd(tmp->info);
            }
        }
        file.close();
    }
    else
         qDebug() << "File " << fileName << "cannot be opened";
}

void Manager::writeFile(QString fileName)
{
    QFile file(fileName);
    QDataStream stream(&file);
    file.open(QIODevice::WriteOnly);
    for (auto iter = dqueue.begin(); iter != dqueue.end(); ++iter)
    {
        iter->toStringRaw(stream);
    }
    file.close();
}

std::string Manager::show()
{
    std::string res="";
    if(size)
        for (node *i=first; i!=NULL; i=i->next)
            res=res+i->info->toString()+'\n';
    else
        res="Deque is empty";
    return res;
}

void Manager::sort(Parameter field, bool course){
    node *one = first;
    node *other = NULL;
    while(one){
        other = one->next;
        while (other){
            if (other->info->compare(one->info,field,course)){
                Base* some;
                some = other->info;
                other->info = one->info;
                one->info = some;
            }
            other = other->next;
        }
        one = one->next;
    }
}

int Manager::accounting()
{
    int res=0;
    if(size)
        for (node *i=first; i!=NULL; i=i->next)
            res=res+i->info->getPrice();
    else
        res=-1;
    return res;
}

int Manager::accountingExps()
{
    int res=0;
    if(size){
        for (node *i=first; i!=NULL; i=i->next)
            if (i->info->check()=="Exps")
                res=res+i->info->getPrice();}
    else
        res=-1;
    return res;
}

int Manager::accountingInc()
{
    int res=0;
    if(size){
        for (node *i=first; i!=NULL; i=i->next)
            if (i->info->check()=="Inc")
                res=res+i->info->getPrice();}
    else
        res=-1;
    return res;
}

int Manager::residual()
{
    int res=0;
    if(size){
        for (node *i=first; i!=NULL; i=i->next)
            if (i->info->check()=="Inc")
                res=res+i->info->getPrice();
            else
                res=res-i->info->getPrice();}
    else
        res=+-666;
    return res;
}
