#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QLocale::setDefault(QLocale::c());
  ui->openGLWidget->indexes.matrix = NULL;
  ui->openGLWidget->vertexes.matrix = NULL;
  ui->openGLWidget->vertexes_base.matrix = NULL;
  settings = new QSettings(this);
  load_settings();
  ui->label_record_gif->hide();
}

MainWindow::~MainWindow() {
  save_settings();
  free_matrixes();
  delete ui;
}

void MainWindow::on_pushButton_bg_color_clicked() {
  QColor BGColor = QColorDialog::getColor(Qt::white, this, tr("Select color"));
  ui->openGLWidget->bg_color[0] = BGColor.redF();
  ui->openGLWidget->bg_color[1] = BGColor.greenF();
  ui->openGLWidget->bg_color[2] = BGColor.blueF();
  QPalette p = ui->lineEdit_bg_color->palette();
  p.setColor(QPalette::Base, BGColor);
  ui->lineEdit_bg_color->setPalette(p);
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_central_clicked() {
  ui->openGLWidget->flag = 1;
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_parallel_clicked() {
  ui->openGLWidget->flag = 0;
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_screenshot_clicked() {
  QFileDialog fileDialog(this, tr("Save as ..."), "");
  fileDialog.setAcceptMode(QFileDialog::AcceptSave);
  QStringList filters;
  filters << "JPG files (*.jpg)"
          << "BMP files (*.bmp)";
  fileDialog.setNameFilters(filters);
  if (fileDialog.exec() == QDialog::Accepted) {
    QString selectedFilter = fileDialog.selectedNameFilter();
    screenshotName = fileDialog.selectedFiles()[0];
    if (selectedFilter == "BMP files (*.bmp)") {
      if (!screenshotName.endsWith(".bmp")) {
        screenshotName += ".bmp";
      }
    } else if (selectedFilter == "JPG files (*.jpg)") {
      if (!screenshotName.endsWith(".jpg")) {
        screenshotName += ".jpg";
      }
    }
    ui->openGLWidget->grab().save(screenshotName);
    screenshotName = NULL;
  }
}

void MainWindow::on_pushButton_file_clicked() {
  QFileDialog fileDialog(this, tr("Open file"), "../src/obj");
  fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
  QStringList filters;
  filters << "OBJ files (*.obj)";
  fileDialog.setNameFilters(filters);
  if (fileDialog.exec() == QDialog::Accepted) {
    ui->openGLWidget->fileName = fileDialog.selectedFiles()[0];
    if (ui->openGLWidget->fileName.endsWith(".obj")) {
      free_matrixes();
      affine_block_restore_settings();
      s21_list *vertexes_list = NULL;
      s21_list *indexes_list = NULL;
      int error_code = s21_get_arrays(
          ui->openGLWidget->fileName.toLocal8Bit().data(), &vertexes_list,
          &ui->openGLWidget->vertexes_coords_count, &indexes_list,
          &ui->openGLWidget->indexes_points_count, &ui->openGLWidget->min_x,
          &ui->openGLWidget->max_x, &ui->openGLWidget->min_y,
          &ui->openGLWidget->max_y, &ui->openGLWidget->min_z,
          &ui->openGLWidget->max_z);
      if (error_code != 2) {
        error_code = s21_lists_to_matrixes(
            vertexes_list, &ui->openGLWidget->vertexes,
            &ui->openGLWidget->vertexes_base,
            ui->openGLWidget->vertexes_coords_count, indexes_list,
            &ui->openGLWidget->indexes, ui->openGLWidget->indexes_points_count,
            &ui->openGLWidget->indexes_array,
            (ui->openGLWidget->max_x + ui->openGLWidget->min_x) / 2,
            (ui->openGLWidget->max_y + ui->openGLWidget->min_y) / 2,
            (ui->openGLWidget->max_z + ui->openGLWidget->min_z) / 2);
      }
      size_t real_vertexes_count = 0;
      size_t real_edges_count = 0;
      if (!error_code) {
        s21_calc_verts_count(ui->openGLWidget->indexes_array,
                             ui->openGLWidget->indexes_points_count,
                             &real_vertexes_count);
        s21_calc_edges_count(ui->openGLWidget->indexes,
                             ui->openGLWidget->indexes_points_count / 2,
                             &real_edges_count);
      }
      ui->label_3->setText("Vertices: " + QString::number(real_vertexes_count));
      ui->label_2->setText("Edges: " + QString::number(real_edges_count));
      if (!error_code) {
        ui->openGLWidget->update();
        ui->label_4->setText(ui->openGLWidget->fileName);
      } else {
        if (error_code == 1) {
          ui->label_4->setText("Out of memory");
        } else if (error_code == 2) {
          ui->label_4->setText("No such file");
        } else if (error_code == 3) {
          ui->label_4->setText("No verices or surfaces specified in this file");
        }
      }
    } else {
      ui->label_4->setText("-");
      ui->openGLWidget->fileName = NULL;
    }
  }
}

void MainWindow::free_matrixes() {
  if (ui->openGLWidget->indexes.matrix != NULL) {
    if (ui->openGLWidget->indexes.matrix[0] != NULL) {
      free(ui->openGLWidget->indexes.matrix[0]);
    }
    free(ui->openGLWidget->indexes.matrix);
  }
  ui->openGLWidget->indexes_points_count = 0;
  if (ui->openGLWidget->vertexes.matrix != NULL) {
    if (ui->openGLWidget->vertexes.matrix[0] != NULL) {
      free(ui->openGLWidget->vertexes.matrix[0]);
    }
    free(ui->openGLWidget->vertexes.matrix);
  }
  ui->openGLWidget->vertexes_coords_count = 0;
  if (ui->openGLWidget->vertexes_base.matrix != NULL) {
    if (ui->openGLWidget->vertexes_base.matrix != NULL) {
      free(ui->openGLWidget->vertexes_base.matrix[0]);
    }
    free(ui->openGLWidget->vertexes_base.matrix);
  }
  ui->openGLWidget->vertexes.matrix = NULL;
  ui->openGLWidget->vertexes_base.matrix = NULL;
  ui->openGLWidget->indexes.matrix = NULL;
}

void MainWindow::on_pushButton_edges_color_clicked() {
  QColor EdgesColor =
      QColorDialog::getColor(Qt::white, this, tr("Select color"));
  ui->openGLWidget->edges_color[0] = EdgesColor.redF();
  ui->openGLWidget->edges_color[1] = EdgesColor.greenF();
  ui->openGLWidget->edges_color[2] = EdgesColor.blueF();
  QPalette e = ui->lineEdit_edges_color->palette();
  e.setColor(QPalette::Base, EdgesColor);
  ui->lineEdit_edges_color->setPalette(e);
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_vertices_none_clicked() {
  ui->openGLWidget->vert_flag = 0;
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_vertices_square_clicked() {
  ui->openGLWidget->vert_flag = 1;
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_vertices_round_clicked() {
  ui->openGLWidget->vert_flag = 2;
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_vertices_color_clicked() {
  QColor verticesColor =
      QColorDialog::getColor(Qt::white, this, tr("Select color"));
  ui->openGLWidget->vertices_color[0] = verticesColor.redF();
  ui->openGLWidget->vertices_color[1] = verticesColor.greenF();
  ui->openGLWidget->vertices_color[2] = verticesColor.blueF();
  QPalette e = ui->lineEdit_vertices_color->palette();
  e.setColor(QPalette::Base, verticesColor);
  ui->lineEdit_vertices_color->setPalette(e);
  ui->openGLWidget->update();
}

void MainWindow::on_horizontalSlider_valueChanged(int value) {
  ui->openGLWidget->points_size = value;
  ui->openGLWidget->update();
}

void MainWindow::save_settings() {
  settings->setValue("radioButton_parallel",
                     ui->radioButton_parallel->isChecked());
  settings->setValue("radioButton_central",
                     ui->radioButton_central->isChecked());
  settings->setValue("lineEdit_bg_color",
                     ui->lineEdit_bg_color->palette().base().color());
  settings->setValue("lineEdit_edges_color",
                     ui->lineEdit_edges_color->palette().base().color());
  settings->setValue("lineEdit_vertices_color",
                     ui->lineEdit_vertices_color->palette().base().color());
  settings->setValue("radioButton_vertices_none",
                     ui->radioButton_vertices_none->isChecked());
  settings->setValue("radioButton_vertices_square",
                     ui->radioButton_vertices_square->isChecked());
  settings->setValue("radioButton_vertices_round",
                     ui->radioButton_vertices_round->isChecked());
  settings->setValue("horizontalSlider", ui->horizontalSlider->value());
  settings->setValue("horizontalSliderPos",
                     ui->horizontalSlider->sliderPosition());
  settings->setValue("radioButton_solid_edges",
                     ui->radioButton_solid_edges->isChecked());
  settings->setValue("radioButton_dashed_edges",
                     ui->radioButton_dashed_edges->isChecked());
  settings->setValue("horizontalSlider_edges",
                     ui->horizontalSlider_edges->value());
  settings->setValue("horizontalSlider_edges_pos",
                     ui->horizontalSlider_edges->sliderPosition());
}

void MainWindow::load_settings() {
  ui->radioButton_parallel->setChecked(
      settings->value("radioButton_parallel", false).toBool());
  ui->radioButton_central->setChecked(
      settings->value("radioButton_central", true).toBool());
  if (ui->radioButton_central->isChecked()) {
    ui->openGLWidget->flag = 1;
  } else {
    ui->openGLWidget->flag = 0;
  }
  color_block_load_settings();
  ui->radioButton_vertices_none->setChecked(
      settings->value("radioButton_vertices_none", true).toBool());
  ui->radioButton_vertices_square->setChecked(
      settings->value("radioButton_vertices_square", false).toBool());
  ui->radioButton_vertices_round->setChecked(
      settings->value("radioButton_vertices_round", false).toBool());
  if (ui->radioButton_vertices_square->isChecked()) {
    ui->openGLWidget->vert_flag = 1;
  } else if (ui->radioButton_vertices_round->isChecked()) {
    ui->openGLWidget->vert_flag = 2;
  } else {
    ui->openGLWidget->vert_flag = 0;
  }
  ui->radioButton_solid_edges->setChecked(
      settings->value("radioButton_solid_edges", true).toBool());
  ui->radioButton_dashed_edges->setChecked(
      settings->value("radioButton_dashed_edges", false).toBool());
  if (ui->radioButton_dashed_edges->isChecked()) {
    ui->openGLWidget->edges_flag = 1;
  }
  ui->horizontalSlider_edges->setValue(
      settings->value("horizontalSlider_edges", 1).toInt());
  ui->horizontalSlider_edges->setSliderPosition(
      settings->value("horizontalSlider_edges_pos", 1).toInt());
  ui->horizontalSlider->setValue(
      settings->value("horizontalSlider", 5).toInt());
  ui->horizontalSlider->setSliderPosition(
      settings->value("horizontalSliderPos", 5).toInt());
  ui->openGLWidget->update();
}

void MainWindow::color_block_load_settings() {
  QPalette s = ui->lineEdit_bg_color->palette();
  QColor tmp;
  tmp.setRedF(0.8);
  tmp.setGreenF(0.8);
  tmp.setBlueF(0.8);
  s.setColor(QPalette::Base,
             settings->value("lineEdit_bg_color", tmp).value<QColor>());
  ui->lineEdit_bg_color->setPalette(s);
  ui->openGLWidget->bg_color[0] = s.base().color().redF();
  ui->openGLWidget->bg_color[1] = s.base().color().greenF();
  ui->openGLWidget->bg_color[2] = s.base().color().blueF();
  s.setColor(QPalette::Base,
             settings->value("lineEdit_edges_color").value<QColor>());
  ui->lineEdit_edges_color->setPalette(s);
  ui->openGLWidget->edges_color[0] = s.base().color().redF();
  ui->openGLWidget->edges_color[1] = s.base().color().greenF();
  ui->openGLWidget->edges_color[2] = s.base().color().blueF();
  s.setColor(QPalette::Base,
             settings->value("lineEdit_vertices_color").value<QColor>());
  ui->lineEdit_vertices_color->setPalette(s);
  ui->openGLWidget->vertices_color[0] = s.base().color().redF();
  ui->openGLWidget->vertices_color[1] = s.base().color().greenF();
  ui->openGLWidget->vertices_color[2] = s.base().color().blueF();
}

void MainWindow::on_pushButton_restore_settings_clicked() {
  ui->openGLWidget->bg_color[0] = 0.8;
  ui->openGLWidget->bg_color[1] = 0.8;
  ui->openGLWidget->bg_color[2] = 0.8;
  QColor tmp;
  tmp.setRedF(0.8);
  tmp.setGreenF(0.8);
  tmp.setBlueF(0.8);
  QPalette p = ui->lineEdit_bg_color->palette();
  p.setColor(QPalette::Base, tmp);
  ui->lineEdit_bg_color->setPalette(p);
  tmp.setRedF(0.0);
  tmp.setGreenF(0.0);
  tmp.setBlueF(0.0);
  p.setColor(QPalette::Base, tmp);
  ui->lineEdit_edges_color->setPalette(p);
  ui->lineEdit_vertices_color->setPalette(p);
  for (int i = 0; i < 3; i++) {
    ui->openGLWidget->edges_color[i] = 0.0;
    ui->openGLWidget->vertices_color[i] = 0.0;
  }
  ui->radioButton_central->setChecked(true);
  ui->openGLWidget->flag = 1;
  ui->radioButton_vertices_none->setChecked(true);
  ui->openGLWidget->vert_flag = 0;
  ui->horizontalSlider->setValue(5);
  ui->horizontalSlider->setSliderPosition(5);
  ui->openGLWidget->edges_flag = 0;
  ui->radioButton_solid_edges->setChecked(true);
  ui->openGLWidget->edges_thickness = 0.1;
  ui->horizontalSlider_edges->setSliderPosition(1);
  ui->horizontalSlider_edges->setValue(1);
  affine_block_restore_settings();
  ui->openGLWidget->update();
}

void MainWindow::affine_block_restore_settings() {
  ui->doubleSpinBox_xR->setValue(0);
  ui->doubleSpinBox_yR->setValue(0);
  ui->doubleSpinBox_zR->setValue(0);
  ui->doubleSpinBox_xM->setValue(0.00);
  ui->doubleSpinBox_yM->setValue(0.00);
  ui->doubleSpinBox_zM->setValue(0.00);
  ui->doubleSpinBox_scale->setValue(1);
  xR = yR = zR = xM = yM = zM = 0;
  scale = 1;
  xM_prev = yM_prev = zM_prev = 0;
  scale_prev = 1;
}

void MainWindow::on_pushButton_create_gif_clicked() {
  ui->label_record_gif->show();
  counter = 0;
  ui->pushButton_create_gif->setDisabled(true);
  gif = new QGifImage;
  gif->setDefaultDelay(10);
  timer = new QTimer(0);
  timer->setInterval(100);
  timer->start();
  connect(timer, SIGNAL(timeout()), this, SLOT(gif_record()));
}

void MainWindow::gif_record() {
  counter++;
  if (counter % 10 == 0) {
    if (counter == 10) {
      ui->label_record_gif->setText("Recording in progress... 4");
    } else if (counter == 20) {
      ui->label_record_gif->setText("Recording in progress... 3");
    } else if (counter == 30) {
      ui->label_record_gif->setText("Recording in progress... 2");
    } else if (counter == 40) {
      ui->label_record_gif->setText("Recording in progress... 1");
    }
  }
  QImage image = ui->openGLWidget->grabFramebuffer();
  image = image.scaled(640, 480);
  gif->addFrame(image);
  if (counter == 50) {
    stop_record();
  }
}

void MainWindow::stop_record() {
  ui->label_record_gif->hide();
  timer->stop();
  QFileDialog fileDialog(this, tr("Save as ..."), "");
  fileDialog.setAcceptMode(QFileDialog::AcceptSave);
  QStringList filters;
  filters << "GIF files (*.gif)";
  fileDialog.setNameFilters(filters);
  if (fileDialog.exec() == QDialog::Accepted) {
    QString selectedFilter = fileDialog.selectedNameFilter();
    gifName = fileDialog.selectedFiles()[0];
    if (!gifName.endsWith(".gif")) {
      gifName += ".gif";
    }
    gif->save(gifName);
    gifName = NULL;
  }
  ui->pushButton_create_gif->setDisabled(false);
}

void MainWindow::on_radioButton_solid_edges_clicked() {
  ui->openGLWidget->edges_flag = 0;
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_dashed_edges_clicked() {
  ui->openGLWidget->edges_flag = 1;
  ui->openGLWidget->update();
}

void MainWindow::on_horizontalSlider_edges_valueChanged(int value) {
  ui->openGLWidget->edges_thickness = value * 0.1;
  ui->openGLWidget->update();
}

void MainWindow::on_doubleSpinBox_xR_valueChanged(double arg1) {
  xR = arg1 * M_PI / 180.0;
  s21_rotate(&ui->openGLWidget->vertexes, &ui->openGLWidget->vertexes_base,
             ui->openGLWidget->vertexes_coords_count / 3, xR, yR, zR, xM, yM,
             zM);
  ui->openGLWidget->update();
}

void MainWindow::on_doubleSpinBox_yR_valueChanged(double arg1) {
  yR = arg1 * M_PI / 180.0;
  s21_rotate(&ui->openGLWidget->vertexes, &ui->openGLWidget->vertexes_base,
             ui->openGLWidget->vertexes_coords_count / 3, xR, yR, zR, xM, yM,
             zM);
  ui->openGLWidget->update();
}

void MainWindow::on_doubleSpinBox_zR_valueChanged(double arg1) {
  zR = arg1 * M_PI / 180.0;
  s21_rotate(&ui->openGLWidget->vertexes, &ui->openGLWidget->vertexes_base,
             ui->openGLWidget->vertexes_coords_count / 3, xR, yR, zR, xM, yM,
             zM);
  ui->openGLWidget->update();
}

void MainWindow::on_doubleSpinBox_xM_valueChanged(double arg1) {
  xM = arg1;
  s21_move(&ui->openGLWidget->vertexes,
           ui->openGLWidget->vertexes_coords_count / 3, xM - xM_prev,
           yM - yM_prev, zM - zM_prev);
  xM_prev = xM;
  ui->openGLWidget->update();
}

void MainWindow::on_doubleSpinBox_yM_valueChanged(double arg1) {
  yM = arg1;
  s21_move(&ui->openGLWidget->vertexes,
           ui->openGLWidget->vertexes_coords_count / 3, xM - xM_prev,
           yM - yM_prev, zM - zM_prev);
  yM_prev = yM;
  ui->openGLWidget->update();
}

void MainWindow::on_doubleSpinBox_zM_valueChanged(double arg1) {
  zM = arg1;
  s21_move(&ui->openGLWidget->vertexes,
           ui->openGLWidget->vertexes_coords_count / 3, xM - xM_prev,
           yM - yM_prev, zM - zM_prev);
  zM_prev = zM;
  ui->openGLWidget->update();
}

void MainWindow::on_doubleSpinBox_scale_valueChanged(double arg1) {
  if (arg1 == 0.0) {
      arg1 = 0.001;
  }
  scale = arg1;
  s21_rescale(&ui->openGLWidget->vertexes, &ui->openGLWidget->vertexes_base,
              ui->openGLWidget->vertexes_coords_count / 3, scale / scale_prev,
              xR, yR, zR, xM, yM, zM);
  scale_prev = scale;
  ui->openGLWidget->update();
}
