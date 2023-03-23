#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "./qcustomplot.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "../s21_smart_calc.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

  char output_buffer[BUFFER_SIZE] = {0};
  char graph_buffer[BUFFER_SIZE] = {0};

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

 private slots:
  void s21_button_clicked();
  void s21_calculate();
  void s21_print_graph();
  void s21_print_curve(double Ox1, double Ox2, double Oy1, double Oy2);
  void s21_print_graph_error(int error_code);
  void s21_print_credit_error(int error_code);
  void s21_calculate_credit();
  int s21_get_credit_data(double *total, double *term, double *rate);
};
#endif  // MAINWINDOW_H
