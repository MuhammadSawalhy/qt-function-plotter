#include <iostream>
#include "mainwindow.h"
#include "QString"
#include "./ui_mainwindow.h"
#include "./plot_settings.h"

#define STEPS 1000

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

  for (int i=0; i<STEPS; i++)
  {
    x[i] = plotSettings->minX +
           (plotSettings->maxX - plotSettings->minX) * i / STEPS;
    y[i] = x[i]*x[i];
  }

  this->setWindowTitle(function);
  customPlot->addGraph();
  customPlot->graph(0)->setName(function);
  customPlot->graph(0)->setData(x, y);
  customPlot->graph(0)->rescaleAxes();
  customPlot->xAxis->setLabel("x");
  customPlot->yAxis->setLabel("y");
  customPlot->replot();
}

void MainWindow::on_plotBtn_clicked()
{
    PlotSettings *newSettings = new PlotSettings();
    newSettings->minX = this->ui->minX->value();
    newSettings->maxX = this->ui->maxX->value();
    newSettings->function = this->ui->functionInput->text().toStdString();

    if (updatePlotSettings(newSettings)) {
        this->plot();
    }
}
