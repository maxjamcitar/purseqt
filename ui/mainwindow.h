#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLayout>
#include <QFileDialog>
#include <cmath>

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
    void addIncome();
    void addExpense();

    void dialogLoadFile();
    void dialogSaveFileAs();

    void sortMngrByType();
    void sortMngrByDate();
    void sortMngrByMoney();
    void sortMngrBySourceGoods();

    void on_comboBoxActiveCurrency_currentTextChanged(const QString &arg1);

    void on_tableTransactions_customContextMenuRequested(const QPoint &pos);
    void editTransaction();
    void removeTransaction();

    void on_buttonConvertMngr_clicked();

    void on_buttonShowChart_clicked();

private:
    void InitializeActCurrencyComboBox();
    void updateMngrInTable(const Manager& argMngr);
    bool loadFile(const QString& fileName);
    bool saveFile(const QString& fileName);
    void updateStats(const Manager& mngr);

    QString makeStrResidualUsual(const Money& moneyValue, const Money& moneyAvg) const;
    QString makeStrForeseeBalance(const Money& balance, const Money& residualDiff) const;

    Ui::MainWindow *ui;

    bool isBackupEnabled;
    QString backupPath;
    bool isStartupLoadEnabled;
    QString startupPath;

    Manager mainMngr;   // for all transaction data
};

#endif // MAINWINDOW_H
