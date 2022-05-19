#include <iostream>
#include "mainwindow.h"
#include "QString"
#include "ui_mainwindow.h"
#include "plot_settings.h"
#include "calculate.h"

bool isFirstPlot = true;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plot()
{
    QString function = this->ui->functionInput->text();
    this->plot(function.toStdString().c_str());
}

void MainWindow::plot(const char *function)
{
  QCustomPlot *customPlot = this->ui->customPlotCanvas;
  QVector<double> x(STEPS), y(STEPS);
  calculate(function, x, y);
  this->setWindowTitle(function);
  customPlot->addGraph();
  customPlot->graph(0)->setName(function);
  customPlot->graph(0)->setData(x, y);
  customPlot->graph(0)->rescaleAxes();
  customPlot->xAxis->setLabel("x");
  customPlot->yAxis->setLabel("y");
  customPlot->replot();
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void MainWindow::on_plotBtn_clicked()
{
    PlotSettings *newSettings = new PlotSettings();
    newSettings->minX = this->ui->minX->value();
    newSettings->maxX = this->ui->maxX->value();
    newSettings->function = this->ui->functionInput->text().toStdString();

    if (updatePlotSettings(newSettings)) {
        this->plot();
        if (isFirstPlot) {
            QMessageBox msg;
            msg.setText("You mouse to move and zoom in/out 🖱");
            msg.exec();
        }
        isFirstPlot = false;
    }
}
