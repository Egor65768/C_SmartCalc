#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  window = new Graph;
  window2 = new Credits;
  window3 = new Deposit;
  connect(this, &MainWindow::signal, window, &Graph::slot);
  connect(this, &MainWindow::signal2, window2, &Credits::slotic);
  connect(this, &MainWindow::signal3, window3, &Deposit::slotics);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_res, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_close, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_minus_close, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_dellast, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_graf, SIGNAL(clicked()), this, SLOT(digits_numbers()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  if ((button == ui->pushButton_AC) || (ui->lineEdit->text() == "Error")) {
    ui->lineEdit->setText("0");
  } else if (button == ui->pushButton_res && ui->lineEdit->text() == "0") {
  } else if (button == ui->pushButton_res &&
             !(ui->lineEdit->text().isEmpty())) {
    QString label_oldline = ui->lineEdit->text();
    QByteArray byteArray = label_oldline.toUtf8();
    char *charArray = byteArray.data();
    double resultat = ui->doubleSpinBox->value();
    int flag_error = calculator(charArray, &resultat);
    ui->lineEdit->setText("0");
    if (flag_error == 0) {
      QString str = QString::number(resultat, 'f', 7);
      ui->lineEdit->setText(str);
    } else {
      ui->lineEdit->setText("Error");
    }

  } else if (button == ui->pushButton_res && (ui->lineEdit->text().isEmpty())) {
    ui->lineEdit->setText("Error");
  } else if (button == ui->pushButton_dellast) {
    QString text = ui->lineEdit->text();
    if (!text.isEmpty()) {
      text.chop(1);
    }
    if (!text.isEmpty()) {
      ui->lineEdit->setText(text);
    } else {
      ui->lineEdit->setText("0");
    }

  } else if (button == ui->pushButton_graf) {
    window->setWindowTitle("Построение графиков");
    window2->close();
    window->show();
    emit signal(ui->lineEdit->text());
  } else {
    if (ui->lineEdit->text() == "0") {
      ui->lineEdit->clear();
    }
    QString label_oldline = ui->lineEdit->text();
    QString new_label = button->text();
    ui->lineEdit->setText(label_oldline + new_label);
  }
}

void MainWindow::on_pushButton_clicked() {
  window->close();
  window3->close();
  window2->setWindowTitle("Кредитный калькулятор");
  window2->show();
  emit signal2();
}

void MainWindow::on_pushButton_10_clicked() {
  window->close();
  window2->close();
  window3->setWindowTitle("Депоитный калькулятор");
  window3->show();
  emit signal3();
}
