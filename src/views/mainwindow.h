#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "credits.h"
#include "deposit.h"
#include "graph.h"

extern "C" {
#include "../s21_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  Graph *window;
  Credits *window2;
  Deposit *window3;

 private slots:
  void digits_numbers();
  void on_pushButton_clicked();

  void on_pushButton_10_clicked();

 signals:
  void signal(QString a);
  void signal2();
  void signal3();
};
#endif  // MAINWINDOW_H
