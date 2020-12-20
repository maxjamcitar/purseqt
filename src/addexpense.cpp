#include "addexpense.h"
#include "ui_addexpense.h"

AddExpense::AddExpense(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddExpense)
{
    ui->setupUi(this);

}

AddExpense::~AddExpense()
{
    delete ui;
}
