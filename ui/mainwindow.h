#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

#include "src/manager.h"
#include "src/money.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonAddIncome_clicked();

    void on_buttonAddExpense_clicked();

    void on_comboBoxActiveCurrency_currentTextChanged(const QString &arg1);

    void on_tableTransactions_customContextMenuRequested(const QPoint &pos);
    void editTransaction();
    void removeTransaction();

    void on_buttonConvertMngr_clicked();

private:
    void InitializeActCurrencyComboBox();
    void updateMngrInTable(const Manager& argMngr);

    Ui::MainWindow *ui;

    Manager mainMngr;   // for all transaction data
};

#endif // MAINWINDOW_H
