#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QDate>
#include <QDialog>

extern "C" {
#include "../s21_calc.h"
}

namespace Ui {
class Deposit;
}

class Deposit : public QDialog {
  Q_OBJECT

 public:
  explicit Deposit(QWidget *parent = nullptr);
  ~Deposit();

 public slots:
  void slotics();

 private slots:
  void on_pushButton_clicked();
  void setDepositDataInTable(DEPOSIT s21_dep, int i, QDate date_now);
  void addSummaryRowToTable(DEPOSIT s21_dep);
  void base_table();
  void base_table_add();
  void on_pushButton_2_clicked();
  void updateDepositOnDate(QDate date_now, DEPOSIT *s21_dep, int *i);
  void addRowToDepositTable(DEPOSIT s21_dep, int i, QDate date_now);
  void on_pushButton_3_clicked();
  void processTaxPayment(QDate date_now, DEPOSIT *s21_dep, double no_taxsum);
  void tax_table();

 private:
  Ui::Deposit *ui;
};

#endif  // DEPOSIT_H
