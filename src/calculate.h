#ifndef CALCULATE_H
#define CALCULATE_H

#include <QVector>

#define STEPS 10000

void calculate(QVector<double> &x, QVector<double> &y);
void calculate(const char *function, QVector<double> &x, QVector<double> &y);
void parse_function(char *function);

#endif // CALCULATE_H
