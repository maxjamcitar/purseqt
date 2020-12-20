#ifndef ADDINCOME_H
#define ADDINCOME_H

#include <QDialog>
#include "src/money.h"

namespace Ui {
class AddIncome;
}

class AddIncome : public QDialog
{
    Q_OBJECT

public:
    explicit AddIncome(QWidget *parent = nullptr);
    ~AddIncome();

private:
    Ui::AddIncome *ui;
};

#endif // ADDINCOME_H
