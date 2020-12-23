#ifndef ADDEXPENSE_H
#define ADDEXPENSE_H

#include <QDialog>
#include <QDate>
#include <QDoubleValidator>
#include "src/money.h"

namespace Ui {
class AddExpense;
}

class DialogAddExpense : public QDialog
{
    Q_OBJECT

    void InitializeCurrencyComboBox();

public:
    explicit DialogAddExpense(QWidget *parent = nullptr);
    ~DialogAddExpense();

    QDate getDate() const;
    Money getMoney() const;
    QString getGoods() const;
    QString getComment() const;

private slots:
    void on_dateEdit_userDateChanged(const QDate &date);

    void on_lineEditMoneyValue_textChanged(const QString &arg1);

    void on_comboBoxCurrency_currentTextChanged(const QString &arg1);

    void on_lineEditGoods_textChanged(const QString &arg1);

    void on_lineEditComment_textChanged(const QString &arg1);

private:
    Ui::AddExpense *ui;

    QDate date;
    float moneyValue;
    QString currency;
    QString goods;
    QString comment;
};

#endif // ADDEXPENSE_H
