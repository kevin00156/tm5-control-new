/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "file_selector_widget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelGripperControl;
    QHBoxLayout *horizontalLayout;
    QPushButton *buttonSetGripperGrip;
    QPushButton *buttonSetGripperRelease;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QCheckBox *checkboxLaunchSim;
    QLineEdit *textRobotIP;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelGripperControl_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *buttonRecordPose;
    QPushButton *buttonReplayAllPoses;
    file_selector_widget *file_selector_widget_PoseControl;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *comboBox_PoseSelector;
    QPushButton *buttonReplaySinglePose;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 100, 170, 52));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        labelGripperControl = new QLabel(layoutWidget);
        labelGripperControl->setObjectName(QString::fromUtf8("labelGripperControl"));

        verticalLayout->addWidget(labelGripperControl);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        buttonSetGripperGrip = new QPushButton(layoutWidget);
        buttonSetGripperGrip->setObjectName(QString::fromUtf8("buttonSetGripperGrip"));

        horizontalLayout->addWidget(buttonSetGripperGrip);

        buttonSetGripperRelease = new QPushButton(layoutWidget);
        buttonSetGripperRelease->setObjectName(QString::fromUtf8("buttonSetGripperRelease"));

        horizontalLayout->addWidget(buttonSetGripperRelease);


        verticalLayout->addLayout(horizontalLayout);

        layoutWidget_2 = new QWidget(centralwidget);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(0, 10, 144, 87));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        checkboxLaunchSim = new QCheckBox(layoutWidget_2);
        checkboxLaunchSim->setObjectName(QString::fromUtf8("checkboxLaunchSim"));

        verticalLayout_2->addWidget(checkboxLaunchSim);

        textRobotIP = new QLineEdit(layoutWidget_2);
        textRobotIP->setObjectName(QString::fromUtf8("textRobotIP"));

        verticalLayout_2->addWidget(textRobotIP);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 152, 211, 131));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        labelGripperControl_2 = new QLabel(widget);
        labelGripperControl_2->setObjectName(QString::fromUtf8("labelGripperControl_2"));

        verticalLayout_3->addWidget(labelGripperControl_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        buttonRecordPose = new QPushButton(widget);
        buttonRecordPose->setObjectName(QString::fromUtf8("buttonRecordPose"));

        horizontalLayout_2->addWidget(buttonRecordPose);

        buttonReplayAllPoses = new QPushButton(widget);
        buttonReplayAllPoses->setObjectName(QString::fromUtf8("buttonReplayAllPoses"));

        horizontalLayout_2->addWidget(buttonReplayAllPoses);


        verticalLayout_3->addLayout(horizontalLayout_2);

        file_selector_widget_PoseControl = new file_selector_widget(widget);
        file_selector_widget_PoseControl->setObjectName(QString::fromUtf8("file_selector_widget_PoseControl"));

        verticalLayout_3->addWidget(file_selector_widget_PoseControl);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        comboBox_PoseSelector = new QComboBox(widget);
        comboBox_PoseSelector->setObjectName(QString::fromUtf8("comboBox_PoseSelector"));

        horizontalLayout_3->addWidget(comboBox_PoseSelector);

        buttonReplaySinglePose = new QPushButton(widget);
        buttonReplaySinglePose->setObjectName(QString::fromUtf8("buttonReplaySinglePose"));

        horizontalLayout_3->addWidget(buttonReplaySinglePose);


        verticalLayout_3->addLayout(horizontalLayout_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        labelGripperControl->setText(QApplication::translate("MainWindow", "GripperControl", nullptr));
        buttonSetGripperGrip->setText(QApplication::translate("MainWindow", "Grip", nullptr));
        buttonSetGripperRelease->setText(QApplication::translate("MainWindow", "Release", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "ROS_TM5", nullptr));
        checkboxLaunchSim->setText(QApplication::translate("MainWindow", "sim", nullptr));
        textRobotIP->setInputMask(QApplication::translate("MainWindow", "000.000.000.000;_", nullptr));
        textRobotIP->setText(QApplication::translate("MainWindow", "192.168.0.12", nullptr));
        labelGripperControl_2->setText(QApplication::translate("MainWindow", "PoseControl", nullptr));
        buttonRecordPose->setText(QApplication::translate("MainWindow", "Record", nullptr));
        buttonReplayAllPoses->setText(QApplication::translate("MainWindow", "Replay All", nullptr));
        buttonReplaySinglePose->setText(QApplication::translate("MainWindow", "Replay", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
