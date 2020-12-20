#ifndef PURSE_H
#define PURSE_H

#include <QMainWindow>
#include "manager.h"

namespace Ui {
class Purse;
}

class Purse : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Purse(QWidget *parent = 0);
    ~Purse();
    
private:
    Ui::Purse *ui;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void showing(Manager mngr);
};

#endif // PURSE_H
