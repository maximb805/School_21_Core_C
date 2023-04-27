/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_3;
    QLineEdit *lineEdit_bg_color;
    QPushButton *pushButton_bg_color;
    QLineEdit *lineEdit_edges_color;
    QPushButton *pushButton_edges_color;
    QLineEdit *lineEdit_vertices_color;
    QPushButton *pushButton_vertices_color;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_12;
    QGroupBox *groupBox_4;
    QRadioButton *radioButton_solid_edges;
    QRadioButton *radioButton_dashed_edges;
    QLabel *label_20;
    QPushButton *pushButton_restore_settings;
    QGroupBox *groupBox;
    QRadioButton *radioButton_parallel;
    QRadioButton *radioButton_central;
    QLabel *label_9;
    QPushButton *pushButton_file;
    QLabel *label_record_gif;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton_screenshot;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton_vertices_none;
    QRadioButton *radioButton_vertices_square;
    QRadioButton *radioButton_vertices_round;
    QLabel *label_8;
    QGroupBox *groupBox_5;
    QLabel *label_11;
    QLabel *label_10;
    QSlider *horizontalSlider;
    QLabel *label;
    QGroupBox *groupBox_7;
    QLabel *label_37;
    QLabel *label_38;
    QSlider *horizontalSlider_edges;
    QLabel *label_39;
    QGroupBox *groupBox_6;
    QLabel *label_29;
    QLabel *label_31;
    QLabel *label_28;
    QLabel *label_30;
    QLabel *label_27;
    QLabel *label_34;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_26;
    QDoubleSpinBox *doubleSpinBox_scale;
    QDoubleSpinBox *doubleSpinBox_zM;
    QDoubleSpinBox *doubleSpinBox_yM;
    QDoubleSpinBox *doubleSpinBox_xM;
    QDoubleSpinBox *doubleSpinBox_xR;
    QDoubleSpinBox *doubleSpinBox_yR;
    QDoubleSpinBox *doubleSpinBox_zR;
    QPushButton *pushButton_create_gif;
    QLabel *label_4;
    GLWidget *openGLWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1072, 886);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setMinimumSize(QSize(265, 120));
        lineEdit_bg_color = new QLineEdit(groupBox_3);
        lineEdit_bg_color->setObjectName(QString::fromUtf8("lineEdit_bg_color"));
        lineEdit_bg_color->setGeometry(QRect(110, 30, 61, 21));
        QPalette palette;
        QBrush brush(QColor(200, 200, 200, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        QBrush brush1(QColor(239, 239, 239, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        lineEdit_bg_color->setPalette(palette);
        lineEdit_bg_color->setFrame(true);
        lineEdit_bg_color->setReadOnly(true);
        pushButton_bg_color = new QPushButton(groupBox_3);
        pushButton_bg_color->setObjectName(QString::fromUtf8("pushButton_bg_color"));
        pushButton_bg_color->setGeometry(QRect(180, 30, 80, 21));
        lineEdit_edges_color = new QLineEdit(groupBox_3);
        lineEdit_edges_color->setObjectName(QString::fromUtf8("lineEdit_edges_color"));
        lineEdit_edges_color->setGeometry(QRect(110, 60, 61, 21));
        QPalette palette1;
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        lineEdit_edges_color->setPalette(palette1);
        lineEdit_edges_color->setFrame(true);
        lineEdit_edges_color->setReadOnly(true);
        pushButton_edges_color = new QPushButton(groupBox_3);
        pushButton_edges_color->setObjectName(QString::fromUtf8("pushButton_edges_color"));
        pushButton_edges_color->setGeometry(QRect(180, 60, 80, 21));
        lineEdit_vertices_color = new QLineEdit(groupBox_3);
        lineEdit_vertices_color->setObjectName(QString::fromUtf8("lineEdit_vertices_color"));
        lineEdit_vertices_color->setGeometry(QRect(110, 90, 61, 21));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        lineEdit_vertices_color->setPalette(palette2);
        lineEdit_vertices_color->setFrame(true);
        lineEdit_vertices_color->setReadOnly(true);
        pushButton_vertices_color = new QPushButton(groupBox_3);
        pushButton_vertices_color->setObjectName(QString::fromUtf8("pushButton_vertices_color"));
        pushButton_vertices_color->setGeometry(QRect(180, 90, 80, 21));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 30, 91, 21));
        QFont font;
        font.setPointSize(10);
        font.setBold(false);
        label_5->setFont(font);
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 60, 51, 21));
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 90, 71, 21));
        label_7->setFont(font);
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(90, 0, 91, 31));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        label_12->setFont(font1);
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(groupBox_3, 2, 4, 1, 1);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        groupBox_4->setMinimumSize(QSize(265, 50));
        QFont font2;
        font2.setPointSize(9);
        groupBox_4->setFont(font2);
        groupBox_4->setAlignment(Qt::AlignCenter);
        groupBox_4->setFlat(false);
        radioButton_solid_edges = new QRadioButton(groupBox_4);
        radioButton_solid_edges->setObjectName(QString::fromUtf8("radioButton_solid_edges"));
        radioButton_solid_edges->setGeometry(QRect(50, 20, 71, 31));
        radioButton_solid_edges->setChecked(true);
        radioButton_solid_edges->setAutoExclusive(true);
        radioButton_dashed_edges = new QRadioButton(groupBox_4);
        radioButton_dashed_edges->setObjectName(QString::fromUtf8("radioButton_dashed_edges"));
        radioButton_dashed_edges->setGeometry(QRect(150, 20, 71, 31));
        radioButton_dashed_edges->setChecked(false);
        radioButton_dashed_edges->setAutoExclusive(true);
        label_20 = new QLabel(groupBox_4);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(90, 0, 91, 31));
        label_20->setFont(font1);

        gridLayout->addWidget(groupBox_4, 5, 4, 1, 1);

        pushButton_restore_settings = new QPushButton(centralwidget);
        pushButton_restore_settings->setObjectName(QString::fromUtf8("pushButton_restore_settings"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_restore_settings->sizePolicy().hasHeightForWidth());
        pushButton_restore_settings->setSizePolicy(sizePolicy1);
        pushButton_restore_settings->setMinimumSize(QSize(0, 50));
        QFont font3;
        font3.setBold(false);
        pushButton_restore_settings->setFont(font3);

        gridLayout->addWidget(pushButton_restore_settings, 8, 4, 2, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(265, 50));
        groupBox->setFont(font2);
        groupBox->setAlignment(Qt::AlignCenter);
        groupBox->setFlat(false);
        radioButton_parallel = new QRadioButton(groupBox);
        radioButton_parallel->setObjectName(QString::fromUtf8("radioButton_parallel"));
        radioButton_parallel->setGeometry(QRect(50, 20, 71, 31));
        radioButton_parallel->setChecked(false);
        radioButton_parallel->setAutoExclusive(true);
        radioButton_central = new QRadioButton(groupBox);
        radioButton_central->setObjectName(QString::fromUtf8("radioButton_central"));
        radioButton_central->setGeometry(QRect(150, 20, 71, 31));
        radioButton_central->setChecked(true);
        radioButton_central->setAutoExclusive(true);
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(80, 0, 121, 31));
        label_9->setFont(font1);

        gridLayout->addWidget(groupBox, 1, 4, 1, 1);

        pushButton_file = new QPushButton(centralwidget);
        pushButton_file->setObjectName(QString::fromUtf8("pushButton_file"));
        sizePolicy1.setHeightForWidth(pushButton_file->sizePolicy().hasHeightForWidth());
        pushButton_file->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_file, 0, 0, 1, 1);

        label_record_gif = new QLabel(centralwidget);
        label_record_gif->setObjectName(QString::fromUtf8("label_record_gif"));
        label_record_gif->setEnabled(true);
        sizePolicy1.setHeightForWidth(label_record_gif->sizePolicy().hasHeightForWidth());
        label_record_gif->setSizePolicy(sizePolicy1);
        QFont font4;
        font4.setPointSize(10);
        label_record_gif->setFont(font4);
        label_record_gif->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_record_gif, 8, 2, 1, 2);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setFont(font4);

        gridLayout->addWidget(label_2, 8, 0, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setFont(font4);

        gridLayout->addWidget(label_3, 8, 1, 1, 1);

        pushButton_screenshot = new QPushButton(centralwidget);
        pushButton_screenshot->setObjectName(QString::fromUtf8("pushButton_screenshot"));
        sizePolicy1.setHeightForWidth(pushButton_screenshot->sizePolicy().hasHeightForWidth());
        pushButton_screenshot->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_screenshot, 9, 0, 1, 2);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMinimumSize(QSize(265, 50));
        groupBox_2->setAlignment(Qt::AlignCenter);
        radioButton_vertices_none = new QRadioButton(groupBox_2);
        radioButton_vertices_none->setObjectName(QString::fromUtf8("radioButton_vertices_none"));
        radioButton_vertices_none->setGeometry(QRect(20, 20, 61, 31));
        radioButton_vertices_none->setChecked(true);
        radioButton_vertices_none->setAutoExclusive(true);
        radioButton_vertices_square = new QRadioButton(groupBox_2);
        radioButton_vertices_square->setObjectName(QString::fromUtf8("radioButton_vertices_square"));
        radioButton_vertices_square->setGeometry(QRect(100, 20, 71, 31));
        radioButton_vertices_square->setChecked(false);
        radioButton_vertices_square->setAutoExclusive(true);
        radioButton_vertices_round = new QRadioButton(groupBox_2);
        radioButton_vertices_round->setObjectName(QString::fromUtf8("radioButton_vertices_round"));
        radioButton_vertices_round->setGeometry(QRect(190, 20, 61, 31));
        radioButton_vertices_round->setAutoExclusive(true);
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(80, 0, 111, 31));
        label_8->setFont(font1);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(groupBox_2, 3, 4, 1, 1);

        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        sizePolicy.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy);
        groupBox_5->setMinimumSize(QSize(265, 70));
        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(190, 50, 31, 20));
        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(80, 0, 111, 31));
        label_10->setFont(font1);
        label_10->setAlignment(Qt::AlignCenter);
        horizontalSlider = new QSlider(groupBox_5);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(50, 30, 160, 21));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(100);
        horizontalSlider->setValue(5);
        horizontalSlider->setSliderPosition(5);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBelow);
        horizontalSlider->setTickInterval(5);
        label = new QLabel(groupBox_5);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(53, 50, 20, 20));

        gridLayout->addWidget(groupBox_5, 4, 4, 1, 1);

        groupBox_7 = new QGroupBox(centralwidget);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        sizePolicy.setHeightForWidth(groupBox_7->sizePolicy().hasHeightForWidth());
        groupBox_7->setSizePolicy(sizePolicy);
        groupBox_7->setMinimumSize(QSize(265, 70));
        label_37 = new QLabel(groupBox_7);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setGeometry(QRect(200, 50, 21, 20));
        label_38 = new QLabel(groupBox_7);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setGeometry(QRect(70, 0, 131, 31));
        label_38->setFont(font1);
        label_38->setAlignment(Qt::AlignCenter);
        horizontalSlider_edges = new QSlider(groupBox_7);
        horizontalSlider_edges->setObjectName(QString::fromUtf8("horizontalSlider_edges"));
        horizontalSlider_edges->setGeometry(QRect(50, 30, 160, 21));
        horizontalSlider_edges->setMinimum(1);
        horizontalSlider_edges->setMaximum(100);
        horizontalSlider_edges->setPageStep(10);
        horizontalSlider_edges->setValue(1);
        horizontalSlider_edges->setSliderPosition(1);
        horizontalSlider_edges->setOrientation(Qt::Horizontal);
        horizontalSlider_edges->setTickPosition(QSlider::TicksBelow);
        horizontalSlider_edges->setTickInterval(0);
        label_39 = new QLabel(groupBox_7);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setGeometry(QRect(45, 50, 21, 20));

        gridLayout->addWidget(groupBox_7, 6, 4, 1, 1);

        groupBox_6 = new QGroupBox(centralwidget);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        sizePolicy.setHeightForWidth(groupBox_6->sizePolicy().hasHeightForWidth());
        groupBox_6->setSizePolicy(sizePolicy);
        groupBox_6->setMinimumSize(QSize(265, 330));
        label_29 = new QLabel(groupBox_6);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(0, 30, 31, 21));
        label_29->setFont(font1);
        label_29->setAlignment(Qt::AlignCenter);
        label_31 = new QLabel(groupBox_6);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(0, 110, 31, 21));
        label_31->setFont(font1);
        label_31->setAlignment(Qt::AlignCenter);
        label_28 = new QLabel(groupBox_6);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(90, 140, 111, 21));
        label_28->setFont(font1);
        label_28->setAlignment(Qt::AlignCenter);
        label_30 = new QLabel(groupBox_6);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(0, 70, 31, 21));
        label_30->setFont(font1);
        label_30->setAlignment(Qt::AlignCenter);
        label_27 = new QLabel(groupBox_6);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(90, 0, 111, 31));
        label_27->setFont(font1);
        label_27->setAlignment(Qt::AlignCenter);
        label_34 = new QLabel(groupBox_6);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(0, 250, 31, 21));
        label_34->setFont(font1);
        label_34->setAlignment(Qt::AlignCenter);
        label_32 = new QLabel(groupBox_6);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(0, 170, 31, 21));
        label_32->setFont(font1);
        label_32->setAlignment(Qt::AlignCenter);
        label_33 = new QLabel(groupBox_6);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(0, 210, 31, 21));
        label_33->setFont(font1);
        label_33->setAlignment(Qt::AlignCenter);
        label_26 = new QLabel(groupBox_6);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(90, 280, 111, 21));
        label_26->setFont(font1);
        label_26->setAlignment(Qt::AlignCenter);
        doubleSpinBox_scale = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_scale->setObjectName(QString::fromUtf8("doubleSpinBox_scale"));
        doubleSpinBox_scale->setGeometry(QRect(30, 300, 231, 24));
        doubleSpinBox_scale->setMinimum(-100.000000000000000);
        doubleSpinBox_scale->setMaximum(100.000000000000000);
        doubleSpinBox_scale->setSingleStep(0.010000000000000);
        doubleSpinBox_scale->setValue(1.000000000000000);
        doubleSpinBox_zM = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_zM->setObjectName(QString::fromUtf8("doubleSpinBox_zM"));
        doubleSpinBox_zM->setGeometry(QRect(30, 250, 231, 24));
        doubleSpinBox_zM->setMinimum(-100.000000000000000);
        doubleSpinBox_zM->setMaximum(100.000000000000000);
        doubleSpinBox_zM->setSingleStep(0.010000000000000);
        doubleSpinBox_zM->setValue(0.000000000000000);
        doubleSpinBox_yM = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_yM->setObjectName(QString::fromUtf8("doubleSpinBox_yM"));
        doubleSpinBox_yM->setGeometry(QRect(30, 210, 231, 24));
        doubleSpinBox_yM->setMinimum(-100.000000000000000);
        doubleSpinBox_yM->setMaximum(100.000000000000000);
        doubleSpinBox_yM->setSingleStep(0.010000000000000);
        doubleSpinBox_yM->setValue(0.000000000000000);
        doubleSpinBox_xM = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_xM->setObjectName(QString::fromUtf8("doubleSpinBox_xM"));
        doubleSpinBox_xM->setGeometry(QRect(30, 170, 231, 24));
        doubleSpinBox_xM->setMinimum(-100.000000000000000);
        doubleSpinBox_xM->setMaximum(100.000000000000000);
        doubleSpinBox_xM->setSingleStep(0.010000000000000);
        doubleSpinBox_xM->setValue(0.000000000000000);
        doubleSpinBox_xR = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_xR->setObjectName(QString::fromUtf8("doubleSpinBox_xR"));
        doubleSpinBox_xR->setGeometry(QRect(30, 30, 231, 24));
        doubleSpinBox_xR->setDecimals(0);
        doubleSpinBox_xR->setMinimum(-1080.000000000000000);
        doubleSpinBox_xR->setMaximum(1080.000000000000000);
        doubleSpinBox_xR->setSingleStep(1.000000000000000);
        doubleSpinBox_xR->setValue(0.000000000000000);
        doubleSpinBox_yR = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_yR->setObjectName(QString::fromUtf8("doubleSpinBox_yR"));
        doubleSpinBox_yR->setGeometry(QRect(30, 70, 231, 24));
        doubleSpinBox_yR->setDecimals(0);
        doubleSpinBox_yR->setMinimum(-1080.000000000000000);
        doubleSpinBox_yR->setMaximum(1080.000000000000000);
        doubleSpinBox_yR->setSingleStep(1.000000000000000);
        doubleSpinBox_yR->setValue(0.000000000000000);
        doubleSpinBox_zR = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_zR->setObjectName(QString::fromUtf8("doubleSpinBox_zR"));
        doubleSpinBox_zR->setGeometry(QRect(30, 110, 231, 24));
        doubleSpinBox_zR->setDecimals(0);
        doubleSpinBox_zR->setMinimum(-1080.000000000000000);
        doubleSpinBox_zR->setMaximum(1080.000000000000000);
        doubleSpinBox_zR->setSingleStep(1.000000000000000);
        doubleSpinBox_zR->setValue(0.000000000000000);

        gridLayout->addWidget(groupBox_6, 7, 4, 1, 1);

        pushButton_create_gif = new QPushButton(centralwidget);
        pushButton_create_gif->setObjectName(QString::fromUtf8("pushButton_create_gif"));
        sizePolicy1.setHeightForWidth(pushButton_create_gif->sizePolicy().hasHeightForWidth());
        pushButton_create_gif->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_create_gif, 9, 2, 1, 2);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setMinimumSize(QSize(0, 17));
        label_4->setWordWrap(true);

        gridLayout->addWidget(label_4, 0, 1, 1, 4);

        openGLWidget = new GLWidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(openGLWidget, 1, 0, 7, 4);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "3dViewer v1.0", nullptr));
        groupBox_3->setTitle(QString());
        pushButton_bg_color->setText(QCoreApplication::translate("MainWindow", "Choose", nullptr));
        pushButton_edges_color->setText(QCoreApplication::translate("MainWindow", "Choose", nullptr));
        pushButton_vertices_color->setText(QCoreApplication::translate("MainWindow", "Choose", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Background", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Edges", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Vertices", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Color", nullptr));
        groupBox_4->setTitle(QString());
        radioButton_solid_edges->setText(QCoreApplication::translate("MainWindow", "Solid", nullptr));
        radioButton_dashed_edges->setText(QCoreApplication::translate("MainWindow", "Dashed", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Edges type", nullptr));
        pushButton_restore_settings->setText(QCoreApplication::translate("MainWindow", "Restore default settings", nullptr));
        groupBox->setTitle(QString());
        radioButton_parallel->setText(QCoreApplication::translate("MainWindow", "Parallel", nullptr));
        radioButton_central->setText(QCoreApplication::translate("MainWindow", "Central", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Projection type", nullptr));
        pushButton_file->setText(QCoreApplication::translate("MainWindow", "Open file", nullptr));
        label_record_gif->setText(QCoreApplication::translate("MainWindow", "Recording in progress... 5", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Vertices: -", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Edges: -", nullptr));
        pushButton_screenshot->setText(QCoreApplication::translate("MainWindow", "Screenshot", nullptr));
        groupBox_2->setTitle(QString());
        radioButton_vertices_none->setText(QCoreApplication::translate("MainWindow", "None", nullptr));
        radioButton_vertices_square->setText(QCoreApplication::translate("MainWindow", "Square", nullptr));
        radioButton_vertices_round->setText(QCoreApplication::translate("MainWindow", "Round", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Vertices type", nullptr));
        groupBox_5->setTitle(QString());
        label_11->setText(QCoreApplication::translate("MainWindow", "100", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Vertices size", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        groupBox_7->setTitle(QString());
        label_37->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "Edges thickness", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "0.1", nullptr));
        groupBox_6->setTitle(QString());
        label_29->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "Move", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "Rotate", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "Scale", nullptr));
        pushButton_create_gif->setText(QCoreApplication::translate("MainWindow", "Create gif", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
