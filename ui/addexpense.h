#ifndef ADDEXPENSE_H
#define ADDEXPENSE_H

#include <QDialog>
#include "src/money.h"

namespace Ui {
class AddExpense;
}

class AddExpense : public QDialog
{
    Q_OBJECT

public:
    explicit AddExpense(QWidget *parent = nullptr);
    ~AddExpense();

private:
    Ui::AddExpense *ui;
};

#endif // ADDEXPENSE_H
