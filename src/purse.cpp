#include "purse.h"
#include "ui_purse.h"
#include "transaction.h"
#include "manager.h"
#include "income.h"
#include <QString>
#include <iostream>
#include <QMessageBox>
#include <string>
#include <QDateTime>
using namespace std;

Purse::Purse(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Purse)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("color: rgb(27, 214, 10)");
    ui->label_2->setStyleSheet("color: rgb(234, 35, 4)");

    QString fileName ("test.bin");
    Manager mngr;
    mngr.readFile(fileName);
    ui->pushButton_10->setStyleSheet("color: rgb(234, 35, 4)");
    ui->pushButton_11->setStyleSheet("color: rgb(27, 214, 10)");
    ui->lineEdit_7->setStyleSheet("color: rgb(234, 35, 4)");
    ui->lineEdit_8->setStyleSheet("color: rgb(27, 214, 10)");

    // currency initialization
    CurrConversion currConvInst;
    CurrConversion::addCurrency("RUB", 73.68);  // todo import coef from elsewhere
    CurrConversion::changeActiveCurrency("RUB");
}

Purse::~Purse()
{
    delete ui;
}


void Purse::showing(Manager mngr)
{
    QString dateFormat = QString("dd.MM.yyyy");
    std::size_t dqSize = mngr.getSize();
    ui->tableWidget->setRowCount(dqSize);
    if (dqSize)
        for (std::size_t i = 0; i < dqSize; i++)
        {
            if (mngr.getBegin()->getClassType() == QString("Income"))
            {
                QSharedPointer<Income> incInst = QSharedPointer<Income>(new Income, mngr.getBegin());
                QTableWidgetItem *tmm = new QTableWidgetItem
                        (incInst->getDate().toString(dateFormat));
                ui->tableWidget->setItem(i,0,tmm);
                ui->tableWidget->item(i,0)->setBackground(Qt::green);
                QTableWidgetItem *im = new QTableWidgetItem("");
                ui->tableWidget->setItem(i,1,im);
                ui->tableWidget->item(i,1)->setBackground(Qt::green);
                QTableWidgetItem *it = new QTableWidgetItem
                        (incInst->getComment());
                ui->tableWidget->setItem(i,2,it);
                ui->tableWidget->item(i,2)->setBackground(Qt::green);
                QTableWidgetItem *t = new QTableWidgetItem("");
                ui->tableWidget->setItem(i,3,t);
                ui->tableWidget->item(i,3)->setBackground(Qt::green);
                QTableWidgetItem *imt = new QTableWidgetItem
                        (incInst->getPrice().to_str(QString(" ")));
                ui->tableWidget->setItem(i,4,imt);
                ui->tableWidget->item(i,4)->setBackground(Qt::green);
                mngr.delBegin();
            }
            else if (mngr.getBegin()->getClassType() == QString("Expense"))
            {
                QSharedPointer<Expense> expInst = QSharedPointer<Expense>(new Expense, mngr.getBegin());
                QTableWidgetItem *itmo = new QTableWidgetItem
                        (expInst->getDate().toString(dateFormat));
                ui->tableWidget->setItem(i,0,itmo);
                ui->tableWidget->item(i,0)->setBackground(Qt::red);
                QTableWidgetItem *ito = new QTableWidgetItem
                        (expInst->getGoods());
                ui->tableWidget->setItem(i,1,ito);
                ui->tableWidget->item(i,1)->setBackground(Qt::red);
                QTableWidgetItem *to = new QTableWidgetItem("");
                ui->tableWidget->setItem(i,2,to);
                ui->tableWidget->item(i,2)->setBackground(Qt::red);
                QTableWidgetItem *imo = new QTableWidgetItem
                        (expInst->getCategory());
                ui->tableWidget->setItem(i,3,imo);
                ui->tableWidget->item(i,3)->setBackground(Qt::red);
                QTableWidgetItem *imto = new QTableWidgetItem
                        (expInst->getPrice().to_str(QString(" ")));
                ui->tableWidget->setItem(i,4,imto);
                ui->tableWidget->item(i,4)->setBackground(Qt::red);
                mngr.delBegin();
            }
        }
}

