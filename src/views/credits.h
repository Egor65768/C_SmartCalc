#ifndef CREDITS_H
#define CREDITS_H

#include <QDialog>
#include <QPixmap>

extern "C" {
#include "../s21_calc.h"
}

namespace Ui {
class Credits;
}

class Credits : public QDialog {
  Q_OBJECT

 public:
  explicit Credits(QWidget *parent = nullptr);
  ~Credits();

 private:
  Ui::Credits *ui;

 public slots:
  void slotic();
 private slots:
  void on_pushButton_res_clicked();
};

#endif  // CREDITS_H
