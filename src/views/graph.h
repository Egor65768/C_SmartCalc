#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QVector>

extern "C" {
#include "../s21_calc.h"
}

namespace Ui {
class Graph;
}

class Graph : public QDialog {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

 private:
  Ui::Graph *ui;
  double xmin, xmax, ymin, ymax, h_step, X;
  int N;

  QVector<double> x, y;

 public slots:
  void slot(QString a);
 private slots:
  void on_pushButton_clicked();
};

#endif  // GRAPH_H