void Purse::on_pushButton_1_clicked()
{
    QString fileName ("test.bin");
    Manager mngr;
    mngr.readFile(fileName);
    QSharedPointer<Income> incItem = QSharedPointer<Income>(new Income, mngr.getBegin());
    incItem->setDate(ui->lineEdit_1->text().toStdString());
    incItem->setComment(QString(ui->lineEdit_6->text().toStdString()));
    incItem->setPrice(ui->lineEdit_2->text());
    Manager mngrShow (mngr);
    Money itemPrice = incItem->getPrice();
    QDate itemDate = incItem->getDate();
    if (itemPrice.getValue() < 0)
    {
        QMessageBox::information (this,"INFO","Price is negative.");
    }
    else
    {
        mngr.addBegin(incItem);
        mngr.writeFile(fileName);
        showing(mngr);
    }
}

void Purse::on_pushButton_2_clicked()
{
    QString fileName ("test.bin");
    Manager mngr;
    mngr.readFile(fileName);
    QSharedPointer<Expense> expItem = QSharedPointer<Expense>(new Expense, mngr.getBegin());
    expItem->setDate(ui->lineEdit_1->text().toStdString());
    expItem->setComment(QString(ui->lineEdit_6->text().toStdString()));
    expItem->setPrice(ui->lineEdit_2->text());
    Manager mngrShow (mngr);
    Money itemPrice = expItem->getPrice();
    QDate itemDate = expItem->getDate();
    if (itemPrice.getValue() < 0)
    {
        QMessageBox::information (this,"INFO","Price is negative.");
    }
    else
    {
        mngr.addBegin(expItem);
        mngr.writeFile(fileName);
        showing(mngr);
    }
}

void Purse::on_pushButton_3_clicked()
{
    QString fileName ("test.bin");
    Manager mngr;
    mngr.readFile(fileName);
    QSharedPointer<Expense> expItem = QSharedPointer<Expense>(new Expense, mngr.getBegin());
    expItem->setDate(ui->lineEdit_3->text().toStdString());
    expItem->setGoods(ui->lineEdit_4->text());
    expItem->setComment(QString(ui->lineEdit_2->text().toStdString()));
    expItem->setPrice(ui->lineEdit_5->text());
    Manager mngrShow (mngr);
    Money itemPrice = expItem->getPrice();
    QDate itemDate = expItem->getDate();
    if (itemPrice.getValue() < 0)
    {
        QMessageBox::information (this,"INFO","Price is negative.");
    }
    else
    {
        mngr.addBegin(expItem);
        mngr.writeFile(fileName);
        showing(mngr);
    }
}

void Purse::on_pushButton_4_clicked()
{
    QString fileName ("test.bin");
    Manager mngr;
    mngr.readFile(fileName);
    QSharedPointer<Expense> expItem = QSharedPointer<Expense>(new Expense, mngr.getBegin());
    expItem->setDate(ui->lineEdit_3->text().toStdString());
    expItem->setGoods(ui->lineEdit_4->text());
    expItem->setComment(QString(ui->lineEdit_2->text().toStdString()));
    expItem->setPrice(ui->lineEdit_5->text());
    Manager mngrShow (mngr);
    Money itemPrice = expItem->getPrice();
    QDate itemDate = expItem->getDate();
    if (itemPrice.getValue() < 0)
    {
        QMessageBox::information (this,"INFO","Price is negative.");
    }
    else
    {
        mngr.addBegin(expItem);
        mngr.writeFile(fileName);
        showing(mngr);
    }
}

void Purse::on_pushButton_5_clicked()
{
    QString fileName ("test.bin");
    Manager mngr;
    mngr.readFile(fileName);
    mngr.delBegin();
    mngr.writeFile(fileName);
    showing(mngr);
}

void Purse::on_pushButton_6_clicked()
{
    QString fileName ("test.bin");
    Manager mngr;
    mngr.readFile(fileName);
    mngr.delEnd();
    mngr.writeFile(fileName);
    showing(mngr);
}

