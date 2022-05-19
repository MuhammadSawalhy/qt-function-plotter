#include <QVector>
#include <QMessageBox>
#include <muParser.h>
#include "calculate.hpp"
#include "plot_settings.hpp"

void calculate(QVector<double> &x, QVector<double> &y) {
    calculate(plotSettings.function.c_str(), x, y);
}

void calculate(const char *function, QVector<double> &x, QVector<double> &y) {
    try {
        mu::Parser p;
        double x_value;
        p.DefineVar("x", &x_value);
        p.SetExpr(function);
        for (int i=0; i<STEPS; i++)
        {
            x_value = plotSettings.minX +
                   (plotSettings.maxX - plotSettings.minX) * i / STEPS;
            x[i] = x_value;
            y[i] = p.Eval();
        }
    } catch (mu::Parser::exception_type &e) {
        QMessageBox msg;
        msg.setText("Error while computing the curve points");
        msg.setDetailedText(e.GetMsg().c_str());
        msg.exec();
    }
}
