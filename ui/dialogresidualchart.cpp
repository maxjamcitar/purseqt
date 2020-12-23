#include "dialogresidualchart.h"
#include "ui_dialogresidualchart.h"

DialogResidualChart::DialogResidualChart(QWidget *parent, Manager* otherMngr) :
    QDialog(parent),
    ui(new Ui::DialogResidualChart)
{
    ui->setupUi(this);

    this->mngr = *otherMngr;

    QLineSeries *series = new QLineSeries();
    //todo fill data (function for that)

    Money resAverageMonth;
    int months = 0;
    QDate minDate = mngr.getMinDate();
    QDate maxDate = mngr.getMaxDate();
    QDate iterDate = minDate;
    double minValue = std::numeric_limits<double>::max();
    double maxValue = std::numeric_limits<double>::min();
    while (iterDate <= maxDate)
    {
        Money resThisMonth = mngr.residualDates(QDate(iterDate.year(), iterDate.month(), 1),
                                                QDate(iterDate.year(), iterDate.month(), iterDate.daysInMonth()));
        QDate iterDateMid(QDate(iterDate.year(), iterDate.month(), 15));
        series->append(iterDateMid.startOfDay().toMSecsSinceEpoch(), resThisMonth.getValue());

        if (resThisMonth.getValue() < minValue)
            minValue = resThisMonth.getValue();
        if (resThisMonth.getValue() > maxValue)
            maxValue = resThisMonth.getValue();

        resAverageMonth += resThisMonth;
        iterDate = iterDate.addMonths(1);
        months++;
    }
    double resAverageMonthValue = resAverageMonth.getValue();
    if (months != 0)
        resAverageMonth.setValue(resAverageMonthValue / months);

    QLineSeries *seriesAvg = new QLineSeries();
    seriesAvg->append(QDate(minDate.year(), minDate.month(), 15).startOfDay().toMSecsSinceEpoch(), resAverageMonthValue);
    seriesAvg->append(QDate(iterDate.addMonths(-1).year(), iterDate.addMonths(-1).month(), 15).startOfDay().toMSecsSinceEpoch(), resAverageMonthValue);

    QChart *chart = new QChart();
    chart->legend()->setVisible(true);
    series->setName("By month");
    chart->addSeries(series);
    seriesAvg->setName("Average");
    chart->addSeries(seriesAvg);
    chart->setTitle("Residual per month");

    QDateTimeAxis *axisX = new QDateTimeAxis;
    //axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Month");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    seriesAvg->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTickCount(10);
    double lowestY = std::min(minValue, resAverageMonthValue);
    double highestY = std::max(maxValue, resAverageMonthValue);
    axisY->setMin(lowestY*0.95);
    axisY->setMax(highestY*1.05);
    axisY->setLabelFormat("%i " + CurrConversion::activeCurrency);
    axisY->setTitleText("Residual");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    seriesAvg->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout* vboxLayout = new QVBoxLayout;
    vboxLayout->addWidget(chartView);
    this->setLayout(vboxLayout);

}

DialogResidualChart::~DialogResidualChart()
{
    delete ui;
}