void Purse::on_pushButton_7_clicked()
{
    QString parameter, categ;
    bool way;
    Parameter field;
    Manager *test;
    test=new Manager;
    test->read(fileName);
    categ = ui->comboBox_3->currentText();
    if (categ == "DATE")
        field = DATE;
    if (categ == "NEED")
        field = NEED;
    if (categ == "CATEGORY")
        field = CATEGORY;
    if (categ == "COMMENT")
        field = COMMENT;
    if (categ == "PRICE")
        field = PRICE;
    parameter = ui->comboBox_4->currentText().toStdString();
    if (parameter != "increasing")
        way = true;
    else
        way = false;
    test->sort(field,way);
    test->write(fileName);
    showing(test);
}

void Purse::on_pushButton_8_clicked(){
    if (ui->tableWidget->item(1,1)==0){
        QMessageBox::information
                (this,"INFORMATION","LIST IS EMPTY");}
    else{
    Manager *test;
    test=new Manager;
    test->read(fileName);
    test->write(fileName);
    showing(test);
    QMessageBox::information
            (this,"INFORMATION","LIST RECORDED");}
}

void Purse::on_pushButton_9_clicked(){
    Manager *test;
    test=new Manager;
    test->read(fileName);
    if (test->isEmpty())
        QMessageBox::information
                (this,"INFORMATION","LIST IS EMPTY");
    else
        showing(test);
}

void Purse::on_pushButton_clicked()
{
    Manager *test;
    test=new Manager;
    test->read(fileName);
    ui->lineEdit->setText
            (QString::number(test->accounting()));
}

void Purse::on_pushButton_10_clicked()
{
    Manager *test;
    test=new Manager;
    test->read(fileName);
    ui->lineEdit_7->setText
            (QString::number(test->accountingExps()));
}

void Purse::on_pushButton_11_clicked()
{
    Manager *test;
    test=new Manager;
    test->read(fileName);
    ui->lineEdit_8->setText
            (QString::number(test->accountingInc()));
}

void Purse::on_pushButton_12_clicked()
{
    Manager *test;
    test=new Manager;
    test->read(fileName);
    ui->lineEdit_9->setText
            (QString::number(test->residual()));
}

void Purse::on_pushButton_13_clicked()
{
    QStringList a = QString("Less eat, more sleep|Do not be lazy, go work|Save, but do not be greedy|Money does not happen much|A good name is better than riches|Money is a good servant but a bad master|Thrift is a great revenue|Money begets money|Money often costs too much|A wise man should have money in his head, but not in his heart").split('|');
    int i;
    i = rand() % 10;
    QMessageBox::information
            (this,"HELPFUL ADVICE",a[i]);
}

