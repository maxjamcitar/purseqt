#ifndef DIALOGRESIDUALCHART_H
#define DIALOGRESIDUALCHART_H

#include <QDialog>
#include <QLineSeries>
#include <QtCharts>
#include <QVBoxLayout>
#include <src/manager.h>
#include <QDateTimeAxis>

namespace Ui {
class DialogResidualChart;
}

class DialogResidualChart : public QDialog
{
    Q_OBJECT

public:
    explicit DialogResidualChart(QWidget *parent = nullptr, Manager* otherMngr = nullptr);
    ~DialogResidualChart();

private:
    Ui::DialogResidualChart *ui;

    Manager mngr;
};

#endif // DIALOGRESIDUALCHART_H
