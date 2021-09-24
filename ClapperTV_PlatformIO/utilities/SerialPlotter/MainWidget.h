#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QProcess>

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>

class QPushButton;
class QTextBrowser;

// This is the declaration of our MainWidget class
// The definition/implementation is in mainwidget.cpp
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0); //Constructor
    ~MainWidget(); // Destructor

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QPushButton *button_;
    QtCharts::QChart *chart_;
    QtCharts::QLineSeries *series_;
};