void Purse::on_pushButton_15_clicked()
{
    QGraphicsScene* scene = new QGraphicsScene(0,0,420,200);
    scene->setBackgroundBrush(Qt::yellow);
    QPen pen_inc(Qt::green, 2);
    QPen pen_exps(Qt::red, 2);
    Manager *test;
    test=new Manager;
    test->read(fileName);
    int a=0, b=0, aa, bb, c=0, d=0, inc, exps;
    inc = test->accountingInc();
    exps = test->accountingExps();
    int max = qMax(inc,exps);
    ui->lineEdit_13->setText(QString::number(0));
    ui->lineEdit_14->setText(QString::number(max));
    if (max<200)
        QMessageBox::information
                (this,"INFORMATION","LIST IS EMPTY");
    else
    {
    max = max/200;
    QString d_beg, d_end, d_day;
    d_beg = QString::fromStdString(test->getBegin()->getDate());
    d_end = QString::fromStdString(test->getEnd()->getDate());
    QDate day_beg, day_end, day;
    day_beg = QDate::fromString(d_beg,"yyyy-MM-dd");
    day_end = QDate::fromString(d_end,"yyyy-MM-dd");
    ui->lineEdit_15->setText(day_beg.toString("yyyy-MM-dd"));
    //ui->lineEdit_11->setText(day_beg.toString(Qt::ISODate));
    ui->lineEdit_16->setText(day_end.toString("yyyy-MM-dd"));
    int days;
    days = day_beg.daysTo(day_end);
    //ui->lineEdit_10->setText(QString::number(days));
    int i, k;
    int n=test->whatSize();
    if (test->whatSize()>0)
        for (i=0;i<n;i++){
            if (test->getBegin()->check()=="Inc"){
                Income *original = static_cast<Income*>(test->getBegin());
                d_day = QString::fromStdString(test->getBegin()->getDate());
                day = QDate::fromString(d_day,"yyyy-MM-dd");
                k = day_beg.daysTo(day);
                aa = original->getPrice();
                test->delBegin();
                scene->addLine(c,-(a/max)+200,k*420/days,-((aa+a)/max)+200, pen_inc);
                c=k*420/days;
                a=aa+a;
            }
            else if (test->getBegin()->check()=="Exps"){
                Expenses *original = static_cast<Expenses*>(test->getBegin());
                d_day = QString::fromStdString(test->getBegin()->getDate());
                day = QDate::fromString(d_day,"yyyy-MM-dd");
                k = day_beg.daysTo(day);
                bb = original->getPrice();
                test->delBegin();
                scene->addLine(d, -(b/max)+200, k*420/days,-((b+bb)/max)+200, pen_exps);
                d=k*420/days;
                b=b+bb;
            }}}
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}
void Purse::on_pushButton_14_clicked()
{
    Manager *test;
    test=new Manager;
    test->read(fileName);
    QString d_beg, d_end;
    d_beg = QString::fromStdString(test->getBegin()->getDate());
    d_end = QString::fromStdString(test->getEnd()->getDate());
    QDate day_beg, day_end;
    day_beg = QDate::fromString(d_beg,"yyyy-MM-dd");
    day_end = QDate::fromString(d_end,"yyyy-MM-dd");
    int days;
    days = day_beg.daysTo(day_end);
    int inc, exps, res;
    inc = test->accountingInc();
    exps = test->accountingExps();
    res = test->residual();
    string time = ui->comboBox->currentText().toStdString();
    if (time == "day")
    {
        if (res>0){
        QMessageBox::information
                (this,"PREDICTION","Next day will be fine.");
        ui->lineEdit_10->setText("+"+QString::number(res/days));}
        else{
            QMessageBox::information
                    (this,"PREDICTION","Next day will be sad.");
            ui->lineEdit_10->setText(QString::number(res/days));}
    }
    else{
        if (time == "week")
        {
            if (res>0){
            QMessageBox::information
                    (this,"PREDICTION","Next week will be fine.");
            ui->lineEdit_11->setText("+"+QString::number(res/days*7));}
            else{
                QMessageBox::information
                        (this,"PREDICTION","Next week will be sad.");
                ui->lineEdit_11->setText(QString::number(res/days*7));}
        }
        else{
            if (time == "month")
            {
                int mon = day_end.month();
                int k;
                if (mon == 1) k=28;
                else if ((mon == 2)||(mon == 4)||(mon == 6)||(mon == 7)||(mon == 9)||(mon == 11)) k=31;
                else k=30;
                if (res>0){
                QMessageBox::information
                        (this,"PREDICTION","Next month will be fine.");
                ui->lineEdit_12->setText("+"+QString::number(res/days*k));}
                else{
                    QMessageBox::information
                            (this,"PREDICTION","Next month will be sad.");
                    ui->lineEdit_12->setText(QString::number(res/days*k));}
            }
            else{
                if (time == "year")
                {
                    if (res>0){
                    QMessageBox::information
                            (this,"PREDICTION","Next year will be fine.");
                    ui->lineEdit_17->setText("+"+QString::number(res/days*365));}
                    else{
                        QMessageBox::information
                                (this,"PREDICTION","Next year will be sad.");
                        ui->lineEdit_17->setText(QString::number(res/days*365));}
                }
            }
        }
    }

}
