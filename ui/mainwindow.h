#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    void InitializeActCurrencyComboBox();
    void showMngrInTable(const Manager& argMngr);


    Ui::MainWindow *ui;

    Manager mainMngr;   // for all transaction data
    //CurrConversion currConversion;
};

#endif // MAINWINDOW_H
