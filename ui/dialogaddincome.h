#ifndef ADDINCOME_H
#define ADDINCOME_H

#include <QDialog>
#include <QDate>
#include <QDoubleValidator>
#include "src/money.h"

namespace Ui {
class AddIncome;
}

class DialogAddIncome : public QDialog
{
    Q_OBJECT

    void InitializeCurrencyComboBox();

public:
    explicit DialogAddIncome(QWidget *parent = nullptr);
    ~DialogAddIncome();

    QDate getDate() const;
    Money getMoney() const;
    QString getSource() const;
    QString getComment() const;

private slots:
    void on_dateEdit_userDateChanged(const QDate &date);

    void on_lineEditMoneyValue_textChanged(const QString &arg1);

    void on_comboBoxCurrency_currentTextChanged(const QString &arg1);

    void on_lineEditSource_textChanged(const QString &arg1);

    void on_lineEditComment_textChanged(const QString &arg1);

private:
    Ui::AddIncome *ui;

    QDate date;
    float moneyValue;
    QString currency;
    QString source;
    QString comment;
};

#endif // ADDINCOME_H
