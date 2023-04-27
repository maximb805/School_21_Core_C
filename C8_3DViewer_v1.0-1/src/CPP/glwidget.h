#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QWidget>

#include "mainwindow.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

class GLWidget : public QOpenGLWidget {
  friend class MainWindow;
  Q_OBJECT

 private:
  QString fileName = NULL;
  s21_uint_matrix indexes;
  unsigned int* indexes_array;
  s21_double_matrix vertexes;
  s21_double_matrix vertexes_base;
  size_t vertexes_coords_count = 0;
  size_t indexes_points_count = 0;
  int flag = 1, vert_flag = 0, edges_flag = 0;
  GLfloat points_size = 5, edges_thickness = 0.1;
  QPoint mPos;
  float xRot = 0, yRot = 0, zRot = 0, xRox_old = 0, yRot_old = 0;
  double min_x = 0, max_x = 0, min_y = 0, max_y = 0, min_z = 0, max_z = 0;
  GLfloat zoom = 0;
  GLfloat bg_color[3] = {0.8, 0.8, 0.8};
  GLfloat edges_color[3] = {0.0, 0.0, 0.0};
  GLfloat vertices_color[3] = {0.0, 0.0, 0.0};

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void drawModel();
  void mousePressEvent(QMouseEvent*) override;
  void mouseReleaseEvent(QMouseEvent*) override;
  void mouseMoveEvent(QMouseEvent*) override;
  void wheelEvent(QWheelEvent*) override;

 public:
  GLWidget(QWidget* parent = nullptr);
};

#endif  // GLWIDGET_H
