#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGifImage/src/gifimage/qgifimage.h>

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QLocale>
#include <QMainWindow>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QPalette>
#include <QSettings>
#include <QTimer>

extern "C" {
#include "../C/s21_3Dviewer.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  friend class GLWidget;
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  QSettings *settings;
  QTimer *timer;
  QGifImage *gif;
  QString screenshotName;
  QString gifName;
  int counter = 0;
  double xR = 0, yR = 0, zR = 0, xM = 0, yM = 0, zM = 0, scale = 1;
  double xM_prev = 0, yM_prev = 0, zM_prev = 0, scale_prev = 1;

 private slots:
  void on_pushButton_bg_color_clicked();
  void on_radioButton_central_clicked();
  void on_radioButton_parallel_clicked();
  void on_pushButton_screenshot_clicked();
  void on_pushButton_file_clicked();
  void on_pushButton_edges_color_clicked();
  void on_radioButton_vertices_none_clicked();
  void on_radioButton_vertices_square_clicked();
  void on_radioButton_vertices_round_clicked();
  void on_pushButton_vertices_color_clicked();
  void on_horizontalSlider_valueChanged(int value);
  void save_settings();
  void load_settings();
  void on_pushButton_restore_settings_clicked();
  void on_pushButton_create_gif_clicked();
  void gif_record();
  void stop_record();
  void affine_block_restore_settings();
  void free_matrixes();
  void color_block_load_settings();
  void on_radioButton_solid_edges_clicked();
  void on_radioButton_dashed_edges_clicked();
  void on_horizontalSlider_edges_valueChanged(int value);
  void on_doubleSpinBox_xM_valueChanged(double arg1);
  void on_doubleSpinBox_yM_valueChanged(double arg1);
  void on_doubleSpinBox_zM_valueChanged(double arg1);
  void on_doubleSpinBox_xR_valueChanged(double arg1);
  void on_doubleSpinBox_yR_valueChanged(double arg1);
  void on_doubleSpinBox_zR_valueChanged(double arg1);
  void on_doubleSpinBox_scale_valueChanged(double arg1);
};
#endif  // MAINWINDOW_H
