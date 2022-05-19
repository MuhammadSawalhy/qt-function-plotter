#include <iostream>
#include "mainwindow.hpp"
#include "QString"
#include "ui_mainwindow.h"
#include "plot_settings.hpp"
#include "calculate.hpp"

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

    std::string statusMsg = "Current plot: ";
    statusMsg += function;
    this->setWindowTitle(statusMsg.c_str());
    this->ui->statusBar->showMessage(statusMsg.c_str());

    customPlot->clearGraphs();
    customPlot->addGraph();
    customPlot->graph(0)->setName(function);
    customPlot->graph(0)->setData(x, y);
    customPlot->graph(0)->rescaleAxes();
    customPlot->xAxis->setRange(-10, 10);
    customPlot->yAxis->setRange(-10, 10);
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

    std::string errMsg = updatePlotSettings(newSettings);
    std::cout << errMsg << std::endl;

    if (!errMsg.empty()) {
        QMessageBox msg;
        msg.setText("Invalid plot settings");
        msg.setDetailedText(errMsg.c_str());
        msg.exec();
        return;
    }

    if (isFirstPlot) {
        QMessageBox msg;
        msg.setText("Use your mouse to move and zoom in/out 🖱");
        msg.exec();
        isFirstPlot = false;
    }

    this->plot();
}
