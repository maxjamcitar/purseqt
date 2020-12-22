#ifndef EDITEXPENSE_H
#define EDITEXPENSE_H

#include <QDialog>
#include <QTableWidget>
#include "src/money.h"
#include "src/transaction.h"
#include "src/expense.h"

namespace Ui {
class EditExpense;
}

class EditExpense : public QDialog
{
    Q_OBJECT

public:
    explicit EditExpense(QWidget *parent = nullptr, QSharedPointer<Expense>* otherExpInst = nullptr);
    ~EditExpense();

    void InitializeCurrencyComboBox();

    QDate getDate() const;
    Money getMoney() const;
    QString getGoods() const;
    QString getComment() const;
    QSharedPointer<Expense> getExpense() const;


private slots:
    void on_dateEdit_userDateChanged(const QDate &date);

    void on_lineEditMoneyValue_textChanged(const QString &arg1);

    void on_comboBoxCurrency_currentTextChanged(const QString &arg1);

    void on_lineEditGoods_textChanged(const QString &arg1);

    void on_lineEditComment_textChanged(const QString &arg1);

private:
    Ui::EditExpense *ui;

    QSharedPointer<Expense> expInst;
};

#endif // EDITEXPENSE_H
