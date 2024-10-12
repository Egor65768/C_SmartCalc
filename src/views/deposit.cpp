#include "deposit.h"

#include <QMessageBox>

#include "mainwindow.h"
#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) : QDialog(parent), ui(new Ui::Deposit) {
  ui->setupUi(this);
  ui->tableWidget_2->clear();
  ui->tableWidget->clear();
  base_table();
  base_table_add();
  tax_table();
}

void Deposit::slotics() {
  ui->radioButton_month->setChecked(true);
  ui->radioButton_inmonth->setChecked(true);
  ui->radioButton_havcap->setChecked(true);
  ui->radioButton_push->setChecked(true);
  ui->dateEdit_2->setDate(QDate::currentDate().addMonths(1));
}

Deposit::~Deposit() { delete ui; }

void Deposit::tax_table() {
  ui->tableWidget_3->clear();
  ui->tableWidget_3->setColumnCount(4);
  ui->tableWidget_3->setHorizontalHeaderLabels(
      QStringList() << "Год" << "Доход" << "Налоговый вычет"
                    << "Налог с учетом вычета");
  ui->tableWidget_3->setRowCount(0);
  ui->tableWidget_3->resizeColumnsToContents();
}

void Deposit::base_table() {
  ui->tableWidget->setColumnCount(5);
  ui->tableWidget->setHorizontalHeaderLabels(
      QStringList() << "Дата" << "Начисление по вкладу" << "Выплаты по вкладу"
                    << "Изменение баланса" << "Денег на счету");
  ui->tableWidget->resizeColumnsToContents();
  ui->tableWidget->setRowCount(6);
  ui->dateEdit->setDate(QDate::currentDate());
}

void Deposit::base_table_add() {
  ui->tableWidget_2->setColumnCount(3);
  ui->tableWidget_2->setHorizontalHeaderLabels(
      QStringList() << "Дата" << "Сумма" << "Тип операции");
  ui->tableWidget_2->setRowCount(0);
}

void Deposit::addSummaryRowToTable(DEPOSIT s21_dep) {
  QTableWidgetItem *table_new;
  int count = ui->tableWidget->rowCount() - 1;
  table_new = new QTableWidgetItem("Итог");
  ui->tableWidget->setItem(count, 0, table_new);
  table_new = new QTableWidgetItem(QString::number(s21_dep.money, 'f', 2));
  ui->tableWidget->setItem(count, 1, table_new);
  table_new = new QTableWidgetItem("-");
  ui->tableWidget->setItem(count, 2, table_new);
  table_new = new QTableWidgetItem("-");
  ui->tableWidget->setItem(count, 3, table_new);
  table_new = new QTableWidgetItem(QString::number(s21_dep.ful_sum, 'f', 2));
  ui->tableWidget->setItem(count, 4, table_new);
}

void Deposit::setDepositDataInTable(DEPOSIT s21_dep, int i, QDate date_now) {
  QTableWidgetItem *table_new;
  table_new = new QTableWidgetItem(date_now.toString("dd.MM.yyyy"));
  ui->tableWidget->setItem(i, 0, table_new);
  table_new =
      new QTableWidgetItem(QString::number(s21_dep.money_month, 'f', 2));
  ui->tableWidget->setItem(i, 1, table_new);
  table_new = new QTableWidgetItem(QString::number(s21_dep.payments, 'f', 2));
  ui->tableWidget->setItem(i, 2, table_new);
  table_new = new QTableWidgetItem(QString::number(s21_dep.delta, 'f', 2));
  ui->tableWidget->setItem(i, 3, table_new);
  table_new = new QTableWidgetItem(QString::number(s21_dep.ful_sum, 'f', 2));
  ui->tableWidget->setItem(i, 4, table_new);
}

void Deposit::addRowToDepositTable(DEPOSIT s21_dep, int i, QDate date_now) {
  if (i != 0) {
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
  }
  QTableWidgetItem *table_new;
  table_new = new QTableWidgetItem(date_now.toString("dd.MM.yyyy"));
  ui->tableWidget->setItem(i, 0, table_new);
  table_new = new QTableWidgetItem("-");
  ui->tableWidget->setItem(i, 1, table_new);
  table_new = new QTableWidgetItem("-");
  ui->tableWidget->setItem(i, 2, table_new);
  if (i == 0) {
    table_new = new QTableWidgetItem(QString::number(s21_dep.ful_sum, 'f', 2));
  } else {
    table_new =
        new QTableWidgetItem(QString::number(s21_dep.add_or_sub, 'f', 2));
  }
  ui->tableWidget->setItem(i, 3, table_new);
  table_new = new QTableWidgetItem(QString::number(s21_dep.ful_sum, 'f', 2));
  ui->tableWidget->setItem(i, 4, table_new);
}

