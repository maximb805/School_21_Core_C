#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->graph_widget->setInteraction(QCP::iRangeZoom, false);
  ui->graph_widget->setInteraction(QCP::iRangeDrag, false);
  ui->graph_widget->xAxis->setRange(-10, 10);
  ui->graph_widget->yAxis->setRange(-10, 10);
  ui->label_graph_error->setStyleSheet("color: rgb(200, 0, 0)");
  ui->label_error_credit->setStyleSheet("color: rgb(200, 0, 0)");

  connect(ui->pushButton_0, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_opBracket, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_clBracket, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_backspace, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));
  connect(ui->pushButton_clear, SIGNAL(clicked()), this,
          SLOT(s21_button_clicked()));

  connect(ui->pushButton_is, SIGNAL(clicked()), this, SLOT(s21_calculate()));

  connect(ui->pushButton_graph, SIGNAL(clicked()), this,
          SLOT(s21_print_graph()));

  connect(ui->pushButton_calc_credit, SIGNAL(clicked()), this,
          SLOT(s21_calculate_credit()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::s21_calculate_credit() {
  ui->label_error_credit->setText("");
  double total;
  double term;
  double rate;
  int type = ui->radioButton_annuity->isChecked() ? 1 : 2;
  int error_code = s21_get_credit_data(&total, &term, &rate);
  if (!error_code) {
    char total_payment[BUFFER_SIZE];
    char monthly[BUFFER_SIZE];
    char overpayment[BUFFER_SIZE];
    if (type == 1) {
      s21_calculate_credit_annuity(total, term, rate, total_payment, monthly,
                                   overpayment);
    } else {
      s21_calculate_credit_differentiated(total, term, rate, total_payment,
                                          monthly, overpayment);
    }
    ui->lineEdit_total_payment_credit->setText(total_payment);
    ui->lineEdit_monthly_payment_credit->setText(monthly);
    ui->lineEdit_overpayment_credit->setText(overpayment);
  } else {
    s21_print_credit_error(error_code);
  }
}

void MainWindow::s21_print_credit_error(int error_code) {
  switch (error_code) {
    case 1:
      ui->label_error_credit->setText(
          "Total credit amount value must be number");
      break;
    case 2:
      ui->label_error_credit->setText("Credit term value must be number");
      break;
    case 3:
      ui->label_error_credit->setText("Interest rate value must be number");
      break;
    case 4:
      ui->label_error_credit->setText(
          "Total credit amount value must be at least 0.01 rub.");
      break;
    case 5:
      ui->label_error_credit->setText(
          "Credit term value must be at least 1 month");
      break;
    case 6:
      ui->label_error_credit->setText("Credit term value must be integer");
      break;
    case 7:
      ui->label_error_credit->setText("Maximum interest rate value is 999");
      break;
    case 8:
      ui->label_error_credit->setText("Minimum interest rate value is 0.01");
      break;
  }
}

int MainWindow::s21_get_credit_data(double *total, double *term, double *rate) {
  char total_str[16] = {0};
  char term_str[10] = {0};
  char rate_str[10] = {0};
  strncpy(
      total_str,
      ui->lineEdit_total_credit_amount->text().toLocal8Bit().constData(),
      strlen(
          ui->lineEdit_total_credit_amount->text().toLocal8Bit().constData()));
  strncpy(term_str, ui->lineEdit_credit_term->text().toLocal8Bit().constData(),
          strlen(ui->lineEdit_credit_term->text().toLocal8Bit().constData()));
  strncpy(rate_str,
          ui->lineEdit_interest_rate->text().toLocal8Bit().constData(),
          strlen(ui->lineEdit_interest_rate->text().toLocal8Bit().constData()));
  int error_code = 0;
  if (!s21_is_double(total_str)) {
    error_code = 1;
  } else if (!s21_is_double(term_str)) {
    error_code = 2;
  } else if (!s21_is_double(rate_str)) {
    error_code = 3;
  }
  if (!error_code) {
    *total = s21_str_to_double(total_str);
    *term = s21_str_to_double(term_str);
    *rate = s21_str_to_double(rate_str);
    if (*total < 0.01) {
      error_code = 4;
    } else if (*term < 1.0) {
      error_code = 5;
    } else if (fmod(*term, 1.0) != 0.0) {
      error_code = 6;
    } else if (*rate > 999.0) {
      error_code = 7;
    } else if (*rate < 0.01) {
      error_code = 8;
    } else {
      s21_round_double(total);
      s21_round_double(term);
      s21_round_double(rate);
    }
  }
  return error_code;
}

void MainWindow::s21_print_graph() {
  ui->label_graph_error->setText("");
  double Ox1 = 0.0 / 0.0;
  double Ox2 = 0.0 / 0.0;
  double Oy1 = 0.0 / 0.0;
  double Oy2 = 0.0 / 0.0;
  char Ox1_str[12] = {0};
  char Ox2_str[12] = {0};
  char Oy1_str[12] = {0};
  char Oy2_str[12] = {0};
  strncpy(Ox1_str, ui->lineEdit_Ox1->text().toLocal8Bit().constData(),
          strlen(ui->lineEdit_Ox1->text().toLocal8Bit().constData()));
  strncpy(Ox2_str, ui->lineEdit_Ox2->text().toLocal8Bit().constData(),
          strlen(ui->lineEdit_Ox2->text().toLocal8Bit().constData()));
  strncpy(Oy1_str, ui->lineEdit_Oy1->text().toLocal8Bit().constData(),
          strlen(ui->lineEdit_Oy1->text().toLocal8Bit().constData()));
  strncpy(Oy2_str, ui->lineEdit_Oy2->text().toLocal8Bit().constData(),
          strlen(ui->lineEdit_Oy2->text().toLocal8Bit().constData()));
  int error_code = s21_get_field_borders(Ox1_str, Ox2_str, Oy1_str, Oy2_str,
                                         &Ox1, &Ox2, &Oy1, &Oy2);
  if (!error_code) {
    ui->graph_widget->xAxis->setRange(Ox1, Ox2);
    ui->graph_widget->yAxis->setRange(Oy1, Oy2);
    if (s21_is_function(ui->lineEdit_expr->text().toLocal8Bit().data())) {
      s21_zero_buffer(graph_buffer);
      int error = s21_get_postfix(output_buffer, graph_buffer);
      if (!error) {
        s21_print_curve(Ox1, Ox2, Oy1, Oy2);
      }
      s21_zero_buffer(graph_buffer);
    }
  } else {
    s21_print_graph_error(error_code);
  }
  ui->graph_widget->replot();
  if (ui->graph_widget->graphCount() > 0) {
    ui->graph_widget->clearGraphs();
  }
}

void MainWindow::s21_print_graph_error(int error_code) {
  switch (error_code) {
    case 1:
      ui->label_graph_error->setText("Border values must be numbers");
      break;
    case 2:
      ui->label_graph_error->setText(
          "Border values must be between -1000000 and 1000000");
      break;
    case 3:
      ui->label_graph_error->setText("Min value must be less than max");
      break;
  }
}

void MainWindow::s21_print_curve(double Ox1, double Ox2, double Oy1,
                                 double Oy2) {
  QVector<double> x_vector(100000);
  QVector<double> y_vector(100000);
  x_vector.fill(0.0 / 0.0);
  y_vector.fill(0.0 / 0.0);
  ui->graph_widget->addGraph();
  double x;
  double y;
  double prev_y = 0.0 / 0.0;
  char tmp[256] = {0};
  int points = 0;
  double step = fabs(Ox2 - Ox1) / 100000;
  for (x = Ox1; x <= Ox2 && points < 100000; x += step) {
    x_vector[points] = x;
    y = s21_get_answer(tmp, graph_buffer, x, ui->radioButton_grad->isChecked());
    if (!points) {
      if (y == y) {
        if (fabs(y) == 1.0 / 0.0) {
          y_vector[points] = y < 0 ? Oy1 : Oy2;
        } else {
          y_vector[points] = y;
        }
        points++;
      }
    } else if (y >= Oy1 && y <= Oy2) {
      if (y_vector[points - 1] != y_vector[points - 1]) {
        y_vector[points] = prev_y;
        x_vector[points] = x - step;
        points++;
      }
      x_vector[points] = x;
      y_vector[points] = y;
      points++;
    } else if (y_vector[points - 1] == y_vector[points - 1] && y == y &&
               fabs(y) != 1.0 / 0.0) {
      if (y > Oy2) {
        y_vector[points] = y_vector[points - 1] < Oy2 ? y : 0.0 / 0.0;
        points++;
      } else {
        y_vector[points] = y_vector[points - 1] > Oy1 ? y : 0.0 / 0.0;
        points++;
      }
    }
    prev_y = y;
  }
  ui->graph_widget->graph(0)->addData(x_vector, y_vector);
  x_vector.clear();
  y_vector.clear();
}

void MainWindow::s21_button_clicked() {
  QPushButton *button = (QPushButton *)sender();
  char arr[10] = {0};
  strncpy(arr, button->text().toLocal8Bit().constData(),
          strlen(button->text().toLocal8Bit().constData()));
  if (strlen(output_buffer) + strlen(arr) < 256 || !strcmp(arr, "<--") ||
      !strcmp(arr, "C")) {
    s21_append_buffer(arr, output_buffer);
  }
  ui->lineEdit_expr->setText(output_buffer);
}

void MainWindow::s21_calculate() {
  char ans[BUFFER_SIZE] = {0};
  char x_str[BUFFER_SIZE] = {0};
  double x = 0.0 / 0.0;
  strncpy(x_str, ui->lineEdit_x->text().toLocal8Bit().constData(),
          strlen(ui->lineEdit_x->text().toLocal8Bit().constData()));
  if (s21_is_double(x_str)) {
    x = s21_str_to_double(x_str);
  }
  int error = s21_get_postfix(output_buffer, ans);
  if (error) {
    sprintf(output_buffer, "Wrong expression");
  } else {
    s21_get_answer(output_buffer, ans, x, ui->radioButton_grad->isChecked());
  }
  ui->lineEdit_expr->setText(output_buffer);
  if (!s21_is_double(output_buffer)) {
    s21_zero_buffer(output_buffer);
  }
}
