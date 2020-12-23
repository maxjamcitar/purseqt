#include "ui/mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/dialogaddincome.h"
#include "ui/dialogaddexpense.h"
#include "ui/dialogeditincome.h"
#include "ui/dialogeditexpense.h"

enum TABCOLUMN {CLASSTR = 0, DATE, VALUE, GOODSSOURCE, COMMENT};    // change if column order changes

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isBackupEnabled = true;
    backupPath = QDir::currentPath() + QString("\\backup.bin");

    isStartupLoadEnabled = true;
    startupPath = QDir::currentPath() + QString("\\startup.bin");

    // make window not resizable
    setFixedSize( QSize(this->geometry().size()) );

    // currency initialization
    CurrConversion::addCurrency("USD", 1);
    CurrConversion::addCurrency("EUR", 0.82);  // todo import coef from elsewhere
    CurrConversion::addCurrency("RUB", 73.68);  // todo import coef from elsewhere
    CurrConversion::addCurrency("GBP", 0.75);  // todo import coef from elsewhere
    CurrConversion::changeActiveCurrency("RUB");
    CurrConversion().requestRatesHttp();

    // context menu on top
    connect(ui->actionAddIncome, SIGNAL(triggered()), this, SLOT(addIncome()));
    connect(ui->actionAddExpense, SIGNAL(triggered()), this, SLOT(addExpense()));
    connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(dialogLoadFile()));
    connect(ui->actionSaveAs, SIGNAL(triggered()), this, SLOT(dialogSaveFileAs()));

    InitializeActCurrencyComboBox();
    ui->tableTransactions->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableTransactions->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableTransactions->setContextMenuPolicy(Qt::CustomContextMenu);

    //try to load from startup.bin
    loadFile(startupPath);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitializeActCurrencyComboBox()
{
    ui->comboBoxActiveCurrency->addItem(CurrConversion::activeCurrency);  // to make active curr on top
    for (auto iter = CurrConversion::currencyList.begin(); iter != CurrConversion::currencyList.end(); ++iter)
    {
        if (*iter != CurrConversion::activeCurrency)
            ui->comboBoxActiveCurrency->addItem(*iter);
    }
}

void MainWindow::addIncome()
{
    DialogAddIncome addIncomeDialog;
    if (addIncomeDialog.exec() == QDialog::Accepted)
    {
        QDate newDate = addIncomeDialog.getDate();
        Money newMoney = addIncomeDialog.getMoney();
        QString newSource = addIncomeDialog.getSource();
        QString newComment = addIncomeDialog.getComment();
        QSharedPointer<Income> newInc = QSharedPointer<Income>::create(newDate, newMoney, newComment, newSource);
        QSharedPointer<Transaction> newTrans = qSharedPointerDynamicCast<Transaction>(newInc);
        mainMngr.addEnd(newInc);

        updateMngrInTable(mainMngr);
    }
}

void MainWindow::addExpense()
{
    DialogAddExpense addExpenseDialog;
    if (addExpenseDialog.exec() == QDialog::Accepted)
    {
        QDate newDate = addExpenseDialog.getDate();
        Money newMoney = addExpenseDialog.getMoney();
        QString newGoods = addExpenseDialog.getGoods();
        QString newComment = addExpenseDialog.getComment();
        QSharedPointer<Expense> newInc = QSharedPointer<Expense>::create(newDate, newMoney, newComment, newGoods);
        QSharedPointer<Transaction> newTrans = qSharedPointerDynamicCast<Transaction>(newInc);
        mainMngr.addEnd(newInc);

        updateMngrInTable(mainMngr);
    }
}

void MainWindow::dialogLoadFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load file"), QDir::currentPath(), tr("*.bin files"));
    if (fileName.size())
    {
        loadFile(fileName);
    }
}

void MainWindow::dialogSaveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Load file"), QDir::currentPath(), tr("*.bin files"));
    if (fileName.size())
    {
        saveFile(fileName);
    }
}

bool MainWindow::loadFile(const QString& fileName)
{
    if (mainMngr.readFile(fileName))
    {
        updateMngrInTable(mainMngr);
        return true;
    }
    else
    {
        qDebug() << "Failed to load file " + fileName + ".";
        return false;
    }
}

bool MainWindow::saveFile(const QString& fileName)
{
    if (mainMngr.writeFile(fileName))
    {
        return true;
    }
    else
    {
        qDebug() <<  "Failed to save in file " + fileName + ".";
        return false;
    }
}