void Deposit::on_pushButton_clicked() {
  DEPOSIT s21_dep;
  s21_dep.add_or_sub = 0;
  s21_dep.money_year = 0;
  s21_dep.delta = 0;
  ui->tableWidget->clear();
  base_table();
  tax_table();
  int row_count = 0;
  s21_dep.ful_sum = ui->doubleSpinBox->value();
  if (ui->radioButton_month->isChecked()) {
    s21_dep.num_month = ui->spinBox->value();
  } else {
    s21_dep.num_month = ui->spinBox->value() * 12;
  }
  s21_dep.persent_year = ui->spinBox_bankpersent->value();
  s21_dep.central_banck_percen = ui->spinBox_centralbank->value();
  s21_dep.tax = ui->spinBox_nalog->value();
  double notaxsum = 10000 * s21_dep.central_banck_percen;
  ui->input->setText(QString::number(notaxsum));
  QDate start_date = ui->dateEdit->date();
  QDate end_date = start_date.addMonths(s21_dep.num_month);
  if (ui->radioButton_havcap->isChecked()) {
    s21_dep.type = capitalization;
  } else {
    s21_dep.type = pay;
  }
  QDate bufer = start_date;
  QDate tax_date = start_date;
  tax_date.setDate(start_date.year() + 1, 1, 1);
  int count_day = start_date.daysTo(end_date);
  if (ui->radioButton_inday->isChecked()) {
    s21_dep.type_pay = every_day;
    row_count = count_day;
  } else if (ui->radioButton_inweek->isChecked()) {
    s21_dep.type_pay = every_month;
    row_count = count_day / 7 + 1;
  } else if (ui->radioButton_inmonth->isChecked()) {
    s21_dep.type_pay = every_week;
    row_count = s21_dep.num_month;
    bufer = bufer.addMonths(1);
  } else if (ui->radioButton_inyear->isChecked()) {
    row_count = s21_dep.num_month / 12;
    if (s21_dep.num_month % 12 != 0) {
      row_count++;
    }
    s21_dep.type_pay = every_year;
    bufer = bufer.addYears(1);
  } else {
    row_count = 1;
    s21_dep.type_pay = at_the_end_of_the_term;
  }
  row_count++;
  int day_for_last_pay = 0;
  int payment_number = 1;
  ui->tableWidget->setRowCount(row_count);
  addRowToDepositTable(s21_dep, 0, start_date);
  for (QDate date_now = start_date; date_now.daysTo(end_date) >= 0;
       date_now = date_now.addDays(1)) {
    if (day_for_last_pay == 1 && s21_dep.type_pay == every_day) {
      s21_calculate_deposit_interest(&s21_dep, date_now.daysInYear(),
                                     day_for_last_pay);
      setDepositDataInTable(s21_dep, payment_number, date_now);
      payment_number++;
      day_for_last_pay = 0;
    } else if (day_for_last_pay == 7 && s21_dep.type_pay == every_week) {
      s21_calculate_deposit_interest(&s21_dep, date_now.daysInYear(),
                                     day_for_last_pay);
      setDepositDataInTable(s21_dep, payment_number, date_now);
      payment_number++;
      day_for_last_pay = 0;
    } else if (bufer == date_now && s21_dep.type_pay == every_month) {
      s21_calculate_deposit_interest(&s21_dep, date_now.daysInYear(),
                                     day_for_last_pay);
      setDepositDataInTable(s21_dep, payment_number, date_now);
      payment_number++;
      day_for_last_pay = 0;
      bufer = bufer.addMonths(1);

    } else if (bufer == date_now && s21_dep.type_pay == every_year) {
      s21_calculate_deposit_interest(&s21_dep, date_now.daysInYear(),
                                     day_for_last_pay);
      setDepositDataInTable(s21_dep, payment_number, date_now);
      payment_number++;
      day_for_last_pay = 0;
      bufer = bufer.addYears(1);
    }
    updateDepositOnDate(date_now, &s21_dep, &payment_number);
    if (tax_date == date_now) {
      processTaxPayment(date_now, &s21_dep, notaxsum);
      tax_date.setDate(tax_date.year() + 1, 1, 1);
    } else if (date_now == end_date) {
      QDate bufDate = date_now;
      bufDate = bufDate.addYears(1);
      processTaxPayment(bufDate, &s21_dep, notaxsum);
    }
    day_for_last_pay++;
  }
  if (day_for_last_pay > 1) {
    s21_calculate_deposit_interest(&s21_dep, end_date.daysInYear(),
                                   day_for_last_pay);
    setDepositDataInTable(s21_dep, payment_number, end_date);
  }
  ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
  addSummaryRowToTable(s21_dep);
  ui->tableWidget->resizeColumnsToContents();
  ui->tableWidget_3->resizeColumnsToContents();
}

