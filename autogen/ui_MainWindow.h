/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionClose;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *controls;
    QGridLayout *gridLayout_2;
    QLabel *labelTop;
    QGridLayout *glLayout;
    QFrame *line;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_FieldOfView;
    QLabel *label_3;
    QComboBox *switch_projection;
    QSlider *slider_FieldOfView;
    QDoubleSpinBox *box_nearPlane;
    QLabel *label_12;
    QDoubleSpinBox *box_FarPlane;
    QGroupBox *groupBox_2;
    QComboBox *switch_renderingMode;
    QLabel *label_renderingMode;
    QLabel *label_Iso;
    QDoubleSpinBox *box_Iso;
    QGroupBox *groupBox_5;
    QLabel *label_9;
    QLCDNumber *usedMemLCD;
    QLabel *label_10;
    QLabel *label_11;
    QLCDNumber *memSizeLCD;
    QVBoxLayout *verticalLayout_2;
    QProgressBar *progressBar;
    QMenuBar *menubar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 720);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1280, 720));
        MainWindow->setMaximumSize(QSize(1280, 720));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        controls = new QWidget(centralwidget);
        controls->setObjectName(QString::fromUtf8("controls"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(controls->sizePolicy().hasHeightForWidth());
        controls->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(controls);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        labelTop = new QLabel(controls);
        labelTop->setObjectName(QString::fromUtf8("labelTop"));

        gridLayout_2->addWidget(labelTop, 2, 0, 1, 1);


        gridLayout->addWidget(controls, 0, 0, 1, 1);

        glLayout = new QGridLayout();
        glLayout->setObjectName(QString::fromUtf8("glLayout"));

        gridLayout->addLayout(glLayout, 2, 0, 1, 1);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 1);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy2);
        widget_2->setMinimumSize(QSize(250, 0));
        widget_2->setMaximumSize(QSize(300, 16777215));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(widget_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        groupBox->setMinimumSize(QSize(200, 0));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 47, 13));
        label_FieldOfView = new QLabel(groupBox);
        label_FieldOfView->setObjectName(QString::fromUtf8("label_FieldOfView"));
        label_FieldOfView->setGeometry(QRect(20, 60, 71, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 90, 61, 16));
        switch_projection = new QComboBox(groupBox);
        switch_projection->addItem(QString());
        switch_projection->addItem(QString());
        switch_projection->setObjectName(QString::fromUtf8("switch_projection"));
        switch_projection->setGeometry(QRect(100, 30, 111, 22));
        slider_FieldOfView = new QSlider(groupBox);
        slider_FieldOfView->setObjectName(QString::fromUtf8("slider_FieldOfView"));
        slider_FieldOfView->setGeometry(QRect(100, 60, 111, 22));
        slider_FieldOfView->setMinimum(1);
        slider_FieldOfView->setMaximum(179);
        slider_FieldOfView->setValue(45);
        slider_FieldOfView->setOrientation(Qt::Horizontal);
        box_nearPlane = new QDoubleSpinBox(groupBox);
        box_nearPlane->setObjectName(QString::fromUtf8("box_nearPlane"));
        box_nearPlane->setGeometry(QRect(100, 90, 111, 22));
        box_nearPlane->setMinimum(0.010000000000000);
        box_nearPlane->setSingleStep(0.100000000000000);
        box_nearPlane->setValue(0.100000000000000);
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 120, 51, 16));
        box_FarPlane = new QDoubleSpinBox(groupBox);
        box_FarPlane->setObjectName(QString::fromUtf8("box_FarPlane"));
        box_FarPlane->setGeometry(QRect(100, 120, 111, 22));
        box_FarPlane->setMaximum(50000.000000000000000);
        box_FarPlane->setSingleStep(0.100000000000000);
        box_FarPlane->setValue(500.000000000000000);

        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(widget_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy3.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy3);
        groupBox_2->setMinimumSize(QSize(200, 0));
        switch_renderingMode = new QComboBox(groupBox_2);
        switch_renderingMode->addItem(QString());
        switch_renderingMode->addItem(QString());
        switch_renderingMode->addItem(QString());
        switch_renderingMode->addItem(QString());
        switch_renderingMode->setObjectName(QString::fromUtf8("switch_renderingMode"));
        switch_renderingMode->setGeometry(QRect(100, 30, 111, 22));
        label_renderingMode = new QLabel(groupBox_2);
        label_renderingMode->setObjectName(QString::fromUtf8("label_renderingMode"));
        label_renderingMode->setGeometry(QRect(20, 30, 47, 20));
        label_Iso = new QLabel(groupBox_2);
        label_Iso->setObjectName(QString::fromUtf8("label_Iso"));
        label_Iso->setGeometry(QRect(20, 60, 47, 20));
        box_Iso = new QDoubleSpinBox(groupBox_2);
        box_Iso->setObjectName(QString::fromUtf8("box_Iso"));
        box_Iso->setGeometry(QRect(100, 60, 111, 22));
        box_Iso->setDecimals(5);
        box_Iso->setMinimum(0.000000000000000);
        box_Iso->setMaximum(1.000000000000000);
        box_Iso->setSingleStep(0.005000000000000);
        box_Iso->setValue(0.100000000000000);

        verticalLayout->addWidget(groupBox_2);

        groupBox_5 = new QGroupBox(widget_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        sizePolicy3.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy3);
        groupBox_5->setMinimumSize(QSize(200, 0));
        label_9 = new QLabel(groupBox_5);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 60, 91, 16));
        usedMemLCD = new QLCDNumber(groupBox_5);
        usedMemLCD->setObjectName(QString::fromUtf8("usedMemLCD"));
        usedMemLCD->setGeometry(QRect(110, 60, 64, 23));
        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 20, 51, 21));
        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 20, 91, 21));
        memSizeLCD = new QLCDNumber(groupBox_5);
        memSizeLCD->setObjectName(QString::fromUtf8("memSizeLCD"));
        memSizeLCD->setGeometry(QRect(110, 20, 64, 23));
        memSizeLCD->setSegmentStyle(QLCDNumber::Filled);

        verticalLayout->addWidget(groupBox_5);


        gridLayout->addWidget(widget_2, 2, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setEnabled(false);
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy4);
        progressBar->setMaximum(100);
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        verticalLayout_2->addWidget(progressBar);


        gridLayout->addLayout(verticalLayout_2, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1282, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Visualisierung 1", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open ...", nullptr));
        actionClose->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        labelTop->setText(QCoreApplication::translate("MainWindow", "No data loaded", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Camera", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Projection", nullptr));
        label_FieldOfView->setText(QCoreApplication::translate("MainWindow", "Field Of View", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Near Plane", nullptr));
        switch_projection->setItemText(0, QCoreApplication::translate("MainWindow", "Perspective", nullptr));
        switch_projection->setItemText(1, QCoreApplication::translate("MainWindow", "Orthographic", nullptr));

        label_12->setText(QCoreApplication::translate("MainWindow", "Far Plane", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Rendering", nullptr));
        switch_renderingMode->setItemText(0, QCoreApplication::translate("MainWindow", "Front Faces", nullptr));
        switch_renderingMode->setItemText(1, QCoreApplication::translate("MainWindow", "Back Faces", nullptr));
        switch_renderingMode->setItemText(2, QCoreApplication::translate("MainWindow", "Positions", nullptr));
        switch_renderingMode->setItemText(3, QCoreApplication::translate("MainWindow", "Shaded", nullptr));

        label_renderingMode->setText(QCoreApplication::translate("MainWindow", "Mode", nullptr));
        label_Iso->setText(QCoreApplication::translate("MainWindow", "Iso-Value", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "GPU", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Used Memory (MB)", nullptr));
        label_10->setText(QString());
        label_11->setText(QCoreApplication::translate("MainWindow", "Total Memory (MB)", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
