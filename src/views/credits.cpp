#include "credits.h"

#include "mainwindow.h"
#include "ui_credits.h"

Credits::Credits(QWidget *parent) : QDialog(parent), ui(new Ui::Credits) {
  ui->setupUi(this);
  QPixmap pix(":/img/img/kartinki-ipoteka-26.jpg");
  int w = ui->image->width();
  int h = ui->image->height();
  ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
  ui->tableWidget->setColumnCount(6);
  ui->tableWidget->setHorizontalHeaderLabels(
      QStringList() << "Дата платежа" << "Осавшееся кол-во платежей"
                    << "Сумма платежа" << "Платеж по основному долгу"
                    << "Платеж по процентам" << "Остаток долга");
  ui->tableWidget->resizeColumnsToContents();
  ui->tableWidget->setRowCount(6);
  ui->dateEdit->setDate(QDate::currentDate());
}

Credits::~Credits() { delete ui; }

void Credits::slotic() {
  ui->radioButton_month->setChecked(true);
  ui->radioButton_an->setChecked(true);
}

void Credits::on_pushButton_res_clicked() {
  CREDIT credits{};
  if (ui->radioButton_month->isChecked()) {
    credits.num_mont = ui->spinBox->value();
  } else if (ui->radioButton_year->isChecked()) {
    credits.num_mont = ui->spinBox->value() * 12;
  }
  if (ui->radioButton_an->isChecked()) {
    credits.type = annuity_loan;
  } else {
    credits.type = deferred_loan;
  }
  credits.ful_sum = ui->doubleSpinBox_sum->value();
  credits.persent_year = ui->doubleSpinBox_persent->value();
  int res = 0;
  QDate date_pay = ui->dateEdit->date().addMonths(1);
  int month_number = 0;
  ui->tableWidget->setRowCount(credits.num_mont + 1);
  while (res == 0) {
    res = s21_calculate_credit_payment(&credits);
    QTableWidgetItem *table_new;
    table_new = new QTableWidgetItem(date_pay.toString("dd.MM.yyyy"));
    ui->tableWidget->setItem(month_number, 0, table_new);
    table_new = new QTableWidgetItem(
        QString::number(credits.num_mont - credits.current_month));
    ui->tableWidget->setItem(month_number, 1, table_new);
    table_new =
        new QTableWidgetItem(QString::number(credits.month_sum, 'f', 2));
    ui->tableWidget->setItem(month_number, 2, table_new);
    table_new = new QTableWidgetItem(QString::number(credits.main_pay, 'f', 2));
    ui->tableWidget->setItem(month_number, 3, table_new);
    table_new =
        new QTableWidgetItem(QString::number(credits.month_persent, 'f', 2));
    ui->tableWidget->setItem(month_number, 4, table_new);
    table_new = new QTableWidgetItem(QString::number(credits.remains, 'f', 2));
    ui->tableWidget->setItem(month_number, 5, table_new);
    month_number++;
  }
  month_number = credits.num_mont;
  QTableWidgetItem *table_new;
  table_new = new QTableWidgetItem("Итого:");
  ui->tableWidget->setItem(month_number, 0, table_new);
  table_new = new QTableWidgetItem("-");
  ui->tableWidget->setItem(month_number, 1, table_new);
  table_new = new QTableWidgetItem("-");
  ui->tableWidget->setItem(month_number, 5, table_new);
  table_new = new QTableWidgetItem(QString::number(credits.all_pay, 'f', 2));
  ui->tableWidget->setItem(month_number, 2, table_new);
  table_new = new QTableWidgetItem(QString::number(credits.ful_sum, 'f', 2));
  ui->tableWidget->setItem(month_number, 3, table_new);
  table_new = new QTableWidgetItem(
      QString::number(credits.all_pay - credits.ful_sum, 'f', 2));
  ui->tableWidget->setItem(month_number, 4, table_new);

  ui->tableWidget->resizeColumnsToContents();
}
