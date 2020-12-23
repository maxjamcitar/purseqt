#ifndef EDITINCOME_H
#define EDITINCOME_H

#include <QDialog>
#include <QTableWidget>
#include "src/money.h"
#include "src/transaction.h"
#include "src/income.h"

namespace Ui {
class EditIncome;
}

class DialogEditIncome : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditIncome(QWidget *parent = nullptr, QSharedPointer<Income>* otherIncInst = nullptr);
    ~DialogEditIncome();

    void InitializeCurrencyComboBox();

    QDate getDate() const;
    Money getMoney() const;
    QString getSource() const;
    QString getComment() const;
    QSharedPointer<Income> getIncome() const;

private slots:
    void on_dateEdit_userDateChanged(const QDate &date);

    void on_lineEditMoneyValue_textChanged(const QString &arg1);

    void on_comboBoxCurrency_currentTextChanged(const QString &arg1);

    void on_lineEditSource_textChanged(const QString &arg1);

    void on_lineEditComment_textChanged(const QString &arg1);

private:
    Ui::EditIncome *ui;

    QSharedPointer<Income> incInst;
};

#endif // EDITINCOME_H