void MainWindow::editTransaction()
{
    int tabRow = ui->tableTransactions->currentRow();
    QSharedPointer<Transaction> rowTrans = mainMngr.getAt(tabRow);
    if (rowTrans->getClassType() == "Income")
    {
        QSharedPointer<Income> rowInc = qSharedPointerDynamicCast<Income>(rowTrans);
        DialogEditIncome editIncomeDialog(this, &rowInc);
        if (editIncomeDialog.exec() == QDialog::Accepted)
        {
            QSharedPointer<Income> newRowInc = QSharedPointer<Income>::create(*(editIncomeDialog.getIncome()));
            QSharedPointer<Transaction> newTransInc = qSharedPointerDynamicCast<Transaction>(newRowInc);
            mainMngr.setAt(tabRow, newTransInc);
            updateMngrInTable(mainMngr);
        }
    }
    else if (rowTrans->getClassType() == "Expense")
    {
        QSharedPointer<Expense> rowExp = qSharedPointerDynamicCast<Expense>(rowTrans);
        DialogEditExpense editExpenseDialog(this, &rowExp);
        if (editExpenseDialog.exec() == QDialog::Accepted)
        {
            QSharedPointer<Expense> newRowExp = QSharedPointer<Expense>::create(*(editExpenseDialog.getExpense()));
            QSharedPointer<Transaction> newTransExp = qSharedPointerDynamicCast<Transaction>(newRowExp);
            mainMngr.setAt(tabRow, newTransExp);
            updateMngrInTable(mainMngr);
        }
    }
    else
        qDebug() << "Failed to extract transaction from " << tabRow << " row";
}

void MainWindow::removeTransaction()
{
    int index = ui->tableTransactions->currentRow();
    mainMngr.delAt(index);
    updateMngrInTable(mainMngr);
}

void MainWindow::updateMngrInTable(const Manager& argMngr)
{
    auto mngrVec = argMngr.getVector();
    ui->tableTransactions->clearContents();
    ui->tableTransactions->setRowCount(mngrVec.size());

    for (auto i = 0; i < mngrVec.size(); ++i)
    {
        QSharedPointer<Transaction> iterTrans = mngrVec.at(i);

        // adding inc/exp
        QTableWidgetItem *twClassType = new QTableWidgetItem
                (iterTrans->getClassType());
        ui->tableTransactions->setItem(i,TABCOLUMN(CLASSTR),twClassType);

        // adding date
        QTableWidgetItem *twDate = new QTableWidgetItem
                (iterTrans->getDate().toString("dd/MM/yyyy"));
        ui->tableTransactions->setItem(i,TABCOLUMN(DATE),twDate);

        // adding value
        Money transMoney (iterTrans->getMoney());
        QTableWidgetItem *twMoney = new QTableWidgetItem
                (transMoney.to_str(" "));
        ui->tableTransactions->setItem(i,TABCOLUMN(VALUE),twMoney);

        // adding comment
        QTableWidgetItem *twComment = new QTableWidgetItem
                (iterTrans->getComment());
        ui->tableTransactions->setItem(i,TABCOLUMN(COMMENT),twComment);

        if (iterTrans->getClassType() == QString("Income"))
        {
            QSharedPointer<Income> iterInc = qSharedPointerDynamicCast<Income>(iterTrans);

            // adding source
            QTableWidgetItem *twSource = new QTableWidgetItem
                    (iterInc->getSource());
            ui->tableTransactions->setItem(i,TABCOLUMN(GOODSSOURCE),twSource);
        }
        else if (iterTrans->getClassType() == QString("Expense"))
        {
            QSharedPointer<Expense> iterExp = qSharedPointerDynamicCast<Expense>(iterTrans);

            // adding goods
            QTableWidgetItem *twGoods = new QTableWidgetItem
                    (iterExp->getGoods());
            ui->tableTransactions->setItem(i,TABCOLUMN(GOODSSOURCE),twGoods);
        }
    }

    if (isBackupEnabled)
        saveFile(backupPath);

    //todo stats update, balance check
}

void MainWindow::on_comboBoxActiveCurrency_currentTextChanged(const QString &arg1)
{
    CurrConversion::changeActiveCurrency(arg1);
}

void MainWindow::on_tableTransactions_customContextMenuRequested(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);

    QAction editItemAction = QAction(tr("Edit item"), this);
    connect(&editItemAction, SIGNAL(triggered()), this, SLOT(editTransaction()));
    contextMenu.addAction(&editItemAction);

    QAction deleteItemAction = QAction(tr("Delete item"), this);
    connect(&deleteItemAction, SIGNAL(triggered()), this, SLOT(removeTransaction()));
    contextMenu.addAction(&deleteItemAction);

    contextMenu.exec(ui->tableTransactions->mapToGlobal(pos));
}

void MainWindow::on_buttonConvertMngr_clicked()
{
    auto mngrVec = mainMngr.getVector();
    for (auto iter = mngrVec.begin(); iter != mngrVec.end(); ++iter)
    {
        Money currentPrice = (*iter)->getMoney();
        currentPrice.convertTo(CurrConversion::activeCurrency);
        (*iter)->setMoney(currentPrice);
    }
    updateMngrInTable(mainMngr);
}
