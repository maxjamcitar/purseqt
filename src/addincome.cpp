#include "addincome.h"
#include "ui_addincome.h"

AddIncome::AddIncome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddIncome)
{
    ui->setupUi(this);
}

AddIncome::~AddIncome()
{
    delete ui;
}

