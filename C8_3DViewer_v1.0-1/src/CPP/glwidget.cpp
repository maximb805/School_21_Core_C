#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void GLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void GLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1, 1, -1, 1, 1, 3);
}

void GLWidget::paintGL() {
  glClearColor(bg_color[0], bg_color[1], bg_color[2], 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  double max_range =
      s21_get_max_range(min_x, max_x, min_y, max_y, min_z, max_z);
  glTranslatef(0, 0, -(max_range * 1.74 / 2 + 1));
  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);
  if (flag == 0) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-(max_range + zoom), max_range + zoom, -(max_range + zoom),
            max_range + zoom, -10000, 10000);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-(1 + zoom), 1 + zoom, -(1 + zoom), 1 + zoom, 1, 10000);
  }
  drawModel();
}

void GLWidget::drawModel() {
  if (!fileName.isNull() && vertexes_coords_count && indexes_points_count) {
    glColor3f(edges_color[0], edges_color[1], edges_color[2]);
    glVertexPointer(3, GL_DOUBLE, 0, vertexes.matrix[0]);
    glEnableClientState(GL_VERTEX_ARRAY);
    if (edges_flag == 1) {
      glLineStipple(10, 0x3333);
      glEnable(GL_LINE_STIPPLE);
    } else {
      glDisable(GL_LINE_STIPPLE);
    }
    glLineWidth(edges_thickness);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_LINES, indexes_points_count, GL_UNSIGNED_INT,
                   indexes.matrix[0]);
    if (vert_flag > 0) {
      glColor3f(vertices_color[0], vertices_color[1], vertices_color[2]);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      if (vert_flag == 2) {
        glEnable(GL_POINT_SMOOTH);
      }
      glPointSize(points_size);
      glDrawElements(GL_POINTS, indexes_points_count, GL_UNSIGNED_INT,
                     indexes.matrix[0]);
      glDisable(GL_POINT_SMOOTH);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void GLWidget::mousePressEvent(QMouseEvent *event) { mPos = event->pos(); }

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  xRot = 1 / M_PI * (event->pos().y() - mPos.y()) + xRox_old;
  yRot = 1 / M_PI * (event->pos().x() - mPos.x()) + yRot_old;
  update();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event) {
  xRox_old = xRot;
  yRot_old = yRot;
}

void GLWidget::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0) {
    zoom -= 0.15;
  } else if (event->angleDelta().y() < 0) {
    zoom += 0.15;
  }
  update();
}