void Deposit::processTaxPayment(QDate date_now, DEPOSIT *s21_dep,
                                double no_taxsum) {
  ui->tableWidget_3->setRowCount(ui->tableWidget_3->rowCount() + 1);
  int count = ui->tableWidget_3->rowCount() - 1;
  double real_tax = s21_dep->money_year - no_taxsum;
  if (real_tax > 0) {
    real_tax = real_tax * s21_dep->central_banck_percen / 100;
    s21_dep->tax = s21_dep->tax + real_tax;
  } else {
    real_tax = 0;
  }
  QTableWidgetItem *table_new;
  table_new = new QTableWidgetItem(QString::number(date_now.year() - 1));
  ui->tableWidget_3->setItem(count, 0, table_new);
  table_new =
      new QTableWidgetItem(QString::number(s21_dep->money_year, 'f', 2));
  ui->tableWidget_3->setItem(count, 1, table_new);
  table_new = new QTableWidgetItem(QString::number(no_taxsum, 'f', 2));
  ui->tableWidget_3->setItem(count, 2, table_new);
  table_new = new QTableWidgetItem(QString::number(real_tax, 'f', 2));
  ui->tableWidget_3->setItem(count, 3, table_new);
  s21_dep->money_year = 0;
}

void Deposit::updateDepositOnDate(QDate date_now, DEPOSIT *s21_dep, int *i) {
  int count = ui->tableWidget_2->rowCount();
  for (int j = 0; j < count; j++) {
    QDate tmpdate =
        QDate::fromString(ui->tableWidget_2->item(j, 0)->text(), "dd.MM.yyyy");
    if (date_now == tmpdate) {
      s21_dep->add_or_sub = ui->tableWidget_2->item(j, 1)->text().toDouble();
      s21_dep->ful_sum = s21_dep->ful_sum + s21_dep->add_or_sub;
      addRowToDepositTable(*s21_dep, *i, date_now);
      *i = *i + 1;
    }
  }
}

void Deposit::on_pushButton_2_clicked() {
  int type_oper = 0;
  double value = ui->doubleSpinBox_2->value();
  if (ui->radioButton_push->isChecked()) {
    type_oper = 1;

  } else {
    type_oper = 2;
    value = -value;
  }
  ui->tableWidget_2->setRowCount(ui->tableWidget_2->rowCount() + 1);
  QTableWidgetItem *table_new;
  table_new =
      new QTableWidgetItem(ui->dateEdit_2->date().toString("dd.MM.yyyy"));
  ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 0, table_new);
  table_new = new QTableWidgetItem(QString::number(value, 'f', 2));
  ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 1, table_new);
  if (type_oper == 1) {
    table_new = new QTableWidgetItem("Пополнение");
  } else {
    table_new = new QTableWidgetItem("Снятие");
  }
  ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 2, table_new);
  QDate buf = ui->dateEdit_2->date();
  buf = buf.addMonths(1);
  ui->dateEdit_2->setDate(buf);
}

void Deposit::on_pushButton_3_clicked() {
  int count_number = 0;
  count_number = ui->spinBox_2->value() - 1;
  if (ui->tableWidget_2->rowCount() > count_number) {
    ui->tableWidget_2->removeRow(count_number);
  } else {
    QMessageBox::warning(this, "Предупреждение",
                         "Операции под таким номером нет");
  }
}
