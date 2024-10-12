#include "graph.h"

#include <QMessageBox>

#include "ui_graph.h"

#define NUMBER_POINT 7500
#define STOCK_RATIO 1.01

Graph::Graph(QWidget* parent) : QDialog(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
  ui->widget->replot();
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  // Устанавливаем серый цвет фона для виджета
  ui->widget->setBackground(QBrush(Qt::lightGray));
  // Устанавливаем цвет осей
  ui->widget->xAxis->setBasePen(QPen(Qt::darkGray));
  ui->widget->yAxis->setBasePen(QPen(Qt::darkGray));
  // Устанавливаем цвет меток осей
  ui->widget->xAxis->setTickPen(QPen(Qt::gray));
  ui->widget->yAxis->setTickPen(QPen(Qt::gray));
  ui->widget->xAxis->setLabelColor(Qt::darkGray);
  ui->widget->yAxis->setLabelColor(Qt::darkGray);
  // Устанавливаем цвет сетки
  ui->widget->xAxis->grid()->setPen(QPen(Qt::lightGray, 1, Qt::SolidLine));
  ui->widget->yAxis->grid()->setPen(QPen(Qt::lightGray, 1, Qt::SolidLine));
  ui->widget->replot();
}

Graph::~Graph() { delete ui; }

void Graph::slot(QString a) { ui->line_func->setText(a); }

void Graph::on_pushButton_clicked() {
  int number_graf = 0;
  x.clear();
  y.clear();
  ui->widget->clearGraphs();
  xmin = ui->doubleSpinBox_xmin->value();
  xmax = ui->doubleSpinBox_xmax->value();
  ymin = ui->doubleSpinBox_ymin->value();
  ymax = ui->doubleSpinBox_ymax->value();
  QString label_oldline = ui->line_func->text();
  QByteArray byteArray = label_oldline.toUtf8();
  char* chararr = byteArray.data();
  if (xmax <= xmin) {
    QMessageBox::critical(this, "Некорректно введены данные",
                          "xmax должно быть больше xmin");
  } else if (ymax <= ymin) {
    QMessageBox::critical(this, "Некорректно введены данные",
                          "ymax должно быть больше ymin");
  } else if (check_for_x(chararr) == 0) {
    QMessageBox::critical(this, "Некорректно введены данные",
                          "Функция должна содержать x");
  } else if (validashion(chararr) != 0) {
    QMessageBox::critical(this, "Некорректно введены данные",
                          "Функция введена некорректно");
  } else {
    double h_step = (xmax - xmin) / NUMBER_POINT;
    ui->line_step->setText(QString::number(h_step));
    ui->widget->xAxis->setRange(STOCK_RATIO * xmin, STOCK_RATIO * xmax);
    ui->widget->yAxis->setRange(STOCK_RATIO * ymin, STOCK_RATIO * ymax);
    X = xmin;
    N = (xmax - xmin) / h_step + 2;
    int flag_error = 0;
    int flag_gap = 0;
    double res;
    for (; X <= xmax && flag_error != 1; X = X + h_step) {
      res = X;
      flag_error = calculate_from_expression(chararr, &res);
      if (flag_error == 0) {
        if (ymin <= res && res <= ymax) {
          x.push_back(X);
          y.push_back(res);
          flag_gap = 0;
        } else if (res <= ymin && flag_gap == 0) {
          flag_gap = 1;
          x.push_back(X);
          y.push_back(ymin);
          ui->widget->addGraph();
          ui->widget->graph(number_graf++)->setData(x, y);
          y.clear();
          x.clear();
        } else if (res >= ymax && flag_gap == 0) {
          flag_gap = 1;
          x.push_back(X);
          y.push_back(ymax);
          ui->widget->addGraph();
          ui->widget->graph(number_graf++)->setData(x, y);
          y.clear();
          x.clear();
        }
      }
    }
    if (flag_error == 0 || flag_error == 2) {
      ui->widget->addGraph();
      ui->widget->graph(number_graf++)->setData(x, y);
      ui->widget->replot();
    } else {
      QMessageBox::warning(
          this, "Предупреждение",
          "Неполучилось построить график, проверьте введенные данные. Возможно "
          "в область значения функции введеный промежуток полностью не входит");
    }
  }
}
