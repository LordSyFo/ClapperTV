#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>

#include "MainWidget.h"

#include <iostream>

QT_CHARTS_USE_NAMESPACE

// Constructor for main widget
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    chart_(new QChart),
    series_(new QLineSeries)
{
    size_t height,width;
    height = 800;
    width = 600;
    resize(width, height);

    // Setup chart
    QChartView *chartView = new QChartView(chart_);
    chartView->setMinimumSize(800, 600);
    chart_->addSeries(series_);
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 100);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Samples");
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 5000);
    axisY->setTitleText("Audio level");
    chart_->addAxis(axisX, Qt::AlignBottom);
    series_->attachAxis(axisX);
    chart_->addAxis(axisY, Qt::AlignLeft);
    series_->attachAxis(axisY);
    chart_->legend()->hide();
    chart_->setTitle("Dummy title");


    button_ = new QPushButton(tr("Push Me!"));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(chartView,0,0);

    setLayout(mainLayout);
   
    setWindowTitle(tr("Connecting buttons to processes.."));
}

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    static int level = 0;
    for (size_t i = 0; i < 100; i++)
    {
        *series_ << QPoint(i,level);
    }
    level += 10;
}


// Destructor
MainWidget::~MainWidget()
{
}